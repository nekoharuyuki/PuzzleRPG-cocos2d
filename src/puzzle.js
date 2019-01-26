
var puzzleLayer = cc.Layer.extend({
    gridSpriteArray:null,
    jewelrySpriteArray:null,
    jewelryDataArray:null,
    selectJewelry:null,
    checkJewelryWaite:false,
    columNum : 6,
    rowNum : 6,
    _time:0,
    moveCnt:0,
    jewelrySize:50,
    maxJewelry:5,
    jewelryCnt:null,
    removeJewely : 0,
    myturn : true,
    jewelyStack : new Array(),
    turnend : true,
    waitCnt : 0,
    ctor:function () {
        //黄色　回復
        //紫　スリップダメージ、毒　1、２、３
        
        this._super();
        var size = cc.winSize;
        
        this.initTouchEvent();
        this.scheduleUpdate();
        
        this.jewelryCnt = [0,0,0,0,0];
        var offset_x = size.width /2 - this.jewelrySize * this.columNum / 2;
        var offset_y = 12;
        
        this.gridSpriteArray = new Array();
        this.jewelrySpriteArray = new Array();
        this.jewelryDataArray = new Array();
        var colum;
        var row;
        for( colum = 0; colum < this.columNum; colum++ ){
            this.gridSpriteArray[colum] = new Array();
            this.jewelrySpriteArray[colum] = new Array();
            this.jewelryDataArray[colum] = new Array();
            
            for(row = 0; row < this.rowNum; row++ ){
                //ジェリーの配置
                //Math.random()は0以上1未満の乱数なので、 ５倍して切捨てを行うことにより0～4の範囲の整数が得られます。
                var rnd = Math.floor( Math.random() * this.maxJewelry );
                this.jewelrySpriteArray[colum][row] = this.createJewelry( colum,  row, rnd );                
                this.addChild( this.jewelrySpriteArray[colum][row], 1 );
                this.jewelryDataArray[colum][row] = rnd;
            }
        }
        //戦闘開始時にジュエリーの揃いチェックをする場合、コメントを外す
        //this.checkJewelry();
        return true;
    },
    update: function( _dt ) {
        this._time += _dt;
        var isMoved = false;
        if (this.checkJewelryWaite == true){
            
            for (var x = 0; x < this.columNum; ++x) {
                for (var y = 0; y < this.rowNum; ++y) {
                    if (this.jewelrySpriteArray[x][y].state != JSTATUS["STOP"]) {
                        isMoved = true;
                        this.waitCnt = 0;
                    }
                }
            }
            if (!isMoved && this.checkJewelryWaite){
                this.checkJewelryWaite = false;
                this.checkJewelry();
            }
            
        }
        if (!isMoved){
            
            if(this.waitCnt > 3){
                this.turnend = true;
            }else{
                this.waitCnt++;
            }
        }
    },
    getPosition:function( _x, _y){
        var size = cc.winSize;
        var offset_x = size.width /2 - this.jewelrySize * this.columNum / 2;
        var offset_y = 12;
        return  cc.p( offset_x + this.jewelrySize * _x + (this.jewelrySize / 2), offset_y + this.jewelrySize * _y + (this.jewelrySize / 2));
    },
    createJewelry: function( _x, _y, _jewelyType ){
        var jewelry = new jewelrySprite( _jewelyType );
        jewelry.setPosition( this.getPosition( _x, _y ) );
        jewelry.jewelryX = _x;
        jewelry.jewelryY = _y;
        jewelry.jewelryNo = _jewelyType;
        return jewelry;
    },

    initTouchEvent: function(){    
        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.TouchBegan,
            onTouchMoved: this.TouchMoved,
            onTouchEnded: this.TouchEnded,
        })

        cc.eventManager.addListener(touchListener, this);
    },

    TouchBegan: function (touch, event){
        var target = event.getCurrentTarget();
        if(!target.myturn){
            return false;
        }
        if(target.checkJewelryWaite == true){
            return false;
        }

        var location = touch.getLocation();
        var locationInNode = target.convertToNodeSpace( location );    
        for (var y = 0; y < target.rowNum; y++) {
            for (var x = 0; x < target.columNum; x++) {
                var jewelry = target.jewelrySpriteArray[x][y];
                
                if (jewelry == null){
                    continue;
                }
                if(jewelry.state != JSTATUS["STOP"]){
                    continue;
                }
                
                var rect = cc.rect(jewelry.x - (target.jewelrySize / 2), jewelry.y - (target.jewelrySize / 2), jewelry.width, jewelry.height) ;
                if( cc.rectContainsPoint(rect, location) ){
                    target.selectJewelry = jewelry;
                    target.moveCnt = 0;
                    break;
                }
            }
        }
        return true;
    },

    TouchMoved: function (touch, event){    
        var target = event.getCurrentTarget();
        if(!target.myturn){
            return false;
        }

        var location = touch.getLocation();
        if(target.selectJewelry != null){
            if(target.moveCnt == 0){//わざと移動制限を入れる
                target.selectJewelry.setPosition( location );
                for (var y = 0; y < target.rowNum; y++) {
                    for (var x = 0; x < target.columNum; x++) {
                        var jewelry = target.jewelrySpriteArray[x][y];
                        if (jewelry == null){ 
                            continue;
                        }
                        if (jewelry == target.selectJewelry) {
                            continue;
                        }
                        if(jewelry.state != JSTATUS["STOP"]){
                            continue;
                        }
                        var rect = cc.rect(jewelry.x - (target.jewelrySize / 2), jewelry.y - (target.jewelrySize / 2), jewelry.width, jewelry.height) ;
                        if( cc.rectContainsPoint(rect, location) ){
                            // 衝突ジュエリーと座標の入れ替え
                            var _cx = target.selectJewelry.jewelryX;
                            var _cy = target.selectJewelry.jewelryY;
                            
                            target.selectJewelry.jewelryX = jewelry.jewelryX;
                            target.selectJewelry.jewelryY = jewelry.jewelryY;
    
                            var pos = target.getPosition( _cx, _cy);
                            
                            target.jewelrySpriteArray[_cx][_cy] = jewelry;
//                            cc.log("move to"+_cx + ":" + _cy +":" + target.jewelrySpriteArray[_cx][_cy]);
                            target.jewelrySpriteArray[_cx][_cy].jewelryMove( pos.x, pos.y );
                            target.setJewelry( _cx, _cy, jewelry.jewelryNo);
                            //cc.log(_cx + ":" + _cy + ":" + jewelry.jewelryNo);
                            target.moveCnt++;
                            break;
                        }
                    }
                }
            }else{
                target.selectJewelry.setPosition( target.getPosition( target.selectJewelry.jewelryX, target.selectJewelry.jewelryY ) );
            }
        }
    },

    TouchEnded: function (touch, event){
        var target = event.getCurrentTarget();
        if(!target.myturn){
            return false;
        }
        if(target.selectJewelry){
            target.selectJewelry.setPosition( target.getPosition( target.selectJewelry.jewelryX, target.selectJewelry.jewelryY ) );
            target.jewelrySpriteArray[target.selectJewelry.jewelryX][target.selectJewelry.jewelryY] = target.selectJewelry;
            target.setJewelry( target.selectJewelry.jewelryX, target.selectJewelry.jewelryY, target.selectJewelry.jewelryNo);
        }
        target.selectJewelry = null;
        target.checkJewelry();
    },
    checkJewelry:function(){
        var isBroken = false;
        this.turnend = false;
        // 揃っていればブロックを壊す
        // 水平方向から順に垂直をチェック
        var tmpRemoveJewelry = new Array();
        this.removeJewely = 0;
        this.jewelryCnt = [0,0,0,0,0];
        var tmp = 9;
        //縦軸チェック
        for (var x = 0; x < this.columNum; x++) {
            tmp = 9;
            tmpRemoveJewelry = new Array();
            for (var y = 0; y < this.rowNum; y++) {
                if (tmp != this.jewelryDataArray[x][y]){
                    tmpRemoveJewelry = new Array();
                }
                tmp = this.jewelryDataArray[x][y];
                tmpRemoveJewelry.push( this.jewelrySpriteArray[x][y] );
                //cc.log(tmpRemoveJewelry.length );
                if (tmpRemoveJewelry.length == 3){
                    for (var i = 0; i < tmpRemoveJewelry.length; i++ ){
                        if(i == 3){
                            break;
                        }
                        var xx = tmpRemoveJewelry[i].jewelryX;
                        var yy = tmpRemoveJewelry[i].jewelryY;
                        this.jewelrySpriteArray[xx][yy].state = JSTATUS["BROKEN"];
                        isBroken = true;
                    }
                } else if (tmpRemoveJewelry.length > 3){
                    this.jewelrySpriteArray[x][y].state = JSTATUS["BROKEN"];
                    isBroken = true;
                }
            }
        }
        //横軸チェック
        for (var y = 0; y < this.rowNum; y++) {
            tmp = 9;
            tmpRemoveJewelry = new Array();
            for (var x = 0; x < this.columNum; x++) {
                if (tmp != this.jewelryDataArray[x][y]){
                    tmpRemoveJewelry = new Array();
                }
                tmp = this.jewelryDataArray[x][y];
                tmpRemoveJewelry.push( this.jewelrySpriteArray[x][y] );
                if (tmpRemoveJewelry.length == 3){
                    for (var i = 0; i < tmpRemoveJewelry.length; i++ ){
                        if(i == 3){
                            break;
                        }
                        var xx = tmpRemoveJewelry[i].jewelryX;
                        var yy = tmpRemoveJewelry[i].jewelryY;
                        this.jewelrySpriteArray[xx][yy].state = JSTATUS["BROKEN"];
                        isBroken = true;
                    }
                } else  if (tmpRemoveJewelry.length > 3){
                    this.jewelrySpriteArray[x][y].state = JSTATUS["BROKEN"];
                    isBroken = true;
                }
            }
        }
        //消去チェック
        if (isBroken == false){
            this.checkJewelryWaite = false;
            return;
        }
        
        for (var x = 0; x < this.columNum; x++) {
            var tmpJewelry = new Array();
            var brokenJewelry = new Array();
            //ジュエリー消去
            for (var y = 0; y < this.rowNum; y++) {
                if (this.jewelrySpriteArray[x][y].state == JSTATUS["BROKEN"]){ // 壊れたブロックとxyを入れ替えて位置も移動
                    brokenJewelry.push( this.jewelrySpriteArray[x][y] );
                    this.jewelryCnt[this.jewelrySpriteArray[x][y].jewelryNo]++;
                    this.jewelrySpriteArray[x][y] = null;
                } else {
                    tmpJewelry.push( this.jewelrySpriteArray[x][y] );
                    this.jewelrySpriteArray[x][y] = null;
                }
            }
            
            //ジュエリーの移動
            var y = 0;
            for (var i = 0; i < tmpJewelry.length; i++ ){
                if(i == tmpJewelry.length ){
                    break;
                }
                this.jewelrySpriteArray[x][y] = tmpJewelry[i];
                var pos = this.getPosition( x, y );
                this.jewelrySpriteArray[x][y].jewelryMove( pos );
                this.setJewelry( x, y, tmpJewelry[i].jewelryNo );
                y++;
            }
            //空いてる配列に新規のジュエリーを設定
            var tmpY = 0;
            for (var i = 0; i < brokenJewelry.length; i++ ){
                if(i == brokenJewelry.length ){
                    break;
                }
                var rnd = Math.floor( Math.random() * this.maxJewelry );
                this.jewelrySpriteArray[x][y] = brokenJewelry[i];
                this.setJewelry( x, y, rnd );
                this.jewelrySpriteArray[x][y].setPosition( this.getPosition( x, this.rowNum + 1 + tmpY ) );
                var pos = this.getPosition( x, y );
                this.jewelrySpriteArray[x][y].jewelryMove( pos );
                y++;
                tmpY++;
            }
        }
        
        //cc.log("removeJewely"+this.removeJewely);
        //cc.log("jewelryCnt"+this.jewelryCnt);
        this.jewelyStack.push( this.jewelryCnt );
        //cc.log("jewelyStack"+jewelyStack);
        this.checkJewelryWaite = true;
    },
    
    setJewelry:function( _x, _y, _jewelryNo ){
        this.jewelrySpriteArray[_x][_y].setJewelry(_jewelryNo);
        this.jewelrySpriteArray[_x][_y].jewelryNo = _jewelryNo;
        this.jewelrySpriteArray[_x][_y].jewelryX = _x;
        this.jewelrySpriteArray[_x][_y].jewelryY = _y;
        this.jewelryDataArray[_x][_y] = _jewelryNo;
    }
});

var puzzleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new puzzleLayer();
        this.addChild(layer);
    }
});
