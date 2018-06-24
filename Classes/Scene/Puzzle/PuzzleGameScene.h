#ifndef __PuzzleGame__GameLayer__
#define __PuzzleGame__GameLayer__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <random>
#include "PuzzleSprite.h"
#include "BattleChar.h"

class PuzzleGameScene : public cocos2d::Layer
{
public:
    PuzzleGameScene(); //コンストラクタ
    virtual bool init(); //初期化
    CREATE_FUNC(PuzzleGameScene); //create関数生成
    static cocos2d::Scene* createScene(int questNo); //シーン生成
    
    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
protected:
    //ボールチェック方向
    enum class Direction
    {
        x,
        y,
    };
    
    //Zオーダー
    enum ZOrder
    {
        BgForCharacter = 0,
        BgForPuzzle,
        Enemy,
        EnemyHp,
        Char,
        CharHp,
        Ball,
        Result,
    };
    
    std::default_random_engine m_engine; //乱数生成エンジン
    std::discrete_distribution<int> m_distForPuzzle; //乱数の分布
    std::uniform_int_distribution<int> m_distForMember; //乱数の範囲
    std::uniform_int_distribution<int> m_distForEnemy; //乱数の範囲
    PuzzleSprite* m_movingPuzzle; //動かしているボール
    bool m_movedPuzzle; //他のボールとの接触有無
    bool m_touchable; //タップの可否
    int m_maxRemovedNo; //一度に削除される最大連鎖の番号
    int m_chainNumber; //連鎖数のカウント
    std::vector<std::map<PuzzleSprite::PuzzleType, int>> m_removeNumbers; //消去するボールのカウント
    static int m_questNo;  // クエストの情報取得
    
    cocos2d::Vector<BattleChar*> m_enemyDatum; //敵の情報
    cocos2d::Vector<cocos2d::Sprite*> m_enemys; //敵画像
    cocos2d::Vector<cocos2d::ui::LoadingBar*> m_hpBarForEnemys; //敵のヒットポイントバー
    cocos2d::Vector<cocos2d::ui::Text*> m_enemyTurn;    // 敵のターン数表示
    
    cocos2d::Vector<BattleChar*> m_memberDatum; //メンバーの情報
    cocos2d::Vector<cocos2d::Sprite*> m_members; //メンバー画像
    cocos2d::ui::LoadingBar* m_hpBarForMembers; //メンバーのヒットポイントバー
    
    void initBackground(); //背景の初期化
    void initPuzzles(); //ボールの初期表示
    PuzzleSprite* newPuzzles(PuzzleSprite::PositionIndex positionIndex, bool visible); //新規ボール作成
    PuzzleSprite* getTouchPuzzle(cocos2d::Point touchPos, PuzzleSprite::PositionIndex withoutPosIndex = PuzzleSprite::PositionIndex()); //タッチしたボールを取得
    void movedPuzzle(); //タップ操作によるボールの移動完了時処理
    void checksLinedPuzzles(); //一列に並んだボールがあるかチェックする
    bool existsLinedPuzzles(); //3個以上並んだボールの存在チェック
    cocos2d::Map<int, PuzzleSprite*> getAllPuzzles(); //全てのボールのBallTypeを取得
    bool isSamePuzzleType(PuzzleSprite::PositionIndex current, Direction direction); //指定方向のボールと同じ色かチェックする
    void initPuzzleParams(); //ボールのパラメータを初期化する
    void checkedPuzzle(PuzzleSprite::PositionIndex current, Direction direction); //全ボールに対してボールの並びをチェックする
    void removeAndGeneratePuzzles(); //ボールの削除とボールの生成
    void generatePuzzles(int xLineNum, int fallCount); //ボールを生成する
    void animationPuzzles(); //ボールの消去と落下アニメーション
    
    void initEnemy(Node* node); //敵の表示
    void initMembers(Node* node); //メンバーの表示
    void calculateDamage(int &chainNum, int &healing, int &damage, std::set<int> &attackers, BattleChar* defender); //ダメージの計算
    bool isAttacker(PuzzleSprite::PuzzleType type, BattleChar::Element element); //アタッカー判定
    void attackToEnemy(int damage, std::set<int> attackers); //敵への攻撃
    void healMember(int healing); //メンバーの回復
    void attackFromEnemy(); //敵からの攻撃
    void endAnimation(); //アニメーション終了時処理
    cocos2d::Spawn* vibratingAnimation(); //振動アニメーション
    
    void winAnimation(); //Winアニメーション
    void loseAnimation(); //Loseアニメーション
    void nextSceneWin(float dt); //次のシーンへ遷移 (Win)
    void nextSceneLose(float dt); //次のシーンへ遷移 (Lose)
};

#endif /* defined(__PuzzleGame__GameLayer__) */
