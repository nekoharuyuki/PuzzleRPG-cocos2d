#ifndef __MathHelper__
#define __MathHelper__

#include "cocos2d.h"

class MathHelper {

public:

    // min以上max以下のint値をランダムに返す
    static int getRandom(int minValue, int maxValue);
    
    // 与えられた角度を0～359の範囲の角度にして返す
    static int getDegreesAngle(int angle);
    
    // 文字列による比較演算子の結果を返す
    static bool isComparisonValue(int leftValue, std::string symbol, int rightValue);

};

#endif /* defined(__MathHelper__) */
