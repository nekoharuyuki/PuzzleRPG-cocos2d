#include "PuzzleGameScene.h"
#include "BattleCharSprite.h"
#include "CharIconSprite.h"
#include "ResultScene.h"
#include "QuestScene.h"
#include "MapData.h"
#include "CharData.h"
#include "PlayerValue.h"
#include "PartyValue.h"
#include "AudioManager.h"
#include "VisibleRect.h"
#include "DamageEffect.h"

#define PUZZLE_NUM_X 6
#define PUZZLE_NUM_Y 6

#define MOTION_STREAK_TAG 10

USING_NS_CC;

using namespace cocostudio::timeline;

int PuzzleGameScene::m_questNo = 0;

//コンストラクタ
PuzzleGameScene::PuzzleGameScene()
: m_movingPuzzle(nullptr)
, m_touchable(true)
, m_maxRemovedNo(0)
, m_chainNumber(0)
{
    //乱数初期化および各ボールの出現の重みを指定
    std::random_device device;
    m_engine = std::default_random_engine(device());
    m_distForPuzzle = std::discrete_distribution<int>{20, 20, 20, 20, 20, 0};
    m_distForMember = std::uniform_int_distribution<int>(0, 2);
    m_distForEnemy = std::uniform_int_distribution<int>(0, 2);
}

//シーン生成
Scene* PuzzleGameScene::createScene(int questNo)
{
    m_questNo = questNo;
    
    auto scene = Scene::create();
    auto layer = PuzzleGameScene::create();
    scene->addChild(layer);
    
    return scene;
}

//初期化
bool PuzzleGameScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    
    initBackground(); //背景の初期化
    
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    node->setLocalZOrder(ZOrder::BgForPuzzle);
    
    // Animationを読み込む
    auto action = ActionTimelineCache::getInstance()->createAction(m_fileName.c_str());
    if(action) {
        node->runAction(action);
        action->gotoFrameAndPause(m_questNo);
    }
    
    // バトル中のBGM再生
    AudioManager::getInstance()->playBgm("battle");
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(PuzzleGameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PuzzleGameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PuzzleGameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(PuzzleGameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initPuzzles(); //ボールの初期表示
    initEnemy(node); //敵の表示
    initMembers(node); //メンバーの表示
    
    // メニューへ戻るボタン
    // ボタンノードを取得
    auto startBtn = node->getChildByName<ui::Button*>("menu_button");
    // タッチイベント追加
    startBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.5f);
        
        // クエストシーンへ移行する
        auto startGame = CallFunc::create([]{
            auto scene = QuestScene::createScene();
            AudioManager::getInstance()->playBgm("all_bgm");
            auto transition = TransitionFadeBL::create(0.5f, scene);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay, startGame, NULL));
    });
    
    return true;
}

//背景の初期化
void PuzzleGameScene::initBackground()
{
    //パズル部の背景
    FileUtils::getInstance()->addSearchPath("asset");
    auto bgForPuzzle = Sprite::create("shared/bg.png");
    if(bgForPuzzle){
        bgForPuzzle->setAnchorPoint(Point::ZERO);
        bgForPuzzle->setPosition(Point::ZERO);
        addChild(bgForPuzzle, ZOrder::BgForPuzzle);
    }
}

//ボールの初期表示
void PuzzleGameScene::initPuzzles()
{
    for (int x = 1; x <= PUZZLE_NUM_X; x++){
        for (int y = 1; y <= PUZZLE_NUM_Y; y++){
            //ボールを生成する
            newPuzzles(PuzzleSprite::PositionIndex(x, y), true);
        }
    }
}

