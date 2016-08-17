var addon    = require("./build/Release/addon");
var structJs = require("./SysUserApiStruct_JS.js");
var fs       = require('fs');
var Spi      = function(){};

var realTimeSystemPath  = "tcp://172.1.128.165:18841";
var innerTestSystemPath = "tcp://172.1.128.111:18842";
var userApi = new addon.FtdcSysUserApi_Wrapper();

 userApi.RegisterFront(realTimeSystemPath);   
// userApi.RegisterFront(innerTestSystemPath);   
userApi.RegisterSpi(new Spi());
userApi.Init();

var loginReqNumbers                   = 1;
var netMonitorReqNumbers              = 0;
var monitorObjectReqNumbers           = 0;
var ReqQrySysUserRegisterTopicNumbers = 0;
var pathName = "result-txt/";
var fileData;
var nRequestID = 1;
var loginField = [];

// for (var i = 0; i < loginReqNumbers; ++i) {
//     loginField[i]           = new structJs.CShfeFtdcReqQrySysUserLoginField();
//     loginField[i].UserID    = "NewUserIDI_" + i;
//     loginField[i].Password  = "1234567";
//     loginField[i].VersionID = "2.0.0.0";   
// }

// loginField[0]           = new structJs.CShfeFtdcReqQrySysUserLoginField();
// loginField[0].UserID    = "admin";
// loginField[0].Password  = "admin";
// loginField[0].VersionID = "2.0.0.0";

    loginField[0]           = new structJs.CShfeFtdcReqQrySysUserLoginField();
    loginField[0].UserID    = "NewUserID_" + 250;
    loginField[0].Password  = "1234567";
    loginField[0].VersionID = "2.0.0.0";   

/*************************************************************  请求登陆 ********************************************************/


/*
NewUserIDE_0-499, 
NewUserIDG_0-499.
NewUserIDI_0-999.

real:

*/
var newRegisterUserNumber = ReqQrySysUserRegisterTopicNumbers;
var SysUserRegisterField  = [];
for (var i = 0; i < newRegisterUserNumber; ++i) {
    SysUserRegisterField[i]                 = new structJs.CShfeFtdcReqQrySysUserRegisterField;
    SysUserRegisterField[i].UserID          = "NewUserID_" + i;
    SysUserRegisterField[i].UserName        = "NewUserName_" + i;
    SysUserRegisterField[i].UserInfo        = "Man";
    SysUserRegisterField[i].Password        = "1234567";
    SysUserRegisterField[i].Privilege       = 63;
    SysUserRegisterField[i].EMail           = "932658921@qq.com ";
    SysUserRegisterField[i].EMailFlag       = 1;
    SysUserRegisterField[i].HomePhone       = "15151803379 ";
    SysUserRegisterField[i].HomePhoneFlag   = 1;
    SysUserRegisterField[i].MobilePhone     = "051584106623 ";
    SysUserRegisterField[i].MobilePhoneFlag = 1;   
}

Spi.prototype.OnFrontConnected = function() {
	
    console.log('\n++++++++++++ JS FrontConnected START! +++++++++++++');    
        
	for (var i = 0; i < loginReqNumbers; ++i) {        
        
       console.log("ReqQrySysUserLoginTopic "+ i + "  result:" 
                        + userApi.ReqQrySysUserLoginTopic(loginField[i], 1) + "\n");			
	}	    	
                
    console.log('++++++++++++ JS FrontConnected END! +++++++++++++\n'); 
}

