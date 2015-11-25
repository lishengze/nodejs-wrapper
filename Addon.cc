
 #include <nan.h>
 #include "FtdcSysUserApi_Wrapper.h"
 #include "SpiCFunc.h"

 using namespace v8;

 void InitAll(Handle<Object> exports) {
   FtdcSysUserApi_Wrapper::InitExports(exports);

   uv_async_init(uv_default_loop(), &async, print_progress);
   uv_async_init(uv_default_loop(), &asyncOnFrontDisconnected, OnFrontDisconnected);
   uv_async_init(uv_default_loop(), &asyncOnHeartBeatWarning, OnHeartBeatWarning);

    uv_mutex_init(&g_RtnNetPartyLinkStatusInfoTopic_data_mutex);
    uv_mutex_init(&g_RtnNetPartyLinkStatusInfoTopic_mutex);
    uv_sem_init(&g_RtnNetPartyLinkStatusInfoTopic_sem, 1);
    
    uv_mutex_init(&g_RtnTradeUserLoginInfoTopic_data_mutex);
    uv_mutex_init(&g_RtnTradeUserLoginInfoTopic_mutex);
    uv_sem_init(&g_RtnTradeUserLoginInfoTopic_sem, 1);
    
    uv_mutex_init(&g_OnRspQryNetMonitorAttrScopeTopic_data_mutex);
    uv_mutex_init(&g_OnRspQryNetMonitorAttrScopeTopic_mutex);
    uv_sem_init(&g_OnRspQryNetMonitorAttrScopeTopicc_sem, 1);

 /////以下为自动生成///////////////////

   uv_async_init(uv_default_loop(), &asyncOnRspQryTopCpuInfoTopic,OnRspQryTopCpuInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTopCpuInfoTopic,OnRtnTopCpuInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTopMemInfoTopic,OnRspQryTopMemInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTopMemInfoTopic,OnRtnTopMemInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTopProcessInfoTopic,OnRspQryTopProcessInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTopProcessInfoTopic,OnRtnTopProcessInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFileSystemInfoTopic,OnRspQryFileSystemInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFileSystemInfoTopic,OnRtnFileSystemInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetworkInfoTopic,OnRspQryNetworkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetworkInfoTopic,OnRtnNetworkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientLoginTopic,OnRspQryClientLoginTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMonitorObjectTopic,OnRspQryMonitorObjectTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMonitorObjectTopic,OnRtnMonitorObjectTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryObjectRationalTopic,OnRspQryObjectRationalTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnObjectRationalTopic,OnRtnObjectRationalTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySyslogInfoTopic,OnRspQrySyslogInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSyslogInfoTopic,OnRtnSyslogInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySubscriberTopic,OnRspQrySubscriberTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryOidRelationTopic,OnRspQryOidRelationTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnOidRelationTopic,OnRtnOidRelationTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryUserInfoTopic,OnRspQryUserInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnUserInfoTopic,OnRtnUserInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryOnlineUserInfoTopic,OnRspQryOnlineUserInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnOnlineUserInfoTopic,OnRtnOnlineUserInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryWarningEventTopic,OnRspQryWarningEventTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnWarningEventTopic,OnRtnWarningEventTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryCPUUsageTopic,OnRspQryCPUUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnCPUUsageTopic,OnRtnCPUUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMemoryUsageTopic,OnRspQryMemoryUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMemoryUsageTopic,OnRtnMemoryUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryDiskUsageTopic,OnRspQryDiskUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnDiskUsageTopic,OnRtnDiskUsageTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryObjectAttrTopic,OnRspQryObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnObjectAttrTopic,OnRtnObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryInvalidateOrderTopic,OnRspQryInvalidateOrderTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnInvalidateOrderTopic,OnRtnInvalidateOrderTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryOrderStatusTopic,OnRspQryOrderStatusTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnOrderStatusTopic,OnRtnOrderStatusTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryBargainOrderTopic,OnRspQryBargainOrderTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnBargainOrderTopic,OnRtnBargainOrderTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryInstPropertyTopic,OnRspQryInstPropertyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnInstPropertyTopic,OnRtnInstPropertyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMarginRateTopic,OnRspQryMarginRateTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMarginRateTopic,OnRtnMarginRateTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPriceLimitTopic,OnRspQryPriceLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPriceLimitTopic,OnRtnPriceLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPartPosiLimitTopic,OnRspQryPartPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPartPosiLimitTopic,OnRtnPartPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientPosiLimitTopic,OnRspQryClientPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnClientPosiLimitTopic,OnRtnClientPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySpecialPosiLimitTopic,OnRspQrySpecialPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSpecialPosiLimitTopic,OnRtnSpecialPosiLimitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTransactionChgTopic,OnRspQryTransactionChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTransactionChgTopic,OnRtnTransactionChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientChgTopic,OnRspQryClientChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnClientChgTopic,OnRtnClientChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPartClientChgTopic,OnRspQryPartClientChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPartClientChgTopic,OnRtnPartClientChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPosiLimitChgTopic,OnRspQryPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPosiLimitChgTopic,OnRtnPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHedgeDetailChgTopic,OnRspQryHedgeDetailChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnHedgeDetailChgTopic,OnRtnHedgeDetailChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryParticipantChgTopic,OnRspQryParticipantChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnParticipantChgTopic,OnRtnParticipantChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMarginRateChgTopic,OnRspQryMarginRateChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMarginRateChgTopic,OnRtnMarginRateChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryUserIpChgTopic,OnRspQryUserIpChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnUserIpChgTopic,OnRtnUserIpChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientPosiLimitChgTopic,OnRspQryClientPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnClientPosiLimitChgTopic,OnRtnClientPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySpecPosiLimitChgTopic,OnRspQrySpecPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSpecPosiLimitChgTopic,OnRtnSpecPosiLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHistoryObjectAttrTopic,OnRspQryHistoryObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnHistoryObjectAttrTopic,OnRtnHistoryObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFrontInfoTopic,OnRspQryFrontInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFrontInfoTopic,OnRtnFrontInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysUserLoginTopic,OnRspQrySysUserLoginTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysUserLogoutTopic,OnRspQrySysUserLogoutTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysUserPasswordUpdateTopic,OnRspQrySysUserPasswordUpdateTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysUserRegisterTopic,OnRspQrySysUserRegisterTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysUserDeleteTopic,OnRspQrySysUserDeleteTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryParticipantInitTopic,OnRspQryParticipantInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnParticipantInitTopic,OnRtnParticipantInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryUserInitTopic,OnRspQryUserInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnUserInitTopic,OnRtnUserInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientInitTopic,OnRspQryClientInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnClientInitTopic,OnRtnClientInitTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeLogTopic,OnRspQryTradeLogTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTradeLogTopic,OnRtnTradeLogTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeUserLoginInfoTopic,OnRspQryTradeUserLoginInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTradeUserLoginInfoTopic,OnRtnTradeUserLoginInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPartTradeTopic,OnRspQryPartTradeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradepeakTopic,OnRspQryTradepeakTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnUpdateSysConfigTopic,OnRtnUpdateSysConfigTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSysUser,OnRtnSysUser);
   uv_async_init(uv_default_loop(), &asyncOnRtnPriceLimitChgTopic,OnRtnPriceLimitChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHistoryCpuInfoTopic,OnRspQryHistoryCpuInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHistoryMemInfoTopic,OnRspQryHistoryMemInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHistoryNetworkInfoTopic,OnRspQryHistoryNetworkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMonitorOnlineUser,OnRspQryMonitorOnlineUser);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFrontStat,OnRspQryFrontStat);
   uv_async_init(uv_default_loop(), &asyncOnRtnSysTimeSyncTopic,OnRtnSysTimeSyncTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnDataCenterChgTopic,OnRtnDataCenterChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryHistoryTradePeakTopic,OnRspQryHistoryTradePeakTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnHistoryTradePeakTopic,OnRtnHistoryTradePeakTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySyslogEventTopic,OnRspQrySyslogEventTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSyslogEventTopic,OnRtnSyslogEventTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeDayChangeTopic,OnRspQryTradeDayChangeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryWebAppInfoTopic,OnRspQryWebAppInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnWebAppInfoTopic,OnRtnWebAppInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryServletInfoTopic,OnRspQryServletInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnServletInfoTopic,OnRtnServletInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFileInfoTopic,OnRspQryFileInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFileInfoTopic,OnRtnFileInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySessionInfoTopic,OnRspQrySessionInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSessionInfoTopic,OnRtnSessionInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryJDBCInfoTopic,OnRspQryJDBCInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnJDBCInfoTopic,OnRtnJDBCInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryThreadInfoTopic,OnRspQryThreadInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnThreadInfoTopic,OnRtnThreadInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryVMInfoTopic,OnRspQryVMInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnVMInfoTopic,OnRtnVMInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPropertyInfoTopic,OnRspQryPropertyInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPropertyInfoTopic,OnRtnPropertyInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMemPoolInfoTopic,OnRspQryMemPoolInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMemPoolInfoTopic,OnRtnMemPoolInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFileContentInfoTopic,OnRspQryFileContentInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFileContentInfoTopic,OnRtnFileContentInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryConnectionInfoTopic,OnRspQryConnectionInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnConnectionInfoTopic,OnRtnConnectionInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryConnectorInfoTopic,OnRspQryConnectorInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnConnectorInfoTopic,OnRtnConnectorInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryDBQueryTopic,OnRspQryDBQueryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnDBQueryTopic,OnRtnDBQueryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryGeneralFieldTopic,OnRspQryGeneralFieldTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnGeneralFieldTopic,OnRtnGeneralFieldTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryGetFileTopic,OnRspQryGetFileTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryWarningQueryTopic,OnRspQryWarningQueryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnWarningQueryTopic,OnRtnWarningQueryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnHostConfig,OnRtnHostConfig);
   uv_async_init(uv_default_loop(), &asyncOnRspQryGeneralOperateTopic,OnRspQryGeneralOperateTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnGeneralOperateTopic,OnRtnGeneralOperateTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceLinkedTopic,OnRspQryNetDeviceLinkedTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDeviceLinkedTopic,OnRtnNetDeviceLinkedTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeUserLoginStatTopic,OnRspQryTradeUserLoginStatTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeFrontOrderRttStatTopic,OnRspQryTradeFrontOrderRttStatTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTradeFrontOrderRttStatTopic,OnRtnTradeFrontOrderRttStatTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryParticTradeOrderStatesTopic,OnRspQryParticTradeOrderStatesTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnParticTradeOrderStatesTopic,OnRtnParticTradeOrderStatesTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryRouterInfoTopic,OnRspQryRouterInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnRouterInfoTopic,OnRtnRouterInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryDiskIOTopic,OnRspQryDiskIOTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnDiskIOTopic,OnRtnDiskIOTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryStatInfoTopic,OnRspQryStatInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnStatInfoTopic,OnRtnStatInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryTradeOrderRttCutLineTopic,OnRspQryTradeOrderRttCutLineTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnTradeOrderRttCutLineTopic,OnRtnTradeOrderRttCutLineTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryClientInfoTopic,OnRspQryClientInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnClientInfoTopic,OnRtnClientInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryEventDescriptionTopic,OnRspQryEventDescriptionTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnEventDescriptionTopic,OnRtnEventDescriptionTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFrontUniqueIDTopic,OnRspQryFrontUniqueIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFrontUniqueIDTopic,OnRtnFrontUniqueIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPartyLinkAddrChangeTopic,OnRspQryNetPartyLinkAddrChangeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPartyLinkAddrChangeTopic,OnRtnNetPartyLinkAddrChangeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDelPartyLinkInfoTopic,OnRspQryNetDelPartyLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDelPartyLinkInfoTopic,OnRtnNetDelPartyLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryPerformanceTopTopic,OnRspQryPerformanceTopTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnPerformanceTopTopic,OnRtnPerformanceTopTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryInstrumentStatusTopic,OnRspQryInstrumentStatusTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnInstrumentStatusTopic,OnRtnInstrumentStatusTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryCurrTradingSegmentAttrTopic,OnRspQryCurrTradingSegmentAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnCurrTradingSegmentAttrTopic,OnRtnCurrTradingSegmentAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetAreaTopic,OnRspQryNetAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetAreaTopic,OnRtnNetAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetSubAreaTopic,OnRspQryNetSubAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetSubAreaTopic,OnRtnNetSubAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetSubAreaIPTopic,OnRspQryNetSubAreaIPTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetSubAreaIPTopic,OnRtnNetSubAreaIPTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceTopic,OnRspQryNetDeviceTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDeviceTopic,OnRtnNetDeviceTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceDetectTopic,OnRspQryNetDeviceDetectTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetBuildingTopic,OnRspQryNetBuildingTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetBuildingTopic,OnRtnNetBuildingTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetRoomTopic,OnRspQryNetRoomTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetRoomTopic,OnRtnNetRoomTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetCabinetsTopic,OnRspQryNetCabinetsTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetCabinetsTopic,OnRtnNetCabinetsTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetOIDTopic,OnRspQryNetOIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetOIDTopic,OnRtnNetOIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetTimePolicyTopic,OnRspQryNetTimePolicyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetTimePolicyTopic,OnRtnNetTimePolicyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetGatherTaskTopic,OnRspQryNetGatherTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetGatherTaskTopic,OnRtnNetGatherTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceChgTopic,OnRspQryNetDeviceChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDeviceChgTopic,OnRtnNetDeviceChgTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceTypeTopic,OnRspQryNetDeviceTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDeviceTypeTopic,OnRtnNetDeviceTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDeviceCategoryTopic,OnRspQryNetDeviceCategoryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDeviceCategoryTopic,OnRtnNetDeviceCategoryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetManufactoryTopic,OnRspQryNetManufactoryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetManufactoryTopic,OnRtnNetManufactoryTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetCommunityTopic,OnRspQryNetCommunityTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetCommunityTopic,OnRtnNetCommunityTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPortTypeTopic,OnRspQryNetPortTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPortTypeTopic,OnRtnNetPortTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPartAccessSpotTopic,OnRspQryNetPartAccessSpotTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPartAccessSpotTopic,OnRtnNetPartAccessSpotTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetInterfaceTopic,OnRspQryNetInterfaceTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetInterfaceTopic,OnRtnNetInterfaceTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetGeneralOIDTopic,OnRspQryNetGeneralOIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetGeneralOIDTopic,OnRtnNetGeneralOIDTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTypeTopic,OnRspQryNetMonitorTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTypeTopic,OnRtnNetMonitorTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorAttrScopeTopic,OnRspQryNetMonitorAttrScopeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorAttrScopeTopic,OnRtnNetMonitorAttrScopeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorAttrTypeTopic,OnRspQryNetMonitorAttrTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorAttrTypeTopic,OnRtnNetMonitorAttrTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorObjectAttrTopic,OnRspQryNetMonitorObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorObjectAttrTopic,OnRtnNetMonitorObjectAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetFuncAreaTopic,OnRspQryNetFuncAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetFuncAreaTopic,OnRtnNetFuncAreaTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorCommandTypeTopic,OnRspQryNetMonitorCommandTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorCommandTypeTopic,OnRtnNetMonitorCommandTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorActionGroupTopic,OnRspQryNetMonitorActionGroupTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorActionGroupTopic,OnRtnNetMonitorActionGroupTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorDeviceGroupTopic,OnRspQryNetMonitorDeviceGroupTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorDeviceGroupTopic,OnRtnNetMonitorDeviceGroupTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTaskInfoTopic,OnRspQryNetMonitorTaskInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTaskInfoTopic,OnRtnNetMonitorTaskInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTaskResultTopic,OnRspQryNetMonitorTaskResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTaskResultTopic,OnRtnNetMonitorTaskResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTaskObjectSetTopic,OnRspQryNetMonitorTaskObjectSetTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTaskObjectSetTopic,OnRtnNetMonitorTaskObjectSetTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPartyLinkInfoTopic,OnRspQryNetPartyLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPartyLinkInfoTopic,OnRtnNetPartyLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorActionAttrTopic,OnRspQryNetMonitorActionAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorActionAttrTopic,OnRtnNetMonitorActionAttrTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetModuleTopic,OnRspQryNetModuleTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetModuleTopic,OnRtnNetModuleTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetEventExprTopic,OnRspQryNetEventExprTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetEventExprTopic,OnRtnNetEventExprTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetEventTypeTopic,OnRspQryNetEventTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetEventTypeTopic,OnRtnNetEventTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetSubEventTypeTopic,OnRspQryNetSubEventTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetSubEventTypeTopic,OnRtnNetSubEventTypeTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetEventLevelTopic,OnRspQryNetEventLevelTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetEventLevelTopic,OnRtnNetEventLevelTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTaskStatusResultTopic,OnRspQryNetMonitorTaskStatusResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTaskStatusResultTopic,OnRtnNetMonitorTaskStatusResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetCfgFileTopic,OnRspQryNetCfgFileTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetCfgFileTopic,OnRtnNetCfgFileTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorDeviceTaskTopic,OnRspQryNetMonitorDeviceTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorDeviceTaskTopic,OnRtnNetMonitorDeviceTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMonitorTaskInstAttrsTopic,OnRspQryNetMonitorTaskInstAttrsTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMonitorTaskInstAttrsTopic,OnRtnNetMonitorTaskInstAttrsTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryFileGeneralOperTopic,OnRspQryFileGeneralOperTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnFileGeneralOperTopic,OnRtnFileGeneralOperTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetBaseLineTopic,OnRspQryNetBaseLineTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetBaseLineTopic,OnRtnNetBaseLineTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetBaseLineTaskTopic,OnRspQryNetBaseLineTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetBaseLineTaskTopic,OnRtnNetBaseLineTaskTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetBaseLineResultTopic,OnRspQryNetBaseLineResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetBaseLineResultTopic,OnRtnNetBaseLineResultTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPartyLinkStatusInfoTopic,OnRspQryNetPartyLinkStatusInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPartyLinkStatusInfoTopic,OnRtnNetPartyLinkStatusInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetMemberSDHLineInfoTopic,OnRspQryNetMemberSDHLineInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetMemberSDHLineInfoTopic,OnRtnNetMemberSDHLineInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetDDNLinkInfoTopic,OnRspQryNetDDNLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetDDNLinkInfoTopic,OnRtnNetDDNLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPseudMemberLinkInfoTopic,OnRspQryNetPseudMemberLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPseudMemberLinkInfoTopic,OnRtnNetPseudMemberLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryOuterDeviceInfTopic,OnRspQryOuterDeviceInfTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetOuterDeviceInfTopic,OnRtnNetOuterDeviceInfTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetLocalPingResultInfoTopic,OnRspQryNetLocalPingResultInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetLocalPingResultInfoTopic,OnRtnNetLocalPingResultInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetRomotePingResultInfoTopic,OnRspQryNetRomotePingResultInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetRomotePingResultInfoTopic,OnRtnNetRomotePingResultInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMonitorTopProcessInfo,OnRtnMonitorTopProcessInfo);
   uv_async_init(uv_default_loop(), &asyncOnRspQrySysInternalTopologyTopic,OnRspQrySysInternalTopologyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnSysInternalTopologyTopic,OnRtnSysInternalTopologyTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryMemberLinkCostTopic,OnRspQryMemberLinkCostTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnMemberLinkCostTopic,OnRtnMemberLinkCostTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetPartylinkMonthlyRentTopic,OnRspQryNetPartylinkMonthlyRentTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetPartylinkMonthlyRentTopic,OnRtnNetPartylinkMonthlyRentTopic);
   uv_async_init(uv_default_loop(), &asyncOnRspQryNetNonPartyLinkInfoTopic,OnRspQryNetNonPartyLinkInfoTopic);
   uv_async_init(uv_default_loop(), &asyncOnRtnNetNonPartyLinkInfoTopic,OnRtnNetNonPartyLinkInfoTopic);
};

NODE_MODULE(addon, InitAll);