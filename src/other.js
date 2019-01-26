
var OtherLayer = cc.Layer.extend({
    menu:null,
    se_on : null,
    se_off : null,
    bgm_on : null,
    bgm_off : null,
    ctor:function () {
        this._super();
        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Other_Scene );
        this.addChild( layer, 1 );
        this.menu = new MenuLayer();
        layer.addChild( this.menu, 2 );
        
        var popup_other = layer.getChildByName( "popup_other" );
        var TitleBack_btn = popup_other.getChildByName( "TitleBack_btn" );
        TitleBack_btn.addTouchEventListener( this.onTitle, this );
        
        this.se_on = popup_other.getChildByName( "se_on" );
        this.se_on.addTouchEventListener( this.onSeOnOff, this );
        this.se_off = popup_other.getChildByName( "se_off" );
        this.se_off.addTouchEventListener( this.onSeOnOff, this );
        this.se_on.setBright( !g_se );
        this.se_on.setEnabled( !g_se );
        this.se_off.setBright( g_se );
        this.se_off.setEnabled( g_se );

        this.bgm_on = popup_other.getChildByName( "bgm_on" );
        this.bgm_on.addTouchEventListener( this.onBgmOnOff, this );
        this.bgm_off = popup_other.getChildByName( "bgm_off" );
        this.bgm_off.addTouchEventListener( this.onBgmOnOff, this );
        this.bgm_on.setBright( !g_bgm );
        this.bgm_on.setEnabled( !g_bgm );
        this.bgm_off.setBright( g_bgm );
        this.bgm_off.setEnabled( g_bgm );        

        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {
        
        
    },
    onTitle: function( button, type ){
        if (type == 2){
            playSe( 0 );
            cc.director.pushScene(new TitleNode);
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
        }
    },
    onBgmOnOff : function( button, type ){
        if (type == 2){
            g_bgm = !g_bgm;
            this.bgm_on.setBright( !g_bgm );
            this.bgm_on.setEnabled( !g_bgm );
            this.bgm_off.setBright( g_bgm );
            this.bgm_off.setEnabled( g_bgm );
            playBgm( 0 );
        }
    },
    onSeOnOff : function( button, type ){
        if (type == 2){
            g_se = !g_se;
            this.se_on.setBright( !g_se );
            this.se_on.setEnabled( !g_se );
            this.se_off.setBright( g_se );
            this.se_off.setEnabled( g_se );
            playSe( 0 );
        }
    },
});

var OtherNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new OtherLayer();
        this.addChild(layer);
    }
});

