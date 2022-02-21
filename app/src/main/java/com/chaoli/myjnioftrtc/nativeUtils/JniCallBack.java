package com.chaoli.myjnioftrtc.nativeUtils;

public class JniCallBack {
    public interface callBack{
        void onUserVideoAvailable(String userId,boolean available);
        void onEnterRoom(int result);
        void onExitRoom(int reason);
    }

    private static callBack CALLBACK;

    public static void setCallback(callBack callback){
        CALLBACK = callback;
    }

    /**
     * jni 调用java方法
     * @param userId 远端用户id
     * @param available 远端流状态
     */
    public static void jniCallUserVideoAvailable(String userId,boolean available){
        CALLBACK.onUserVideoAvailable(userId,available);
    }

    public static void jniCallOnEnterRoom(int result){
        CALLBACK.onEnterRoom(result);
    }

    public static void jniCallOnExitRoom(int reason){
        CALLBACK.onExitRoom(reason);
    }
}
