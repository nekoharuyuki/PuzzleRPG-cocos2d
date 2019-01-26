
var CharselectLayer = cc.Layer.extend({
    popup_1 : null,
    popup_2 : null,
    popup_3 : null,
    selectId : 1,
    ctor:function () {
        this._super();
        var size = cc.winSize;
        
        var layer = ccs.csLoader.createNode( res.Charselect_Scene );
        this.addChild( layer, 1 );
        
        this.popup_1 = layer.getChildByName( "popup_1" );
        var char1_btn = this.popup_1.getChildByName( "char1_btn" );
        char1_btn.addTouchEventListener( this.onChar1, this );
        var char2_btn = this.popup_1.getChildByName( "char2_btn" );
        char2_btn.addTouchEventListener( this.onChar2, this );
        var char3_btn = this.popup_1.getChildByName( "char3_btn" );
        char3_btn.addTouchEventListener( this.onChar3, this );
        
        this.popup_2 = layer.getChildByName( "popup_2" );
        this.popup_2.visible = false;
        this.popup_3 = layer.getChildByName( "popup_3" );
        this.popup_3.visible = false;
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {

    },
    onChar:function( _id ){
        playSe( 0 );
        this.popup_1.visible = false;
        var yes_btn = this.popup_2.getChildByName( "yes_btn" );
        yes_btn.addTouchEventListener( this.onYes, this );
        var back_btn = this.popup_2.getChildByName( "back_btn" );
        back_btn.addTouchEventListener( this.onBack, this );
        var AttributeNode = this.popup_2.getChildByName( "AttributeNode" );
        var NameText = this.popup_2.getChildByName( "NameText" );
        NameText.setString( CharData.char[_id].name );
        var LevelText = this.popup_2.getChildByName( "LevelText" );
        var AtkText = this.popup_2.getChildByName( "AtkText" );
        AtkText.setString( CharData.char[_id].atk );
        var SkillText = this.popup_2.getChildByName( "SkillText" );
        SkillText.setString( CharData.char[_id].skillText );
        var chara_princessselect = this.popup_2.getChildByName( "chara_princessselect" );
        chara_princessselect.removeAllChildren();
        var charSprite = new charSelectSprite( _id+1 );
        chara_princessselect.addChild( charSprite, 1 );
        this.selectId = _id;
        this.popup_2.visible = true;
    },
    onChar1: function( button, type ){
        if ( type == 2 ){
            this.onChar( 0 );
        }
    },
    onChar2: function( button, type ){
        if ( type == 2 ){
            this.onChar( 1 );
        }
    },
    onChar3: function( button, type ){
        if ( type == 2 ){
            this.onChar( 2 );
        }
    },
    onYes: function( button, type ){
        if (type == 2){
            playSe( 0 );
            this.popup_2.visible = false;
            var start_btn = this.popup_3.getChildByName( "start_btn" );
            start_btn.addTouchEventListener( this.onStart, this );
            var NameText = this.popup_3.getChildByName( "NameText" );
            NameText.setString( CharData.char[this.selectId].name );
            var chara_princessselect = this.popup_3.getChildByName( "chara_princessselect" );
            var charSprite = new charSelectSprite( this.selectId+1 );
            chara_princessselect.addChild( charSprite );
            this.popup_3.visible = true;
        }
    },
    onBack: function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            this.popup_1.visible = true;
            this.popup_2.visible = false;
        }
    },
    onStart: function( button, type ){
        if (type == 2){
            playSe( 0 );
            //保存する
            playerValue.first = false;
            playerValue.char_id = this.selectId+1;
            playerValue.name = "Gen san";
            playerValue.coin = 100;
            playerValue.max_stamina = 9;
            playerValue.stamina = 9;
            
            CharStorage.push( getChar( this.selectId+1, 1, 0 ) );
            CharStorage[0].storageId = 0;
            
            //
            partyValue.push( CharStorage[0] );
            partyValue[0].party = true;
            
            dataSave();
            cc.director.pushScene( new MypageNode );
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
        }
    },
});

var CharselectNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new CharselectLayer();
        this.addChild(layer);
    }
});