//新規ボール作成
PuzzleSprite* PuzzleGameScene::newPuzzles(PuzzleSprite::PositionIndex positionIndex, bool visible)
{
    //現在のタグを取得
    int currentTag = PuzzleSprite::generateTag(positionIndex);
    
    //乱数を元に、ランダムでタイプを取得
    int puzzleType = m_distForPuzzle(m_engine);
    while (true)
    {
        puzzleType = m_distForPuzzle(m_engine);
        
        if (!visible){ break; }
        
        //妥当性のチェック（ボールが隣り合わせにならないようにする）
        
        //左隣のボール
        auto puzzleX1Tag = currentTag - 10; //1つ左隣は10引いた値
        auto puzzleX2Tag = currentTag - 20; //2つ左隣は20引いた値
        auto puzzleX1 = (PuzzleSprite*)(getChildByTag(puzzleX1Tag));
        auto puzzleX2 = (PuzzleSprite*)(getChildByTag(puzzleX2Tag));
        
        //現在のボールが、1つ左隣と2つ左隣のボールと同じだとNG
        if (!(puzzleX1 && puzzleType == (int)puzzleX1->getPuzzleType()) ||
            !(puzzleX2 && puzzleType == (int)puzzleX2->getPuzzleType()))
        {
            //下隣のボール
            auto puzzleY1Tag = currentTag - 1; //1つ下隣は1引いた値
            auto puzzleY2Tag = currentTag - 2; //2つ下隣は2引いた値
            auto puzzleY1 = (PuzzleSprite*)(getChildByTag(puzzleY1Tag));
            auto puzzleY2 = (PuzzleSprite*)(getChildByTag(puzzleY2Tag));
            
            //現在のボールが、1つ下隣と2つ下隣のボールと同じだとNG
            if (!(puzzleY1 && puzzleType == (int)puzzleY1->getPuzzleType()) ||
                !(puzzleY2 && puzzleType == (int)puzzleY2->getPuzzleType()))
            {
                //左隣と下隣が揃わない場合は、ループを抜ける
                break;
            }
        }
    }
    
    //ボールの表示
    auto puzzle = PuzzleSprite::create((PuzzleSprite::PuzzleType)puzzleType, visible);
    if(puzzle){
        puzzle->setPositionIndexAndChangePosition(positionIndex);
        addChild(puzzle, ZOrder::Ball);
    }
    return puzzle;
}

bool PuzzleGameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    // 指でなぞったラインを描画する
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = MotionStreak::create(0.5f, 1.0f, 10.0f, Color3B(255, 255, 0), "system/images/line.png");
    pStreak->setPosition(point);
    this->addChild(pStreak, ZOrder::Ball + 1, MOTION_STREAK_TAG);
    
    // パズルのタッチイベント
    if (!m_touchable){
        return false;
    }
    m_movingPuzzle = getTouchPuzzle(touch->getLocation());
    
    if (m_movingPuzzle){
        return true;
    }else{
        return false;
    }
}

void PuzzleGameScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    // 指でなぞったラインを描画する
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = (MotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
    
    //スワイプとともにボールを移動する
    m_movingPuzzle->setPosition(m_movingPuzzle->getPosition() + touch->getDelta());
    
    //移動しているボールが、別のボールの位置に移動
    auto touchPuzzle = getTouchPuzzle(touch->getLocation(), m_movingPuzzle->getPositionIndex());
    if (touchPuzzle && m_movingPuzzle != touchPuzzle){
        // ボール移動時のSE再生
        AudioManager::getInstance()->playSe("moving_puzzle");
        //別のボールの位置インデックスを取得
        auto touchPuzzlePositionIndex = touchPuzzle->getPositionIndex();
        //別のボールを移動しているボールの元の位置へ移動する
        touchPuzzle->setPositionIndexAndChangePosition(m_movingPuzzle->getPositionIndex());
        //移動しているボールの情報を変更
        m_movingPuzzle->setPositionIndex(touchPuzzlePositionIndex);
    }
}

void PuzzleGameScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    //タップ操作によるボールの移動完了時処理
    movedPuzzle();
}

void PuzzleGameScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

//タップした位置のチェック
PuzzleSprite* PuzzleGameScene::getTouchPuzzle(Point touchPos, PuzzleSprite::PositionIndex withoutPosIndex)
{
    for (int x = 1; x <= PUZZLE_NUM_X; x++){
        for (int y = 1; y <= PUZZLE_NUM_Y; y++){
            if (x == withoutPosIndex.x && y == withoutPosIndex.y){
                //指定位置のボールの場合は、以下の処理を行わない
                continue;
            }
            //タップ位置にあるボールかどうかを判断する
            int tag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(x, y));
            auto ball = (PuzzleSprite*)(getChildByTag(tag));
            if (ball){
                //2点間の距離を求める
                float distance = ball->getPosition().getDistance(touchPos);
                
                //ボールの当たり判定は円形。つまりボールの中心からの半径で判断する
                if (distance <= BALL_SIZE / 2){
                    //タップした位置にボールが存在する
                    return ball;
                }
            }
        }
    }
    
    return nullptr;
}

//タップ操作によるボールの移動完了時処理
void PuzzleGameScene::movedPuzzle()
{
    //移動しているボールを本来の位置に戻す
    m_movingPuzzle->resetPosition();
    m_movingPuzzle = nullptr;

    //一列に並んだボールがあるかチェックする
    m_chainNumber = 0;
    m_removeNumbers.clear();
    checksLinedPuzzles();
}

