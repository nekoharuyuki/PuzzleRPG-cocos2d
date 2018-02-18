#ifndef __PuzzleGame__GameLayer__
#define __PuzzleGame__GameLayer__

#include "cocos2d.h"
#include <random>
#include "PuzzleSprite.h"

class PuzzleGameScene : public cocos2d::Layer
{
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
        Level,
        Result,
    };
    
    std::default_random_engine m_engine; //乱数生成エンジン
    std::discrete_distribution<int> m_distForPuzzle; //乱数の分布
    PuzzleSprite* m_movingPuzzle; //動かしているボール
    bool m_movedPuzzle; //他のボールとの接触有無
    bool m_touchable; //タップの可否
    int m_maxRemovedNo; //一度に削除される最大連鎖の番号
    int m_chainNumber; //連鎖数のカウント
    std::vector<std::map<PuzzleSprite::PuzzleType, int>> m_removeNumbers; //消去するボールのカウント
    
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

public:
    PuzzleGameScene(); //コンストラクタ
    virtual bool init(); //初期化
    CREATE_FUNC(PuzzleGameScene); //create関数生成
    static cocos2d::Scene* createScene(); //シーン生成

    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__PuzzleGame__GameLayer__) */
