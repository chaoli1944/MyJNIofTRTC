//
// Created by lichao on 2022/2/18.
//
#include <jni.h>
#include "TRTCCloudCore.h"
#include "LogUtil.h"

TRTCCloudCore *TRTCCloudCore::m_instance = nullptr;


TRTCCloudCore *TRTCCloudCore::GetInstance(JNIEnv *env) {
    if (m_instance == nullptr) {
        m_instance = new TRTCCloudCore(env);
    }
    return m_instance;
}

void TRTCCloudCore::Destory() {
    if(m_instance){
        delete m_instance;
        m_instance = nullptr;
    }

}

TRTCCloudCore::TRTCCloudCore(JNIEnv *env) {
    m_pCloud = getTRTCShareInstance(nullptr);
    m_pDeviceManager = m_pCloud->getDeviceManager();
    m_env = env;
}

TRTCCloudCore::~TRTCCloudCore()  {
    LOGE("destroy");
    destroyTRTCShareInstance();
    m_pCloud = nullptr;
    m_env = nullptr;
}

void TRTCCloudCore::InitCallBack() {
    m_pCloud->addCallback(this);
}

void TRTCCloudCore::UnInitCallBack() {
    m_pCloud->removeCallback(this);
}

void TRTCCloudCore::PreUninit() {
    m_bPreUninit = true;
    m_pCloud->stopAllRemoteView();
    m_pCloud->stopLocalAudio();
    m_pCloud->stopLocalPreview();
    m_pCloud->exitRoom();
}

ITRTCCloud *TRTCCloudCore::getTRTCCloud() {
    return m_pCloud;
}

void TRTCCloudCore::onError(TXLiteAVError errCode, const char *errMsg, void *extraInfo) {
    LOGE("onError errCode[%d],errMsg[%s]\n",errCode,errMsg);
}

void TRTCCloudCore::onWarning(TXLiteAVWarning warningCode, const char *warningMsg,
                              void *extraInfo) {
    LOGE("onWarning errCode[%d],errMsg[%s]\n",warningCode,warningMsg);
}

void TRTCCloudCore::onEnterRoom(int result) {
    LOGE("onEnterRoom result[%d]\n",result);
    jclass clazz = m_env->FindClass("com/chaoli/myjnioftrtc/nativeUtils/JniCallBack");
    jmethodID videoAvailable = m_env->GetStaticMethodID(clazz,"jniCallOnEnterRoom","(I)V");
    m_env->CallStaticVoidMethod(clazz,videoAvailable,result);
}

void TRTCCloudCore::onExitRoom(int reason) {
    LOGE("onExitRoom reason[%d]\n",reason);
    jclass clazz = m_env->FindClass("com/chaoli/myjnioftrtc/nativeUtils/JniCallBack");
    jmethodID videoAvailable = m_env->GetStaticMethodID(clazz,"jniCallOnExitRoom","(I)V");
    m_env->CallStaticVoidMethod(clazz,videoAvailable,reason);
}

void TRTCCloudCore::onRemoteUserEnterRoom(const char *userId) {
    LOGE("onRemoteUserEnterRoom userId[%s]\n",userId);
}

void TRTCCloudCore::onRemoteUserLeaveRoom(const char *userId, int reason) {
    LOGE("onRemoteUserLeaveRoom userId[%s],reason[%d]\n",userId,reason);
}

void TRTCCloudCore::onUserVideoAvailable(const char *userId, bool available) {
    LOGE("onUserVideoAvailable userId[%s],available[%d]\n",userId,available);
    jclass clazz = m_env->FindClass("com/chaoli/myjnioftrtc/nativeUtils/JniCallBack");
    jmethodID videoAvailable = m_env->GetStaticMethodID(clazz,"jniCallUserVideoAvailable","(Ljava/lang/String;Z)V");
    jstring jUser = m_env->NewStringUTF(userId);
    jboolean jAvailable = available;
    m_env->CallStaticVoidMethod(clazz,videoAvailable,jUser,jAvailable);
}

void TRTCCloudCore::onUserAudioAvailable(const char *userId, bool available) {
    LOGE("onUserAudioAvailable userId[%s],available[%d]\n",userId,available);
}

void TRTCCloudCore::onNetworkQuality(TRTCQualityInfo localQuality, TRTCQualityInfo *remoteQuality,
                                     uint32_t remoteQualityCount) {

}

void TRTCCloudCore::onStatistics(const TRTCStatistics &statistics) {

}

void TRTCCloudCore::onCameraDidReady() {
    LOGE("onCameraDidReady \n");
}

void TRTCCloudCore::onMicDidReady() {
    LOGE("onMicDidReady \n");
}

