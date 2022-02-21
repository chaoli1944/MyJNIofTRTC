//
// Created by lichao on 2022/2/18.
//

#ifndef MYJNIOFTRTC_LOGUTIL_H
#define MYJNIOFTRTC_LOGUTIL_H

#include <android/log.h>

#define TAG "CHAOLILOG"
//...我都不知道传入什么，借助JNI里面的宏来自动帮我填充
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGI(...)__android_log_print(ANDROID_LOG_NFO,TAG,__VA_ARGS__)


#endif //MYJNIOFTRTC_LOGUTIL_H
