
var MenuLayer = cc.Layer.extend({
	sprite:null,
	mypageBtn:null,
	questBtn:null,
	partyBtn:null,
	syntheticBtn:null,
	evolutionBtn:null,
	otherBtn:null,
	ctor:function () {
		//////////////////////////////
		// 1. super init first
		this._super();

		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.
		// ask the window size
		var size = cc.winSize;
		

		var layer = ccs.csLoader.createNode( res.Menu_Scene );
		this.addChild(layer, 1);

		this.mypageBtn = layer.getChildByName("ui_mypage_btn");
		this.mypageBtn.addTouchEventListener(this.onMypage, this);
		this.questBtn = layer.getChildByName("ui_quest_btn");
		this.questBtn.addTouchEventListener(this.onQuest, this);
		this.partyBtn = layer.getChildByName("ui_party_btn");
		this.partyBtn.addTouchEventListener(this.onParty, this);
		this.syntheticBtn = layer.getChildByName("ui_mix_btn");
		this.syntheticBtn.addTouchEventListener(this.onSynthetic, this);
		this.evolutionBtn = layer.getChildByName("ui_shinka_btn");
		this.evolutionBtn.addTouchEventListener(this.onEvolution, this);
		this.otherBtn = layer.getChildByName("ui_etc_btn");
		this.otherBtn.addTouchEventListener(this.onOther, this);
		
		this.scheduleUpdate();
		return true;
	},
	update: function( _dt ) {

	},
	onMypage: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new MypageNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	},
	onQuest: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new QuestNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	},
	onParty: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new PartyNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	},
	onSynthetic: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new SyntheticNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	},
	onEvolution: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new EvolutionNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	},
	onOther: function( button, type ){
		if (type == 2){
			playSe( 0 );
			cc.director.pushScene(new OtherNode);
			cc.eventManager.removeAllListeners();
			this.removeAllChildren();
		}
	}
});

var MenuNode = cc.Scene.extend({
	onEnter:function () {
		this._super();
		var layer = new MenuLayer();
		this.addChild(layer);
	}
});

