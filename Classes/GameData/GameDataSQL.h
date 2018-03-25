#ifndef __GAME_DATA_SQL__
#define __GAME_DATA_SQL__

#include "cocos2d.h"
#include "sqlite3.h"

class GameDataSQL{

public:
    
    // データベースの存在確認
    static bool hasData();
    
    //データベースを開く
    static int sqliteOpen(sqlite3 **db);
    
    //データベースのテーブルの作成
    static void sqliteCreateTable();
    
    //keyから値を取り出す。
    static const char* sqliteGetValueForKey(const char *key);
    
    //keyとvalueを設定する(初期)
    static void sqliteSetValueForKey(const char *key,const char *value);
    
    //keyを元にValueの値を更新する
    static void sqliteUpdateValueForKey(const char *key,const char *value);

};

#endif /* defined(__GAME_DATA_SQL__) */