//一列に並んだボールがあるかチェックする
void PuzzleGameScene::checksLinedPuzzles()
{
    //画面をタップ不可とする
    m_touchable = false;
    
    if (existsLinedPuzzles()){
        //3個以上並んだボールの存在する場合
        
        //ボールの消去SE再生
        AudioManager::getInstance()->playSe("removed_no"+std::to_string(m_chainNumber+1));
        
        //連鎖カウントアップ
        m_chainNumber++;
        
        //ボールの削除と生成
        removeAndGeneratePuzzles();
        
        //アニメーション後に再チェック
        auto delay = DelayTime::create(ONE_ACTION_TIME * (m_maxRemovedNo + 1));
        auto func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::checksLinedPuzzles, this));
        auto seq = Sequence::create(delay, func, nullptr);
        runAction(seq);
    }else{
        
        int chainNum = 0;
        int damage = 0;
        int healing = 0;
        std::set<int> attackers;
        int index = 0;
        
        //敵にダメージを与える
        do {
            //ランダムで敵を1体選択
            index = m_distForMember(m_engine);
            BattleChar* enemyData = m_enemyDatum.at(index);
            if(enemyData->getHp() > 0){
                //ダメージ・回復量の計算
                calculateDamage(chainNum, healing, damage, attackers, enemyData);
                break;
            }
            //HPが0のメンバーを選択した場合は、再度選択し直す
        } while (true);
        
        //アタック処理
        if (damage > 0) {
            attackToEnemy(index, damage, attackers);
        }
        
        //回復処理
        if (healing > 0) {
            healMember(healing);
        }
        
        //敵にダメージを与えた後の処理を設定
        CallFunc* func;
        if(m_enemyDatum.at(0)->getHp() <= 0 &&
           m_enemyDatum.at(1)->getHp() <= 0 &&
           m_enemyDatum.at(2)->getHp() <= 0){
            func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::winAnimation, this));
        } else {
            func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::attackFromEnemy, this));
        }
        runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
        endAnimation();
    }
}

//3個以上並んだボールの存在チェック
bool PuzzleGameScene::existsLinedPuzzles()
{
    //ボールのパラメータを初期化する
    initPuzzleParams();
    //消去される順番の初期化
    m_maxRemovedNo = 0;
    for (int x = 1; x <= PUZZLE_NUM_X; x++)
    {
        for (int y = 1; y <= PUZZLE_NUM_Y; y++)
        {
            //x方向のボールをチェック
            checkedPuzzle(PuzzleSprite::PositionIndex(x, y), Direction::x);
            //y方向のボールをチェック
            checkedPuzzle(PuzzleSprite::PositionIndex(x, y), Direction::y);
        }
    }
    //戻り値の決定
    return m_maxRemovedNo > 0;
}

//全てのボールのBallTypeを取得
Map<int, PuzzleSprite*> PuzzleGameScene::getAllPuzzles()
{
    auto balls = Map<int, PuzzleSprite*>();
    
    for (auto object : getChildren())
    {
        auto ball = dynamic_cast<PuzzleSprite*>(object);
        if (ball){
            balls.insert(ball->getTag(), ball);
        }
    }
    return balls;
}

//指定方向のボールと同じ色かチェックする
bool PuzzleGameScene::isSamePuzzleType(PuzzleSprite::PositionIndex current, Direction direction)
{
    //全てのボールのPuzzleTypeを取得
    auto allPuzzles = getAllPuzzles();
    
    if (direction == Direction::x){
        if (current.x + 1 > PUZZLE_NUM_X){
            //列が存在しない場合は抜ける
            return false;
        }
    }else{
        if (current.y + 1 > PUZZLE_NUM_Y){
            //行が存在しない場合は抜ける
            return false;
        }
    }
    
    //現在のボールを取得
    int currentTag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(current.x, current.y));
    PuzzleSprite* currentPuzzle = allPuzzles.at(currentTag);
    
    //次のボールを取得
    int nextTag;
    if (direction == Direction::x){
        nextTag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(current.x + 1, current.y));
    }else{
        nextTag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(current.x, current.y + 1));
    }
    auto nextPuzzle = allPuzzles.at(nextTag);
    if (currentPuzzle->getPuzzleType() == nextPuzzle->getPuzzleType()) {
        //次のボールが同じBallTypeである
        return true;
    }
    return false;
}

//ボールのパラメータを初期化する
void PuzzleGameScene::initPuzzleParams()
{
    //全てのボールのBallTypeを取得
    auto allPuzzles = getAllPuzzles();
    for (auto puzzle : allPuzzles) {
        puzzle.second->resetParams();
    }
}

