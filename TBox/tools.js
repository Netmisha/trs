function md5(){
  var l='length',
  h=[
   '0123456789abcdef',0x0F,0x80,0xFFFF,
    0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476
  ],
  x=[
    [0,1,[7,12,17,22]],
    [1,5,[5, 9,14,20]],
    [5,3,[4,11,16,23]],
    [0,7,[6,10,15,21]]
  ],
  A=function(x,y,z){
    return(((x>>16)+(y>>16)+((z=(x&h[3])+(y&h[3]))>>16))<<16)|(z&h[3])
  },
  B=function(s){
    var n=((s[l]+8)>>6)+1,b=new Array(1+n*16).join('0').split('');
    for(var i=0;i<s[l];i++)b[i>>2]|=s.charCodeAt(i)<<((i%4)*8);
    return(b[i>>2]|=h[2]<<((i%4)*8),b[n*16-2]=s[l]*8,b)
  },
  R=function(n,c){return(n<<c)|(n>>>(32-c))},
  C=function(q,a,b,x,s,t){return A(R(A(A(a,q),A(x,t)),s),b)},
  F=function(a,b,c,d,x,s,t){return C((b&c)|((~b)&d),a,b,x,s,t)},
  G=function(a,b,c,d,x,s,t){return C((b&d)|(c&(~d)),a,b,x,s,t)},
  H=function(a,b,c,d,x,s,t){return C(b^c^d,a,b,x,s,t)},
  I=function(a,b,c,d,x,s,t){return C(c^(b|(~d)),a,b,x,s,t)},
  _=[F,G,H,I],
  S=(function(){
    with(Math)for(var i=0,a=[],x=pow(2,32);i<64;a[i]=floor(abs(sin(++i))*x));
    return a
  })(),
  X=function (n){
    for(var j=0,s='';j<4;j++)
      s+=h[0].charAt((n>>(j*8+4))&h[1])+h[0].charAt((n>>(j*8))&h[1]);
    return s
  };
  return function(s){
    var $=B(''+s),a=[0,1,2,3],b=[0,3,2,1],v=[h[4],h[5],h[6],h[7]];
    for(var i,j,k,N=0,J=0,o=[].concat(v);N<$[l];N+=16,o=[].concat(v),J=0){
      for(i=0;i<4;i++)
        for(j=0;j<4;j++)
          for(k=0;k<4;k++,a.unshift(a.pop()))
            v[b[k]]=_[i](
              v[a[0]],
              v[a[1]],
              v[a[2]],
              v[a[3]],
              $[N+(((j*4+k)*x[i][1]+x[i][0])%16)],
              x[i][2][k],
              S[J++]
            );
      for(i=0;i<4;i++)
        v[i]=A(v[i],o[i]);
    };return X(v[0])+X(v[1])+X(v[2])+X(v[3]);
}};

function hash(data) {
    return md5()(data);
}

function getHash(obj){
  var strObj = JSON.stringify(obj);
  console.log("strObj: "+strObj);
  strObj = strObj.replace(/\.[A-Z0-9]{25}/g, '');
  console.log("strObj: "+strObj);
  return hash(strObj);
};

function getTicCount(){
  return (new Date()).getTime();
};
function FAIL(msg) {
    Test.FAIL(msg);
    throw "FAIL";
}
function SUCCESS(msg) {
    Test.SUCCESS(msg);
    throw "SUCCESS";
}

////////////////////////////////////////////////
NB.document.executeCommand = function (command, args) {

    var jsonData = { "command": command, "args": args };

    NB.ajaxNew('POST', 'document/executeCommand', jsonData)
            .fail(function (data) {
                throw (data);
            });
};
////////////////////////////////////////////////////

NB.ui.mainMenu = function() {
    var data = [];

    var _success = function(param) {
        data = param;
    };

    NB.ajax("GET", "ui/mainmenu", null, _success);
    return data;
};

