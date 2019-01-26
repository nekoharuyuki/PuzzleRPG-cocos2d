
var MypageLayer = cc.Layer.extend({
	sprite:null,
	menu:null,
	ctor:function () {
		this._super();

		var size = cc.winSize;
		var layer = ccs.csLoader.createNode( res.Mypage_Scene );
		this.addChild( layer, 1 );
		this.menu = new MenuLayer();
		layer.addChild( this.menu, 2 );
		
		//プレイヤーデー読込み表示
		//ここにプレイヤーのデータを読み込むコードを書く
		//あとでjsonフォーマットになると思う
		var CoinText = layer.getChildByName( "CoinText" );
		CoinText.setString( playerValue.coin );
		
		//パーティデータ読込み表示
		var CharIconNode = new Array();
		var CharLv = new Array();
		var Atk = new Array();
		var CharName = new Array();
		var i;
		for(i = 0; i < 3; i++){
			CharIconNode[i] = layer.getChildByName( "CharIconNode"+i );
			CharLv[i] = layer.getChildByName( "CharLv"+i );
			CharName[i] = layer.getChildByName( "CharName"+i );
			if(i < partyValue.length){
				var charIcon = new charIconSprite( partyValue[i].id );
				CharIconNode[i].addChild( charIcon );
				CharLv[i].setString( "Lv" + partyValue[i].level );
				CharName[i].setString( partyValue[i].name );
			}else{
				CharLv[i].setString( " " );
				CharName[i].setString( " " );
			}
			
		}
		for(i = 0; i < 3; i++){
			cc.log(i);
			Atk[i] = layer.getChildByName( "Atk"+i );
			Atk[i].setString( getAtk(i) );
		}
		var PartyHpText = layer.getChildByName( "PartyHpText" );
		var TotalHp = getTotalHp();
		PartyHpText.setString( TotalHp );
		
		this.scheduleUpdate();
		return true;
	},
	update: function( _dt ) {
		
	}
});

var MypageNode = cc.Scene.extend({
	onEnter:function () {
		this._super();
		var layer = new MypageLayer();
		this.addChild(layer);
	}
});