//全ボールに対してボールの並びをチェックする
void PuzzleGameScene::checkedPuzzle(PuzzleSprite::PositionIndex current, Direction direction)
{
    //全てのボールのBallTypeを取得
    auto allPuzzles = getAllPuzzles();
    
    //検索するタグの生成
    int tag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(current.x, current.y));
    PuzzleSprite* puzzle = allPuzzles.at(tag);
    
    //指定方向のチェック済みフラグを取得
    bool checked;
    if (direction == Direction::x) {
        checked = puzzle->getCheckedX();
    } else {
        checked = puzzle->getCheckedY();
    }
    if (!checked) {
        int num = 0;
        while (true)
        {
            //検索位置を取得
            PuzzleSprite::PositionIndex searchPosition;
            if (direction == Direction::x){
                searchPosition = PuzzleSprite::PositionIndex(current.x + num, current.y);
            }else{
                searchPosition = PuzzleSprite::PositionIndex(current.x, current.y + num);
            }
            //次のボールと同じPuzzleTypeかチェックする
            if (isSamePuzzleType(searchPosition, direction)){
                //次のボールと同じPuzzleType
                int nextTag = PuzzleSprite::generateTag(searchPosition);
                auto nextPuzzle = allPuzzles.at(nextTag);
                //チェックしたボールのチェック済みフラグを立てる
                if (direction == Direction::x){
                    nextPuzzle->setCheckedX(true);
                }else{
                    nextPuzzle->setCheckedY(true);
                }
                num++;
            }else{
                //次のボールが異なるballType
                if (num >= 2){
                    int removedNo = 0;
                    
                    //消去するボールのカウント
                    if (m_removeNumbers.size() <= m_chainNumber){
                        //配列が存在しない場合は追加する
                        std::map<PuzzleSprite::PuzzleType, int> removeNumber;
                        m_removeNumbers.push_back(removeNumber);
                    }
                    m_removeNumbers[m_chainNumber][puzzle->getPuzzleType()] += num + 1;
                    
                    //すでにRemovedNoがあるものが存在するかチェック
                    for (int i = 0; i <= num; i++)
                    {
                        PuzzleSprite::PositionIndex linedPosition;
                        if (direction == Direction::x){
                            linedPosition = PuzzleSprite::PositionIndex(current.x + i, current.y);
                        }else{
                            linedPosition = PuzzleSprite::PositionIndex(current.x, current.y + i);
                        }
                        int linedPuzzleTag = PuzzleSprite::generateTag(linedPosition);
                        auto linedPuzzle = allPuzzles.at(linedPuzzleTag);
                        if (linedPuzzle->getRemovedNo() > 0){
                            //すでにRemovedNoがあるものが存在するので、removedNoを取得し次の処理を行う
                            removedNo = linedPuzzle->getRemovedNo();
                            break;
                        }
                    }
                    //消去する順番のカウントアップ
                    if (removedNo == 0){
                        removedNo = ++m_maxRemovedNo;
                    }
                    //3個以上並んでいた場合は、reomvedNoをセットする
                    for (int i = 0; i <= num; i++)
                    {
                        PuzzleSprite::PositionIndex linedPosition;
                        if (direction == Direction::x){
                            linedPosition = PuzzleSprite::PositionIndex(current.x + i, current.y);
                        }else{
                            linedPosition = PuzzleSprite::PositionIndex(current.x, current.y + i);
                        }
                        int linedPuzzleTag = PuzzleSprite::generateTag(linedPosition);
                        auto linedPuzzle = allPuzzles.at(linedPuzzleTag);
                        linedPuzzle->setRemovedNo(removedNo);
                    }
                }
                break;
            }
        };
        //指定方向をチェック済みとする
        if (direction == Direction::x) {
            puzzle->setCheckedX(true);
        }else{
            puzzle->setCheckedY(true);
        }
    }
}

//ボールの削除とボールの生成
void PuzzleGameScene::removeAndGeneratePuzzles()
{
    //全てのボールのPuzzleTypeを取得
    auto allPuzzles = getAllPuzzles();
    int maxRemovedNo = 0;
    for (int x = 1; x <= PUZZLE_NUM_X; x++) {
        int fallCount = 0;
        for (int y = 1; y <= PUZZLE_NUM_Y; y++) {
            int tag = PuzzleSprite::generateTag(PuzzleSprite::PositionIndex(x, y));
            auto puzzle = allPuzzles.at(tag);
            if (puzzle) {
                int removedNoForPuzzle = puzzle->getRemovedNo();
                if (removedNoForPuzzle > 0){
                    //落ちる段数をカウント
                    fallCount++;
                    if (removedNoForPuzzle > maxRemovedNo){
                        maxRemovedNo = removedNoForPuzzle;
                    }
                }else{
                    //落ちる段数をセット
                    puzzle->setFallCount(fallCount);
                }
            }
        }
        //ボールを生成する
        generatePuzzles(x, fallCount);
    }
    //ボールの消去＆落下アニメーション
    animationPuzzles();
}

