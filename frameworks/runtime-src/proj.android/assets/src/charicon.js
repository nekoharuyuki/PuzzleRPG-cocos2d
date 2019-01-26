var charIconSprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.charIcon_00_png,res.charIcon_01_png,res.charIcon_02_png,res.charIcon_03_png,res.charIcon_04_png,res.charIcon_05_png,res.charIcon_06_png,res.charIcon_07_png,res.charIcon_08_png,res.charIcon_09_png],
	touched : null,
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 0 || this.spriteList.length -1 < char_id ){
			char_id = 0;
		}
		this.initWithFile( this.spriteList[ char_id ] );
		this.charId = char_id;
	},
	isTouchPoint : function( _point ){
		return cc.rectContainsPoint( this.getRect(), _point );
	},
	getRect : function(){
		var point = cc.p( this.x, this.y );
		point = this.convertToWorldSpace( point );
		var w = this.getContentSize().width;
		var h = this.getContentSize().height;
		return cc.rect( point.x, point.y, w, h );
	}
})

var charBattleIconSprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.charBattleIcon_00_png,res.charBattleIcon_01_png,res.charBattleIcon_02_png,res.charBattleIcon_03_png,res.charBattleIcon_04_png,res.charBattleIcon_05_png,res.charBattleIcon_06_png,res.charBattleIcon_07_png,res.charBattleIcon_08_png,res.charBattleIcon_09_png],
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 0 || this.spriteList.length -1 < char_id ){
			char_id = 0;
		}
		this.initWithFile( this.spriteList[ char_id ] );
		this.charId = char_id;
	}
})

var charSprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.player_01_png,res.player_02_png,res.player_03_png,res.player_04_png,res.player_05_png,res.player_06_png,res.player_07_png,res.player_08_png,res.player_09_png],
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 1 || this.spriteList.length -1 < char_id ){
			char_id = 1;
		}
		this.initWithFile( this.spriteList[ char_id - 1 ] );
		this.charId = char_id;
	}
})

var charSelectSprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.princessselect_01_png,res.princessselect_02_png,res.princessselect_03_png,res.princessselect_04_png,res.princessselect_05_png,res.princessselect_06_png,res.princessselect_07_png,res.princessselect_08_png,res.princessselect_09_png],
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 1 || this.spriteList.length -1 < char_id ){
			char_id = 1;
		}
		this.initWithFile( this.spriteList[ char_id - 1 ] );
		this.charId = char_id;
	}
})

var enemyIconSprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.enemyIcon_01_png,res.enemyIcon_02_png,res.enemyIcon_03_png,res.enemyIcon_04_png,res.enemyIcon_05_png,res.enemyIcon_06_png,res.enemyIcon_07_png,res.enemyIcon_08_png,res.enemyIcon_09_png],
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 1 || this.spriteList.length -1 < char_id ){
			char_id = 1;
		}
		this.initWithFile( this.spriteList[ char_id - 1 ] );
		this.charId = char_id;
	}
})

var enemySprite = cc.Sprite.extend({
	charId : 0,
	spriteList : [res.enemy_01_png,res.enemy_02_png,res.enemy_03_png,res.enemy_04_png,res.enemy_05_png,res.enemy_06_png,res.enemy_07_png,res.enemy_08_png,res.enemy_09_png],
	ctor:function( char_id ){
		this._super();
		char_id = parseInt( char_id );
		if( char_id < 1 || this.spriteList.length -1 < char_id ){
			char_id = 1;
		}
		this.initWithFile( this.spriteList[ char_id - 1 ] );
		this.setAnchorPoint( 0.5, 0 );
		this.charId = char_id;
	}
})