function CMainMenu(){};

    var ResetID = 0;
    var MenuObject = NB.ui.mainMenu().replace(/\t/g,' ').replace(/\\/g," ");

    for( var i = 0;i < MenuObject.length; i++) {
        MenuObject = MenuObject.replace("-1", ResetID);
        ++ResetID;
    }

    CMainMenu.prototype = JSON.parse(MenuObject);

    CMainMenu.prototype.menu = function(ID) {
        for(var item in this.MainMenu) {
            var sumMenu = this.MainMenu[item];
                if(sumMenu.ID == ID) {
                    var resultItem = Object.create(MainMenu.prototype);console.log("result",resultItem);
                    resultItem.MainMenu = sumMenu;console.log(resultItem);
                    return resultItem;
                }
        }
    }

    CMainMenu.prototype.update = function() {
        ResetID = 0;
        var getUpdatedCoord = NB.ui.mainMenu().replace(/\t/g,' ').replace(/\\/g," ");
        for( var i = 0;i < getUpdatedCoord.length; i++) {
            getUpdatedCoord = getUpdatedCoord.replace("-1", ResetID);
            ++ResetID;
        };
        var newData = JSON.parse(getUpdatedCoord);
        CMainMenu.prototype.MainMenu = newData.MainMenu;
    }

    var getInfo = function(menuID,subMenu) {
        var currentMenu;
             if(subMenu !== undefined) {
                 currentMenu = subMenu;
             }
             else {
                 currentMenu = CMainMenu.prototype.MainMenu;
             }
        for(var item in currentMenu) {
            var subMenu = currentMenu[item];
            if(subMenu !== undefined ) {
                if(subMenu.ID !== undefined) {
                    if(subMenu.ID == menuID) {
                        return subMenu;
                    }
                    else {
                        var retVal = getInfo(menuID,subMenu);
                        if(retVal !== undefined) {
                            return retVal;
                        }
                    }
                }
            }
            else {
                return;
            }
        }
    }
    CMainMenu.prototype.click = function(menuId) {console.log(this);
        this.update();
        var currentMenu = getInfo(menuId);
        console.log("clickCurrentMenu", currentMenu.rect["x"]);
        Box.SetMousePos(parseInt(currentMenu.rect["x"]) + parseInt(currentMenu.rect["width"])/2, parseInt(currentMenu.rect["y"])+parseInt(currentMenu.rect["height"]/2));
        Box.MouseClick(0);
   }
    var MainMenu = new CMainMenu();




    NB.ui.GetRootMenuObject = function() {
        return MainMenu.prototype;
    }

    NB.ui.GetUpdatedMenu = function(){console.log("ENTER");
        var res = NB.ui.mainMenu().replace(/\t/g,' ');
        MainMenu.prototype = JSON.parse(res);
        return MainMenu.prototype;
    }

    NB.ui.ClickOnMenuItem = function(MenuItem) {

        click(MenuItem["MainMenu"]);
        console.log("=============================================================================");
        ObjArray.reverse();
        console.log(ObjArray);
        var retVal = ObjArray;
        ObjArray = [];
        return retVal;
    }