//ボールを生成する
void PuzzleGameScene::generatePuzzles(int xLineNum, int fallCount)
{
    for (int i = 1; i <= fallCount; i++) {
        //ボールを生成する
        auto positionIndex = PuzzleSprite::PositionIndex(xLineNum, PUZZLE_NUM_Y + i);
        auto puzzle = newPuzzles(positionIndex, false);
        puzzle->setFallCount(fallCount);
    }
}

//ボールの消去と落下アニメーション
void PuzzleGameScene::animationPuzzles()
{
    //全てのボールのPuzzleTypeを取得
    auto allPuzzles = getAllPuzzles();
    
    for (auto Puzzle : allPuzzles) {
        //ボールのアニメーションを実行する
        Puzzle.second->removingAndFallingAnimation(m_maxRemovedNo);
    }
}

void PuzzleGameScene::initEnemy(Node* node)
{
    for (int i = 0; i < 3; i++)
    {
        //敵の情報
        int enemyNo = MapData::getMapData(m_questNo).mapEnemy[rand()% MapData::getMapData(m_questNo).mapEnemy.size()];
        auto enemyDataParam = CharData::getEnemyData(enemyNo-1);
        auto enemyData = BattleChar::create();
        if(enemyData){
            enemyData->retain();
            enemyData->setHp(enemyDataParam.enemyHp);
            enemyData->setMaxHp(enemyData->getHp());
            enemyData->setAttack(enemyDataParam.enemyAtk);
            
            switch (enemyDataParam.enemyAttribute)
            {
                case 1: // 赤ボール : 火属性
                    enemyData->setElement(BattleChar::Element::Fire);
                    break;
                case 2: // 青ボール : 水属性
                    enemyData->setElement(BattleChar::Element::Water);
                    break;
                case 3: // 緑ボール : 風属性
                    enemyData->setElement(BattleChar::Element::Wind);
                    break;
                case 4: // 黄ボール : 光属性
                    enemyData->setElement(BattleChar::Element::Holy);
                    break;
                case 5: // 紫ボール : 紫属性
                    enemyData->setElement(BattleChar::Element::Shadow);
                    break;
                default:
                    enemyData->setElement(BattleChar::Element::None);
                    break;
            }
            enemyData->setTurnCount(enemyDataParam.enemyTurn);
            auto eturn = node->getChildByName<ui::Text*>( "eturn"+std::to_string(i) );
            if(eturn){
                eturn->setString( std::to_string(enemyDataParam.enemyTurn) + " turn" );
                m_enemyTurn.pushBack(eturn);
            }
            m_enemyDatum.pushBack(enemyData);
            
            //敵の表示
            auto ename = node->getChildByName<ui::Text*>( "ename"+std::to_string(i) );
            if(ename){
                ename->setString( enemyDataParam.enemyName );
            }
            
            auto charaEnemyNode = node->getChildByName<Node*>( "chara_enemy_"+std::to_string(i) );
            if(charaEnemyNode){
                auto charaEnemySprite = BattleCharSprite::create(enemyNo, BattleCharSprite::CharType::Enemy);
                if(charaEnemySprite){
                    charaEnemyNode->addChild( charaEnemySprite, ZOrder::Enemy );
                    m_enemys.pushBack(charaEnemySprite);
                }
            }
            
            auto iconEnemyNode = node->getChildByName<Node*>( "enemy_base"+std::to_string(i) );
            if(iconEnemyNode){
                auto iconEnemySprite = CharIconSprite::create(enemyNo, CharIconSprite::CharType::Enemy);
                if(iconEnemySprite){
                    iconEnemyNode->addChild( iconEnemySprite, ZOrder::Enemy );
                    m_enemysIcon.pushBack(iconEnemySprite);
                }
            }
            
            //敵ヒットポイントバーの表示
            auto enemyHPNode = node->getChildByName<Node*>( "EnemyHp_bar"+std::to_string(i) );
            if(enemyHPNode){
                auto hpBar = enemyHPNode->getChildByName<cocos2d::ui::LoadingBar*>("hp_bar");
                if(hpBar){
                    hpBar->setPercent(enemyData->getHpPercentage());
                    m_hpBarForEnemys.pushBack(hpBar);
                }
            }
        }
    }
}

