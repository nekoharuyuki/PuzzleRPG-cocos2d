#ifndef __AudioManager__
#define __AudioManager__

#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"

class AudioManager {

private:

    enum AudioType {
        BGM = 0,
        SE = 1
    };

    enum FadeType {
        NONE = 0,
        FADE_IN = 1,
        FADE_OUT = 2,
        FADE_IN_RESUME = 3,
        FADE_OUT_PAUSE = 4
    };

	AudioManager();
	static AudioManager* m_instance;

    // update実行用
    static cocos2d::Scheduler* m_scheduler;

    // BGMファイルリスト
    std::map<std::string, std::string> m_bgmList;
    // BGMファイル区間設定リスト
    struct BgmLoopParams {
        float startPos;
        float endPos;
        bool isLoopInterval;
    };
    std::map<std::string, BgmLoopParams> m_bgmLoopList;
    // SEファイルリスト
    std::map<std::string, std::string> m_seList;

    // SE用チャンク
    int m_chunk[8];

    // BGMは1種類のみ
    int m_bgmId;
    // 同じファイル名の場合は無視
    std::string m_bgmFileName;
    // 再生中BGMの拡張子
    std::string m_bgmFileExt;

    // オーディオ管理ファイルを使用する場合はそのファイルパス
    CC_SYNTHESIZE(std::string, m_audioListFile, AudioListFile);

    // BGM音量
    float  m_bgmVolume;
    // SE音量
    float m_seVolume;

    // BGMフェード関連
    FadeType m_fadeCondition;
    float m_bgmFadeVolumeFrom;
    float m_bgmFadeVolumeTo;
    float m_bgmFadeVolumeNow;
    float m_bgmFadeTime;
    bool m_stopBgmReleaseFlg;

    //==========================

public:

	~AudioManager();
	static AudioManager* getInstance();
	static void deleteInstance();

    // 毎フレーム実行
    virtual void update(float dt);

    // オーディオ管理ファイルを読み込む
    bool readAudioListFile(const std::string fileName);
    // AudioEngine全てのキャッシュを削除する
    void releaseAll();
    
    // BGMとSEの音量の初期化
    void initVolume(float bgmVolume, float seVolume);

    // BGMのPreLoad
    void preloadBgm(const std::string baseName);
    // BGMの再生
    int playBgm(const std::string baseName, float fadeTime = 0, bool loop = true);
    int playBgm(const std::string baseName, float fadeTime, bool loop, float volume);
    // BGMを一時停止する
    void pauseBgm(float fadeTime = 0);
    // BGMをリジューム再生する
    void resumeBgm(float fadeTime = 0);
    // BGMを停止する
    // Arg2 - release : キャッシュを破棄する場合はtrue
    void stopBgm(float fadeTime = 0, bool release = true);
    // BGMが再生されているかどうか
    bool isPlayingBgm();
    // BGMの音量を変更する
    // Arg2 - save : 変数_bgmVolumeに保存する場合はtrue
    void setBgmVolume(float volume, bool save = true);
    // BGMの音量を取得する
    float getBgmVolume();
    // BGMのキャシュを解放する
    void releaseBgm();

    // 効果音のPreLoad
    void preloadSe(const std::string baseName);
    // 効果音を再生する
    // Args2 - chunkNo : チャンクを指定すると同じチャンク番号が指定された場合は、前の音を上書きする
    int playSe(const std::string baseName, int chunkNo);
    int playSe(const std::string baseName, int chunkNo, bool loop, float volume);
    int playSe(const std::string baseName, bool loop = false);
    int playSe(const std::string baseName, bool loop, float volume);
    // 効果音を停止する
    void stopSe(int soundId);
    // 効果音の音量を変更する
    void setSeVolume(float volume);
    // 効果音の音量を取得する
    float getSeVolume();
    // 効果音のキャッシュを解放する
    void releaseSe(const std::string baseName);

    // AudioEngineを解放する
    void endAudioEngine();

private:
    // 環境に応じて拡張子付きファイル名に変換する
    std::string getFileName(AudioType type, std::string baseName);

    // pauseBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
    void pauseBgmEngine();

    // stopBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
    void stopBgmEngine(bool release = true);
    
    // モバイルデバイスかどうか
    bool isMobileDevice();
};

#endif /* defined(__AudioManager__) */
