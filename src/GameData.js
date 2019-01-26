var playerValue = {
    char_id : 0,
    name : "test",
    level : 1,
    coin : 0,
    jewelry : 0,
    exp : 0,
    stamina : 0,
    max_stamina : 0,
    first : true,
    field : 0,
    mapid : 0,
};

var expTable = [0,5,29,81,168,293,463,681,951,1277,1663,2110,2623,3204,3856,4582,5385,6266,7229,8275,9407,10628,11938,13342,14839,16434,18127,19921,21817,23817,25924,28139,30463,32899,35448,38113,40894,43793,46812,49953,53217,56606,60121,63764,67536,71439,75474,79643,83947,88388,92967,97685,102544,107546,112690,117980,123416,129000,134733,140616,146650,152837,159178,165674,172327,179138,186107,193237,200528,207982,215600,223383,231332,239448,247733,256187,264812,273609,282579,291724,301043,310539,320213,330065,340097,350309,360703,371281,382042,392988,404120,415439,426947,438643,450530,462608,474878,487342,500000];
var partyValue = new Array();
var CharData = null;
var MapData = null;
var CharStorage = new Array();
var stageNo = 0;
var g_bgm = true;
var g_se = true;

var charDatatInit = function(){
    cc.loader.loadJson(res.char_data, function( error, data ){
        cc.log(data); //data is the json object
        CharData = data;
    });
}

var mapDatatInit = function(){
    cc.loader.loadJson( res.map_data, function( error, data ){
        cc.log(data); //data is the json object
        MapData = data;
    });
}

var dataLoad = function(){
    var dataString = cc.sys.localStorage.getItem( "playerValue" );
    cc.log( "load:"+dataString );
    playerValue = JSON.parse( dataString );
    var partyString = cc.sys.localStorage.getItem( "partyValue" );
    cc.log( "load:"+partyString );
    partyValue = JSON.parse( partyString );
    var CharStorageString = cc.sys.localStorage.getItem( "CharStorage" );
    cc.log( "load:"+CharStorageString );
    CharStorage = JSON.parse( CharStorageString );
}

var dataSave = function(){
    var dataString = JSON.stringify( playerValue );
    cc.log( "save:"+dataString );
    cc.sys.localStorage.setItem( "playerValue", dataString );
    var partyString = JSON.stringify( partyValue );
    cc.log( "save:"+partyString );
    cc.sys.localStorage.setItem( "partyValue", partyString );
    var CharStorageString = JSON.stringify( CharStorage );
    cc.log( "save:"+CharStorageString );
    cc.sys.localStorage.setItem( "CharStorage", CharStorageString );
}

var dataClear = function(){
    cc.sys.localStorage.removeItem( "playerValue" );
    cc.sys.localStorage.removeItem( "partyValue" );
}

var hasData = function(){
    if( cc.sys.localStorage.getItem( "playerValue" ) != "" && cc.sys.localStorage.getItem( "playerValue" ) != null){
        return true;
    }
    return false;
}

var getTotalHp = function(){
    var hp = 0;
    for(var i = 0; i < partyValue.length; i++ ){
        hp += partyValue[i].hp;
    }
    return hp;
}

var getAtk = function( _attribute ){
    var atk = 0;
    var i;
    for( i = 0; i < partyValue.length; i++ ){
        if( _attribute == partyValue[i].attribute ){
            atk += partyValue[i].atk;
        }
    }
    return atk;
}

var getTotalAtk = function(){
    var atk = 0;
    for( var i = 0; i < partyValue.length; i++ ){
        atk += partyValue[i].atk;
    }
    return atk;
}

var popCharStorage = function( _start, _length ){
    var resultArray = new Array();
    var i;
    for( i = _start; i < _length; i++ ){
        resultArray.push( CharStorage[i] );
    }
    return resultArray;
}

var getChar = function( _id, _level,  _storageId){
    var selectChar = CharData.char[ _id - 1 ];
    if(_storageId < 0){
        _storageId = CharStorage.length;
    }
    var newValue = {
            "name" : selectChar.name,
            "storageId" : _storageId,
            "id" : selectChar.id,
            "hp" : selectChar.hp,
            "atk" : selectChar.atk,
            "attribute" : selectChar.attribute,
            "maxLevel" : selectChar.maxLevel[selectChar.overLimit],
            "rare" : selectChar.rare,
            "skill" : selectChar.skill,
            "skillText" : selectChar.skillText,
            "skillTurn" : selectChar.skillTurn,
            "mix_exp" : selectChar.mix_exp,
            "level" : _level,
            "exp" : 0,
            "price" : selectChar.price,
            "party" : false,
            "overLimit" : selectChar.overLimit,
            "evolution" : selectChar.evolution
    };
    var CharStorageString = JSON.stringify( newValue );
    cc.log( "getChar:"+CharStorageString );
    return newValue;
}

var removeChar = function( _id ){
    CharStorage.splice( _id, 1 );
    for( var i = 0; i < CharStorage.length; i++ ){
        CharStorage[i].storageId = i;
    }
}

var levelUpCheck = function( _level, _exp ){
    cc.log( "level up "+_level+" "+getLevel( _exp ) );
    if( _level < getLevel( _exp ) ){
        return true;
    }
    return false;
}

var getCurrentExp = function( _level, _exp ){
    var exp =0;
    exp = _exp - expTable[_level-1];
    return exp;
}

var getNextExp = function( _level ){
    var exp = 0;
    exp = expTable[_level] - expTable[_level-1];
    return exp;
}

var getLevel = function( _exp ){
    var level = 0;
    for( var i = 0; i < 100; i++ ){
        if( expTable[i] > _exp ){
            level = i;
            break;
        }
    }
    return level;
}

var playBgm = function( _type ) {
cc.log( "playBgm( " + _type + ")" );
    if( g_bgm ){
        var bgmlist = [ res.ALL_BGM,
        res.BATTLE_BGM,
        res.VICTORY_JINGLE,
        res.LOSE_JINGLE,
        res.LEVELUP_JINGLE ];
        cc.audioEngine.stopMusic(true);
        cc.audioEngine.end();
        cc.audioEngine.playMusic( bgmlist[_type], true );
    }else{
        cc.audioEngine.stopMusic(true);
    }
}

var playSe = function( _type ){
    if( g_se ){
        var effectList = [res.HIT_SE,
        res.SKILL1_SE,
        res.SKILL2_SE,
        res.SKILL3_SE,
        res.SKILL4_SE,
        res.SKILL5_SE, ];
        cc.audioEngine.playEffect( effectList[_type], false );
    }else{
        cc.audioEngine.stopAllEffects();
    }
}