void PuzzleGameScene::initMembers(Node* node)
{
    //パーティデータ読込み表示
    PartyValue::getInstance()->dataLoad();
    
    // メンバーは仮
    std::vector<int> BattleCharNo{ 10, 11, 12, };
    
    int allMemberHP = 0;
    for (int i = 0; i < 3; i++)
    {
        //メンバー
        // TODO: ステータスは仮なので、後の実装でユーザーのキャラクターデータを取得する
        auto charDataParam = CharData::getCharData(BattleCharNo[i]-1);
        auto memberData = BattleChar::create();
        if(memberData){
            memberData->setHp(charDataParam.charHp);
            memberData->setMaxHp(memberData->getHp());
            allMemberHP += memberData->getHp();
            switch (charDataParam.charAttribute)
            {
                case 1: // 赤ボール : 火属性
                    memberData->setElement(BattleChar::Element::Fire);
                    break;
                case 2: // 青ボール : 水属性
                    memberData->setElement(BattleChar::Element::Water);
                    break;
                case 3: // 緑ボール : 風属性
                    memberData->setElement(BattleChar::Element::Wind);
                    break;
                case 4: // 黄ボール : 光属性
                    memberData->setElement(BattleChar::Element::Holy);
                    break;
                case 5: // 紫ボール : 紫属性
                    memberData->setElement(BattleChar::Element::Shadow);
                    break;
                default:
                    memberData->setElement(BattleChar::Element::None);
                    break;
            }
            m_memberDatum.pushBack(memberData);
        }
        
        //メンバーの表示
        auto name = node->getChildByName<ui::Text*>( "name"+std::to_string(i) );
        if(name){
            name->setString( charDataParam.charName );
        }
        
        auto charaPlayerNode = node->getChildByName<Node*>( "chara_player_"+std::to_string(i) );
        if(charaPlayerNode){
            auto charaPlayerSprite = BattleCharSprite::create(BattleCharNo[i], BattleCharSprite::CharType::Member);
            if(charaPlayerSprite){
                charaPlayerNode->addChild( charaPlayerSprite, ZOrder::Char );
                m_members.pushBack(charaPlayerSprite);
            }
        }
        
        auto iconPlayerNode = node->getChildByName<Node*>( "CharIconNode"+std::to_string(i) );
        if(iconPlayerNode){
            auto iconPlayerSprite = CharIconSprite::create(BattleCharNo[i], CharIconSprite::CharType::Member);
            if(iconPlayerSprite){
                iconPlayerNode->addChild( iconPlayerSprite, ZOrder::Char );
                m_membersIcon.pushBack(iconPlayerSprite);
            }
        }
    }
    
    //メンバー全員のヒットポイントバーの表示
    auto partyHpNode = node->getChildByName<Node*>( "PartyHp_bar" );
    if(partyHpNode){
        m_hpBarForMembers = partyHpNode->getChildByName<cocos2d::ui::LoadingBar*>("hp_bar");
        if(m_hpBarForMembers){
            m_hpBarForMembers->setPercent(allMemberHP);
        }
    }
}

// ダメージの計算
void PuzzleGameScene::calculateDamage(int &chainNum, int &healing, int &damage, std::set<int> &attackers, BattleChar* defender)
{
    auto removeIt = m_removeNumbers.begin();
    while (removeIt != m_removeNumbers.end())
    {
        auto ballIt = (*removeIt).begin();
        while(ballIt != (*removeIt).end())
        {
            if ((*ballIt).first == PuzzleSprite::PuzzleType::Pink) {
                // 回復
                healing += 5;
            } else {
                // アタッカー分のデータを繰り返す
                for (int i = 0; i < m_memberDatum.size(); i++)
                {
                    // メンバー情報取得
                    auto memberData = m_memberDatum.at(i);
                    // メンバーのHPが0の場合は、以下の処理を行わない
                    if (memberData->getHp() <= 0) {
                        continue;
                    }
                    // 消されたボールとアタッカーの属性よりアタッカーの判定
                    if (isAttacker((*ballIt).first, memberData->getElement())) {
                        // アタッカー情報の保持
                        attackers.insert(i);
                        // ダメージ
                        damage += BattleChar::getDamage((*ballIt).second, chainNum, memberData, defender);
                    }
                }
            }
            chainNum++;
            ballIt++;
        }
        removeIt++;
    }
}

