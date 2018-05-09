#ifndef __PuzzleSprite__
#define __PuzzleSprite__

#include "cocos2d.h"

#define BALL_SIZE 50 //ボールのサイズ
#define ONE_ACTION_TIME 0.2 //ボール削除・落下アクションの時間

class PuzzleSprite : public cocos2d::Sprite
{
public:
    //ボールの種類
    enum class PuzzleType
    {
        Red,    //赤
        Blue,   //青
        Green,  //緑
        Yellow, //黄
        Purple, //紫
        Pink,   //ピンク
    };
    
    //位置インデックス
    struct PositionIndex
    {
        //コンストラクタ
        PositionIndex(){
            x = 0;
            y = 0;
        }
        
        //コンストラクタ
        PositionIndex(int _x, int _y){
            x = _x;
            y = _y;
        }
        
        int x; //x方向のインデックス
        int y; //y方向のインデックス
    };
    
    PuzzleSprite(); //コンストラクタ
    static PuzzleSprite* create(PuzzleType type, bool visible); //インスタンス生成
    virtual bool init(PuzzleType type, bool visible); //初期化
    
    CC_SYNTHESIZE(int, m_removedNo, RemovedNo); //ボール削除の順番
    CC_SYNTHESIZE(bool, m_checkedX, CheckedX); //横方向確認フラグ
    CC_SYNTHESIZE(bool, m_checkedY, CheckedY); //縦方向確認フラグ
    CC_SYNTHESIZE(int, m_fallCount, FallCount); //ボール落下時の落下段数
    CC_SYNTHESIZE_READONLY(PuzzleType, m_ballType, PuzzleType); //ボールの種類
    CC_PROPERTY(PositionIndex, m_positionIndex, PositionIndex); //位置インデックス
    
    void setPositionIndexAndChangePosition(PositionIndex positionIndex); //位置インデックスの設定および位置変更
    void resetParams(); //パラメータのリセット
    void resetPosition(); //初期位置へ移動
    void removingAndFallingAnimation(int maxRemovedNo); //消去アニメーションと落下アニメーション
    
    static std::string getPuzzleImageFilePath(PuzzleType type); //ボール画像取得
    static cocos2d::Point getPositionForPositionIndex(PositionIndex positionIndex); //位置インデックスからPointを取得
    static int generateTag(PositionIndex positionIndex); //位置インデックスからタグを取得
    
protected:
    void removingAnimation(int maxRemovedNo); //ボール削除アニメーション
    void fallingAnimation(int maxRemovedNo); //ボール落下アニメーション
};

#endif /* defined(__PuzzleSprite__) */
