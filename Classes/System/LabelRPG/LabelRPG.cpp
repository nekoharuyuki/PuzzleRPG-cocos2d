//
//  LabelRPG.cpp
//  Cocos2dRogueLike
//
//  Created by kyokomi on 2014/04/20.
//
//

#include "LabelRPG.h"

USING_NS_CC;

LabelRPG::LabelRPG(FontAtlas *atlas /* = nullptr */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
             TextVAlignment vAlignment /* = TextVAlignment::TOP */,bool useDistanceField /* = false */,bool useA8Shader /* = false */)
:nowLabelLenght_(0)
,nowLabelText_()
{
    
}

LabelRPG::~LabelRPG()
{
}

LabelRPG* LabelRPG::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment /* = TextHAlignment::CENTER */, int maxLineWidth /* = 0 */)
{
    auto ret = new LabelRPG(nullptr,alignment);
    
    if (ret && FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) && ret->setTTFConfig(ttfConfig))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();
        
        return ret;
    }
    
    delete ret;
    return nullptr;
}

void LabelRPG::setStringWithRunText(const std::string &text, float interval)
{
    // 検証したのはTTFだけなので...
    if (_currentLabelType == LabelType::TTF) {
        nowLabelLenght_ = 0;
        nowLabelText_ = std::string(text);
        
        Director::getInstance()->getScheduler()->schedule([this](float time) {
            // 全部表示したら停止
            if (nowLabelLenght_ == this->nowLabelText_.length()) {
                Director::getInstance()->getScheduler()->unschedule("textTimer", this);
            } else {
                // マルチバイト対応
                unsigned char lead = this->nowLabelText_[nowLabelLenght_];
                int charSize;
                if (lead < 0x80) {
                    charSize = 1;
                } else if (lead < 0xE0) {
                    charSize = 2;
                } else if (lead < 0xF0) {
                    charSize = 3;
                } else {
                    charSize = 4;
                }
                nowLabelLenght_ += charSize;

                std::string s(this->nowLabelText_, 0, nowLabelLenght_);
                CCLOG("tim = %f len = %ld text = %s nowText = %s", time, this->getString().length(), this->nowLabelText_.c_str(), s.c_str());
                this->setString(s);
                this->setPosition(Point(originalPoint_.x + this->getSystemFontSize() / 2 + this->getContentSize().width / 2, originalPoint_.y - this->getContentSize().height / 2 - this->getSystemFontSize() / 2));
            }
        }, this, interval, -1, 0, false, "textTimer");
    }
}
