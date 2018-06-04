/*
 Audio系ライブラリ
 */

#pragma execution_character_set("utf-8")

#include "audio/include/AudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"

#include "AudioManager.h"

USING_NS_CC;
using namespace experimental;

AudioManager* AudioManager::m_instance = nullptr;
cocos2d::Scheduler* AudioManager::m_scheduler = nullptr;

// コンストラクタ
AudioManager::AudioManager()
: m_bgmId(-1)
, m_bgmFileName("")
, m_bgmFileExt("")
, m_audioListFile("")
, m_bgmVolume(0.5f)
, m_seVolume(0.6f)
, m_fadeCondition(FadeType::NONE)
, m_bgmFadeVolumeNow(0)
, m_bgmFadeVolumeFrom(0)
, m_bgmFadeVolumeTo(0)
, m_bgmFadeTime(0)
, m_stopBgmReleaseFlg(true)
{
    // チャンク配列の初期化
    for(int i=0; i < sizeof(m_chunk) / sizeof(m_chunk[0]); i++) {
        m_chunk[i] = AudioEngine::INVALID_AUDIO_ID;
    }
}

// デストラクタ
AudioManager::~AudioManager() {
    CC_SAFE_RELEASE_NULL(m_scheduler);
}

// 初期化
AudioManager* AudioManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new AudioManager();
        // スケジューラをインスタンスに追加し、updateを呼び出せるようにする
        m_scheduler = Director::getInstance()->getScheduler();
        m_scheduler->retain();
        m_scheduler->scheduleUpdate(m_instance, 0, false);
	}
	return m_instance;
}

// 削除する際に使用
void AudioManager::deleteInstance() {
    if (m_instance != nullptr) {
		delete m_instance;
	}
    m_instance = nullptr;
}

// オーディオ管理ファイルを読み込む
bool AudioManager::readAudioListFile(const std::string fileName) {
    // Resourceの中にあるファイルを読み込む
    // ファイル読み込み
    std::string strData = FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(strData.c_str());
    if (doc.HasParseError()) {
        // 解析エラー
        CCLOG("JSON parse error.");
        return false;
    }
    if (doc.IsObject()) {
        CCLOG("%s", strData.c_str());
        // 初期化
        m_bgmList.clear();
        m_bgmLoopList.clear();
        m_seList.clear();
        // BGM
        rapidjson::Value& bgms = doc["BGM"];
        // キーと値をリストに登録する
        for (rapidjson::Value::ConstMemberIterator it = bgms.MemberBegin(); it != bgms.MemberEnd(); it++) {
            std::string key = it->name.GetString();
            const rapidjson::Value& value = it->value;
            // 通常のファイルパスの場合
            if (value.GetType() == rapidjson::kStringType) {
                m_bgmList[key] = value.GetString();
            }
            // 配列の場合
            else if (value.GetType() == rapidjson::kArrayType) {
                // 1番目はファイルパス
                m_bgmList[key] = value[0].GetString();
                // 2番目はループ後の再生開始位置
                if (value.Size() > 1) {
                    m_bgmLoopList[key].startPos = (float)(value[1].GetDouble());
                }
                // 3番目はループ終端位置
                if (value.Size() > 2) {
                    m_bgmLoopList[key].endPos = (float)(value[2].GetDouble());
                }
            }
        }
        // SE
        rapidjson::Value& ses = doc["SE"];
        // キーと値をリストに登録する
        for (rapidjson::Value::ConstMemberIterator it = ses.MemberBegin(); it != ses.MemberEnd(); it++) {
            std::string key = it->name.GetString();
            const rapidjson::Value& value = it->value;
            if (value.GetType() == rapidjson::kStringType) {
                m_seList[key] = value.GetString();
            }
        }
        // 現在のファイルをセット
        m_audioListFile = fileName;
        return true;
    }
    return false;
}