/***********************************************************************************************************/
var ReqQrySysUserLoginTopicCallbackData = [];
var rspQrySysUserLoginTopicCalledTime   = 0;
var SysUserLoginTopicfileName           = "OnRspQrySysUserLoginTopic-JS-Test-CallbackData.txt";
var SysUserLoginTopicStringData         = "";
Spi.prototype.OnRspQrySysUserLoginTopic = function(pRspQrySysUserLogin,pRspInfo,nRequestID,bIsLast)
{
        var outputStr = "";
        outputStr += "\n++++++++++++++++ JS OnRspQrySysUserLoginTopic: START! ++++++++++++++++++\n";
        // outputStr += '\n>>>>>>>>>>>>>>>>>>>>>> JS pid: ' + process.pid.toString() + ' <<<<<<<<<<<<<<<<<<<\n';
		if (pRspQrySysUserLogin instanceof Object) {
            outputStr += "LoginTime :                 " + pRspQrySysUserLogin.LoginTime.toString() + "\n"
			           + "UserID :                    " + pRspQrySysUserLogin.UserID.toString() + "\n"
			           + "Privilege :                 " + pRspQrySysUserLogin.Privilege.toString() + "\n"
			           + "TradingDay :                " + pRspQrySysUserLogin.TradingDay.toString() + "\n"
			           + "VersionFlag :               " + pRspQrySysUserLogin.VersionFlag.toString() + "\n"	
			           + "SysUserLoginCalledTime :    " + rspQrySysUserLoginTopicCalledTime.toString() + "\n";	
			
			ReqQrySysUserLoginTopicCallbackData.push(pRspQrySysUserLogin);
		} else {
            outputStr += "pRspQrySysUserLogin is NULL!\n";
        }
		rspQrySysUserLoginTopicCalledTime++;
        outputStr += "bIsLastNew :               " + bIsLast + "\n";
        outputStr += "++++++++++++++++ JS OnRspQrySysUserLoginTopic: END! ++++++++++++++++++" + "\n"
        console.log(outputStr);
        
        SysUserLoginTopicStringData += outputStr;
        
        for (var i = 0; i < netMonitorReqNumbers; ++i) {	
            console.log("NetMonitorAttrScopeTopic:  "+i.toString() +" result:" + 
            userApi.ReqQryNetMonitorAttrScopeTopic (netMonitorAttrerScopeField, nRequestID) + "\n");
        }
    
        for (var i = 0; i < monitorObjectReqNumbers; ++i) {	
            console.log("MonitorObjectTopic:  "+i.toString() +" result:" + 
            userApi.ReqQryMonitorObjectTopic (monitorObjectField, nRequestID) + "\n");
        }
        
        for (var i = 0; i < ReqQrySysUserRegisterTopicNumbers; ++i) {            
            console.log("ReqQrySysUserRegisterTopic " + i.toString() +" result:" + 
            userApi.ReqQrySysUserRegisterTopic (SysUserRegisterField[i], 1) + "\n");
        }
        	
		if (true === bIsLast) {
			fs.writeFile(pathName + SysUserLoginTopicfileName, SysUserLoginTopicStringData, function(err) {
				if (err) {
					console.log(err);
				} else {
					console.log('Succeed in saving ' + pathName + SysUserLoginTopicfileName);
				}	
			});						
			ReqQrySysUserLoginTopicCallbackData = [];		
		}
}


/*****************************************************************************************************/
var OnRspQrySysUserRegisterTopicStringData = "";
var OnRspQrySysUserRegisterTopicFileData   = [];
var OnRspQrySysUserRegisterTopicCallTime   = 0;
Spi.prototype.OnRspQrySysUserRegisterTopic = function (pRspQrySysUserRegister, pRspInfo, nRequestID, bIsLast) {
    var tmpStr = "\n************ JS::OnRspQrySysUserRegisterTopic: START! ***********\n";    
    
    if (pRspQrySysUserRegister instanceof Object) {
        tmpStr += "UserID:                               " + pRspQrySysUserRegister.UserID.toString() + "\n"
                + "Privilege:                            " + pRspQrySysUserRegister.Privilege.toString() + "\n";
    } else {
        tmpStr += "pRspQrySysUserRegister is NULL!\n";    
    }
    
    tmpStr += "bIsLast in JS is:                     " + bIsLast.toString() + "\n";
	tmpStr += "OnRspQrySysUserRegisterTopicCallTime: " + OnRspQrySysUserRegisterTopicCallTime.toString() + "\n";
    tmpStr += "************ JS::OnRspQrySysUserRegisterTopic: END! ***********\n"
    
    console.log(tmpStr);
    
    OnRspQrySysUserRegisterTopicStringData += tmpStr;
    OnRspQrySysUserRegisterTopicCallTime++;
    
    if (true === bIsLast) {
		var fileName = "OnRspQrySysUserRegisterTopic-Test-CallbackData.txt";
		fs.writeFile(pathName + fileName, OnRspQrySysUserRegisterTopicStringData, function(err) {
				if (err) {
					console.log(err);
				} else {
					// console.log('Succeed in saving ' + pathName + fileName);
				}	
		});
		OnRspQrySysUserRegisterTopicStringData = "";					
	}
    
}

/************************************************ NetMonitorAttr *************************************************/ 
var netMonitorAttrerScopeField           = new structJs.CShfeFtdcReqQryNetMonitorAttrScopeField;
netMonitorAttrerScopeField.OperationType = 0;
netMonitorAttrerScopeField.ID            = 0;
netMonitorAttrerScopeField.CName         = " ";
netMonitorAttrerScopeField.EName         = " ";
netMonitorAttrerScopeField.Comments      = " ";

