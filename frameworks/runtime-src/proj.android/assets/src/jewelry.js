var JSTATUS ={
		STOP : 0,
		MOVE : 1,
		BROKEN :2
}



var jewelrySprite = cc.Sprite.extend({
	jewelryNo:0,
	jewelryX:0,
	jewelryY:0,
	state:JSTATUS["STOP"],
	jewelryPngArray:[res.jewelry1_png, res.jewelry2_png, res.jewelry3_png, res.jewelry4_png, res.jewelry5_png],
	ctor:function(jewelryType){
		this._super();
		this.state = JSTATUS["STOP"];
		
		if( jewelryType > this.jewelryPngArray.length - 1 ){
			jewelryType = 0;
		}
		this.initWithFile( this.jewelryPngArray[jewelryType] );
		this.jewelryNo = jewelryType;
	},
	jewelryBroken:function(){
		this.stopAllActions();
		var action = cc.RemoveSelf.create();
		this.runAction( action );
		this.state = JSTATUS["BROKEN"];
	},
	jewelryMove:function( _x, _y ){
		this.state = JSTATUS["MOVE"];
		var mySprite = this;	//コールバック関数内で自身を参照する為のおまじない
		var moveAction = cc.MoveTo.create( 0.2, cc.p( _x, _y) );
		var moveFunc = cc.CallFunc.create( function() {
			mySprite.state = JSTATUS["STOP"];
		});
		var moveSequence = cc.Sequence.create( moveAction,moveFunc  );
		this.runAction( moveSequence );
	},
	setJewelry:function(_jewelryNo){
		this.initWithFile( this.jewelryPngArray[_jewelryNo] );
		this.jewelryNo = _jewelryNo;
	}
})