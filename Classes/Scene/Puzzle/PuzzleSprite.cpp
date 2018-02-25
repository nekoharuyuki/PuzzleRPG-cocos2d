#include "PuzzleSprite.h"
#include "VisibleRect.h"

USING_NS_CC;

//コンストラクタ
PuzzleSprite::PuzzleSprite()
: _removedNo(0)
, _checkedX(false)
, _checkedY(false)
, _fallCount(0)
, _positionIndex(0, 0)
{
}

//インスタンス生成
PuzzleSprite* PuzzleSprite::create(PuzzleType type, bool visible)
{
    PuzzleSprite *pRet = new PuzzleSprite();
    if (pRet && pRet->init(type, visible)){
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

//初期化
bool PuzzleSprite::init(PuzzleType type, bool visible)
{
    if (!Sprite::initWithFile(getPuzzleImageFilePath(type))){
        return false;
    }
    
    _ballType = type;
    
    setVisible(visible);
    
    return true;
}

//パラメータのリセット
void PuzzleSprite::resetParams()
{
    _removedNo = 0;
    _checkedX = false;
    _checkedY = false;
    _fallCount = 0;
}

//初期位置へ移動
void PuzzleSprite::resetPosition()
{
    //位置を変更する
    setPosition(getPositionForPositionIndex(_positionIndex));
}

//位置インデックスを返す
PuzzleSprite::PositionIndex PuzzleSprite::getPositionIndex() const
{
    //位置インデックスを返す
    return _positionIndex;
}

//位置インデックスとタグを変更する
void PuzzleSprite::setPositionIndex(PositionIndex positionIndex)
{
    //位置インデックスを保持する
    _positionIndex = positionIndex;
    
    //タグをセットする
    setTag(generateTag(_positionIndex));
}

//インデックスとタグと位置を変更する
void PuzzleSprite::setPositionIndexAndChangePosition(PositionIndex positionIndex)
{
    //インデックスとタグを変更する
    setPositionIndex(positionIndex);
    
    //位置を変更する
    resetPosition();
}

//消去アニメーションと落下アニメーション
void PuzzleSprite::removingAndFallingAnimation(int maxRemovedNo)
{
    //ボールを消すアニメーション
    removingAnimation(maxRemovedNo);
    
    //ボールを落とすアニメーション
    fallingAnimation(maxRemovedNo);
}

//ボール削除アニメーション
void PuzzleSprite::removingAnimation(int maxRemovedNo)
{
    if (_removedNo > 0)
    {
        //ボールを消すアニメーション
        auto delay1 = DelayTime::create(ONE_ACTION_TIME * (_removedNo - 1));
        auto fade = FadeTo::create(ONE_ACTION_TIME, 0);
        auto delay2 = DelayTime::create(ONE_ACTION_TIME * (maxRemovedNo - _removedNo));
        auto removeSelf = RemoveSelf::create(false);
        
        //アニメーション実行
        runAction(Sequence::create(delay1, fade, delay2, removeSelf, nullptr));
    }
}

//ボール落下アニメーション
void PuzzleSprite::fallingAnimation(int maxRemovedNo)
{
    if (_fallCount > 0)
    {
        //ボールを落とすアニメーション
        setPositionIndex(PositionIndex(_positionIndex.x, _positionIndex.y - _fallCount));
        
        auto delay = DelayTime::create(ONE_ACTION_TIME * maxRemovedNo);
        auto show = Show::create();
        auto move = MoveTo::create(ONE_ACTION_TIME, getPositionForPositionIndex(getPositionIndex()));
        runAction(Sequence::create(delay, show, move, nullptr));
    }
}

//ボール画像取得
std::string PuzzleSprite::getPuzzleImageFilePath(PuzzleType type)
{
    FileUtils::getInstance()->addSearchPath("Resources/asset");
    
    //ボールタイプに適した画像を返す
    switch (type)
    {
        case PuzzleType::Red:    return "puzzle/01.png";
        case PuzzleType::Blue:   return "puzzle/02.png";
        case PuzzleType::Green:  return "puzzle/03.png";
        case PuzzleType::Yellow: return "puzzle/04.png";
        case PuzzleType::Purple: return "puzzle/05.png";
        default:                 return "Default/Sprite.png";
    }
}

//位置インデックスからPointを取得
Point PuzzleSprite::getPositionForPositionIndex(PositionIndex positionIndex)
{
    double x = BALL_SIZE * (positionIndex.x - 0.5) + 1;
    double y = BALL_SIZE * (positionIndex.y - 0.5) + 1;
    
    Rect rect = VisibleRect::getVisibleRect();
    
    double offset_x = rect.size.width / 2 - BALL_SIZE * 3;
    double offset_y = 12.f;
    
    return Point(x + offset_x, y + offset_y);
}

//位置インデックスからタグを取得
int PuzzleSprite::generateTag(PositionIndex positionIndex)
{
    return positionIndex.x * 10 + positionIndex.y;
}
