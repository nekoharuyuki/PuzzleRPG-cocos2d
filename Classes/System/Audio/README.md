# AudioManager
helper and functions for cocos2d-x v3.8 over.

sorry. comment language is japanese.

### AudioManager : Audio系ライブラリ
AudioManagerでは、Cocos2d-xのAudioEngineを使用しています。  
**BGMのフェードや区間ループ、SEのチャンク指定再生にも対応しています。**

シンプルな使い方

    // 1.5秒のフェードインをしながらtitleを再生
    AudioManager::getInstance()->playBgm("bgm/title", 1.5f);

拡張子は不要です(Cocos2dxが対応する拡張子が存在すれば再生します)  

また、事前にjson形式のaudio定義ファイルを読み込むことによって、再生キー名、ファイルパスを定義することができ、ファイル名の仕様変更等に対応できます。さらに、BGMの区間ループにも対応可能となります。

定義ファイルの構造と読み込み方法

[Resources/data/audio.json]

    {
        "BGM":{
            "title":"bgm/title",
            "game_happy":["bgm/game01", 20.129, 79.990]
        }
        ,
        "SE":
        {
            "ui_ok":"sounds/ui_ok",
            "ui_cancel":"sounds/ui_cancel"
        }
    }

読み込みコード(AppDelegate.cpp等)

    // オーディオ定義ファイルの読み込み  
    AudioManager::getInstance()->readAudioListFile("data/audio.json");

BGMのvalueを配列指定の場合、[ファイルパス, ループ開始位置(秒), ループ終端位置(秒)] で区間ループに対応します。

定義ファイルを読み込んでいない場合、オーディオ再生に指定するファイル名はファイルパスを指定してください。

#### 実装

*BGMの再生*

    // 1.5秒のフェードインをしながらtitleを再生
    AudioManager::getInstance()->playBgm("title", 1.5f);

*BGMの停止*

    // 1.5秒のフェードアウトをしながら停止
    AudioManager::getInstance()->stopBgm(1.5f);

*BGMの一時停止*

    // 1.5秒のフェードアウトを一時停止
    AudioManager::getInstance()->pauseBgm(1.5f);

*BGMのリジューム再生*

    // 1.5秒のフェードインをしながら再開
    AudioManager::getInstance()->resumeBgm(1.5f);

*SEの再生*

    // OK音を再生
    AudioManager::getInstance()->playSe("ui_ok");
    // OK音をチャンクを指定して再生(チャンクは0～7まで使用できます)
    AudioManager::getInstance()->playSe("ui_ok", 1);