// 端末ごとに読み込む拡張子を変えて、そのファイル名を返す
std::string AudioManager::getFileName(AudioType type, std::string baseName) {
    auto platform = Application::getInstance()->getTargetPlatform();
    std::string ext = ".wav";               // 拡張子
    // オーディオ管理ファイルを使う場合、キーからファイル名を取得する
    if (m_audioListFile != "") {
        if (type == AudioType::BGM) {
            if (m_bgmList.count(baseName) != 0) {
                baseName = m_bgmList[baseName];
            }
        } else if (type == AudioType::SE) {
            if (m_seList.count(baseName) != 0) {
                baseName = m_seList[baseName];
            }
        }
    }
    // すでに拡張子(.～)が含まれているならそのまま返す
    if (baseName.find_last_of(".") != std::string::npos) {
        if (FileUtils::getInstance()->isFileExist(baseName)) {
            return baseName;
        } else {
            return "";
        }
    }
    switch (platform) {
        case cocos2d::ApplicationProtocol::Platform::OS_WINDOWS:
        case cocos2d::ApplicationProtocol::Platform::OS_MAC:
            // ogg > mp3 > wav
            if (FileUtils::getInstance()->isFileExist(baseName + ".ogg")) {
                ext = ".ogg";
            } else if (FileUtils::getInstance()->isFileExist(baseName + ".mp3")) {
                ext = ".mp3";
            }
            break;
        case cocos2d::ApplicationProtocol::Platform::OS_ANDROID:
            // ogg > m4a > mp3 > wav
            if (FileUtils::getInstance()->isFileExist(baseName + ".ogg")) {
                ext = ".ogg";
            } else if (FileUtils::getInstance()->isFileExist(baseName + ".m4a")) {
                ext = ".m4a";
            } else if (FileUtils::getInstance()->isFileExist(baseName + ".mp3")) {
                ext = ".mp3";
            }
            break;
        case cocos2d::ApplicationProtocol::Platform::OS_IPHONE:
        case cocos2d::ApplicationProtocol::Platform::OS_IPAD:
            // m4a > caf > mp3 > wav
            if (FileUtils::getInstance()->isFileExist(baseName + ".m4a")) {
                ext = ".m4a";
            } else if (FileUtils::getInstance()->isFileExist(baseName + ".caf")) {
                ext = ".caf";
            } else if (FileUtils::getInstance()->isFileExist(baseName + ".mp3")) {
                ext = ".mp3";
            }
            break;
        default:
            break;
    }
    if (FileUtils::getInstance()->isFileExist(baseName + ext)) {
        return baseName + ext;
    }
    // それでも見つからなければ空文字を返して、その先でエラーとする
    CCLOG("file not found %s.", baseName.c_str());
    return baseName;
}

// AudioEngine全てのキャッシュを削除する
void AudioManager::releaseAll() {
    AudioEngine::uncacheAll();
}