// アタッカー判定
bool PuzzleGameScene::isAttacker(PuzzleSprite::PuzzleType type, BattleChar::Element element)
{
    switch (type)
    {
        case PuzzleSprite::PuzzleType::Red:
            // 赤ボール : 火属性
            if (element == BattleChar::Element::Fire)
                return true;
            break;
            
        case PuzzleSprite::PuzzleType::Blue:
            // 青ボール : 水属性
            if (element == BattleChar::Element::Water)
                return true;
            break;
            
        case PuzzleSprite::PuzzleType::Green:
            // 緑ボール : 風属性
            if (element == BattleChar::Element::Wind)
                return true;
            break;
            
        case PuzzleSprite::PuzzleType::Yellow:
            // 黄ボール : 光属性
            if (element == BattleChar::Element::Holy)
                return true;
            break;
            
        case PuzzleSprite::PuzzleType::Purple:
            // 紫ボール : 紫属性
            if (element == BattleChar::Element::Shadow)
                return true;
            break;
            
        default:
            break;
    }
    
    return false;
}

// 敵への攻撃
void PuzzleGameScene::attackToEnemy(int index, int damage, std::set<int> attackers)
{
    // 敵のHPを取得する
    BattleChar* enemyData = m_enemyDatum.at(index);
    
    // ダメージ表示
    DamageEffect* effect = DamageEffect::create();
    if(effect){
        effect->setPosition(Vec2(m_enemys.at(index)->getParent()->getPositionX(),
                                 m_enemys.at(index)->getParent()->getPositionY()));
        effect->showEffect(damage);
        this->addChild(effect, Damage);
    }
    
    // 敵にダメージを与える
    int afterHp = enemyData->getHp() - damage;
    if (afterHp > enemyData->getMaxHp()){
        afterHp = enemyData->getMaxHp();
    }
    enemyData->setHp(afterHp);
    
    //敵ヒットポイントバーのアニメーション
    m_hpBarForEnemys.at(index)->setPercent(enemyData->getHpPercentage());
    
    //敵の被ダメージアニメーション
    m_enemys.at(index)->runAction(vibratingAnimation());
    m_enemysIcon.at(index)->runAction(vibratingAnimation());
    
    //メンバーの攻撃アニメーション
    int count = 1;
    for (auto attacker : attackers)
    {
        AudioManager::getInstance()->playSe("attack0"+std::to_string(count));
        auto seq = Sequence::create(MoveBy::create(0.1, Point(0, 10)), MoveBy::create(0.1, Point(0, -10)), nullptr);
        m_members.at(attacker)->runAction(seq);
        count++;
    }
    
    //敵のHPが0以下であった場合
    if(afterHp <= 0){
        m_enemys.at(index)->setVisible(false);
    }
    
    //敵の全滅チェック
    bool allHpZero = true;
    for (auto enemy : m_enemyDatum)
    {
        if (enemy->getHp() > 0) {
            allHpZero = false;
            break;
        }
    }
    
    // アニメーション終了時処理
    CallFunc* func;
    if (allHpZero) {
        func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::winAnimation, this));
    } else {
        func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::endAnimation, this));
    }
    runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
}

// メンバーの回復
void PuzzleGameScene::healMember(int healing)
{
    for (int i = 0; i < m_memberDatum.size(); i++)
    {
        // メンバーデータ取得
        auto memberData = m_memberDatum.at(i);
        // HPが0の場合は、回復しない
        if (memberData->getHp() <= 0) {
            continue;
        }
        // メンバーを回復する
        int afterHp = memberData->getHp() + healing;
        if (afterHp > memberData->getMaxHp()) afterHp = memberData->getMaxHp();
        memberData->setHp(afterHp);
        // メンバーHPアニメーション
        m_hpBarForMembers->setPercent(memberData->getHpPercentage());
    }
}

//敵からの攻撃
void PuzzleGameScene::attackFromEnemy()
{
    int enemyCount = 0;
    for (const auto& e : m_enemyDatum) {
        // 敵のHPが0の場合
        if (e->getHp() <= 0){
            continue;
        }
        
        if (e->isAttackTurn()) {
            //メンバーを1人選択
            //ランダムでメンバーを選択
            int index = m_distForMember(m_engine);
            BattleChar* memberData = m_memberDatum.at(index);
            
            //メンバーにダメージを与える
            int afterHp = memberData->getHp() - 25;
            if (afterHp > memberData->getMaxHp()){
                afterHp = memberData->getMaxHp();
            }
            memberData->setHp(afterHp);
            
            //メンバーヒットポイントバーのアニメーション
            m_hpBarForMembers->setPercent(memberData->getHpPercentage());
            
            //メンバーの被ダメージアニメーション
            m_members.at(index)->runAction(vibratingAnimation());
            m_membersIcon.at(index)->runAction(vibratingAnimation());
            
            AudioManager::getInstance()->playSe("hit");
            
            //敵の攻撃アニメーション
            auto seq = Sequence::create(MoveBy::create(0.1, Point(0, -10)), MoveBy::create(0.1, Point(0, 10)), nullptr);
            m_enemys.at(enemyCount)->runAction(seq);
        }
        m_enemyTurn.at(enemyCount)->setString( std::to_string(e->getRemainingTurn()) + " turn" );
        enemyCount++;
    }
    
    //味方の全滅チェック
    bool allHpZero = true;
    
    for (auto character : m_memberDatum)
    {
        if (character->getHp() > 0)
        {
            allHpZero = false;
            break;
        }
    }
    
    // アニメーション終了時処理
    CallFunc* func;
    if (allHpZero) {
        func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::loseAnimation, this));
    } else {
        //敵の攻撃ターンでない場合は、一連の攻撃の処理を終わらせる
        func = CallFunc::create(CC_CALLBACK_0(PuzzleGameScene::endAnimation, this));
    }
    runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
}

