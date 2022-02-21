package com.chaoli.myjnioftrtc.nativeUtils;

import com.tencent.rtmp.ui.TXCloudVideoView;
import com.tencent.trtc.TRTCCloudDef;

public class TRTCNativeManager {
    // Used to load the 'myjnioftrtc' library on application startup.
    static {
        System.loadLibrary("myjnioftrtc");
    }

    /**
     * 获取sdk版本
     * @return sdk版本
     */
    public static native String getSDKVersion();

    /**
     * 打开本地摄像头
     * @param frontCamera 前后置摄像头
     * @param view 预览view
     */
    public static native void startLocalPreview	(	boolean 	frontCamera,
                                   TXCloudVideoView view
    );


    /**
     * 开启音频上行
     */
    public static native void startLocalAudio();


    /**
     * 进房
     * @param roomId
     * @param userId
     * @param userSig
     * @param sdkappid
     *
     */
    public static native void enterRoom	(	String roomId,
                           String userId,
                           String userSig,
                           int sdkappid
    );

    public static native void exitRoom	();

    /**
     * 订阅远端用户的视频流，并绑定视频渲染控件
     * @param userId 指定远端用户的 ID
     * @param
     * @param view 用于承载视频画面的渲染控件
     */
    public static native void startRemoteView	(	String 	userId,
                                 TXCloudVideoView 	view
    );

    /**
     * 停止本地音频的采集和发布
     */
    public static native void stopLocalAudio();

    /**
     * 停止摄像头预览
     */
    public static native void stopLocalPreview();

    /**
     * 取消订阅远端用户的视频流
     * @param userId 指定远端用户的 ID
     */
    public static native void stopRemoteView	(	String 	userId);

    /**
     * 显示仪表盘
     * @param showType 0：不显示；1：显示精简版（仅显示音视频信息）；2：显示完整版（包含音视频信息和事件信息）。
     */
    public static native void showDebugView	(	int 	showType	);


    public static native void nativeDestroy();
}