// 毎フレーム実行
void AudioManager::update(float dt) {
    // フェードイン、アウトを実行する
    switch (m_fadeCondition) {
        case FadeType::FADE_IN:
        case FadeType::FADE_IN_RESUME:
            // 0除算回避
            if (m_bgmFadeTime == 0) {
                m_bgmFadeTime = 0.01f;
            }
            // dt時間後の増分ボリュームを求める。 _bgmVolume:_bgmFadeTime = dV : dt
            m_bgmFadeVolumeNow += (dt * (m_bgmFadeVolumeTo - m_bgmFadeVolumeFrom)) / m_bgmFadeTime;
            
            if (m_bgmFadeVolumeNow >= m_bgmFadeVolumeTo) {
                m_bgmFadeVolumeNow = m_bgmFadeVolumeTo;
                m_bgmFadeVolumeFrom = m_bgmFadeVolumeTo;
                m_fadeCondition = FadeType::NONE;
            }
            this->setBgmVolume(m_bgmFadeVolumeNow, false);
            break;
        case FadeType::FADE_OUT:
        case FadeType::FADE_OUT_PAUSE:
            // 0除算回避
            if (m_bgmFadeTime == 0) {
                m_bgmFadeTime = 0.01f;
            }
            // dt時間後の減分ボリュームを求める。 _bgmVolume:_bgmFadeTime = dV : dt
            m_bgmFadeVolumeNow += (dt * (m_bgmFadeVolumeTo - m_bgmFadeVolumeFrom)) / m_bgmFadeTime;
            if (m_bgmFadeVolumeNow <= m_bgmFadeVolumeTo) {
                m_bgmFadeVolumeNow = m_bgmFadeVolumeTo;
                m_bgmFadeVolumeFrom = m_bgmFadeVolumeTo;
                if (m_fadeCondition == FadeType::FADE_OUT) {
                    // stopBgmを実行
                    stopBgm(0, m_stopBgmReleaseFlg);
                } else if (m_fadeCondition == FadeType::FADE_OUT_PAUSE) {
                    // pauseBgmを実行
                    pauseBgm(0);
                }
                m_fadeCondition = FadeType::NONE;
            }
            this->setBgmVolume(m_bgmFadeVolumeNow, false);
            break;
        default:
            break;
    }
    // ループチェック
    if (this->isPlayingBgm() && m_bgmLoopList.count(m_bgmFileName) > 0) {
        if (m_bgmFileName != "") {
            // 現在のBGM情報を取得
            float currentTime = AudioEngine::getCurrentTime(m_bgmId);    // 現在の位置
            float duration = AudioEngine::getDuration(m_bgmId);                  // オーディオの長さ
            // 区間設定情報
            float startPos = m_bgmLoopList[m_bgmFileName].startPos;
            float endPos = duration;
            // 開始位置を超えていたら、区間内フラグを立てる
            if (!m_bgmLoopList[m_bgmFileName].isLoopInterval && currentTime > startPos) {
                m_bgmLoopList[m_bgmFileName].isLoopInterval = true;
            }
            if (m_bgmLoopList[m_bgmFileName].endPos > 0) {
                endPos = m_bgmLoopList[m_bgmFileName].endPos;
                if (endPos > duration) {
                    endPos = duration;
                }
            }
            if (endPos <= 0) { return; }
            if (// 2回目以降なのに、ループ開始地点より前にあったら
                (m_bgmLoopList[m_bgmFileName].isLoopInterval && currentTime < startPos - 0.4f)
                // または、endPosが終端近くではなくて、endPosを超えている場合
                || (duration - endPos >= 0.2f && currentTime >= endPos)) {
                CCLOG("bgm end. current time is %f sec.", currentTime);
                AudioEngine::setCurrentTime(m_bgmId, startPos);
            }
        }
    }
}

// BGMとSEの音量の初期化
void AudioManager::initVolume(float bgmVolume, float seVolume) {
    m_bgmVolume = bgmVolume;
    m_seVolume = seVolume;
}

// モバイルデバイスかどうか
bool AudioManager::isMobileDevice() {
    auto platform = Application::getInstance()->getTargetPlatform();
    if (platform == cocos2d::ApplicationProtocol::Platform::OS_ANDROID
        || platform == cocos2d::ApplicationProtocol::Platform::OS_IPHONE
        || platform == cocos2d::ApplicationProtocol::Platform::OS_IPAD) {
        return true;
    }
    return false;
}

//===================
// BGM
//===================

// BGMのPreLoad
void AudioManager::preloadBgm(const std::string baseName) {
    std::string fileName = getFileName(AudioType::BGM, baseName);
    if (fileName == "") {
        return;
    }
    AudioEngine::preload(fileName);
}

// BGMの再生
int AudioManager::playBgm(const std::string baseName, float fadeTime /* =0*/, bool loop /* = true*/) {
    return playBgm(baseName, fadeTime, loop, m_bgmVolume);
}