// アニメーション終了時処理
void PuzzleGameScene::endAnimation()
{
    // タップを有効にする
    m_touchable = true;
}

// 振動アニメーション
Spawn* PuzzleGameScene::vibratingAnimation()
{
    // 振動アニメーション
    auto move = Sequence::create(MoveBy::create(0.025, Point( 5, 5)),
                                 MoveBy::create(0.025, Point(-5, -5)),
                                 MoveBy::create(0.025, Point(-5, -5)),
                                 MoveBy::create(0.025, Point( 5, 5)),
                                 MoveBy::create(0.025, Point( 5, -5)),
                                 MoveBy::create(0.025, Point(-5, 5)),
                                 MoveBy::create(0.025, Point(-5, 5)),
                                 MoveBy::create(0.025, Point( 5, -5)),
                                 nullptr);
    
    // ダメージ時に色を赤くする
    Action* tint = Sequence::create(TintTo::create(0, 255, 0, 0),
                                    DelayTime::create(0.2),
                                    TintTo::create(0, 255, 255, 255),
                                    nullptr);
    
    return Spawn::create(move, tint, nullptr);
}

//Winアニメーション
void PuzzleGameScene::winAnimation()
{
    // タップを無効にする
    m_touchable = false;
    
    // クエストクリアデータを保存する
    // ユーザーデータ作成
    PlayerValue::getInstance()->dataLoad();
    int clearMap = PlayerValue::getInstance()->getClearMap();
    if(clearMap < m_questNo+1){
        PlayerValue::getInstance()->setClearMap(m_questNo+1);
        PlayerValue::getInstance()->dataSave();
    }
    
    //白い背景を用意する
    auto whiteLayer = LayerColor::create(Color4B(255, 255, 255, 127), WINSIZE.width, WINSIZE.height);
    if(whiteLayer) {
        whiteLayer->setPosition(Point::ZERO);
        addChild(whiteLayer, ZOrder::Result);
    }
    
    //Win画像を表示する
    auto win = Sprite::create("asset/battle/WIN.png");
    if(win) {
        win->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
        addChild(win, ZOrder::Result);
    }
    
    //指定秒数後に次のシーンへ
    scheduleOnce(schedule_selector(PuzzleGameScene::nextSceneWin), 1.f);
}

//Loseアニメーション
void PuzzleGameScene::loseAnimation()
{
    // タップを無効にする
    m_touchable = false;
    
    //黒い背景を用意する
    auto blackLayer = LayerColor::create(Color4B(0, 0, 0, 127), WINSIZE.width, WINSIZE.height);
    if(blackLayer) {
        blackLayer->setPosition(Point::ZERO);
        addChild(blackLayer, ZOrder::Result);
    }
    
    // LoseBGM再生
    AudioManager::getInstance()->playBgm("lose");
    
    //Lose画像を表示する
    auto lose = Sprite::create("asset/battle/LOSE.png");
    if(lose) {
        lose->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
        addChild(lose, ZOrder::Result);
    }
    
    //指定秒数後に次のシーンへ
    scheduleOnce(schedule_selector(PuzzleGameScene::nextSceneLose), 5.f);
}

//次のシーンへ遷移 (Win)
void PuzzleGameScene::nextSceneWin(float dt)
{
    // 次のシーンを生成する
    auto nextScene = CallFunc::create([dt]{
        auto scene = ResultScene::createScene(m_questNo);
        auto transition = TransitionFade::create(dt, scene, Color3B::WHITE);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(Sequence::create(nextScene, NULL));
}

//次のシーンへ遷移 (Lose)
void PuzzleGameScene::nextSceneLose(float dt)
{
    // 次のシーンを生成する
    auto nextScene = CallFunc::create([dt]{
        auto scene = QuestScene::createScene();
        AudioManager::getInstance()->playBgm("all_bgm");
        auto transition = TransitionFadeBL::create(0.2f, scene);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(Sequence::create(nextScene, NULL));
}
