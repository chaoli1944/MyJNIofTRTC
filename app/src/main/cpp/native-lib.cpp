#include <jni.h>
#include <string>


#include "ITRTCCloud.h"


#include <android/log.h>

#include "TRTCCloudCore.h"

#define TAG "CHAOLILOG"
//...我都不知道传入什么，借助JNI里面的宏来自动帮我填充
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


void checkTRTC(JNIEnv *pEnv);

using namespace trtc;

TRTCCloudCore *trtcCloudCore = nullptr;

void checkTRTC(JNIEnv *pEnv) {
    if(trtcCloudCore== nullptr){
        trtcCloudCore = TRTCCloudCore::GetInstance(pEnv);
    }

}

extern "C" JNIEXPORT jstring JNICALL
Java_com_chaoli_myjnioftrtc_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    std::string jniVersion;


    trtc::ITRTCCloud* itrtcCloud = trtc::ITRTCCloud::getTRTCShareInstance(nullptr);

    const char* ver = itrtcCloud->getSDKVersion();
    LOGE("调用JNI获取版本号：%s\n",ver);
    jniVersion = ver;


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_getSDKVersion(JNIEnv *env, jclass clazz) {
    checkTRTC(env);
    return env->NewStringUTF(liteav::ITRTCCloud::getTRTCShareInstance(nullptr)->getSDKVersion());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_startLocalPreview(JNIEnv *env,
                                                                            jclass clazz,
                                                                            jboolean front_camera,
                                                                            jobject view) {
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalPreview(front_camera,view);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_startLocalAudio(JNIEnv *env,
                                                                          jclass clazz) {
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalAudio(liteav::TRTCAudioQualityDefault);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_enterRoom(JNIEnv *env, jclass clazz,
                                                                    jstring room_id, jstring user_id, jstring user_sig,
                                                                    jint sdk_app_id) {
    checkTRTC(env);
    const char *roomId = env->GetStringUTFChars(room_id, nullptr);
    const char *userid = env->GetStringUTFChars(user_id, nullptr);
    const char *userSig = env->GetStringUTFChars(user_sig, nullptr);

    TRTCParams trtcParams;
    trtcParams.role = liteav::TRTCRoleAnchor;
    trtcParams.strRoomId = roomId;
    trtcParams.userId = userid;
    trtcParams.userSig = userSig;
    trtcParams.sdkAppId = sdk_app_id;

    trtcCloudCore->getTRTCCloud()->enterRoom(trtcParams, liteav::TRTCAppSceneVideoCall);
    trtcCloudCore->InitCallBack();

    env->ReleaseStringUTFChars(room_id,roomId);
    env->ReleaseStringUTFChars(user_id,userid);
    env->ReleaseStringUTFChars(user_sig,userSig);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_startRemoteView(JNIEnv *env, jclass clazz,
                                                                          jstring user_id,
                                                                          jobject view) {
    checkTRTC(env);
    const char* userId = env->GetStringUTFChars(user_id, nullptr);
    trtcCloudCore->getTRTCCloud()->startRemoteView(
            userId,
            liteav::TRTCVideoStreamTypeBig,
            view
            );
    env->ReleaseStringUTFChars(user_id,userId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_stopRemoteView(JNIEnv *env, jclass clazz,
                                                                         jstring user_id) {
    checkTRTC(env);
    const char* userId = env->GetStringUTFChars(user_id, nullptr);

    trtcCloudCore->getTRTCCloud()->stopRemoteView(userId,liteav::TRTCVideoStreamTypeBig);
    env->ReleaseStringUTFChars(user_id,userId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_nativeDestroy(JNIEnv *env, jclass clazz) {
    checkTRTC(env);
    trtcCloudCore->UnInitCallBack();
    trtcCloudCore->PreUninit();
    TRTCCloudCore::Destory();
    trtcCloudCore = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_exitRoom(JNIEnv *env, jclass clazz) {
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->exitRoom();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_stopLocalAudio(JNIEnv *env,
                                                                         jclass clazz) {
    // TODO: implement stopLocalAudio()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->stopLocalAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_stopLocalPreview(JNIEnv *env,
                                                                           jclass clazz) {
    // TODO: implement stopLocalPreview()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->stopLocalPreview();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_chaoli_myjnioftrtc_nativeUtils_TRTCNativeManager_showDebugView(JNIEnv *env, jclass clazz,
                                                                        jint show_type) {
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->showDebugView(show_type);
}