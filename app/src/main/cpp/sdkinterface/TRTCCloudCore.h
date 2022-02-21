//
// Created by lichao on 2022/2/18.
//

#ifndef MYJNIOFTRTC_TRTCCLOUDCORE_H
#define MYJNIOFTRTC_TRTCCLOUDCORE_H

#include "ITRTCCloud.h"
#include "LogUtil.h"

using namespace liteav;

class TRTCCloudCore : public ITRTCCloudCallback{

public:
    static TRTCCloudCore* GetInstance(JNIEnv *env);
    static void Destory();
    TRTCCloudCore(JNIEnv *m_env);
    ~TRTCCloudCore();


public:
    void InitCallBack();
    void UnInitCallBack();
    void PreUninit();
    ITRTCCloud* getTRTCCloud();


public:
//https://liteav.sdk.qcloud.com/doc/api/zh-cn/group__TRTCCloudCallback__cplusplus.html#a9724da0b3da9b2eca5736fa8e54aa410
//错误和警告事件
    virtual void 	onError (TXLiteAVError errCode, const char *errMsg, void *extraInfo);

    virtual void 	onWarning (TXLiteAVWarning warningCode, const char *warningMsg, void *extraInfo);
//房间相关事件回调
    virtual void 	onEnterRoom (int result);

    virtual void 	onExitRoom (int reason);

    //用户相关事件回调
    virtual void 	onRemoteUserEnterRoom (const char *userId);

    virtual void 	onRemoteUserLeaveRoom (const char *userId, int reason);

    virtual void 	onUserVideoAvailable (const char *userId, bool available);

    virtual void 	onUserAudioAvailable (const char *userId, bool available);


   // 网络和技术指标统计回调
    virtual void 	onNetworkQuality (TRTCQualityInfo localQuality, TRTCQualityInfo *remoteQuality, uint32_t remoteQualityCount);

    virtual void 	onStatistics (const TRTCStatistics &statistics);


   // TODO 与云端连接情况的事件回调


   // 硬件设备相关事件回调
    virtual void 	onCameraDidReady ();

    virtual void 	onMicDidReady ();


   // TODO 自定义消息的接收事件回调

   // TODO CDN 相关事件回调

   //TODO 屏幕分享相关事件回调

   //TODO 本地录制和本地截图的事件回调

private:
    static TRTCCloudCore* m_instance;
    ITRTCCloud* m_pCloud = nullptr;
    ITXDeviceManager* m_pDeviceManager = nullptr;
    bool m_bPreUninit = false;
    JNIEnv *m_env;
};



#endif //MYJNIOFTRTC_TRTCCLOUDCORE_H
