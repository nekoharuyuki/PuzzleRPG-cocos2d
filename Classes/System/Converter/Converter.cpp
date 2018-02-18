/*
 文字列からの型変換、操作等
*/

#pragma execution_character_set("utf-8")

#include "Converter.h"

USING_NS_CC;

// "0xARGB"の文字列からアルファ付きのColor4Bを返す
cocos2d::Color4B Converter::fromARGB(const std::string &code) {

    // 0xARGBコードが見つかったら
    if (code.find("0x") == 0 && code.length() == 10) {

        try {
            // A
            int a = (int)strtol(code.substr(2, 2).c_str(), nullptr, 16);
            // R
            int r = (int)strtol(code.substr(4, 2).c_str(), nullptr, 16);
            // G
            int g = (int)strtol(code.substr(6, 2).c_str(), nullptr, 16);
            // B
            int b = (int)strtol(code.substr(8, 2).c_str(), nullptr, 16);
            
            return cocos2d::Color4B(r, g, b, a);

        } catch (...) {
            // Error
            CCLOG("illegal color code : %s", code.c_str());
        }
    } else {
        // Error
        CCLOG("not support format : %s", code.c_str());
    }

    return cocos2d::Color4B::BLACK;
}

// 文字列の "true" or "false" を bool型の true or false に変換する
// "1"もtrueとして扱う
bool Converter::stringToBool(const std::string &strBool, const bool &def) {

    if (strBool == "true" || strBool == "1") {
        return true;
    } else if (strBool == "false" || strBool == "0") {
        return false;
    }

    return def;
}

bool Converter::stringToBool(const std::string &strBool) {
    return stringToBool(strBool, false);
}

// 文字列のSplit
std::vector<std::string> Converter::split(const std::string &str, const char &delim) {

    std::vector<std::string> result;
    std::string::size_type current = 0;

    while (current != std::string::npos) {
        std::string::size_type delimIdx = str.find_first_of(delim, current);

        if (delimIdx == std::string::npos) {
            result.push_back(str.substr(current));
            break;
        } else {
            result.push_back(str.substr(current, delimIdx - current));
        }
        current = delimIdx + 1;
    }

    return result;
}

// 文字列の全置換
std::string Converter::replaceAll(std::string str, std::string before, std::string after) {

    std::string::size_type pos(str.find(before));

    while (pos != std::string::npos) {
        str.replace(pos, before.length(), after);
        pos = str.find(before, pos + after.length());
    }

    return str;
}

// 文字列の先頭と末尾にあるホワイトスペースを取り除く
std::string Converter::trim(const std::string& str, const char* trimChars /* = " \t\v\r\n" */) {

    std::string result;
    std::string::size_type left = str.find_first_not_of(trimChars);

    if (left != std::string::npos) {
        std::string::size_type right = str.find_last_not_of(trimChars);
        result = str.substr(left, right - left + 1);
    }

    return result;
}

// 秒を分と秒に分けて文字列に変換する
std::string Converter::secToMinSecString(int sec, std::string format /*= "%02d : %02d"*/ ) {

    int allSec = std::floor(sec);
    int viewMin = allSec / 60;
    int viewSec = allSec % 60;

    return StringUtils::format(format.c_str(), viewMin, viewSec);
}
