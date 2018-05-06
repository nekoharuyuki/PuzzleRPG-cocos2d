#include "PuzzleGameScene.h"
#include "QuestScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"

#define PUZZLE_NUM_X 6
#define PUZZLE_NUM_Y 6

#define MOTION_STREAK_TAG 10

USING_NS_CC;

using namespace cocostudio::timeline;

int PuzzleGameScene::m_questNo = 0;

//コンストラクタ
PuzzleGameScene::PuzzleGameScene()
: m_movingPuzzle(nullptr)
, m_movedPuzzle(false)
, m_touchable(true)
, m_maxRemovedNo(0)
, m_chainNumber(0)
{
    //乱数初期化および各ボールの出現の重みを指定
    std::random_device device;
    m_engine = std::default_random_engine(device());
    m_distForPuzzle = std::discrete_distribution<int>{20, 20, 20, 20, 20, 0};
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
bool PuzzleGameScene::init()
{
    if (!Layer::init()){
        return false;
    }
    
    initBackground(); //背景の初期化
    
    auto rootNode = CSLoader::createNode("battle/BattleScene.csb");
    if(rootNode){
        addChild(rootNode, ZOrder::BgForPuzzle);
    }
    
    // Animationを読み込む
    auto action = ActionTimelineCache::getInstance()->createAction("battle/BattleScene.csb");
    if(action) {
        rootNode->runAction(action);
        action->gotoFrameAndPause(m_questNo);
    }
    
    // バトル中のBGM再生
    AudioManager::getInstance()->playBgm("battle");
    
    // メニューへ戻るボタン
    // ボタンノードを取得
    auto startBtn = rootNode->getChildByName<ui::Button*>("menu_button");
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
        return true;    // イベントを実行する
    });
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(PuzzleGameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PuzzleGameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PuzzleGameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(PuzzleGameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initPuzzles(); //ボールの初期表示
    
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
    int puzzleType;
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
    m_movedPuzzle = false;
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
    
    auto touchPuzzle = getTouchPuzzle(touch->getLocation(), m_movingPuzzle->getPositionIndex());
    if (touchPuzzle && m_movingPuzzle != touchPuzzle){
        //移動しているボールが、別のボールの位置に移動
        m_movedPuzzle = true;
        
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
        //タップを有効にする
        m_touchable = true;
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
    
    if (currentPuzzle->getPuzzleType() == nextPuzzle->getPuzzleType()){
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
    
    for (auto puzzle : allPuzzles){
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
    if (direction == Direction::x){
        checked = puzzle->getCheckedX();
    }else{
        checked = puzzle->getCheckedY();
    }
    if (!checked){
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
