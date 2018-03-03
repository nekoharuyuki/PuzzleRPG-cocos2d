#ifndef __GAME_DATA_SQL__
#define __GAME_DATA_SQL__

#include "cocos2d.h"
#include "sqlite3.h"

namespace GameDataSQL
{
    static int sqliteOpen(sqlite3 **db);
    static void sqliteCreateTable();
    static const char* sqliteGetValueForKey(const char *key);
    static void sqliteSetValueForKey(const char *key,const char *value);
    static void sqliteUpdateValueForKey(const char *key,const char *value);
};

#endif /* defined(__GAME_DATA_SQL__) */
