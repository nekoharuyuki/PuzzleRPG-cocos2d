# PuzzleRPG-cocos2d
![ss_TitleScene](https://github.com/nekoharuyuki/PuzzleRPG-cocos2d/blob/master/Resources/asset/ss/ss_TitleScene.jpg)
  
[パズルRPGの作り方](https://www.shoeisha.co.jp/book/detail/9784798141589)を参考にC++でiOS/androidアプリでの作成を行いました。  
  
> パズルRPGとは、ゲームのストーリー性とキャラクターの成長を特徴とするRPG（ロールプレイングゲーム）と、パズルゲームの要素をミックスした定番ゲームスタイルのひとつです。RPGでの敵キャラクターとの戦闘部分に、パズルゲームの要素が盛り込まれているのが特徴です。  
>   
> 本書は、ゲーム開発やプログラミングの初級者に向けて、パズルRPGの開発の仕方を解説した本です。Webブラウザを使って簡単に動かせるサンプルゲームをもとに、ゲーム企画や開発環境の準備から、パズルゲームのアイデア出し、RPG部分の戦闘／クエスト画面、ステージの作り方、仲間の追加／バトルパーティの組み方、キャラクターの合成／進化の方法などについて解説します。また、エフェクトやサウンドの付け方、スマホアプリにする方法も説明します。  
>   
> ブラウザゲームやスマートフォンのゲーム作りに挑戦してみたい方におすすめの一冊です。  
  
***
  
## 環境構築　
[リンク](https://github.com/nekoharuyuki/Study-cocos2d/wiki/%E9%96%8B%E7%99%BA%E7%92%B0%E5%A2%83%E3%81%AE%E6%A7%8B%E7%AF%89)

### Cocos2d-xに必要なもの
  * Cocos2d-xの本体
  * Python 2.7.x（Python 3.x ではダメだそうです）
  * JDK
  * Android SDK
  * Android NDK
  * Apache ANT
  
### 手順
* Cocos2d-xの本体をダウンロード
  * Cocos2d-xの設定
* JDKのインストール
* Android SDK のインストール
* Android Studio と SDK ツールをダウンロード
  * ANDROID_SDK_ROOTのパスを設定
* Android NDK のダウンロード
  * NDK_ROOTのパスを設定
* Apache ANTのダウンロード
  * ANT_ROOTのパスを設定
  
### Androidアプリのビルド
  * cocos compile -p android --ap android-25  
  
### iOSアプリのビルド
  * frameworks > runtime-src > proj.ios_mac  
  
![ss_BattleScene](https://github.com/nekoharuyuki/PuzzleRPG-cocos2d/blob/master/Resources/asset/ss/ss_BattleScene.jpg)
