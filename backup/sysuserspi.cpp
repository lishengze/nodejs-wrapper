#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory.h>
#include "sysuserspi.h"
#include "v8-transform-data.h"
#include "tool-function.h"
#include <fstream>
#include <queue>
#include <map>
#include <vector>
using std::queue;
using std::map;
using std::vector;
using std::fstream;
using std::cin;
using std::cout;
using std::endl;
 
extern fstream g_RunningResult_File;

void SysUserSpi::OnFrontConnected( ){ 
    OutputCallbackMessage("\n****** SysUserSpi:: FrontConnected: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: FrontConnected: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[1];
    if (NULL == paramArray) {

    paramArray[0] = (void*)pSpiObj;

    uv_mutex_lock (&g_FrontConnected_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_FrontConnected_IOUser_vec.begin();
        it != g_FrontConnected_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_FrontConnected_IOUser_vec.end()) {
        g_FrontConnected_IOUser_vec.push_back(this->m_frontid);
    }
    g_FrontConnected_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_FrontConnected_mutex);

    uv_async_send(&g_FrontConnected_async);
    OutputCallbackMessage("****** SysUserSpi:: FrontConnected: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnFrontDisconnected(int nReason){ 
    OutputCallbackMessage("\n****** SysUserSpi:: FrontDisconnected: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: FrontDisconnected: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    int* pNewnReason = NULL;
    if (NULL != nReason) { 
        pNewnReason = new int;
        if (NULL == pNewnReason) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewnReason", g_RunningResult_File);
            return;
        }
        memcpy (pNewnReason, &nReason, sizeof(int));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewnReason;
    if (NULL == nReason) { 
        OutputCallbackMessage("SysUserSpi::nReason is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("nReason:", nReason, g_RunningResult_File);
    }

    uv_mutex_lock (&g_FrontDisconnected_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_FrontDisconnected_IOUser_vec.begin();
        it != g_FrontDisconnected_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_FrontDisconnected_IOUser_vec.end()) {
        g_FrontDisconnected_IOUser_vec.push_back(this->m_frontid);
    }
    g_FrontDisconnected_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_FrontDisconnected_mutex);

    uv_async_send(&g_FrontDisconnected_async);
    OutputCallbackMessage("****** SysUserSpi:: FrontDisconnected: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnHeartBeatWarning(int nTimeLapse){ 
    OutputCallbackMessage("\n****** SysUserSpi:: HeartBeatWarning: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: HeartBeatWarning: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    int* pNewnTimeLapse = NULL;
    if (NULL != nTimeLapse) { 
        pNewnTimeLapse = new int;
        if (NULL == pNewnTimeLapse) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewnTimeLapse", g_RunningResult_File);
            return;
        }
        memcpy (pNewnTimeLapse, &nTimeLapse, sizeof(int));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewnTimeLapse;
    if (NULL == nTimeLapse) { 
        OutputCallbackMessage("SysUserSpi::nTimeLapse is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("nTimeLapse:", nTimeLapse, g_RunningResult_File);
    }

    uv_mutex_lock (&g_HeartBeatWarning_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_HeartBeatWarning_IOUser_vec.begin();
        it != g_HeartBeatWarning_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_HeartBeatWarning_IOUser_vec.end()) {
        g_HeartBeatWarning_IOUser_vec.push_back(this->m_frontid);
    }
    g_HeartBeatWarning_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_HeartBeatWarning_mutex);

    uv_async_send(&g_HeartBeatWarning_async);
    OutputCallbackMessage("****** SysUserSpi:: HeartBeatWarning: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTopCpuInfoTopic(CShfeFtdcRspQryTopCpuInfoField* pRspQryTopCpuInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTopCpuInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTopCpuInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTopCpuInfoField* pNewRspQryTopCpuInfo = NULL;
    if (NULL != pRspQryTopCpuInfo) { 
        pNewRspQryTopCpuInfo = new CShfeFtdcRspQryTopCpuInfoField;
        if (NULL == pNewRspQryTopCpuInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTopCpuInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTopCpuInfo,pRspQryTopCpuInfo, sizeof(CShfeFtdcRspQryTopCpuInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTopCpuInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTopCpuInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTopCpuInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTopCpuInfo->HostName: ", pRspQryTopCpuInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->MonDate: ", pRspQryTopCpuInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->MonTime: ", pRspQryTopCpuInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->CPU: ", pRspQryTopCpuInfo->CPU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->LOAD: ", pRspQryTopCpuInfo->LOAD, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->USER: ", pRspQryTopCpuInfo->USER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->NICE: ", pRspQryTopCpuInfo->NICE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->SYS: ", pRspQryTopCpuInfo->SYS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->IDLE: ", pRspQryTopCpuInfo->IDLE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->BLOCK: ", pRspQryTopCpuInfo->BLOCK, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->SWAIT: ", pRspQryTopCpuInfo->SWAIT, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->INTR: ", pRspQryTopCpuInfo->INTR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopCpuInfo->SSYS: ", pRspQryTopCpuInfo->SSYS, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTopCpuInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTopCpuInfoTopic_IOUser_vec.begin();
        it != g_RspQryTopCpuInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTopCpuInfoTopic_IOUser_vec.end()) {
        g_RspQryTopCpuInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTopCpuInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTopCpuInfoTopic_mutex);

    uv_async_send(&g_RspQryTopCpuInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTopCpuInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTopCpuInfoTopic(CShfeFtdcRtnTopCpuInfoField* pRtnTopCpuInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTopCpuInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTopCpuInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTopCpuInfoField* pNewRtnTopCpuInfo = NULL;
    if (NULL != pRtnTopCpuInfo) { 
        pNewRtnTopCpuInfo = new CShfeFtdcRtnTopCpuInfoField;
        if (NULL == pNewRtnTopCpuInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTopCpuInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTopCpuInfo,pRtnTopCpuInfo, sizeof(CShfeFtdcRtnTopCpuInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTopCpuInfo;
    if (NULL == pRtnTopCpuInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnTopCpuInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTopCpuInfo->HostName: ", pRtnTopCpuInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->MonDate: ", pRtnTopCpuInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->MonTime: ", pRtnTopCpuInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->CPU: ", pRtnTopCpuInfo->CPU, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->LOAD: ", pRtnTopCpuInfo->LOAD, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->USER: ", pRtnTopCpuInfo->USER, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->NICE: ", pRtnTopCpuInfo->NICE, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->SYS: ", pRtnTopCpuInfo->SYS, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->IDLE: ", pRtnTopCpuInfo->IDLE, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->BLOCK: ", pRtnTopCpuInfo->BLOCK, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->SWAIT: ", pRtnTopCpuInfo->SWAIT, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->INTR: ", pRtnTopCpuInfo->INTR, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopCpuInfo->SSYS: ", pRtnTopCpuInfo->SSYS, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTopCpuInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTopCpuInfoTopic_IOUser_vec.begin();
        it != g_RtnTopCpuInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTopCpuInfoTopic_IOUser_vec.end()) {
        g_RtnTopCpuInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTopCpuInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTopCpuInfoTopic_mutex);

    uv_async_send(&g_RtnTopCpuInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTopCpuInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTopMemInfoTopic(CShfeFtdcRspQryTopMemInfoField* pRspQryTopMemInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTopMemInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTopMemInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTopMemInfoField* pNewRspQryTopMemInfo = NULL;
    if (NULL != pRspQryTopMemInfo) { 
        pNewRspQryTopMemInfo = new CShfeFtdcRspQryTopMemInfoField;
        if (NULL == pNewRspQryTopMemInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTopMemInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTopMemInfo,pRspQryTopMemInfo, sizeof(CShfeFtdcRspQryTopMemInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTopMemInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTopMemInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTopMemInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTopMemInfo->HostName: ", pRspQryTopMemInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->MonDate: ", pRspQryTopMemInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->MonTime: ", pRspQryTopMemInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->TOTALREAL: ", pRspQryTopMemInfo->TOTALREAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->ACTIVEREAL: ", pRspQryTopMemInfo->ACTIVEREAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->TOTALVIRTUAL: ", pRspQryTopMemInfo->TOTALVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->ACTIVEVIRTUAL: ", pRspQryTopMemInfo->ACTIVEVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopMemInfo->FREE: ", pRspQryTopMemInfo->FREE, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTopMemInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTopMemInfoTopic_IOUser_vec.begin();
        it != g_RspQryTopMemInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTopMemInfoTopic_IOUser_vec.end()) {
        g_RspQryTopMemInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTopMemInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTopMemInfoTopic_mutex);

    uv_async_send(&g_RspQryTopMemInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTopMemInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTopMemInfoTopic(CShfeFtdcRtnTopMemInfoField* pRtnTopMemInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTopMemInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTopMemInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTopMemInfoField* pNewRtnTopMemInfo = NULL;
    if (NULL != pRtnTopMemInfo) { 
        pNewRtnTopMemInfo = new CShfeFtdcRtnTopMemInfoField;
        if (NULL == pNewRtnTopMemInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTopMemInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTopMemInfo,pRtnTopMemInfo, sizeof(CShfeFtdcRtnTopMemInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTopMemInfo;
    if (NULL == pRtnTopMemInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnTopMemInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTopMemInfo->HostName: ", pRtnTopMemInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->MonDate: ", pRtnTopMemInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->MonTime: ", pRtnTopMemInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->TOTALREAL: ", pRtnTopMemInfo->TOTALREAL, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->ACTIVEREAL: ", pRtnTopMemInfo->ACTIVEREAL, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->TOTALVIRTUAL: ", pRtnTopMemInfo->TOTALVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->ACTIVEVIRTUAL: ", pRtnTopMemInfo->ACTIVEVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopMemInfo->FREE: ", pRtnTopMemInfo->FREE, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTopMemInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTopMemInfoTopic_IOUser_vec.begin();
        it != g_RtnTopMemInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTopMemInfoTopic_IOUser_vec.end()) {
        g_RtnTopMemInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTopMemInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTopMemInfoTopic_mutex);

    uv_async_send(&g_RtnTopMemInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTopMemInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTopProcessInfoTopic(CShfeFtdcRspQryTopProcessInfoField* pRspQryTopProcessInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTopProcessInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTopProcessInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTopProcessInfoField* pNewRspQryTopProcessInfo = NULL;
    if (NULL != pRspQryTopProcessInfo) { 
        pNewRspQryTopProcessInfo = new CShfeFtdcRspQryTopProcessInfoField;
        if (NULL == pNewRspQryTopProcessInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTopProcessInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTopProcessInfo,pRspQryTopProcessInfo, sizeof(CShfeFtdcRspQryTopProcessInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTopProcessInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTopProcessInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTopProcessInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTopProcessInfo->HostName: ", pRspQryTopProcessInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->MonDate: ", pRspQryTopProcessInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->MonTime: ", pRspQryTopProcessInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->CPU: ", pRspQryTopProcessInfo->CPU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->TTY: ", pRspQryTopProcessInfo->TTY, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->PID: ", pRspQryTopProcessInfo->PID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->USERNAME: ", pRspQryTopProcessInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->PRI: ", pRspQryTopProcessInfo->PRI, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->NI: ", pRspQryTopProcessInfo->NI, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->SIZE: ", pRspQryTopProcessInfo->SIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->RES: ", pRspQryTopProcessInfo->RES, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->STATE: ", pRspQryTopProcessInfo->STATE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->TIME: ", pRspQryTopProcessInfo->TIME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->pWCPU: ", pRspQryTopProcessInfo->pWCPU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->pCPU: ", pRspQryTopProcessInfo->pCPU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTopProcessInfo->COMMAND: ", pRspQryTopProcessInfo->COMMAND, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTopProcessInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTopProcessInfoTopic_IOUser_vec.begin();
        it != g_RspQryTopProcessInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTopProcessInfoTopic_IOUser_vec.end()) {
        g_RspQryTopProcessInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTopProcessInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTopProcessInfoTopic_mutex);

    uv_async_send(&g_RspQryTopProcessInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTopProcessInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTopProcessInfoTopic(CShfeFtdcRtnTopProcessInfoField* pRtnTopProcessInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTopProcessInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTopProcessInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTopProcessInfoField* pNewRtnTopProcessInfo = NULL;
    if (NULL != pRtnTopProcessInfo) { 
        pNewRtnTopProcessInfo = new CShfeFtdcRtnTopProcessInfoField;
        if (NULL == pNewRtnTopProcessInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTopProcessInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTopProcessInfo,pRtnTopProcessInfo, sizeof(CShfeFtdcRtnTopProcessInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTopProcessInfo;
    if (NULL == pRtnTopProcessInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnTopProcessInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTopProcessInfo->HostName: ", pRtnTopProcessInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->MonDate: ", pRtnTopProcessInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->MonTime: ", pRtnTopProcessInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->CPU: ", pRtnTopProcessInfo->CPU, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->TTY: ", pRtnTopProcessInfo->TTY, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->PID: ", pRtnTopProcessInfo->PID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->USERNAME: ", pRtnTopProcessInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->PRI: ", pRtnTopProcessInfo->PRI, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->NI: ", pRtnTopProcessInfo->NI, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->SIZE: ", pRtnTopProcessInfo->SIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->RES: ", pRtnTopProcessInfo->RES, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->STATE: ", pRtnTopProcessInfo->STATE, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->TIME: ", pRtnTopProcessInfo->TIME, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->pWCPU: ", pRtnTopProcessInfo->pWCPU, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->pCPU: ", pRtnTopProcessInfo->pCPU, g_RunningResult_File);
        OutputCallbackMessage("pRtnTopProcessInfo->COMMAND: ", pRtnTopProcessInfo->COMMAND, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTopProcessInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTopProcessInfoTopic_IOUser_vec.begin();
        it != g_RtnTopProcessInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTopProcessInfoTopic_IOUser_vec.end()) {
        g_RtnTopProcessInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTopProcessInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTopProcessInfoTopic_mutex);

    uv_async_send(&g_RtnTopProcessInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTopProcessInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFileSystemInfoTopic(CShfeFtdcRspQryFileSystemInfoField* pRspQryFileSystemInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFileSystemInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFileSystemInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFileSystemInfoField* pNewRspQryFileSystemInfo = NULL;
    if (NULL != pRspQryFileSystemInfo) { 
        pNewRspQryFileSystemInfo = new CShfeFtdcRspQryFileSystemInfoField;
        if (NULL == pNewRspQryFileSystemInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFileSystemInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFileSystemInfo,pRspQryFileSystemInfo, sizeof(CShfeFtdcRspQryFileSystemInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFileSystemInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFileSystemInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFileSystemInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFileSystemInfo->HostName: ", pRspQryFileSystemInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->MonDate: ", pRspQryFileSystemInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->MonTime: ", pRspQryFileSystemInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->FILESYSTEM: ", pRspQryFileSystemInfo->FILESYSTEM, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->SIZE: ", pRspQryFileSystemInfo->SIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->USED: ", pRspQryFileSystemInfo->USED, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->AVAIL: ", pRspQryFileSystemInfo->AVAIL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->pUSERD: ", pRspQryFileSystemInfo->pUSERD, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->ISIZE: ", pRspQryFileSystemInfo->ISIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->IUSED: ", pRspQryFileSystemInfo->IUSED, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->IFREE: ", pRspQryFileSystemInfo->IFREE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->pIUSED: ", pRspQryFileSystemInfo->pIUSED, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileSystemInfo->MountedOn: ", pRspQryFileSystemInfo->MountedOn, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFileSystemInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFileSystemInfoTopic_IOUser_vec.begin();
        it != g_RspQryFileSystemInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFileSystemInfoTopic_IOUser_vec.end()) {
        g_RspQryFileSystemInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFileSystemInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFileSystemInfoTopic_mutex);

    uv_async_send(&g_RspQryFileSystemInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFileSystemInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFileSystemInfoTopic(CShfeFtdcRtnFileSystemInfoField* pRtnFileSystemInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFileSystemInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFileSystemInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFileSystemInfoField* pNewRtnFileSystemInfo = NULL;
    if (NULL != pRtnFileSystemInfo) { 
        pNewRtnFileSystemInfo = new CShfeFtdcRtnFileSystemInfoField;
        if (NULL == pNewRtnFileSystemInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFileSystemInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFileSystemInfo,pRtnFileSystemInfo, sizeof(CShfeFtdcRtnFileSystemInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFileSystemInfo;
    if (NULL == pRtnFileSystemInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnFileSystemInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFileSystemInfo->HostName: ", pRtnFileSystemInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->MonDate: ", pRtnFileSystemInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->MonTime: ", pRtnFileSystemInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->FILESYSTEM: ", pRtnFileSystemInfo->FILESYSTEM, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->SIZE: ", pRtnFileSystemInfo->SIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->USED: ", pRtnFileSystemInfo->USED, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->AVAIL: ", pRtnFileSystemInfo->AVAIL, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->pUSERD: ", pRtnFileSystemInfo->pUSERD, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->ISIZE: ", pRtnFileSystemInfo->ISIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->IUSED: ", pRtnFileSystemInfo->IUSED, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->IFREE: ", pRtnFileSystemInfo->IFREE, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->pIUSED: ", pRtnFileSystemInfo->pIUSED, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileSystemInfo->MountedOn: ", pRtnFileSystemInfo->MountedOn, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFileSystemInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFileSystemInfoTopic_IOUser_vec.begin();
        it != g_RtnFileSystemInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFileSystemInfoTopic_IOUser_vec.end()) {
        g_RtnFileSystemInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFileSystemInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFileSystemInfoTopic_mutex);

    uv_async_send(&g_RtnFileSystemInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFileSystemInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetworkInfoTopic(CShfeFtdcRspQryNetworkInfoField* pRspQryNetworkInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetworkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetworkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetworkInfoField* pNewRspQryNetworkInfo = NULL;
    if (NULL != pRspQryNetworkInfo) { 
        pNewRspQryNetworkInfo = new CShfeFtdcRspQryNetworkInfoField;
        if (NULL == pNewRspQryNetworkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetworkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetworkInfo,pRspQryNetworkInfo, sizeof(CShfeFtdcRspQryNetworkInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetworkInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetworkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetworkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetworkInfo->HostName: ", pRspQryNetworkInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->MonDate: ", pRspQryNetworkInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->MonTime: ", pRspQryNetworkInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->LANNAME: ", pRspQryNetworkInfo->LANNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->LANSTATUS: ", pRspQryNetworkInfo->LANSTATUS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->IPADDRESS: ", pRspQryNetworkInfo->IPADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->RECVBYTES: ", pRspQryNetworkInfo->RECVBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->RECVPACKETS: ", pRspQryNetworkInfo->RECVPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->RECVERRORPACKETS: ", pRspQryNetworkInfo->RECVERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->RECVDROPPACKETS: ", pRspQryNetworkInfo->RECVDROPPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->SENDBYTES: ", pRspQryNetworkInfo->SENDBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->SENDPACKETS: ", pRspQryNetworkInfo->SENDPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->SENDERRORPACKETS: ", pRspQryNetworkInfo->SENDERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetworkInfo->SENDDROPPACKETS: ", pRspQryNetworkInfo->SENDDROPPACKETS, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetworkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetworkInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetworkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetworkInfoTopic_IOUser_vec.end()) {
        g_RspQryNetworkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetworkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetworkInfoTopic_mutex);

    uv_async_send(&g_RspQryNetworkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetworkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetworkInfoTopic(CShfeFtdcRtnNetworkInfoField* pRtnNetworkInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetworkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetworkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetworkInfoField* pNewRtnNetworkInfo = NULL;
    if (NULL != pRtnNetworkInfo) { 
        pNewRtnNetworkInfo = new CShfeFtdcRtnNetworkInfoField;
        if (NULL == pNewRtnNetworkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetworkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetworkInfo,pRtnNetworkInfo, sizeof(CShfeFtdcRtnNetworkInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetworkInfo;
    if (NULL == pRtnNetworkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetworkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetworkInfo->HostName: ", pRtnNetworkInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->MonDate: ", pRtnNetworkInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->MonTime: ", pRtnNetworkInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->LANNAME: ", pRtnNetworkInfo->LANNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->LANSTATUS: ", pRtnNetworkInfo->LANSTATUS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->IPADDRESS: ", pRtnNetworkInfo->IPADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->RECVBYTES: ", pRtnNetworkInfo->RECVBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->RECVPACKETS: ", pRtnNetworkInfo->RECVPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->RECVERRORPACKETS: ", pRtnNetworkInfo->RECVERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->RECVDROPPACKETS: ", pRtnNetworkInfo->RECVDROPPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->SENDBYTES: ", pRtnNetworkInfo->SENDBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->SENDPACKETS: ", pRtnNetworkInfo->SENDPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->SENDERRORPACKETS: ", pRtnNetworkInfo->SENDERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetworkInfo->SENDDROPPACKETS: ", pRtnNetworkInfo->SENDDROPPACKETS, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetworkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetworkInfoTopic_IOUser_vec.begin();
        it != g_RtnNetworkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetworkInfoTopic_IOUser_vec.end()) {
        g_RtnNetworkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetworkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetworkInfoTopic_mutex);

    uv_async_send(&g_RtnNetworkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetworkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryMonitorObjectTopic(CShfeFtdcRspQryMonitorObjectField* pRspQryMonitorObject, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryMonitorObjectTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryMonitorObjectTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryMonitorObjectField* pNewRspQryMonitorObject = NULL;
    if (NULL != pRspQryMonitorObject) { 
        pNewRspQryMonitorObject = new CShfeFtdcRspQryMonitorObjectField;
        if (NULL == pNewRspQryMonitorObject) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryMonitorObject", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryMonitorObject,pRspQryMonitorObject, sizeof(CShfeFtdcRspQryMonitorObjectField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryMonitorObject;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryMonitorObject) { 
        OutputCallbackMessage("SysUserSpi::pRspQryMonitorObject is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryMonitorObject->ObjectID: ", pRspQryMonitorObject->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMonitorObject->ObjectName: ", pRspQryMonitorObject->ObjectName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMonitorObject->WarningActive: ", pRspQryMonitorObject->WarningActive, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryMonitorObjectTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryMonitorObjectTopic_IOUser_vec.begin();
        it != g_RspQryMonitorObjectTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryMonitorObjectTopic_IOUser_vec.end()) {
        g_RspQryMonitorObjectTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryMonitorObjectTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryMonitorObjectTopic_mutex);

    uv_async_send(&g_RspQryMonitorObjectTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryMonitorObjectTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnMonitorObjectTopic(CShfeFtdcRtnMonitorObjectField* pRtnMonitorObject){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnMonitorObjectTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnMonitorObjectTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnMonitorObjectField* pNewRtnMonitorObject = NULL;
    if (NULL != pRtnMonitorObject) { 
        pNewRtnMonitorObject = new CShfeFtdcRtnMonitorObjectField;
        if (NULL == pNewRtnMonitorObject) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnMonitorObject", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnMonitorObject,pRtnMonitorObject, sizeof(CShfeFtdcRtnMonitorObjectField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnMonitorObject;
    if (NULL == pRtnMonitorObject) { 
        OutputCallbackMessage("SysUserSpi::pRtnMonitorObject is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnMonitorObject->ObjectID: ", pRtnMonitorObject->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMonitorObject->ObjectName: ", pRtnMonitorObject->ObjectName, g_RunningResult_File);
        OutputCallbackMessage("pRtnMonitorObject->WarningActive: ", pRtnMonitorObject->WarningActive, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnMonitorObjectTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnMonitorObjectTopic_IOUser_vec.begin();
        it != g_RtnMonitorObjectTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnMonitorObjectTopic_IOUser_vec.end()) {
        g_RtnMonitorObjectTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnMonitorObjectTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnMonitorObjectTopic_mutex);

    uv_async_send(&g_RtnMonitorObjectTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnMonitorObjectTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryObjectRationalTopic(CShfeFtdcRspQryObjectRationalField* pRspQryObjectRational, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryObjectRationalTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryObjectRationalTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryObjectRationalField* pNewRspQryObjectRational = NULL;
    if (NULL != pRspQryObjectRational) { 
        pNewRspQryObjectRational = new CShfeFtdcRspQryObjectRationalField;
        if (NULL == pNewRspQryObjectRational) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryObjectRational", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryObjectRational,pRspQryObjectRational, sizeof(CShfeFtdcRspQryObjectRationalField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryObjectRational;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryObjectRational) { 
        OutputCallbackMessage("SysUserSpi::pRspQryObjectRational is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryObjectRational->ObjectID: ", pRspQryObjectRational->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectRational->HostObjectID: ", pRspQryObjectRational->HostObjectID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryObjectRationalTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryObjectRationalTopic_IOUser_vec.begin();
        it != g_RspQryObjectRationalTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryObjectRationalTopic_IOUser_vec.end()) {
        g_RspQryObjectRationalTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryObjectRationalTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryObjectRationalTopic_mutex);

    uv_async_send(&g_RspQryObjectRationalTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryObjectRationalTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnObjectRationalTopic(CShfeFtdcRtnObjectRationalField* pRtnObjectRational){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnObjectRationalTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnObjectRationalTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnObjectRationalField* pNewRtnObjectRational = NULL;
    if (NULL != pRtnObjectRational) { 
        pNewRtnObjectRational = new CShfeFtdcRtnObjectRationalField;
        if (NULL == pNewRtnObjectRational) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnObjectRational", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnObjectRational,pRtnObjectRational, sizeof(CShfeFtdcRtnObjectRationalField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnObjectRational;
    if (NULL == pRtnObjectRational) { 
        OutputCallbackMessage("SysUserSpi::pRtnObjectRational is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnObjectRational->ObjectID: ", pRtnObjectRational->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectRational->HostObjectID: ", pRtnObjectRational->HostObjectID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnObjectRationalTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnObjectRationalTopic_IOUser_vec.begin();
        it != g_RtnObjectRationalTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnObjectRationalTopic_IOUser_vec.end()) {
        g_RtnObjectRationalTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnObjectRationalTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnObjectRationalTopic_mutex);

    uv_async_send(&g_RtnObjectRationalTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnObjectRationalTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySyslogInfoTopic(CShfeFtdcRspQrySyslogInfoField* pRspQrySyslogInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySyslogInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySyslogInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySyslogInfoField* pNewRspQrySyslogInfo = NULL;
    if (NULL != pRspQrySyslogInfo) { 
        pNewRspQrySyslogInfo = new CShfeFtdcRspQrySyslogInfoField;
        if (NULL == pNewRspQrySyslogInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySyslogInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySyslogInfo,pRspQrySyslogInfo, sizeof(CShfeFtdcRspQrySyslogInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySyslogInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySyslogInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySyslogInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySyslogInfo->MonDate: ", pRspQrySyslogInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogInfo->MonTime: ", pRspQrySyslogInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogInfo->ObjectID: ", pRspQrySyslogInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogInfo->AttrType: ", pRspQrySyslogInfo->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogInfo->ContLen: ", pRspQrySyslogInfo->ContLen, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogInfo->FileContent: ", pRspQrySyslogInfo->FileContent, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySyslogInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySyslogInfoTopic_IOUser_vec.begin();
        it != g_RspQrySyslogInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySyslogInfoTopic_IOUser_vec.end()) {
        g_RspQrySyslogInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySyslogInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySyslogInfoTopic_mutex);

    uv_async_send(&g_RspQrySyslogInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySyslogInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSyslogInfoTopic(CShfeFtdcRtnSyslogInfoField* pRtnSyslogInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSyslogInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSyslogInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSyslogInfoField* pNewRtnSyslogInfo = NULL;
    if (NULL != pRtnSyslogInfo) { 
        pNewRtnSyslogInfo = new CShfeFtdcRtnSyslogInfoField;
        if (NULL == pNewRtnSyslogInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSyslogInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSyslogInfo,pRtnSyslogInfo, sizeof(CShfeFtdcRtnSyslogInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSyslogInfo;
    if (NULL == pRtnSyslogInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnSyslogInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSyslogInfo->MonDate: ", pRtnSyslogInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogInfo->MonTime: ", pRtnSyslogInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogInfo->ObjectID: ", pRtnSyslogInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogInfo->AttrType: ", pRtnSyslogInfo->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogInfo->ContLen: ", pRtnSyslogInfo->ContLen, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogInfo->FileContent: ", pRtnSyslogInfo->FileContent, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSyslogInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSyslogInfoTopic_IOUser_vec.begin();
        it != g_RtnSyslogInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSyslogInfoTopic_IOUser_vec.end()) {
        g_RtnSyslogInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSyslogInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSyslogInfoTopic_mutex);

    uv_async_send(&g_RtnSyslogInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSyslogInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySubscriberTopic(CShfeFtdcRspQrySubscriberField* pRspQrySubscriber, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySubscriberTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySubscriberTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySubscriberField* pNewRspQrySubscriber = NULL;
    if (NULL != pRspQrySubscriber) { 
        pNewRspQrySubscriber = new CShfeFtdcRspQrySubscriberField;
        if (NULL == pNewRspQrySubscriber) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySubscriber", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySubscriber,pRspQrySubscriber, sizeof(CShfeFtdcRspQrySubscriberField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySubscriber;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySubscriber) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySubscriber is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySubscriber->ErrorID: ", pRspQrySubscriber->ErrorID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySubscriber->ErrorMsg: ", pRspQrySubscriber->ErrorMsg, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySubscriber->ObjectID: ", pRspQrySubscriber->ObjectID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySubscriberTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySubscriberTopic_IOUser_vec.begin();
        it != g_RspQrySubscriberTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySubscriberTopic_IOUser_vec.end()) {
        g_RspQrySubscriberTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySubscriberTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySubscriberTopic_mutex);

    uv_async_send(&g_RspQrySubscriberTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySubscriberTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryOidRelationTopic(CShfeFtdcRspQryOidRelationField* pRspQryOidRelation, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryOidRelationTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryOidRelationTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryOidRelationField* pNewRspQryOidRelation = NULL;
    if (NULL != pRspQryOidRelation) { 
        pNewRspQryOidRelation = new CShfeFtdcRspQryOidRelationField;
        if (NULL == pNewRspQryOidRelation) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryOidRelation", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryOidRelation,pRspQryOidRelation, sizeof(CShfeFtdcRspQryOidRelationField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryOidRelation;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryOidRelation) { 
        OutputCallbackMessage("SysUserSpi::pRspQryOidRelation is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryOidRelation->ObjectID: ", pRspQryOidRelation->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOidRelation->HoldObjectID: ", pRspQryOidRelation->HoldObjectID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryOidRelationTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryOidRelationTopic_IOUser_vec.begin();
        it != g_RspQryOidRelationTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryOidRelationTopic_IOUser_vec.end()) {
        g_RspQryOidRelationTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryOidRelationTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryOidRelationTopic_mutex);

    uv_async_send(&g_RspQryOidRelationTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryOidRelationTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnOidRelationTopic(CShfeFtdcRtnOidRelationField* pRtnOidRelation){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnOidRelationTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnOidRelationTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnOidRelationField* pNewRtnOidRelation = NULL;
    if (NULL != pRtnOidRelation) { 
        pNewRtnOidRelation = new CShfeFtdcRtnOidRelationField;
        if (NULL == pNewRtnOidRelation) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnOidRelation", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnOidRelation,pRtnOidRelation, sizeof(CShfeFtdcRtnOidRelationField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnOidRelation;
    if (NULL == pRtnOidRelation) { 
        OutputCallbackMessage("SysUserSpi::pRtnOidRelation is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnOidRelation->ObjectID: ", pRtnOidRelation->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOidRelation->HoldObjectID: ", pRtnOidRelation->HoldObjectID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnOidRelationTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnOidRelationTopic_IOUser_vec.begin();
        it != g_RtnOidRelationTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnOidRelationTopic_IOUser_vec.end()) {
        g_RtnOidRelationTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnOidRelationTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnOidRelationTopic_mutex);

    uv_async_send(&g_RtnOidRelationTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnOidRelationTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryUserInfoTopic(CShfeFtdcRspQryUserInfoField* pRspQryUserInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryUserInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryUserInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryUserInfoField* pNewRspQryUserInfo = NULL;
    if (NULL != pRspQryUserInfo) { 
        pNewRspQryUserInfo = new CShfeFtdcRspQryUserInfoField;
        if (NULL == pNewRspQryUserInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryUserInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryUserInfo,pRspQryUserInfo, sizeof(CShfeFtdcRspQryUserInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryUserInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryUserInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryUserInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryUserInfo->USERNAME: ", pRspQryUserInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->USERID: ", pRspQryUserInfo->USERID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->GROUPNAME: ", pRspQryUserInfo->GROUPNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->GROUPID: ", pRspQryUserInfo->GROUPID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->HOMEPATH: ", pRspQryUserInfo->HOMEPATH, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->SHELL: ", pRspQryUserInfo->SHELL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->ObjectID: ", pRspQryUserInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->MonTime: ", pRspQryUserInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserInfo->MonDate: ", pRspQryUserInfo->MonDate, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryUserInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryUserInfoTopic_IOUser_vec.begin();
        it != g_RspQryUserInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryUserInfoTopic_IOUser_vec.end()) {
        g_RspQryUserInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryUserInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryUserInfoTopic_mutex);

    uv_async_send(&g_RspQryUserInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryUserInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnUserInfoTopic(CShfeFtdcRtnUserInfoField* pRtnUserInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnUserInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnUserInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnUserInfoField* pNewRtnUserInfo = NULL;
    if (NULL != pRtnUserInfo) { 
        pNewRtnUserInfo = new CShfeFtdcRtnUserInfoField;
        if (NULL == pNewRtnUserInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnUserInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnUserInfo,pRtnUserInfo, sizeof(CShfeFtdcRtnUserInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnUserInfo;
    if (NULL == pRtnUserInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnUserInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnUserInfo->USERNAME: ", pRtnUserInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->USERID: ", pRtnUserInfo->USERID, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->GROUPNAME: ", pRtnUserInfo->GROUPNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->GROUPID: ", pRtnUserInfo->GROUPID, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->HOMEPATH: ", pRtnUserInfo->HOMEPATH, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->SHELL: ", pRtnUserInfo->SHELL, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->ObjectID: ", pRtnUserInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->MonTime: ", pRtnUserInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserInfo->MonDate: ", pRtnUserInfo->MonDate, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnUserInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnUserInfoTopic_IOUser_vec.begin();
        it != g_RtnUserInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnUserInfoTopic_IOUser_vec.end()) {
        g_RtnUserInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnUserInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnUserInfoTopic_mutex);

    uv_async_send(&g_RtnUserInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnUserInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryOnlineUserInfoTopic(CShfeFtdcRspQryOnlineUserInfoField* pRspQryOnlineUserInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryOnlineUserInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryOnlineUserInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryOnlineUserInfoField* pNewRspQryOnlineUserInfo = NULL;
    if (NULL != pRspQryOnlineUserInfo) { 
        pNewRspQryOnlineUserInfo = new CShfeFtdcRspQryOnlineUserInfoField;
        if (NULL == pNewRspQryOnlineUserInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryOnlineUserInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryOnlineUserInfo,pRspQryOnlineUserInfo, sizeof(CShfeFtdcRspQryOnlineUserInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryOnlineUserInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryOnlineUserInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryOnlineUserInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryOnlineUserInfo->USERNAME: ", pRspQryOnlineUserInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->TIME: ", pRspQryOnlineUserInfo->TIME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->TTY: ", pRspQryOnlineUserInfo->TTY, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->IP: ", pRspQryOnlineUserInfo->IP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->CONNECTIME: ", pRspQryOnlineUserInfo->CONNECTIME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->PID: ", pRspQryOnlineUserInfo->PID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->ObjectID: ", pRspQryOnlineUserInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->MonTime: ", pRspQryOnlineUserInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOnlineUserInfo->MonDate: ", pRspQryOnlineUserInfo->MonDate, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryOnlineUserInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryOnlineUserInfoTopic_IOUser_vec.begin();
        it != g_RspQryOnlineUserInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryOnlineUserInfoTopic_IOUser_vec.end()) {
        g_RspQryOnlineUserInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryOnlineUserInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryOnlineUserInfoTopic_mutex);

    uv_async_send(&g_RspQryOnlineUserInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryOnlineUserInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnOnlineUserInfoTopic(CShfeFtdcRtnOnlineUserInfoField* pRtnOnlineUserInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnOnlineUserInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnOnlineUserInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnOnlineUserInfoField* pNewRtnOnlineUserInfo = NULL;
    if (NULL != pRtnOnlineUserInfo) { 
        pNewRtnOnlineUserInfo = new CShfeFtdcRtnOnlineUserInfoField;
        if (NULL == pNewRtnOnlineUserInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnOnlineUserInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnOnlineUserInfo,pRtnOnlineUserInfo, sizeof(CShfeFtdcRtnOnlineUserInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnOnlineUserInfo;
    if (NULL == pRtnOnlineUserInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnOnlineUserInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnOnlineUserInfo->USERNAME: ", pRtnOnlineUserInfo->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->TIME: ", pRtnOnlineUserInfo->TIME, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->TTY: ", pRtnOnlineUserInfo->TTY, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->IP: ", pRtnOnlineUserInfo->IP, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->CONNECTIME: ", pRtnOnlineUserInfo->CONNECTIME, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->PID: ", pRtnOnlineUserInfo->PID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->ObjectID: ", pRtnOnlineUserInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->MonTime: ", pRtnOnlineUserInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnOnlineUserInfo->MonDate: ", pRtnOnlineUserInfo->MonDate, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnOnlineUserInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnOnlineUserInfoTopic_IOUser_vec.begin();
        it != g_RtnOnlineUserInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnOnlineUserInfoTopic_IOUser_vec.end()) {
        g_RtnOnlineUserInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnOnlineUserInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnOnlineUserInfoTopic_mutex);

    uv_async_send(&g_RtnOnlineUserInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnOnlineUserInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryWarningEventTopic(CShfeFtdcRspQryWarningEventField* pRspQryWarningEvent, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryWarningEventTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryWarningEventTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryWarningEventField* pNewRspQryWarningEvent = NULL;
    if (NULL != pRspQryWarningEvent) { 
        pNewRspQryWarningEvent = new CShfeFtdcRspQryWarningEventField;
        if (NULL == pNewRspQryWarningEvent) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryWarningEvent", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryWarningEvent,pRspQryWarningEvent, sizeof(CShfeFtdcRspQryWarningEventField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryWarningEvent;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryWarningEvent) { 
        OutputCallbackMessage("SysUserSpi::pRspQryWarningEvent is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryWarningEvent->MonDate: ", pRspQryWarningEvent->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->MonTime: ", pRspQryWarningEvent->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->OccurDate: ", pRspQryWarningEvent->OccurDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->OccurTime: ", pRspQryWarningEvent->OccurTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EvendID: ", pRspQryWarningEvent->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->ObjectID: ", pRspQryWarningEvent->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->IPAddress: ", pRspQryWarningEvent->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EventName: ", pRspQryWarningEvent->EventName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EventNum: ", pRspQryWarningEvent->EventNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EventType: ", pRspQryWarningEvent->EventType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EventDes: ", pRspQryWarningEvent->EventDes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->ProcessFlag: ", pRspQryWarningEvent->ProcessFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->WarningLevel: ", pRspQryWarningEvent->WarningLevel, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->EventDealDes: ", pRspQryWarningEvent->EventDealDes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningEvent->FullEventName: ", pRspQryWarningEvent->FullEventName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryWarningEventTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryWarningEventTopic_IOUser_vec.begin();
        it != g_RspQryWarningEventTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryWarningEventTopic_IOUser_vec.end()) {
        g_RspQryWarningEventTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryWarningEventTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryWarningEventTopic_mutex);

    uv_async_send(&g_RspQryWarningEventTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryWarningEventTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnWarningEventTopic(CShfeFtdcRtnWarningEventField* pRtnWarningEvent){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnWarningEventTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnWarningEventTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnWarningEventField* pNewRtnWarningEvent = NULL;
    if (NULL != pRtnWarningEvent) { 
        pNewRtnWarningEvent = new CShfeFtdcRtnWarningEventField;
        if (NULL == pNewRtnWarningEvent) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnWarningEvent", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnWarningEvent,pRtnWarningEvent, sizeof(CShfeFtdcRtnWarningEventField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnWarningEvent;
    if (NULL == pRtnWarningEvent) { 
        OutputCallbackMessage("SysUserSpi::pRtnWarningEvent is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnWarningEvent->MonDate: ", pRtnWarningEvent->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->MonTime: ", pRtnWarningEvent->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->OccurDate: ", pRtnWarningEvent->OccurDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->OccurTime: ", pRtnWarningEvent->OccurTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EvendID: ", pRtnWarningEvent->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->ObjectID: ", pRtnWarningEvent->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->IPAddress: ", pRtnWarningEvent->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventName: ", pRtnWarningEvent->EventName, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventNum: ", pRtnWarningEvent->EventNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventType: ", pRtnWarningEvent->EventType, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventDes: ", pRtnWarningEvent->EventDes, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->ProcessFlag: ", pRtnWarningEvent->ProcessFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->WarningLevel: ", pRtnWarningEvent->WarningLevel, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventDealDes: ", pRtnWarningEvent->EventDealDes, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->FullEventName: ", pRtnWarningEvent->FullEventName, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningEvent->EventCount: ", pRtnWarningEvent->EventCount, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnWarningEventTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnWarningEventTopic_IOUser_vec.begin();
        it != g_RtnWarningEventTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnWarningEventTopic_IOUser_vec.end()) {
        g_RtnWarningEventTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnWarningEventTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnWarningEventTopic_mutex);

    uv_async_send(&g_RtnWarningEventTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnWarningEventTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryObjectAttrTopic(CShfeFtdcRspQryObjectAttrField* pRspQryObjectAttr, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryObjectAttrField* pNewRspQryObjectAttr = NULL;
    if (NULL != pRspQryObjectAttr) { 
        pNewRspQryObjectAttr = new CShfeFtdcRspQryObjectAttrField;
        if (NULL == pNewRspQryObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryObjectAttr,pRspQryObjectAttr, sizeof(CShfeFtdcRspQryObjectAttrField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryObjectAttr;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRspQryObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryObjectAttr->ObjectID: ", pRspQryObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectAttr->AttrType: ", pRspQryObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectAttr->MonDate: ", pRspQryObjectAttr->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectAttr->MonTime: ", pRspQryObjectAttr->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectAttr->ValueType: ", pRspQryObjectAttr->ValueType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryObjectAttr->AttrValue: ", pRspQryObjectAttr->AttrValue, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryObjectAttrTopic_IOUser_vec.begin();
        it != g_RspQryObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryObjectAttrTopic_IOUser_vec.end()) {
        g_RspQryObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryObjectAttrTopic_mutex);

    uv_async_send(&g_RspQryObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnObjectAttrTopic(CShfeFtdcRtnObjectAttrField* pRtnObjectAttr){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnObjectAttrField* pNewRtnObjectAttr = NULL;
    if (NULL != pRtnObjectAttr) { 
        pNewRtnObjectAttr = new CShfeFtdcRtnObjectAttrField;
        if (NULL == pNewRtnObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnObjectAttr,pRtnObjectAttr, sizeof(CShfeFtdcRtnObjectAttrField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnObjectAttr;
    if (NULL == pRtnObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRtnObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnObjectAttr->ObjectID: ", pRtnObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectAttr->AttrType: ", pRtnObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectAttr->MonDate: ", pRtnObjectAttr->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectAttr->MonTime: ", pRtnObjectAttr->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectAttr->ValueType: ", pRtnObjectAttr->ValueType, g_RunningResult_File);
        OutputCallbackMessage("pRtnObjectAttr->AttrValue: ", pRtnObjectAttr->AttrValue, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnObjectAttrTopic_IOUser_vec.begin();
        it != g_RtnObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnObjectAttrTopic_IOUser_vec.end()) {
        g_RtnObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnObjectAttrTopic_mutex);

    uv_async_send(&g_RtnObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryInvalidateOrderTopic(CShfeFtdcRspQryInvalidateOrderField* pRspQryInvalidateOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryInvalidateOrderTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryInvalidateOrderTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryInvalidateOrderField* pNewRspQryInvalidateOrder = NULL;
    if (NULL != pRspQryInvalidateOrder) { 
        pNewRspQryInvalidateOrder = new CShfeFtdcRspQryInvalidateOrderField;
        if (NULL == pNewRspQryInvalidateOrder) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryInvalidateOrder", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryInvalidateOrder,pRspQryInvalidateOrder, sizeof(CShfeFtdcRspQryInvalidateOrderField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryInvalidateOrder;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryInvalidateOrder) { 
        OutputCallbackMessage("SysUserSpi::pRspQryInvalidateOrder is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryInvalidateOrder->OrderSysID: ", pRspQryInvalidateOrder->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->OrderLocalID: ", pRspQryInvalidateOrder->OrderLocalID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->ActionDate: ", pRspQryInvalidateOrder->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->ActionTime: ", pRspQryInvalidateOrder->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->ErrorMsg: ", pRspQryInvalidateOrder->ErrorMsg, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->ParticipantID: ", pRspQryInvalidateOrder->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->UserID: ", pRspQryInvalidateOrder->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->ClientID: ", pRspQryInvalidateOrder->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->InstrumentID: ", pRspQryInvalidateOrder->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->Direction: ", pRspQryInvalidateOrder->Direction, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->CombOffsetFlag: ", pRspQryInvalidateOrder->CombOffsetFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->CombHedgeFlag: ", pRspQryInvalidateOrder->CombHedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->LimitPrice: ", pRspQryInvalidateOrder->LimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->VolumeTotalOriginal: ", pRspQryInvalidateOrder->VolumeTotalOriginal, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->TimeCondition: ", pRspQryInvalidateOrder->TimeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->VolumeCondition: ", pRspQryInvalidateOrder->VolumeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInvalidateOrder->MinVolume: ", pRspQryInvalidateOrder->MinVolume, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryInvalidateOrderTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryInvalidateOrderTopic_IOUser_vec.begin();
        it != g_RspQryInvalidateOrderTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryInvalidateOrderTopic_IOUser_vec.end()) {
        g_RspQryInvalidateOrderTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryInvalidateOrderTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryInvalidateOrderTopic_mutex);

    uv_async_send(&g_RspQryInvalidateOrderTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryInvalidateOrderTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnInvalidateOrderTopic(CShfeFtdcRtnInvalidateOrderField* pRtnInvalidateOrder){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnInvalidateOrderTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnInvalidateOrderTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnInvalidateOrderField* pNewRtnInvalidateOrder = NULL;
    if (NULL != pRtnInvalidateOrder) { 
        pNewRtnInvalidateOrder = new CShfeFtdcRtnInvalidateOrderField;
        if (NULL == pNewRtnInvalidateOrder) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnInvalidateOrder", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnInvalidateOrder,pRtnInvalidateOrder, sizeof(CShfeFtdcRtnInvalidateOrderField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnInvalidateOrder;
    if (NULL == pRtnInvalidateOrder) { 
        OutputCallbackMessage("SysUserSpi::pRtnInvalidateOrder is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnInvalidateOrder->OrderSysID: ", pRtnInvalidateOrder->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->OrderLocalID: ", pRtnInvalidateOrder->OrderLocalID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->ActionDate: ", pRtnInvalidateOrder->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->ActionTime: ", pRtnInvalidateOrder->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->ErrorMsg: ", pRtnInvalidateOrder->ErrorMsg, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->ParticipantID: ", pRtnInvalidateOrder->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->UserID: ", pRtnInvalidateOrder->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->ClientID: ", pRtnInvalidateOrder->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->InstrumentID: ", pRtnInvalidateOrder->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->Direction: ", pRtnInvalidateOrder->Direction, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->CombOffsetFlag: ", pRtnInvalidateOrder->CombOffsetFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->CombHedgeFlag: ", pRtnInvalidateOrder->CombHedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->LimitPrice: ", pRtnInvalidateOrder->LimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->VolumeTotalOriginal: ", pRtnInvalidateOrder->VolumeTotalOriginal, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->TimeCondition: ", pRtnInvalidateOrder->TimeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->VolumeCondition: ", pRtnInvalidateOrder->VolumeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRtnInvalidateOrder->MinVolume: ", pRtnInvalidateOrder->MinVolume, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnInvalidateOrderTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnInvalidateOrderTopic_IOUser_vec.begin();
        it != g_RtnInvalidateOrderTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnInvalidateOrderTopic_IOUser_vec.end()) {
        g_RtnInvalidateOrderTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnInvalidateOrderTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnInvalidateOrderTopic_mutex);

    uv_async_send(&g_RtnInvalidateOrderTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnInvalidateOrderTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryOrderStatusTopic(CShfeFtdcRspQryOrderStatusField* pRspQryOrderStatus, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryOrderStatusTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryOrderStatusTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryOrderStatusField* pNewRspQryOrderStatus = NULL;
    if (NULL != pRspQryOrderStatus) { 
        pNewRspQryOrderStatus = new CShfeFtdcRspQryOrderStatusField;
        if (NULL == pNewRspQryOrderStatus) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryOrderStatus", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryOrderStatus,pRspQryOrderStatus, sizeof(CShfeFtdcRspQryOrderStatusField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryOrderStatus;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryOrderStatus) { 
        OutputCallbackMessage("SysUserSpi::pRspQryOrderStatus is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryOrderStatus->ActionDate: ", pRspQryOrderStatus->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->ActionTime: ", pRspQryOrderStatus->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->OrderSysID: ", pRspQryOrderStatus->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->OrderLocalID: ", pRspQryOrderStatus->OrderLocalID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->InsertDate: ", pRspQryOrderStatus->InsertDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->InsertTime: ", pRspQryOrderStatus->InsertTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->OrderStatus: ", pRspQryOrderStatus->OrderStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->ParticipantID: ", pRspQryOrderStatus->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->UserID: ", pRspQryOrderStatus->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->ClientID: ", pRspQryOrderStatus->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->InstrumentID: ", pRspQryOrderStatus->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->Direction: ", pRspQryOrderStatus->Direction, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->CombOffsetFlag: ", pRspQryOrderStatus->CombOffsetFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->CombHedgeFlag: ", pRspQryOrderStatus->CombHedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->LimitPrice: ", pRspQryOrderStatus->LimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->VolumeTotalOriginal: ", pRspQryOrderStatus->VolumeTotalOriginal, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->TimeCondition: ", pRspQryOrderStatus->TimeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->VolumeCondition: ", pRspQryOrderStatus->VolumeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryOrderStatus->MinVolume: ", pRspQryOrderStatus->MinVolume, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryOrderStatusTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryOrderStatusTopic_IOUser_vec.begin();
        it != g_RspQryOrderStatusTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryOrderStatusTopic_IOUser_vec.end()) {
        g_RspQryOrderStatusTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryOrderStatusTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryOrderStatusTopic_mutex);

    uv_async_send(&g_RspQryOrderStatusTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryOrderStatusTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnOrderStatusTopic(CShfeFtdcRtnOrderStatusField* pRtnOrderStatus){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnOrderStatusTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnOrderStatusTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnOrderStatusField* pNewRtnOrderStatus = NULL;
    if (NULL != pRtnOrderStatus) { 
        pNewRtnOrderStatus = new CShfeFtdcRtnOrderStatusField;
        if (NULL == pNewRtnOrderStatus) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnOrderStatus", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnOrderStatus,pRtnOrderStatus, sizeof(CShfeFtdcRtnOrderStatusField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnOrderStatus;
    if (NULL == pRtnOrderStatus) { 
        OutputCallbackMessage("SysUserSpi::pRtnOrderStatus is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnOrderStatus->ActionDate: ", pRtnOrderStatus->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->ActionTime: ", pRtnOrderStatus->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->OrderSysID: ", pRtnOrderStatus->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->OrderLocalID: ", pRtnOrderStatus->OrderLocalID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->InsertDate: ", pRtnOrderStatus->InsertDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->InsertTime: ", pRtnOrderStatus->InsertTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->OrderStatus: ", pRtnOrderStatus->OrderStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->ParticipantID: ", pRtnOrderStatus->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->UserID: ", pRtnOrderStatus->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->ClientID: ", pRtnOrderStatus->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->InstrumentID: ", pRtnOrderStatus->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->Direction: ", pRtnOrderStatus->Direction, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->CombOffsetFlag: ", pRtnOrderStatus->CombOffsetFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->CombHedgeFlag: ", pRtnOrderStatus->CombHedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->LimitPrice: ", pRtnOrderStatus->LimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->VolumeTotalOriginal: ", pRtnOrderStatus->VolumeTotalOriginal, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->TimeCondition: ", pRtnOrderStatus->TimeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->VolumeCondition: ", pRtnOrderStatus->VolumeCondition, g_RunningResult_File);
        OutputCallbackMessage("pRtnOrderStatus->MinVolume: ", pRtnOrderStatus->MinVolume, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnOrderStatusTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnOrderStatusTopic_IOUser_vec.begin();
        it != g_RtnOrderStatusTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnOrderStatusTopic_IOUser_vec.end()) {
        g_RtnOrderStatusTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnOrderStatusTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnOrderStatusTopic_mutex);

    uv_async_send(&g_RtnOrderStatusTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnOrderStatusTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryBargainOrderTopic(CShfeFtdcRspQryBargainOrderField* pRspQryBargainOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryBargainOrderTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryBargainOrderTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryBargainOrderField* pNewRspQryBargainOrder = NULL;
    if (NULL != pRspQryBargainOrder) { 
        pNewRspQryBargainOrder = new CShfeFtdcRspQryBargainOrderField;
        if (NULL == pNewRspQryBargainOrder) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryBargainOrder", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryBargainOrder,pRspQryBargainOrder, sizeof(CShfeFtdcRspQryBargainOrderField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryBargainOrder;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryBargainOrder) { 
        OutputCallbackMessage("SysUserSpi::pRspQryBargainOrder is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryBargainOrder->ActionDate: ", pRspQryBargainOrder->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->ActionTime: ", pRspQryBargainOrder->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->TradeID: ", pRspQryBargainOrder->TradeID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->OrderSysID: ", pRspQryBargainOrder->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->InstrumentID: ", pRspQryBargainOrder->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->Price: ", pRspQryBargainOrder->Price, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->Volume: ", pRspQryBargainOrder->Volume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->ParticipantID: ", pRspQryBargainOrder->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->UserID: ", pRspQryBargainOrder->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryBargainOrder->ClientID: ", pRspQryBargainOrder->ClientID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryBargainOrderTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryBargainOrderTopic_IOUser_vec.begin();
        it != g_RspQryBargainOrderTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryBargainOrderTopic_IOUser_vec.end()) {
        g_RspQryBargainOrderTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryBargainOrderTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryBargainOrderTopic_mutex);

    uv_async_send(&g_RspQryBargainOrderTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryBargainOrderTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnBargainOrderTopic(CShfeFtdcRtnBargainOrderField* pRtnBargainOrder){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnBargainOrderTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnBargainOrderTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnBargainOrderField* pNewRtnBargainOrder = NULL;
    if (NULL != pRtnBargainOrder) { 
        pNewRtnBargainOrder = new CShfeFtdcRtnBargainOrderField;
        if (NULL == pNewRtnBargainOrder) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnBargainOrder", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnBargainOrder,pRtnBargainOrder, sizeof(CShfeFtdcRtnBargainOrderField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnBargainOrder;
    if (NULL == pRtnBargainOrder) { 
        OutputCallbackMessage("SysUserSpi::pRtnBargainOrder is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnBargainOrder->ActionDate: ", pRtnBargainOrder->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->ActionTime: ", pRtnBargainOrder->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->TradeID: ", pRtnBargainOrder->TradeID, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->OrderSysID: ", pRtnBargainOrder->OrderSysID, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->InstrumentID: ", pRtnBargainOrder->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->Price: ", pRtnBargainOrder->Price, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->Volume: ", pRtnBargainOrder->Volume, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->ParticipantID: ", pRtnBargainOrder->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->UserID: ", pRtnBargainOrder->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnBargainOrder->ClientID: ", pRtnBargainOrder->ClientID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnBargainOrderTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnBargainOrderTopic_IOUser_vec.begin();
        it != g_RtnBargainOrderTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnBargainOrderTopic_IOUser_vec.end()) {
        g_RtnBargainOrderTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnBargainOrderTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnBargainOrderTopic_mutex);

    uv_async_send(&g_RtnBargainOrderTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnBargainOrderTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryInstPropertyTopic(CShfeFtdcRspQryInstPropertyField* pRspQryInstProperty, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryInstPropertyTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryInstPropertyTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryInstPropertyField* pNewRspQryInstProperty = NULL;
    if (NULL != pRspQryInstProperty) { 
        pNewRspQryInstProperty = new CShfeFtdcRspQryInstPropertyField;
        if (NULL == pNewRspQryInstProperty) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryInstProperty", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryInstProperty,pRspQryInstProperty, sizeof(CShfeFtdcRspQryInstPropertyField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryInstProperty;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryInstProperty) { 
        OutputCallbackMessage("SysUserSpi::pRspQryInstProperty is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryInstProperty->ActionDate: ", pRspQryInstProperty->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->ActionTime: ", pRspQryInstProperty->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->InstrumentID: ", pRspQryInstProperty->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->SettlementGroupID: ", pRspQryInstProperty->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->UnderlyingInstrID: ", pRspQryInstProperty->UnderlyingInstrID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->ProductClass: ", pRspQryInstProperty->ProductClass, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->PositionType: ", pRspQryInstProperty->PositionType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->VolumeMultiple: ", pRspQryInstProperty->VolumeMultiple, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->UnderlyingMultiple: ", pRspQryInstProperty->UnderlyingMultiple, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->InstLifePhase: ", pRspQryInstProperty->InstLifePhase, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->OpenDate: ", pRspQryInstProperty->OpenDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->ExpireDate: ", pRspQryInstProperty->ExpireDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->StartDelivDate: ", pRspQryInstProperty->StartDelivDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->EndDelivDate: ", pRspQryInstProperty->EndDelivDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->BasisPrice: ", pRspQryInstProperty->BasisPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->MaxMarketOrderVolume: ", pRspQryInstProperty->MaxMarketOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->MinMarketOrderVolume: ", pRspQryInstProperty->MinMarketOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->MaxLimitOrderVolume: ", pRspQryInstProperty->MaxLimitOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->MinLimitOrderVolume: ", pRspQryInstProperty->MinLimitOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->PriceTick: ", pRspQryInstProperty->PriceTick, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstProperty->AllowDelivPersonOpen: ", pRspQryInstProperty->AllowDelivPersonOpen, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryInstPropertyTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryInstPropertyTopic_IOUser_vec.begin();
        it != g_RspQryInstPropertyTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryInstPropertyTopic_IOUser_vec.end()) {
        g_RspQryInstPropertyTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryInstPropertyTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryInstPropertyTopic_mutex);

    uv_async_send(&g_RspQryInstPropertyTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryInstPropertyTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnInstPropertyTopic(CShfeFtdcRtnInstPropertyField* pRtnInstProperty){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnInstPropertyTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnInstPropertyTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnInstPropertyField* pNewRtnInstProperty = NULL;
    if (NULL != pRtnInstProperty) { 
        pNewRtnInstProperty = new CShfeFtdcRtnInstPropertyField;
        if (NULL == pNewRtnInstProperty) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnInstProperty", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnInstProperty,pRtnInstProperty, sizeof(CShfeFtdcRtnInstPropertyField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnInstProperty;
    if (NULL == pRtnInstProperty) { 
        OutputCallbackMessage("SysUserSpi::pRtnInstProperty is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnInstProperty->ActionDate: ", pRtnInstProperty->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->ActionTime: ", pRtnInstProperty->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->InstrumentID: ", pRtnInstProperty->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->SettlementGroupID: ", pRtnInstProperty->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->UnderlyingInstrID: ", pRtnInstProperty->UnderlyingInstrID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->ProductClass: ", pRtnInstProperty->ProductClass, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->PositionType: ", pRtnInstProperty->PositionType, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->VolumeMultiple: ", pRtnInstProperty->VolumeMultiple, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->UnderlyingMultiple: ", pRtnInstProperty->UnderlyingMultiple, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->InstLifePhase: ", pRtnInstProperty->InstLifePhase, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->OpenDate: ", pRtnInstProperty->OpenDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->ExpireDate: ", pRtnInstProperty->ExpireDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->StartDelivDate: ", pRtnInstProperty->StartDelivDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->EndDelivDate: ", pRtnInstProperty->EndDelivDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->BasisPrice: ", pRtnInstProperty->BasisPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->MaxMarketOrderVolume: ", pRtnInstProperty->MaxMarketOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->MinMarketOrderVolume: ", pRtnInstProperty->MinMarketOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->MaxLimitOrderVolume: ", pRtnInstProperty->MaxLimitOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->MinLimitOrderVolume: ", pRtnInstProperty->MinLimitOrderVolume, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->PriceTick: ", pRtnInstProperty->PriceTick, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstProperty->AllowDelivPersonOpen: ", pRtnInstProperty->AllowDelivPersonOpen, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnInstPropertyTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnInstPropertyTopic_IOUser_vec.begin();
        it != g_RtnInstPropertyTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnInstPropertyTopic_IOUser_vec.end()) {
        g_RtnInstPropertyTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnInstPropertyTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnInstPropertyTopic_mutex);

    uv_async_send(&g_RtnInstPropertyTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnInstPropertyTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryMarginRateTopic(CShfeFtdcRspQryMarginRateField* pRspQryMarginRate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryMarginRateTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryMarginRateTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryMarginRateField* pNewRspQryMarginRate = NULL;
    if (NULL != pRspQryMarginRate) { 
        pNewRspQryMarginRate = new CShfeFtdcRspQryMarginRateField;
        if (NULL == pNewRspQryMarginRate) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryMarginRate", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryMarginRate,pRspQryMarginRate, sizeof(CShfeFtdcRspQryMarginRateField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryMarginRate;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryMarginRate) { 
        OutputCallbackMessage("SysUserSpi::pRspQryMarginRate is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryMarginRate->ActionDate: ", pRspQryMarginRate->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->ActionTime: ", pRspQryMarginRate->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->InstrumentID: ", pRspQryMarginRate->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->ParticipantID: ", pRspQryMarginRate->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->TradingRole: ", pRspQryMarginRate->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->HedgeFlag: ", pRspQryMarginRate->HedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->ValueMode: ", pRspQryMarginRate->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->LongMarginRatio: ", pRspQryMarginRate->LongMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRate->ShortMarginRatio: ", pRspQryMarginRate->ShortMarginRatio, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryMarginRateTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryMarginRateTopic_IOUser_vec.begin();
        it != g_RspQryMarginRateTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryMarginRateTopic_IOUser_vec.end()) {
        g_RspQryMarginRateTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryMarginRateTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryMarginRateTopic_mutex);

    uv_async_send(&g_RspQryMarginRateTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryMarginRateTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnMarginRateTopic(CShfeFtdcRtnMarginRateField* pRtnMarginRate){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnMarginRateTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnMarginRateTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnMarginRateField* pNewRtnMarginRate = NULL;
    if (NULL != pRtnMarginRate) { 
        pNewRtnMarginRate = new CShfeFtdcRtnMarginRateField;
        if (NULL == pNewRtnMarginRate) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnMarginRate", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnMarginRate,pRtnMarginRate, sizeof(CShfeFtdcRtnMarginRateField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnMarginRate;
    if (NULL == pRtnMarginRate) { 
        OutputCallbackMessage("SysUserSpi::pRtnMarginRate is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnMarginRate->ActionDate: ", pRtnMarginRate->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->ActionTime: ", pRtnMarginRate->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->InstrumentID: ", pRtnMarginRate->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->ParticipantID: ", pRtnMarginRate->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->TradingRole: ", pRtnMarginRate->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->HedgeFlag: ", pRtnMarginRate->HedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->ValueMode: ", pRtnMarginRate->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->LongMarginRatio: ", pRtnMarginRate->LongMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRate->ShortMarginRatio: ", pRtnMarginRate->ShortMarginRatio, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnMarginRateTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnMarginRateTopic_IOUser_vec.begin();
        it != g_RtnMarginRateTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnMarginRateTopic_IOUser_vec.end()) {
        g_RtnMarginRateTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnMarginRateTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnMarginRateTopic_mutex);

    uv_async_send(&g_RtnMarginRateTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnMarginRateTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPriceLimitTopic(CShfeFtdcRspQryPriceLimitField* pRspQryPriceLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPriceLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPriceLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPriceLimitField* pNewRspQryPriceLimit = NULL;
    if (NULL != pRspQryPriceLimit) { 
        pNewRspQryPriceLimit = new CShfeFtdcRspQryPriceLimitField;
        if (NULL == pNewRspQryPriceLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPriceLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPriceLimit,pRspQryPriceLimit, sizeof(CShfeFtdcRspQryPriceLimitField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPriceLimit;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPriceLimit) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPriceLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPriceLimit->ActionDate: ", pRspQryPriceLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->ActionTime: ", pRspQryPriceLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->InstrumentID: ", pRspQryPriceLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->ValueMode: ", pRspQryPriceLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->RoundingMode: ", pRspQryPriceLimit->RoundingMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->UpperLimitPrice: ", pRspQryPriceLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPriceLimit->LowerLimitPrice: ", pRspQryPriceLimit->LowerLimitPrice, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPriceLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPriceLimitTopic_IOUser_vec.begin();
        it != g_RspQryPriceLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPriceLimitTopic_IOUser_vec.end()) {
        g_RspQryPriceLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPriceLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPriceLimitTopic_mutex);

    uv_async_send(&g_RspQryPriceLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPriceLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPriceLimitTopic(CShfeFtdcRtnPriceLimitField* pRtnPriceLimit){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPriceLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPriceLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPriceLimitField* pNewRtnPriceLimit = NULL;
    if (NULL != pRtnPriceLimit) { 
        pNewRtnPriceLimit = new CShfeFtdcRtnPriceLimitField;
        if (NULL == pNewRtnPriceLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPriceLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPriceLimit,pRtnPriceLimit, sizeof(CShfeFtdcRtnPriceLimitField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPriceLimit;
    if (NULL == pRtnPriceLimit) { 
        OutputCallbackMessage("SysUserSpi::pRtnPriceLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPriceLimit->ActionDate: ", pRtnPriceLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->ActionTime: ", pRtnPriceLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->InstrumentID: ", pRtnPriceLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->ValueMode: ", pRtnPriceLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->RoundingMode: ", pRtnPriceLimit->RoundingMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->UpperLimitPrice: ", pRtnPriceLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnPriceLimit->LowerLimitPrice: ", pRtnPriceLimit->LowerLimitPrice, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPriceLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPriceLimitTopic_IOUser_vec.begin();
        it != g_RtnPriceLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPriceLimitTopic_IOUser_vec.end()) {
        g_RtnPriceLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPriceLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPriceLimitTopic_mutex);

    uv_async_send(&g_RtnPriceLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPriceLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPartPosiLimitTopic(CShfeFtdcRspQryPartPosiLimitField* pRspQryPartPosiLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPartPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPartPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPartPosiLimitField* pNewRspQryPartPosiLimit = NULL;
    if (NULL != pRspQryPartPosiLimit) { 
        pNewRspQryPartPosiLimit = new CShfeFtdcRspQryPartPosiLimitField;
        if (NULL == pNewRspQryPartPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPartPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPartPosiLimit,pRspQryPartPosiLimit, sizeof(CShfeFtdcRspQryPartPosiLimitField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPartPosiLimit;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPartPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPartPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPartPosiLimit->ActionDate: ", pRspQryPartPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->ActionTime: ", pRspQryPartPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->InstrumentID: ", pRspQryPartPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->ParticipantID: ", pRspQryPartPosiLimit->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->TradingRole: ", pRspQryPartPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->StartTotalPosition: ", pRspQryPartPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->ValueMode: ", pRspQryPartPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->LongPosLimit: ", pRspQryPartPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->ShortPosLimit: ", pRspQryPartPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->UpperLimitPrice: ", pRspQryPartPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartPosiLimit->LowerLimitPrice: ", pRspQryPartPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPartPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPartPosiLimitTopic_IOUser_vec.begin();
        it != g_RspQryPartPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPartPosiLimitTopic_IOUser_vec.end()) {
        g_RspQryPartPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPartPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPartPosiLimitTopic_mutex);

    uv_async_send(&g_RspQryPartPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPartPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPartPosiLimitTopic(CShfeFtdcRtnPartPosiLimitField* pRtnPartPosiLimit){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPartPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPartPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPartPosiLimitField* pNewRtnPartPosiLimit = NULL;
    if (NULL != pRtnPartPosiLimit) { 
        pNewRtnPartPosiLimit = new CShfeFtdcRtnPartPosiLimitField;
        if (NULL == pNewRtnPartPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPartPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPartPosiLimit,pRtnPartPosiLimit, sizeof(CShfeFtdcRtnPartPosiLimitField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPartPosiLimit;
    if (NULL == pRtnPartPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRtnPartPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPartPosiLimit->ActionDate: ", pRtnPartPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->ActionTime: ", pRtnPartPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->InstrumentID: ", pRtnPartPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->ParticipantID: ", pRtnPartPosiLimit->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->TradingRole: ", pRtnPartPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->StartTotalPosition: ", pRtnPartPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->ValueMode: ", pRtnPartPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->LongPosLimit: ", pRtnPartPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->ShortPosLimit: ", pRtnPartPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->UpperLimitPrice: ", pRtnPartPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartPosiLimit->LowerLimitPrice: ", pRtnPartPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPartPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPartPosiLimitTopic_IOUser_vec.begin();
        it != g_RtnPartPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPartPosiLimitTopic_IOUser_vec.end()) {
        g_RtnPartPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPartPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPartPosiLimitTopic_mutex);

    uv_async_send(&g_RtnPartPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPartPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryClientPosiLimitTopic(CShfeFtdcRspQryClientPosiLimitField* pRspQryClientPosiLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryClientPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryClientPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryClientPosiLimitField* pNewRspQryClientPosiLimit = NULL;
    if (NULL != pRspQryClientPosiLimit) { 
        pNewRspQryClientPosiLimit = new CShfeFtdcRspQryClientPosiLimitField;
        if (NULL == pNewRspQryClientPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryClientPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryClientPosiLimit,pRspQryClientPosiLimit, sizeof(CShfeFtdcRspQryClientPosiLimitField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryClientPosiLimit;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryClientPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRspQryClientPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryClientPosiLimit->ActionDate: ", pRspQryClientPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->ActionTime: ", pRspQryClientPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->InstrumentID: ", pRspQryClientPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->ClientType: ", pRspQryClientPosiLimit->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->TradingRole: ", pRspQryClientPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->StartTotalPosition: ", pRspQryClientPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->ValueMode: ", pRspQryClientPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->LongPosLimit: ", pRspQryClientPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->ShortPosLimit: ", pRspQryClientPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->UpperLimitPrice: ", pRspQryClientPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimit->LowerLimitPrice: ", pRspQryClientPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryClientPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryClientPosiLimitTopic_IOUser_vec.begin();
        it != g_RspQryClientPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryClientPosiLimitTopic_IOUser_vec.end()) {
        g_RspQryClientPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryClientPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryClientPosiLimitTopic_mutex);

    uv_async_send(&g_RspQryClientPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryClientPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnClientPosiLimitTopic(CShfeFtdcRtnClientPosiLimitField* pRtnClientPosiLimit){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnClientPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnClientPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnClientPosiLimitField* pNewRtnClientPosiLimit = NULL;
    if (NULL != pRtnClientPosiLimit) { 
        pNewRtnClientPosiLimit = new CShfeFtdcRtnClientPosiLimitField;
        if (NULL == pNewRtnClientPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnClientPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnClientPosiLimit,pRtnClientPosiLimit, sizeof(CShfeFtdcRtnClientPosiLimitField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnClientPosiLimit;
    if (NULL == pRtnClientPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRtnClientPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnClientPosiLimit->ActionDate: ", pRtnClientPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->ActionTime: ", pRtnClientPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->InstrumentID: ", pRtnClientPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->ClientType: ", pRtnClientPosiLimit->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->TradingRole: ", pRtnClientPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->StartTotalPosition: ", pRtnClientPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->ValueMode: ", pRtnClientPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->LongPosLimit: ", pRtnClientPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->ShortPosLimit: ", pRtnClientPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->UpperLimitPrice: ", pRtnClientPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimit->LowerLimitPrice: ", pRtnClientPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnClientPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnClientPosiLimitTopic_IOUser_vec.begin();
        it != g_RtnClientPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnClientPosiLimitTopic_IOUser_vec.end()) {
        g_RtnClientPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnClientPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnClientPosiLimitTopic_mutex);

    uv_async_send(&g_RtnClientPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnClientPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySpecialPosiLimitTopic(CShfeFtdcRspQrySpecialPosiLimitField* pRspQrySpecialPosiLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySpecialPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySpecialPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySpecialPosiLimitField* pNewRspQrySpecialPosiLimit = NULL;
    if (NULL != pRspQrySpecialPosiLimit) { 
        pNewRspQrySpecialPosiLimit = new CShfeFtdcRspQrySpecialPosiLimitField;
        if (NULL == pNewRspQrySpecialPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySpecialPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySpecialPosiLimit,pRspQrySpecialPosiLimit, sizeof(CShfeFtdcRspQrySpecialPosiLimitField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySpecialPosiLimit;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySpecialPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySpecialPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySpecialPosiLimit->ActionDate: ", pRspQrySpecialPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->ActionTime: ", pRspQrySpecialPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->InstrumentID: ", pRspQrySpecialPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->ClientID: ", pRspQrySpecialPosiLimit->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->TradingRole: ", pRspQrySpecialPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->StartTotalPosition: ", pRspQrySpecialPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->ValueMode: ", pRspQrySpecialPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->LongPosLimit: ", pRspQrySpecialPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->ShortPosLimit: ", pRspQrySpecialPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->UpperLimitPrice: ", pRspQrySpecialPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecialPosiLimit->LowerLimitPrice: ", pRspQrySpecialPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySpecialPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySpecialPosiLimitTopic_IOUser_vec.begin();
        it != g_RspQrySpecialPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySpecialPosiLimitTopic_IOUser_vec.end()) {
        g_RspQrySpecialPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySpecialPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySpecialPosiLimitTopic_mutex);

    uv_async_send(&g_RspQrySpecialPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySpecialPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSpecialPosiLimitTopic(CShfeFtdcRtnSpecialPosiLimitField* pRtnSpecialPosiLimit){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSpecialPosiLimitTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSpecialPosiLimitTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSpecialPosiLimitField* pNewRtnSpecialPosiLimit = NULL;
    if (NULL != pRtnSpecialPosiLimit) { 
        pNewRtnSpecialPosiLimit = new CShfeFtdcRtnSpecialPosiLimitField;
        if (NULL == pNewRtnSpecialPosiLimit) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSpecialPosiLimit", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSpecialPosiLimit,pRtnSpecialPosiLimit, sizeof(CShfeFtdcRtnSpecialPosiLimitField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSpecialPosiLimit;
    if (NULL == pRtnSpecialPosiLimit) { 
        OutputCallbackMessage("SysUserSpi::pRtnSpecialPosiLimit is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSpecialPosiLimit->ActionDate: ", pRtnSpecialPosiLimit->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->ActionTime: ", pRtnSpecialPosiLimit->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->InstrumentID: ", pRtnSpecialPosiLimit->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->ClientID: ", pRtnSpecialPosiLimit->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->TradingRole: ", pRtnSpecialPosiLimit->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->StartTotalPosition: ", pRtnSpecialPosiLimit->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->ValueMode: ", pRtnSpecialPosiLimit->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->LongPosLimit: ", pRtnSpecialPosiLimit->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->ShortPosLimit: ", pRtnSpecialPosiLimit->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->UpperLimitPrice: ", pRtnSpecialPosiLimit->UpperLimitPrice, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecialPosiLimit->LowerLimitPrice: ", pRtnSpecialPosiLimit->LowerLimitPrice, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSpecialPosiLimitTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSpecialPosiLimitTopic_IOUser_vec.begin();
        it != g_RtnSpecialPosiLimitTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSpecialPosiLimitTopic_IOUser_vec.end()) {
        g_RtnSpecialPosiLimitTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSpecialPosiLimitTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSpecialPosiLimitTopic_mutex);

    uv_async_send(&g_RtnSpecialPosiLimitTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSpecialPosiLimitTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTransactionChgTopic(CShfeFtdcRspQryTransactionChgField* pRspQryTransactionChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTransactionChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTransactionChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTransactionChgField* pNewRspQryTransactionChg = NULL;
    if (NULL != pRspQryTransactionChg) { 
        pNewRspQryTransactionChg = new CShfeFtdcRspQryTransactionChgField;
        if (NULL == pNewRspQryTransactionChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTransactionChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTransactionChg,pRspQryTransactionChg, sizeof(CShfeFtdcRspQryTransactionChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTransactionChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTransactionChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTransactionChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTransactionChg->ActionDate: ", pRspQryTransactionChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTransactionChg->ActionTime: ", pRspQryTransactionChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTransactionChg->BillSN: ", pRspQryTransactionChg->BillSN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTransactionChg->ParticipantAccount: ", pRspQryTransactionChg->ParticipantAccount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTransactionChg->ParticipantID: ", pRspQryTransactionChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTransactionChg->Amount: ", pRspQryTransactionChg->Amount, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTransactionChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTransactionChgTopic_IOUser_vec.begin();
        it != g_RspQryTransactionChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTransactionChgTopic_IOUser_vec.end()) {
        g_RspQryTransactionChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTransactionChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTransactionChgTopic_mutex);

    uv_async_send(&g_RspQryTransactionChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTransactionChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTransactionChgTopic(CShfeFtdcRtnTransactionChgField* pRtnTransactionChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTransactionChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTransactionChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTransactionChgField* pNewRtnTransactionChg = NULL;
    if (NULL != pRtnTransactionChg) { 
        pNewRtnTransactionChg = new CShfeFtdcRtnTransactionChgField;
        if (NULL == pNewRtnTransactionChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTransactionChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTransactionChg,pRtnTransactionChg, sizeof(CShfeFtdcRtnTransactionChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTransactionChg;
    if (NULL == pRtnTransactionChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnTransactionChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTransactionChg->ActionDate: ", pRtnTransactionChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTransactionChg->ActionTime: ", pRtnTransactionChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTransactionChg->BillSN: ", pRtnTransactionChg->BillSN, g_RunningResult_File);
        OutputCallbackMessage("pRtnTransactionChg->ParticipantAccount: ", pRtnTransactionChg->ParticipantAccount, g_RunningResult_File);
        OutputCallbackMessage("pRtnTransactionChg->ParticipantID: ", pRtnTransactionChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTransactionChg->Amount: ", pRtnTransactionChg->Amount, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTransactionChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTransactionChgTopic_IOUser_vec.begin();
        it != g_RtnTransactionChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTransactionChgTopic_IOUser_vec.end()) {
        g_RtnTransactionChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTransactionChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTransactionChgTopic_mutex);

    uv_async_send(&g_RtnTransactionChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTransactionChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryClientChgTopic(CShfeFtdcRspQryClientChgField* pRspQryClientChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryClientChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryClientChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryClientChgField* pNewRspQryClientChg = NULL;
    if (NULL != pRspQryClientChg) { 
        pNewRspQryClientChg = new CShfeFtdcRspQryClientChgField;
        if (NULL == pNewRspQryClientChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryClientChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryClientChg,pRspQryClientChg, sizeof(CShfeFtdcRspQryClientChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryClientChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryClientChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryClientChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryClientChg->ActionDate: ", pRspQryClientChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->ActionTime: ", pRspQryClientChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->ClientID: ", pRspQryClientChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->ClientName: ", pRspQryClientChg->ClientName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->ClientType: ", pRspQryClientChg->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->IsActive: ", pRspQryClientChg->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->IdentifiedCardType: ", pRspQryClientChg->IdentifiedCardType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->IdentifiedCardNo: ", pRspQryClientChg->IdentifiedCardNo, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientChg->OperationType: ", pRspQryClientChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryClientChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryClientChgTopic_IOUser_vec.begin();
        it != g_RspQryClientChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryClientChgTopic_IOUser_vec.end()) {
        g_RspQryClientChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryClientChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryClientChgTopic_mutex);

    uv_async_send(&g_RspQryClientChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryClientChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnClientChgTopic(CShfeFtdcRtnClientChgField* pRtnClientChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnClientChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnClientChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnClientChgField* pNewRtnClientChg = NULL;
    if (NULL != pRtnClientChg) { 
        pNewRtnClientChg = new CShfeFtdcRtnClientChgField;
        if (NULL == pNewRtnClientChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnClientChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnClientChg,pRtnClientChg, sizeof(CShfeFtdcRtnClientChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnClientChg;
    if (NULL == pRtnClientChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnClientChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnClientChg->ActionDate: ", pRtnClientChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->ActionTime: ", pRtnClientChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->ClientID: ", pRtnClientChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->ClientName: ", pRtnClientChg->ClientName, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->ClientType: ", pRtnClientChg->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->IsActive: ", pRtnClientChg->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->IdentifiedCardType: ", pRtnClientChg->IdentifiedCardType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->IdentifiedCardNo: ", pRtnClientChg->IdentifiedCardNo, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientChg->OperationType: ", pRtnClientChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnClientChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnClientChgTopic_IOUser_vec.begin();
        it != g_RtnClientChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnClientChgTopic_IOUser_vec.end()) {
        g_RtnClientChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnClientChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnClientChgTopic_mutex);

    uv_async_send(&g_RtnClientChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnClientChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPartClientChgTopic(CShfeFtdcRspQryPartClientChgField* pRspQryPartClientChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPartClientChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPartClientChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPartClientChgField* pNewRspQryPartClientChg = NULL;
    if (NULL != pRspQryPartClientChg) { 
        pNewRspQryPartClientChg = new CShfeFtdcRspQryPartClientChgField;
        if (NULL == pNewRspQryPartClientChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPartClientChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPartClientChg,pRspQryPartClientChg, sizeof(CShfeFtdcRspQryPartClientChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPartClientChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPartClientChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPartClientChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPartClientChg->ActionDate: ", pRspQryPartClientChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartClientChg->ActionTime: ", pRspQryPartClientChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartClientChg->ClientID: ", pRspQryPartClientChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartClientChg->ParticipantID: ", pRspQryPartClientChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartClientChg->OperationType: ", pRspQryPartClientChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPartClientChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPartClientChgTopic_IOUser_vec.begin();
        it != g_RspQryPartClientChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPartClientChgTopic_IOUser_vec.end()) {
        g_RspQryPartClientChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPartClientChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPartClientChgTopic_mutex);

    uv_async_send(&g_RspQryPartClientChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPartClientChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPartClientChgTopic(CShfeFtdcRtnPartClientChgField* pRtnPartClientChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPartClientChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPartClientChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPartClientChgField* pNewRtnPartClientChg = NULL;
    if (NULL != pRtnPartClientChg) { 
        pNewRtnPartClientChg = new CShfeFtdcRtnPartClientChgField;
        if (NULL == pNewRtnPartClientChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPartClientChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPartClientChg,pRtnPartClientChg, sizeof(CShfeFtdcRtnPartClientChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPartClientChg;
    if (NULL == pRtnPartClientChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnPartClientChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPartClientChg->ActionDate: ", pRtnPartClientChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartClientChg->ActionTime: ", pRtnPartClientChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartClientChg->ClientID: ", pRtnPartClientChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartClientChg->ParticipantID: ", pRtnPartClientChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPartClientChg->OperationType: ", pRtnPartClientChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPartClientChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPartClientChgTopic_IOUser_vec.begin();
        it != g_RtnPartClientChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPartClientChgTopic_IOUser_vec.end()) {
        g_RtnPartClientChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPartClientChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPartClientChgTopic_mutex);

    uv_async_send(&g_RtnPartClientChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPartClientChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPosiLimitChgTopic(CShfeFtdcRspQryPosiLimitChgField* pRspQryPosiLimitChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPosiLimitChgField* pNewRspQryPosiLimitChg = NULL;
    if (NULL != pRspQryPosiLimitChg) { 
        pNewRspQryPosiLimitChg = new CShfeFtdcRspQryPosiLimitChgField;
        if (NULL == pNewRspQryPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPosiLimitChg,pRspQryPosiLimitChg, sizeof(CShfeFtdcRspQryPosiLimitChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPosiLimitChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPosiLimitChg->ActionDate: ", pRspQryPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->ActionTime: ", pRspQryPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->InstrumentID: ", pRspQryPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->ParticipantID: ", pRspQryPosiLimitChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->TradingRole: ", pRspQryPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->StartTotalPosition: ", pRspQryPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->ValueMode: ", pRspQryPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->LongPosLimit: ", pRspQryPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->ShortPosLimit: ", pRspQryPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPosiLimitChg->OperationType: ", pRspQryPosiLimitChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RspQryPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPosiLimitChgTopic_IOUser_vec.end()) {
        g_RspQryPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPosiLimitChgTopic_mutex);

    uv_async_send(&g_RspQryPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPosiLimitChgTopic(CShfeFtdcRtnPosiLimitChgField* pRtnPosiLimitChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPosiLimitChgField* pNewRtnPosiLimitChg = NULL;
    if (NULL != pRtnPosiLimitChg) { 
        pNewRtnPosiLimitChg = new CShfeFtdcRtnPosiLimitChgField;
        if (NULL == pNewRtnPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPosiLimitChg,pRtnPosiLimitChg, sizeof(CShfeFtdcRtnPosiLimitChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPosiLimitChg;
    if (NULL == pRtnPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPosiLimitChg->ActionDate: ", pRtnPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->ActionTime: ", pRtnPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->InstrumentID: ", pRtnPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->ParticipantID: ", pRtnPosiLimitChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->TradingRole: ", pRtnPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->StartTotalPosition: ", pRtnPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->ValueMode: ", pRtnPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->LongPosLimit: ", pRtnPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->ShortPosLimit: ", pRtnPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnPosiLimitChg->OperationType: ", pRtnPosiLimitChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RtnPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPosiLimitChgTopic_IOUser_vec.end()) {
        g_RtnPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPosiLimitChgTopic_mutex);

    uv_async_send(&g_RtnPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHedgeDetailChgTopic(CShfeFtdcRspQryHedgeDetailChgField* pRspQryHedgeDetailChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHedgeDetailChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHedgeDetailChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHedgeDetailChgField* pNewRspQryHedgeDetailChg = NULL;
    if (NULL != pRspQryHedgeDetailChg) { 
        pNewRspQryHedgeDetailChg = new CShfeFtdcRspQryHedgeDetailChgField;
        if (NULL == pNewRspQryHedgeDetailChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHedgeDetailChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHedgeDetailChg,pRspQryHedgeDetailChg, sizeof(CShfeFtdcRspQryHedgeDetailChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHedgeDetailChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHedgeDetailChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHedgeDetailChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHedgeDetailChg->ActionDate: ", pRspQryHedgeDetailChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->ActionTime: ", pRspQryHedgeDetailChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->ParticipantID: ", pRspQryHedgeDetailChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->ClientID: ", pRspQryHedgeDetailChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->OperatorID: ", pRspQryHedgeDetailChg->OperatorID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->Time: ", pRspQryHedgeDetailChg->Time, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->InstrumentID: ", pRspQryHedgeDetailChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->PosiDirection: ", pRspQryHedgeDetailChg->PosiDirection, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->TradingVolume: ", pRspQryHedgeDetailChg->TradingVolume, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->HedgeQuota: ", pRspQryHedgeDetailChg->HedgeQuota, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHedgeDetailChg->OperationType: ", pRspQryHedgeDetailChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHedgeDetailChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHedgeDetailChgTopic_IOUser_vec.begin();
        it != g_RspQryHedgeDetailChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHedgeDetailChgTopic_IOUser_vec.end()) {
        g_RspQryHedgeDetailChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHedgeDetailChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHedgeDetailChgTopic_mutex);

    uv_async_send(&g_RspQryHedgeDetailChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHedgeDetailChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnHedgeDetailChgTopic(CShfeFtdcRtnHedgeDetailChgField* pRtnHedgeDetailChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnHedgeDetailChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnHedgeDetailChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnHedgeDetailChgField* pNewRtnHedgeDetailChg = NULL;
    if (NULL != pRtnHedgeDetailChg) { 
        pNewRtnHedgeDetailChg = new CShfeFtdcRtnHedgeDetailChgField;
        if (NULL == pNewRtnHedgeDetailChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnHedgeDetailChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnHedgeDetailChg,pRtnHedgeDetailChg, sizeof(CShfeFtdcRtnHedgeDetailChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnHedgeDetailChg;
    if (NULL == pRtnHedgeDetailChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnHedgeDetailChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnHedgeDetailChg->ActionDate: ", pRtnHedgeDetailChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->ActionTime: ", pRtnHedgeDetailChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->ParticipantID: ", pRtnHedgeDetailChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->ClientID: ", pRtnHedgeDetailChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->OperatorID: ", pRtnHedgeDetailChg->OperatorID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->Time: ", pRtnHedgeDetailChg->Time, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->InstrumentID: ", pRtnHedgeDetailChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->PosiDirection: ", pRtnHedgeDetailChg->PosiDirection, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->TradingVolume: ", pRtnHedgeDetailChg->TradingVolume, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->HedgeQuota: ", pRtnHedgeDetailChg->HedgeQuota, g_RunningResult_File);
        OutputCallbackMessage("pRtnHedgeDetailChg->OperationType: ", pRtnHedgeDetailChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnHedgeDetailChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnHedgeDetailChgTopic_IOUser_vec.begin();
        it != g_RtnHedgeDetailChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnHedgeDetailChgTopic_IOUser_vec.end()) {
        g_RtnHedgeDetailChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnHedgeDetailChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnHedgeDetailChgTopic_mutex);

    uv_async_send(&g_RtnHedgeDetailChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnHedgeDetailChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryParticipantChgTopic(CShfeFtdcRspQryParticipantChgField* pRspQryParticipantChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryParticipantChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryParticipantChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryParticipantChgField* pNewRspQryParticipantChg = NULL;
    if (NULL != pRspQryParticipantChg) { 
        pNewRspQryParticipantChg = new CShfeFtdcRspQryParticipantChgField;
        if (NULL == pNewRspQryParticipantChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryParticipantChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryParticipantChg,pRspQryParticipantChg, sizeof(CShfeFtdcRspQryParticipantChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryParticipantChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryParticipantChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryParticipantChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryParticipantChg->ActionDate: ", pRspQryParticipantChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->ActionTime: ", pRspQryParticipantChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->ParticipantID: ", pRspQryParticipantChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->ParticipantName: ", pRspQryParticipantChg->ParticipantName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->ParticipantAbbr: ", pRspQryParticipantChg->ParticipantAbbr, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->MemberType: ", pRspQryParticipantChg->MemberType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->IsActive: ", pRspQryParticipantChg->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticipantChg->OperationType: ", pRspQryParticipantChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryParticipantChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryParticipantChgTopic_IOUser_vec.begin();
        it != g_RspQryParticipantChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryParticipantChgTopic_IOUser_vec.end()) {
        g_RspQryParticipantChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryParticipantChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryParticipantChgTopic_mutex);

    uv_async_send(&g_RspQryParticipantChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryParticipantChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnParticipantChgTopic(CShfeFtdcRtnParticipantChgField* pRtnParticipantChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnParticipantChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnParticipantChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnParticipantChgField* pNewRtnParticipantChg = NULL;
    if (NULL != pRtnParticipantChg) { 
        pNewRtnParticipantChg = new CShfeFtdcRtnParticipantChgField;
        if (NULL == pNewRtnParticipantChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnParticipantChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnParticipantChg,pRtnParticipantChg, sizeof(CShfeFtdcRtnParticipantChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnParticipantChg;
    if (NULL == pRtnParticipantChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnParticipantChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnParticipantChg->ActionDate: ", pRtnParticipantChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->ActionTime: ", pRtnParticipantChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->ParticipantID: ", pRtnParticipantChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->ParticipantName: ", pRtnParticipantChg->ParticipantName, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->ParticipantAbbr: ", pRtnParticipantChg->ParticipantAbbr, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->MemberType: ", pRtnParticipantChg->MemberType, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->IsActive: ", pRtnParticipantChg->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticipantChg->OperationType: ", pRtnParticipantChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnParticipantChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnParticipantChgTopic_IOUser_vec.begin();
        it != g_RtnParticipantChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnParticipantChgTopic_IOUser_vec.end()) {
        g_RtnParticipantChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnParticipantChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnParticipantChgTopic_mutex);

    uv_async_send(&g_RtnParticipantChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnParticipantChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryMarginRateChgTopic(CShfeFtdcRspQryMarginRateChgField* pRspQryMarginRateChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryMarginRateChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryMarginRateChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryMarginRateChgField* pNewRspQryMarginRateChg = NULL;
    if (NULL != pRspQryMarginRateChg) { 
        pNewRspQryMarginRateChg = new CShfeFtdcRspQryMarginRateChgField;
        if (NULL == pNewRspQryMarginRateChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryMarginRateChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryMarginRateChg,pRspQryMarginRateChg, sizeof(CShfeFtdcRspQryMarginRateChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryMarginRateChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryMarginRateChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryMarginRateChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryMarginRateChg->ActionDate: ", pRspQryMarginRateChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->ActionTime: ", pRspQryMarginRateChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->InstrumentID: ", pRspQryMarginRateChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->ParticipantID: ", pRspQryMarginRateChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->TradingRole: ", pRspQryMarginRateChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->HedgeFlag: ", pRspQryMarginRateChg->HedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->ValueMode: ", pRspQryMarginRateChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->LongMarginRatio: ", pRspQryMarginRateChg->LongMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->ShortMarginRatio: ", pRspQryMarginRateChg->ShortMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMarginRateChg->OperationType: ", pRspQryMarginRateChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryMarginRateChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryMarginRateChgTopic_IOUser_vec.begin();
        it != g_RspQryMarginRateChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryMarginRateChgTopic_IOUser_vec.end()) {
        g_RspQryMarginRateChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryMarginRateChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryMarginRateChgTopic_mutex);

    uv_async_send(&g_RspQryMarginRateChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryMarginRateChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnMarginRateChgTopic(CShfeFtdcRtnMarginRateChgField* pRtnMarginRateChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnMarginRateChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnMarginRateChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnMarginRateChgField* pNewRtnMarginRateChg = NULL;
    if (NULL != pRtnMarginRateChg) { 
        pNewRtnMarginRateChg = new CShfeFtdcRtnMarginRateChgField;
        if (NULL == pNewRtnMarginRateChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnMarginRateChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnMarginRateChg,pRtnMarginRateChg, sizeof(CShfeFtdcRtnMarginRateChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnMarginRateChg;
    if (NULL == pRtnMarginRateChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnMarginRateChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnMarginRateChg->ActionDate: ", pRtnMarginRateChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->ActionTime: ", pRtnMarginRateChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->InstrumentID: ", pRtnMarginRateChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->ParticipantID: ", pRtnMarginRateChg->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->TradingRole: ", pRtnMarginRateChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->HedgeFlag: ", pRtnMarginRateChg->HedgeFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->ValueMode: ", pRtnMarginRateChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->LongMarginRatio: ", pRtnMarginRateChg->LongMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->ShortMarginRatio: ", pRtnMarginRateChg->ShortMarginRatio, g_RunningResult_File);
        OutputCallbackMessage("pRtnMarginRateChg->OperationType: ", pRtnMarginRateChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnMarginRateChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnMarginRateChgTopic_IOUser_vec.begin();
        it != g_RtnMarginRateChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnMarginRateChgTopic_IOUser_vec.end()) {
        g_RtnMarginRateChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnMarginRateChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnMarginRateChgTopic_mutex);

    uv_async_send(&g_RtnMarginRateChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnMarginRateChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryUserIpChgTopic(CShfeFtdcRspQryUserIpChgField* pRspQryUserIpChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryUserIpChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryUserIpChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryUserIpChgField* pNewRspQryUserIpChg = NULL;
    if (NULL != pRspQryUserIpChg) { 
        pNewRspQryUserIpChg = new CShfeFtdcRspQryUserIpChgField;
        if (NULL == pNewRspQryUserIpChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryUserIpChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryUserIpChg,pRspQryUserIpChg, sizeof(CShfeFtdcRspQryUserIpChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryUserIpChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryUserIpChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryUserIpChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryUserIpChg->ActionDate: ", pRspQryUserIpChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserIpChg->ActionTime: ", pRspQryUserIpChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserIpChg->UserID: ", pRspQryUserIpChg->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserIpChg->IPAddress: ", pRspQryUserIpChg->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserIpChg->IPMask: ", pRspQryUserIpChg->IPMask, g_RunningResult_File);
        OutputCallbackMessage("pRspQryUserIpChg->OperationType: ", pRspQryUserIpChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryUserIpChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryUserIpChgTopic_IOUser_vec.begin();
        it != g_RspQryUserIpChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryUserIpChgTopic_IOUser_vec.end()) {
        g_RspQryUserIpChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryUserIpChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryUserIpChgTopic_mutex);

    uv_async_send(&g_RspQryUserIpChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryUserIpChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnUserIpChgTopic(CShfeFtdcRtnUserIpChgField* pRtnUserIpChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnUserIpChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnUserIpChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnUserIpChgField* pNewRtnUserIpChg = NULL;
    if (NULL != pRtnUserIpChg) { 
        pNewRtnUserIpChg = new CShfeFtdcRtnUserIpChgField;
        if (NULL == pNewRtnUserIpChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnUserIpChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnUserIpChg,pRtnUserIpChg, sizeof(CShfeFtdcRtnUserIpChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnUserIpChg;
    if (NULL == pRtnUserIpChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnUserIpChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnUserIpChg->ActionDate: ", pRtnUserIpChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserIpChg->ActionTime: ", pRtnUserIpChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserIpChg->UserID: ", pRtnUserIpChg->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserIpChg->IPAddress: ", pRtnUserIpChg->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserIpChg->IPMask: ", pRtnUserIpChg->IPMask, g_RunningResult_File);
        OutputCallbackMessage("pRtnUserIpChg->OperationType: ", pRtnUserIpChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnUserIpChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnUserIpChgTopic_IOUser_vec.begin();
        it != g_RtnUserIpChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnUserIpChgTopic_IOUser_vec.end()) {
        g_RtnUserIpChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnUserIpChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnUserIpChgTopic_mutex);

    uv_async_send(&g_RtnUserIpChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnUserIpChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryClientPosiLimitChgTopic(CShfeFtdcRspQryClientPosiLimitChgField* pRspQryClientPosiLimitChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryClientPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryClientPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryClientPosiLimitChgField* pNewRspQryClientPosiLimitChg = NULL;
    if (NULL != pRspQryClientPosiLimitChg) { 
        pNewRspQryClientPosiLimitChg = new CShfeFtdcRspQryClientPosiLimitChgField;
        if (NULL == pNewRspQryClientPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryClientPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryClientPosiLimitChg,pRspQryClientPosiLimitChg, sizeof(CShfeFtdcRspQryClientPosiLimitChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryClientPosiLimitChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryClientPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryClientPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryClientPosiLimitChg->ActionDate: ", pRspQryClientPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->ActionTime: ", pRspQryClientPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->InstrumentID: ", pRspQryClientPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->ClientType: ", pRspQryClientPosiLimitChg->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->TradingRole: ", pRspQryClientPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->StartTotalPosition: ", pRspQryClientPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->ValueMode: ", pRspQryClientPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->LongPosLimit: ", pRspQryClientPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->ShortPosLimit: ", pRspQryClientPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientPosiLimitChg->OperationType: ", pRspQryClientPosiLimitChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryClientPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryClientPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RspQryClientPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryClientPosiLimitChgTopic_IOUser_vec.end()) {
        g_RspQryClientPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryClientPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryClientPosiLimitChgTopic_mutex);

    uv_async_send(&g_RspQryClientPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryClientPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnClientPosiLimitChgTopic(CShfeFtdcRtnClientPosiLimitChgField* pRtnClientPosiLimitChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnClientPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnClientPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnClientPosiLimitChgField* pNewRtnClientPosiLimitChg = NULL;
    if (NULL != pRtnClientPosiLimitChg) { 
        pNewRtnClientPosiLimitChg = new CShfeFtdcRtnClientPosiLimitChgField;
        if (NULL == pNewRtnClientPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnClientPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnClientPosiLimitChg,pRtnClientPosiLimitChg, sizeof(CShfeFtdcRtnClientPosiLimitChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnClientPosiLimitChg;
    if (NULL == pRtnClientPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnClientPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnClientPosiLimitChg->ActionDate: ", pRtnClientPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->ActionTime: ", pRtnClientPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->InstrumentID: ", pRtnClientPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->ClientType: ", pRtnClientPosiLimitChg->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->TradingRole: ", pRtnClientPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->StartTotalPosition: ", pRtnClientPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->ValueMode: ", pRtnClientPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->LongPosLimit: ", pRtnClientPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->ShortPosLimit: ", pRtnClientPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientPosiLimitChg->OperationType: ", pRtnClientPosiLimitChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnClientPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnClientPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RtnClientPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnClientPosiLimitChgTopic_IOUser_vec.end()) {
        g_RtnClientPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnClientPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnClientPosiLimitChgTopic_mutex);

    uv_async_send(&g_RtnClientPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnClientPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySpecPosiLimitChgTopic(CShfeFtdcRspQrySpecPosiLimitChgField* pRspQrySpecPosiLimitChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySpecPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySpecPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySpecPosiLimitChgField* pNewRspQrySpecPosiLimitChg = NULL;
    if (NULL != pRspQrySpecPosiLimitChg) { 
        pNewRspQrySpecPosiLimitChg = new CShfeFtdcRspQrySpecPosiLimitChgField;
        if (NULL == pNewRspQrySpecPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySpecPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySpecPosiLimitChg,pRspQrySpecPosiLimitChg, sizeof(CShfeFtdcRspQrySpecPosiLimitChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySpecPosiLimitChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySpecPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySpecPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->ActionDate: ", pRspQrySpecPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->ActionTime: ", pRspQrySpecPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->InstrumentID: ", pRspQrySpecPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->ClientID: ", pRspQrySpecPosiLimitChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->TradingRole: ", pRspQrySpecPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->StartTotalPosition: ", pRspQrySpecPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->ValueMode: ", pRspQrySpecPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->LongPosLimit: ", pRspQrySpecPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->ShortPosLimit: ", pRspQrySpecPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySpecPosiLimitChg->OperationType: ", pRspQrySpecPosiLimitChg->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySpecPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySpecPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RspQrySpecPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySpecPosiLimitChgTopic_IOUser_vec.end()) {
        g_RspQrySpecPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySpecPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySpecPosiLimitChgTopic_mutex);

    uv_async_send(&g_RspQrySpecPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySpecPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSpecPosiLimitChgTopic(CShfeFtdcRtnSpecPosiLimitChgField* pRtnSpecPosiLimitChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSpecPosiLimitChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSpecPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSpecPosiLimitChgField* pNewRtnSpecPosiLimitChg = NULL;
    if (NULL != pRtnSpecPosiLimitChg) { 
        pNewRtnSpecPosiLimitChg = new CShfeFtdcRtnSpecPosiLimitChgField;
        if (NULL == pNewRtnSpecPosiLimitChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSpecPosiLimitChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSpecPosiLimitChg,pRtnSpecPosiLimitChg, sizeof(CShfeFtdcRtnSpecPosiLimitChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSpecPosiLimitChg;
    if (NULL == pRtnSpecPosiLimitChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnSpecPosiLimitChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSpecPosiLimitChg->ActionDate: ", pRtnSpecPosiLimitChg->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->ActionTime: ", pRtnSpecPosiLimitChg->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->InstrumentID: ", pRtnSpecPosiLimitChg->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->ClientID: ", pRtnSpecPosiLimitChg->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->TradingRole: ", pRtnSpecPosiLimitChg->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->StartTotalPosition: ", pRtnSpecPosiLimitChg->StartTotalPosition, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->ValueMode: ", pRtnSpecPosiLimitChg->ValueMode, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->LongPosLimit: ", pRtnSpecPosiLimitChg->LongPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->ShortPosLimit: ", pRtnSpecPosiLimitChg->ShortPosLimit, g_RunningResult_File);
        OutputCallbackMessage("pRtnSpecPosiLimitChg->OperationType: ", pRtnSpecPosiLimitChg->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSpecPosiLimitChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSpecPosiLimitChgTopic_IOUser_vec.begin();
        it != g_RtnSpecPosiLimitChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSpecPosiLimitChgTopic_IOUser_vec.end()) {
        g_RtnSpecPosiLimitChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSpecPosiLimitChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSpecPosiLimitChgTopic_mutex);

    uv_async_send(&g_RtnSpecPosiLimitChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSpecPosiLimitChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHistoryObjectAttrTopic(CShfeFtdcRspQryHistoryObjectAttrField* pRspQryHistoryObjectAttr, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHistoryObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHistoryObjectAttrField* pNewRspQryHistoryObjectAttr = NULL;
    if (NULL != pRspQryHistoryObjectAttr) { 
        pNewRspQryHistoryObjectAttr = new CShfeFtdcRspQryHistoryObjectAttrField;
        if (NULL == pNewRspQryHistoryObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHistoryObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHistoryObjectAttr,pRspQryHistoryObjectAttr, sizeof(CShfeFtdcRspQryHistoryObjectAttrField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHistoryObjectAttr;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHistoryObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHistoryObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHistoryObjectAttr->MonDate: ", pRspQryHistoryObjectAttr->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->BeginTime: ", pRspQryHistoryObjectAttr->BeginTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->EndTime: ", pRspQryHistoryObjectAttr->EndTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->ObjectID: ", pRspQryHistoryObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->AttrType: ", pRspQryHistoryObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->ValueType: ", pRspQryHistoryObjectAttr->ValueType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->FirstValue: ", pRspQryHistoryObjectAttr->FirstValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->EndValue: ", pRspQryHistoryObjectAttr->EndValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->AvgValue: ", pRspQryHistoryObjectAttr->AvgValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->MinValue: ", pRspQryHistoryObjectAttr->MinValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->MaxValue: ", pRspQryHistoryObjectAttr->MaxValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryObjectAttr->ValueCount: ", pRspQryHistoryObjectAttr->ValueCount, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHistoryObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHistoryObjectAttrTopic_IOUser_vec.begin();
        it != g_RspQryHistoryObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHistoryObjectAttrTopic_IOUser_vec.end()) {
        g_RspQryHistoryObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHistoryObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHistoryObjectAttrTopic_mutex);

    uv_async_send(&g_RspQryHistoryObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnHistoryObjectAttrTopic(CShfeFtdcRtnHistoryObjectAttrField* pRtnHistoryObjectAttr){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnHistoryObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnHistoryObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnHistoryObjectAttrField* pNewRtnHistoryObjectAttr = NULL;
    if (NULL != pRtnHistoryObjectAttr) { 
        pNewRtnHistoryObjectAttr = new CShfeFtdcRtnHistoryObjectAttrField;
        if (NULL == pNewRtnHistoryObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnHistoryObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnHistoryObjectAttr,pRtnHistoryObjectAttr, sizeof(CShfeFtdcRtnHistoryObjectAttrField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnHistoryObjectAttr;
    if (NULL == pRtnHistoryObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRtnHistoryObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnHistoryObjectAttr->MonDate: ", pRtnHistoryObjectAttr->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->BeginTime: ", pRtnHistoryObjectAttr->BeginTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->EndTime: ", pRtnHistoryObjectAttr->EndTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->ObjectID: ", pRtnHistoryObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->AttrType: ", pRtnHistoryObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->ValueType: ", pRtnHistoryObjectAttr->ValueType, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->FirstValue: ", pRtnHistoryObjectAttr->FirstValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->EndValue: ", pRtnHistoryObjectAttr->EndValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->AvgValue: ", pRtnHistoryObjectAttr->AvgValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->MinValue: ", pRtnHistoryObjectAttr->MinValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->MaxValue: ", pRtnHistoryObjectAttr->MaxValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryObjectAttr->ValueCount: ", pRtnHistoryObjectAttr->ValueCount, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnHistoryObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnHistoryObjectAttrTopic_IOUser_vec.begin();
        it != g_RtnHistoryObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnHistoryObjectAttrTopic_IOUser_vec.end()) {
        g_RtnHistoryObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnHistoryObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnHistoryObjectAttrTopic_mutex);

    uv_async_send(&g_RtnHistoryObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnHistoryObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFrontInfoTopic(CShfeFtdcRspQryFrontInfoField* pRspQryFrontInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFrontInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFrontInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFrontInfoField* pNewRspQryFrontInfo = NULL;
    if (NULL != pRspQryFrontInfo) { 
        pNewRspQryFrontInfo = new CShfeFtdcRspQryFrontInfoField;
        if (NULL == pNewRspQryFrontInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFrontInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFrontInfo,pRspQryFrontInfo, sizeof(CShfeFtdcRspQryFrontInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFrontInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFrontInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFrontInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFrontInfo->MonDate: ", pRspQryFrontInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontInfo->MonTime: ", pRspQryFrontInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontInfo->FrontId: ", pRspQryFrontInfo->FrontId, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontInfo->RspCondition: ", pRspQryFrontInfo->RspCondition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontInfo->ReqCount: ", pRspQryFrontInfo->ReqCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontInfo->ReqRate: ", pRspQryFrontInfo->ReqRate, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFrontInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFrontInfoTopic_IOUser_vec.begin();
        it != g_RspQryFrontInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFrontInfoTopic_IOUser_vec.end()) {
        g_RspQryFrontInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFrontInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFrontInfoTopic_mutex);

    uv_async_send(&g_RspQryFrontInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFrontInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFrontInfoTopic(CShfeFtdcRtnFrontInfoField* pRtnFrontInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFrontInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFrontInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFrontInfoField* pNewRtnFrontInfo = NULL;
    if (NULL != pRtnFrontInfo) { 
        pNewRtnFrontInfo = new CShfeFtdcRtnFrontInfoField;
        if (NULL == pNewRtnFrontInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFrontInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFrontInfo,pRtnFrontInfo, sizeof(CShfeFtdcRtnFrontInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFrontInfo;
    if (NULL == pRtnFrontInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnFrontInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFrontInfo->MonDate: ", pRtnFrontInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontInfo->MonTime: ", pRtnFrontInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontInfo->FrontId: ", pRtnFrontInfo->FrontId, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontInfo->RspCondition: ", pRtnFrontInfo->RspCondition, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontInfo->ReqCount: ", pRtnFrontInfo->ReqCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontInfo->ReqRate: ", pRtnFrontInfo->ReqRate, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFrontInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFrontInfoTopic_IOUser_vec.begin();
        it != g_RtnFrontInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFrontInfoTopic_IOUser_vec.end()) {
        g_RtnFrontInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFrontInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFrontInfoTopic_mutex);

    uv_async_send(&g_RtnFrontInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFrontInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySysUserLoginTopic(CShfeFtdcRspQrySysUserLoginField* pRspQrySysUserLogin, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySysUserLoginTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserLoginTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySysUserLoginField* pNewRspQrySysUserLogin = NULL;
    if (NULL != pRspQrySysUserLogin) { 
        pNewRspQrySysUserLogin = new CShfeFtdcRspQrySysUserLoginField;
        if (NULL == pNewRspQrySysUserLogin) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySysUserLogin", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySysUserLogin,pRspQrySysUserLogin, sizeof(CShfeFtdcRspQrySysUserLoginField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySysUserLogin;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySysUserLogin) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySysUserLogin is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySysUserLogin->UserID: ", pRspQrySysUserLogin->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserLogin->TradingDay: ", pRspQrySysUserLogin->TradingDay, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserLogin->LoginTime: ", pRspQrySysUserLogin->LoginTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserLogin->Privilege: ", pRspQrySysUserLogin->Privilege, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserLogin->VersionFlag: ", pRspQrySysUserLogin->VersionFlag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySysUserLoginTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySysUserLoginTopic_IOUser_vec.begin();
        it != g_RspQrySysUserLoginTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySysUserLoginTopic_IOUser_vec.end()) {
        g_RspQrySysUserLoginTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySysUserLoginTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySysUserLoginTopic_mutex);

    uv_async_send(&g_RspQrySysUserLoginTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserLoginTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySysUserLogoutTopic(CShfeFtdcRspQrySysUserLogoutField* pRspQrySysUserLogout, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySysUserLogoutTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserLogoutTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySysUserLogoutField* pNewRspQrySysUserLogout = NULL;
    if (NULL != pRspQrySysUserLogout) { 
        pNewRspQrySysUserLogout = new CShfeFtdcRspQrySysUserLogoutField;
        if (NULL == pNewRspQrySysUserLogout) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySysUserLogout", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySysUserLogout,pRspQrySysUserLogout, sizeof(CShfeFtdcRspQrySysUserLogoutField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySysUserLogout;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySysUserLogout) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySysUserLogout is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySysUserLogout->UserID: ", pRspQrySysUserLogout->UserID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySysUserLogoutTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySysUserLogoutTopic_IOUser_vec.begin();
        it != g_RspQrySysUserLogoutTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySysUserLogoutTopic_IOUser_vec.end()) {
        g_RspQrySysUserLogoutTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySysUserLogoutTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySysUserLogoutTopic_mutex);

    uv_async_send(&g_RspQrySysUserLogoutTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserLogoutTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySysUserPasswordUpdateTopic(CShfeFtdcRspQrySysUserPasswordUpdateField* pRspQrySysUserPasswordUpdate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySysUserPasswordUpdateTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserPasswordUpdateTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySysUserPasswordUpdateField* pNewRspQrySysUserPasswordUpdate = NULL;
    if (NULL != pRspQrySysUserPasswordUpdate) { 
        pNewRspQrySysUserPasswordUpdate = new CShfeFtdcRspQrySysUserPasswordUpdateField;
        if (NULL == pNewRspQrySysUserPasswordUpdate) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySysUserPasswordUpdate", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySysUserPasswordUpdate,pRspQrySysUserPasswordUpdate, sizeof(CShfeFtdcRspQrySysUserPasswordUpdateField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySysUserPasswordUpdate;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySysUserPasswordUpdate) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySysUserPasswordUpdate is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySysUserPasswordUpdate->UserID: ", pRspQrySysUserPasswordUpdate->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserPasswordUpdate->PasswordChgMsg: ", pRspQrySysUserPasswordUpdate->PasswordChgMsg, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySysUserPasswordUpdateTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySysUserPasswordUpdateTopic_IOUser_vec.begin();
        it != g_RspQrySysUserPasswordUpdateTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySysUserPasswordUpdateTopic_IOUser_vec.end()) {
        g_RspQrySysUserPasswordUpdateTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySysUserPasswordUpdateTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySysUserPasswordUpdateTopic_mutex);

    uv_async_send(&g_RspQrySysUserPasswordUpdateTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserPasswordUpdateTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySysUserRegisterTopic(CShfeFtdcRspQrySysUserRegisterField* pRspQrySysUserRegister, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySysUserRegisterTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserRegisterTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySysUserRegisterField* pNewRspQrySysUserRegister = NULL;
    if (NULL != pRspQrySysUserRegister) { 
        pNewRspQrySysUserRegister = new CShfeFtdcRspQrySysUserRegisterField;
        if (NULL == pNewRspQrySysUserRegister) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySysUserRegister", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySysUserRegister,pRspQrySysUserRegister, sizeof(CShfeFtdcRspQrySysUserRegisterField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySysUserRegister;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySysUserRegister) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySysUserRegister is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySysUserRegister->UserID: ", pRspQrySysUserRegister->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySysUserRegister->Privilege: ", pRspQrySysUserRegister->Privilege, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySysUserRegisterTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySysUserRegisterTopic_IOUser_vec.begin();
        it != g_RspQrySysUserRegisterTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySysUserRegisterTopic_IOUser_vec.end()) {
        g_RspQrySysUserRegisterTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySysUserRegisterTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySysUserRegisterTopic_mutex);

    uv_async_send(&g_RspQrySysUserRegisterTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserRegisterTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySysUserDeleteTopic(CShfeFtdcRspQrySysUserDeleteField* pRspQrySysUserDelete, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySysUserDeleteTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserDeleteTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySysUserDeleteField* pNewRspQrySysUserDelete = NULL;
    if (NULL != pRspQrySysUserDelete) { 
        pNewRspQrySysUserDelete = new CShfeFtdcRspQrySysUserDeleteField;
        if (NULL == pNewRspQrySysUserDelete) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySysUserDelete", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySysUserDelete,pRspQrySysUserDelete, sizeof(CShfeFtdcRspQrySysUserDeleteField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySysUserDelete;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySysUserDelete) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySysUserDelete is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySysUserDelete->UserID: ", pRspQrySysUserDelete->UserID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySysUserDeleteTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySysUserDeleteTopic_IOUser_vec.begin();
        it != g_RspQrySysUserDeleteTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySysUserDeleteTopic_IOUser_vec.end()) {
        g_RspQrySysUserDeleteTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySysUserDeleteTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySysUserDeleteTopic_mutex);

    uv_async_send(&g_RspQrySysUserDeleteTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySysUserDeleteTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradeLogTopic(CShfeFtdcRspQryTradeLogField* pRspQryTradeLog, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradeLogTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradeLogTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradeLogField* pNewRspQryTradeLog = NULL;
    if (NULL != pRspQryTradeLog) { 
        pNewRspQryTradeLog = new CShfeFtdcRspQryTradeLogField;
        if (NULL == pNewRspQryTradeLog) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradeLog", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradeLog,pRspQryTradeLog, sizeof(CShfeFtdcRspQryTradeLogField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradeLog;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradeLog) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradeLog is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradeLog->bFlag: ", pRspQryTradeLog->bFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeLog->TradeLogStr: ", pRspQryTradeLog->TradeLogStr, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradeLogTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradeLogTopic_IOUser_vec.begin();
        it != g_RspQryTradeLogTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradeLogTopic_IOUser_vec.end()) {
        g_RspQryTradeLogTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradeLogTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradeLogTopic_mutex);

    uv_async_send(&g_RspQryTradeLogTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradeLogTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTradeLogTopic(CShfeFtdcRtnTradeLogField* pRtnTradeLog){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTradeLogTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTradeLogTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTradeLogField* pNewRtnTradeLog = NULL;
    if (NULL != pRtnTradeLog) { 
        pNewRtnTradeLog = new CShfeFtdcRtnTradeLogField;
        if (NULL == pNewRtnTradeLog) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTradeLog", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTradeLog,pRtnTradeLog, sizeof(CShfeFtdcRtnTradeLogField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTradeLog;
    if (NULL == pRtnTradeLog) { 
        OutputCallbackMessage("SysUserSpi::pRtnTradeLog is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTradeLog->bFlag: ", pRtnTradeLog->bFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeLog->TradeLogStr: ", pRtnTradeLog->TradeLogStr, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTradeLogTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTradeLogTopic_IOUser_vec.begin();
        it != g_RtnTradeLogTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTradeLogTopic_IOUser_vec.end()) {
        g_RtnTradeLogTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTradeLogTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTradeLogTopic_mutex);

    uv_async_send(&g_RtnTradeLogTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTradeLogTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradeUserLoginInfoTopic(CShfeFtdcRspQryTradeUserLoginInfoField* pRspQryTradeUserLoginInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradeUserLoginInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradeUserLoginInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradeUserLoginInfoField* pNewRspQryTradeUserLoginInfo = NULL;
    if (NULL != pRspQryTradeUserLoginInfo) { 
        pNewRspQryTradeUserLoginInfo = new CShfeFtdcRspQryTradeUserLoginInfoField;
        if (NULL == pNewRspQryTradeUserLoginInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradeUserLoginInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradeUserLoginInfo,pRspQryTradeUserLoginInfo, sizeof(CShfeFtdcRspQryTradeUserLoginInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradeUserLoginInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradeUserLoginInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradeUserLoginInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ObjectID: ", pRspQryTradeUserLoginInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->UserID: ", pRspQryTradeUserLoginInfo->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ParticipantID: ", pRspQryTradeUserLoginInfo->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ProtocolInfo: ", pRspQryTradeUserLoginInfo->ProtocolInfo, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->IPAddress: ", pRspQryTradeUserLoginInfo->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->FrontID: ", pRspQryTradeUserLoginInfo->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->UserType: ", pRspQryTradeUserLoginInfo->UserType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->AccessType: ", pRspQryTradeUserLoginInfo->AccessType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ActionDate: ", pRspQryTradeUserLoginInfo->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ActionTime: ", pRspQryTradeUserLoginInfo->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->ActionFlag: ", pRspQryTradeUserLoginInfo->ActionFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginInfo->DataCenter: ", pRspQryTradeUserLoginInfo->DataCenter, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradeUserLoginInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradeUserLoginInfoTopic_IOUser_vec.begin();
        it != g_RspQryTradeUserLoginInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradeUserLoginInfoTopic_IOUser_vec.end()) {
        g_RspQryTradeUserLoginInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradeUserLoginInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradeUserLoginInfoTopic_mutex);

    uv_async_send(&g_RspQryTradeUserLoginInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradeUserLoginInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTradeUserLoginInfoTopic(CShfeFtdcRtnTradeUserLoginInfoField* pRtnTradeUserLoginInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTradeUserLoginInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTradeUserLoginInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTradeUserLoginInfoField* pNewRtnTradeUserLoginInfo = NULL;
    if (NULL != pRtnTradeUserLoginInfo) { 
        pNewRtnTradeUserLoginInfo = new CShfeFtdcRtnTradeUserLoginInfoField;
        if (NULL == pNewRtnTradeUserLoginInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTradeUserLoginInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTradeUserLoginInfo,pRtnTradeUserLoginInfo, sizeof(CShfeFtdcRtnTradeUserLoginInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTradeUserLoginInfo;
    if (NULL == pRtnTradeUserLoginInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnTradeUserLoginInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ObjectID: ", pRtnTradeUserLoginInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->UserID: ", pRtnTradeUserLoginInfo->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ParticipantID: ", pRtnTradeUserLoginInfo->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ProtocolInfo: ", pRtnTradeUserLoginInfo->ProtocolInfo, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->IPAddress: ", pRtnTradeUserLoginInfo->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->FrontID: ", pRtnTradeUserLoginInfo->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->UserType: ", pRtnTradeUserLoginInfo->UserType, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->AccessType: ", pRtnTradeUserLoginInfo->AccessType, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ActionDate: ", pRtnTradeUserLoginInfo->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ActionTime: ", pRtnTradeUserLoginInfo->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->ActionFlag: ", pRtnTradeUserLoginInfo->ActionFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeUserLoginInfo->DataCenter: ", pRtnTradeUserLoginInfo->DataCenter, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTradeUserLoginInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTradeUserLoginInfoTopic_IOUser_vec.begin();
        it != g_RtnTradeUserLoginInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTradeUserLoginInfoTopic_IOUser_vec.end()) {
        g_RtnTradeUserLoginInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTradeUserLoginInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTradeUserLoginInfoTopic_mutex);

    uv_async_send(&g_RtnTradeUserLoginInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTradeUserLoginInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPartTradeTopic(CShfeFtdcRspQryPartTradeField* pRspQryPartTrade, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPartTradeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPartTradeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPartTradeField* pNewRspQryPartTrade = NULL;
    if (NULL != pRspQryPartTrade) { 
        pNewRspQryPartTrade = new CShfeFtdcRspQryPartTradeField;
        if (NULL == pNewRspQryPartTrade) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPartTrade", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPartTrade,pRspQryPartTrade, sizeof(CShfeFtdcRspQryPartTradeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPartTrade;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPartTrade) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPartTrade is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPartTrade->ActionDate: ", pRspQryPartTrade->ActionDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->ActionTime: ", pRspQryPartTrade->ActionTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->InstrumentID: ", pRspQryPartTrade->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->ParticipantID: ", pRspQryPartTrade->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalPositiveOrder: ", pRspQryPartTrade->TotalPositiveOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalNegativeOrder: ", pRspQryPartTrade->TotalNegativeOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalPositiveTrade: ", pRspQryPartTrade->TotalPositiveTrade, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalNegativeTrade: ", pRspQryPartTrade->TotalNegativeTrade, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalPositivePosi: ", pRspQryPartTrade->TotalPositivePosi, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->TotalNegativePosi: ", pRspQryPartTrade->TotalNegativePosi, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPartTrade->OperationType: ", pRspQryPartTrade->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPartTradeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPartTradeTopic_IOUser_vec.begin();
        it != g_RspQryPartTradeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPartTradeTopic_IOUser_vec.end()) {
        g_RspQryPartTradeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPartTradeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPartTradeTopic_mutex);

    uv_async_send(&g_RspQryPartTradeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPartTradeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradepeakTopic(CShfeFtdcRspQryTradepeakField* pRspQryTradepeak, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradepeakTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradepeakTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradepeakField* pNewRspQryTradepeak = NULL;
    if (NULL != pRspQryTradepeak) { 
        pNewRspQryTradepeak = new CShfeFtdcRspQryTradepeakField;
        if (NULL == pNewRspQryTradepeak) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradepeak", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradepeak,pRspQryTradepeak, sizeof(CShfeFtdcRspQryTradepeakField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradepeak;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradepeak) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradepeak is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradepeak->TradepeakFlag: ", pRspQryTradepeak->TradepeakFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->PeakTime: ", pRspQryTradepeak->PeakTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->InsertOrder: ", pRspQryTradepeak->InsertOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->ActionOrder: ", pRspQryTradepeak->ActionOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->InvalidOrder: ", pRspQryTradepeak->InvalidOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->TotalBusiness: ", pRspQryTradepeak->TotalBusiness, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->TradeCount: ", pRspQryTradepeak->TradeCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradepeak->TotalCount: ", pRspQryTradepeak->TotalCount, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradepeakTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradepeakTopic_IOUser_vec.begin();
        it != g_RspQryTradepeakTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradepeakTopic_IOUser_vec.end()) {
        g_RspQryTradepeakTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradepeakTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradepeakTopic_mutex);

    uv_async_send(&g_RspQryTradepeakTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradepeakTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHistoryCpuInfoTopic(CShfeFtdcRspQryHistoryCpuInfoField* pRspQryHistoryCpuInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHistoryCpuInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryCpuInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHistoryCpuInfoField* pNewRspQryHistoryCpuInfo = NULL;
    if (NULL != pRspQryHistoryCpuInfo) { 
        pNewRspQryHistoryCpuInfo = new CShfeFtdcRspQryHistoryCpuInfoField;
        if (NULL == pNewRspQryHistoryCpuInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHistoryCpuInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHistoryCpuInfo,pRspQryHistoryCpuInfo, sizeof(CShfeFtdcRspQryHistoryCpuInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHistoryCpuInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHistoryCpuInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHistoryCpuInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHistoryCpuInfo->HostName: ", pRspQryHistoryCpuInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->MonDate: ", pRspQryHistoryCpuInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->MonTime: ", pRspQryHistoryCpuInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->CPU: ", pRspQryHistoryCpuInfo->CPU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->LOAD: ", pRspQryHistoryCpuInfo->LOAD, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->USER: ", pRspQryHistoryCpuInfo->USER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->NICE: ", pRspQryHistoryCpuInfo->NICE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->SYS: ", pRspQryHistoryCpuInfo->SYS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->IDLE: ", pRspQryHistoryCpuInfo->IDLE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->BLOCK: ", pRspQryHistoryCpuInfo->BLOCK, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->SWAIT: ", pRspQryHistoryCpuInfo->SWAIT, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->INTR: ", pRspQryHistoryCpuInfo->INTR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryCpuInfo->SSYS: ", pRspQryHistoryCpuInfo->SSYS, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHistoryCpuInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHistoryCpuInfoTopic_IOUser_vec.begin();
        it != g_RspQryHistoryCpuInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHistoryCpuInfoTopic_IOUser_vec.end()) {
        g_RspQryHistoryCpuInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHistoryCpuInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHistoryCpuInfoTopic_mutex);

    uv_async_send(&g_RspQryHistoryCpuInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryCpuInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHistoryMemInfoTopic(CShfeFtdcRspQryHistoryMemInfoField* pRspQryHistoryMemInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHistoryMemInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryMemInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHistoryMemInfoField* pNewRspQryHistoryMemInfo = NULL;
    if (NULL != pRspQryHistoryMemInfo) { 
        pNewRspQryHistoryMemInfo = new CShfeFtdcRspQryHistoryMemInfoField;
        if (NULL == pNewRspQryHistoryMemInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHistoryMemInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHistoryMemInfo,pRspQryHistoryMemInfo, sizeof(CShfeFtdcRspQryHistoryMemInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHistoryMemInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHistoryMemInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHistoryMemInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHistoryMemInfo->HostName: ", pRspQryHistoryMemInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->MonDate: ", pRspQryHistoryMemInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->MonTime: ", pRspQryHistoryMemInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->TOTALREAL: ", pRspQryHistoryMemInfo->TOTALREAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->ACTIVEREAL: ", pRspQryHistoryMemInfo->ACTIVEREAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->TOTALVIRTUAL: ", pRspQryHistoryMemInfo->TOTALVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->ACTIVEVIRTUAL: ", pRspQryHistoryMemInfo->ACTIVEVIRTUAL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryMemInfo->FREE: ", pRspQryHistoryMemInfo->FREE, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHistoryMemInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHistoryMemInfoTopic_IOUser_vec.begin();
        it != g_RspQryHistoryMemInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHistoryMemInfoTopic_IOUser_vec.end()) {
        g_RspQryHistoryMemInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHistoryMemInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHistoryMemInfoTopic_mutex);

    uv_async_send(&g_RspQryHistoryMemInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryMemInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHistoryNetworkInfoTopic(CShfeFtdcRspQryHistoryNetworkInfoField* pRspQryHistoryNetworkInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHistoryNetworkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryNetworkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHistoryNetworkInfoField* pNewRspQryHistoryNetworkInfo = NULL;
    if (NULL != pRspQryHistoryNetworkInfo) { 
        pNewRspQryHistoryNetworkInfo = new CShfeFtdcRspQryHistoryNetworkInfoField;
        if (NULL == pNewRspQryHistoryNetworkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHistoryNetworkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHistoryNetworkInfo,pRspQryHistoryNetworkInfo, sizeof(CShfeFtdcRspQryHistoryNetworkInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHistoryNetworkInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHistoryNetworkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHistoryNetworkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->HostName: ", pRspQryHistoryNetworkInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->MonDate: ", pRspQryHistoryNetworkInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->MonTime: ", pRspQryHistoryNetworkInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->LANNAME: ", pRspQryHistoryNetworkInfo->LANNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->LANSTATUS: ", pRspQryHistoryNetworkInfo->LANSTATUS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->IPADDRESS: ", pRspQryHistoryNetworkInfo->IPADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->RECVBYTES: ", pRspQryHistoryNetworkInfo->RECVBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->RECVPACKETS: ", pRspQryHistoryNetworkInfo->RECVPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->RECVERRORPACKETS: ", pRspQryHistoryNetworkInfo->RECVERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->RECVDROPPACKETS: ", pRspQryHistoryNetworkInfo->RECVDROPPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->SENDBYTES: ", pRspQryHistoryNetworkInfo->SENDBYTES, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->SENDPACKETS: ", pRspQryHistoryNetworkInfo->SENDPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->SENDERRORPACKETS: ", pRspQryHistoryNetworkInfo->SENDERRORPACKETS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryNetworkInfo->SENDDROPPACKETS: ", pRspQryHistoryNetworkInfo->SENDDROPPACKETS, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHistoryNetworkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHistoryNetworkInfoTopic_IOUser_vec.begin();
        it != g_RspQryHistoryNetworkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHistoryNetworkInfoTopic_IOUser_vec.end()) {
        g_RspQryHistoryNetworkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHistoryNetworkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHistoryNetworkInfoTopic_mutex);

    uv_async_send(&g_RspQryHistoryNetworkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryNetworkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryMonitorOnlineUser(CShfeFtdcRspQryMonitorOnlineUserField* pRspQryMonitorOnlineUser, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryMonitorOnlineUser: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryMonitorOnlineUser: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryMonitorOnlineUserField* pNewRspQryMonitorOnlineUser = NULL;
    if (NULL != pRspQryMonitorOnlineUser) { 
        pNewRspQryMonitorOnlineUser = new CShfeFtdcRspQryMonitorOnlineUserField;
        if (NULL == pNewRspQryMonitorOnlineUser) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryMonitorOnlineUser", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryMonitorOnlineUser,pRspQryMonitorOnlineUser, sizeof(CShfeFtdcRspQryMonitorOnlineUserField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryMonitorOnlineUser;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryMonitorOnlineUser) { 
        OutputCallbackMessage("SysUserSpi::pRspQryMonitorOnlineUser is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryMonitorOnlineUser->UserID: ", pRspQryMonitorOnlineUser->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMonitorOnlineUser->IPAddress: ", pRspQryMonitorOnlineUser->IPAddress, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryMonitorOnlineUser_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryMonitorOnlineUser_IOUser_vec.begin();
        it != g_RspQryMonitorOnlineUser_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryMonitorOnlineUser_IOUser_vec.end()) {
        g_RspQryMonitorOnlineUser_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryMonitorOnlineUser_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryMonitorOnlineUser_mutex);

    uv_async_send(&g_RspQryMonitorOnlineUser_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryMonitorOnlineUser: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFrontStat(CShfeFtdcRspQryFrontStatField* pRspQryFrontStat, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFrontStat: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFrontStat: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFrontStatField* pNewRspQryFrontStat = NULL;
    if (NULL != pRspQryFrontStat) { 
        pNewRspQryFrontStat = new CShfeFtdcRspQryFrontStatField;
        if (NULL == pNewRspQryFrontStat) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFrontStat", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFrontStat,pRspQryFrontStat, sizeof(CShfeFtdcRspQryFrontStatField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFrontStat;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFrontStat) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFrontStat is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFrontStat->FrontID: ", pRspQryFrontStat->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->PositiveOrder: ", pRspQryFrontStat->PositiveOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->NegativeOrder: ", pRspQryFrontStat->NegativeOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->TotalPositiveOrder: ", pRspQryFrontStat->TotalPositiveOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->TotalNegativeOrder: ", pRspQryFrontStat->TotalNegativeOrder, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->OrderAction: ", pRspQryFrontStat->OrderAction, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontStat->TotalOrderAction: ", pRspQryFrontStat->TotalOrderAction, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFrontStat_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFrontStat_IOUser_vec.begin();
        it != g_RspQryFrontStat_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFrontStat_IOUser_vec.end()) {
        g_RspQryFrontStat_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFrontStat_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFrontStat_mutex);

    uv_async_send(&g_RspQryFrontStat_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFrontStat: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSysTimeSyncTopic(CShfeFtdcRtnSysTimeSyncField* pRtnSysTimeSync){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSysTimeSyncTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSysTimeSyncTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSysTimeSyncField* pNewRtnSysTimeSync = NULL;
    if (NULL != pRtnSysTimeSync) { 
        pNewRtnSysTimeSync = new CShfeFtdcRtnSysTimeSyncField;
        if (NULL == pNewRtnSysTimeSync) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSysTimeSync", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSysTimeSync,pRtnSysTimeSync, sizeof(CShfeFtdcRtnSysTimeSyncField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSysTimeSync;
    if (NULL == pRtnSysTimeSync) { 
        OutputCallbackMessage("SysUserSpi::pRtnSysTimeSync is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSysTimeSync->MonDate: ", pRtnSysTimeSync->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSysTimeSync->MonTime: ", pRtnSysTimeSync->MonTime, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSysTimeSyncTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSysTimeSyncTopic_IOUser_vec.begin();
        it != g_RtnSysTimeSyncTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSysTimeSyncTopic_IOUser_vec.end()) {
        g_RtnSysTimeSyncTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSysTimeSyncTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSysTimeSyncTopic_mutex);

    uv_async_send(&g_RtnSysTimeSyncTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSysTimeSyncTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnDataCenterChgTopic(CShfeFtdcRtnDataCenterChgField* pRtnDataCenterChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnDataCenterChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnDataCenterChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnDataCenterChgField* pNewRtnDataCenterChg = NULL;
    if (NULL != pRtnDataCenterChg) { 
        pNewRtnDataCenterChg = new CShfeFtdcRtnDataCenterChgField;
        if (NULL == pNewRtnDataCenterChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnDataCenterChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnDataCenterChg,pRtnDataCenterChg, sizeof(CShfeFtdcRtnDataCenterChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnDataCenterChg;
    if (NULL == pRtnDataCenterChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnDataCenterChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnDataCenterChg->DataCenterID: ", pRtnDataCenterChg->DataCenterID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnDataCenterChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnDataCenterChgTopic_IOUser_vec.begin();
        it != g_RtnDataCenterChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnDataCenterChgTopic_IOUser_vec.end()) {
        g_RtnDataCenterChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnDataCenterChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnDataCenterChgTopic_mutex);

    uv_async_send(&g_RtnDataCenterChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnDataCenterChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryHistoryTradePeakTopic(CShfeFtdcRspQryHistoryTradePeakField* pRspQryHistoryTradePeak, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryHistoryTradePeakTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryTradePeakTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryHistoryTradePeakField* pNewRspQryHistoryTradePeak = NULL;
    if (NULL != pRspQryHistoryTradePeak) { 
        pNewRspQryHistoryTradePeak = new CShfeFtdcRspQryHistoryTradePeakField;
        if (NULL == pNewRspQryHistoryTradePeak) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryHistoryTradePeak", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryHistoryTradePeak,pRspQryHistoryTradePeak, sizeof(CShfeFtdcRspQryHistoryTradePeakField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryHistoryTradePeak;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryHistoryTradePeak) { 
        OutputCallbackMessage("SysUserSpi::pRspQryHistoryTradePeak is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryHistoryTradePeak->ObjectID: ", pRspQryHistoryTradePeak->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MonDate: ", pRspQryHistoryTradePeak->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MonTime: ", pRspQryHistoryTradePeak->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->AttrType: ", pRspQryHistoryTradePeak->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->AttrValue: ", pRspQryHistoryTradePeak->AttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->RltAttrType: ", pRspQryHistoryTradePeak->RltAttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->RltAttrValue: ", pRspQryHistoryTradePeak->RltAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MaxMonDate: ", pRspQryHistoryTradePeak->MaxMonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MaxMonTime: ", pRspQryHistoryTradePeak->MaxMonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MaxAttrValue: ", pRspQryHistoryTradePeak->MaxAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->MaxRltAttrValue: ", pRspQryHistoryTradePeak->MaxRltAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->OldMonDate: ", pRspQryHistoryTradePeak->OldMonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->OldMonTime: ", pRspQryHistoryTradePeak->OldMonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->OldAttrValue: ", pRspQryHistoryTradePeak->OldAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryHistoryTradePeak->OldRltAttrValue: ", pRspQryHistoryTradePeak->OldRltAttrValue, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryHistoryTradePeakTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryHistoryTradePeakTopic_IOUser_vec.begin();
        it != g_RspQryHistoryTradePeakTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryHistoryTradePeakTopic_IOUser_vec.end()) {
        g_RspQryHistoryTradePeakTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryHistoryTradePeakTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryHistoryTradePeakTopic_mutex);

    uv_async_send(&g_RspQryHistoryTradePeakTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryHistoryTradePeakTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnHistoryTradePeakTopic(CShfeFtdcRtnHistoryTradePeakField* pRtnHistoryTradePeak){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnHistoryTradePeakTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnHistoryTradePeakTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnHistoryTradePeakField* pNewRtnHistoryTradePeak = NULL;
    if (NULL != pRtnHistoryTradePeak) { 
        pNewRtnHistoryTradePeak = new CShfeFtdcRtnHistoryTradePeakField;
        if (NULL == pNewRtnHistoryTradePeak) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnHistoryTradePeak", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnHistoryTradePeak,pRtnHistoryTradePeak, sizeof(CShfeFtdcRtnHistoryTradePeakField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnHistoryTradePeak;
    if (NULL == pRtnHistoryTradePeak) { 
        OutputCallbackMessage("SysUserSpi::pRtnHistoryTradePeak is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnHistoryTradePeak->ObjectID: ", pRtnHistoryTradePeak->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MonDate: ", pRtnHistoryTradePeak->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MonTime: ", pRtnHistoryTradePeak->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->AttrType: ", pRtnHistoryTradePeak->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->AttrValue: ", pRtnHistoryTradePeak->AttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->RltAttrType: ", pRtnHistoryTradePeak->RltAttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->RltAttrValue: ", pRtnHistoryTradePeak->RltAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MaxMonDate: ", pRtnHistoryTradePeak->MaxMonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MaxMonTime: ", pRtnHistoryTradePeak->MaxMonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MaxAttrValue: ", pRtnHistoryTradePeak->MaxAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->MaxRltAttrValue: ", pRtnHistoryTradePeak->MaxRltAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->OldMonDate: ", pRtnHistoryTradePeak->OldMonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->OldMonTime: ", pRtnHistoryTradePeak->OldMonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->OldAttrValue: ", pRtnHistoryTradePeak->OldAttrValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnHistoryTradePeak->OldRltAttrValue: ", pRtnHistoryTradePeak->OldRltAttrValue, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnHistoryTradePeakTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnHistoryTradePeakTopic_IOUser_vec.begin();
        it != g_RtnHistoryTradePeakTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnHistoryTradePeakTopic_IOUser_vec.end()) {
        g_RtnHistoryTradePeakTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnHistoryTradePeakTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnHistoryTradePeakTopic_mutex);

    uv_async_send(&g_RtnHistoryTradePeakTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnHistoryTradePeakTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySyslogEventTopic(CShfeFtdcRspQrySyslogEventField* pRspQrySyslogEvent, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySyslogEventTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySyslogEventTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySyslogEventField* pNewRspQrySyslogEvent = NULL;
    if (NULL != pRspQrySyslogEvent) { 
        pNewRspQrySyslogEvent = new CShfeFtdcRspQrySyslogEventField;
        if (NULL == pNewRspQrySyslogEvent) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySyslogEvent", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySyslogEvent,pRspQrySyslogEvent, sizeof(CShfeFtdcRspQrySyslogEventField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySyslogEvent;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySyslogEvent) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySyslogEvent is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySyslogEvent->MonDate: ", pRspQrySyslogEvent->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->MonTime: ", pRspQrySyslogEvent->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->OccurDate: ", pRspQrySyslogEvent->OccurDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->OccurTime: ", pRspQrySyslogEvent->OccurTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EvendID: ", pRspQrySyslogEvent->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->ObjectID: ", pRspQrySyslogEvent->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->IPAddress: ", pRspQrySyslogEvent->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventName: ", pRspQrySyslogEvent->EventName, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventNum: ", pRspQrySyslogEvent->EventNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventType: ", pRspQrySyslogEvent->EventType, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventDes: ", pRspQrySyslogEvent->EventDes, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->ProcessFlag: ", pRspQrySyslogEvent->ProcessFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->WarningLevel: ", pRspQrySyslogEvent->WarningLevel, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventDealDes: ", pRspQrySyslogEvent->EventDealDes, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->FullEventName: ", pRspQrySyslogEvent->FullEventName, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySyslogEvent->EventCount: ", pRspQrySyslogEvent->EventCount, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySyslogEventTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySyslogEventTopic_IOUser_vec.begin();
        it != g_RspQrySyslogEventTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySyslogEventTopic_IOUser_vec.end()) {
        g_RspQrySyslogEventTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySyslogEventTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySyslogEventTopic_mutex);

    uv_async_send(&g_RspQrySyslogEventTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySyslogEventTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSyslogEventTopic(CShfeFtdcRtnSyslogEventField* pRtnSyslogEvent){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSyslogEventTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSyslogEventTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSyslogEventField* pNewRtnSyslogEvent = NULL;
    if (NULL != pRtnSyslogEvent) { 
        pNewRtnSyslogEvent = new CShfeFtdcRtnSyslogEventField;
        if (NULL == pNewRtnSyslogEvent) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSyslogEvent", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSyslogEvent,pRtnSyslogEvent, sizeof(CShfeFtdcRtnSyslogEventField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSyslogEvent;
    if (NULL == pRtnSyslogEvent) { 
        OutputCallbackMessage("SysUserSpi::pRtnSyslogEvent is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSyslogEvent->MonDate: ", pRtnSyslogEvent->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->MonTime: ", pRtnSyslogEvent->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->OccurDate: ", pRtnSyslogEvent->OccurDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->OccurTime: ", pRtnSyslogEvent->OccurTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EvendID: ", pRtnSyslogEvent->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->ObjectID: ", pRtnSyslogEvent->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->IPAddress: ", pRtnSyslogEvent->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EventName: ", pRtnSyslogEvent->EventName, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EventNum: ", pRtnSyslogEvent->EventNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EventType: ", pRtnSyslogEvent->EventType, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EventDes: ", pRtnSyslogEvent->EventDes, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->ProcessFlag: ", pRtnSyslogEvent->ProcessFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->WarningLevel: ", pRtnSyslogEvent->WarningLevel, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->EventDealDes: ", pRtnSyslogEvent->EventDealDes, g_RunningResult_File);
        OutputCallbackMessage("pRtnSyslogEvent->FullEventName: ", pRtnSyslogEvent->FullEventName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSyslogEventTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSyslogEventTopic_IOUser_vec.begin();
        it != g_RtnSyslogEventTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSyslogEventTopic_IOUser_vec.end()) {
        g_RtnSyslogEventTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSyslogEventTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSyslogEventTopic_mutex);

    uv_async_send(&g_RtnSyslogEventTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSyslogEventTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryWebAppInfoTopic(CShfeFtdcRspQryWebAppInfoField* pRspQryWebAppInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryWebAppInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryWebAppInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryWebAppInfoField* pNewRspQryWebAppInfo = NULL;
    if (NULL != pRspQryWebAppInfo) { 
        pNewRspQryWebAppInfo = new CShfeFtdcRspQryWebAppInfoField;
        if (NULL == pNewRspQryWebAppInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryWebAppInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryWebAppInfo,pRspQryWebAppInfo, sizeof(CShfeFtdcRspQryWebAppInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryWebAppInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryWebAppInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryWebAppInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryWebAppInfo->ObjectID: ", pRspQryWebAppInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->MonDate: ", pRspQryWebAppInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->MonTime: ", pRspQryWebAppInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->AppName: ", pRspQryWebAppInfo->AppName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->Status: ", pRspQryWebAppInfo->Status, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->Desc: ", pRspQryWebAppInfo->Desc, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->StartTime: ", pRspQryWebAppInfo->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->ServletNum: ", pRspQryWebAppInfo->ServletNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->ProcessTime: ", pRspQryWebAppInfo->ProcessTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->RequestNum: ", pRspQryWebAppInfo->RequestNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->ErrorNum: ", pRspQryWebAppInfo->ErrorNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->SessionSize: ", pRspQryWebAppInfo->SessionSize, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->TimeOut: ", pRspQryWebAppInfo->TimeOut, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->JDBCUsage: ", pRspQryWebAppInfo->JDBCUsage, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWebAppInfo->JSPNum: ", pRspQryWebAppInfo->JSPNum, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryWebAppInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryWebAppInfoTopic_IOUser_vec.begin();
        it != g_RspQryWebAppInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryWebAppInfoTopic_IOUser_vec.end()) {
        g_RspQryWebAppInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryWebAppInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryWebAppInfoTopic_mutex);

    uv_async_send(&g_RspQryWebAppInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryWebAppInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnWebAppInfoTopic(CShfeFtdcRtnWebAppInfoField* pRtnWebAppInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnWebAppInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnWebAppInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnWebAppInfoField* pNewRtnWebAppInfo = NULL;
    if (NULL != pRtnWebAppInfo) { 
        pNewRtnWebAppInfo = new CShfeFtdcRtnWebAppInfoField;
        if (NULL == pNewRtnWebAppInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnWebAppInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnWebAppInfo,pRtnWebAppInfo, sizeof(CShfeFtdcRtnWebAppInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnWebAppInfo;
    if (NULL == pRtnWebAppInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnWebAppInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnWebAppInfo->ObjectID: ", pRtnWebAppInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->MonDate: ", pRtnWebAppInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->MonTime: ", pRtnWebAppInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->AppName: ", pRtnWebAppInfo->AppName, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->Status: ", pRtnWebAppInfo->Status, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->Desc: ", pRtnWebAppInfo->Desc, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->StartTime: ", pRtnWebAppInfo->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->ServletNum: ", pRtnWebAppInfo->ServletNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->ProcessTime: ", pRtnWebAppInfo->ProcessTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->RequestNum: ", pRtnWebAppInfo->RequestNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->ErrorNum: ", pRtnWebAppInfo->ErrorNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->SessionSize: ", pRtnWebAppInfo->SessionSize, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->TimeOut: ", pRtnWebAppInfo->TimeOut, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->JDBCUsage: ", pRtnWebAppInfo->JDBCUsage, g_RunningResult_File);
        OutputCallbackMessage("pRtnWebAppInfo->JSPNum: ", pRtnWebAppInfo->JSPNum, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnWebAppInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnWebAppInfoTopic_IOUser_vec.begin();
        it != g_RtnWebAppInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnWebAppInfoTopic_IOUser_vec.end()) {
        g_RtnWebAppInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnWebAppInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnWebAppInfoTopic_mutex);

    uv_async_send(&g_RtnWebAppInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnWebAppInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryServletInfoTopic(CShfeFtdcRspQryServletInfoField* pRspQryServletInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryServletInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryServletInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryServletInfoField* pNewRspQryServletInfo = NULL;
    if (NULL != pRspQryServletInfo) { 
        pNewRspQryServletInfo = new CShfeFtdcRspQryServletInfoField;
        if (NULL == pNewRspQryServletInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryServletInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryServletInfo,pRspQryServletInfo, sizeof(CShfeFtdcRspQryServletInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryServletInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryServletInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryServletInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryServletInfo->ObjectID: ", pRspQryServletInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->MonDate: ", pRspQryServletInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->MonTime: ", pRspQryServletInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->Name: ", pRspQryServletInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->LoadTime: ", pRspQryServletInfo->LoadTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->RequestNum: ", pRspQryServletInfo->RequestNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->RequestErrNum: ", pRspQryServletInfo->RequestErrNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->ProcessTime: ", pRspQryServletInfo->ProcessTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->MixTime: ", pRspQryServletInfo->MixTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryServletInfo->MaxTime: ", pRspQryServletInfo->MaxTime, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryServletInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryServletInfoTopic_IOUser_vec.begin();
        it != g_RspQryServletInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryServletInfoTopic_IOUser_vec.end()) {
        g_RspQryServletInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryServletInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryServletInfoTopic_mutex);

    uv_async_send(&g_RspQryServletInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryServletInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnServletInfoTopic(CShfeFtdcRtnServletInfoField* pRtnServletInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnServletInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnServletInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnServletInfoField* pNewRtnServletInfo = NULL;
    if (NULL != pRtnServletInfo) { 
        pNewRtnServletInfo = new CShfeFtdcRtnServletInfoField;
        if (NULL == pNewRtnServletInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnServletInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnServletInfo,pRtnServletInfo, sizeof(CShfeFtdcRtnServletInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnServletInfo;
    if (NULL == pRtnServletInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnServletInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnServletInfo->ObjectID: ", pRtnServletInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->MonDate: ", pRtnServletInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->MonTime: ", pRtnServletInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->Name: ", pRtnServletInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->LoadTime: ", pRtnServletInfo->LoadTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->RequestNum: ", pRtnServletInfo->RequestNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->RequestErrNum: ", pRtnServletInfo->RequestErrNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->ProcessTime: ", pRtnServletInfo->ProcessTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->MixTime: ", pRtnServletInfo->MixTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnServletInfo->MaxTime: ", pRtnServletInfo->MaxTime, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnServletInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnServletInfoTopic_IOUser_vec.begin();
        it != g_RtnServletInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnServletInfoTopic_IOUser_vec.end()) {
        g_RtnServletInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnServletInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnServletInfoTopic_mutex);

    uv_async_send(&g_RtnServletInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnServletInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFileInfoTopic(CShfeFtdcRspQryFileInfoField* pRspQryFileInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFileInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFileInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFileInfoField* pNewRspQryFileInfo = NULL;
    if (NULL != pRspQryFileInfo) { 
        pNewRspQryFileInfo = new CShfeFtdcRspQryFileInfoField;
        if (NULL == pNewRspQryFileInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFileInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFileInfo,pRspQryFileInfo, sizeof(CShfeFtdcRspQryFileInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFileInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFileInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFileInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFileInfo->ObjectID: ", pRspQryFileInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->MonDate: ", pRspQryFileInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->MonTime: ", pRspQryFileInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->PathName: ", pRspQryFileInfo->PathName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->FileSize: ", pRspQryFileInfo->FileSize, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->LastModDate: ", pRspQryFileInfo->LastModDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileInfo->FileType: ", pRspQryFileInfo->FileType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFileInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFileInfoTopic_IOUser_vec.begin();
        it != g_RspQryFileInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFileInfoTopic_IOUser_vec.end()) {
        g_RspQryFileInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFileInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFileInfoTopic_mutex);

    uv_async_send(&g_RspQryFileInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFileInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFileInfoTopic(CShfeFtdcRtnFileInfoField* pRtnFileInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFileInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFileInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFileInfoField* pNewRtnFileInfo = NULL;
    if (NULL != pRtnFileInfo) { 
        pNewRtnFileInfo = new CShfeFtdcRtnFileInfoField;
        if (NULL == pNewRtnFileInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFileInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFileInfo,pRtnFileInfo, sizeof(CShfeFtdcRtnFileInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFileInfo;
    if (NULL == pRtnFileInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnFileInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFileInfo->ObjectID: ", pRtnFileInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->MonDate: ", pRtnFileInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->MonTime: ", pRtnFileInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->PathName: ", pRtnFileInfo->PathName, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->FileSize: ", pRtnFileInfo->FileSize, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->LastModDate: ", pRtnFileInfo->LastModDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileInfo->FileType: ", pRtnFileInfo->FileType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFileInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFileInfoTopic_IOUser_vec.begin();
        it != g_RtnFileInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFileInfoTopic_IOUser_vec.end()) {
        g_RtnFileInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFileInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFileInfoTopic_mutex);

    uv_async_send(&g_RtnFileInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFileInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQrySessionInfoTopic(CShfeFtdcRspQrySessionInfoField* pRspQrySessionInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQrySessionInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQrySessionInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQrySessionInfoField* pNewRspQrySessionInfo = NULL;
    if (NULL != pRspQrySessionInfo) { 
        pNewRspQrySessionInfo = new CShfeFtdcRspQrySessionInfoField;
        if (NULL == pNewRspQrySessionInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQrySessionInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQrySessionInfo,pRspQrySessionInfo, sizeof(CShfeFtdcRspQrySessionInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQrySessionInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQrySessionInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQrySessionInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQrySessionInfo->ObjectID: ", pRspQrySessionInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->MonDate: ", pRspQrySessionInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->MonTime: ", pRspQrySessionInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->SessionID: ", pRspQrySessionInfo->SessionID, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->SessionName: ", pRspQrySessionInfo->SessionName, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->RemoteIP: ", pRspQrySessionInfo->RemoteIP, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->BeginTime: ", pRspQrySessionInfo->BeginTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->LatestTime: ", pRspQrySessionInfo->LatestTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQrySessionInfo->MaxIdleTime: ", pRspQrySessionInfo->MaxIdleTime, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQrySessionInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQrySessionInfoTopic_IOUser_vec.begin();
        it != g_RspQrySessionInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQrySessionInfoTopic_IOUser_vec.end()) {
        g_RspQrySessionInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQrySessionInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQrySessionInfoTopic_mutex);

    uv_async_send(&g_RspQrySessionInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQrySessionInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnSessionInfoTopic(CShfeFtdcRtnSessionInfoField* pRtnSessionInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnSessionInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnSessionInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnSessionInfoField* pNewRtnSessionInfo = NULL;
    if (NULL != pRtnSessionInfo) { 
        pNewRtnSessionInfo = new CShfeFtdcRtnSessionInfoField;
        if (NULL == pNewRtnSessionInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnSessionInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnSessionInfo,pRtnSessionInfo, sizeof(CShfeFtdcRtnSessionInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnSessionInfo;
    if (NULL == pRtnSessionInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnSessionInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnSessionInfo->ObjectID: ", pRtnSessionInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->MonDate: ", pRtnSessionInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->MonTime: ", pRtnSessionInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->SessionID: ", pRtnSessionInfo->SessionID, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->SessionName: ", pRtnSessionInfo->SessionName, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->RemoteIP: ", pRtnSessionInfo->RemoteIP, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->BeginTime: ", pRtnSessionInfo->BeginTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->LatestTime: ", pRtnSessionInfo->LatestTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnSessionInfo->MaxIdleTime: ", pRtnSessionInfo->MaxIdleTime, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnSessionInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnSessionInfoTopic_IOUser_vec.begin();
        it != g_RtnSessionInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnSessionInfoTopic_IOUser_vec.end()) {
        g_RtnSessionInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnSessionInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnSessionInfoTopic_mutex);

    uv_async_send(&g_RtnSessionInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnSessionInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryJDBCInfoTopic(CShfeFtdcRspQryJDBCInfoField* pRspQryJDBCInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryJDBCInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryJDBCInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryJDBCInfoField* pNewRspQryJDBCInfo = NULL;
    if (NULL != pRspQryJDBCInfo) { 
        pNewRspQryJDBCInfo = new CShfeFtdcRspQryJDBCInfoField;
        if (NULL == pNewRspQryJDBCInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryJDBCInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryJDBCInfo,pRspQryJDBCInfo, sizeof(CShfeFtdcRspQryJDBCInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryJDBCInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryJDBCInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryJDBCInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryJDBCInfo->ObjectID: ", pRspQryJDBCInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->MonDate: ", pRspQryJDBCInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->MonTime: ", pRspQryJDBCInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->AppName: ", pRspQryJDBCInfo->AppName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->Name: ", pRspQryJDBCInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->Usage: ", pRspQryJDBCInfo->Usage, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->ConnNumMax: ", pRspQryJDBCInfo->ConnNumMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->ConnNumFree: ", pRspQryJDBCInfo->ConnNumFree, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->ConnNumUnRU: ", pRspQryJDBCInfo->ConnNumUnRU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->ConnNumRU: ", pRspQryJDBCInfo->ConnNumRU, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->UserName: ", pRspQryJDBCInfo->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->Type: ", pRspQryJDBCInfo->Type, g_RunningResult_File);
        OutputCallbackMessage("pRspQryJDBCInfo->URL: ", pRspQryJDBCInfo->URL, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryJDBCInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryJDBCInfoTopic_IOUser_vec.begin();
        it != g_RspQryJDBCInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryJDBCInfoTopic_IOUser_vec.end()) {
        g_RspQryJDBCInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryJDBCInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryJDBCInfoTopic_mutex);

    uv_async_send(&g_RspQryJDBCInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryJDBCInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnJDBCInfoTopic(CShfeFtdcRtnJDBCInfoField* pRtnJDBCInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnJDBCInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnJDBCInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnJDBCInfoField* pNewRtnJDBCInfo = NULL;
    if (NULL != pRtnJDBCInfo) { 
        pNewRtnJDBCInfo = new CShfeFtdcRtnJDBCInfoField;
        if (NULL == pNewRtnJDBCInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnJDBCInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnJDBCInfo,pRtnJDBCInfo, sizeof(CShfeFtdcRtnJDBCInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnJDBCInfo;
    if (NULL == pRtnJDBCInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnJDBCInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnJDBCInfo->ObjectID: ", pRtnJDBCInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->MonDate: ", pRtnJDBCInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->MonTime: ", pRtnJDBCInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->AppName: ", pRtnJDBCInfo->AppName, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->Name: ", pRtnJDBCInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->Usage: ", pRtnJDBCInfo->Usage, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->ConnNumMax: ", pRtnJDBCInfo->ConnNumMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->ConnNumFree: ", pRtnJDBCInfo->ConnNumFree, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->ConnNumUnRU: ", pRtnJDBCInfo->ConnNumUnRU, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->ConnNumRU: ", pRtnJDBCInfo->ConnNumRU, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->UserName: ", pRtnJDBCInfo->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->Type: ", pRtnJDBCInfo->Type, g_RunningResult_File);
        OutputCallbackMessage("pRtnJDBCInfo->URL: ", pRtnJDBCInfo->URL, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnJDBCInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnJDBCInfoTopic_IOUser_vec.begin();
        it != g_RtnJDBCInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnJDBCInfoTopic_IOUser_vec.end()) {
        g_RtnJDBCInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnJDBCInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnJDBCInfoTopic_mutex);

    uv_async_send(&g_RtnJDBCInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnJDBCInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryThreadInfoTopic(CShfeFtdcRspQryThreadInfoField* pRspQryThreadInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryThreadInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryThreadInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryThreadInfoField* pNewRspQryThreadInfo = NULL;
    if (NULL != pRspQryThreadInfo) { 
        pNewRspQryThreadInfo = new CShfeFtdcRspQryThreadInfoField;
        if (NULL == pNewRspQryThreadInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryThreadInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryThreadInfo,pRspQryThreadInfo, sizeof(CShfeFtdcRspQryThreadInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryThreadInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryThreadInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryThreadInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryThreadInfo->ObjectID: ", pRspQryThreadInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->MonDate: ", pRspQryThreadInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->MonTime: ", pRspQryThreadInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->Name: ", pRspQryThreadInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->ThreadNum: ", pRspQryThreadInfo->ThreadNum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->ThreadStatus: ", pRspQryThreadInfo->ThreadStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->InNative: ", pRspQryThreadInfo->InNative, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->Suspended: ", pRspQryThreadInfo->Suspended, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->BlockCount: ", pRspQryThreadInfo->BlockCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->WaitCount: ", pRspQryThreadInfo->WaitCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->CpuTime: ", pRspQryThreadInfo->CpuTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryThreadInfo->UserTime: ", pRspQryThreadInfo->UserTime, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryThreadInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryThreadInfoTopic_IOUser_vec.begin();
        it != g_RspQryThreadInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryThreadInfoTopic_IOUser_vec.end()) {
        g_RspQryThreadInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryThreadInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryThreadInfoTopic_mutex);

    uv_async_send(&g_RspQryThreadInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryThreadInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnThreadInfoTopic(CShfeFtdcRtnThreadInfoField* pRtnThreadInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnThreadInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnThreadInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnThreadInfoField* pNewRtnThreadInfo = NULL;
    if (NULL != pRtnThreadInfo) { 
        pNewRtnThreadInfo = new CShfeFtdcRtnThreadInfoField;
        if (NULL == pNewRtnThreadInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnThreadInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnThreadInfo,pRtnThreadInfo, sizeof(CShfeFtdcRtnThreadInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnThreadInfo;
    if (NULL == pRtnThreadInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnThreadInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnThreadInfo->ObjectID: ", pRtnThreadInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->MonDate: ", pRtnThreadInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->MonTime: ", pRtnThreadInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->Name: ", pRtnThreadInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->ThreadNum: ", pRtnThreadInfo->ThreadNum, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->ThreadStatus: ", pRtnThreadInfo->ThreadStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->InNative: ", pRtnThreadInfo->InNative, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->Suspended: ", pRtnThreadInfo->Suspended, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->BlockCount: ", pRtnThreadInfo->BlockCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->WaitCount: ", pRtnThreadInfo->WaitCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->CpuTime: ", pRtnThreadInfo->CpuTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnThreadInfo->UserTime: ", pRtnThreadInfo->UserTime, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnThreadInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnThreadInfoTopic_IOUser_vec.begin();
        it != g_RtnThreadInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnThreadInfoTopic_IOUser_vec.end()) {
        g_RtnThreadInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnThreadInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnThreadInfoTopic_mutex);

    uv_async_send(&g_RtnThreadInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnThreadInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryVMInfoTopic(CShfeFtdcRspQryVMInfoField* pRspQryVMInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryVMInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryVMInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryVMInfoField* pNewRspQryVMInfo = NULL;
    if (NULL != pRspQryVMInfo) { 
        pNewRspQryVMInfo = new CShfeFtdcRspQryVMInfoField;
        if (NULL == pNewRspQryVMInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryVMInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryVMInfo,pRspQryVMInfo, sizeof(CShfeFtdcRspQryVMInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryVMInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryVMInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryVMInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryVMInfo->ObjectID: ", pRspQryVMInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->MonDate: ", pRspQryVMInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->MonTime: ", pRspQryVMInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->Name: ", pRspQryVMInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->VmName: ", pRspQryVMInfo->VmName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->VmVendor: ", pRspQryVMInfo->VmVendor, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->VmVersion: ", pRspQryVMInfo->VmVersion, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->StartTime: ", pRspQryVMInfo->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->BootClassPath: ", pRspQryVMInfo->BootClassPath, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->ClassPath: ", pRspQryVMInfo->ClassPath, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->LibraryPath: ", pRspQryVMInfo->LibraryPath, g_RunningResult_File);
        OutputCallbackMessage("pRspQryVMInfo->Arguments: ", pRspQryVMInfo->Arguments, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryVMInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryVMInfoTopic_IOUser_vec.begin();
        it != g_RspQryVMInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryVMInfoTopic_IOUser_vec.end()) {
        g_RspQryVMInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryVMInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryVMInfoTopic_mutex);

    uv_async_send(&g_RspQryVMInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryVMInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnVMInfoTopic(CShfeFtdcRtnVMInfoField* pRtnVMInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnVMInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnVMInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnVMInfoField* pNewRtnVMInfo = NULL;
    if (NULL != pRtnVMInfo) { 
        pNewRtnVMInfo = new CShfeFtdcRtnVMInfoField;
        if (NULL == pNewRtnVMInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnVMInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnVMInfo,pRtnVMInfo, sizeof(CShfeFtdcRtnVMInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnVMInfo;
    if (NULL == pRtnVMInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnVMInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnVMInfo->ObjectID: ", pRtnVMInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->MonDate: ", pRtnVMInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->MonTime: ", pRtnVMInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->Name: ", pRtnVMInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->VmName: ", pRtnVMInfo->VmName, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->VmVendor: ", pRtnVMInfo->VmVendor, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->VmVersion: ", pRtnVMInfo->VmVersion, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->StartTime: ", pRtnVMInfo->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->BootClassPath: ", pRtnVMInfo->BootClassPath, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->ClassPath: ", pRtnVMInfo->ClassPath, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->LibraryPath: ", pRtnVMInfo->LibraryPath, g_RunningResult_File);
        OutputCallbackMessage("pRtnVMInfo->Arguments: ", pRtnVMInfo->Arguments, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnVMInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnVMInfoTopic_IOUser_vec.begin();
        it != g_RtnVMInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnVMInfoTopic_IOUser_vec.end()) {
        g_RtnVMInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnVMInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnVMInfoTopic_mutex);

    uv_async_send(&g_RtnVMInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnVMInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPropertyInfoTopic(CShfeFtdcRspQryPropertyInfoField* pRspQryPropertyInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPropertyInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPropertyInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPropertyInfoField* pNewRspQryPropertyInfo = NULL;
    if (NULL != pRspQryPropertyInfo) { 
        pNewRspQryPropertyInfo = new CShfeFtdcRspQryPropertyInfoField;
        if (NULL == pNewRspQryPropertyInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPropertyInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPropertyInfo,pRspQryPropertyInfo, sizeof(CShfeFtdcRspQryPropertyInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPropertyInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPropertyInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPropertyInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPropertyInfo->ObjectID: ", pRspQryPropertyInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPropertyInfo->MonDate: ", pRspQryPropertyInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPropertyInfo->MonTime: ", pRspQryPropertyInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPropertyInfo->Property: ", pRspQryPropertyInfo->Property, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPropertyInfo->ClipFlag: ", pRspQryPropertyInfo->ClipFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPropertyInfo->Value: ", pRspQryPropertyInfo->Value, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPropertyInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPropertyInfoTopic_IOUser_vec.begin();
        it != g_RspQryPropertyInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPropertyInfoTopic_IOUser_vec.end()) {
        g_RspQryPropertyInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPropertyInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPropertyInfoTopic_mutex);

    uv_async_send(&g_RspQryPropertyInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPropertyInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPropertyInfoTopic(CShfeFtdcRtnPropertyInfoField* pRtnPropertyInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPropertyInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPropertyInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPropertyInfoField* pNewRtnPropertyInfo = NULL;
    if (NULL != pRtnPropertyInfo) { 
        pNewRtnPropertyInfo = new CShfeFtdcRtnPropertyInfoField;
        if (NULL == pNewRtnPropertyInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPropertyInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPropertyInfo,pRtnPropertyInfo, sizeof(CShfeFtdcRtnPropertyInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPropertyInfo;
    if (NULL == pRtnPropertyInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnPropertyInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPropertyInfo->ObjectID: ", pRtnPropertyInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnPropertyInfo->MonDate: ", pRtnPropertyInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnPropertyInfo->MonTime: ", pRtnPropertyInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnPropertyInfo->Property: ", pRtnPropertyInfo->Property, g_RunningResult_File);
        OutputCallbackMessage("pRtnPropertyInfo->ClipFlag: ", pRtnPropertyInfo->ClipFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnPropertyInfo->Value: ", pRtnPropertyInfo->Value, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPropertyInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPropertyInfoTopic_IOUser_vec.begin();
        it != g_RtnPropertyInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPropertyInfoTopic_IOUser_vec.end()) {
        g_RtnPropertyInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPropertyInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPropertyInfoTopic_mutex);

    uv_async_send(&g_RtnPropertyInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPropertyInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryMemPoolInfoTopic(CShfeFtdcRspQryMemPoolInfoField* pRspQryMemPoolInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryMemPoolInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryMemPoolInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryMemPoolInfoField* pNewRspQryMemPoolInfo = NULL;
    if (NULL != pRspQryMemPoolInfo) { 
        pNewRspQryMemPoolInfo = new CShfeFtdcRspQryMemPoolInfoField;
        if (NULL == pNewRspQryMemPoolInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryMemPoolInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryMemPoolInfo,pRspQryMemPoolInfo, sizeof(CShfeFtdcRspQryMemPoolInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryMemPoolInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryMemPoolInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryMemPoolInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryMemPoolInfo->ObjectID: ", pRspQryMemPoolInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->MonDate: ", pRspQryMemPoolInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->MonTime: ", pRspQryMemPoolInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->PoolName: ", pRspQryMemPoolInfo->PoolName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->Usage: ", pRspQryMemPoolInfo->Usage, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->committedbytes: ", pRspQryMemPoolInfo->committedbytes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->initbytes: ", pRspQryMemPoolInfo->initbytes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->maxbytes: ", pRspQryMemPoolInfo->maxbytes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->usedbytes: ", pRspQryMemPoolInfo->usedbytes, g_RunningResult_File);
        OutputCallbackMessage("pRspQryMemPoolInfo->Type: ", pRspQryMemPoolInfo->Type, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryMemPoolInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryMemPoolInfoTopic_IOUser_vec.begin();
        it != g_RspQryMemPoolInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryMemPoolInfoTopic_IOUser_vec.end()) {
        g_RspQryMemPoolInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryMemPoolInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryMemPoolInfoTopic_mutex);

    uv_async_send(&g_RspQryMemPoolInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryMemPoolInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnMemPoolInfoTopic(CShfeFtdcRtnMemPoolInfoField* pRtnMemPoolInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnMemPoolInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnMemPoolInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnMemPoolInfoField* pNewRtnMemPoolInfo = NULL;
    if (NULL != pRtnMemPoolInfo) { 
        pNewRtnMemPoolInfo = new CShfeFtdcRtnMemPoolInfoField;
        if (NULL == pNewRtnMemPoolInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnMemPoolInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnMemPoolInfo,pRtnMemPoolInfo, sizeof(CShfeFtdcRtnMemPoolInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnMemPoolInfo;
    if (NULL == pRtnMemPoolInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnMemPoolInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnMemPoolInfo->ObjectID: ", pRtnMemPoolInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->MonDate: ", pRtnMemPoolInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->MonTime: ", pRtnMemPoolInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->PoolName: ", pRtnMemPoolInfo->PoolName, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->Usage: ", pRtnMemPoolInfo->Usage, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->committedbytes: ", pRtnMemPoolInfo->committedbytes, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->initbytes: ", pRtnMemPoolInfo->initbytes, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->maxbytes: ", pRtnMemPoolInfo->maxbytes, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->usedbytes: ", pRtnMemPoolInfo->usedbytes, g_RunningResult_File);
        OutputCallbackMessage("pRtnMemPoolInfo->Type: ", pRtnMemPoolInfo->Type, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnMemPoolInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnMemPoolInfoTopic_IOUser_vec.begin();
        it != g_RtnMemPoolInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnMemPoolInfoTopic_IOUser_vec.end()) {
        g_RtnMemPoolInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnMemPoolInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnMemPoolInfoTopic_mutex);

    uv_async_send(&g_RtnMemPoolInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnMemPoolInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFileContentInfoTopic(CShfeFtdcRspQryFileContentInfoField* pRspQryFileContentInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFileContentInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFileContentInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFileContentInfoField* pNewRspQryFileContentInfo = NULL;
    if (NULL != pRspQryFileContentInfo) { 
        pNewRspQryFileContentInfo = new CShfeFtdcRspQryFileContentInfoField;
        if (NULL == pNewRspQryFileContentInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFileContentInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFileContentInfo,pRspQryFileContentInfo, sizeof(CShfeFtdcRspQryFileContentInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFileContentInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFileContentInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFileContentInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFileContentInfo->ObjectID: ", pRspQryFileContentInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileContentInfo->MonDate: ", pRspQryFileContentInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileContentInfo->MonTime: ", pRspQryFileContentInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileContentInfo->FileName: ", pRspQryFileContentInfo->FileName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileContentInfo->FileContent: ", pRspQryFileContentInfo->FileContent, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFileContentInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFileContentInfoTopic_IOUser_vec.begin();
        it != g_RspQryFileContentInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFileContentInfoTopic_IOUser_vec.end()) {
        g_RspQryFileContentInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFileContentInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFileContentInfoTopic_mutex);

    uv_async_send(&g_RspQryFileContentInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFileContentInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFileContentInfoTopic(CShfeFtdcRtnFileContentInfoField* pRtnFileContentInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFileContentInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFileContentInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFileContentInfoField* pNewRtnFileContentInfo = NULL;
    if (NULL != pRtnFileContentInfo) { 
        pNewRtnFileContentInfo = new CShfeFtdcRtnFileContentInfoField;
        if (NULL == pNewRtnFileContentInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFileContentInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFileContentInfo,pRtnFileContentInfo, sizeof(CShfeFtdcRtnFileContentInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFileContentInfo;
    if (NULL == pRtnFileContentInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnFileContentInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFileContentInfo->ObjectID: ", pRtnFileContentInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileContentInfo->MonDate: ", pRtnFileContentInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileContentInfo->MonTime: ", pRtnFileContentInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileContentInfo->FileName: ", pRtnFileContentInfo->FileName, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileContentInfo->FileContent: ", pRtnFileContentInfo->FileContent, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFileContentInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFileContentInfoTopic_IOUser_vec.begin();
        it != g_RtnFileContentInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFileContentInfoTopic_IOUser_vec.end()) {
        g_RtnFileContentInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFileContentInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFileContentInfoTopic_mutex);

    uv_async_send(&g_RtnFileContentInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFileContentInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryConnectionInfoTopic(CShfeFtdcRspQryConnectionInfoField* pRspQryConnectionInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryConnectionInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryConnectionInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryConnectionInfoField* pNewRspQryConnectionInfo = NULL;
    if (NULL != pRspQryConnectionInfo) { 
        pNewRspQryConnectionInfo = new CShfeFtdcRspQryConnectionInfoField;
        if (NULL == pNewRspQryConnectionInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryConnectionInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryConnectionInfo,pRspQryConnectionInfo, sizeof(CShfeFtdcRspQryConnectionInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryConnectionInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryConnectionInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryConnectionInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryConnectionInfo->ObjectID: ", pRspQryConnectionInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->MonDate: ", pRspQryConnectionInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->MonTime: ", pRspQryConnectionInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->ServiceName: ", pRspQryConnectionInfo->ServiceName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->Stage: ", pRspQryConnectionInfo->Stage, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->RequestCount: ", pRspQryConnectionInfo->RequestCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->ErrorCount: ", pRspQryConnectionInfo->ErrorCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->ProcTime: ", pRspQryConnectionInfo->ProcTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->BytesReceived: ", pRspQryConnectionInfo->BytesReceived, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->BytesSent: ", pRspQryConnectionInfo->BytesSent, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->RemoteIP: ", pRspQryConnectionInfo->RemoteIP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectionInfo->MaxAccessURI: ", pRspQryConnectionInfo->MaxAccessURI, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryConnectionInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryConnectionInfoTopic_IOUser_vec.begin();
        it != g_RspQryConnectionInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryConnectionInfoTopic_IOUser_vec.end()) {
        g_RspQryConnectionInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryConnectionInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryConnectionInfoTopic_mutex);

    uv_async_send(&g_RspQryConnectionInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryConnectionInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnConnectionInfoTopic(CShfeFtdcRtnConnectionInfoField* pRtnConnectionInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnConnectionInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnConnectionInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnConnectionInfoField* pNewRtnConnectionInfo = NULL;
    if (NULL != pRtnConnectionInfo) { 
        pNewRtnConnectionInfo = new CShfeFtdcRtnConnectionInfoField;
        if (NULL == pNewRtnConnectionInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnConnectionInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnConnectionInfo,pRtnConnectionInfo, sizeof(CShfeFtdcRtnConnectionInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnConnectionInfo;
    if (NULL == pRtnConnectionInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnConnectionInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnConnectionInfo->ObjectID: ", pRtnConnectionInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->MonDate: ", pRtnConnectionInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->MonTime: ", pRtnConnectionInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->ServiceName: ", pRtnConnectionInfo->ServiceName, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->Stage: ", pRtnConnectionInfo->Stage, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->RequestCount: ", pRtnConnectionInfo->RequestCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->ErrorCount: ", pRtnConnectionInfo->ErrorCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->ProcTime: ", pRtnConnectionInfo->ProcTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->BytesReceived: ", pRtnConnectionInfo->BytesReceived, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->BytesSent: ", pRtnConnectionInfo->BytesSent, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->RemoteIP: ", pRtnConnectionInfo->RemoteIP, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectionInfo->MaxAccessURI: ", pRtnConnectionInfo->MaxAccessURI, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnConnectionInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnConnectionInfoTopic_IOUser_vec.begin();
        it != g_RtnConnectionInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnConnectionInfoTopic_IOUser_vec.end()) {
        g_RtnConnectionInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnConnectionInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnConnectionInfoTopic_mutex);

    uv_async_send(&g_RtnConnectionInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnConnectionInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryConnectorInfoTopic(CShfeFtdcRspQryConnectorInfoField* pRspQryConnectorInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryConnectorInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryConnectorInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryConnectorInfoField* pNewRspQryConnectorInfo = NULL;
    if (NULL != pRspQryConnectorInfo) { 
        pNewRspQryConnectorInfo = new CShfeFtdcRspQryConnectorInfoField;
        if (NULL == pNewRspQryConnectorInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryConnectorInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryConnectorInfo,pRspQryConnectorInfo, sizeof(CShfeFtdcRspQryConnectorInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryConnectorInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryConnectorInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryConnectorInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryConnectorInfo->ObjectID: ", pRspQryConnectorInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MonDate: ", pRspQryConnectorInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MonTime: ", pRspQryConnectorInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->Name: ", pRspQryConnectorInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->ThreadsCount: ", pRspQryConnectorInfo->ThreadsCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->BusyThreadsCount: ", pRspQryConnectorInfo->BusyThreadsCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MaxThreads: ", pRspQryConnectorInfo->MaxThreads, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MaxSpareThreads: ", pRspQryConnectorInfo->MaxSpareThreads, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MinSpareThreads: ", pRspQryConnectorInfo->MinSpareThreads, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MaxTime: ", pRspQryConnectorInfo->MaxTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->MaxProcTime: ", pRspQryConnectorInfo->MaxProcTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->RequestCount: ", pRspQryConnectorInfo->RequestCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->ErrorCount: ", pRspQryConnectorInfo->ErrorCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->BytesReceived: ", pRspQryConnectorInfo->BytesReceived, g_RunningResult_File);
        OutputCallbackMessage("pRspQryConnectorInfo->BytesSent: ", pRspQryConnectorInfo->BytesSent, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryConnectorInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryConnectorInfoTopic_IOUser_vec.begin();
        it != g_RspQryConnectorInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryConnectorInfoTopic_IOUser_vec.end()) {
        g_RspQryConnectorInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryConnectorInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryConnectorInfoTopic_mutex);

    uv_async_send(&g_RspQryConnectorInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryConnectorInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnConnectorInfoTopic(CShfeFtdcRtnConnectorInfoField* pRtnConnectorInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnConnectorInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnConnectorInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnConnectorInfoField* pNewRtnConnectorInfo = NULL;
    if (NULL != pRtnConnectorInfo) { 
        pNewRtnConnectorInfo = new CShfeFtdcRtnConnectorInfoField;
        if (NULL == pNewRtnConnectorInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnConnectorInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnConnectorInfo,pRtnConnectorInfo, sizeof(CShfeFtdcRtnConnectorInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnConnectorInfo;
    if (NULL == pRtnConnectorInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnConnectorInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnConnectorInfo->ObjectID: ", pRtnConnectorInfo->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MonDate: ", pRtnConnectorInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MonTime: ", pRtnConnectorInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->Name: ", pRtnConnectorInfo->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->ThreadsCount: ", pRtnConnectorInfo->ThreadsCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->BusyThreadsCount: ", pRtnConnectorInfo->BusyThreadsCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MaxThreads: ", pRtnConnectorInfo->MaxThreads, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MaxSpareThreads: ", pRtnConnectorInfo->MaxSpareThreads, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MinSpareThreads: ", pRtnConnectorInfo->MinSpareThreads, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MaxTime: ", pRtnConnectorInfo->MaxTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->MaxProcTime: ", pRtnConnectorInfo->MaxProcTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->RequestCount: ", pRtnConnectorInfo->RequestCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->ErrorCount: ", pRtnConnectorInfo->ErrorCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->BytesReceived: ", pRtnConnectorInfo->BytesReceived, g_RunningResult_File);
        OutputCallbackMessage("pRtnConnectorInfo->BytesSent: ", pRtnConnectorInfo->BytesSent, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnConnectorInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnConnectorInfoTopic_IOUser_vec.begin();
        it != g_RtnConnectorInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnConnectorInfoTopic_IOUser_vec.end()) {
        g_RtnConnectorInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnConnectorInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnConnectorInfoTopic_mutex);

    uv_async_send(&g_RtnConnectorInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnConnectorInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryDBQueryTopic(CShfeFtdcRspQryDBQueryField* pRspQryDBQuery, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryDBQueryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryDBQueryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryDBQueryField* pNewRspQryDBQuery = NULL;
    if (NULL != pRspQryDBQuery) { 
        pNewRspQryDBQuery = new CShfeFtdcRspQryDBQueryField;
        if (NULL == pNewRspQryDBQuery) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryDBQuery", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryDBQuery,pRspQryDBQuery, sizeof(CShfeFtdcRspQryDBQueryField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryDBQuery;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryDBQuery) { 
        OutputCallbackMessage("SysUserSpi::pRspQryDBQuery is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryDBQuery->ObjectID: ", pRspQryDBQuery->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDBQuery->AttrType: ", pRspQryDBQuery->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDBQuery->MonDate: ", pRspQryDBQuery->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDBQuery->MonTime: ", pRspQryDBQuery->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDBQuery->DBQueryResult: ", pRspQryDBQuery->DBQueryResult, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryDBQueryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryDBQueryTopic_IOUser_vec.begin();
        it != g_RspQryDBQueryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryDBQueryTopic_IOUser_vec.end()) {
        g_RspQryDBQueryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryDBQueryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryDBQueryTopic_mutex);

    uv_async_send(&g_RspQryDBQueryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryDBQueryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnDBQueryTopic(CShfeFtdcRtnDBQueryField* pRtnDBQuery){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnDBQueryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnDBQueryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnDBQueryField* pNewRtnDBQuery = NULL;
    if (NULL != pRtnDBQuery) { 
        pNewRtnDBQuery = new CShfeFtdcRtnDBQueryField;
        if (NULL == pNewRtnDBQuery) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnDBQuery", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnDBQuery,pRtnDBQuery, sizeof(CShfeFtdcRtnDBQueryField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnDBQuery;
    if (NULL == pRtnDBQuery) { 
        OutputCallbackMessage("SysUserSpi::pRtnDBQuery is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnDBQuery->ObjectID: ", pRtnDBQuery->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnDBQuery->AttrType: ", pRtnDBQuery->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnDBQuery->MonDate: ", pRtnDBQuery->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnDBQuery->MonTime: ", pRtnDBQuery->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnDBQuery->DBQueryResult: ", pRtnDBQuery->DBQueryResult, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnDBQueryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnDBQueryTopic_IOUser_vec.begin();
        it != g_RtnDBQueryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnDBQueryTopic_IOUser_vec.end()) {
        g_RtnDBQueryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnDBQueryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnDBQueryTopic_mutex);

    uv_async_send(&g_RtnDBQueryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnDBQueryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryGeneralFieldTopic(CShfeFtdcSysGeneralFieldField* pSysGeneralField, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryGeneralFieldTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryGeneralFieldTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcSysGeneralFieldField* pNewSysGeneralField = NULL;
    if (NULL != pSysGeneralField) { 
        pNewSysGeneralField = new CShfeFtdcSysGeneralFieldField;
        if (NULL == pNewSysGeneralField) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewSysGeneralField", g_RunningResult_File);
            return;
        }
        memcpy (pNewSysGeneralField,pSysGeneralField, sizeof(CShfeFtdcSysGeneralFieldField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewSysGeneralField;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pSysGeneralField) { 
        OutputCallbackMessage("SysUserSpi::pSysGeneralField is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pSysGeneralField->MonDate: ", pSysGeneralField->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->MonTime: ", pSysGeneralField->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->ObjectID: ", pSysGeneralField->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->SubObjectID: ", pSysGeneralField->SubObjectID, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->AttrType: ", pSysGeneralField->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->Content: ", pSysGeneralField->Content, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryGeneralFieldTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryGeneralFieldTopic_IOUser_vec.begin();
        it != g_RspQryGeneralFieldTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryGeneralFieldTopic_IOUser_vec.end()) {
        g_RspQryGeneralFieldTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryGeneralFieldTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryGeneralFieldTopic_mutex);

    uv_async_send(&g_RspQryGeneralFieldTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryGeneralFieldTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnGeneralFieldTopic(CShfeFtdcSysGeneralFieldField* pSysGeneralField){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnGeneralFieldTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnGeneralFieldTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcSysGeneralFieldField* pNewSysGeneralField = NULL;
    if (NULL != pSysGeneralField) { 
        pNewSysGeneralField = new CShfeFtdcSysGeneralFieldField;
        if (NULL == pNewSysGeneralField) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewSysGeneralField", g_RunningResult_File);
            return;
        }
        memcpy (pNewSysGeneralField,pSysGeneralField, sizeof(CShfeFtdcSysGeneralFieldField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewSysGeneralField;
    if (NULL == pSysGeneralField) { 
        OutputCallbackMessage("SysUserSpi::pSysGeneralField is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pSysGeneralField->MonDate: ", pSysGeneralField->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->MonTime: ", pSysGeneralField->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->ObjectID: ", pSysGeneralField->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->SubObjectID: ", pSysGeneralField->SubObjectID, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->AttrType: ", pSysGeneralField->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pSysGeneralField->Content: ", pSysGeneralField->Content, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnGeneralFieldTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnGeneralFieldTopic_IOUser_vec.begin();
        it != g_RtnGeneralFieldTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnGeneralFieldTopic_IOUser_vec.end()) {
        g_RtnGeneralFieldTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnGeneralFieldTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnGeneralFieldTopic_mutex);

    uv_async_send(&g_RtnGeneralFieldTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnGeneralFieldTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryGetFileTopic(CShfeFtdcRspQryGetFileField* pRspQryGetFile, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryGetFileTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryGetFileTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryGetFileField* pNewRspQryGetFile = NULL;
    if (NULL != pRspQryGetFile) { 
        pNewRspQryGetFile = new CShfeFtdcRspQryGetFileField;
        if (NULL == pNewRspQryGetFile) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryGetFile", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryGetFile,pRspQryGetFile, sizeof(CShfeFtdcRspQryGetFileField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryGetFile;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryGetFile) { 
        OutputCallbackMessage("SysUserSpi::pRspQryGetFile is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryGetFile->FileName: ", pRspQryGetFile->FileName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGetFile->Version: ", pRspQryGetFile->Version, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGetFile->Offset: ", pRspQryGetFile->Offset, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGetFile->Length: ", pRspQryGetFile->Length, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGetFile->Comment: ", pRspQryGetFile->Comment, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryGetFileTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryGetFileTopic_IOUser_vec.begin();
        it != g_RspQryGetFileTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryGetFileTopic_IOUser_vec.end()) {
        g_RspQryGetFileTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryGetFileTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryGetFileTopic_mutex);

    uv_async_send(&g_RspQryGetFileTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryGetFileTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryWarningQueryTopic(CShfeFtdcRspQryWarningQueryField* pRspQryWarningQuery, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryWarningQueryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryWarningQueryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryWarningQueryField* pNewRspQryWarningQuery = NULL;
    if (NULL != pRspQryWarningQuery) { 
        pNewRspQryWarningQuery = new CShfeFtdcRspQryWarningQueryField;
        if (NULL == pNewRspQryWarningQuery) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryWarningQuery", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryWarningQuery,pRspQryWarningQuery, sizeof(CShfeFtdcRspQryWarningQueryField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryWarningQuery;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryWarningQuery) { 
        OutputCallbackMessage("SysUserSpi::pRspQryWarningQuery is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryWarningQuery->MonDate: ", pRspQryWarningQuery->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningQuery->MonTime: ", pRspQryWarningQuery->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningQuery->EvendID: ", pRspQryWarningQuery->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryWarningQuery->DBQueryResult: ", pRspQryWarningQuery->DBQueryResult, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryWarningQueryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryWarningQueryTopic_IOUser_vec.begin();
        it != g_RspQryWarningQueryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryWarningQueryTopic_IOUser_vec.end()) {
        g_RspQryWarningQueryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryWarningQueryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryWarningQueryTopic_mutex);

    uv_async_send(&g_RspQryWarningQueryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryWarningQueryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnWarningQueryTopic(CShfeFtdcRtnWarningQueryField* pRtnWarningQuery){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnWarningQueryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnWarningQueryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnWarningQueryField* pNewRtnWarningQuery = NULL;
    if (NULL != pRtnWarningQuery) { 
        pNewRtnWarningQuery = new CShfeFtdcRtnWarningQueryField;
        if (NULL == pNewRtnWarningQuery) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnWarningQuery", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnWarningQuery,pRtnWarningQuery, sizeof(CShfeFtdcRtnWarningQueryField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnWarningQuery;
    if (NULL == pRtnWarningQuery) { 
        OutputCallbackMessage("SysUserSpi::pRtnWarningQuery is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnWarningQuery->MonDate: ", pRtnWarningQuery->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningQuery->MonTime: ", pRtnWarningQuery->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningQuery->EvendID: ", pRtnWarningQuery->EvendID, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningQuery->DBQueryResult: ", pRtnWarningQuery->DBQueryResult, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnWarningQueryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnWarningQueryTopic_IOUser_vec.begin();
        it != g_RtnWarningQueryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnWarningQueryTopic_IOUser_vec.end()) {
        g_RtnWarningQueryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnWarningQueryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnWarningQueryTopic_mutex);

    uv_async_send(&g_RtnWarningQueryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnWarningQueryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnWarningActiveChange(CShfeFtdcRtnWarningActiveChangeField* pRtnWarningActiveChange){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnWarningActiveChange: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnWarningActiveChange: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnWarningActiveChangeField* pNewRtnWarningActiveChange = NULL;
    if (NULL != pRtnWarningActiveChange) { 
        pNewRtnWarningActiveChange = new CShfeFtdcRtnWarningActiveChangeField;
        if (NULL == pNewRtnWarningActiveChange) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnWarningActiveChange", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnWarningActiveChange,pRtnWarningActiveChange, sizeof(CShfeFtdcRtnWarningActiveChangeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnWarningActiveChange;
    if (NULL == pRtnWarningActiveChange) { 
        OutputCallbackMessage("SysUserSpi::pRtnWarningActiveChange is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnWarningActiveChange->ObjectID: ", pRtnWarningActiveChange->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningActiveChange->MonDate: ", pRtnWarningActiveChange->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningActiveChange->MonTime: ", pRtnWarningActiveChange->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnWarningActiveChange->WarningActive: ", pRtnWarningActiveChange->WarningActive, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnWarningActiveChange_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnWarningActiveChange_IOUser_vec.begin();
        it != g_RtnWarningActiveChange_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnWarningActiveChange_IOUser_vec.end()) {
        g_RtnWarningActiveChange_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnWarningActiveChange_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnWarningActiveChange_mutex);

    uv_async_send(&g_RtnWarningActiveChange_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnWarningActiveChange: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryGeneralOperateTopic(CShfeFtdcRspQryGeneralOperateField* pRspQryGeneralOperate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryGeneralOperateTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryGeneralOperateTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryGeneralOperateField* pNewRspQryGeneralOperate = NULL;
    if (NULL != pRspQryGeneralOperate) { 
        pNewRspQryGeneralOperate = new CShfeFtdcRspQryGeneralOperateField;
        if (NULL == pNewRspQryGeneralOperate) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryGeneralOperate", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryGeneralOperate,pRspQryGeneralOperate, sizeof(CShfeFtdcRspQryGeneralOperateField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryGeneralOperate;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryGeneralOperate) { 
        OutputCallbackMessage("SysUserSpi::pRspQryGeneralOperate is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryGeneralOperate->GeneralOperateType: ", pRspQryGeneralOperate->GeneralOperateType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGeneralOperate->GeneralOperateTable: ", pRspQryGeneralOperate->GeneralOperateTable, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGeneralOperate->GeneralOperateOption: ", pRspQryGeneralOperate->GeneralOperateOption, g_RunningResult_File);
        OutputCallbackMessage("pRspQryGeneralOperate->GeneralOperateSet: ", pRspQryGeneralOperate->GeneralOperateSet, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryGeneralOperateTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryGeneralOperateTopic_IOUser_vec.begin();
        it != g_RspQryGeneralOperateTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryGeneralOperateTopic_IOUser_vec.end()) {
        g_RspQryGeneralOperateTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryGeneralOperateTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryGeneralOperateTopic_mutex);

    uv_async_send(&g_RspQryGeneralOperateTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryGeneralOperateTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnGeneralOperateTopic(CShfeFtdcRtnGeneralOperateField* pRtnGeneralOperate){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnGeneralOperateTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnGeneralOperateTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnGeneralOperateField* pNewRtnGeneralOperate = NULL;
    if (NULL != pRtnGeneralOperate) { 
        pNewRtnGeneralOperate = new CShfeFtdcRtnGeneralOperateField;
        if (NULL == pNewRtnGeneralOperate) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnGeneralOperate", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnGeneralOperate,pRtnGeneralOperate, sizeof(CShfeFtdcRtnGeneralOperateField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnGeneralOperate;
    if (NULL == pRtnGeneralOperate) { 
        OutputCallbackMessage("SysUserSpi::pRtnGeneralOperate is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnGeneralOperate->GeneralOperateType: ", pRtnGeneralOperate->GeneralOperateType, g_RunningResult_File);
        OutputCallbackMessage("pRtnGeneralOperate->GeneralOperateTable: ", pRtnGeneralOperate->GeneralOperateTable, g_RunningResult_File);
        OutputCallbackMessage("pRtnGeneralOperate->GeneralOperateOption: ", pRtnGeneralOperate->GeneralOperateOption, g_RunningResult_File);
        OutputCallbackMessage("pRtnGeneralOperate->GeneralOperateSet: ", pRtnGeneralOperate->GeneralOperateSet, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnGeneralOperateTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnGeneralOperateTopic_IOUser_vec.begin();
        it != g_RtnGeneralOperateTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnGeneralOperateTopic_IOUser_vec.end()) {
        g_RtnGeneralOperateTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnGeneralOperateTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnGeneralOperateTopic_mutex);

    uv_async_send(&g_RtnGeneralOperateTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnGeneralOperateTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceLinkedTopic(CShfeFtdcRspQryNetDeviceLinkedField* pRspQryNetDeviceLinked, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceLinkedTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceLinkedTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceLinkedField* pNewRspQryNetDeviceLinked = NULL;
    if (NULL != pRspQryNetDeviceLinked) { 
        pNewRspQryNetDeviceLinked = new CShfeFtdcRspQryNetDeviceLinkedField;
        if (NULL == pNewRspQryNetDeviceLinked) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDeviceLinked", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDeviceLinked,pRspQryNetDeviceLinked, sizeof(CShfeFtdcRspQryNetDeviceLinkedField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDeviceLinked;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDeviceLinked) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDeviceLinked is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDeviceLinked->OperationType: ", pRspQryNetDeviceLinked->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->ID: ", pRspQryNetDeviceLinked->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->NetDeviceID: ", pRspQryNetDeviceLinked->NetDeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->NetPortID: ", pRspQryNetDeviceLinked->NetPortID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->NetObjectID: ", pRspQryNetDeviceLinked->NetObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->NetPortType: ", pRspQryNetDeviceLinked->NetPortType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->LinkNetDeviceID: ", pRspQryNetDeviceLinked->LinkNetDeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->LinkNetPortID: ", pRspQryNetDeviceLinked->LinkNetPortID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->LinkNetObjectID: ", pRspQryNetDeviceLinked->LinkNetObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->LinkNetPortType: ", pRspQryNetDeviceLinked->LinkNetPortType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceLinked->LinkSource: ", pRspQryNetDeviceLinked->LinkSource, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceLinkedTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceLinkedTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceLinkedTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceLinkedTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceLinkedTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceLinkedTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceLinkedTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceLinkedTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceLinkedTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDeviceLinkedTopic(CShfeFtdcRtnNetDeviceLinkedField* pRtnNetDeviceLinked){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDeviceLinkedTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceLinkedTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDeviceLinkedField* pNewRtnNetDeviceLinked = NULL;
    if (NULL != pRtnNetDeviceLinked) { 
        pNewRtnNetDeviceLinked = new CShfeFtdcRtnNetDeviceLinkedField;
        if (NULL == pNewRtnNetDeviceLinked) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDeviceLinked", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDeviceLinked,pRtnNetDeviceLinked, sizeof(CShfeFtdcRtnNetDeviceLinkedField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDeviceLinked;
    if (NULL == pRtnNetDeviceLinked) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDeviceLinked is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDeviceLinked->OperationType: ", pRtnNetDeviceLinked->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->ID: ", pRtnNetDeviceLinked->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->NetDeviceID: ", pRtnNetDeviceLinked->NetDeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->NetPortID: ", pRtnNetDeviceLinked->NetPortID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->NetObjectID: ", pRtnNetDeviceLinked->NetObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->NetPortType: ", pRtnNetDeviceLinked->NetPortType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->LinkNetDeviceID: ", pRtnNetDeviceLinked->LinkNetDeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->LinkNetPortID: ", pRtnNetDeviceLinked->LinkNetPortID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->LinkNetObjectID: ", pRtnNetDeviceLinked->LinkNetObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->LinkNetPortType: ", pRtnNetDeviceLinked->LinkNetPortType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceLinked->LinkSource: ", pRtnNetDeviceLinked->LinkSource, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDeviceLinkedTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDeviceLinkedTopic_IOUser_vec.begin();
        it != g_RtnNetDeviceLinkedTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDeviceLinkedTopic_IOUser_vec.end()) {
        g_RtnNetDeviceLinkedTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDeviceLinkedTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDeviceLinkedTopic_mutex);

    uv_async_send(&g_RtnNetDeviceLinkedTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceLinkedTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradeUserLoginStatTopic(CShfeFtdcRspQryTradeUserLoginStatField* pRspQryTradeUserLoginStat, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradeUserLoginStatTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradeUserLoginStatTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradeUserLoginStatField* pNewRspQryTradeUserLoginStat = NULL;
    if (NULL != pRspQryTradeUserLoginStat) { 
        pNewRspQryTradeUserLoginStat = new CShfeFtdcRspQryTradeUserLoginStatField;
        if (NULL == pNewRspQryTradeUserLoginStat) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradeUserLoginStat", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradeUserLoginStat,pRspQryTradeUserLoginStat, sizeof(CShfeFtdcRspQryTradeUserLoginStatField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradeUserLoginStat;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradeUserLoginStat) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradeUserLoginStat is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradeUserLoginStat->MonDate: ", pRspQryTradeUserLoginStat->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->MonTime: ", pRspQryTradeUserLoginStat->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->ObjectID: ", pRspQryTradeUserLoginStat->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->IPAddress: ", pRspQryTradeUserLoginStat->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->ParticipantID: ", pRspQryTradeUserLoginStat->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->UserID: ", pRspQryTradeUserLoginStat->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeUserLoginStat->FrontId: ", pRspQryTradeUserLoginStat->FrontId, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradeUserLoginStatTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradeUserLoginStatTopic_IOUser_vec.begin();
        it != g_RspQryTradeUserLoginStatTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradeUserLoginStatTopic_IOUser_vec.end()) {
        g_RspQryTradeUserLoginStatTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradeUserLoginStatTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradeUserLoginStatTopic_mutex);

    uv_async_send(&g_RspQryTradeUserLoginStatTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradeUserLoginStatTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradeFrontOrderRttStatTopic(CShfeFtdcRspQryTradeFrontOrderRttStatField* pRspQryTradeFrontOrderRttStat, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradeFrontOrderRttStatTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradeFrontOrderRttStatTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradeFrontOrderRttStatField* pNewRspQryTradeFrontOrderRttStat = NULL;
    if (NULL != pRspQryTradeFrontOrderRttStat) { 
        pNewRspQryTradeFrontOrderRttStat = new CShfeFtdcRspQryTradeFrontOrderRttStatField;
        if (NULL == pNewRspQryTradeFrontOrderRttStat) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradeFrontOrderRttStat", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradeFrontOrderRttStat,pRspQryTradeFrontOrderRttStat, sizeof(CShfeFtdcRspQryTradeFrontOrderRttStatField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradeFrontOrderRttStat;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradeFrontOrderRttStat) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradeFrontOrderRttStat is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->MonDate: ", pRspQryTradeFrontOrderRttStat->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->MonTime: ", pRspQryTradeFrontOrderRttStat->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->ObjectID: ", pRspQryTradeFrontOrderRttStat->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderCount: ", pRspQryTradeFrontOrderRttStat->OrderCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderRttSum: ", pRspQryTradeFrontOrderRttStat->OrderRttSum, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderMaxRtt: ", pRspQryTradeFrontOrderRttStat->OrderMaxRtt, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderMinRtt: ", pRspQryTradeFrontOrderRttStat->OrderMinRtt, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderRttSqu: ", pRspQryTradeFrontOrderRttStat->OrderRttSqu, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeFrontOrderRttStat->OrderRttCutDistrib: ", pRspQryTradeFrontOrderRttStat->OrderRttCutDistrib, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradeFrontOrderRttStatTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradeFrontOrderRttStatTopic_IOUser_vec.begin();
        it != g_RspQryTradeFrontOrderRttStatTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradeFrontOrderRttStatTopic_IOUser_vec.end()) {
        g_RspQryTradeFrontOrderRttStatTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradeFrontOrderRttStatTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradeFrontOrderRttStatTopic_mutex);

    uv_async_send(&g_RspQryTradeFrontOrderRttStatTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradeFrontOrderRttStatTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTradeFrontOrderRttStatTopic(CShfeFtdcRtnTradeFrontOrderRttStatField* pRtnTradeFrontOrderRttStat){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTradeFrontOrderRttStatTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTradeFrontOrderRttStatTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTradeFrontOrderRttStatField* pNewRtnTradeFrontOrderRttStat = NULL;
    if (NULL != pRtnTradeFrontOrderRttStat) { 
        pNewRtnTradeFrontOrderRttStat = new CShfeFtdcRtnTradeFrontOrderRttStatField;
        if (NULL == pNewRtnTradeFrontOrderRttStat) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTradeFrontOrderRttStat", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTradeFrontOrderRttStat,pRtnTradeFrontOrderRttStat, sizeof(CShfeFtdcRtnTradeFrontOrderRttStatField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTradeFrontOrderRttStat;
    if (NULL == pRtnTradeFrontOrderRttStat) { 
        OutputCallbackMessage("SysUserSpi::pRtnTradeFrontOrderRttStat is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->MonDate: ", pRtnTradeFrontOrderRttStat->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->MonTime: ", pRtnTradeFrontOrderRttStat->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->ObjectID: ", pRtnTradeFrontOrderRttStat->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderCount: ", pRtnTradeFrontOrderRttStat->OrderCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderRttSum: ", pRtnTradeFrontOrderRttStat->OrderRttSum, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderMaxRtt: ", pRtnTradeFrontOrderRttStat->OrderMaxRtt, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderMinRtt: ", pRtnTradeFrontOrderRttStat->OrderMinRtt, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderRttSqu: ", pRtnTradeFrontOrderRttStat->OrderRttSqu, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeFrontOrderRttStat->OrderRttCutDistrib: ", pRtnTradeFrontOrderRttStat->OrderRttCutDistrib, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTradeFrontOrderRttStatTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTradeFrontOrderRttStatTopic_IOUser_vec.begin();
        it != g_RtnTradeFrontOrderRttStatTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTradeFrontOrderRttStatTopic_IOUser_vec.end()) {
        g_RtnTradeFrontOrderRttStatTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTradeFrontOrderRttStatTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTradeFrontOrderRttStatTopic_mutex);

    uv_async_send(&g_RtnTradeFrontOrderRttStatTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTradeFrontOrderRttStatTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryParticTradeOrderStatesTopic(CShfeFtdcRspQryParticTradeOrderStatesField* pRspQryParticTradeOrderStates, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryParticTradeOrderStatesTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryParticTradeOrderStatesTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryParticTradeOrderStatesField* pNewRspQryParticTradeOrderStates = NULL;
    if (NULL != pRspQryParticTradeOrderStates) { 
        pNewRspQryParticTradeOrderStates = new CShfeFtdcRspQryParticTradeOrderStatesField;
        if (NULL == pNewRspQryParticTradeOrderStates) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryParticTradeOrderStates", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryParticTradeOrderStates,pRspQryParticTradeOrderStates, sizeof(CShfeFtdcRspQryParticTradeOrderStatesField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryParticTradeOrderStates;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryParticTradeOrderStates) { 
        OutputCallbackMessage("SysUserSpi::pRspQryParticTradeOrderStates is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryParticTradeOrderStates->ParticipantID: ", pRspQryParticTradeOrderStates->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->UserID: ", pRspQryParticTradeOrderStates->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->MonDate: ", pRspQryParticTradeOrderStates->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->MonTime: ", pRspQryParticTradeOrderStates->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->StaticWidth: ", pRspQryParticTradeOrderStates->StaticWidth, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->FrontID: ", pRspQryParticTradeOrderStates->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->OrderCount: ", pRspQryParticTradeOrderStates->OrderCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->CancleCount: ", pRspQryParticTradeOrderStates->CancleCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->QueryCount: ", pRspQryParticTradeOrderStates->QueryCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->TradeCount: ", pRspQryParticTradeOrderStates->TradeCount, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->TradeMoney: ", pRspQryParticTradeOrderStates->TradeMoney, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->OrderCntMax: ", pRspQryParticTradeOrderStates->OrderCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->CancleCntMax: ", pRspQryParticTradeOrderStates->CancleCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->QueryCntMax: ", pRspQryParticTradeOrderStates->QueryCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->TradeCntMax: ", pRspQryParticTradeOrderStates->TradeCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryParticTradeOrderStates->TradeMoneyMax: ", pRspQryParticTradeOrderStates->TradeMoneyMax, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryParticTradeOrderStatesTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryParticTradeOrderStatesTopic_IOUser_vec.begin();
        it != g_RspQryParticTradeOrderStatesTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryParticTradeOrderStatesTopic_IOUser_vec.end()) {
        g_RspQryParticTradeOrderStatesTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryParticTradeOrderStatesTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryParticTradeOrderStatesTopic_mutex);

    uv_async_send(&g_RspQryParticTradeOrderStatesTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryParticTradeOrderStatesTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnParticTradeOrderStatesTopic(CShfeFtdcRtnParticTradeOrderStatesField* pRtnParticTradeOrderStates){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnParticTradeOrderStatesTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnParticTradeOrderStatesTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnParticTradeOrderStatesField* pNewRtnParticTradeOrderStates = NULL;
    if (NULL != pRtnParticTradeOrderStates) { 
        pNewRtnParticTradeOrderStates = new CShfeFtdcRtnParticTradeOrderStatesField;
        if (NULL == pNewRtnParticTradeOrderStates) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnParticTradeOrderStates", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnParticTradeOrderStates,pRtnParticTradeOrderStates, sizeof(CShfeFtdcRtnParticTradeOrderStatesField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnParticTradeOrderStates;
    if (NULL == pRtnParticTradeOrderStates) { 
        OutputCallbackMessage("SysUserSpi::pRtnParticTradeOrderStates is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnParticTradeOrderStates->ParticipantID: ", pRtnParticTradeOrderStates->ParticipantID, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->UserID: ", pRtnParticTradeOrderStates->UserID, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->MonDate: ", pRtnParticTradeOrderStates->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->MonTime: ", pRtnParticTradeOrderStates->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->StaticWidth: ", pRtnParticTradeOrderStates->StaticWidth, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->FrontID: ", pRtnParticTradeOrderStates->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->OrderCount: ", pRtnParticTradeOrderStates->OrderCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->CancleCount: ", pRtnParticTradeOrderStates->CancleCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->QueryCount: ", pRtnParticTradeOrderStates->QueryCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->TradeCount: ", pRtnParticTradeOrderStates->TradeCount, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->TradeMoney: ", pRtnParticTradeOrderStates->TradeMoney, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->OrderCntMax: ", pRtnParticTradeOrderStates->OrderCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->CancleCntMax: ", pRtnParticTradeOrderStates->CancleCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->QueryCntMax: ", pRtnParticTradeOrderStates->QueryCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->TradeCntMax: ", pRtnParticTradeOrderStates->TradeCntMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnParticTradeOrderStates->TradeMoneyMax: ", pRtnParticTradeOrderStates->TradeMoneyMax, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnParticTradeOrderStatesTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnParticTradeOrderStatesTopic_IOUser_vec.begin();
        it != g_RtnParticTradeOrderStatesTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnParticTradeOrderStatesTopic_IOUser_vec.end()) {
        g_RtnParticTradeOrderStatesTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnParticTradeOrderStatesTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnParticTradeOrderStatesTopic_mutex);

    uv_async_send(&g_RtnParticTradeOrderStatesTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnParticTradeOrderStatesTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryRouterInfoTopic(CShfeFtdcRspQryRouterInfoField* pRspQryRouterInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryRouterInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryRouterInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryRouterInfoField* pNewRspQryRouterInfo = NULL;
    if (NULL != pRspQryRouterInfo) { 
        pNewRspQryRouterInfo = new CShfeFtdcRspQryRouterInfoField;
        if (NULL == pNewRspQryRouterInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryRouterInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryRouterInfo,pRspQryRouterInfo, sizeof(CShfeFtdcRspQryRouterInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryRouterInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryRouterInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryRouterInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryRouterInfo->HostName: ", pRspQryRouterInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->MonDate: ", pRspQryRouterInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->MonTime: ", pRspQryRouterInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Dev: ", pRspQryRouterInfo->Dev, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Destination: ", pRspQryRouterInfo->Destination, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Gateway: ", pRspQryRouterInfo->Gateway, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Mask: ", pRspQryRouterInfo->Mask, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Flag: ", pRspQryRouterInfo->Flag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->RefCnt: ", pRspQryRouterInfo->RefCnt, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Use: ", pRspQryRouterInfo->Use, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Metric: ", pRspQryRouterInfo->Metric, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Mtu: ", pRspQryRouterInfo->Mtu, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Win: ", pRspQryRouterInfo->Win, g_RunningResult_File);
        OutputCallbackMessage("pRspQryRouterInfo->Rtt: ", pRspQryRouterInfo->Rtt, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryRouterInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryRouterInfoTopic_IOUser_vec.begin();
        it != g_RspQryRouterInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryRouterInfoTopic_IOUser_vec.end()) {
        g_RspQryRouterInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryRouterInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryRouterInfoTopic_mutex);

    uv_async_send(&g_RspQryRouterInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryRouterInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnRouterInfoTopic(CShfeFtdcRtnRouterInfoField* pRtnRouterInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnRouterInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnRouterInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnRouterInfoField* pNewRtnRouterInfo = NULL;
    if (NULL != pRtnRouterInfo) { 
        pNewRtnRouterInfo = new CShfeFtdcRtnRouterInfoField;
        if (NULL == pNewRtnRouterInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnRouterInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnRouterInfo,pRtnRouterInfo, sizeof(CShfeFtdcRtnRouterInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnRouterInfo;
    if (NULL == pRtnRouterInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnRouterInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnRouterInfo->HostName: ", pRtnRouterInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->MonDate: ", pRtnRouterInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->MonTime: ", pRtnRouterInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Dev: ", pRtnRouterInfo->Dev, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Destination: ", pRtnRouterInfo->Destination, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Gateway: ", pRtnRouterInfo->Gateway, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Mask: ", pRtnRouterInfo->Mask, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Flag: ", pRtnRouterInfo->Flag, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->RefCnt: ", pRtnRouterInfo->RefCnt, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Use: ", pRtnRouterInfo->Use, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Metric: ", pRtnRouterInfo->Metric, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Mtu: ", pRtnRouterInfo->Mtu, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Win: ", pRtnRouterInfo->Win, g_RunningResult_File);
        OutputCallbackMessage("pRtnRouterInfo->Rtt: ", pRtnRouterInfo->Rtt, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnRouterInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnRouterInfoTopic_IOUser_vec.begin();
        it != g_RtnRouterInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnRouterInfoTopic_IOUser_vec.end()) {
        g_RtnRouterInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnRouterInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnRouterInfoTopic_mutex);

    uv_async_send(&g_RtnRouterInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnRouterInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryDiskIOTopic(CShfeFtdcRspQryDiskIOField* pRspQryDiskIO, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryDiskIOTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryDiskIOTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryDiskIOField* pNewRspQryDiskIO = NULL;
    if (NULL != pRspQryDiskIO) { 
        pNewRspQryDiskIO = new CShfeFtdcRspQryDiskIOField;
        if (NULL == pNewRspQryDiskIO) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryDiskIO", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryDiskIO,pRspQryDiskIO, sizeof(CShfeFtdcRspQryDiskIOField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryDiskIO;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryDiskIO) { 
        OutputCallbackMessage("SysUserSpi::pRspQryDiskIO is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryDiskIO->HostName: ", pRspQryDiskIO->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->MonDate: ", pRspQryDiskIO->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->MonTime: ", pRspQryDiskIO->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->PartName: ", pRspQryDiskIO->PartName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->ReadMerges: ", pRspQryDiskIO->ReadMerges, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->WriteMerges: ", pRspQryDiskIO->WriteMerges, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->ReadIOs: ", pRspQryDiskIO->ReadIOs, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->WriteIOs: ", pRspQryDiskIO->WriteIOs, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->ReadKBs: ", pRspQryDiskIO->ReadKBs, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->WriteKBs: ", pRspQryDiskIO->WriteKBs, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->SizeVal: ", pRspQryDiskIO->SizeVal, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->QueueVal: ", pRspQryDiskIO->QueueVal, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->Svc_t: ", pRspQryDiskIO->Svc_t, g_RunningResult_File);
        OutputCallbackMessage("pRspQryDiskIO->Busy: ", pRspQryDiskIO->Busy, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryDiskIOTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryDiskIOTopic_IOUser_vec.begin();
        it != g_RspQryDiskIOTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryDiskIOTopic_IOUser_vec.end()) {
        g_RspQryDiskIOTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryDiskIOTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryDiskIOTopic_mutex);

    uv_async_send(&g_RspQryDiskIOTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryDiskIOTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnDiskIOTopic(CShfeFtdcRtnDiskIOField* pRtnDiskIO){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnDiskIOTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnDiskIOTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnDiskIOField* pNewRtnDiskIO = NULL;
    if (NULL != pRtnDiskIO) { 
        pNewRtnDiskIO = new CShfeFtdcRtnDiskIOField;
        if (NULL == pNewRtnDiskIO) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnDiskIO", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnDiskIO,pRtnDiskIO, sizeof(CShfeFtdcRtnDiskIOField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnDiskIO;
    if (NULL == pRtnDiskIO) { 
        OutputCallbackMessage("SysUserSpi::pRtnDiskIO is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnDiskIO->HostName: ", pRtnDiskIO->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->MonDate: ", pRtnDiskIO->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->MonTime: ", pRtnDiskIO->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->PartName: ", pRtnDiskIO->PartName, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->ReadMerges: ", pRtnDiskIO->ReadMerges, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->WriteMerges: ", pRtnDiskIO->WriteMerges, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->ReadIOs: ", pRtnDiskIO->ReadIOs, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->WriteIOs: ", pRtnDiskIO->WriteIOs, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->ReadKBs: ", pRtnDiskIO->ReadKBs, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->WriteKBs: ", pRtnDiskIO->WriteKBs, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->SizeVal: ", pRtnDiskIO->SizeVal, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->QueueVal: ", pRtnDiskIO->QueueVal, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->Svc_t: ", pRtnDiskIO->Svc_t, g_RunningResult_File);
        OutputCallbackMessage("pRtnDiskIO->Busy: ", pRtnDiskIO->Busy, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnDiskIOTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnDiskIOTopic_IOUser_vec.begin();
        it != g_RtnDiskIOTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnDiskIOTopic_IOUser_vec.end()) {
        g_RtnDiskIOTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnDiskIOTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnDiskIOTopic_mutex);

    uv_async_send(&g_RtnDiskIOTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnDiskIOTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryStatInfoTopic(CShfeFtdcRspQryStatInfoField* pRspQryStatInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryStatInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryStatInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryStatInfoField* pNewRspQryStatInfo = NULL;
    if (NULL != pRspQryStatInfo) { 
        pNewRspQryStatInfo = new CShfeFtdcRspQryStatInfoField;
        if (NULL == pNewRspQryStatInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryStatInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryStatInfo,pRspQryStatInfo, sizeof(CShfeFtdcRspQryStatInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryStatInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryStatInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryStatInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryStatInfo->HostName: ", pRspQryStatInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->MonDate: ", pRspQryStatInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->MonTime: ", pRspQryStatInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->ProcRun: ", pRspQryStatInfo->ProcRun, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->ProcBlk: ", pRspQryStatInfo->ProcBlk, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->SwapIn: ", pRspQryStatInfo->SwapIn, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->SwapOut: ", pRspQryStatInfo->SwapOut, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->BlockIn: ", pRspQryStatInfo->BlockIn, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->BlockOut: ", pRspQryStatInfo->BlockOut, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->Inter: ", pRspQryStatInfo->Inter, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->Context: ", pRspQryStatInfo->Context, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->CPUUser: ", pRspQryStatInfo->CPUUser, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->CPUSys: ", pRspQryStatInfo->CPUSys, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->CPUIdle: ", pRspQryStatInfo->CPUIdle, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->CPUIOWait: ", pRspQryStatInfo->CPUIOWait, g_RunningResult_File);
        OutputCallbackMessage("pRspQryStatInfo->CPUSteal: ", pRspQryStatInfo->CPUSteal, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryStatInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryStatInfoTopic_IOUser_vec.begin();
        it != g_RspQryStatInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryStatInfoTopic_IOUser_vec.end()) {
        g_RspQryStatInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryStatInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryStatInfoTopic_mutex);

    uv_async_send(&g_RspQryStatInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryStatInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnStatInfoTopic(CShfeFtdcRtnStatInfoField* pRtnStatInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnStatInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnStatInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnStatInfoField* pNewRtnStatInfo = NULL;
    if (NULL != pRtnStatInfo) { 
        pNewRtnStatInfo = new CShfeFtdcRtnStatInfoField;
        if (NULL == pNewRtnStatInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnStatInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnStatInfo,pRtnStatInfo, sizeof(CShfeFtdcRtnStatInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnStatInfo;
    if (NULL == pRtnStatInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnStatInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnStatInfo->HostName: ", pRtnStatInfo->HostName, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->MonDate: ", pRtnStatInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->MonTime: ", pRtnStatInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->ProcRun: ", pRtnStatInfo->ProcRun, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->ProcBlk: ", pRtnStatInfo->ProcBlk, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->SwapIn: ", pRtnStatInfo->SwapIn, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->SwapOut: ", pRtnStatInfo->SwapOut, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->BlockIn: ", pRtnStatInfo->BlockIn, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->BlockOut: ", pRtnStatInfo->BlockOut, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->Inter: ", pRtnStatInfo->Inter, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->Context: ", pRtnStatInfo->Context, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->CPUUser: ", pRtnStatInfo->CPUUser, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->CPUSys: ", pRtnStatInfo->CPUSys, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->CPUIdle: ", pRtnStatInfo->CPUIdle, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->CPUIOWait: ", pRtnStatInfo->CPUIOWait, g_RunningResult_File);
        OutputCallbackMessage("pRtnStatInfo->CPUSteal: ", pRtnStatInfo->CPUSteal, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnStatInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnStatInfoTopic_IOUser_vec.begin();
        it != g_RtnStatInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnStatInfoTopic_IOUser_vec.end()) {
        g_RtnStatInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnStatInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnStatInfoTopic_mutex);

    uv_async_send(&g_RtnStatInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnStatInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryTradeOrderRttCutLineTopic(CShfeFtdcRspQryTradeOrderRttCutLineField* pRspQryTradeOrderRttCutLine, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryTradeOrderRttCutLineTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryTradeOrderRttCutLineTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryTradeOrderRttCutLineField* pNewRspQryTradeOrderRttCutLine = NULL;
    if (NULL != pRspQryTradeOrderRttCutLine) { 
        pNewRspQryTradeOrderRttCutLine = new CShfeFtdcRspQryTradeOrderRttCutLineField;
        if (NULL == pNewRspQryTradeOrderRttCutLine) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryTradeOrderRttCutLine", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryTradeOrderRttCutLine,pRspQryTradeOrderRttCutLine, sizeof(CShfeFtdcRspQryTradeOrderRttCutLineField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryTradeOrderRttCutLine;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryTradeOrderRttCutLine) { 
        OutputCallbackMessage("SysUserSpi::pRspQryTradeOrderRttCutLine is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryTradeOrderRttCutLine->MonDate: ", pRspQryTradeOrderRttCutLine->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeOrderRttCutLine->MonTime: ", pRspQryTradeOrderRttCutLine->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeOrderRttCutLine->UserName: ", pRspQryTradeOrderRttCutLine->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeOrderRttCutLine->OrderRttCutLine: ", pRspQryTradeOrderRttCutLine->OrderRttCutLine, g_RunningResult_File);
        OutputCallbackMessage("pRspQryTradeOrderRttCutLine->OrderRttWidth: ", pRspQryTradeOrderRttCutLine->OrderRttWidth, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryTradeOrderRttCutLineTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryTradeOrderRttCutLineTopic_IOUser_vec.begin();
        it != g_RspQryTradeOrderRttCutLineTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryTradeOrderRttCutLineTopic_IOUser_vec.end()) {
        g_RspQryTradeOrderRttCutLineTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryTradeOrderRttCutLineTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryTradeOrderRttCutLineTopic_mutex);

    uv_async_send(&g_RspQryTradeOrderRttCutLineTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryTradeOrderRttCutLineTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnTradeOrderRttCutLineTopic(CShfeFtdcRtnTradeOrderRttCutLineField* pRtnTradeOrderRttCutLine){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnTradeOrderRttCutLineTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnTradeOrderRttCutLineTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnTradeOrderRttCutLineField* pNewRtnTradeOrderRttCutLine = NULL;
    if (NULL != pRtnTradeOrderRttCutLine) { 
        pNewRtnTradeOrderRttCutLine = new CShfeFtdcRtnTradeOrderRttCutLineField;
        if (NULL == pNewRtnTradeOrderRttCutLine) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnTradeOrderRttCutLine", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnTradeOrderRttCutLine,pRtnTradeOrderRttCutLine, sizeof(CShfeFtdcRtnTradeOrderRttCutLineField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnTradeOrderRttCutLine;
    if (NULL == pRtnTradeOrderRttCutLine) { 
        OutputCallbackMessage("SysUserSpi::pRtnTradeOrderRttCutLine is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnTradeOrderRttCutLine->MonDate: ", pRtnTradeOrderRttCutLine->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnTradeOrderRttCutLine->OrderRttCutLine: ", pRtnTradeOrderRttCutLine->OrderRttCutLine, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnTradeOrderRttCutLineTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnTradeOrderRttCutLineTopic_IOUser_vec.begin();
        it != g_RtnTradeOrderRttCutLineTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnTradeOrderRttCutLineTopic_IOUser_vec.end()) {
        g_RtnTradeOrderRttCutLineTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnTradeOrderRttCutLineTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnTradeOrderRttCutLineTopic_mutex);

    uv_async_send(&g_RtnTradeOrderRttCutLineTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnTradeOrderRttCutLineTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryClientInfoTopic(CShfeFtdcRspQryClientInfoField* pRspQryClientInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryClientInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryClientInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryClientInfoField* pNewRspQryClientInfo = NULL;
    if (NULL != pRspQryClientInfo) { 
        pNewRspQryClientInfo = new CShfeFtdcRspQryClientInfoField;
        if (NULL == pNewRspQryClientInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryClientInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryClientInfo,pRspQryClientInfo, sizeof(CShfeFtdcRspQryClientInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryClientInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryClientInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryClientInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryClientInfo->ClientID: ", pRspQryClientInfo->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->ClientName: ", pRspQryClientInfo->ClientName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->IdentifiedCardType: ", pRspQryClientInfo->IdentifiedCardType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->IdentifiedCardNo: ", pRspQryClientInfo->IdentifiedCardNo, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->TradingRole: ", pRspQryClientInfo->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->ClientType: ", pRspQryClientInfo->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->IsActive: ", pRspQryClientInfo->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRspQryClientInfo->OperationType: ", pRspQryClientInfo->OperationType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryClientInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryClientInfoTopic_IOUser_vec.begin();
        it != g_RspQryClientInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryClientInfoTopic_IOUser_vec.end()) {
        g_RspQryClientInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryClientInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryClientInfoTopic_mutex);

    uv_async_send(&g_RspQryClientInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryClientInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnClientInfoTopic(CShfeFtdcRtnClientInfoField* pRtnClientInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnClientInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnClientInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnClientInfoField* pNewRtnClientInfo = NULL;
    if (NULL != pRtnClientInfo) { 
        pNewRtnClientInfo = new CShfeFtdcRtnClientInfoField;
        if (NULL == pNewRtnClientInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnClientInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnClientInfo,pRtnClientInfo, sizeof(CShfeFtdcRtnClientInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnClientInfo;
    if (NULL == pRtnClientInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnClientInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnClientInfo->ClientID: ", pRtnClientInfo->ClientID, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->ClientName: ", pRtnClientInfo->ClientName, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->IdentifiedCardType: ", pRtnClientInfo->IdentifiedCardType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->IdentifiedCardNo: ", pRtnClientInfo->IdentifiedCardNo, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->TradingRole: ", pRtnClientInfo->TradingRole, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->ClientType: ", pRtnClientInfo->ClientType, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->IsActive: ", pRtnClientInfo->IsActive, g_RunningResult_File);
        OutputCallbackMessage("pRtnClientInfo->OperationType: ", pRtnClientInfo->OperationType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnClientInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnClientInfoTopic_IOUser_vec.begin();
        it != g_RtnClientInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnClientInfoTopic_IOUser_vec.end()) {
        g_RtnClientInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnClientInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnClientInfoTopic_mutex);

    uv_async_send(&g_RtnClientInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnClientInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryEventDescriptionTopic(CShfeFtdcRspQryEventDescriptionField* pRspQryEventDescription, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryEventDescriptionTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryEventDescriptionTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryEventDescriptionField* pNewRspQryEventDescription = NULL;
    if (NULL != pRspQryEventDescription) { 
        pNewRspQryEventDescription = new CShfeFtdcRspQryEventDescriptionField;
        if (NULL == pNewRspQryEventDescription) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryEventDescription", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryEventDescription,pRspQryEventDescription, sizeof(CShfeFtdcRspQryEventDescriptionField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryEventDescription;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryEventDescription) { 
        OutputCallbackMessage("SysUserSpi::pRspQryEventDescription is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryEventDescription->EventDesID: ", pRspQryEventDescription->EventDesID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryEventDescription->UserName: ", pRspQryEventDescription->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryEventDescription->MonDate: ", pRspQryEventDescription->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryEventDescription->MonTime: ", pRspQryEventDescription->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryEventDescription->EventDes: ", pRspQryEventDescription->EventDes, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryEventDescriptionTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryEventDescriptionTopic_IOUser_vec.begin();
        it != g_RspQryEventDescriptionTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryEventDescriptionTopic_IOUser_vec.end()) {
        g_RspQryEventDescriptionTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryEventDescriptionTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryEventDescriptionTopic_mutex);

    uv_async_send(&g_RspQryEventDescriptionTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryEventDescriptionTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnEventDescriptionTopic(CShfeFtdcRtnEventDescriptionField* pRtnEventDescription){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnEventDescriptionTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnEventDescriptionTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnEventDescriptionField* pNewRtnEventDescription = NULL;
    if (NULL != pRtnEventDescription) { 
        pNewRtnEventDescription = new CShfeFtdcRtnEventDescriptionField;
        if (NULL == pNewRtnEventDescription) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnEventDescription", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnEventDescription,pRtnEventDescription, sizeof(CShfeFtdcRtnEventDescriptionField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnEventDescription;
    if (NULL == pRtnEventDescription) { 
        OutputCallbackMessage("SysUserSpi::pRtnEventDescription is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnEventDescription->EventDesID: ", pRtnEventDescription->EventDesID, g_RunningResult_File);
        OutputCallbackMessage("pRtnEventDescription->UserName: ", pRtnEventDescription->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRtnEventDescription->MonDate: ", pRtnEventDescription->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnEventDescription->MonTime: ", pRtnEventDescription->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnEventDescription->EventDes: ", pRtnEventDescription->EventDes, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnEventDescriptionTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnEventDescriptionTopic_IOUser_vec.begin();
        it != g_RtnEventDescriptionTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnEventDescriptionTopic_IOUser_vec.end()) {
        g_RtnEventDescriptionTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnEventDescriptionTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnEventDescriptionTopic_mutex);

    uv_async_send(&g_RtnEventDescriptionTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnEventDescriptionTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFrontUniqueIDTopic(CShfeFtdcRspQryFrontUniqueIDField* pRspQryFrontUniqueID, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFrontUniqueIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFrontUniqueIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFrontUniqueIDField* pNewRspQryFrontUniqueID = NULL;
    if (NULL != pRspQryFrontUniqueID) { 
        pNewRspQryFrontUniqueID = new CShfeFtdcRspQryFrontUniqueIDField;
        if (NULL == pNewRspQryFrontUniqueID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFrontUniqueID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFrontUniqueID,pRspQryFrontUniqueID, sizeof(CShfeFtdcRspQryFrontUniqueIDField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFrontUniqueID;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFrontUniqueID) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFrontUniqueID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFrontUniqueID->FrontID: ", pRspQryFrontUniqueID->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFrontUniqueID->FrontName: ", pRspQryFrontUniqueID->FrontName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFrontUniqueIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFrontUniqueIDTopic_IOUser_vec.begin();
        it != g_RspQryFrontUniqueIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFrontUniqueIDTopic_IOUser_vec.end()) {
        g_RspQryFrontUniqueIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFrontUniqueIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFrontUniqueIDTopic_mutex);

    uv_async_send(&g_RspQryFrontUniqueIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFrontUniqueIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFrontUniqueIDTopic(CShfeFtdcRtnFrontUniqueIDField* pRtnFrontUniqueID){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFrontUniqueIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFrontUniqueIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFrontUniqueIDField* pNewRtnFrontUniqueID = NULL;
    if (NULL != pRtnFrontUniqueID) { 
        pNewRtnFrontUniqueID = new CShfeFtdcRtnFrontUniqueIDField;
        if (NULL == pNewRtnFrontUniqueID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFrontUniqueID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFrontUniqueID,pRtnFrontUniqueID, sizeof(CShfeFtdcRtnFrontUniqueIDField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFrontUniqueID;
    if (NULL == pRtnFrontUniqueID) { 
        OutputCallbackMessage("SysUserSpi::pRtnFrontUniqueID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFrontUniqueID->FrontID: ", pRtnFrontUniqueID->FrontID, g_RunningResult_File);
        OutputCallbackMessage("pRtnFrontUniqueID->FrontName: ", pRtnFrontUniqueID->FrontName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFrontUniqueIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFrontUniqueIDTopic_IOUser_vec.begin();
        it != g_RtnFrontUniqueIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFrontUniqueIDTopic_IOUser_vec.end()) {
        g_RtnFrontUniqueIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFrontUniqueIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFrontUniqueIDTopic_mutex);

    uv_async_send(&g_RtnFrontUniqueIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFrontUniqueIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetPartyLinkAddrChangeTopic(CShfeFtdcRspQryNetPartyLinkAddrChangeField* pRspQryNetPartyLinkAddrChange, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetPartyLinkAddrChangeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkAddrChangeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetPartyLinkAddrChangeField* pNewRspQryNetPartyLinkAddrChange = NULL;
    if (NULL != pRspQryNetPartyLinkAddrChange) { 
        pNewRspQryNetPartyLinkAddrChange = new CShfeFtdcRspQryNetPartyLinkAddrChangeField;
        if (NULL == pNewRspQryNetPartyLinkAddrChange) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetPartyLinkAddrChange", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetPartyLinkAddrChange,pRspQryNetPartyLinkAddrChange, sizeof(CShfeFtdcRspQryNetPartyLinkAddrChangeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetPartyLinkAddrChange;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetPartyLinkAddrChange) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetPartyLinkAddrChange is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->OperationType: ", pRspQryNetPartyLinkAddrChange->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->ID: ", pRspQryNetPartyLinkAddrChange->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->RelationID: ", pRspQryNetPartyLinkAddrChange->RelationID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->OLDADDRESS: ", pRspQryNetPartyLinkAddrChange->OLDADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->NEWADDRESS: ", pRspQryNetPartyLinkAddrChange->NEWADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->OPERATOR: ", pRspQryNetPartyLinkAddrChange->OPERATOR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->MonDate: ", pRspQryNetPartyLinkAddrChange->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkAddrChange->MonTime: ", pRspQryNetPartyLinkAddrChange->MonTime, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetPartyLinkAddrChangeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetPartyLinkAddrChangeTopic_IOUser_vec.begin();
        it != g_RspQryNetPartyLinkAddrChangeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetPartyLinkAddrChangeTopic_IOUser_vec.end()) {
        g_RspQryNetPartyLinkAddrChangeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetPartyLinkAddrChangeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetPartyLinkAddrChangeTopic_mutex);

    uv_async_send(&g_RspQryNetPartyLinkAddrChangeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkAddrChangeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetPartyLinkAddrChangeTopic(CShfeFtdcRtnNetPartyLinkAddrChangeField* pRtnNetPartyLinkAddrChange){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetPartyLinkAddrChangeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkAddrChangeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetPartyLinkAddrChangeField* pNewRtnNetPartyLinkAddrChange = NULL;
    if (NULL != pRtnNetPartyLinkAddrChange) { 
        pNewRtnNetPartyLinkAddrChange = new CShfeFtdcRtnNetPartyLinkAddrChangeField;
        if (NULL == pNewRtnNetPartyLinkAddrChange) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetPartyLinkAddrChange", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetPartyLinkAddrChange,pRtnNetPartyLinkAddrChange, sizeof(CShfeFtdcRtnNetPartyLinkAddrChangeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetPartyLinkAddrChange;
    if (NULL == pRtnNetPartyLinkAddrChange) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetPartyLinkAddrChange is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->OperationType: ", pRtnNetPartyLinkAddrChange->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->ID: ", pRtnNetPartyLinkAddrChange->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->RelationID: ", pRtnNetPartyLinkAddrChange->RelationID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->OLDADDRESS: ", pRtnNetPartyLinkAddrChange->OLDADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->NEWADDRESS: ", pRtnNetPartyLinkAddrChange->NEWADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->OPERATOR: ", pRtnNetPartyLinkAddrChange->OPERATOR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->MonDate: ", pRtnNetPartyLinkAddrChange->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkAddrChange->MonTime: ", pRtnNetPartyLinkAddrChange->MonTime, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetPartyLinkAddrChangeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetPartyLinkAddrChangeTopic_IOUser_vec.begin();
        it != g_RtnNetPartyLinkAddrChangeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetPartyLinkAddrChangeTopic_IOUser_vec.end()) {
        g_RtnNetPartyLinkAddrChangeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetPartyLinkAddrChangeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetPartyLinkAddrChangeTopic_mutex);

    uv_async_send(&g_RtnNetPartyLinkAddrChangeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkAddrChangeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDelPartyLinkInfoTopic(CShfeFtdcRspQryNetDelPartyLinkInfoField* pRspQryNetDelPartyLinkInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDelPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDelPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDelPartyLinkInfoField* pNewRspQryNetDelPartyLinkInfo = NULL;
    if (NULL != pRspQryNetDelPartyLinkInfo) { 
        pNewRspQryNetDelPartyLinkInfo = new CShfeFtdcRspQryNetDelPartyLinkInfoField;
        if (NULL == pNewRspQryNetDelPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDelPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDelPartyLinkInfo,pRspQryNetDelPartyLinkInfo, sizeof(CShfeFtdcRspQryNetDelPartyLinkInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDelPartyLinkInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDelPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDelPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->OperationType: ", pRspQryNetDelPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->ID: ", pRspQryNetDelPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->MEMBER_NO: ", pRspQryNetDelPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->MEMBER_NAME: ", pRspQryNetDelPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->REMOTE_ADDR: ", pRspQryNetDelPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->LOCAL_ADDR: ", pRspQryNetDelPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->ADDRESS: ", pRspQryNetDelPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->LINE_STATUS: ", pRspQryNetDelPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->CONTACT: ", pRspQryNetDelPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->TELEPHONE: ", pRspQryNetDelPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->MOBILEPHONE: ", pRspQryNetDelPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->EMAIL: ", pRspQryNetDelPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->FAX: ", pRspQryNetDelPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->PROVINCE: ", pRspQryNetDelPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->DDN_NO: ", pRspQryNetDelPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IN_MODE: ", pRspQryNetDelPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IP_WAN: ", pRspQryNetDelPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IP_LAN: ", pRspQryNetDelPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IPADDR: ", pRspQryNetDelPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->Interface: ", pRspQryNetDelPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->INTERFACE_DATE: ", pRspQryNetDelPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->SOFTWARE: ", pRspQryNetDelPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->FEE_TYPE: ", pRspQryNetDelPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->SERVICEPROVIDER: ", pRspQryNetDelPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IF_ZIYING: ", pRspQryNetDelPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->IF_TUOGUAN: ", pRspQryNetDelPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->HASOTHER: ", pRspQryNetDelPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->SEAT_NO: ", pRspQryNetDelPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDelPartyLinkInfo->PRO: ", pRspQryNetDelPartyLinkInfo->PRO, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDelPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDelPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetDelPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDelPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RspQryNetDelPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDelPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDelPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RspQryNetDelPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDelPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDelPartyLinkInfoTopic(CShfeFtdcRtnNetDelPartyLinkInfoField* pRtnNetDelPartyLinkInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDelPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDelPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDelPartyLinkInfoField* pNewRtnNetDelPartyLinkInfo = NULL;
    if (NULL != pRtnNetDelPartyLinkInfo) { 
        pNewRtnNetDelPartyLinkInfo = new CShfeFtdcRtnNetDelPartyLinkInfoField;
        if (NULL == pNewRtnNetDelPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDelPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDelPartyLinkInfo,pRtnNetDelPartyLinkInfo, sizeof(CShfeFtdcRtnNetDelPartyLinkInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDelPartyLinkInfo;
    if (NULL == pRtnNetDelPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDelPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->OperationType: ", pRtnNetDelPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->ID: ", pRtnNetDelPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->MEMBER_NO: ", pRtnNetDelPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->MEMBER_NAME: ", pRtnNetDelPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->REMOTE_ADDR: ", pRtnNetDelPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->LOCAL_ADDR: ", pRtnNetDelPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->ADDRESS: ", pRtnNetDelPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->LINE_STATUS: ", pRtnNetDelPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->CONTACT: ", pRtnNetDelPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->TELEPHONE: ", pRtnNetDelPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->MOBILEPHONE: ", pRtnNetDelPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->EMAIL: ", pRtnNetDelPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->FAX: ", pRtnNetDelPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->PROVINCE: ", pRtnNetDelPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->DDN_NO: ", pRtnNetDelPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IN_MODE: ", pRtnNetDelPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IP_WAN: ", pRtnNetDelPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IP_LAN: ", pRtnNetDelPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IPADDR: ", pRtnNetDelPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->Interface: ", pRtnNetDelPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->INTERFACE_DATE: ", pRtnNetDelPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->SOFTWARE: ", pRtnNetDelPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->FEE_TYPE: ", pRtnNetDelPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->SERVICEPROVIDER: ", pRtnNetDelPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IF_ZIYING: ", pRtnNetDelPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->IF_TUOGUAN: ", pRtnNetDelPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->HASOTHER: ", pRtnNetDelPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->SEAT_NO: ", pRtnNetDelPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDelPartyLinkInfo->PRO: ", pRtnNetDelPartyLinkInfo->PRO, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDelPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDelPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RtnNetDelPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDelPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RtnNetDelPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDelPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDelPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RtnNetDelPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDelPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryPerformanceTopTopic(CShfeFtdcRspQryPerformanceTopField* pRspQryPerformanceTop, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryPerformanceTopTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryPerformanceTopTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryPerformanceTopField* pNewRspQryPerformanceTop = NULL;
    if (NULL != pRspQryPerformanceTop) { 
        pNewRspQryPerformanceTop = new CShfeFtdcRspQryPerformanceTopField;
        if (NULL == pNewRspQryPerformanceTop) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryPerformanceTop", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryPerformanceTop,pRspQryPerformanceTop, sizeof(CShfeFtdcRspQryPerformanceTopField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryPerformanceTop;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryPerformanceTop) { 
        OutputCallbackMessage("SysUserSpi::pRspQryPerformanceTop is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryPerformanceTop->OperationType: ", pRspQryPerformanceTop->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->AttrType: ", pRspQryPerformanceTop->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->NetArea: ", pRspQryPerformanceTop->NetArea, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->NetSubArea: ", pRspQryPerformanceTop->NetSubArea, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->KeyWord: ", pRspQryPerformanceTop->KeyWord, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->SortValue: ", pRspQryPerformanceTop->SortValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->SortType: ", pRspQryPerformanceTop->SortType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->DuringTimeType: ", pRspQryPerformanceTop->DuringTimeType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->DuringTimeValue: ", pRspQryPerformanceTop->DuringTimeValue, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->TopN: ", pRspQryPerformanceTop->TopN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryPerformanceTop->TopResult: ", pRspQryPerformanceTop->TopResult, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryPerformanceTopTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryPerformanceTopTopic_IOUser_vec.begin();
        it != g_RspQryPerformanceTopTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryPerformanceTopTopic_IOUser_vec.end()) {
        g_RspQryPerformanceTopTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryPerformanceTopTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryPerformanceTopTopic_mutex);

    uv_async_send(&g_RspQryPerformanceTopTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryPerformanceTopTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnPerformanceTopTopic(CShfeFtdcRtnPerformanceTopField* pRtnPerformanceTop){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnPerformanceTopTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnPerformanceTopTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnPerformanceTopField* pNewRtnPerformanceTop = NULL;
    if (NULL != pRtnPerformanceTop) { 
        pNewRtnPerformanceTop = new CShfeFtdcRtnPerformanceTopField;
        if (NULL == pNewRtnPerformanceTop) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnPerformanceTop", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnPerformanceTop,pRtnPerformanceTop, sizeof(CShfeFtdcRtnPerformanceTopField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnPerformanceTop;
    if (NULL == pRtnPerformanceTop) { 
        OutputCallbackMessage("SysUserSpi::pRtnPerformanceTop is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnPerformanceTop->OperationType: ", pRtnPerformanceTop->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->AttrType: ", pRtnPerformanceTop->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->NetArea: ", pRtnPerformanceTop->NetArea, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->NetSubArea: ", pRtnPerformanceTop->NetSubArea, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->KeyWord: ", pRtnPerformanceTop->KeyWord, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->SortValue: ", pRtnPerformanceTop->SortValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->SortType: ", pRtnPerformanceTop->SortType, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->DuringTimeType: ", pRtnPerformanceTop->DuringTimeType, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->DuringTimeValue: ", pRtnPerformanceTop->DuringTimeValue, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->TopN: ", pRtnPerformanceTop->TopN, g_RunningResult_File);
        OutputCallbackMessage("pRtnPerformanceTop->TopResult: ", pRtnPerformanceTop->TopResult, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnPerformanceTopTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnPerformanceTopTopic_IOUser_vec.begin();
        it != g_RtnPerformanceTopTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnPerformanceTopTopic_IOUser_vec.end()) {
        g_RtnPerformanceTopTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnPerformanceTopTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnPerformanceTopTopic_mutex);

    uv_async_send(&g_RtnPerformanceTopTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnPerformanceTopTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryInstrumentStatusTopic(CShfeFtdcRspQryInstrumentStatusField* pRspQryInstrumentStatus, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryInstrumentStatusTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryInstrumentStatusTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryInstrumentStatusField* pNewRspQryInstrumentStatus = NULL;
    if (NULL != pRspQryInstrumentStatus) { 
        pNewRspQryInstrumentStatus = new CShfeFtdcRspQryInstrumentStatusField;
        if (NULL == pNewRspQryInstrumentStatus) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryInstrumentStatus", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryInstrumentStatus,pRspQryInstrumentStatus, sizeof(CShfeFtdcRspQryInstrumentStatusField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryInstrumentStatus;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryInstrumentStatus) { 
        OutputCallbackMessage("SysUserSpi::pRspQryInstrumentStatus is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryInstrumentStatus->SettlementGroupID: ", pRspQryInstrumentStatus->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->InstrumentID: ", pRspQryInstrumentStatus->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->InstrumentStatus: ", pRspQryInstrumentStatus->InstrumentStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->TradingSegmentSN: ", pRspQryInstrumentStatus->TradingSegmentSN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->EnterTime: ", pRspQryInstrumentStatus->EnterTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->EnterReason: ", pRspQryInstrumentStatus->EnterReason, g_RunningResult_File);
        OutputCallbackMessage("pRspQryInstrumentStatus->EnterDate: ", pRspQryInstrumentStatus->EnterDate, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryInstrumentStatusTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryInstrumentStatusTopic_IOUser_vec.begin();
        it != g_RspQryInstrumentStatusTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryInstrumentStatusTopic_IOUser_vec.end()) {
        g_RspQryInstrumentStatusTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryInstrumentStatusTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryInstrumentStatusTopic_mutex);

    uv_async_send(&g_RspQryInstrumentStatusTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryInstrumentStatusTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnInstrumentStatusTopic(CShfeFtdcRtnInstrumentStatusField* pRtnInstrumentStatus){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnInstrumentStatusTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnInstrumentStatusTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnInstrumentStatusField* pNewRtnInstrumentStatus = NULL;
    if (NULL != pRtnInstrumentStatus) { 
        pNewRtnInstrumentStatus = new CShfeFtdcRtnInstrumentStatusField;
        if (NULL == pNewRtnInstrumentStatus) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnInstrumentStatus", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnInstrumentStatus,pRtnInstrumentStatus, sizeof(CShfeFtdcRtnInstrumentStatusField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnInstrumentStatus;
    if (NULL == pRtnInstrumentStatus) { 
        OutputCallbackMessage("SysUserSpi::pRtnInstrumentStatus is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnInstrumentStatus->SettlementGroupID: ", pRtnInstrumentStatus->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->InstrumentID: ", pRtnInstrumentStatus->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->InstrumentStatus: ", pRtnInstrumentStatus->InstrumentStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->TradingSegmentSN: ", pRtnInstrumentStatus->TradingSegmentSN, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->EnterTime: ", pRtnInstrumentStatus->EnterTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->EnterReason: ", pRtnInstrumentStatus->EnterReason, g_RunningResult_File);
        OutputCallbackMessage("pRtnInstrumentStatus->EnterDate: ", pRtnInstrumentStatus->EnterDate, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnInstrumentStatusTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnInstrumentStatusTopic_IOUser_vec.begin();
        it != g_RtnInstrumentStatusTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnInstrumentStatusTopic_IOUser_vec.end()) {
        g_RtnInstrumentStatusTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnInstrumentStatusTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnInstrumentStatusTopic_mutex);

    uv_async_send(&g_RtnInstrumentStatusTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnInstrumentStatusTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryCurrTradingSegmentAttrTopic(CShfeFtdcRspQryCurrTradingSegmentAttrField* pRspQryCurrTradingSegmentAttr, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryCurrTradingSegmentAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryCurrTradingSegmentAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryCurrTradingSegmentAttrField* pNewRspQryCurrTradingSegmentAttr = NULL;
    if (NULL != pRspQryCurrTradingSegmentAttr) { 
        pNewRspQryCurrTradingSegmentAttr = new CShfeFtdcRspQryCurrTradingSegmentAttrField;
        if (NULL == pNewRspQryCurrTradingSegmentAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryCurrTradingSegmentAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryCurrTradingSegmentAttr,pRspQryCurrTradingSegmentAttr, sizeof(CShfeFtdcRspQryCurrTradingSegmentAttrField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryCurrTradingSegmentAttr;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryCurrTradingSegmentAttr) { 
        OutputCallbackMessage("SysUserSpi::pRspQryCurrTradingSegmentAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->SettlementGroupID: ", pRspQryCurrTradingSegmentAttr->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->TradingSegmentSN: ", pRspQryCurrTradingSegmentAttr->TradingSegmentSN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->TradingSegmentName: ", pRspQryCurrTradingSegmentAttr->TradingSegmentName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->StartTime: ", pRspQryCurrTradingSegmentAttr->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->InstrumentStatus: ", pRspQryCurrTradingSegmentAttr->InstrumentStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->InstrumentID: ", pRspQryCurrTradingSegmentAttr->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryCurrTradingSegmentAttr->AdvanceDays: ", pRspQryCurrTradingSegmentAttr->AdvanceDays, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryCurrTradingSegmentAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryCurrTradingSegmentAttrTopic_IOUser_vec.begin();
        it != g_RspQryCurrTradingSegmentAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryCurrTradingSegmentAttrTopic_IOUser_vec.end()) {
        g_RspQryCurrTradingSegmentAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryCurrTradingSegmentAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryCurrTradingSegmentAttrTopic_mutex);

    uv_async_send(&g_RspQryCurrTradingSegmentAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryCurrTradingSegmentAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnCurrTradingSegmentAttrTopic(CShfeFtdcRtnCurrTradingSegmentAttrField* pRtnCurrTradingSegmentAttr){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnCurrTradingSegmentAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnCurrTradingSegmentAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnCurrTradingSegmentAttrField* pNewRtnCurrTradingSegmentAttr = NULL;
    if (NULL != pRtnCurrTradingSegmentAttr) { 
        pNewRtnCurrTradingSegmentAttr = new CShfeFtdcRtnCurrTradingSegmentAttrField;
        if (NULL == pNewRtnCurrTradingSegmentAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnCurrTradingSegmentAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnCurrTradingSegmentAttr,pRtnCurrTradingSegmentAttr, sizeof(CShfeFtdcRtnCurrTradingSegmentAttrField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnCurrTradingSegmentAttr;
    if (NULL == pRtnCurrTradingSegmentAttr) { 
        OutputCallbackMessage("SysUserSpi::pRtnCurrTradingSegmentAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->SettlementGroupID: ", pRtnCurrTradingSegmentAttr->SettlementGroupID, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->TradingSegmentSN: ", pRtnCurrTradingSegmentAttr->TradingSegmentSN, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->TradingSegmentName: ", pRtnCurrTradingSegmentAttr->TradingSegmentName, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->StartTime: ", pRtnCurrTradingSegmentAttr->StartTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->InstrumentStatus: ", pRtnCurrTradingSegmentAttr->InstrumentStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->InstrumentID: ", pRtnCurrTradingSegmentAttr->InstrumentID, g_RunningResult_File);
        OutputCallbackMessage("pRtnCurrTradingSegmentAttr->AdvanceDays: ", pRtnCurrTradingSegmentAttr->AdvanceDays, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnCurrTradingSegmentAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnCurrTradingSegmentAttrTopic_IOUser_vec.begin();
        it != g_RtnCurrTradingSegmentAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnCurrTradingSegmentAttrTopic_IOUser_vec.end()) {
        g_RtnCurrTradingSegmentAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnCurrTradingSegmentAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnCurrTradingSegmentAttrTopic_mutex);

    uv_async_send(&g_RtnCurrTradingSegmentAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnCurrTradingSegmentAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetAreaTopic(CShfeFtdcRspQryNetAreaField* pRspQryNetArea, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetAreaTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetAreaTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetAreaField* pNewRspQryNetArea = NULL;
    if (NULL != pRspQryNetArea) { 
        pNewRspQryNetArea = new CShfeFtdcRspQryNetAreaField;
        if (NULL == pNewRspQryNetArea) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetArea", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetArea,pRspQryNetArea, sizeof(CShfeFtdcRspQryNetAreaField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetArea;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetArea) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetArea is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetArea->OperationType: ", pRspQryNetArea->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetArea->ID: ", pRspQryNetArea->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetArea->CName: ", pRspQryNetArea->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetArea->EName: ", pRspQryNetArea->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetAreaTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetAreaTopic_IOUser_vec.begin();
        it != g_RspQryNetAreaTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetAreaTopic_IOUser_vec.end()) {
        g_RspQryNetAreaTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetAreaTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetAreaTopic_mutex);

    uv_async_send(&g_RspQryNetAreaTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetAreaTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetAreaTopic(CShfeFtdcRtnNetAreaField* pRtnNetArea){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetAreaTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetAreaTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetAreaField* pNewRtnNetArea = NULL;
    if (NULL != pRtnNetArea) { 
        pNewRtnNetArea = new CShfeFtdcRtnNetAreaField;
        if (NULL == pNewRtnNetArea) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetArea", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetArea,pRtnNetArea, sizeof(CShfeFtdcRtnNetAreaField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetArea;
    if (NULL == pRtnNetArea) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetArea is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetArea->OperationType: ", pRtnNetArea->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetArea->ID: ", pRtnNetArea->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetArea->CName: ", pRtnNetArea->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetArea->EName: ", pRtnNetArea->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetAreaTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetAreaTopic_IOUser_vec.begin();
        it != g_RtnNetAreaTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetAreaTopic_IOUser_vec.end()) {
        g_RtnNetAreaTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetAreaTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetAreaTopic_mutex);

    uv_async_send(&g_RtnNetAreaTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetAreaTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetSubAreaTopic(CShfeFtdcRspQryNetSubAreaField* pRspQryNetSubArea, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetSubAreaTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetSubAreaTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetSubAreaField* pNewRspQryNetSubArea = NULL;
    if (NULL != pRspQryNetSubArea) { 
        pNewRspQryNetSubArea = new CShfeFtdcRspQryNetSubAreaField;
        if (NULL == pNewRspQryNetSubArea) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetSubArea", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetSubArea,pRspQryNetSubArea, sizeof(CShfeFtdcRspQryNetSubAreaField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetSubArea;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetSubArea) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetSubArea is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetSubArea->OperationType: ", pRspQryNetSubArea->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubArea->ID: ", pRspQryNetSubArea->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubArea->SysNetAreaID: ", pRspQryNetSubArea->SysNetAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubArea->CName: ", pRspQryNetSubArea->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubArea->EName: ", pRspQryNetSubArea->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetSubAreaTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetSubAreaTopic_IOUser_vec.begin();
        it != g_RspQryNetSubAreaTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetSubAreaTopic_IOUser_vec.end()) {
        g_RspQryNetSubAreaTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetSubAreaTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetSubAreaTopic_mutex);

    uv_async_send(&g_RspQryNetSubAreaTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetSubAreaTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetSubAreaTopic(CShfeFtdcRtnNetSubAreaField* pRtnNetSubArea){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetSubAreaTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetSubAreaTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetSubAreaField* pNewRtnNetSubArea = NULL;
    if (NULL != pRtnNetSubArea) { 
        pNewRtnNetSubArea = new CShfeFtdcRtnNetSubAreaField;
        if (NULL == pNewRtnNetSubArea) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetSubArea", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetSubArea,pRtnNetSubArea, sizeof(CShfeFtdcRtnNetSubAreaField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetSubArea;
    if (NULL == pRtnNetSubArea) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetSubArea is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetSubArea->OperationType: ", pRtnNetSubArea->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubArea->ID: ", pRtnNetSubArea->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubArea->SysNetAreaID: ", pRtnNetSubArea->SysNetAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubArea->CName: ", pRtnNetSubArea->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubArea->EName: ", pRtnNetSubArea->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetSubAreaTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetSubAreaTopic_IOUser_vec.begin();
        it != g_RtnNetSubAreaTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetSubAreaTopic_IOUser_vec.end()) {
        g_RtnNetSubAreaTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetSubAreaTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetSubAreaTopic_mutex);

    uv_async_send(&g_RtnNetSubAreaTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetSubAreaTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetSubAreaIPTopic(CShfeFtdcRspQryNetSubAreaIPField* pRspQryNetSubAreaIP, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetSubAreaIPTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetSubAreaIPTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetSubAreaIPField* pNewRspQryNetSubAreaIP = NULL;
    if (NULL != pRspQryNetSubAreaIP) { 
        pNewRspQryNetSubAreaIP = new CShfeFtdcRspQryNetSubAreaIPField;
        if (NULL == pNewRspQryNetSubAreaIP) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetSubAreaIP", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetSubAreaIP,pRspQryNetSubAreaIP, sizeof(CShfeFtdcRspQryNetSubAreaIPField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetSubAreaIP;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetSubAreaIP) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetSubAreaIP is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetSubAreaIP->OperationType: ", pRspQryNetSubAreaIP->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubAreaIP->ID: ", pRspQryNetSubAreaIP->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubAreaIP->SysNetSubAreaID: ", pRspQryNetSubAreaIP->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubAreaIP->IP: ", pRspQryNetSubAreaIP->IP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetSubAreaIP->Mask: ", pRspQryNetSubAreaIP->Mask, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetSubAreaIPTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetSubAreaIPTopic_IOUser_vec.begin();
        it != g_RspQryNetSubAreaIPTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetSubAreaIPTopic_IOUser_vec.end()) {
        g_RspQryNetSubAreaIPTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetSubAreaIPTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetSubAreaIPTopic_mutex);

    uv_async_send(&g_RspQryNetSubAreaIPTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetSubAreaIPTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetSubAreaIPTopic(CShfeFtdcRtnNetSubAreaIPField* pRtnNetSubAreaIP){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetSubAreaIPTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetSubAreaIPTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetSubAreaIPField* pNewRtnNetSubAreaIP = NULL;
    if (NULL != pRtnNetSubAreaIP) { 
        pNewRtnNetSubAreaIP = new CShfeFtdcRtnNetSubAreaIPField;
        if (NULL == pNewRtnNetSubAreaIP) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetSubAreaIP", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetSubAreaIP,pRtnNetSubAreaIP, sizeof(CShfeFtdcRtnNetSubAreaIPField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetSubAreaIP;
    if (NULL == pRtnNetSubAreaIP) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetSubAreaIP is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetSubAreaIP->OperationType: ", pRtnNetSubAreaIP->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubAreaIP->ID: ", pRtnNetSubAreaIP->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubAreaIP->SysNetSubAreaID: ", pRtnNetSubAreaIP->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubAreaIP->IP: ", pRtnNetSubAreaIP->IP, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetSubAreaIP->Mask: ", pRtnNetSubAreaIP->Mask, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetSubAreaIPTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetSubAreaIPTopic_IOUser_vec.begin();
        it != g_RtnNetSubAreaIPTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetSubAreaIPTopic_IOUser_vec.end()) {
        g_RtnNetSubAreaIPTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetSubAreaIPTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetSubAreaIPTopic_mutex);

    uv_async_send(&g_RtnNetSubAreaIPTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetSubAreaIPTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceTopic(CShfeFtdcRspQryNetDeviceField* pRspQryNetDevice, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceField* pNewRspQryNetDevice = NULL;
    if (NULL != pRspQryNetDevice) { 
        pNewRspQryNetDevice = new CShfeFtdcRspQryNetDeviceField;
        if (NULL == pNewRspQryNetDevice) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDevice", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDevice,pRspQryNetDevice, sizeof(CShfeFtdcRspQryNetDeviceField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDevice;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDevice) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDevice is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDevice->OperationType: ", pRspQryNetDevice->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ID: ", pRspQryNetDevice->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ObjectID: ", pRspQryNetDevice->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->MonitorType_ID: ", pRspQryNetDevice->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->SysNetSubAreaID: ", pRspQryNetDevice->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->CATEGORY_ID: ", pRspQryNetDevice->CATEGORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->FuctionArea: ", pRspQryNetDevice->FuctionArea, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->IPADDR: ", pRspQryNetDevice->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->IPDECODE: ", pRspQryNetDevice->IPDECODE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->NAME: ", pRspQryNetDevice->NAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->PORTNUMBER: ", pRspQryNetDevice->PORTNUMBER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->CONFIGFILE: ", pRspQryNetDevice->CONFIGFILE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->RCOMMUNITY: ", pRspQryNetDevice->RCOMMUNITY, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->SNMPVERSION: ", pRspQryNetDevice->SNMPVERSION, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->RAMSIZE: ", pRspQryNetDevice->RAMSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->FLASHSIZE: ", pRspQryNetDevice->FLASHSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->NVRAMSIZE: ", pRspQryNetDevice->NVRAMSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->CABINET_ID: ", pRspQryNetDevice->CABINET_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ROOM_ID: ", pRspQryNetDevice->ROOM_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->IOSVERSION_ID: ", pRspQryNetDevice->IOSVERSION_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->DESCRIPTION: ", pRspQryNetDevice->DESCRIPTION, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->USERNAME: ", pRspQryNetDevice->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->PASSWD: ", pRspQryNetDevice->PASSWD, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ENPASSWD: ", pRspQryNetDevice->ENPASSWD, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->MANUFACTORY_ID: ", pRspQryNetDevice->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->CFGSAVETYPE: ", pRspQryNetDevice->CFGSAVETYPE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->DEVICETYPE: ", pRspQryNetDevice->DEVICETYPE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->SENDSMS: ", pRspQryNetDevice->SENDSMS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ISSNMP: ", pRspQryNetDevice->ISSNMP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->SLOTNUM: ", pRspQryNetDevice->SLOTNUM, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->ISPING: ", pRspQryNetDevice->ISPING, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->IFNUM: ", pRspQryNetDevice->IFNUM, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDevice->APPLICATION_ID: ", pRspQryNetDevice->APPLICATION_ID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDeviceTopic(CShfeFtdcRtnNetDeviceField* pRtnNetDevice){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDeviceTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDeviceField* pNewRtnNetDevice = NULL;
    if (NULL != pRtnNetDevice) { 
        pNewRtnNetDevice = new CShfeFtdcRtnNetDeviceField;
        if (NULL == pNewRtnNetDevice) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDevice", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDevice,pRtnNetDevice, sizeof(CShfeFtdcRtnNetDeviceField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDevice;
    if (NULL == pRtnNetDevice) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDevice is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDevice->OperationType: ", pRtnNetDevice->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ID: ", pRtnNetDevice->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ObjectID: ", pRtnNetDevice->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->MonitorType_ID: ", pRtnNetDevice->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->SysNetSubAreaID: ", pRtnNetDevice->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->CATEGORY_ID: ", pRtnNetDevice->CATEGORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->FuctionArea: ", pRtnNetDevice->FuctionArea, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->IPADDR: ", pRtnNetDevice->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->IPDECODE: ", pRtnNetDevice->IPDECODE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->NAME: ", pRtnNetDevice->NAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->PORTNUMBER: ", pRtnNetDevice->PORTNUMBER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->CONFIGFILE: ", pRtnNetDevice->CONFIGFILE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->RCOMMUNITY: ", pRtnNetDevice->RCOMMUNITY, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->SNMPVERSION: ", pRtnNetDevice->SNMPVERSION, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->RAMSIZE: ", pRtnNetDevice->RAMSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->FLASHSIZE: ", pRtnNetDevice->FLASHSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->NVRAMSIZE: ", pRtnNetDevice->NVRAMSIZE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->CABINET_ID: ", pRtnNetDevice->CABINET_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ROOM_ID: ", pRtnNetDevice->ROOM_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->IOSVERSION_ID: ", pRtnNetDevice->IOSVERSION_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->DESCRIPTION: ", pRtnNetDevice->DESCRIPTION, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->USERNAME: ", pRtnNetDevice->USERNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->PASSWD: ", pRtnNetDevice->PASSWD, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ENPASSWD: ", pRtnNetDevice->ENPASSWD, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->MANUFACTORY_ID: ", pRtnNetDevice->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->CFGSAVETYPE: ", pRtnNetDevice->CFGSAVETYPE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->DEVICETYPE: ", pRtnNetDevice->DEVICETYPE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->SENDSMS: ", pRtnNetDevice->SENDSMS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ISSNMP: ", pRtnNetDevice->ISSNMP, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->SLOTNUM: ", pRtnNetDevice->SLOTNUM, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->ISPING: ", pRtnNetDevice->ISPING, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->IFNUM: ", pRtnNetDevice->IFNUM, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDevice->APPLICATION_ID: ", pRtnNetDevice->APPLICATION_ID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDeviceTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDeviceTopic_IOUser_vec.begin();
        it != g_RtnNetDeviceTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDeviceTopic_IOUser_vec.end()) {
        g_RtnNetDeviceTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDeviceTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDeviceTopic_mutex);

    uv_async_send(&g_RtnNetDeviceTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceDetectTopic(CShfeFtdcRspQryNetDeviceDetectField* pRspQryNetDeviceDetect, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceDetectTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceDetectTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceDetectField* pNewRspQryNetDeviceDetect = NULL;
    if (NULL != pRspQryNetDeviceDetect) { 
        pNewRspQryNetDeviceDetect = new CShfeFtdcRspQryNetDeviceDetectField;
        if (NULL == pNewRspQryNetDeviceDetect) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDeviceDetect", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDeviceDetect,pRspQryNetDeviceDetect, sizeof(CShfeFtdcRspQryNetDeviceDetectField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDeviceDetect;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDeviceDetect) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDeviceDetect is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDeviceDetect->SysNetAreaID: ", pRspQryNetDeviceDetect->SysNetAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceDetect->SysNetSubAreaID: ", pRspQryNetDeviceDetect->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceDetect->IP: ", pRspQryNetDeviceDetect->IP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceDetect->Mask: ", pRspQryNetDeviceDetect->Mask, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceDetectTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceDetectTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceDetectTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceDetectTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceDetectTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceDetectTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceDetectTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceDetectTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceDetectTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetBuildingTopic(CShfeFtdcRspQryNetBuildingField* pRspQryNetBuilding, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetBuildingTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetBuildingTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetBuildingField* pNewRspQryNetBuilding = NULL;
    if (NULL != pRspQryNetBuilding) { 
        pNewRspQryNetBuilding = new CShfeFtdcRspQryNetBuildingField;
        if (NULL == pNewRspQryNetBuilding) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetBuilding", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetBuilding,pRspQryNetBuilding, sizeof(CShfeFtdcRspQryNetBuildingField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetBuilding;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetBuilding) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetBuilding is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetBuilding->OperationType: ", pRspQryNetBuilding->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBuilding->ID: ", pRspQryNetBuilding->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBuilding->CName: ", pRspQryNetBuilding->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBuilding->EName: ", pRspQryNetBuilding->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetBuildingTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetBuildingTopic_IOUser_vec.begin();
        it != g_RspQryNetBuildingTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetBuildingTopic_IOUser_vec.end()) {
        g_RspQryNetBuildingTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetBuildingTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetBuildingTopic_mutex);

    uv_async_send(&g_RspQryNetBuildingTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetBuildingTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetBuildingTopic(CShfeFtdcRtnNetBuildingField* pRtnNetBuilding){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetBuildingTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetBuildingTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetBuildingField* pNewRtnNetBuilding = NULL;
    if (NULL != pRtnNetBuilding) { 
        pNewRtnNetBuilding = new CShfeFtdcRtnNetBuildingField;
        if (NULL == pNewRtnNetBuilding) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetBuilding", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetBuilding,pRtnNetBuilding, sizeof(CShfeFtdcRtnNetBuildingField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetBuilding;
    if (NULL == pRtnNetBuilding) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetBuilding is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetBuilding->OperationType: ", pRtnNetBuilding->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBuilding->ID: ", pRtnNetBuilding->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBuilding->CName: ", pRtnNetBuilding->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBuilding->EName: ", pRtnNetBuilding->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetBuildingTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetBuildingTopic_IOUser_vec.begin();
        it != g_RtnNetBuildingTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetBuildingTopic_IOUser_vec.end()) {
        g_RtnNetBuildingTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetBuildingTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetBuildingTopic_mutex);

    uv_async_send(&g_RtnNetBuildingTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetBuildingTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetRoomTopic(CShfeFtdcRspQryNetRoomField* pRspQryNetRoom, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetRoomTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetRoomTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetRoomField* pNewRspQryNetRoom = NULL;
    if (NULL != pRspQryNetRoom) { 
        pNewRspQryNetRoom = new CShfeFtdcRspQryNetRoomField;
        if (NULL == pNewRspQryNetRoom) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetRoom", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetRoom,pRspQryNetRoom, sizeof(CShfeFtdcRspQryNetRoomField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetRoom;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetRoom) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetRoom is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetRoom->OperationType: ", pRspQryNetRoom->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRoom->ID: ", pRspQryNetRoom->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRoom->SysNetBuildingID: ", pRspQryNetRoom->SysNetBuildingID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRoom->CName: ", pRspQryNetRoom->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRoom->EName: ", pRspQryNetRoom->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetRoomTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetRoomTopic_IOUser_vec.begin();
        it != g_RspQryNetRoomTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetRoomTopic_IOUser_vec.end()) {
        g_RspQryNetRoomTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetRoomTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetRoomTopic_mutex);

    uv_async_send(&g_RspQryNetRoomTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetRoomTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetRoomTopic(CShfeFtdcRtnNetRoomField* pRtnNetRoom){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetRoomTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetRoomTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetRoomField* pNewRtnNetRoom = NULL;
    if (NULL != pRtnNetRoom) { 
        pNewRtnNetRoom = new CShfeFtdcRtnNetRoomField;
        if (NULL == pNewRtnNetRoom) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetRoom", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetRoom,pRtnNetRoom, sizeof(CShfeFtdcRtnNetRoomField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetRoom;
    if (NULL == pRtnNetRoom) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetRoom is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetRoom->OperationType: ", pRtnNetRoom->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRoom->ID: ", pRtnNetRoom->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRoom->SysNetBuildingID: ", pRtnNetRoom->SysNetBuildingID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRoom->CName: ", pRtnNetRoom->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRoom->EName: ", pRtnNetRoom->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetRoomTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetRoomTopic_IOUser_vec.begin();
        it != g_RtnNetRoomTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetRoomTopic_IOUser_vec.end()) {
        g_RtnNetRoomTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetRoomTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetRoomTopic_mutex);

    uv_async_send(&g_RtnNetRoomTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetRoomTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetCabinetsTopic(CShfeFtdcRspQryNetCabinetsField* pRspQryNetCabinets, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetCabinetsTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetCabinetsTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetCabinetsField* pNewRspQryNetCabinets = NULL;
    if (NULL != pRspQryNetCabinets) { 
        pNewRspQryNetCabinets = new CShfeFtdcRspQryNetCabinetsField;
        if (NULL == pNewRspQryNetCabinets) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetCabinets", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetCabinets,pRspQryNetCabinets, sizeof(CShfeFtdcRspQryNetCabinetsField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetCabinets;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetCabinets) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetCabinets is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetCabinets->OperationType: ", pRspQryNetCabinets->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->ID: ", pRspQryNetCabinets->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->SysNetRoomID: ", pRspQryNetCabinets->SysNetRoomID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->SysNetBuildingID: ", pRspQryNetCabinets->SysNetBuildingID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->CName: ", pRspQryNetCabinets->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->EName: ", pRspQryNetCabinets->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCabinets->CabinetsType: ", pRspQryNetCabinets->CabinetsType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetCabinetsTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetCabinetsTopic_IOUser_vec.begin();
        it != g_RspQryNetCabinetsTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetCabinetsTopic_IOUser_vec.end()) {
        g_RspQryNetCabinetsTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetCabinetsTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetCabinetsTopic_mutex);

    uv_async_send(&g_RspQryNetCabinetsTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetCabinetsTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetCabinetsTopic(CShfeFtdcRtnNetCabinetsField* pRtnNetCabinets){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetCabinetsTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetCabinetsTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetCabinetsField* pNewRtnNetCabinets = NULL;
    if (NULL != pRtnNetCabinets) { 
        pNewRtnNetCabinets = new CShfeFtdcRtnNetCabinetsField;
        if (NULL == pNewRtnNetCabinets) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetCabinets", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetCabinets,pRtnNetCabinets, sizeof(CShfeFtdcRtnNetCabinetsField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetCabinets;
    if (NULL == pRtnNetCabinets) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetCabinets is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetCabinets->OperationType: ", pRtnNetCabinets->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->ID: ", pRtnNetCabinets->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->SysNetRoomID: ", pRtnNetCabinets->SysNetRoomID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->SysNetBuildingID: ", pRtnNetCabinets->SysNetBuildingID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->CName: ", pRtnNetCabinets->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->EName: ", pRtnNetCabinets->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCabinets->CabinetsType: ", pRtnNetCabinets->CabinetsType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetCabinetsTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetCabinetsTopic_IOUser_vec.begin();
        it != g_RtnNetCabinetsTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetCabinetsTopic_IOUser_vec.end()) {
        g_RtnNetCabinetsTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetCabinetsTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetCabinetsTopic_mutex);

    uv_async_send(&g_RtnNetCabinetsTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetCabinetsTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetOIDTopic(CShfeFtdcRspQryNetOIDField* pRspQryNetOID, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetOIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetOIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetOIDField* pNewRspQryNetOID = NULL;
    if (NULL != pRspQryNetOID) { 
        pNewRspQryNetOID = new CShfeFtdcRspQryNetOIDField;
        if (NULL == pNewRspQryNetOID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetOID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetOID,pRspQryNetOID, sizeof(CShfeFtdcRspQryNetOIDField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetOID;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetOID) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetOID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetOID->OperationType: ", pRspQryNetOID->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->ID: ", pRspQryNetOID->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->Manufactory: ", pRspQryNetOID->Manufactory, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->DeviceType: ", pRspQryNetOID->DeviceType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->CName: ", pRspQryNetOID->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->EName: ", pRspQryNetOID->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->OID: ", pRspQryNetOID->OID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->Unit: ", pRspQryNetOID->Unit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetOID->isTheTable: ", pRspQryNetOID->isTheTable, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetOIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetOIDTopic_IOUser_vec.begin();
        it != g_RspQryNetOIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetOIDTopic_IOUser_vec.end()) {
        g_RspQryNetOIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetOIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetOIDTopic_mutex);

    uv_async_send(&g_RspQryNetOIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetOIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetOIDTopic(CShfeFtdcRtnNetOIDField* pRtnNetOID){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetOIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetOIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetOIDField* pNewRtnNetOID = NULL;
    if (NULL != pRtnNetOID) { 
        pNewRtnNetOID = new CShfeFtdcRtnNetOIDField;
        if (NULL == pNewRtnNetOID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetOID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetOID,pRtnNetOID, sizeof(CShfeFtdcRtnNetOIDField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetOID;
    if (NULL == pRtnNetOID) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetOID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetOID->OperationType: ", pRtnNetOID->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->ID: ", pRtnNetOID->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->Manufactory: ", pRtnNetOID->Manufactory, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->DeviceType: ", pRtnNetOID->DeviceType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->CName: ", pRtnNetOID->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->EName: ", pRtnNetOID->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->OID: ", pRtnNetOID->OID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->Unit: ", pRtnNetOID->Unit, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetOID->isTheTable: ", pRtnNetOID->isTheTable, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetOIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetOIDTopic_IOUser_vec.begin();
        it != g_RtnNetOIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetOIDTopic_IOUser_vec.end()) {
        g_RtnNetOIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetOIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetOIDTopic_mutex);

    uv_async_send(&g_RtnNetOIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetOIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetTimePolicyTopic(CShfeFtdcRspQryNetTimePolicyField* pRspQryNetTimePolicy, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetTimePolicyTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetTimePolicyTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetTimePolicyField* pNewRspQryNetTimePolicy = NULL;
    if (NULL != pRspQryNetTimePolicy) { 
        pNewRspQryNetTimePolicy = new CShfeFtdcRspQryNetTimePolicyField;
        if (NULL == pNewRspQryNetTimePolicy) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetTimePolicy", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetTimePolicy,pRspQryNetTimePolicy, sizeof(CShfeFtdcRspQryNetTimePolicyField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetTimePolicy;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetTimePolicy) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetTimePolicy is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetTimePolicy->OperationType: ", pRspQryNetTimePolicy->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->ID: ", pRspQryNetTimePolicy->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->CName: ", pRspQryNetTimePolicy->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->EName: ", pRspQryNetTimePolicy->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->PolicyType: ", pRspQryNetTimePolicy->PolicyType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->PolicyString: ", pRspQryNetTimePolicy->PolicyString, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->TradingDay: ", pRspQryNetTimePolicy->TradingDay, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->Description: ", pRspQryNetTimePolicy->Description, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetTimePolicy->Operation: ", pRspQryNetTimePolicy->Operation, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetTimePolicyTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetTimePolicyTopic_IOUser_vec.begin();
        it != g_RspQryNetTimePolicyTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetTimePolicyTopic_IOUser_vec.end()) {
        g_RspQryNetTimePolicyTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetTimePolicyTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetTimePolicyTopic_mutex);

    uv_async_send(&g_RspQryNetTimePolicyTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetTimePolicyTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetTimePolicyTopic(CShfeFtdcRtnNetTimePolicyField* pRtnNetTimePolicy){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetTimePolicyTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetTimePolicyTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetTimePolicyField* pNewRtnNetTimePolicy = NULL;
    if (NULL != pRtnNetTimePolicy) { 
        pNewRtnNetTimePolicy = new CShfeFtdcRtnNetTimePolicyField;
        if (NULL == pNewRtnNetTimePolicy) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetTimePolicy", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetTimePolicy,pRtnNetTimePolicy, sizeof(CShfeFtdcRtnNetTimePolicyField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetTimePolicy;
    if (NULL == pRtnNetTimePolicy) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetTimePolicy is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetTimePolicy->OperationType: ", pRtnNetTimePolicy->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->ID: ", pRtnNetTimePolicy->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->CName: ", pRtnNetTimePolicy->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->EName: ", pRtnNetTimePolicy->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->PolicyType: ", pRtnNetTimePolicy->PolicyType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->PolicyString: ", pRtnNetTimePolicy->PolicyString, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->TradingDay: ", pRtnNetTimePolicy->TradingDay, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->Description: ", pRtnNetTimePolicy->Description, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetTimePolicy->Operation: ", pRtnNetTimePolicy->Operation, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetTimePolicyTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetTimePolicyTopic_IOUser_vec.begin();
        it != g_RtnNetTimePolicyTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetTimePolicyTopic_IOUser_vec.end()) {
        g_RtnNetTimePolicyTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetTimePolicyTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetTimePolicyTopic_mutex);

    uv_async_send(&g_RtnNetTimePolicyTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetTimePolicyTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetGatherTaskTopic(CShfeFtdcRspQryNetGatherTaskField* pRspQryNetGatherTask, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetGatherTaskTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetGatherTaskTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetGatherTaskField* pNewRspQryNetGatherTask = NULL;
    if (NULL != pRspQryNetGatherTask) { 
        pNewRspQryNetGatherTask = new CShfeFtdcRspQryNetGatherTaskField;
        if (NULL == pNewRspQryNetGatherTask) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetGatherTask", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetGatherTask,pRspQryNetGatherTask, sizeof(CShfeFtdcRspQryNetGatherTaskField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetGatherTask;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetGatherTask) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetGatherTask is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetGatherTask->OperationType: ", pRspQryNetGatherTask->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->ID: ", pRspQryNetGatherTask->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->ObjectID: ", pRspQryNetGatherTask->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->AttrType: ", pRspQryNetGatherTask->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->PolicyTypeID: ", pRspQryNetGatherTask->PolicyTypeID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->DataType: ", pRspQryNetGatherTask->DataType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGatherTask->TypeFlag: ", pRspQryNetGatherTask->TypeFlag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetGatherTaskTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetGatherTaskTopic_IOUser_vec.begin();
        it != g_RspQryNetGatherTaskTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetGatherTaskTopic_IOUser_vec.end()) {
        g_RspQryNetGatherTaskTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetGatherTaskTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetGatherTaskTopic_mutex);

    uv_async_send(&g_RspQryNetGatherTaskTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetGatherTaskTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetGatherTaskTopic(CShfeFtdcRtnNetGatherTaskField* pRtnNetGatherTask){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetGatherTaskTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetGatherTaskTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetGatherTaskField* pNewRtnNetGatherTask = NULL;
    if (NULL != pRtnNetGatherTask) { 
        pNewRtnNetGatherTask = new CShfeFtdcRtnNetGatherTaskField;
        if (NULL == pNewRtnNetGatherTask) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetGatherTask", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetGatherTask,pRtnNetGatherTask, sizeof(CShfeFtdcRtnNetGatherTaskField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetGatherTask;
    if (NULL == pRtnNetGatherTask) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetGatherTask is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetGatherTask->OperationType: ", pRtnNetGatherTask->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->ID: ", pRtnNetGatherTask->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->ObjectID: ", pRtnNetGatherTask->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->AttrType: ", pRtnNetGatherTask->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->PolicyTypeID: ", pRtnNetGatherTask->PolicyTypeID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->DataType: ", pRtnNetGatherTask->DataType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGatherTask->TypeFlag: ", pRtnNetGatherTask->TypeFlag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetGatherTaskTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetGatherTaskTopic_IOUser_vec.begin();
        it != g_RtnNetGatherTaskTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetGatherTaskTopic_IOUser_vec.end()) {
        g_RtnNetGatherTaskTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetGatherTaskTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetGatherTaskTopic_mutex);

    uv_async_send(&g_RtnNetGatherTaskTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetGatherTaskTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceChgTopic(CShfeFtdcRspQryNetDeviceChgField* pRspQryNetDeviceChg, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceChgField* pNewRspQryNetDeviceChg = NULL;
    if (NULL != pRspQryNetDeviceChg) { 
        pNewRspQryNetDeviceChg = new CShfeFtdcRspQryNetDeviceChgField;
        if (NULL == pNewRspQryNetDeviceChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDeviceChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDeviceChg,pRspQryNetDeviceChg, sizeof(CShfeFtdcRspQryNetDeviceChgField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDeviceChg;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDeviceChg) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDeviceChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDeviceChg->DeviceID: ", pRspQryNetDeviceChg->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceChg->SysNetSubAreaID: ", pRspQryNetDeviceChg->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceChg->OldObjectID: ", pRspQryNetDeviceChg->OldObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceChg->NewObjectID: ", pRspQryNetDeviceChg->NewObjectID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceChgTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceChgTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceChgTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDeviceChgTopic(CShfeFtdcRtnNetDeviceChgField* pRtnNetDeviceChg){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDeviceChgTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceChgTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDeviceChgField* pNewRtnNetDeviceChg = NULL;
    if (NULL != pRtnNetDeviceChg) { 
        pNewRtnNetDeviceChg = new CShfeFtdcRtnNetDeviceChgField;
        if (NULL == pNewRtnNetDeviceChg) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDeviceChg", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDeviceChg,pRtnNetDeviceChg, sizeof(CShfeFtdcRtnNetDeviceChgField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDeviceChg;
    if (NULL == pRtnNetDeviceChg) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDeviceChg is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDeviceChg->DeviceID: ", pRtnNetDeviceChg->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceChg->SysNetSubAreaID: ", pRtnNetDeviceChg->SysNetSubAreaID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceChg->OldObjectID: ", pRtnNetDeviceChg->OldObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceChg->NewObjectID: ", pRtnNetDeviceChg->NewObjectID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDeviceChgTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDeviceChgTopic_IOUser_vec.begin();
        it != g_RtnNetDeviceChgTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDeviceChgTopic_IOUser_vec.end()) {
        g_RtnNetDeviceChgTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDeviceChgTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDeviceChgTopic_mutex);

    uv_async_send(&g_RtnNetDeviceChgTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceChgTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceTypeTopic(CShfeFtdcRspQryNetDeviceTypeField* pRspQryNetDeviceType, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceTypeField* pNewRspQryNetDeviceType = NULL;
    if (NULL != pRspQryNetDeviceType) { 
        pNewRspQryNetDeviceType = new CShfeFtdcRspQryNetDeviceTypeField;
        if (NULL == pNewRspQryNetDeviceType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDeviceType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDeviceType,pRspQryNetDeviceType, sizeof(CShfeFtdcRspQryNetDeviceTypeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDeviceType;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDeviceType) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDeviceType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDeviceType->OperationType: ", pRspQryNetDeviceType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceType->ID: ", pRspQryNetDeviceType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceType->Manufactory: ", pRspQryNetDeviceType->Manufactory, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceType->DeviceType: ", pRspQryNetDeviceType->DeviceType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceTypeTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceTypeTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceTypeTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDeviceTypeTopic(CShfeFtdcRtnNetDeviceTypeField* pRtnNetDeviceType){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDeviceTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDeviceTypeField* pNewRtnNetDeviceType = NULL;
    if (NULL != pRtnNetDeviceType) { 
        pNewRtnNetDeviceType = new CShfeFtdcRtnNetDeviceTypeField;
        if (NULL == pNewRtnNetDeviceType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDeviceType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDeviceType,pRtnNetDeviceType, sizeof(CShfeFtdcRtnNetDeviceTypeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDeviceType;
    if (NULL == pRtnNetDeviceType) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDeviceType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDeviceType->OperationType: ", pRtnNetDeviceType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceType->ID: ", pRtnNetDeviceType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceType->Manufactory: ", pRtnNetDeviceType->Manufactory, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceType->DeviceType: ", pRtnNetDeviceType->DeviceType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDeviceTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDeviceTypeTopic_IOUser_vec.begin();
        it != g_RtnNetDeviceTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDeviceTypeTopic_IOUser_vec.end()) {
        g_RtnNetDeviceTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDeviceTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDeviceTypeTopic_mutex);

    uv_async_send(&g_RtnNetDeviceTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetDeviceCategoryTopic(CShfeFtdcRspQryNetDeviceCategoryField* pRspQryNetDeviceCategory, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetDeviceCategoryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceCategoryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetDeviceCategoryField* pNewRspQryNetDeviceCategory = NULL;
    if (NULL != pRspQryNetDeviceCategory) { 
        pNewRspQryNetDeviceCategory = new CShfeFtdcRspQryNetDeviceCategoryField;
        if (NULL == pNewRspQryNetDeviceCategory) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetDeviceCategory", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetDeviceCategory,pRspQryNetDeviceCategory, sizeof(CShfeFtdcRspQryNetDeviceCategoryField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetDeviceCategory;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetDeviceCategory) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetDeviceCategory is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetDeviceCategory->OperationType: ", pRspQryNetDeviceCategory->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceCategory->ID: ", pRspQryNetDeviceCategory->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceCategory->CName: ", pRspQryNetDeviceCategory->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetDeviceCategory->EName: ", pRspQryNetDeviceCategory->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetDeviceCategoryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetDeviceCategoryTopic_IOUser_vec.begin();
        it != g_RspQryNetDeviceCategoryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetDeviceCategoryTopic_IOUser_vec.end()) {
        g_RspQryNetDeviceCategoryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetDeviceCategoryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetDeviceCategoryTopic_mutex);

    uv_async_send(&g_RspQryNetDeviceCategoryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetDeviceCategoryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetDeviceCategoryTopic(CShfeFtdcRtnNetDeviceCategoryField* pRtnNetDeviceCategory){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetDeviceCategoryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceCategoryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetDeviceCategoryField* pNewRtnNetDeviceCategory = NULL;
    if (NULL != pRtnNetDeviceCategory) { 
        pNewRtnNetDeviceCategory = new CShfeFtdcRtnNetDeviceCategoryField;
        if (NULL == pNewRtnNetDeviceCategory) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetDeviceCategory", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetDeviceCategory,pRtnNetDeviceCategory, sizeof(CShfeFtdcRtnNetDeviceCategoryField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetDeviceCategory;
    if (NULL == pRtnNetDeviceCategory) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetDeviceCategory is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetDeviceCategory->OperationType: ", pRtnNetDeviceCategory->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceCategory->ID: ", pRtnNetDeviceCategory->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceCategory->CName: ", pRtnNetDeviceCategory->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetDeviceCategory->EName: ", pRtnNetDeviceCategory->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetDeviceCategoryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetDeviceCategoryTopic_IOUser_vec.begin();
        it != g_RtnNetDeviceCategoryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetDeviceCategoryTopic_IOUser_vec.end()) {
        g_RtnNetDeviceCategoryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetDeviceCategoryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetDeviceCategoryTopic_mutex);

    uv_async_send(&g_RtnNetDeviceCategoryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetDeviceCategoryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetManufactoryTopic(CShfeFtdcRspQryNetManufactoryField* pRspQryNetManufactory, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetManufactoryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetManufactoryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetManufactoryField* pNewRspQryNetManufactory = NULL;
    if (NULL != pRspQryNetManufactory) { 
        pNewRspQryNetManufactory = new CShfeFtdcRspQryNetManufactoryField;
        if (NULL == pNewRspQryNetManufactory) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetManufactory", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetManufactory,pRspQryNetManufactory, sizeof(CShfeFtdcRspQryNetManufactoryField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetManufactory;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetManufactory) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetManufactory is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetManufactory->OperationType: ", pRspQryNetManufactory->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetManufactory->ID: ", pRspQryNetManufactory->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetManufactory->CName: ", pRspQryNetManufactory->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetManufactory->EName: ", pRspQryNetManufactory->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetManufactoryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetManufactoryTopic_IOUser_vec.begin();
        it != g_RspQryNetManufactoryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetManufactoryTopic_IOUser_vec.end()) {
        g_RspQryNetManufactoryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetManufactoryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetManufactoryTopic_mutex);

    uv_async_send(&g_RspQryNetManufactoryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetManufactoryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetManufactoryTopic(CShfeFtdcRtnNetManufactoryField* pRtnNetManufactory){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetManufactoryTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetManufactoryTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetManufactoryField* pNewRtnNetManufactory = NULL;
    if (NULL != pRtnNetManufactory) { 
        pNewRtnNetManufactory = new CShfeFtdcRtnNetManufactoryField;
        if (NULL == pNewRtnNetManufactory) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetManufactory", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetManufactory,pRtnNetManufactory, sizeof(CShfeFtdcRtnNetManufactoryField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetManufactory;
    if (NULL == pRtnNetManufactory) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetManufactory is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetManufactory->OperationType: ", pRtnNetManufactory->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetManufactory->ID: ", pRtnNetManufactory->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetManufactory->CName: ", pRtnNetManufactory->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetManufactory->EName: ", pRtnNetManufactory->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetManufactoryTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetManufactoryTopic_IOUser_vec.begin();
        it != g_RtnNetManufactoryTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetManufactoryTopic_IOUser_vec.end()) {
        g_RtnNetManufactoryTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetManufactoryTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetManufactoryTopic_mutex);

    uv_async_send(&g_RtnNetManufactoryTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetManufactoryTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetCommunityTopic(CShfeFtdcRspQryNetCommunityField* pRspQryNetCommunity, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetCommunityTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetCommunityTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetCommunityField* pNewRspQryNetCommunity = NULL;
    if (NULL != pRspQryNetCommunity) { 
        pNewRspQryNetCommunity = new CShfeFtdcRspQryNetCommunityField;
        if (NULL == pNewRspQryNetCommunity) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetCommunity", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetCommunity,pRspQryNetCommunity, sizeof(CShfeFtdcRspQryNetCommunityField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetCommunity;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetCommunity) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetCommunity is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetCommunity->OperationType: ", pRspQryNetCommunity->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCommunity->ID: ", pRspQryNetCommunity->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCommunity->IPADDR: ", pRspQryNetCommunity->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCommunity->COMMUNITY: ", pRspQryNetCommunity->COMMUNITY, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetCommunityTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetCommunityTopic_IOUser_vec.begin();
        it != g_RspQryNetCommunityTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetCommunityTopic_IOUser_vec.end()) {
        g_RspQryNetCommunityTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetCommunityTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetCommunityTopic_mutex);

    uv_async_send(&g_RspQryNetCommunityTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetCommunityTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetCommunityTopic(CShfeFtdcRtnNetCommunityField* pRtnNetCommunity){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetCommunityTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetCommunityTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetCommunityField* pNewRtnNetCommunity = NULL;
    if (NULL != pRtnNetCommunity) { 
        pNewRtnNetCommunity = new CShfeFtdcRtnNetCommunityField;
        if (NULL == pNewRtnNetCommunity) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetCommunity", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetCommunity,pRtnNetCommunity, sizeof(CShfeFtdcRtnNetCommunityField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetCommunity;
    if (NULL == pRtnNetCommunity) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetCommunity is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetCommunity->OperationType: ", pRtnNetCommunity->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCommunity->ID: ", pRtnNetCommunity->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCommunity->IPADDR: ", pRtnNetCommunity->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCommunity->COMMUNITY: ", pRtnNetCommunity->COMMUNITY, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetCommunityTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetCommunityTopic_IOUser_vec.begin();
        it != g_RtnNetCommunityTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetCommunityTopic_IOUser_vec.end()) {
        g_RtnNetCommunityTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetCommunityTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetCommunityTopic_mutex);

    uv_async_send(&g_RtnNetCommunityTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetCommunityTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetPortTypeTopic(CShfeFtdcRspQryNetPortTypeField* pRspQryNetPortType, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetPortTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetPortTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetPortTypeField* pNewRspQryNetPortType = NULL;
    if (NULL != pRspQryNetPortType) { 
        pNewRspQryNetPortType = new CShfeFtdcRspQryNetPortTypeField;
        if (NULL == pNewRspQryNetPortType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetPortType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetPortType,pRspQryNetPortType, sizeof(CShfeFtdcRspQryNetPortTypeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetPortType;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetPortType) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetPortType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetPortType->OperationType: ", pRspQryNetPortType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPortType->ID: ", pRspQryNetPortType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPortType->CName: ", pRspQryNetPortType->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPortType->EName: ", pRspQryNetPortType->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPortType->Description: ", pRspQryNetPortType->Description, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetPortTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetPortTypeTopic_IOUser_vec.begin();
        it != g_RspQryNetPortTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetPortTypeTopic_IOUser_vec.end()) {
        g_RspQryNetPortTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetPortTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetPortTypeTopic_mutex);

    uv_async_send(&g_RspQryNetPortTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetPortTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetPortTypeTopic(CShfeFtdcRtnNetPortTypeField* pRtnNetPortType){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetPortTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetPortTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetPortTypeField* pNewRtnNetPortType = NULL;
    if (NULL != pRtnNetPortType) { 
        pNewRtnNetPortType = new CShfeFtdcRtnNetPortTypeField;
        if (NULL == pNewRtnNetPortType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetPortType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetPortType,pRtnNetPortType, sizeof(CShfeFtdcRtnNetPortTypeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetPortType;
    if (NULL == pRtnNetPortType) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetPortType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetPortType->OperationType: ", pRtnNetPortType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPortType->ID: ", pRtnNetPortType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPortType->CName: ", pRtnNetPortType->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPortType->EName: ", pRtnNetPortType->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPortType->Description: ", pRtnNetPortType->Description, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetPortTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetPortTypeTopic_IOUser_vec.begin();
        it != g_RtnNetPortTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetPortTypeTopic_IOUser_vec.end()) {
        g_RtnNetPortTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetPortTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetPortTypeTopic_mutex);

    uv_async_send(&g_RtnNetPortTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetPortTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetPartAccessSpotTopic(CShfeFtdcRspQryNetPartAccessSpotField* pRspQryNetPartAccessSpot, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetPartAccessSpotTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartAccessSpotTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetPartAccessSpotField* pNewRspQryNetPartAccessSpot = NULL;
    if (NULL != pRspQryNetPartAccessSpot) { 
        pNewRspQryNetPartAccessSpot = new CShfeFtdcRspQryNetPartAccessSpotField;
        if (NULL == pNewRspQryNetPartAccessSpot) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetPartAccessSpot", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetPartAccessSpot,pRspQryNetPartAccessSpot, sizeof(CShfeFtdcRspQryNetPartAccessSpotField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetPartAccessSpot;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetPartAccessSpot) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetPartAccessSpot is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetPartAccessSpot->OperationType: ", pRspQryNetPartAccessSpot->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartAccessSpot->ID: ", pRspQryNetPartAccessSpot->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartAccessSpot->CName: ", pRspQryNetPartAccessSpot->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartAccessSpot->EName: ", pRspQryNetPartAccessSpot->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetPartAccessSpotTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetPartAccessSpotTopic_IOUser_vec.begin();
        it != g_RspQryNetPartAccessSpotTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetPartAccessSpotTopic_IOUser_vec.end()) {
        g_RspQryNetPartAccessSpotTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetPartAccessSpotTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetPartAccessSpotTopic_mutex);

    uv_async_send(&g_RspQryNetPartAccessSpotTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartAccessSpotTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetPartAccessSpotTopic(CShfeFtdcRtnNetPartAccessSpotField* pRtnNetPartAccessSpot){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetPartAccessSpotTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetPartAccessSpotTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetPartAccessSpotField* pNewRtnNetPartAccessSpot = NULL;
    if (NULL != pRtnNetPartAccessSpot) { 
        pNewRtnNetPartAccessSpot = new CShfeFtdcRtnNetPartAccessSpotField;
        if (NULL == pNewRtnNetPartAccessSpot) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetPartAccessSpot", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetPartAccessSpot,pRtnNetPartAccessSpot, sizeof(CShfeFtdcRtnNetPartAccessSpotField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetPartAccessSpot;
    if (NULL == pRtnNetPartAccessSpot) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetPartAccessSpot is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetPartAccessSpot->OperationType: ", pRtnNetPartAccessSpot->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartAccessSpot->ID: ", pRtnNetPartAccessSpot->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartAccessSpot->CName: ", pRtnNetPartAccessSpot->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartAccessSpot->EName: ", pRtnNetPartAccessSpot->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetPartAccessSpotTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetPartAccessSpotTopic_IOUser_vec.begin();
        it != g_RtnNetPartAccessSpotTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetPartAccessSpotTopic_IOUser_vec.end()) {
        g_RtnNetPartAccessSpotTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetPartAccessSpotTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetPartAccessSpotTopic_mutex);

    uv_async_send(&g_RtnNetPartAccessSpotTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetPartAccessSpotTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetInterfaceTopic(CShfeFtdcRspQryNetInterfaceField* pRspQryNetInterface, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetInterfaceTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetInterfaceTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetInterfaceField* pNewRspQryNetInterface = NULL;
    if (NULL != pRspQryNetInterface) { 
        pNewRspQryNetInterface = new CShfeFtdcRspQryNetInterfaceField;
        if (NULL == pNewRspQryNetInterface) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetInterface", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetInterface,pRspQryNetInterface, sizeof(CShfeFtdcRspQryNetInterfaceField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetInterface;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetInterface) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetInterface is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetInterface->OperationType: ", pRspQryNetInterface->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->ID: ", pRspQryNetInterface->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->ObjectID: ", pRspQryNetInterface->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->MonitorType_ID: ", pRspQryNetInterface->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->IfType: ", pRspQryNetInterface->IfType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->EName: ", pRspQryNetInterface->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->IpAddress: ", pRspQryNetInterface->IpAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->IpMask: ", pRspQryNetInterface->IpMask, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->IfStatus: ", pRspQryNetInterface->IfStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->MAC: ", pRspQryNetInterface->MAC, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->DeviceID: ", pRspQryNetInterface->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->DeviceObjectID: ", pRspQryNetInterface->DeviceObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->DeviceIndex: ", pRspQryNetInterface->DeviceIndex, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->isPolling: ", pRspQryNetInterface->isPolling, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetInterface->Description: ", pRspQryNetInterface->Description, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetInterfaceTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetInterfaceTopic_IOUser_vec.begin();
        it != g_RspQryNetInterfaceTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetInterfaceTopic_IOUser_vec.end()) {
        g_RspQryNetInterfaceTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetInterfaceTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetInterfaceTopic_mutex);

    uv_async_send(&g_RspQryNetInterfaceTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetInterfaceTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetInterfaceTopic(CShfeFtdcRtnNetInterfaceField* pRtnNetInterface){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetInterfaceTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetInterfaceTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetInterfaceField* pNewRtnNetInterface = NULL;
    if (NULL != pRtnNetInterface) { 
        pNewRtnNetInterface = new CShfeFtdcRtnNetInterfaceField;
        if (NULL == pNewRtnNetInterface) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetInterface", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetInterface,pRtnNetInterface, sizeof(CShfeFtdcRtnNetInterfaceField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetInterface;
    if (NULL == pRtnNetInterface) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetInterface is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetInterface->OperationType: ", pRtnNetInterface->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->ID: ", pRtnNetInterface->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->ObjectID: ", pRtnNetInterface->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->MonitorType_ID: ", pRtnNetInterface->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->IfType: ", pRtnNetInterface->IfType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->EName: ", pRtnNetInterface->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->IpAddress: ", pRtnNetInterface->IpAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->IpMask: ", pRtnNetInterface->IpMask, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->IfStatus: ", pRtnNetInterface->IfStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->MAC: ", pRtnNetInterface->MAC, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->DeviceID: ", pRtnNetInterface->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->DeviceObjectID: ", pRtnNetInterface->DeviceObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->DeviceIndex: ", pRtnNetInterface->DeviceIndex, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->isPolling: ", pRtnNetInterface->isPolling, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetInterface->Description: ", pRtnNetInterface->Description, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetInterfaceTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetInterfaceTopic_IOUser_vec.begin();
        it != g_RtnNetInterfaceTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetInterfaceTopic_IOUser_vec.end()) {
        g_RtnNetInterfaceTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetInterfaceTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetInterfaceTopic_mutex);

    uv_async_send(&g_RtnNetInterfaceTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetInterfaceTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetGeneralOIDTopic(CShfeFtdcRspQryNetGeneralOIDField* pRspQryNetGeneralOID, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetGeneralOIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetGeneralOIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetGeneralOIDField* pNewRspQryNetGeneralOID = NULL;
    if (NULL != pRspQryNetGeneralOID) { 
        pNewRspQryNetGeneralOID = new CShfeFtdcRspQryNetGeneralOIDField;
        if (NULL == pNewRspQryNetGeneralOID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetGeneralOID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetGeneralOID,pRspQryNetGeneralOID, sizeof(CShfeFtdcRspQryNetGeneralOIDField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetGeneralOID;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetGeneralOID) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetGeneralOID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetGeneralOID->OperationType: ", pRspQryNetGeneralOID->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->ID: ", pRspQryNetGeneralOID->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->CName: ", pRspQryNetGeneralOID->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->EName: ", pRspQryNetGeneralOID->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->OID: ", pRspQryNetGeneralOID->OID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->Unit: ", pRspQryNetGeneralOID->Unit, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetGeneralOID->isTheTable: ", pRspQryNetGeneralOID->isTheTable, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetGeneralOIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetGeneralOIDTopic_IOUser_vec.begin();
        it != g_RspQryNetGeneralOIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetGeneralOIDTopic_IOUser_vec.end()) {
        g_RspQryNetGeneralOIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetGeneralOIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetGeneralOIDTopic_mutex);

    uv_async_send(&g_RspQryNetGeneralOIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetGeneralOIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetGeneralOIDTopic(CShfeFtdcRtnNetGeneralOIDField* pRtnNetGeneralOID){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetGeneralOIDTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetGeneralOIDTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetGeneralOIDField* pNewRtnNetGeneralOID = NULL;
    if (NULL != pRtnNetGeneralOID) { 
        pNewRtnNetGeneralOID = new CShfeFtdcRtnNetGeneralOIDField;
        if (NULL == pNewRtnNetGeneralOID) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetGeneralOID", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetGeneralOID,pRtnNetGeneralOID, sizeof(CShfeFtdcRtnNetGeneralOIDField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetGeneralOID;
    if (NULL == pRtnNetGeneralOID) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetGeneralOID is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetGeneralOID->OperationType: ", pRtnNetGeneralOID->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->ID: ", pRtnNetGeneralOID->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->CName: ", pRtnNetGeneralOID->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->EName: ", pRtnNetGeneralOID->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->OID: ", pRtnNetGeneralOID->OID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->Unit: ", pRtnNetGeneralOID->Unit, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetGeneralOID->isTheTable: ", pRtnNetGeneralOID->isTheTable, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetGeneralOIDTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetGeneralOIDTopic_IOUser_vec.begin();
        it != g_RtnNetGeneralOIDTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetGeneralOIDTopic_IOUser_vec.end()) {
        g_RtnNetGeneralOIDTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetGeneralOIDTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetGeneralOIDTopic_mutex);

    uv_async_send(&g_RtnNetGeneralOIDTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetGeneralOIDTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorTypeTopic(CShfeFtdcRspQryNetMonitorTypeField* pRspQryNetMonitorType, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorTypeField* pNewRspQryNetMonitorType = NULL;
    if (NULL != pRspQryNetMonitorType) { 
        pNewRspQryNetMonitorType = new CShfeFtdcRspQryNetMonitorTypeField;
        if (NULL == pNewRspQryNetMonitorType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorType,pRspQryNetMonitorType, sizeof(CShfeFtdcRspQryNetMonitorTypeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorType;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorType) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorType->OperationType: ", pRspQryNetMonitorType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorType->ID: ", pRspQryNetMonitorType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorType->CName: ", pRspQryNetMonitorType->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorType->EName: ", pRspQryNetMonitorType->EName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorTypeTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorTypeTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorTypeTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorTypeTopic(CShfeFtdcRtnNetMonitorTypeField* pRtnNetMonitorType){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorTypeField* pNewRtnNetMonitorType = NULL;
    if (NULL != pRtnNetMonitorType) { 
        pNewRtnNetMonitorType = new CShfeFtdcRtnNetMonitorTypeField;
        if (NULL == pNewRtnNetMonitorType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorType,pRtnNetMonitorType, sizeof(CShfeFtdcRtnNetMonitorTypeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorType;
    if (NULL == pRtnNetMonitorType) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorType->OperationType: ", pRtnNetMonitorType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorType->ID: ", pRtnNetMonitorType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorType->CName: ", pRtnNetMonitorType->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorType->EName: ", pRtnNetMonitorType->EName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorTypeTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorTypeTopic_IOUser_vec.end()) {
        g_RtnNetMonitorTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorTypeTopic_mutex);

    uv_async_send(&g_RtnNetMonitorTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorAttrScopeTopic(CShfeFtdcRspQryNetMonitorAttrScopeField* pRspQryNetMonitorAttrScope, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorAttrScopeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorAttrScopeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorAttrScopeField* pNewRspQryNetMonitorAttrScope = NULL;
    if (NULL != pRspQryNetMonitorAttrScope) { 
        pNewRspQryNetMonitorAttrScope = new CShfeFtdcRspQryNetMonitorAttrScopeField;
        if (NULL == pNewRspQryNetMonitorAttrScope) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorAttrScope", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorAttrScope,pRspQryNetMonitorAttrScope, sizeof(CShfeFtdcRspQryNetMonitorAttrScopeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorAttrScope;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorAttrScope) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorAttrScope is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorAttrScope->OperationType: ", pRspQryNetMonitorAttrScope->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrScope->ID: ", pRspQryNetMonitorAttrScope->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrScope->CName: ", pRspQryNetMonitorAttrScope->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrScope->EName: ", pRspQryNetMonitorAttrScope->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrScope->Comments: ", pRspQryNetMonitorAttrScope->Comments, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorAttrScopeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorAttrScopeTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorAttrScopeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorAttrScopeTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorAttrScopeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorAttrScopeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorAttrScopeTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorAttrScopeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorAttrScopeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorAttrScopeTopic(CShfeFtdcRtnNetMonitorAttrScopeField* pRtnNetMonitorAttrScope){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorAttrScopeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorAttrScopeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorAttrScopeField* pNewRtnNetMonitorAttrScope = NULL;
    if (NULL != pRtnNetMonitorAttrScope) { 
        pNewRtnNetMonitorAttrScope = new CShfeFtdcRtnNetMonitorAttrScopeField;
        if (NULL == pNewRtnNetMonitorAttrScope) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorAttrScope", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorAttrScope,pRtnNetMonitorAttrScope, sizeof(CShfeFtdcRtnNetMonitorAttrScopeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorAttrScope;
    if (NULL == pRtnNetMonitorAttrScope) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorAttrScope is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorAttrScope->OperationType: ", pRtnNetMonitorAttrScope->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrScope->ID: ", pRtnNetMonitorAttrScope->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrScope->CName: ", pRtnNetMonitorAttrScope->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrScope->EName: ", pRtnNetMonitorAttrScope->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrScope->Comments: ", pRtnNetMonitorAttrScope->Comments, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorAttrScopeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorAttrScopeTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorAttrScopeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorAttrScopeTopic_IOUser_vec.end()) {
        g_RtnNetMonitorAttrScopeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorAttrScopeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorAttrScopeTopic_mutex);

    uv_async_send(&g_RtnNetMonitorAttrScopeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorAttrScopeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorAttrTypeTopic(CShfeFtdcRspQryNetMonitorAttrTypeField* pRspQryNetMonitorAttrType, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorAttrTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorAttrTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorAttrTypeField* pNewRspQryNetMonitorAttrType = NULL;
    if (NULL != pRspQryNetMonitorAttrType) { 
        pNewRspQryNetMonitorAttrType = new CShfeFtdcRspQryNetMonitorAttrTypeField;
        if (NULL == pNewRspQryNetMonitorAttrType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorAttrType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorAttrType,pRspQryNetMonitorAttrType, sizeof(CShfeFtdcRspQryNetMonitorAttrTypeField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorAttrType;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorAttrType) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorAttrType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorAttrType->OperationType: ", pRspQryNetMonitorAttrType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->ID: ", pRspQryNetMonitorAttrType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->MANUFACTORY_ID: ", pRspQryNetMonitorAttrType->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->MonitorType_ID: ", pRspQryNetMonitorAttrType->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->AttrType_ID: ", pRspQryNetMonitorAttrType->AttrType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->MANUFACTORY: ", pRspQryNetMonitorAttrType->MANUFACTORY, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->MonitorType: ", pRspQryNetMonitorAttrType->MonitorType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorAttrType->AttrType: ", pRspQryNetMonitorAttrType->AttrType, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorAttrTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorAttrTypeTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorAttrTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorAttrTypeTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorAttrTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorAttrTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorAttrTypeTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorAttrTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorAttrTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorAttrTypeTopic(CShfeFtdcRtnNetMonitorAttrTypeField* pRtnNetMonitorAttrType){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorAttrTypeTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorAttrTypeTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorAttrTypeField* pNewRtnNetMonitorAttrType = NULL;
    if (NULL != pRtnNetMonitorAttrType) { 
        pNewRtnNetMonitorAttrType = new CShfeFtdcRtnNetMonitorAttrTypeField;
        if (NULL == pNewRtnNetMonitorAttrType) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorAttrType", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorAttrType,pRtnNetMonitorAttrType, sizeof(CShfeFtdcRtnNetMonitorAttrTypeField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorAttrType;
    if (NULL == pRtnNetMonitorAttrType) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorAttrType is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorAttrType->OperationType: ", pRtnNetMonitorAttrType->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->ID: ", pRtnNetMonitorAttrType->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->MANUFACTORY_ID: ", pRtnNetMonitorAttrType->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->MonitorType_ID: ", pRtnNetMonitorAttrType->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->AttrType_ID: ", pRtnNetMonitorAttrType->AttrType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->MANUFACTORY: ", pRtnNetMonitorAttrType->MANUFACTORY, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->MonitorType: ", pRtnNetMonitorAttrType->MonitorType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorAttrType->AttrType: ", pRtnNetMonitorAttrType->AttrType, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorAttrTypeTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorAttrTypeTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorAttrTypeTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorAttrTypeTopic_IOUser_vec.end()) {
        g_RtnNetMonitorAttrTypeTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorAttrTypeTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorAttrTypeTopic_mutex);

    uv_async_send(&g_RtnNetMonitorAttrTypeTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorAttrTypeTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorObjectAttrTopic(CShfeFtdcRspQryNetMonitorObjectAttrField* pRspQryNetMonitorObjectAttr, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorObjectAttrField* pNewRspQryNetMonitorObjectAttr = NULL;
    if (NULL != pRspQryNetMonitorObjectAttr) { 
        pNewRspQryNetMonitorObjectAttr = new CShfeFtdcRspQryNetMonitorObjectAttrField;
        if (NULL == pNewRspQryNetMonitorObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorObjectAttr,pRspQryNetMonitorObjectAttr, sizeof(CShfeFtdcRspQryNetMonitorObjectAttrField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorObjectAttr;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorObjectAttr->OperationType: ", pRspQryNetMonitorObjectAttr->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorObjectAttr->ID: ", pRspQryNetMonitorObjectAttr->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorObjectAttr->ObjectID: ", pRspQryNetMonitorObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorObjectAttr->AttrType: ", pRspQryNetMonitorObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorObjectAttr->PolicyTypeID: ", pRspQryNetMonitorObjectAttr->PolicyTypeID, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorObjectAttrTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorObjectAttrTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorObjectAttrTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorObjectAttrTopic(CShfeFtdcRtnNetMonitorObjectAttrField* pRtnNetMonitorObjectAttr){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorObjectAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorObjectAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorObjectAttrField* pNewRtnNetMonitorObjectAttr = NULL;
    if (NULL != pRtnNetMonitorObjectAttr) { 
        pNewRtnNetMonitorObjectAttr = new CShfeFtdcRtnNetMonitorObjectAttrField;
        if (NULL == pNewRtnNetMonitorObjectAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorObjectAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorObjectAttr,pRtnNetMonitorObjectAttr, sizeof(CShfeFtdcRtnNetMonitorObjectAttrField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorObjectAttr;
    if (NULL == pRtnNetMonitorObjectAttr) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorObjectAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorObjectAttr->OperationType: ", pRtnNetMonitorObjectAttr->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorObjectAttr->ID: ", pRtnNetMonitorObjectAttr->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorObjectAttr->ObjectID: ", pRtnNetMonitorObjectAttr->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorObjectAttr->AttrType: ", pRtnNetMonitorObjectAttr->AttrType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorObjectAttr->PolicyTypeID: ", pRtnNetMonitorObjectAttr->PolicyTypeID, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorObjectAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorObjectAttrTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorObjectAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorObjectAttrTopic_IOUser_vec.end()) {
        g_RtnNetMonitorObjectAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorObjectAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorObjectAttrTopic_mutex);

    uv_async_send(&g_RtnNetMonitorObjectAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorObjectAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorDeviceGroupTopic(CShfeFtdcRspQryNetMonitorDeviceGroupField* pRspQryNetMonitorDeviceGroup, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorDeviceGroupTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorDeviceGroupTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorDeviceGroupField* pNewRspQryNetMonitorDeviceGroup = NULL;
    if (NULL != pRspQryNetMonitorDeviceGroup) { 
        pNewRspQryNetMonitorDeviceGroup = new CShfeFtdcRspQryNetMonitorDeviceGroupField;
        if (NULL == pNewRspQryNetMonitorDeviceGroup) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorDeviceGroup", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorDeviceGroup,pRspQryNetMonitorDeviceGroup, sizeof(CShfeFtdcRspQryNetMonitorDeviceGroupField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorDeviceGroup;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorDeviceGroup) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorDeviceGroup is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->OperationType: ", pRspQryNetMonitorDeviceGroup->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->ID: ", pRspQryNetMonitorDeviceGroup->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->CName: ", pRspQryNetMonitorDeviceGroup->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->EName: ", pRspQryNetMonitorDeviceGroup->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->Condition: ", pRspQryNetMonitorDeviceGroup->Condition, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceGroup->Comments: ", pRspQryNetMonitorDeviceGroup->Comments, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorDeviceGroupTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorDeviceGroupTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorDeviceGroupTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorDeviceGroupTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorDeviceGroupTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorDeviceGroupTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorDeviceGroupTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorDeviceGroupTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorDeviceGroupTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorDeviceGroupTopic(CShfeFtdcRtnNetMonitorDeviceGroupField* pRtnNetMonitorDeviceGroup){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorDeviceGroupTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorDeviceGroupTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorDeviceGroupField* pNewRtnNetMonitorDeviceGroup = NULL;
    if (NULL != pRtnNetMonitorDeviceGroup) { 
        pNewRtnNetMonitorDeviceGroup = new CShfeFtdcRtnNetMonitorDeviceGroupField;
        if (NULL == pNewRtnNetMonitorDeviceGroup) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorDeviceGroup", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorDeviceGroup,pRtnNetMonitorDeviceGroup, sizeof(CShfeFtdcRtnNetMonitorDeviceGroupField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorDeviceGroup;
    if (NULL == pRtnNetMonitorDeviceGroup) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorDeviceGroup is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->OperationType: ", pRtnNetMonitorDeviceGroup->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->ID: ", pRtnNetMonitorDeviceGroup->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->CName: ", pRtnNetMonitorDeviceGroup->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->EName: ", pRtnNetMonitorDeviceGroup->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->Condition: ", pRtnNetMonitorDeviceGroup->Condition, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceGroup->Comments: ", pRtnNetMonitorDeviceGroup->Comments, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorDeviceGroupTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorDeviceGroupTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorDeviceGroupTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorDeviceGroupTopic_IOUser_vec.end()) {
        g_RtnNetMonitorDeviceGroupTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorDeviceGroupTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorDeviceGroupTopic_mutex);

    uv_async_send(&g_RtnNetMonitorDeviceGroupTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorDeviceGroupTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorTaskInfoTopic(CShfeFtdcRspQryNetMonitorTaskInfoField* pRspQryNetMonitorTaskInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorTaskInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorTaskInfoField* pNewRspQryNetMonitorTaskInfo = NULL;
    if (NULL != pRspQryNetMonitorTaskInfo) { 
        pNewRspQryNetMonitorTaskInfo = new CShfeFtdcRspQryNetMonitorTaskInfoField;
        if (NULL == pNewRspQryNetMonitorTaskInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorTaskInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorTaskInfo,pRspQryNetMonitorTaskInfo, sizeof(CShfeFtdcRspQryNetMonitorTaskInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorTaskInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorTaskInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorTaskInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->OperationType: ", pRspQryNetMonitorTaskInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ID: ", pRspQryNetMonitorTaskInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->CName: ", pRspQryNetMonitorTaskInfo->CName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->EName: ", pRspQryNetMonitorTaskInfo->EName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->DeviceGroup_ID: ", pRspQryNetMonitorTaskInfo->DeviceGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ManagerGroup_ID: ", pRspQryNetMonitorTaskInfo->ManagerGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->TimePolicy_ID: ", pRspQryNetMonitorTaskInfo->TimePolicy_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->TaskPriority_ID: ", pRspQryNetMonitorTaskInfo->TaskPriority_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->OutputPolicy_ID: ", pRspQryNetMonitorTaskInfo->OutputPolicy_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ActionGroup_ID: ", pRspQryNetMonitorTaskInfo->ActionGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->EventExprStr: ", pRspQryNetMonitorTaskInfo->EventExprStr, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->DeviceGroup: ", pRspQryNetMonitorTaskInfo->DeviceGroup, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ManagerGroup: ", pRspQryNetMonitorTaskInfo->ManagerGroup, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->TimePolicy: ", pRspQryNetMonitorTaskInfo->TimePolicy, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->TaskPriority: ", pRspQryNetMonitorTaskInfo->TaskPriority, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->OutputPolicy: ", pRspQryNetMonitorTaskInfo->OutputPolicy, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ActionGroup: ", pRspQryNetMonitorTaskInfo->ActionGroup, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->ValidFlag: ", pRspQryNetMonitorTaskInfo->ValidFlag, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->TaskStatus: ", pRspQryNetMonitorTaskInfo->TaskStatus, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskInfo->Comments: ", pRspQryNetMonitorTaskInfo->Comments, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorTaskInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorTaskInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorTaskInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorTaskInfoTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorTaskInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorTaskInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorTaskInfoTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorTaskInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorTaskInfoTopic(CShfeFtdcRtnNetMonitorTaskInfoField* pRtnNetMonitorTaskInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorTaskInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorTaskInfoField* pNewRtnNetMonitorTaskInfo = NULL;
    if (NULL != pRtnNetMonitorTaskInfo) { 
        pNewRtnNetMonitorTaskInfo = new CShfeFtdcRtnNetMonitorTaskInfoField;
        if (NULL == pNewRtnNetMonitorTaskInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorTaskInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorTaskInfo,pRtnNetMonitorTaskInfo, sizeof(CShfeFtdcRtnNetMonitorTaskInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorTaskInfo;
    if (NULL == pRtnNetMonitorTaskInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorTaskInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->OperationType: ", pRtnNetMonitorTaskInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ID: ", pRtnNetMonitorTaskInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->CName: ", pRtnNetMonitorTaskInfo->CName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->EName: ", pRtnNetMonitorTaskInfo->EName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->DeviceGroup_ID: ", pRtnNetMonitorTaskInfo->DeviceGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ManagerGroup_ID: ", pRtnNetMonitorTaskInfo->ManagerGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->TimePolicy_ID: ", pRtnNetMonitorTaskInfo->TimePolicy_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->TaskPriority_ID: ", pRtnNetMonitorTaskInfo->TaskPriority_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->OutputPolicy_ID: ", pRtnNetMonitorTaskInfo->OutputPolicy_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ActionGroup_ID: ", pRtnNetMonitorTaskInfo->ActionGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->EventExprStr: ", pRtnNetMonitorTaskInfo->EventExprStr, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->DeviceGroup: ", pRtnNetMonitorTaskInfo->DeviceGroup, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ManagerGroup: ", pRtnNetMonitorTaskInfo->ManagerGroup, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->TimePolicy: ", pRtnNetMonitorTaskInfo->TimePolicy, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->TaskPriority: ", pRtnNetMonitorTaskInfo->TaskPriority, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->OutputPolicy: ", pRtnNetMonitorTaskInfo->OutputPolicy, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ActionGroup: ", pRtnNetMonitorTaskInfo->ActionGroup, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->ValidFlag: ", pRtnNetMonitorTaskInfo->ValidFlag, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->TaskStatus: ", pRtnNetMonitorTaskInfo->TaskStatus, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskInfo->Comments: ", pRtnNetMonitorTaskInfo->Comments, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorTaskInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorTaskInfoTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorTaskInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorTaskInfoTopic_IOUser_vec.end()) {
        g_RtnNetMonitorTaskInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorTaskInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorTaskInfoTopic_mutex);

    uv_async_send(&g_RtnNetMonitorTaskInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorTaskResultTopic(CShfeFtdcRspQryNetMonitorTaskResultField* pRspQryNetMonitorTaskResult, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorTaskResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorTaskResultField* pNewRspQryNetMonitorTaskResult = NULL;
    if (NULL != pRspQryNetMonitorTaskResult) { 
        pNewRspQryNetMonitorTaskResult = new CShfeFtdcRspQryNetMonitorTaskResultField;
        if (NULL == pNewRspQryNetMonitorTaskResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorTaskResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorTaskResult,pRspQryNetMonitorTaskResult, sizeof(CShfeFtdcRspQryNetMonitorTaskResultField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorTaskResult;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorTaskResult) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorTaskResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->OperationType: ", pRspQryNetMonitorTaskResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->ObjectID: ", pRspQryNetMonitorTaskResult->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->Task_ID: ", pRspQryNetMonitorTaskResult->Task_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->OperateTime: ", pRspQryNetMonitorTaskResult->OperateTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->MonDate: ", pRspQryNetMonitorTaskResult->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->MonTime: ", pRspQryNetMonitorTaskResult->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->InstructChain: ", pRspQryNetMonitorTaskResult->InstructChain, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->ResultChain: ", pRspQryNetMonitorTaskResult->ResultChain, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskResult->Flag: ", pRspQryNetMonitorTaskResult->Flag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorTaskResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorTaskResultTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorTaskResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorTaskResultTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorTaskResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorTaskResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorTaskResultTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorTaskResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorTaskResultTopic(CShfeFtdcRtnNetMonitorTaskResultField* pRtnNetMonitorTaskResult){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorTaskResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorTaskResultField* pNewRtnNetMonitorTaskResult = NULL;
    if (NULL != pRtnNetMonitorTaskResult) { 
        pNewRtnNetMonitorTaskResult = new CShfeFtdcRtnNetMonitorTaskResultField;
        if (NULL == pNewRtnNetMonitorTaskResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorTaskResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorTaskResult,pRtnNetMonitorTaskResult, sizeof(CShfeFtdcRtnNetMonitorTaskResultField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorTaskResult;
    if (NULL == pRtnNetMonitorTaskResult) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorTaskResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorTaskResult->OperationType: ", pRtnNetMonitorTaskResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->ObjectID: ", pRtnNetMonitorTaskResult->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->Task_ID: ", pRtnNetMonitorTaskResult->Task_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->OperateTime: ", pRtnNetMonitorTaskResult->OperateTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->MonDate: ", pRtnNetMonitorTaskResult->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->MonTime: ", pRtnNetMonitorTaskResult->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->InstructChain: ", pRtnNetMonitorTaskResult->InstructChain, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->ResultChain: ", pRtnNetMonitorTaskResult->ResultChain, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskResult->Flag: ", pRtnNetMonitorTaskResult->Flag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorTaskResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorTaskResultTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorTaskResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorTaskResultTopic_IOUser_vec.end()) {
        g_RtnNetMonitorTaskResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorTaskResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorTaskResultTopic_mutex);

    uv_async_send(&g_RtnNetMonitorTaskResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorTaskObjectSetTopic(CShfeFtdcRspQryNetMonitorTaskObjectSetField* pRspQryNetMonitorTaskObjectSet, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorTaskObjectSetTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskObjectSetTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorTaskObjectSetField* pNewRspQryNetMonitorTaskObjectSet = NULL;
    if (NULL != pRspQryNetMonitorTaskObjectSet) { 
        pNewRspQryNetMonitorTaskObjectSet = new CShfeFtdcRspQryNetMonitorTaskObjectSetField;
        if (NULL == pNewRspQryNetMonitorTaskObjectSet) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorTaskObjectSet", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorTaskObjectSet,pRspQryNetMonitorTaskObjectSet, sizeof(CShfeFtdcRspQryNetMonitorTaskObjectSetField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorTaskObjectSet;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorTaskObjectSet) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorTaskObjectSet is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorTaskObjectSet->OperationType: ", pRspQryNetMonitorTaskObjectSet->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskObjectSet->ID: ", pRspQryNetMonitorTaskObjectSet->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskObjectSet->DeviceGroup_ID: ", pRspQryNetMonitorTaskObjectSet->DeviceGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskObjectSet->Device_ID: ", pRspQryNetMonitorTaskObjectSet->Device_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskObjectSet->DataCenter: ", pRspQryNetMonitorTaskObjectSet->DataCenter, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorTaskObjectSetTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorTaskObjectSetTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorTaskObjectSetTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorTaskObjectSetTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorTaskObjectSetTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorTaskObjectSetTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorTaskObjectSetTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorTaskObjectSetTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskObjectSetTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorTaskObjectSetTopic(CShfeFtdcRtnNetMonitorTaskObjectSetField* pRtnNetMonitorTaskObjectSet){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorTaskObjectSetTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskObjectSetTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorTaskObjectSetField* pNewRtnNetMonitorTaskObjectSet = NULL;
    if (NULL != pRtnNetMonitorTaskObjectSet) { 
        pNewRtnNetMonitorTaskObjectSet = new CShfeFtdcRtnNetMonitorTaskObjectSetField;
        if (NULL == pNewRtnNetMonitorTaskObjectSet) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorTaskObjectSet", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorTaskObjectSet,pRtnNetMonitorTaskObjectSet, sizeof(CShfeFtdcRtnNetMonitorTaskObjectSetField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorTaskObjectSet;
    if (NULL == pRtnNetMonitorTaskObjectSet) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorTaskObjectSet is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorTaskObjectSet->OperationType: ", pRtnNetMonitorTaskObjectSet->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskObjectSet->ID: ", pRtnNetMonitorTaskObjectSet->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskObjectSet->DeviceGroup_ID: ", pRtnNetMonitorTaskObjectSet->DeviceGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskObjectSet->Device_ID: ", pRtnNetMonitorTaskObjectSet->Device_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskObjectSet->DataCenter: ", pRtnNetMonitorTaskObjectSet->DataCenter, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorTaskObjectSetTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorTaskObjectSetTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorTaskObjectSetTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorTaskObjectSetTopic_IOUser_vec.end()) {
        g_RtnNetMonitorTaskObjectSetTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorTaskObjectSetTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorTaskObjectSetTopic_mutex);

    uv_async_send(&g_RtnNetMonitorTaskObjectSetTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskObjectSetTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetPartyLinkInfoTopic(CShfeFtdcRspQryNetPartyLinkInfoField* pRspQryNetPartyLinkInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetPartyLinkInfoField* pNewRspQryNetPartyLinkInfo = NULL;
    if (NULL != pRspQryNetPartyLinkInfo) { 
        pNewRspQryNetPartyLinkInfo = new CShfeFtdcRspQryNetPartyLinkInfoField;
        if (NULL == pNewRspQryNetPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetPartyLinkInfo,pRspQryNetPartyLinkInfo, sizeof(CShfeFtdcRspQryNetPartyLinkInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetPartyLinkInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->OperationType: ", pRspQryNetPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->ID: ", pRspQryNetPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->MEMBER_NO: ", pRspQryNetPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->MEMBER_NAME: ", pRspQryNetPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->REMOTE_ADDR: ", pRspQryNetPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->LOCAL_ADDR: ", pRspQryNetPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->ADDRESS: ", pRspQryNetPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->LINE_STATUS: ", pRspQryNetPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->CONTACT: ", pRspQryNetPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->TELEPHONE: ", pRspQryNetPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->MOBILEPHONE: ", pRspQryNetPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->EMAIL: ", pRspQryNetPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->FAX: ", pRspQryNetPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->PROVINCE: ", pRspQryNetPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->DDN_NO: ", pRspQryNetPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IN_MODE: ", pRspQryNetPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IP_WAN: ", pRspQryNetPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IP_LAN: ", pRspQryNetPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IPADDR: ", pRspQryNetPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->Interface: ", pRspQryNetPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->INTERFACE_DATE: ", pRspQryNetPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->SOFTWARE: ", pRspQryNetPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->FEE_TYPE: ", pRspQryNetPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->SERVICEPROVIDER: ", pRspQryNetPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IF_ZIYING: ", pRspQryNetPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->IF_TUOGUAN: ", pRspQryNetPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->HASOTHER: ", pRspQryNetPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->SEAT_NO: ", pRspQryNetPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkInfo->PRO: ", pRspQryNetPartyLinkInfo->PRO, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RspQryNetPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RspQryNetPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetPartyLinkInfoTopic(CShfeFtdcRtnNetPartyLinkInfoField* pRtnNetPartyLinkInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetPartyLinkInfoField* pNewRtnNetPartyLinkInfo = NULL;
    if (NULL != pRtnNetPartyLinkInfo) { 
        pNewRtnNetPartyLinkInfo = new CShfeFtdcRtnNetPartyLinkInfoField;
        if (NULL == pNewRtnNetPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetPartyLinkInfo,pRtnNetPartyLinkInfo, sizeof(CShfeFtdcRtnNetPartyLinkInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetPartyLinkInfo;
    if (NULL == pRtnNetPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetPartyLinkInfo->OperationType: ", pRtnNetPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->ID: ", pRtnNetPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->MEMBER_NO: ", pRtnNetPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->MEMBER_NAME: ", pRtnNetPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->REMOTE_ADDR: ", pRtnNetPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->LOCAL_ADDR: ", pRtnNetPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->ADDRESS: ", pRtnNetPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->LINE_STATUS: ", pRtnNetPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->CONTACT: ", pRtnNetPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->TELEPHONE: ", pRtnNetPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->MOBILEPHONE: ", pRtnNetPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->EMAIL: ", pRtnNetPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->FAX: ", pRtnNetPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->PROVINCE: ", pRtnNetPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->DDN_NO: ", pRtnNetPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IN_MODE: ", pRtnNetPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IP_WAN: ", pRtnNetPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IP_LAN: ", pRtnNetPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IPADDR: ", pRtnNetPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->Interface: ", pRtnNetPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->INTERFACE_DATE: ", pRtnNetPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->SOFTWARE: ", pRtnNetPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->FEE_TYPE: ", pRtnNetPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->SERVICEPROVIDER: ", pRtnNetPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IF_ZIYING: ", pRtnNetPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->IF_TUOGUAN: ", pRtnNetPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->HASOTHER: ", pRtnNetPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->SEAT_NO: ", pRtnNetPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkInfo->PRO: ", pRtnNetPartyLinkInfo->PRO, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RtnNetPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RtnNetPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RtnNetPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorActionAttrTopic(CShfeFtdcRspQryNetMonitorActionAttrField* pRspQryNetMonitorActionAttr, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorActionAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorActionAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorActionAttrField* pNewRspQryNetMonitorActionAttr = NULL;
    if (NULL != pRspQryNetMonitorActionAttr) { 
        pNewRspQryNetMonitorActionAttr = new CShfeFtdcRspQryNetMonitorActionAttrField;
        if (NULL == pNewRspQryNetMonitorActionAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorActionAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorActionAttr,pRspQryNetMonitorActionAttr, sizeof(CShfeFtdcRspQryNetMonitorActionAttrField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorActionAttr;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorActionAttr) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorActionAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorActionAttr->OperationType: ", pRspQryNetMonitorActionAttr->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorActionAttr->ID: ", pRspQryNetMonitorActionAttr->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorActionAttr->ActionGroup_ID: ", pRspQryNetMonitorActionAttr->ActionGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorActionAttr->MonitorAttr_ID: ", pRspQryNetMonitorActionAttr->MonitorAttr_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorActionAttr->MonitorAttrName: ", pRspQryNetMonitorActionAttr->MonitorAttrName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorActionAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorActionAttrTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorActionAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorActionAttrTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorActionAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorActionAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorActionAttrTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorActionAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorActionAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorActionAttrTopic(CShfeFtdcRtnNetMonitorActionAttrField* pRtnNetMonitorActionAttr){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorActionAttrTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorActionAttrTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorActionAttrField* pNewRtnNetMonitorActionAttr = NULL;
    if (NULL != pRtnNetMonitorActionAttr) { 
        pNewRtnNetMonitorActionAttr = new CShfeFtdcRtnNetMonitorActionAttrField;
        if (NULL == pNewRtnNetMonitorActionAttr) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorActionAttr", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorActionAttr,pRtnNetMonitorActionAttr, sizeof(CShfeFtdcRtnNetMonitorActionAttrField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorActionAttr;
    if (NULL == pRtnNetMonitorActionAttr) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorActionAttr is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorActionAttr->OperationType: ", pRtnNetMonitorActionAttr->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorActionAttr->ID: ", pRtnNetMonitorActionAttr->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorActionAttr->ActionGroup_ID: ", pRtnNetMonitorActionAttr->ActionGroup_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorActionAttr->MonitorAttr_ID: ", pRtnNetMonitorActionAttr->MonitorAttr_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorActionAttr->MonitorAttrName: ", pRtnNetMonitorActionAttr->MonitorAttrName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorActionAttrTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorActionAttrTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorActionAttrTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorActionAttrTopic_IOUser_vec.end()) {
        g_RtnNetMonitorActionAttrTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorActionAttrTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorActionAttrTopic_mutex);

    uv_async_send(&g_RtnNetMonitorActionAttrTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorActionAttrTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetModuleTopic(CShfeFtdcRspQryNetModuleField* pRspQryNetModule, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetModuleTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetModuleTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetModuleField* pNewRspQryNetModule = NULL;
    if (NULL != pRspQryNetModule) { 
        pNewRspQryNetModule = new CShfeFtdcRspQryNetModuleField;
        if (NULL == pNewRspQryNetModule) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetModule", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetModule,pRspQryNetModule, sizeof(CShfeFtdcRspQryNetModuleField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetModule;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetModule) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetModule is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetModule->OperationType: ", pRspQryNetModule->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->ID: ", pRspQryNetModule->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->ObjectID: ", pRspQryNetModule->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->MonitorType_ID: ", pRspQryNetModule->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->DeviceID: ", pRspQryNetModule->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->DeviceObjectID: ", pRspQryNetModule->DeviceObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->Name: ", pRspQryNetModule->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->Description: ", pRspQryNetModule->Description, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->ModuleIndex: ", pRspQryNetModule->ModuleIndex, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetModule->EntPhyIndex: ", pRspQryNetModule->EntPhyIndex, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetModuleTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetModuleTopic_IOUser_vec.begin();
        it != g_RspQryNetModuleTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetModuleTopic_IOUser_vec.end()) {
        g_RspQryNetModuleTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetModuleTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetModuleTopic_mutex);

    uv_async_send(&g_RspQryNetModuleTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetModuleTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetModuleTopic(CShfeFtdcRtnNetModuleField* pRtnNetModule){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetModuleTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetModuleTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetModuleField* pNewRtnNetModule = NULL;
    if (NULL != pRtnNetModule) { 
        pNewRtnNetModule = new CShfeFtdcRtnNetModuleField;
        if (NULL == pNewRtnNetModule) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetModule", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetModule,pRtnNetModule, sizeof(CShfeFtdcRtnNetModuleField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetModule;
    if (NULL == pRtnNetModule) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetModule is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetModule->OperationType: ", pRtnNetModule->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->ID: ", pRtnNetModule->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->ObjectID: ", pRtnNetModule->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->MonitorType_ID: ", pRtnNetModule->MonitorType_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->DeviceID: ", pRtnNetModule->DeviceID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->DeviceObjectID: ", pRtnNetModule->DeviceObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->Name: ", pRtnNetModule->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->Description: ", pRtnNetModule->Description, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->ModuleIndex: ", pRtnNetModule->ModuleIndex, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetModule->EntPhyIndex: ", pRtnNetModule->EntPhyIndex, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetModuleTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetModuleTopic_IOUser_vec.begin();
        it != g_RtnNetModuleTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetModuleTopic_IOUser_vec.end()) {
        g_RtnNetModuleTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetModuleTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetModuleTopic_mutex);

    uv_async_send(&g_RtnNetModuleTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetModuleTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorTaskStatusResultTopic(CShfeFtdcRspQryNetMonitorTaskStatusResultField* pRspQryNetMonitorTaskStatusResult, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorTaskStatusResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskStatusResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorTaskStatusResultField* pNewRspQryNetMonitorTaskStatusResult = NULL;
    if (NULL != pRspQryNetMonitorTaskStatusResult) { 
        pNewRspQryNetMonitorTaskStatusResult = new CShfeFtdcRspQryNetMonitorTaskStatusResultField;
        if (NULL == pNewRspQryNetMonitorTaskStatusResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorTaskStatusResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorTaskStatusResult,pRspQryNetMonitorTaskStatusResult, sizeof(CShfeFtdcRspQryNetMonitorTaskStatusResultField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorTaskStatusResult;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorTaskStatusResult) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorTaskStatusResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->OperationType: ", pRspQryNetMonitorTaskStatusResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->ObjectID: ", pRspQryNetMonitorTaskStatusResult->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->Task_ID: ", pRspQryNetMonitorTaskStatusResult->Task_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->OperateTime: ", pRspQryNetMonitorTaskStatusResult->OperateTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->MonDate: ", pRspQryNetMonitorTaskStatusResult->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->MonTime: ", pRspQryNetMonitorTaskStatusResult->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorTaskStatusResult->Flag: ", pRspQryNetMonitorTaskStatusResult->Flag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorTaskStatusResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorTaskStatusResultTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorTaskStatusResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorTaskStatusResultTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorTaskStatusResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorTaskStatusResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorTaskStatusResultTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorTaskStatusResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorTaskStatusResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorTaskStatusResultTopic(CShfeFtdcRtnNetMonitorTaskStatusResultField* pRtnNetMonitorTaskStatusResult){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorTaskStatusResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskStatusResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorTaskStatusResultField* pNewRtnNetMonitorTaskStatusResult = NULL;
    if (NULL != pRtnNetMonitorTaskStatusResult) { 
        pNewRtnNetMonitorTaskStatusResult = new CShfeFtdcRtnNetMonitorTaskStatusResultField;
        if (NULL == pNewRtnNetMonitorTaskStatusResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorTaskStatusResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorTaskStatusResult,pRtnNetMonitorTaskStatusResult, sizeof(CShfeFtdcRtnNetMonitorTaskStatusResultField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorTaskStatusResult;
    if (NULL == pRtnNetMonitorTaskStatusResult) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorTaskStatusResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->OperationType: ", pRtnNetMonitorTaskStatusResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->ObjectID: ", pRtnNetMonitorTaskStatusResult->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->Task_ID: ", pRtnNetMonitorTaskStatusResult->Task_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->OperateTime: ", pRtnNetMonitorTaskStatusResult->OperateTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->MonDate: ", pRtnNetMonitorTaskStatusResult->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->MonTime: ", pRtnNetMonitorTaskStatusResult->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorTaskStatusResult->Flag: ", pRtnNetMonitorTaskStatusResult->Flag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorTaskStatusResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorTaskStatusResultTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorTaskStatusResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorTaskStatusResultTopic_IOUser_vec.end()) {
        g_RtnNetMonitorTaskStatusResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorTaskStatusResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorTaskStatusResultTopic_mutex);

    uv_async_send(&g_RtnNetMonitorTaskStatusResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorTaskStatusResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetCfgFileTopic(CShfeFtdcRspQryNetCfgFileField* pRspQryNetCfgFile, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetCfgFileTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetCfgFileTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetCfgFileField* pNewRspQryNetCfgFile = NULL;
    if (NULL != pRspQryNetCfgFile) { 
        pNewRspQryNetCfgFile = new CShfeFtdcRspQryNetCfgFileField;
        if (NULL == pNewRspQryNetCfgFile) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetCfgFile", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetCfgFile,pRspQryNetCfgFile, sizeof(CShfeFtdcRspQryNetCfgFileField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetCfgFile;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetCfgFile) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetCfgFile is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetCfgFile->OperationType: ", pRspQryNetCfgFile->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCfgFile->ObjectID: ", pRspQryNetCfgFile->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCfgFile->MonDate: ", pRspQryNetCfgFile->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCfgFile->MonTime: ", pRspQryNetCfgFile->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetCfgFile->CfgFileName: ", pRspQryNetCfgFile->CfgFileName, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetCfgFileTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetCfgFileTopic_IOUser_vec.begin();
        it != g_RspQryNetCfgFileTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetCfgFileTopic_IOUser_vec.end()) {
        g_RspQryNetCfgFileTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetCfgFileTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetCfgFileTopic_mutex);

    uv_async_send(&g_RspQryNetCfgFileTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetCfgFileTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetCfgFileTopic(CShfeFtdcRtnNetCfgFileField* pRtnNetCfgFile){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetCfgFileTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetCfgFileTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetCfgFileField* pNewRtnNetCfgFile = NULL;
    if (NULL != pRtnNetCfgFile) { 
        pNewRtnNetCfgFile = new CShfeFtdcRtnNetCfgFileField;
        if (NULL == pNewRtnNetCfgFile) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetCfgFile", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetCfgFile,pRtnNetCfgFile, sizeof(CShfeFtdcRtnNetCfgFileField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetCfgFile;
    if (NULL == pRtnNetCfgFile) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetCfgFile is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetCfgFile->OperationType: ", pRtnNetCfgFile->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCfgFile->ObjectID: ", pRtnNetCfgFile->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCfgFile->MonDate: ", pRtnNetCfgFile->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCfgFile->MonTime: ", pRtnNetCfgFile->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetCfgFile->CfgFileName: ", pRtnNetCfgFile->CfgFileName, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetCfgFileTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetCfgFileTopic_IOUser_vec.begin();
        it != g_RtnNetCfgFileTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetCfgFileTopic_IOUser_vec.end()) {
        g_RtnNetCfgFileTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetCfgFileTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetCfgFileTopic_mutex);

    uv_async_send(&g_RtnNetCfgFileTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetCfgFileTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetMonitorDeviceTaskTopic(CShfeFtdcRspQryNetMonitorDeviceTaskField* pRspQryNetMonitorDeviceTask, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetMonitorDeviceTaskTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorDeviceTaskTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetMonitorDeviceTaskField* pNewRspQryNetMonitorDeviceTask = NULL;
    if (NULL != pRspQryNetMonitorDeviceTask) { 
        pNewRspQryNetMonitorDeviceTask = new CShfeFtdcRspQryNetMonitorDeviceTaskField;
        if (NULL == pNewRspQryNetMonitorDeviceTask) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetMonitorDeviceTask", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetMonitorDeviceTask,pRspQryNetMonitorDeviceTask, sizeof(CShfeFtdcRspQryNetMonitorDeviceTaskField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetMonitorDeviceTask;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetMonitorDeviceTask) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetMonitorDeviceTask is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->OperationType: ", pRspQryNetMonitorDeviceTask->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->ID: ", pRspQryNetMonitorDeviceTask->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->ObjectID: ", pRspQryNetMonitorDeviceTask->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->IPAddress: ", pRspQryNetMonitorDeviceTask->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->Manufactory_ID: ", pRspQryNetMonitorDeviceTask->Manufactory_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->InstructChain: ", pRspQryNetMonitorDeviceTask->InstructChain, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->InstructAlias: ", pRspQryNetMonitorDeviceTask->InstructAlias, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->InstructArgs: ", pRspQryNetMonitorDeviceTask->InstructArgs, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->DefParamChain: ", pRspQryNetMonitorDeviceTask->DefParamChain, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetMonitorDeviceTask->Flag: ", pRspQryNetMonitorDeviceTask->Flag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetMonitorDeviceTaskTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetMonitorDeviceTaskTopic_IOUser_vec.begin();
        it != g_RspQryNetMonitorDeviceTaskTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetMonitorDeviceTaskTopic_IOUser_vec.end()) {
        g_RspQryNetMonitorDeviceTaskTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetMonitorDeviceTaskTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetMonitorDeviceTaskTopic_mutex);

    uv_async_send(&g_RspQryNetMonitorDeviceTaskTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetMonitorDeviceTaskTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetMonitorDeviceTaskTopic(CShfeFtdcRtnNetMonitorDeviceTaskField* pRtnNetMonitorDeviceTask){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetMonitorDeviceTaskTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorDeviceTaskTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetMonitorDeviceTaskField* pNewRtnNetMonitorDeviceTask = NULL;
    if (NULL != pRtnNetMonitorDeviceTask) { 
        pNewRtnNetMonitorDeviceTask = new CShfeFtdcRtnNetMonitorDeviceTaskField;
        if (NULL == pNewRtnNetMonitorDeviceTask) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetMonitorDeviceTask", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetMonitorDeviceTask,pRtnNetMonitorDeviceTask, sizeof(CShfeFtdcRtnNetMonitorDeviceTaskField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetMonitorDeviceTask;
    if (NULL == pRtnNetMonitorDeviceTask) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetMonitorDeviceTask is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->OperationType: ", pRtnNetMonitorDeviceTask->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->ID: ", pRtnNetMonitorDeviceTask->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->ObjectID: ", pRtnNetMonitorDeviceTask->ObjectID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->IPAddress: ", pRtnNetMonitorDeviceTask->IPAddress, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->Manufactory_ID: ", pRtnNetMonitorDeviceTask->Manufactory_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->InstructChain: ", pRtnNetMonitorDeviceTask->InstructChain, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->InstructAlias: ", pRtnNetMonitorDeviceTask->InstructAlias, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->InstructArgs: ", pRtnNetMonitorDeviceTask->InstructArgs, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->DefParamChain: ", pRtnNetMonitorDeviceTask->DefParamChain, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetMonitorDeviceTask->Flag: ", pRtnNetMonitorDeviceTask->Flag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetMonitorDeviceTaskTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetMonitorDeviceTaskTopic_IOUser_vec.begin();
        it != g_RtnNetMonitorDeviceTaskTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetMonitorDeviceTaskTopic_IOUser_vec.end()) {
        g_RtnNetMonitorDeviceTaskTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetMonitorDeviceTaskTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetMonitorDeviceTaskTopic_mutex);

    uv_async_send(&g_RtnNetMonitorDeviceTaskTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetMonitorDeviceTaskTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryFileGeneralOperTopic(CShfeFtdcRspQryFileGeneralOperField* pRspQryFileGeneralOper, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryFileGeneralOperTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryFileGeneralOperTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryFileGeneralOperField* pNewRspQryFileGeneralOper = NULL;
    if (NULL != pRspQryFileGeneralOper) { 
        pNewRspQryFileGeneralOper = new CShfeFtdcRspQryFileGeneralOperField;
        if (NULL == pNewRspQryFileGeneralOper) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryFileGeneralOper", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryFileGeneralOper,pRspQryFileGeneralOper, sizeof(CShfeFtdcRspQryFileGeneralOperField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryFileGeneralOper;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryFileGeneralOper) { 
        OutputCallbackMessage("SysUserSpi::pRspQryFileGeneralOper is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryFileGeneralOper->OperationType: ", pRspQryFileGeneralOper->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->FileName: ", pRspQryFileGeneralOper->FileName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->Version: ", pRspQryFileGeneralOper->Version, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->SubVersion: ", pRspQryFileGeneralOper->SubVersion, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->MonDate: ", pRspQryFileGeneralOper->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->MonTime: ", pRspQryFileGeneralOper->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->UserName: ", pRspQryFileGeneralOper->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->OperType: ", pRspQryFileGeneralOper->OperType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->OperResult: ", pRspQryFileGeneralOper->OperResult, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->Comments: ", pRspQryFileGeneralOper->Comments, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->Offset: ", pRspQryFileGeneralOper->Offset, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->Length: ", pRspQryFileGeneralOper->Length, g_RunningResult_File);
        OutputCallbackMessage("pRspQryFileGeneralOper->FileContent: ", pRspQryFileGeneralOper->FileContent, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryFileGeneralOperTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryFileGeneralOperTopic_IOUser_vec.begin();
        it != g_RspQryFileGeneralOperTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryFileGeneralOperTopic_IOUser_vec.end()) {
        g_RspQryFileGeneralOperTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryFileGeneralOperTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryFileGeneralOperTopic_mutex);

    uv_async_send(&g_RspQryFileGeneralOperTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryFileGeneralOperTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnFileGeneralOperTopic(CShfeFtdcRtnFileGeneralOperField* pRtnFileGeneralOper){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnFileGeneralOperTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnFileGeneralOperTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnFileGeneralOperField* pNewRtnFileGeneralOper = NULL;
    if (NULL != pRtnFileGeneralOper) { 
        pNewRtnFileGeneralOper = new CShfeFtdcRtnFileGeneralOperField;
        if (NULL == pNewRtnFileGeneralOper) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnFileGeneralOper", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnFileGeneralOper,pRtnFileGeneralOper, sizeof(CShfeFtdcRtnFileGeneralOperField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnFileGeneralOper;
    if (NULL == pRtnFileGeneralOper) { 
        OutputCallbackMessage("SysUserSpi::pRtnFileGeneralOper is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnFileGeneralOper->OperationType: ", pRtnFileGeneralOper->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->FileName: ", pRtnFileGeneralOper->FileName, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->Version: ", pRtnFileGeneralOper->Version, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->SubVersion: ", pRtnFileGeneralOper->SubVersion, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->MonDate: ", pRtnFileGeneralOper->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->MonTime: ", pRtnFileGeneralOper->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->UserName: ", pRtnFileGeneralOper->UserName, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->OperType: ", pRtnFileGeneralOper->OperType, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->OperResult: ", pRtnFileGeneralOper->OperResult, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->Comments: ", pRtnFileGeneralOper->Comments, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->Offset: ", pRtnFileGeneralOper->Offset, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->Length: ", pRtnFileGeneralOper->Length, g_RunningResult_File);
        OutputCallbackMessage("pRtnFileGeneralOper->FileContent: ", pRtnFileGeneralOper->FileContent, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnFileGeneralOperTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnFileGeneralOperTopic_IOUser_vec.begin();
        it != g_RtnFileGeneralOperTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnFileGeneralOperTopic_IOUser_vec.end()) {
        g_RtnFileGeneralOperTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnFileGeneralOperTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnFileGeneralOperTopic_mutex);

    uv_async_send(&g_RtnFileGeneralOperTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnFileGeneralOperTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetBaseLineTopic(CShfeFtdcRspQryNetBaseLineField* pRspQryNetBaseLine, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetBaseLineTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetBaseLineTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetBaseLineField* pNewRspQryNetBaseLine = NULL;
    if (NULL != pRspQryNetBaseLine) { 
        pNewRspQryNetBaseLine = new CShfeFtdcRspQryNetBaseLineField;
        if (NULL == pNewRspQryNetBaseLine) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetBaseLine", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetBaseLine,pRspQryNetBaseLine, sizeof(CShfeFtdcRspQryNetBaseLineField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetBaseLine;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetBaseLine) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetBaseLine is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetBaseLine->OperationType: ", pRspQryNetBaseLine->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->ID: ", pRspQryNetBaseLine->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->MANUFACTORY_ID: ", pRspQryNetBaseLine->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->Name: ", pRspQryNetBaseLine->Name, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->SerialUsed: ", pRspQryNetBaseLine->SerialUsed, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->data: ", pRspQryNetBaseLine->data, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->memo: ", pRspQryNetBaseLine->memo, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLine->Flag: ", pRspQryNetBaseLine->Flag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetBaseLineTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetBaseLineTopic_IOUser_vec.begin();
        it != g_RspQryNetBaseLineTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetBaseLineTopic_IOUser_vec.end()) {
        g_RspQryNetBaseLineTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetBaseLineTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetBaseLineTopic_mutex);

    uv_async_send(&g_RspQryNetBaseLineTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetBaseLineTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetBaseLineTopic(CShfeFtdcRtnNetBaseLineField* pRtnNetBaseLine){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetBaseLineTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetBaseLineTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetBaseLineField* pNewRtnNetBaseLine = NULL;
    if (NULL != pRtnNetBaseLine) { 
        pNewRtnNetBaseLine = new CShfeFtdcRtnNetBaseLineField;
        if (NULL == pNewRtnNetBaseLine) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetBaseLine", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetBaseLine,pRtnNetBaseLine, sizeof(CShfeFtdcRtnNetBaseLineField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetBaseLine;
    if (NULL == pRtnNetBaseLine) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetBaseLine is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetBaseLine->OperationType: ", pRtnNetBaseLine->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->ID: ", pRtnNetBaseLine->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->MANUFACTORY_ID: ", pRtnNetBaseLine->MANUFACTORY_ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->Name: ", pRtnNetBaseLine->Name, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->SerialUsed: ", pRtnNetBaseLine->SerialUsed, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->data: ", pRtnNetBaseLine->data, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->memo: ", pRtnNetBaseLine->memo, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLine->Flag: ", pRtnNetBaseLine->Flag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetBaseLineTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetBaseLineTopic_IOUser_vec.begin();
        it != g_RtnNetBaseLineTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetBaseLineTopic_IOUser_vec.end()) {
        g_RtnNetBaseLineTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetBaseLineTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetBaseLineTopic_mutex);

    uv_async_send(&g_RtnNetBaseLineTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetBaseLineTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetBaseLineResultTopic(CShfeFtdcRspQryNetBaseLineResultField* pRspQryNetBaseLineResult, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetBaseLineResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetBaseLineResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetBaseLineResultField* pNewRspQryNetBaseLineResult = NULL;
    if (NULL != pRspQryNetBaseLineResult) { 
        pNewRspQryNetBaseLineResult = new CShfeFtdcRspQryNetBaseLineResultField;
        if (NULL == pNewRspQryNetBaseLineResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetBaseLineResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetBaseLineResult,pRspQryNetBaseLineResult, sizeof(CShfeFtdcRspQryNetBaseLineResultField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetBaseLineResult;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetBaseLineResult) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetBaseLineResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetBaseLineResult->OperationType: ", pRspQryNetBaseLineResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->ID: ", pRspQryNetBaseLineResult->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->BaseLineName: ", pRspQryNetBaseLineResult->BaseLineName, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->DeviceObjID: ", pRspQryNetBaseLineResult->DeviceObjID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->DeviceIP: ", pRspQryNetBaseLineResult->DeviceIP, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->Result: ", pRspQryNetBaseLineResult->Result, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->GenDate: ", pRspQryNetBaseLineResult->GenDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->GenTime: ", pRspQryNetBaseLineResult->GenTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->GenUser: ", pRspQryNetBaseLineResult->GenUser, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetBaseLineResult->Flag: ", pRspQryNetBaseLineResult->Flag, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetBaseLineResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetBaseLineResultTopic_IOUser_vec.begin();
        it != g_RspQryNetBaseLineResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetBaseLineResultTopic_IOUser_vec.end()) {
        g_RspQryNetBaseLineResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetBaseLineResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetBaseLineResultTopic_mutex);

    uv_async_send(&g_RspQryNetBaseLineResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetBaseLineResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetBaseLineResultTopic(CShfeFtdcRtnNetBaseLineResultField* pRtnNetBaseLineResult){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetBaseLineResultTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetBaseLineResultTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetBaseLineResultField* pNewRtnNetBaseLineResult = NULL;
    if (NULL != pRtnNetBaseLineResult) { 
        pNewRtnNetBaseLineResult = new CShfeFtdcRtnNetBaseLineResultField;
        if (NULL == pNewRtnNetBaseLineResult) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetBaseLineResult", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetBaseLineResult,pRtnNetBaseLineResult, sizeof(CShfeFtdcRtnNetBaseLineResultField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetBaseLineResult;
    if (NULL == pRtnNetBaseLineResult) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetBaseLineResult is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetBaseLineResult->OperationType: ", pRtnNetBaseLineResult->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->ID: ", pRtnNetBaseLineResult->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->BaseLineName: ", pRtnNetBaseLineResult->BaseLineName, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->DeviceObjID: ", pRtnNetBaseLineResult->DeviceObjID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->DeviceIP: ", pRtnNetBaseLineResult->DeviceIP, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->Result: ", pRtnNetBaseLineResult->Result, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->GenDate: ", pRtnNetBaseLineResult->GenDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->GenTime: ", pRtnNetBaseLineResult->GenTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->GenUser: ", pRtnNetBaseLineResult->GenUser, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetBaseLineResult->Flag: ", pRtnNetBaseLineResult->Flag, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetBaseLineResultTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetBaseLineResultTopic_IOUser_vec.begin();
        it != g_RtnNetBaseLineResultTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetBaseLineResultTopic_IOUser_vec.end()) {
        g_RtnNetBaseLineResultTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetBaseLineResultTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetBaseLineResultTopic_mutex);

    uv_async_send(&g_RtnNetBaseLineResultTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetBaseLineResultTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetPartyLinkStatusInfoTopic(CShfeFtdcRspQryNetPartyLinkStatusInfoField* pRspQryNetPartyLinkStatusInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetPartyLinkStatusInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkStatusInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetPartyLinkStatusInfoField* pNewRspQryNetPartyLinkStatusInfo = NULL;
    if (NULL != pRspQryNetPartyLinkStatusInfo) { 
        pNewRspQryNetPartyLinkStatusInfo = new CShfeFtdcRspQryNetPartyLinkStatusInfoField;
        if (NULL == pNewRspQryNetPartyLinkStatusInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetPartyLinkStatusInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetPartyLinkStatusInfo,pRspQryNetPartyLinkStatusInfo, sizeof(CShfeFtdcRspQryNetPartyLinkStatusInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetPartyLinkStatusInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetPartyLinkStatusInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetPartyLinkStatusInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->OperationType: ", pRspQryNetPartyLinkStatusInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->MonDate: ", pRspQryNetPartyLinkStatusInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->MonTime: ", pRspQryNetPartyLinkStatusInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->SEAT_NO: ", pRspQryNetPartyLinkStatusInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->IPADDR: ", pRspQryNetPartyLinkStatusInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->Interface: ", pRspQryNetPartyLinkStatusInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetPartyLinkStatusInfo->status: ", pRspQryNetPartyLinkStatusInfo->status, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetPartyLinkStatusInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetPartyLinkStatusInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetPartyLinkStatusInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetPartyLinkStatusInfoTopic_IOUser_vec.end()) {
        g_RspQryNetPartyLinkStatusInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetPartyLinkStatusInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetPartyLinkStatusInfoTopic_mutex);

    uv_async_send(&g_RspQryNetPartyLinkStatusInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetPartyLinkStatusInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetPartyLinkStatusInfoTopic(CShfeFtdcRtnNetPartyLinkStatusInfoField* pRtnNetPartyLinkStatusInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetPartyLinkStatusInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkStatusInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetPartyLinkStatusInfoField* pNewRtnNetPartyLinkStatusInfo = NULL;
    if (NULL != pRtnNetPartyLinkStatusInfo) { 
        pNewRtnNetPartyLinkStatusInfo = new CShfeFtdcRtnNetPartyLinkStatusInfoField;
        if (NULL == pNewRtnNetPartyLinkStatusInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetPartyLinkStatusInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetPartyLinkStatusInfo,pRtnNetPartyLinkStatusInfo, sizeof(CShfeFtdcRtnNetPartyLinkStatusInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetPartyLinkStatusInfo;
    if (NULL == pRtnNetPartyLinkStatusInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetPartyLinkStatusInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->OperationType: ", pRtnNetPartyLinkStatusInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->MonDate: ", pRtnNetPartyLinkStatusInfo->MonDate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->MonTime: ", pRtnNetPartyLinkStatusInfo->MonTime, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->SEAT_NO: ", pRtnNetPartyLinkStatusInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->IPADDR: ", pRtnNetPartyLinkStatusInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->Interface: ", pRtnNetPartyLinkStatusInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetPartyLinkStatusInfo->status: ", pRtnNetPartyLinkStatusInfo->status, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetPartyLinkStatusInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetPartyLinkStatusInfoTopic_IOUser_vec.begin();
        it != g_RtnNetPartyLinkStatusInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetPartyLinkStatusInfoTopic_IOUser_vec.end()) {
        g_RtnNetPartyLinkStatusInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetPartyLinkStatusInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetPartyLinkStatusInfoTopic_mutex);

    uv_async_send(&g_RtnNetPartyLinkStatusInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetPartyLinkStatusInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetLocalPingResultInfoTopic(CShfeFtdcRspQryNetLocalPingResultInfoField* pRspQryNetLocalPingResultInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetLocalPingResultInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetLocalPingResultInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetLocalPingResultInfoField* pNewRspQryNetLocalPingResultInfo = NULL;
    if (NULL != pRspQryNetLocalPingResultInfo) { 
        pNewRspQryNetLocalPingResultInfo = new CShfeFtdcRspQryNetLocalPingResultInfoField;
        if (NULL == pNewRspQryNetLocalPingResultInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetLocalPingResultInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetLocalPingResultInfo,pRspQryNetLocalPingResultInfo, sizeof(CShfeFtdcRspQryNetLocalPingResultInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetLocalPingResultInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetLocalPingResultInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetLocalPingResultInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->OperationType: ", pRspQryNetLocalPingResultInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->ID: ", pRspQryNetLocalPingResultInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->SouIPADDR: ", pRspQryNetLocalPingResultInfo->SouIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->SouNAME: ", pRspQryNetLocalPingResultInfo->SouNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->TarIPADDR: ", pRspQryNetLocalPingResultInfo->TarIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->TarNAME: ", pRspQryNetLocalPingResultInfo->TarNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->PDateSta: ", pRspQryNetLocalPingResultInfo->PDateSta, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->PTimeSta: ", pRspQryNetLocalPingResultInfo->PTimeSta, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetLocalPingResultInfo->ConnRate: ", pRspQryNetLocalPingResultInfo->ConnRate, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetLocalPingResultInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetLocalPingResultInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetLocalPingResultInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetLocalPingResultInfoTopic_IOUser_vec.end()) {
        g_RspQryNetLocalPingResultInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetLocalPingResultInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetLocalPingResultInfoTopic_mutex);

    uv_async_send(&g_RspQryNetLocalPingResultInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetLocalPingResultInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetLocalPingResultInfoTopic(CShfeFtdcRtnNetLocalPingResultInfoField* pRtnNetLocalPingResultInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetLocalPingResultInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetLocalPingResultInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetLocalPingResultInfoField* pNewRtnNetLocalPingResultInfo = NULL;
    if (NULL != pRtnNetLocalPingResultInfo) { 
        pNewRtnNetLocalPingResultInfo = new CShfeFtdcRtnNetLocalPingResultInfoField;
        if (NULL == pNewRtnNetLocalPingResultInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetLocalPingResultInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetLocalPingResultInfo,pRtnNetLocalPingResultInfo, sizeof(CShfeFtdcRtnNetLocalPingResultInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetLocalPingResultInfo;
    if (NULL == pRtnNetLocalPingResultInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetLocalPingResultInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->OperationType: ", pRtnNetLocalPingResultInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->ID: ", pRtnNetLocalPingResultInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->SouIPADDR: ", pRtnNetLocalPingResultInfo->SouIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->SouNAME: ", pRtnNetLocalPingResultInfo->SouNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->TarIPADDR: ", pRtnNetLocalPingResultInfo->TarIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->TarNAME: ", pRtnNetLocalPingResultInfo->TarNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->PDateSta: ", pRtnNetLocalPingResultInfo->PDateSta, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->PTimeSta: ", pRtnNetLocalPingResultInfo->PTimeSta, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetLocalPingResultInfo->ConnRate: ", pRtnNetLocalPingResultInfo->ConnRate, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetLocalPingResultInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetLocalPingResultInfoTopic_IOUser_vec.begin();
        it != g_RtnNetLocalPingResultInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetLocalPingResultInfoTopic_IOUser_vec.end()) {
        g_RtnNetLocalPingResultInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetLocalPingResultInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetLocalPingResultInfoTopic_mutex);

    uv_async_send(&g_RtnNetLocalPingResultInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetLocalPingResultInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetRomotePingResultInfoTopic(CShfeFtdcRspQryNetRomotePingResultInfoField* pRspQryNetRomotePingResultInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetRomotePingResultInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetRomotePingResultInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetRomotePingResultInfoField* pNewRspQryNetRomotePingResultInfo = NULL;
    if (NULL != pRspQryNetRomotePingResultInfo) { 
        pNewRspQryNetRomotePingResultInfo = new CShfeFtdcRspQryNetRomotePingResultInfoField;
        if (NULL == pNewRspQryNetRomotePingResultInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetRomotePingResultInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetRomotePingResultInfo,pRspQryNetRomotePingResultInfo, sizeof(CShfeFtdcRspQryNetRomotePingResultInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetRomotePingResultInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetRomotePingResultInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetRomotePingResultInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->OperationType: ", pRspQryNetRomotePingResultInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->ID: ", pRspQryNetRomotePingResultInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->SouIPADDR: ", pRspQryNetRomotePingResultInfo->SouIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->SouNAME: ", pRspQryNetRomotePingResultInfo->SouNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->TarIPADDR: ", pRspQryNetRomotePingResultInfo->TarIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->TarNAME: ", pRspQryNetRomotePingResultInfo->TarNAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->PDateSta: ", pRspQryNetRomotePingResultInfo->PDateSta, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->PTimeSta: ", pRspQryNetRomotePingResultInfo->PTimeSta, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->ConnRate: ", pRspQryNetRomotePingResultInfo->ConnRate, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->TimeDlyMin: ", pRspQryNetRomotePingResultInfo->TimeDlyMin, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->TimeDlyMax: ", pRspQryNetRomotePingResultInfo->TimeDlyMax, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetRomotePingResultInfo->TimeDlyAvg: ", pRspQryNetRomotePingResultInfo->TimeDlyAvg, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetRomotePingResultInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetRomotePingResultInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetRomotePingResultInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetRomotePingResultInfoTopic_IOUser_vec.end()) {
        g_RspQryNetRomotePingResultInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetRomotePingResultInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetRomotePingResultInfoTopic_mutex);

    uv_async_send(&g_RspQryNetRomotePingResultInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetRomotePingResultInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetRomotePingResultInfoTopic(CShfeFtdcRtnNetRomotePingResultInfoField* pRtnNetRomotePingResultInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetRomotePingResultInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetRomotePingResultInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetRomotePingResultInfoField* pNewRtnNetRomotePingResultInfo = NULL;
    if (NULL != pRtnNetRomotePingResultInfo) { 
        pNewRtnNetRomotePingResultInfo = new CShfeFtdcRtnNetRomotePingResultInfoField;
        if (NULL == pNewRtnNetRomotePingResultInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetRomotePingResultInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetRomotePingResultInfo,pRtnNetRomotePingResultInfo, sizeof(CShfeFtdcRtnNetRomotePingResultInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetRomotePingResultInfo;
    if (NULL == pRtnNetRomotePingResultInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetRomotePingResultInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->OperationType: ", pRtnNetRomotePingResultInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->ID: ", pRtnNetRomotePingResultInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->SouIPADDR: ", pRtnNetRomotePingResultInfo->SouIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->SouNAME: ", pRtnNetRomotePingResultInfo->SouNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->TarIPADDR: ", pRtnNetRomotePingResultInfo->TarIPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->TarNAME: ", pRtnNetRomotePingResultInfo->TarNAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->PDateSta: ", pRtnNetRomotePingResultInfo->PDateSta, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->PTimeSta: ", pRtnNetRomotePingResultInfo->PTimeSta, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->ConnRate: ", pRtnNetRomotePingResultInfo->ConnRate, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->TimeDlyMin: ", pRtnNetRomotePingResultInfo->TimeDlyMin, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->TimeDlyMax: ", pRtnNetRomotePingResultInfo->TimeDlyMax, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetRomotePingResultInfo->TimeDlyAvg: ", pRtnNetRomotePingResultInfo->TimeDlyAvg, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetRomotePingResultInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetRomotePingResultInfoTopic_IOUser_vec.begin();
        it != g_RtnNetRomotePingResultInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetRomotePingResultInfoTopic_IOUser_vec.end()) {
        g_RtnNetRomotePingResultInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetRomotePingResultInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetRomotePingResultInfoTopic_mutex);

    uv_async_send(&g_RtnNetRomotePingResultInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetRomotePingResultInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRspQryNetNonPartyLinkInfoTopic(CShfeFtdcRspQryNetNonPartyLinkInfoField* pRspQryNetNonPartyLinkInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    OutputCallbackMessage("\n****** SysUserSpi:: RspQryNetNonPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RspQryNetNonPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[5];
    if (NULL == paramArray) {
    CShfeFtdcRspQryNetNonPartyLinkInfoField* pNewRspQryNetNonPartyLinkInfo = NULL;
    if (NULL != pRspQryNetNonPartyLinkInfo) { 
        pNewRspQryNetNonPartyLinkInfo = new CShfeFtdcRspQryNetNonPartyLinkInfoField;
        if (NULL == pNewRspQryNetNonPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRspQryNetNonPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRspQryNetNonPartyLinkInfo,pRspQryNetNonPartyLinkInfo, sizeof(CShfeFtdcRspQryNetNonPartyLinkInfoField));
    }
    CShfeFtdcRspInfoField* pRspInfoNew = NULL; 
    if (NULL != pRspInfo){ 
        pRspInfoNew = new CShfeFtdcRspInfoField;
        if (NULL == pRspInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pRspInfo", g_RunningResult_File);
            return; 
        } 
        memcpy(pRspInfoNew,pRspInfo,sizeof(CShfeFtdcRspInfoField));
    } 

    int*  pId = new int(nRequestID); 
    if (NULL == pId) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pId", g_RunningResult_File);
        return;
    } 

    bool* bIsLastNew = new bool(bIsLast); 
    if (NULL == bIsLastNew) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for bIsLastNew", g_RunningResult_File); 
        return; 
    } 

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRspQryNetNonPartyLinkInfo;    paramArray[2] = (void*)pRspInfoNew; 
    paramArray[3] = (void*)pId; 
    paramArray[4] = (void*)bIsLastNew; 


    if (NULL == pRspQryNetNonPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRspQryNetNonPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->OperationType: ", pRspQryNetNonPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->ID: ", pRspQryNetNonPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->MEMBER_NO: ", pRspQryNetNonPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->MEMBER_NAME: ", pRspQryNetNonPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->REMOTE_ADDR: ", pRspQryNetNonPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->LOCAL_ADDR: ", pRspQryNetNonPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->ADDRESS: ", pRspQryNetNonPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->LINE_STATUS: ", pRspQryNetNonPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->CONTACT: ", pRspQryNetNonPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->TELEPHONE: ", pRspQryNetNonPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->MOBILEPHONE: ", pRspQryNetNonPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->EMAIL: ", pRspQryNetNonPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->FAX: ", pRspQryNetNonPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->PROVINCE: ", pRspQryNetNonPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->DDN_NO: ", pRspQryNetNonPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IN_MODE: ", pRspQryNetNonPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IP_WAN: ", pRspQryNetNonPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IP_LAN: ", pRspQryNetNonPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IPADDR: ", pRspQryNetNonPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->Interface: ", pRspQryNetNonPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->INTERFACE_DATE: ", pRspQryNetNonPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->SOFTWARE: ", pRspQryNetNonPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->FEE_TYPE: ", pRspQryNetNonPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->SERVICEPROVIDER: ", pRspQryNetNonPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IF_ZIYING: ", pRspQryNetNonPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->IF_TUOGUAN: ", pRspQryNetNonPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->HASOTHER: ", pRspQryNetNonPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->SEAT_NO: ", pRspQryNetNonPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRspQryNetNonPartyLinkInfo->PRO: ", pRspQryNetNonPartyLinkInfo->PRO, g_RunningResult_File);
    }
    OutputCallbackMessage("pRspInfo:", pRspInfo, g_RunningResult_File);
    OutputCallbackMessage("nRequestID:", nRequestID, g_RunningResult_File);
    OutputCallbackMessage("bIsLast:", bIsLast, g_RunningResult_File);

    uv_mutex_lock (&g_RspQryNetNonPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RspQryNetNonPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RspQryNetNonPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RspQryNetNonPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RspQryNetNonPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RspQryNetNonPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RspQryNetNonPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RspQryNetNonPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RspQryNetNonPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}

void SysUserSpi::OnRtnNetNonPartyLinkInfoTopic(CShfeFtdcRtnNetNonPartyLinkInfoField* pRtnNetNonPartyLinkInfo){ 
    OutputCallbackMessage("\n****** SysUserSpi:: RtnNetNonPartyLinkInfoTopic: START! ******", g_RunningResult_File);
    Nan::Persistent<v8::Object>* pSpiObj = new Nan::Persistent<v8::Object>; 
    if (NULL == pSpiObj) { 
        OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pSpiObj", g_RunningResult_File);
        OutputCallbackMessage("****** SysUserSpi:: RtnNetNonPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
    }
    memcpy(pSpiObj, &(this->m_spiobj), sizeof(Nan::Persistent<v8::Object>)); 

    void** paramArray = new void*[2];
    if (NULL == paramArray) {
    CShfeFtdcRtnNetNonPartyLinkInfoField* pNewRtnNetNonPartyLinkInfo = NULL;
    if (NULL != pRtnNetNonPartyLinkInfo) { 
        pNewRtnNetNonPartyLinkInfo = new CShfeFtdcRtnNetNonPartyLinkInfoField;
        if (NULL == pNewRtnNetNonPartyLinkInfo) {
            OutputCallbackMessage("SysUserSpi:: Faild in allocating memory for pNewRtnNetNonPartyLinkInfo", g_RunningResult_File);
            return;
        }
        memcpy (pNewRtnNetNonPartyLinkInfo,pRtnNetNonPartyLinkInfo, sizeof(CShfeFtdcRtnNetNonPartyLinkInfoField));
    }

    paramArray[0] = (void*)pSpiObj;
    paramArray[1] = (void*)pNewRtnNetNonPartyLinkInfo;
    if (NULL == pRtnNetNonPartyLinkInfo) { 
        OutputCallbackMessage("SysUserSpi::pRtnNetNonPartyLinkInfo is NULL" , g_RunningResult_File); 
    } else {
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->OperationType: ", pRtnNetNonPartyLinkInfo->OperationType, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->ID: ", pRtnNetNonPartyLinkInfo->ID, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->MEMBER_NO: ", pRtnNetNonPartyLinkInfo->MEMBER_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->MEMBER_NAME: ", pRtnNetNonPartyLinkInfo->MEMBER_NAME, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->REMOTE_ADDR: ", pRtnNetNonPartyLinkInfo->REMOTE_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->LOCAL_ADDR: ", pRtnNetNonPartyLinkInfo->LOCAL_ADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->ADDRESS: ", pRtnNetNonPartyLinkInfo->ADDRESS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->LINE_STATUS: ", pRtnNetNonPartyLinkInfo->LINE_STATUS, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->CONTACT: ", pRtnNetNonPartyLinkInfo->CONTACT, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->TELEPHONE: ", pRtnNetNonPartyLinkInfo->TELEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->MOBILEPHONE: ", pRtnNetNonPartyLinkInfo->MOBILEPHONE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->EMAIL: ", pRtnNetNonPartyLinkInfo->EMAIL, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->FAX: ", pRtnNetNonPartyLinkInfo->FAX, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->PROVINCE: ", pRtnNetNonPartyLinkInfo->PROVINCE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->DDN_NO: ", pRtnNetNonPartyLinkInfo->DDN_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IN_MODE: ", pRtnNetNonPartyLinkInfo->IN_MODE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IP_WAN: ", pRtnNetNonPartyLinkInfo->IP_WAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IP_LAN: ", pRtnNetNonPartyLinkInfo->IP_LAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IPADDR: ", pRtnNetNonPartyLinkInfo->IPADDR, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->Interface: ", pRtnNetNonPartyLinkInfo->Interface, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->INTERFACE_DATE: ", pRtnNetNonPartyLinkInfo->INTERFACE_DATE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->SOFTWARE: ", pRtnNetNonPartyLinkInfo->SOFTWARE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->FEE_TYPE: ", pRtnNetNonPartyLinkInfo->FEE_TYPE, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->SERVICEPROVIDER: ", pRtnNetNonPartyLinkInfo->SERVICEPROVIDER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IF_ZIYING: ", pRtnNetNonPartyLinkInfo->IF_ZIYING, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->IF_TUOGUAN: ", pRtnNetNonPartyLinkInfo->IF_TUOGUAN, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->HASOTHER: ", pRtnNetNonPartyLinkInfo->HASOTHER, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->SEAT_NO: ", pRtnNetNonPartyLinkInfo->SEAT_NO, g_RunningResult_File);
        OutputCallbackMessage("pRtnNetNonPartyLinkInfo->PRO: ", pRtnNetNonPartyLinkInfo->PRO, g_RunningResult_File);
    }

    uv_mutex_lock (&g_RtnNetNonPartyLinkInfoTopic_mutex);
    vector<FRONT_ID>::iterator it ;
    for(it = g_RtnNetNonPartyLinkInfoTopic_IOUser_vec.begin();
        it != g_RtnNetNonPartyLinkInfoTopic_IOUser_vec.end(); it++ ) {
        if (*it == this->m_frontid) break;     
    }
    if (it == g_RtnNetNonPartyLinkInfoTopic_IOUser_vec.end()) {
        g_RtnNetNonPartyLinkInfoTopic_IOUser_vec.push_back(this->m_frontid);
    }
    g_RtnNetNonPartyLinkInfoTopic_Data_map[this->m_frontid].push ((void**)&paramArray[0]);
    uv_mutex_unlock (&g_RtnNetNonPartyLinkInfoTopic_mutex);

    uv_async_send(&g_RtnNetNonPartyLinkInfoTopic_async);
    OutputCallbackMessage("****** SysUserSpi:: RtnNetNonPartyLinkInfoTopic: END! ******\n", g_RunningResult_File);
}


