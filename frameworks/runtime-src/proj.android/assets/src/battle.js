
var BattleLayer = cc.Layer.extend({
    puzzle : null,
    enemy : null,
    hpBar : null,
    spBar : new Array(),
    chara_player : new Array(),
    playerAnimNode : new Array(),
    playerAction : new Array(),
    enemyAnimNode : new Array(),
    enemyAction : new Array(),
    totalHp : 0,
    maxHp : 0,
    turn : 0,
    slipTurn : 0,
    slipDmg : 0,
    CharIconNode : new Array(),
    chara_enemy : new Array(),
    enemy_base : new Array(),
    ename : new Array(),
    eturn : new Array(),
    ehpBar : new Array(),
    _time:0,
    jewelyStackData : [0,0,0,0,0],
    action : null,
    stageData : null,
    fieldNo : 0,
    fieldEnd : false,
    gameover : false,
    gameoverCnt : 0,
    skillOn :false,
    skillCnt : 1,
    skillSelectChar : -1,
    healOn : false,
    healCnt : 1,
    myTurn : new Array(),
    ctor:function () {
        this._super();
        
        var size = cc.winSize;
        
        charDatatInit();
        mapDatatInit();
        
        this.initEnemy();
        
        var layer = ccs.csLoader.createNode( res.Battle_Scene );
        this.addChild( layer, 1 );
        var puzzleBase = layer.getChildByName( "battle_puzle" );
        this.puzzle = new puzzleLayer();
        puzzleBase.addChild( this.puzzle, 2 );
        var PartyHp_bar = layer.getChildByName( "PartyHp_bar" );
        this.hpBar = PartyHp_bar.getChildByName( "hp_bar" );
        var barVal = this.hpBar.getPercent();
        barVal = 100;
        this.hpBar.setPercent( barVal );
        for( var i = 0; i < 3; i++ ){
            //プレイヤー初期化
            this.myTurn[i] = 0;
            var CharSp_bar = layer.getChildByName( "CharSp_bar"+i );
            this.spBar[i] = CharSp_bar.getChildByName( "sp_bar" );
            this.spBar[i].setPercent( 0 );
            
            this.CharIconNode[i] = layer.getChildByName( "CharIconNode"+i );
            
            this.chara_player[i] = layer.getChildByName( "chara_player_"+i );
            var tmpNode = ccs.csLoader.createNode( res.PlayerBattleAnim );
            this.chara_player[i].addChild( tmpNode );
            this.playerAnimNode[i] = tmpNode.getChildByName( "CharNode" );
            this.playerAction[i] = ccs.actionTimelineCache.createAction( res.PlayerBattleAnim );
            this.playerAnimNode[i].runAction( this.playerAction[i] );
            this.playerAction[i].gotoFrameAndPause( 0 );
            
            var leveltext = layer.getChildByName( "level"+i );
            var nametext = layer.getChildByName( "name"+i );
            if( typeof partyValue[i] !== "undefined" ){
                var charIcon = new charIconSprite( partyValue[i].id );
                this.CharIconNode[i].addChild( charIcon );
                var charPng = new charSprite( partyValue[i].id );
                this.playerAnimNode[i].addChild( charPng );
                leveltext.setString( "Lv"+partyValue[i].level );
                nametext.setString( partyValue[i].name );
                var skill_btn = this.CharIconNode[i].getChildByName( "skill_btn"+i );
                skill_btn.addTouchEventListener( this.onSkill, this );
            }else{
                nametext.setString( " " );
                leveltext.setString( " " );
            }
            
            //敵初期化
            this.chara_enemy[i] = layer.getChildByName( "chara_enemy_"+ i );
            this.enemy_base[i] = layer.getChildByName( "enemy_base"+ i );
            this.ename[i] = layer.getChildByName( "ename"+i );
            this.eturn[i] = layer.getChildByName( "eturn"+ i );
            var tmpHp_bar = layer.getChildByName( "EnemyHp_bar"+i );
            this.ehpBar[i] = tmpHp_bar.getChildByName( "hp_bar" );
            var tmpNode = ccs.csLoader.createNode( res.EnemyBattleAnim );
            this.chara_enemy[i].addChild( tmpNode );
            this.enemyAnimNode[i] = tmpNode.getChildByName( "CharNode" );
            this.enemyAction[i] = ccs.actionTimelineCache.createAction( res.EnemyBattleAnim );
            this.enemyAnimNode[i].runAction( this.enemyAction[i] );
            this.enemyAction[i].gotoFrameAndPause( 0 );
            
        }
        this.initBattle();
        
        this.action = ccs.actionTimelineCache.createAction( res.Battle_Scene );
        layer.runAction( this.action );
        this.action.gotoFrameAndPause( playerValue.mapid );
        
        this.totalHp = getTotalHp();
        this.maxHp = this.totalHp;
        
        playBgm( 1 );
        
        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {
	if( this.gameover == true ){
            if( this.gameoverCnt > 280 ){
                cc.director.pushScene( new QuestNode );
                this.removeAllChildren();
                playBgm( 0 );
            } else {
                this.gameoverCnt++;
            }
	}
        var barVal = this.hpBar.getPercent();
        if( this.fieldEnd ){
            if( this.fieldNo >= this.stageData.stage ){
                //result に移動
                cc.director.pushScene( new ResultNode );
                cc.eventManager.removeAllListeners();
                this.removeAllChildren();
            }else{
                this.action.gotoFrameAndPause( areaNo );
                this.initEnemy();
                this.initBattle();
                this.fieldEnd = false;
                this.puzzle.myturn = true;
            }
        }else{
            if( this.puzzle.jewelyStack.length > 0 ){
                
                this.puzzle.myturn = false;
                tmpStackData = this.puzzle.jewelyStack.shift();
                //一通りスタックされたデータを取り出す
                for( var i = 0; i < 5; i++ ){
                    this.jewelyStackData[i] += tmpStackData[i];
                }
                cc.log("jewelyStack:"+this.puzzle.jewelyStack.length);
            }else{
                //cc.log("myturn:"+this.puzzle.myturn);
                if( !this.puzzle.myturn ){
                    //自分の攻撃
                    //cc.log("jewelyStackData:"+this.jewelyStackData);
                    for( var i = 0; i < 5; i++ ){
                        if( this.jewelyStackData[i] > 0 ){
                            this.myAttack( i, this.jewelyStackData[i] );

                            this.jewelyStackData[i] = 0;
                            playSe( 0 );
                            break;
                        }
                    }
                    
                    if( this.puzzle.turnend && !this.puzzle.myturn ){
                        if( !this.playerAction[0].isPlaying() &&
                            !this.playerAction[1].isPlaying() &&
                            !this.playerAction[2].isPlaying() ){
                            
                            this.puzzle.myturn = true;
                            for( var i = 0; i < 3; i++ ){
                                cc.log("e"+i+":"+this.enemy[i].hp);
                                var hpVal = this.enemy[i].hp / this.enemy[i].max_hp * 100;
                                this.ehpBar[i].setPercent( hpVal );
                                if( this.ehpBar[i].getPercent() == 0 ){
                                    this.chara_enemy[i].visible = false;
                                    this.enemy_base[i].removeAllChildren();
                                    this.ename[i].setString( " " );
                                    this.eturn[i].setString( " " );
                                }else{
                                    this.eturn[i].setString( this.enemy[i].current_turn+"turn" );
                                }
                                
                                this.enemy[i].current_turn--;
                            }
                            //スリップダメージ処理
                            if(this.slipTurn > 0){
                                for( i = 0; i < 3; i++ ){
                                    if( this.enemy[i].hp > 0 ){
                                        this.enemy[i].hp -= this.slipDmg;
                                        if( this.enemy[i].hp < 0 ){
                                            this.enemy[i].hp = 0;
                                        }
                                        var hpVal = this.enemy[i].hp / this.enemy[i].max_hp * 100;
	                                this.ehpBar[i].setPercent( hpVal );
                                        this.skillParticle(0, 4, 0, 400, 0);
                                        playSe( 5 );
                                        break;
                                    }
                                }
                                this.slipTurn--;
                            }
                            cc.log("slip Turn"+this.slipTurn);
                            cc.log("turn end");
                        }
                        
                        //ステージクリア判定
                        if( this.ehpBar[0].getPercent() == 0 &&
                            this.ehpBar[1].getPercent() == 0 &&
                            this.ehpBar[2].getPercent() == 0 &&
                            !this.fieldEnd ){
                            this.fieldNo++;
                            this.fieldEnd = true;
                            this.puzzle.myturn = false;
                        }
                    }
                }
            }
        }
        //敵の攻撃チェック
        if( !this.enemyAction[0].isPlaying() &&
            !this.enemyAction[1].isPlaying() &&
            !this.enemyAction[2].isPlaying() ){
            this.enemyAttack();
        }
        //HP減算処理
        var hpVal = this.totalHp / this.maxHp * 100;
        this.hpBar.setPercent( hpVal );
/****************
	
        if(this.healOn){
            this.healCnt++;
            if( (this.healCnt % 60)== 0 ){
                this.healOn = false;
                this.healCnt = 1;
                for( i = 0; i < 3; i++ ){
                    if( typeof partyValue[i] !== "undefined" ){
                        this.skillEnd( i );
                    }
                }    
            }
        }
************/
        // スキル発動
        if( this.skillOn ){
            if( this.skillCnt == 1 ){
                this.skillParticle( this.skillSelectChar, partyValue[this.skillSelectChar].attribute, partyValue[this.skillSelectChar].skill, 0, 0 );
                playSe( partyValue[this.skillSelectChar].attribute + 1 );
            }
            if( (this.skillCnt % 60)==0 ){
                this.skillCnt = 1;
                this.skillOn = false;
                this.skillEnd( this.skillSelectChar );
                this.spBar[this.skillSelectChar].setPercent( 0 );
                
                for( i = 0; i < 3; i++ ){
                    var atkPlus = 1.0+(partyValue[this.skillSelectChar].skill/5);
                    if( this.enemy[i].attribute == partyValue[this.skillSelectChar].attribute ){
                        atkPlus *= 1.2;
                    }
                    this.enemy[i].hp -= partyValue[this.skillSelectChar].atk * atkPlus;
                    if( this.enemy[i].hp < 0 ){
                        this.enemy[i].hp = 0;
                    }
                    
                    var hpVal = this.enemy[i].hp / this.enemy[i].max_hp * 100;
                    this.ehpBar[i].setPercent( hpVal );
                }
                this.skillSelectChar = -1;
                cc.log("skill end");
            }else{
                this.skillCnt++;
            }
        }
    },
    initBattle : function() {
        for( var i = 0; i < 3; i++ ){
            var tmpenemy = new enemySprite( this.enemy[i].id );
            this.enemyAnimNode[i].addChild( tmpenemy );
            var tmpIcon = new enemyIconSprite( this.enemy[i].id );
            this.enemy_base[i].addChild( tmpIcon );
            this.ename[i].setString( this.enemy[i].name );
            this.eturn[i].setString( this.enemy[i].current_turn+"turn" );
            this.ehpBar[i].setPercent( 100 );
        }
    },
    initEnemy : function() {
        this.stageData = MapData.map[ playerValue.mapid ];
        
        this.enemy = new Array();
        for( var i = 0; i < 3; i++ ){
            var rnd = Math.floor( Math.random() * this.stageData.enemy.length );
            this.enemy[i] = this.createEnemy( this.stageData.enemy[rnd], this.stageData.id );
        }
        cc.log("enemy data"+this.enemy );
    },
    createEnemy : function( _id, _level ) {
        var baseCharaData = CharData.enemy[_id - 1];
        var enemyHp = baseCharaData.hp + (baseCharaData.maxHp - baseCharaData.hp) * ((_level - 1)/(99-1));
        var enemyAtk = baseCharaData.atk + (baseCharaData.maxAtk - baseCharaData.atk) * ((_level - 1)/(99-1));
        var enemyData = {
                id : _id,
                name : baseCharaData.name,
                level : _level,
                hp : enemyHp,
                max_hp : enemyHp,
                atk : enemyAtk,
                exp : baseCharaData.exp * _level,
                attribute : baseCharaData.attribute,
                turn : baseCharaData.turn,
                current_turn : baseCharaData.turn
        };
        return enemyData;
    },
    myAttack : function( type, atk) {
        var totalAtk = 0;
        var i;
        var attributeTable = [2, 0, 1];
        cc.log("myattack");
        switch ( type ) {
        case 0:
        case 1:
        case 2:
            if( atk > 0 ){
                for( i = 0; i < 3; i++ ){
                    if( typeof partyValue[i] !== "undefined" ){
                        if( partyValue[i].attribute == type ){
                            totalAtk += ( 1 + ( atk - 3 ) * 0.2 ) * partyValue[i].atk;
                            this.playerAction[i].gotoFrameAndPlay( 0, false );
                            this.myTurn[i]++;
                            if( this.myTurn[i] > partyValue[i].skillTurn ){
                                this.myTurn[i] = partyValue[i].skillTurn;
                            }
                            var spVal = parseFloat( this.myTurn[i] ) / parseFloat( partyValue[i].skillTurn ) * 100.0;
                            this.spBar[i].setPercent( spVal );
                        }
                    }
                }
                
                for( i = 0; i < 3; i++ ){
                    if( this.enemy[i].hp > 0 ){
                        var atkPlus = 1.0;
                        if( this.enemy[i].attribute == attributeTable[type] ){
                            atkPlus = 1.2;
                        }
                        this.enemy[i].hp -= totalAtk * atkPlus;
                        if( this.enemy[i].hp < 0 ){
                            this.enemy[i].hp = 0;
                        }
                        break;
                    }
                }
            }
            break;
        case 3:
            //回復
            if( atk > 0 ){
                var totalHeal = 0;
                for( i = 0; i < 3; i++ ){
                    if( typeof partyValue[i] !== "undefined" ){
                        totalHeal += (1 + (atk - 3) * 0.2) * (partyValue[i].atk * 0.2);
                    }
                }

                if( this.totalHp < this.maxHp ){
                    this.totalHp += totalHeal;
                    if( this.totalHp > this.maxHp ){
                        this.totalHp = this.maxHp;
                    }
                }
                this.healOn = true;
                this.healCnt = 1;
                for( i = 0; i < 3; i++ ){
                    cc.log("i:"+i);
                    if( typeof partyValue[i] !== "undefined" ){
                    cc.log("OK:"+i);
                        this.skillParticle(i, 3, 0, 0, 0);
                    }
                }
                //HP増加処理
                var hpVal = this.totalHp / this.maxHp * 100;
                this.hpBar.setPercent( hpVal );
                playSe( 4 );
            }
            break;
        case 4:
            //スリップ
            if( atk > 0 ){
                totalAtk = 0;
                this.slipDmg = 0;
                for( i = 0; i < 3; i++ ){
                    if( typeof partyValue[i] !== "undefined" ){
                        totalAtk += partyValue[i].atk;
                    }
                }
                cc.log("totalAtk:"+totalAtk);
                this.slipTurn = atk - 1;
                if( this.slipTurn > 5 ){
                    this.slipTurn = 5;
                }
                this.slipDmg = totalAtk * 0.05;
            }
            cc.log("slip dmg:"+totalAtk + ":" + this.slipDmg);
            break;
        default:
            break;
        }
    },
    enemyAttack : function() {
        for( var i = 0; i < 3; i++ ){
            if( this.enemy[i].hp > 0 && this.enemy[i].current_turn < 0 ){
                //攻撃
                cc.log("enemy attack");
                this.totalHp -= this.enemy[i].atk;
                this.enemy[i].current_turn = this.enemy[i].turn;
                this.enemyAction[i].gotoFrameAndPlay( 0, false );
                if( this.totalHp <= 0 && this.gameover == false){
                    //ゲームオーバー
                    //一旦強制的にクエスト画面に戻す
                    cc.log("game over");
                    this.gameover = true;
                    this.gameoverCn = 0;
                    playBgm( 3 )
                    cc.eventManager.removeAllListeners();
                }
            }
        }
    },
    onStageClear : function() {
        
    },
    onResult : function(){
        cc.director.pushScene( new ResultNode );
        cc.eventManager.removeAllListeners();
        this.removeAllChildren();
    },
    onSkill : function( button, type ){
        cc.log("skill btn "+button.getTag() );
        if( type == 2 ){
            if( !this.skillOn && this.skillSelectChar == -1 ){
                this.skillSelectChar = button.getTag();
                if( this.myTurn[this.skillSelectChar] == partyValue[this.skillSelectChar].skillTurn ){
                    this.skillOn = true;
                    this.myTurn[this.skillSelectChar] = 0;
                }
            }
        }
        cc.log("skill btn "+this.skillSelectChar );
    },
    skillParticle:function ( no, attrib, rare, x, y ) {
        var skillName = ["Fire","Water","Wood","Heal","Slip"];
        var sName = "res."+skillName[attrib]+"_texture"+(rare+1)+"_plist";
        var tempParticle = new cc.ParticleSystem( eval( sName ) );
        cc.log("skillParticle " + sName + " " + tempParticle);
        tempParticle.setPosition( x, y );
        tempParticle.setName( "skill_" + sName);
        this.chara_player[no].addChild( tempParticle, 20 );
        tempParticle.setAutoRemoveOnFinish( true );
    },
    skillEnd : function( no ){
        var allChildren = this.chara_player[no].getChildren();
        for(var ii = 0; ii< allChildren.length; ii++) {
            cc.log(allChildren[ii].getName());
            if(allChildren[ii].getName() == "skill"){
                this.chara_player[no].removeChild( allChildren[ii] );
                break;
            }
        }
    }
    
});

var BattleNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new BattleLayer();
        this.addChild( layer );
    }
});

