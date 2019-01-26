
var QuestLayer = cc.Layer.extend({
    menu:null,
    popup_quest : null,
    quest : new Array(),
    ctor:function () {
        this._super();
        var size = cc.winSize;
        var layer = ccs.csLoader.createNode( res.Quest_Scene );
        this.addChild(layer, 1);
        this.menu = new MenuLayer();
        layer.addChild(this.menu, 2);
        this.popup_quest = layer.getChildByName( "popup_quest" );
        this.popup_quest.visible = false;
        areaNo = playerValue.field;
        for(var i = 0; i < 30; i++){
            //cc.log("quest_"+(i+1)+" "+layer.getChildByName( "quest_"+(i+1) ));
            this.quest[i] = layer.getChildByName( "quest_"+(i+1) );
            var quest_btn = this.quest[i].getChildByName( "quest_btn" );
            quest_btn.userdata = i;
            if( i <= playerValue.field ){
                quest_btn.setBright(true);
                quest_btn.setEnabled(true);
                quest_btn.addTouchEventListener( this.onQuest, this );
            }
        }

        this.scheduleUpdate();
        return true;
    },
    update: function( _dt ) {

    },
    onQuest : function( button, type ){
        if(this.popup_quest.visible == true){
            return;
        }
        if (type == 2){
            playSe( 0 );
            this.popup_quest.visible = true;
            
            var quest_btn = this.popup_quest.getChildByName( "QuestStart_btn" );
            quest_btn.addTouchEventListener( this.onQuestStart, this );
            var Back_btn = this.popup_quest.getChildByName( "Back_btn" );
            Back_btn.addTouchEventListener( this.onBack, this );
            
            var nametext = this.popup_quest.getChildByName( "nametext" );
            nametext.setString( MapData.map[button.userdata].name );
            playerValue.mapid = button.userdata;
        }
    },
    onQuestStart : function( button, type ){
        if (type == 2){
            playSe( 0 );
            cc.director.pushScene( new BattleNode );
            cc.eventManager.removeAllListeners();
            this.removeAllChildren();
        }
    },
    onBack : function( button, type ){
        if (type == 2){
            playSe( 0 );
            this.popup_quest.visible = false;
        }
    }
});

var QuestNode = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new QuestLayer();
        this.addChild(layer);
    }
});

