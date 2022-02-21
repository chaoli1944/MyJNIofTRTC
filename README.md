# MyJNIofTRTC
通过JNI集成腾讯实时音视频，实现1V1视频通话

### 说明
代码主要演示AndroidStudio通过JNI的方式，集成TRTCSDK，并实现1V1视频通话

### 前提条件
您已 [注册腾讯云](https://cloud.tencent.com/document/product/378/17985) 账号，并完成 [实名认证](https://cloud.tencent.com/document/product/378/3629)。


### 申请 SDKAPPID 和 SECRETKEY
1. 登录实时音视频控制台，选择【开发辅助】>【[快速跑通Demo](https://console.cloud.tencent.com/trtc/quickstart)】。
2. 单击【立即开始】，输入您的应用名称，例如`TestTRTC`，单击【创建应用】。

![ #900px](https://main.qcloudimg.com/raw/169391f6711857dca6ed8cfce7b391bd.png)
3. 创建应用完成后，单击【我已下载，下一步】，可以查看 SDKAppID 和密钥信息。


### 配置 Demo 工程文件
1. 使用 Android Studio（3.5及以上的版本）打开源码工程`TRTC-API-Example`
2. 找到并打开`TRTC-API-Example/Debug/src/main/java/com/tencent/trtc/debug/GenerateTestUserSig.java`文件。
3. 设置`GenerateTestUserSig.java`文件中的相关参数：
  - `SDKAPPID`：默认为 PLACEHOLDER ，请设置为实际的 SDKAppID；
  - `SECRETKEY`：默认为空字符串，请设置为实际的密钥信息；
 ![ #900px](https://main.qcloudimg.com/raw/8fb309ce8c378dd3ad2c0099c57795a5.png)

4. 返回实时音视频控制台，单击【粘贴完成，下一步】。
5. 单击【关闭指引，进入控制台管理应用】。
6. demo中演示了自定义采集音频，需要pcm文件，请自行获取。
7. 包文件夹下，有一个pcm音乐文件，提供测试使用，可以把它放到手机本地sd下audioResearch/PCM路径下。
8. pcm文件名称：bei_yi_wang_de_shi_guang.pcm  、 44100hz 、 双声道 、 16位宽，无损音质。

>!本文提到的生成 UserSig 的方案是在客户端代码中配置 SECRETKEY，该方法中 SECRETKEY 很容易被反编译逆向破解，一旦您的密钥泄露，攻击者就可以盗用您的腾讯云流量，因此**该方法仅适合本地跑通 Demo 和功能调试**。
>正确的 UserSig 签发方式是将 UserSig 的计算代码集成到您的服务端，并提供面向 App 的接口，在需要 UserSig 时由您的 App 向业务服务器发起请求获取动态 UserSig。更多详情请参见 [服务端生成 UserSig](https://cloud.tencent.com/document/product/647/17275#Server)。
