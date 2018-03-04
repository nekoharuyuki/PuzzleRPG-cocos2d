#ifndef __GAME_DATA_SQL__
#define __GAME_DATA_SQL__

#include "cocos2d.h"
#include "sqlite3.h"

namespace GameDataSQL
{
    int sqliteOpen(sqlite3 **db);
    void sqliteCreateTable();
    const char* sqliteGetValueForKey(const char *key);
    void sqliteSetValueForKey(const char *key,const char *value);
    void sqliteUpdateValueForKey(const char *key,const char *value);
};

#endif /* defined(__GAME_DATA_SQL__) */
