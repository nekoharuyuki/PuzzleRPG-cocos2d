
var EvolutionLayer = cc.Layer.extend({
    menu:null,
    selectchar : new Array(),
    materialnametext : new Array(),
    materialleveltext : new Array(),
    char : new Array(),
    charnametext : new Array(),
    charleveltext : new Array(),
    iconArray : new Array(),
    selectIcon : -1,
    offsetPos : null,
    DragNode : null,
    currentPos : 0,
    nametext : null,
    leveltext : null,
    needcointext : null,
    needcoin : 0,
    cointext : null,
    exptext : null,
    base : null,
    materialBase : new Array(),
    material : new Array(),
    evolution_btn : null,
    evolution : false,
    evolutionCnt : 0,
    ctor:function () {
        this._super();
        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Evolution_Scene );
        this.addChild(layer, 1);
        this.menu = new MenuLayer();
        layer.addChild(this.menu, 2);        
        var synthetic_base = layer.getChildByName( "evolution_base" );
        this.DragNode = synthetic_base.getChildByName( "DragNode" );
        this.selectchar[0] = synthetic_base.getChildByName( "basechar" );
        this.iconArray[0] = new charIconSprite( 0 );
        this.selectchar[0].addChild( this.iconArray[0] );
        this.iconArray[0].opacity = 1;
        this.nametext = synthetic_base.getChildByName( "nametext" );
        this.nametext.setString( " " );
        this.leveltext = synthetic_base.getChildByName( "leveltext" );
        this.leveltext.setString( " " );
        this.needcointext = synthetic_base.getChildByName( "needcointext" );
        this.needcointext.setString( "0" );
        this.cointext = synthetic_base.getChildByName( "cointext" );
        this.cointext.setString( playerValue.coin );
        this.exptext = synthetic_base.getChildByName( "exptext" );
        this.exptext.setString( "0" );
        this.evolution_btn = synthetic_base.getChildByName( "evolution_btn" );
        this.evolution_btn.addTouchEventListener( this.onEvolution, this );
        var left0_btn = synthetic_base.getChildByName( "left0_btn" );
        left0_btn.addTouchEventListener( this.onLeft0, this );
        var right0_btn = synthetic_base.getChildByName( "right0_btn" );
        right0_btn.addTouchEventListener( this.onRight0, this );
        var left1_btn = synthetic_base.getChildByName( "left1_btn" );
        left1_btn.addTouchEventListener( this.onLeft1, this );
        var right1_btn = synthetic_base.getChildByName( "right1_btn" );
        right1_btn.addTouchEventListener( this.onRight1, this );

        for( var i = 0; i < 3; i++ ){
            //素材キャラ用
            this.selectchar[i+1] = synthetic_base.getChildByName( "material"+i );
            this.iconArray[i+1] = new charIconSprite( 0 );
            this.selectchar[i+1].addChild( this.iconArray[ i+1 ] );
            this.iconArray[i+1].opacity = 1;

            this.materialnametext[i] = synthetic_base.getChildByName( "materialnametext"+i );
            this.materialnametext[i].setString( " " );
            this.materialleveltext[i] = synthetic_base.getChildByName( "materialleveltext"+i );
            this.materialleveltext[i].setString( " " );
            //選択キャラ用
            this.selectchar[i+4] = synthetic_base.getChildByName( "char"+i );
            this.charleveltext[i] = synthetic_base.getChildByName( "charleveltext"+i );
            this.charnametext[i] = synthetic_base.getChildByName( "charnametext"+i );
            if( typeof CharStorage[ this.currentPos+i ] === "undefined" ){
                this.charleveltext[i].setString( " " );
                this.charnametext[i].setString( " " );
            }else{
                this.iconArray[i+4] =  new charIconSprite( CharStorage[ this.currentPos+i ].id ) ;
                this.selectchar[i+4].addChild( this.iconArray[i+4] );
                this.iconArray[i+4].opacity = 255;
                this.charleveltext[i].setString( "Lv"+CharStorage[ this.currentPos+i ].level );
                this.charnametext[i].setString( CharStorage[ this.currentPos+i ].name );
            }
        }

        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.TouchBegan,
            onTouchMoved: this.TouchMoved,
            onTouchEnded: this.TouchEnded,
        });
        cc.eventManager.addListener( touchListener, this );
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {
        // 進化のジングル分ウェイト
        if( this.evolution == true ){
            if( this.evolutionCnt > 200 ){
                this.evolution = false;
                this.evolution = 0;
                playBgm( 0 );
            } else {
                this.evolutionCnt++;
            }
        }

    },
    TouchBegan: function (touch, event){
        var target = event.getCurrentTarget();
        target.move = false;
        var location = touch.getLocation();
        for( var i = 4; i < 7; i++ ){
            if( target.iconArray[i] ){
                if( target.iconArray[i].isTouchPoint( location ) ){
                    if( target.iconArray[i].opacity != 100 ){
                        target.selectIcon = i;
                        target.DragNode.removeAllChildren();
                        var icon = new charIconSprite( target.iconArray[i].charId );
                        target.iconArray[i].opacity = 100;
                        target.DragNode.addChild( icon );
                        target.DragNode.setPosition( target.selectchar[i].getPosition() );
                        target.offsetPos = cc.p( target.DragNode.x - location.x, target.DragNode.y - location.y );
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
        if( target.selectIcon > -1 ){
            var movePos = cc.p( location.x + target.offsetPos.x, location.y + target.offsetPos.y );
            target.DragNode.setPosition( movePos );
            target.move = true;
        }
    },
    TouchEnded: function (touch, event){
        var target = event.getCurrentTarget();
        var location = touch.getLocation();

        if( target.selectIcon > -1 ){
            target.DragNode.removeAllChildren();
            target.iconArray[target.selectIcon].opacity = 255;
            if( target.selectIcon > 2 ){

                for( var i = 0; i < 4; i++ ){
                    if( target.iconArray[i] ){
                        if( target.iconArray[i].isTouchPoint( location ) ){
                            cc.log("icon drop"+i);
                            if( i == 0 ){
                                target.selectchar[i].removeAllChildren();
                                target.base = CharStorage[ target.currentPos+target.selectIcon-4 ];
                                target.iconArray[i] = new charIconSprite( target.base.id );
                                target.selectchar[i].addChild( target.iconArray[i] );
                                target.iconArray[target.selectIcon].opacity = 100;
                                target.nametext.setString( target.base.name );
                                target.leveltext.setString( "Lv" + target.base.level );
                                target.exptext.setString( getCurrentExp( target.base.level, target.base.exp )+"/"+getNextExp( target.base.level )  );
                                //ここで、ドロップが完了した時点で、素材キャラアイコンを表示させる
                                for( var j = 0; j < 3; j++){
                                    //キャラテーブルから該当するキャラデータを引っ張る
                                    target.materialBase[j] = CharData.char[ target.base.evolution[j] - 1 ];
                                    var tempCoin = target.materialBase[j].price;
                                    //アイコンのみ表示させる　半透明で
                                    var materialBaseIcon = new charIconSprite( target.materialBase[j].id );
                                    target.selectchar[j+1].addChild( materialBaseIcon );
                                    materialBaseIcon.opacity = 100;
                                    target.needcoin += tempCoin;
                                }
                                target.needcointext.setString( target.needcoin );
                            }else{
                                if( target.iconArray[0].opacity > 1 && 
                                    !CharStorage[ target.currentPos+target.selectIcon-4 ].party &&
                                    target.materialBase[i-1].id == CharStorage[ target.currentPos+target.selectIcon-4 ].id ){
                                    target.selectchar[i].removeAllChildren();
                                    target.material[i-1] = CharStorage[ target.currentPos+target.selectIcon-4 ];
                                    target.iconArray[i] = new charIconSprite( target.material[i-1].id );
                                    target.selectchar[i].addChild( target.iconArray[i] );
                                    target.iconArray[target.selectIcon].opacity = 100;
                                    target.materialnametext[i-1].setString( target.material[i-1].name );
                                    target.materialleveltext[i-1].setString( "Lv" + target.material[i-1].level );
                                    target.needcoin += target.material[i-1].price;
                                    target.needcointext.setString( target.needcoin );
                                    target.evolution_btn.setBright( true );
                                    target.evolution_btn.setEnabled( true );
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        target.UpdateStorage();
        target.offsetPos = null;
        target.selectIcon = -1;

    },
    onLeft1: function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            this.currentPos--;
            if( this.currentPos < 0 ){
                this.currentPos = 0;
            }
            this.UpdateStorage();
        }
    },
    onRight1: function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            this.currentPos++;
            if( this.currentPos > CharStorage.length-3 ){
                this.currentPos = CharStorage.length-3;
                if( CharStorage.length < 3 ){
                    this.currentPos = 0;
                }
            }
            this.UpdateStorage();
        }
    },
    onEvolution : function( button, type ){
        if ( type == 2 ){
            playSe( 0 );
            //進化に必要なお金があるか確認
            if( playerValue.coin < this.needcoin ){
                return;
            }
            //進化の処理
            //進化できるかチェックする
            //最大レベル未満の時は進化させない
            if( this.base.maxLevel > this.base.level ){
                return;
            }
            //必要な素材キャラが揃っているかチェック
            for( var i = 0; i < 3; i++ ){
                if( typeof this.material[i] === "undefined" || this.material[i] == null ){
                    continue;
                }else{
                    if( this.material[i].id == this.base.evolution[i] ){
                        this.evolution = true;
                    }else{
                        this.evolution = false;
                        break;
                    }
                }
            }
            if(!this.evolution){
                return;
            }
            playBgm( 4 );
            evolutionCnt = 0;
            //限界突破
            this.base.overLimit++;
            this.base.maxLevel = CharData.char[ this.base.id - 1 ].maxLevel[ this.base.overLimit ];
            //素材キャラのアイコン消して
            //ストレージからも素材キャラけして
            for( var i = 0; i < 3; i++ ){
                this.selectchar[i+1].removeAllChildren();
                this.iconArray[i+1] = new charIconSprite( 0 );
                this.selectchar[i+1].addChild( this.iconArray[i+1] );
                this.iconArray[i+1].opacity = 1;
                this.materialnametext[i].setString( " " );
                this.materialleveltext[i].setString( " " );
                if( typeof this.material[i] === "undefined" || this.material[i] == null ){
                    continue;
                }else{
                    removeChar( this.material[i].storageId );
                    this.material[i] = null;
                }
            }
            //ストレージの表示更新する
            this.UpdateStorage();
            //ベースのステータス更新
            this.leveltext.setString( "Lv" + this.base.level );
            this.exptext.setString( getCurrentExp( this.base.level, this.base.exp )+"/"+getNextExp( this.base.level )  );
            //ボタンのdisable化
            this.evolution_btn.setBright( false );
            this.evolution_btn.setEnabled( false );
            playerValue.coin -= this.needcoin;
            this.cointext.setString( playerValue.coin );
            this.needcoin = 0;
            this.needcointext.setString( this.needcoin );
            dataSave();
        }
    },
    UpdateStorage : function(){
        for( var i = 0; i < 3; i++ ){
            this.selectchar[i+4].removeAllChildren();
            if( this.currentPos+i < CharStorage.length ){
                this.iconArray[i+4] = new charIconSprite( CharStorage[ this.currentPos+i ].id );
                this.selectchar[i+4].addChild( this.iconArray[i+4] );
                
                this.charleveltext[i].setString( "Lv"+CharStorage[ this.currentPos+i ].level );
                this.charnametext[i].setString( CharStorage[ this.currentPos+i ].name );
                
                if(CharStorage[ this.currentPos+i ].party && this.base != null ){
                    this.iconArray[i+4].opacity = 100;
                }else{
                    this.iconArray[i+4].opacity = 255;
                }
                if( this.base != null ){
                    if( this.base.storageId == CharStorage[ this.currentPos+i ].storageId ){
                        this.iconArray[i+4].opacity = 100;
                    }
                }
                for( var j = 0; j < 3; j++ ){
                    cc.log("material"+this.material[j]);
                    if( typeof this.material[j] === "undefined" || this.material[j] == null ){
                        continue;
                    }else{
                        if( this.material[j].storageId == CharStorage[ this.currentPos+i ].storageId ){
                            this.iconArray[i+4].opacity = 100;
                        }
                    }
                }
            }
        }
    },
});

var EvolutionNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new EvolutionLayer();
        this.addChild( layer );
    }
});

