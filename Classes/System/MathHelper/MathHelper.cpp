/*
 ランダム値取得等
*/
#pragma execution_character_set("utf-8")

#include "MathHelper.h"

USING_NS_CC;

// min以上max以下のint値をランダムに返す
int MathHelper::getRandom(int minValue, int maxValue) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> num(minValue, maxValue);

    return num(mt);
}

// 与えられた角度を0～359の範囲の角度にして返す
int MathHelper::getDegreesAngle(int angle) {
    
    angle %= 360;
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}

// 文字列で渡された比較演算子の結果を返す
bool MathHelper::isComparisonValue(int leftValue, std::string symbol, int rightValue) {

    // %値 対応
    int modNum = 1;
    if (symbol.substr(0, 1) == "%") {
        modNum = std::atoi(symbol.substr(1).c_str());
        symbol = "%";
    }

    if (symbol == "=" || symbol == "==") {
        if (leftValue == rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == ">") {
        if (leftValue > rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == "<") {
        if (leftValue < rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == ">=") {
        if (leftValue >= rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == "<=") {
        if (leftValue <= rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == "!=") {
        if (leftValue != rightValue) {
            return true;
        } else {
            return false;
        }
    } else if (symbol == "%") {
        if (leftValue % modNum == rightValue) {
            return true;
        } else {
            return false;
        }
    } else {
        // 演算子がみつからない
        return false;
    }
}