var netMonitorReqCalledTime              = 0;
var rspQryNetMonitorAttrScopeTopicFileData = "";

Spi.prototype.OnRspQryNetMonitorAttrScopeTopic = function (pRspQryNetMonitorAttrScope, pRspInfo, nRequestID, bIsLast) {
	
	var tmpStr = "\n************ JS::RspNetMonitorAttrScopeTopic: START! ***********\n";
	
	if (pRspQryNetMonitorAttrScope instanceof Object) {		
		      tmpStr += "OperationType in JS is:  " + pRspQryNetMonitorAttrScope.OperationType.toString() + "\n" + 
			            "ID in JS is:             " + pRspQryNetMonitorAttrScope.ID.toString() + "\n" + 
						"CName in JS is:          " + pRspQryNetMonitorAttrScope.CName.toString() + "\n" + 
						"EName in JS is:          " + pRspQryNetMonitorAttrScope.EName.toString() + "\n" + 
						"Comments in JS is:       " + pRspQryNetMonitorAttrScope.Comments.toString() + "\n";					
											
	} else {
		tmpStr += "pRspQryNetMonitorAttrScope  is NULL;\n";
	}
				
	tmpStr += "bIsLast in JS is:        " + bIsLast.toString() + "\n";
	tmpStr += "JS-netMonitorReqCalledTime: " + netMonitorReqCalledTime.toString() + "\n";
	tmpStr += "************ JS::RspNetMonitorAttrScopeTopic: END! *********** \n";
    
    rspQryNetMonitorAttrScopeTopicFileData += tmpStr;
    
    console.log(tmpStr);
    
	if (true === bIsLast) {
		var fileName = "OnRspQryNetMonitorAttrScopeTopic-Test-CallbackData.txt";
		fs.writeFile(pathName + fileName, rspQryNetMonitorAttrScopeTopicFileData, function(err) {
				if (err) {
					console.log(err);
				} else {
					console.log('Succeed in saving ' + pathName + fileName);
				}	
		});
		rspQryNetMonitorAttrScopeTopicFileData = "";					
	}
		
}
	


/*************************************    ReqQryMonitorObjectTopic   **************************************/

var monitorObjectCalledTime  = 0;
var rspMonitorObjectStringData = "";

Spi.prototype.OnRspQryMonitorObjectTopic = function (pRspQryMonitorObject, pRspInfo, nRequestID, bIsLast) {
	var tmpStr = "";
    tmpStr += "\n************ JS::OnRspQryMonitorObjectTopic: START! ***********\n";	
	if (pRspQryMonitorObject instanceof Object) {		
		tmpStr += "ObjectID :               " + pRspQryMonitorObject.ObjectID.toString() + "\n" + 
			      "ObjectName :             " + pRspQryMonitorObject.ObjectName.toString() + "\n" + 
				  "WarningActive :          " + pRspQryMonitorObject.WarningActive.toString() + "\n";							
											
	} else {
		tmpStr += "pRspQryMonitorObject is NULL;\n";
	}
	
    tmpStr += "bIsLast:                 " + bIsLast.toString() + "\n";
    tmpStr += "MonitorObjectCalledTime: " + monitorObjectCalledTime.toString() + "\n";
    tmpStr += "************ JS::OnRspQryMonitorObjectTopic: END! *********** \n";
    rspMonitorObjectStringData += tmpStr;	
    
    monitorObjectCalledTime++;
    
    console.log(tmpStr);
    
	if (true === bIsLast) {
		var fileName = "OnRspQryMonitorObjectTopic-Test-CallbackData.txt";
		fs.writeFile(pathName + fileName, rspMonitorObjectStringData, function(err) {
				if (err) {
					console.log(err);
				} else {
					console.log('Succeed in saving ' + pathName + fileName);
				}	
		});
		rspMonitorObjectStringData = "";					
	}	
}

var OutputMessage = function (varName, varData,  fileData) {		
	console.log(varName + varData.toString());
}

function sleep(sleepTime) {
       for(var start = Date.now(); Date.now() - start <= sleepTime; ) { } 
}

process.on('beforeExit', function (code) {
	console.log('Nodejs, beforeExit: ' + code.toString());
});

process.on('exit', function (code) {
	console.log('Nodejs, exit: ' + code.toString());
});