function CToolBar () {};
CToolBar.prototype.PrevPage = function(){  NB.document.executeCommand("com.smarttech.feature.page_navigator.previous", {"command_id" : "previous", "feature_id":"com.smarttech.feature.page_navigator"});}
CToolBar.prototype.NextPage = function(){  NB.document.executeCommand("com.smarttech.feature.page_navigator.next", {"command_id" : "next", "feature_id":"com.smarttech.feature.page_navigator"});}
CToolBar.prototype.Undo = function(){  NB.document.executeCommand("com.smarttech.feature.undo", {"feature_id":"com.smarttech.feature.undo"});}
CToolBar.prototype.Redo = function(){  NB.document.executeCommand("com.smarttech.feature.redo", {"feature_id":"com.smarttech.feature.redo"});}
CToolBar.prototype.AddPage = function(){  NB.document.executeCommand("com.smarttech.feature.document.insert_page", {"command_id" : "insert_page", "feature_id":"com.smarttech.feature.document"});}
CToolBar.prototype.DelPage = function(){  NB.document.executeCommand("com.smarttech.feature.document.delete_page", {"command_id" : "delete_page", "feature_id":"com.smarttech.feature.document"});}
CToolBar.prototype.OpenFile = function(){  NB.document.executeCommand("com.smarttech.feature.document.open", {"command_id" : "open", "feature_id":"com.smarttech.feature.document"});}
CToolBar.prototype.Save = function(){  NB.document.executeCommand("com.smarttech.feature.document.save", {"command_id" : "save", "feature_id":"com.smarttech.feature.document"});}
CToolBar.prototype.Delete = function(){  NB.document.executeCommand("com.smarttech.feature.object.delete", {"command_id" : "delete", "feature_id":"com.smarttech.feature.object"});}
CToolBar.prototype.ScrShade = function(){  NB.document.executeCommand("com.smarttech.feature.screenshade", {"feature_id":"com.smarttech.feature.screenshade"});}
CToolBar.prototype.Table = function(){  NB.document.executeCommand("com.smarttech.feature.popup.dismiss", {"command_id" : "launch", "feature_id":"com.smarttech.feature.table"});}
CToolBar.prototype.MeasurTools = function(){  NB.document.executeCommand("com.smarttech.feature.popup.dismiss", {"command_id" : "group", "feature_id":"com.smarttech.feature.measurementtools"});}
CToolBar.prototype.ViewScr = function(){  NB.document.executeCommand("com.smarttech.feature.popup.dismiss", {"command_id" : "group", "feature_id":"com.smarttech.feature.view"});}
CToolBar.prototype.Response = function(){  NB.document.executeCommand("com.smarttech.feature.external.response2", {"command_id" : "response2", "feature_id":"com.smarttech.feature.external"});}
CToolBar.prototype.Lab = function(){  NB.document.executeCommand("com.smarttech.feature.external.lab", {"command_id" : "lab", "feature_id":"com.smarttech.feature.external"});}
CToolBar.prototype.MathBtn = function(){  NB.document.executeCommand("com.math.feature.math_slideout_toggle", {"command_id" : "math_slideout_toggle", "feature_id":"com.math.feature"});}
CToolBar.prototype.AddOns = function(){  NB.document.executeCommand("com.smarttech.feature.addons.toggleAddons", {"command_id" : "toggleAddons", "feature_id":"com.smarttech.feature.addons"});}
CToolBar.prototype.Select = function(){  NB.document.executeCommand("com.smarttech.feature.selection", {"feature_id":"com.smarttech.feature.selection"});}
CToolBar.prototype.Pens = function(){  NB.document.executeCommand("com.smarttech.feature.pens.pentool", {"command_id" : "pentool", "feature_id":"com.smarttech.feature.pens"});}
CToolBar.prototype.Shapes = function(){  NB.document.executeCommand("com.smarttech.feature.shape", {"feature_id":"com.smarttech.feature.shape"});}
CToolBar.prototype.Text = function(){  NB.document.executeCommand("com.smarttech.feature.text", {"feature_id":"com.smarttech.feature.text"});}
CToolBar.prototype.RegPolygons = function(){  NB.document.executeCommand("com.smarttech.feature.polygons", {"feature_id":"com.smarttech.feature.polygons"});}
CToolBar.prototype.Lines = function(){  NB.document.executeCommand("com.smarttech.feature.line", {"feature_id":"com.smarttech.feature.line"});}
CToolBar.prototype.Fill = function(){  NB.document.executeCommand("com.smarttech.feature.fill", {"feature_id":"com.smarttech.feature.fill"});}
CToolBar.prototype.Eraser = function(){  NB.document.executeCommand("com.smarttech.feature.eraser", {"feature_id":"com.smarttech.feature.eraser"});}
CToolBar.prototype.PenLine0 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_0", {"command_id" : "pen_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine1 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_1", {"command_id" : "pen_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine2 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_2", {"command_id" : "pen_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine3 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_3", {"command_id" : "pen_command_3", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine4 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_4", {"command_id" : "pen_command_4", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine5 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_5", {"command_id" : "pen_command_5", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine6 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_6", {"command_id" : "pen_command_6", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.PenLine7 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.pen_command_7", {"command_id" : "pen_command_7", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.AlignBottom = function(){  NB.document.executeCommand("com.smarttech.feature.addons.com###DOT###smarttech###DOT###addon###DOT###alignment_alignBottom", {"command_id" : "com###DOT###smarttech###DOT###addon###DOT###alignment_alignBottom", "feature_id":"com.smarttech.feature.addons"});}
CToolBar.prototype.AlignTop = function(){  NB.document.executeCommand("com.smarttech.feature.addons.com###DOT###smarttech###DOT###addon###DOT###alignment_alignTop", {"command_id" : "com###DOT###smarttech###DOT###addon###DOT###alignment_alignTop", "feature_id":"com.smarttech.feature.addons"});}
CToolBar.prototype.AlignLeft = function(){  NB.document.executeCommand("com.smarttech.feature.addons.com###DOT###smarttech###DOT###addon###DOT###alignment_alignLeft", {"command_id" : "com###DOT###smarttech###DOT###addon###DOT###alignment_alignLeft", "feature_id":"com.smarttech.feature.addons"});}
CToolBar.prototype.AlignRight = function(){  NB.document.executeCommand("com.smarttech.feature.addons.com###DOT###smarttech###DOT###addon###DOT###alignment_alignRight", {"command_id" : "com###DOT###smarttech###DOT###addon###DOT###alignment_alignRight", "feature_id":"com.smarttech.feature.addons"});}
CToolBar.prototype.SmallEraser = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.eraser_command_0", {"command_id" : "eraser_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.MediumEraser = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.eraser_command_1", {"command_id" : "eraser_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.LargeEraser = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.eraser_command_2", {"command_id" : "eraser_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType0 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_0", {"command_id" : "shape_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType1 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_1", {"command_id" : "shape_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType2 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_2", {"command_id" : "shape_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType3 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_3", {"command_id" : "shape_command_3", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType4 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_4", {"command_id" : "shape_command_4", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType5 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_5", {"command_id" : "shape_command_5", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType6 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_6", {"command_id" : "shape_command_6", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType7 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_7", {"command_id" : "shape_command_7", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType8 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_8", {"command_id" : "shape_command_8", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType9 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_9", {"command_id" : "shape_command_9", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType10 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_10", {"command_id" : "shape_command_10", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType11 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_11", {"command_id" : "shape_command_11", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType12 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_12", {"command_id" : "shape_command_12", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType13 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_13", {"command_id" : "shape_command_13", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType14 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_14", {"command_id" : "shape_command_14", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType15 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_15", {"command_id" : "shape_command_15", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType16 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_16", {"command_id" : "shape_command_16", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType17 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_17", {"command_id" : "shape_command_17", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType18 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_18", {"command_id" : "shape_command_18", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType19 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_19", {"command_id" : "shape_command_19", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType20 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_20", {"command_id" : "shape_command_20", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.ShapesType21 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.shape_command_21", {"command_id" : "shape_command_21", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType0 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_0", {"command_id" : "text_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType1 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_1", {"command_id" : "text_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType2 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_2", {"command_id" : "text_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType3 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_3", {"command_id" : "text_command_3", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType4 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_4", {"command_id" : "text_command_4", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.TextType5 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.text_command_5", {"command_id" : "text_command_5", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon0 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_0", {"command_id" : "polygon_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon1 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_1", {"command_id" : "polygon_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon2 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_2", {"command_id" : "polygon_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon3 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_3", {"command_id" : "polygon_command_3", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon4 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_4", {"command_id" : "polygon_command_4", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon5 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_5", {"command_id" : "polygon_command_5", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon6 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_6", {"command_id" : "polygon_command_6", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon7 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_7", {"command_id" : "polygon_command_7", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon8 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_8", {"command_id" : "polygon_command_8", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Polygon9 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.polygon_command_9", {"command_id" : "polygon_command_9", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line0 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_0", {"command_id" : "line_command_0", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line1 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_1", {"command_id" : "line_command_1", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line2 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_2", {"command_id" : "line_command_2", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line3 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_3", {"command_id" : "line_command_3", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line4 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_4", {"command_id" : "line_command_4", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line5 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_5", {"command_id" : "line_command_5", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line6 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_6", {"command_id" : "line_command_6", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line7 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_7", {"command_id" : "line_command_7", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line8 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_8", {"command_id" : "line_command_8", "feature_id":"com.smarttech.feature.tools.presets"});}
CToolBar.prototype.Line9 = function(){  NB.document.executeCommand("com.smarttech.feature.tools.presets.line_command_9", {"command_id" : "line_command_9", "feature_id":"com.smarttech.feature.tools.presets"});}
var ToolBar = new CToolBar();
