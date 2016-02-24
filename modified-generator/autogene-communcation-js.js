/**
 * Created by li.shengze on 2016/2/24.
 */
var fs = require('fs');
function hereDoc(f) {
    return f.toString().replace(/^[^\/]+\/\*!?\s?/, '').replace(/\*\/[^\/]+$/, '');
}
var fileData = hereDoc(function () {
/*var EVENTS = require('./events.json');
var Spi = function(){
    
    this.user = {};    
    
*/});
var jsonContent=require("./package.json");

var tabSpace = ["","    ", "        ", "            ", "                ","                    "];
var beforeRspQryTopCpuInfoTopic=0;
while(jsonContent.FTD.packages[0].package[beforeRspQryTopCpuInfoTopic].$.name!=="RspQryTopCpuInfoTopic"){
    beforeRspQryTopCpuInfoTopic++;
}
var AfterRtnNetNonPartyLinkInfoTopic=0;
while(jsonContent.FTD.packages[0].package[AfterRtnNetNonPartyLinkInfoTopic].$.name!=="RtnNetNonPartyLinkInfoTopic"){
    AfterRtnNetNonPartyLinkInfoTopic++;
}
AfterRtnNetNonPartyLinkInfoTopic++;

for(var i=beforeRspQryTopCpuInfoTopic;i<AfterRtnNetNonPartyLinkInfoTopic;i++){
    var funcName = jsonContent.FTD.packages[0].package[i].$.name;
	var fieldName = jsonContent.FTD.packages[0].package[i].field[0].$.name;
    var funcType = funcName.substring(0,3);
    if(funcType === "Rsp" || funcType === "Rtn"){
        var pValueName = "p" + fieldName;
		var funcCallbackDataName = funcName + "CallbackData\n;";
		fileData += tabSpace[1] + funcCallbackDataName + " = [];\n";
        if (funcType === "Rsp") {
            fileData += tabSpace[1] + "this.On" + funcName + " = function (" + pValueName  + ", pRspInfo, nRequestID, bIsLast) {\n";
        } else {
            fileData += tabSpace[1] + "this.On" + funcName + " = function (" + pValueName + "){ \n";
        }     
		
		fileData += tabSpace[2] + "if ("+ pValueName + "instanceof Object) { \n"
		          + tabSpace[3] + funcCallbackDataName + ".push( " + pValueName +");\n"
				  + tabSpace[2] + "}"
				  
		fileData += tabSpace[2] + "if (true === bIsLast) {\n"
				  + tabSpace[3] + "this.user.socket.emit(" + "EVENTS." + funcName + ", " + funcCallbackDataName + ");\n"
                  + tabSpace[2] + "}\n";
    }
}


var pathName = '../new file/';
var fileName = 'communication.js';
fs.writeFile(pathName + fileName, fileData, function (err) {
    if (err) {
        console.log(err);
    } else {            
        console.log('Succeed in saving ' + pathName + fileName);
    }

});