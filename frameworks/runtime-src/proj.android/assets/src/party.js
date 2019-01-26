
var PartyLayer = cc.Layer.extend({
    menu:null,
    party : new Array(),
    nametext : new Array(),
    leveltext : new Array(),
    stock : new Array(),
    paty_base : null,
    chara_statusbase : null,
    conform : null,
    currentPos : 0,
    iconArray : new Array(),
    selectIcon : -1,
    offsetPos : null,
    DragNode : null,
    healingtext : null,
    hptext : null,
    atktext0 : null,
    atktext1 : null,
    atktext2 : null,
    move : false,
    sellId : -1,
    tempPrice : 0,
    ctor:function () {
        this._super();

        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Party_Scene );
        this.addChild(layer, 1);
        this.menu = new MenuLayer();
        layer.addChild(this.menu, 2);
        
        this.chara_statusbase = layer.getChildByName( "chara_statusbase" );
        this.chara_statusbase.visible = false;
        this.conform = layer.getChildByName( "conform" );
        this.conform.visible = false;
        this.paty_base = layer.getChildByName( "paty_base" );
        this.DragNode = this.paty_base.getChildByName( "DragNode" );
        //パーティデータ読み込み
        for(var i = 0; i < 3; i++ ){
            this.party[i] = this.paty_base.getChildByName( "party"+i );
            this.nametext[i] = this.paty_base.getChildByName( "nametext"+i );
            this.leveltext[i] = this.paty_base.getChildByName( "leveltext"+i );
            if( i < partyValue.length ){
                this.iconArray[i] = new charIconSprite( partyValue[i].id );
                this.party[i].addChild( this.iconArray[i] );
                this.nametext[i].setString( partyValue[i].name );
                this.leveltext[i].setString( "Lv" + partyValue[i].level );
            }else{
                this.iconArray[i] = new charIconSprite( 0 );//ダミーアイコンの追加
                this.party[i].addChild( this.iconArray[i] );
                this.iconArray[i].opacity = 1;
                this.nametext[i].setString( " " );
                this.leveltext[i].setString( " " );
            }
        }
        
        this.healingtext = this.paty_base.getChildByName( "healingtext" );
        this.healingtext.setString( getTotalAtk() );
        this.hptext = this.paty_base.getChildByName( "hptext" );
        this.hptext.setString( getTotalHp() );
        this.atktext0 = this.paty_base.getChildByName( "atktext0" );
        this.atktext0.setString( getAtk(0) );
        this.atktext1 = this.paty_base.getChildByName( "atktext1" );
        this.atktext1.setString( getAtk(1) );
        this.atktext2 = this.paty_base.getChildByName( "atktext2" );
        this.atktext2.setString( getAtk(2) );
        for( var i = 0; i < 5; i++ ){
            this.party[i+3] = this.paty_base.getChildByName( "stock"+i );
            this.party[i+3].removeAllChildren();
            if( this.currentPos+i < CharStorage.length ){
                this.iconArray[i+3] = new charIconSprite( CharStorage[ this.currentPos+i ].id );
                this.party[i+3].addChild( this.iconArray[i+3] );
                if( CharStorage[ this.currentPos+i ].party ){
                    this.iconArray[i+3].opacity = 128;
                }else{
                    this.iconArray[i+3].opacity = 255;
                }
            }
        }
        var right_btn = this.paty_base.getChildByName( "right_btn" );
        right_btn.addTouchEventListener( this.onRight, this );
        var left_btn = this.paty_base.getChildByName( "left_btn" );
        left_btn.addTouchEventListener( this.onLeft, this );
        
        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.TouchBegan,
            onTouchMoved: this.TouchMoved,
            onTouchEnded: this.TouchEnded,
        });

        cc.eventManager.addListener(touchListener, this);
        
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {

    },
    TouchBegan: function (touch, event){
        var target = event.getCurrentTarget();
        if( target.chara_statusbase.visible ){
            return;
        }
        target.move = false;
        var location = touch.getLocation();
        for(var i = 3; i < 8; i++ ){
            if( target.iconArray[i] ){
                if( target.iconArray[i].isTouchPoint( location ) ){
                    if( target.iconArray[i].opacity != 128 ){
                        target.selectIcon = i;
                        target.DragNode.removeAllChildren();
                        var icon = new charIconSprite( target.iconArray[i].charId );
                        target.iconArray[i].opacity = 128;
                        target.DragNode.addChild( icon );
                        target.DragNode.setPosition( target.party[i].getPosition() );
                        target.offsetPos = cc.p(target.DragNode.x - location.x, target.DragNode.y - location.y);
                        break;
                    }
                }
            }
        }
        return true;
    },
    TouchMoved: function (touch, event){    
        var target = event.getCurrentTarget();
        var location = touch.getLocation();
        if( target.chara_statusbase.visible ){
            return;
        }
        if( target.selectIcon > -1 ){
            var movePos = cc.p( location.x + target.offsetPos.x, location.y + target.offsetPos.y );
            target.DragNode.setPosition( movePos );
            target.move = true;
        }
    },
    TouchEnded: function (touch, event){
        var target = event.getCurrentTarget();
        var location = touch.getLocation();
        var i;
        if( target.chara_statusbase.visible ){
            return;
        }
        if( target.selectIcon > -1 ){
            target.DragNode.removeAllChildren();
            target.iconArray[target.selectIcon].opacity = 255;
            if( target.selectIcon > 2 ){
                
                for( i = 0; i < 3; i++ ){
                    if( target.iconArray[i] ){
                        if( target.iconArray[i].isTouchPoint( location ) ){
                            cc.log("icon drop"+i);
                            target.party[i].removeAllChildren();
                            target.iconArray[i] = new charIconSprite( target.iconArray[target.selectIcon].charId );
                            target.party[i].addChild( target.iconArray[i] );
                            if( partyValue.length <= i ){
                                partyValue.push( CharStorage[target.currentPos + target.selectIcon - 3 ] );
                                partyValue[i].party = true;
                            }else{
                                partyValue[i].party = false;
                                partyValue[i] = CharStorage[target.currentPos + target.selectIcon - 3 ];
                                partyValue[i].party = true;
                            }
                            target.iconArray[target.selectIcon].opacity = 128;
                            target.nametext[i].setString( partyValue[i].name );
                            target.leveltext[i].setString( "Lv" + partyValue[i].level );
                            break;
                        }
                    }
                }
            }
        }
        target.UpdateStorage();
        if( !target.move ){
            for( i = 0; i < 8; i++ ){
                if( target.iconArray[i] ){
                    if( target.iconArray[i].isTouchPoint( location ) ){
                        var id = 1;
                        if(i < 3){
                            if( typeof partyValue[i] === "undefined" ){
                                continue;
                            }
                            id = partyValue[i].storageId;
                        }else{
                            id = CharStorage[ target.currentPos + i - 3 ].storageId;
                        }
                        cc.log(id);
                        target.sellId = id;
                        target.onShowStatus( id );
                        break;
                    }
                }
            }
        }
        target.healingtext.setString( getTotalAtk() );
        target.hptext.setString( getTotalHp() );
        target.atktext0.setString( getAtk(0) );
        target.atktext1.setString( getAtk(1) );
        target.atktext2.setString( getAtk(2) );
        target.offsetPos = null;
        target.selectIcon = -1;
        
    },
    onRight : function( button, type ) {
        if( this.chara_statusbase.visible ){
            return;
        }
        if ( type == 2 ){
            playSe( 0 );
            this.currentPos++;
            if( this.currentPos > CharStorage.length-5 ){
                this.currentPos = CharStorage.length-5;
                if( CharStorage.length < 5 ){
                    this.currentPos = 0;
                }
            }
            this.UpdateStorage();
        }
    },
    onLeft : function( button, type ) {
        if( this.chara_statusbase.visible ){
            return;
        }
        if ( type == 2 ){
            playSe( 0 );
            this.currentPos--;
            if( this.currentPos < 0 ){
                this.currentPos = 0;
            }
            this.UpdateStorage();
        }
    },
    onShowStatus : function( _id ) {
        playSe( 0 );
        this.chara_statusbase.visible = true;
        this.paty_base.visible = false;
        var sell_btn = this.chara_statusbase.getChildByName( "sell_btn" );
        sell_btn.addTouchEventListener( this.onSell, this );
        if( CharStorage[ _id ].party ){
            sell_btn.setEnabled(false);
            sell_btn.setBright(false);
        }else{
            sell_btn.setEnabled(true);
            sell_btn.setBright(true);
        }
        
        var back_btn = this.chara_statusbase.getChildByName( "back_btn" );
        back_btn.addTouchEventListener(this.onBack, this);
        var leveltext = this.chara_statusbase.getChildByName( "leveltext" );
        leveltext.setString( "Lv"+CharStorage[ _id ].level );
        var atktext = this.chara_statusbase.getChildByName( "atktext" );
        atktext.setString( CharStorage[ _id ].atk );
        var exptext = this.chara_statusbase.getChildByName( "exptext" );
        exptext.setString( CharStorage[ _id ].exp );
        var skilltext = this.chara_statusbase.getChildByName( "skilltext" );
        skilltext.setString( CharStorage[ _id ].skillText );
        var pricetext = this.chara_statusbase.getChildByName( "pricetext" );
        pricetext.setString( CharStorage[ _id ].price );
        var selectchar = this.chara_statusbase.getChildByName( "selectchar" );
        selectchar.removeAllChildren();
        var charPng = new charSelectSprite( CharStorage[ _id ].id );
        selectchar.addChild( charPng );
        var nametext = this.chara_statusbase.getChildByName( "nametext" );
        nametext.setString( CharStorage[ _id ].name );
        var attribute = this.chara_statusbase.getChildByName( "attribute" );
        
    },
    onSell : function( button, type ){
        if( this.conform.visible ){
            return;
        }
        if ( type == 2 ){
            playSe( 0 );
            var yes_btn = this.conform.getChildByName( "yes_btn" );
            yes_btn.addTouchEventListener( this.onYes, this );
            var no_btn = this.conform.getChildByName( "no_btn" );
            no_btn.addTouchEventListener( this.onNo, this );
            var pricetext_2 = this.conform.getChildByName( "pricetext_2" );
            pricetext_2.setString( CharStorage[ this.sellId ].price );
            this.conform.visible = true;
        }
    },
    onBack : function( button, type ){
        if( this.conform.visible ){
            return;
        }
        if ( type == 2 ){
            playSe( 0 );
            this.chara_statusbase.visible = false;
            this.paty_base.visible = true;
        }
    },
    onYes : function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            playerValue.coin += CharStorage[ this.sellId ].price;
            removeChar( this.sellId );
            this.sellId = -1;
            this.UpdateStorage();
            this.conform.visible = false;
            this.chara_statusbase.visible = false;
            this.paty_base.visible = true;
        }
    },
    onNo : function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            this.conform.visible = false;
            this.paty_base.visible = true;
        }
    },
    UpdateStorage : function(){
        for( var i = 0; i < 5; i++ ){
            this.party[i+3].removeAllChildren();
            if(this.currentPos+i < CharStorage.length){
                this.iconArray[i+3] = new charIconSprite( CharStorage[ this.currentPos+i ].id );
                this.party[i+3].addChild( this.iconArray[i+3] );
                if( CharStorage[ this.currentPos+i ].party ){
                    this.iconArray[i+3].opacity = 128;
                }else{
                    this.iconArray[i+3].opacity = 255;
                }
            }
        }
    }
});

var PartyNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new PartyLayer();
        this.addChild(layer);
    }
});