// BGMの再生
int AudioManager::playBgm(const std::string baseName, float fadeTime, bool loop, float volume) {
    int soundId = AudioEngine::INVALID_AUDIO_ID;
    std::string fileName = getFileName(AudioType::BGM, baseName);
    if (fileName == "") {
        return soundId;
    }
    if (m_bgmFileName == baseName && AudioEngine::getState(m_bgmId) == AudioEngine::AudioState::PLAYING) {
        // 前回と同じファイル名で、再生中の場合は無視する
        return m_bgmId;
    }
    // 拡張子を登録
    m_bgmFileExt = fileName.substr(fileName.size() - 4, 4);
    // 前回のBGMを停止
    stopBgm();
    // フェード指定の場合
    if (fadeTime != 0) {
        m_fadeCondition = FadeType::FADE_IN;
        m_bgmFadeVolumeNow = 0;
        m_bgmFadeVolumeFrom = 0;
        m_bgmFadeTime = fadeTime;
    } else {
        m_fadeCondition = FadeType::NONE;
        m_bgmFadeVolumeNow = volume;
    }
    m_bgmFadeVolumeTo = volume;
    m_bgmId = AudioEngine::play2d(fileName, loop, volume);
    if (loop) {
        // FinishCallback は ループ中には実行されない
        // 失敗した時のみ実行される
        AudioEngine::setFinishCallback(m_bgmId, [this, loop, volume](int bgmId, std::string fileName) {
            stopBgm(0, false);
            m_bgmId = playBgm(m_bgmFileName, 0, loop, volume);
        });
    }
    m_bgmFileName = baseName;
    if (m_bgmLoopList.count(m_bgmFileName) > 0) {
        m_bgmLoopList[m_bgmFileName].isLoopInterval = false;
    }
    CCLOG( "playBgm(  %s  )", baseName.c_str() );
    return m_bgmId;
}

// BGMを一時停止する
void AudioManager::pauseBgm(float fadeTime /*= 0*/) {
    m_bgmFadeVolumeTo = 0;
    if (fadeTime != 0) {
        // フェード指定の場合
        m_fadeCondition = FadeType::FADE_OUT_PAUSE;
        m_bgmFadeVolumeNow = m_bgmVolume;
        m_bgmFadeVolumeFrom = m_bgmVolume;
        m_bgmFadeTime = fadeTime;
    } else {
        // フェードなしの場合
        m_fadeCondition = FadeType::NONE;
        m_bgmFadeVolumeNow = 0;
        pauseBgmEngine();
    }
}

// pauseBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
void AudioManager::pauseBgmEngine() {
    AudioEngine::pause(m_bgmId);
}

// BGMをリジューム再生する
void AudioManager::resumeBgm(float fadeTime /*=0*/) {
    // フェード指定の場合
    if (fadeTime != 0) {
        m_fadeCondition = FadeType::FADE_IN_RESUME;
        m_bgmFadeVolumeNow = 0;
        m_bgmFadeVolumeFrom = 0;
        m_bgmFadeTime = fadeTime;
    } else {
        m_fadeCondition = FadeType::NONE;
        m_bgmFadeVolumeNow = m_bgmVolume;
    }
    m_bgmFadeVolumeTo = m_bgmVolume;
    AudioEngine::resume(m_bgmId);
}

// BGMを停止する
void AudioManager::stopBgm(float fadeTime /*= 0*/, bool release /* = true */) {
    m_bgmFadeVolumeTo = 0;
    if (fadeTime != 0) {
        // フェード指定の場合
        m_fadeCondition = FadeType::FADE_OUT;
        m_bgmFadeVolumeNow = m_bgmVolume;
        m_bgmFadeVolumeFrom = m_bgmVolume;
        m_bgmFadeTime = fadeTime;
        m_stopBgmReleaseFlg = release;
    } else {
        // フェードなしの場合
        m_fadeCondition = FadeType::NONE;
        m_bgmFadeVolumeNow = 0;
        stopBgmEngine(release);
    }
}

// stopBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
void AudioManager::stopBgmEngine(bool release /* = true */) {
    AudioEngine::stop(m_bgmId);
    // キャッシュ解放
    if (release) {
        releaseBgm();
    }
    m_bgmId = AudioEngine::INVALID_AUDIO_ID;
    m_bgmFileName = "";
    m_bgmFileExt = "";
}

// BGMが再生されているかどうか
bool AudioManager::isPlayingBgm() {
    if (m_bgmFileName == "") {
        return false;
    }
    std::string fileName = m_bgmFileName + m_bgmFileExt;
    AudioEngine::AudioState state = AudioEngine::getState(m_bgmId);
    if (state == AudioEngine::AudioState::PLAYING) {
        return true;
    }
    return false;
}

// BGMの音量を変更する
void AudioManager::setBgmVolume(float volume, bool save /* = true */) {
    // 変数保持フラグがonの場合は変数を切り替える
    if (save) {
        m_bgmVolume = volume;
    }
    AudioEngine::setVolume(m_bgmId, volume);
}

// BGMの音量を取得する
float AudioManager::getBgmVolume() {
    return m_bgmVolume;
}

// BGMのキャシュを解放する
void AudioManager::releaseBgm() {
    auto fileName = m_bgmFileName + m_bgmFileExt;
    AudioEngine::uncache(fileName);
}

//===================
// SE
//===================

// 効果音のPreLoad
void AudioManager::preloadSe(const std::string baseName) {
    std::string fileName = getFileName(AudioType::SE, baseName);
    if (fileName == "") {
        return;
    }
    AudioEngine::preload(fileName);
}

// 効果音を再生する
int AudioManager::playSe(const std::string baseName, int chunkNo) {
    return this->playSe(baseName, chunkNo, false, m_seVolume);
}
// 効果音を再生する
int AudioManager::playSe(const std::string baseName, int chunkNo, bool loop, float volume) {
    int soundId = AudioEngine::INVALID_AUDIO_ID;
    bool chunkFlag = false;
    std::string fileName = getFileName(AudioType::SE, baseName);
    if (fileName == "") {
        return soundId;
    }
    // チャンクが指定されていたら
    if (chunkNo >= 0 && chunkNo < sizeof(m_chunk) / sizeof(m_chunk[0])) {
        chunkFlag = true;
        // 指定チャンクの再生中の音を停止
        this->stopSe(m_chunk[chunkNo]);
    }
    soundId = AudioEngine::play2d(fileName, loop, volume);
    if (chunkFlag) {
        // チャンクにSoundIdを登録
        m_chunk[chunkNo] = soundId;
    }
    CCLOG( "playSe(  %s  )", baseName.c_str() );
    return soundId;
}
// 効果音を再生する
int AudioManager::playSe(const std::string baseName, bool loop, float volume) {
    return this->playSe(baseName, -1, loop, volume);
}
// 効果音を再生する
int AudioManager::playSe(const std::string baseName, bool loop /* = false */) {
    return this->playSe(baseName, loop, m_seVolume);
}

// 効果音を停止する
void AudioManager::stopSe(int soundId) {
    AudioEngine::stop(soundId);
}

// 効果音の音量を変更する
void AudioManager::setSeVolume(float volume) {
    m_seVolume = volume;
}

// 効果音の音量を取得する
float AudioManager::getSeVolume() {
    return m_seVolume;
}

// 効果音のキャッシュを解放する
void AudioManager::releaseSe(const std::string baseName) {
    std::string fileName = getFileName(AudioType::SE, baseName);
    if (fileName == "") {
        return;
    }
    AudioEngine::uncache(fileName);
}

// AudioEngineを解放する
void AudioManager::endAudioEngine() {
    AudioEngine::end();
}

//------------------------------------------------------------------
