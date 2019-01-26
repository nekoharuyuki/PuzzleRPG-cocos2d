
var ResultLayer = cc.Layer.extend({
    stageData:null,
    dropChar :new Array(),
    ctor:function () {
        this._super();
        this.stageData = MapData.map[ playerValue.mapid ];
        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Result_Scene );
        this.addChild( layer, 1 );
        var QuestMap_btn = layer.getChildByName( "QuestMap_btn" );
        QuestMap_btn.addTouchEventListener( this.onQuest, this );
        var cointext = layer.getChildByName( "cointext" );

        var rnd = Math.random() * 0.4;
        this.dropCoin = MapData.map[playerValue.mapid].dropCoin * (0.8 + rnd);
        playerValue.coin += this.dropCoin;
        cointext.setString(this.dropCoin );

        var iconArray = new Array();
        for(var i = 0; i < 5; i++){
            iconArray[i] = layer.getChildByName( "char"+i );
        }
        //取得できる最大値を求める
        var range = Math.floor( Math.random() * 5 );
        for(var i = 0; i < range; i++ ){
            var charArgs = Math.floor( Math.random() * MapData.map[playerValue.mapid].dropChar.length );
            var charId = MapData.map[playerValue.mapid].dropChar[charArgs];
            this.dropChar.push( charId );
            var tmpchar = new charIconSprite( charId );
            iconArray[i].addChild( tmpchar );
            CharStorage.push( getChar( charId, 1, -1 ) );
        }
        playBgm( 2 );
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {

    },
    onQuest: function( button, type ){
        if (type == 2){
            playSe( 0 );
            areaNo++;
            if(areaNo >= 30 ){
                areaNo = 29;
            }
            
            cc.director.pushScene(new QuestNode);
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
            playBgm( 0 );

        }
    },
});

var ResultNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new ResultLayer();
        this.addChild(layer);
    }
});

