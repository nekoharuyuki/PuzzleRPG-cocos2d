
var TitleLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
        charDatatInit();
        mapDatatInit();
        if(hasData()){
            dataLoad();
        } else {
            dataSave();
        }
        //デッバッグ用に常にプレイヤーデータを初期化
        //dataClear();
        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Title_Scene );
        this.addChild( layer );
        var startBtn = layer.getChildByName( "start_btn" );
        if( playerValue.first ){
            startBtn.addTouchEventListener( this.onCharSelect, this );
        }else{
            startBtn.addTouchEventListener( this.onMypage, this );
        }
        
        playBgm( 0 );
        
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {
        
    },
    onMypage: function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            cc.director.pushScene(new MypageNode);
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
        }
    },
    onCharSelect:function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            cc.director.pushScene( new CharselectNode );
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
        }
    }
});

var TitleNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new TitleLayer();
        this.addChild(layer);
    }
});

