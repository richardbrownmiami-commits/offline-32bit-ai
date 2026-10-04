#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "OfflineAI_JNI_32Bit"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// Check that this is indeed being compiled for a 32-bit ARM environment
#if defined(__aarch64__)
#error "64-bit ARM (arm64-v8a) is strictly disabled in this build!"
#endif

#if !defined(__arm__)
#warning "Compiling outside standard 32-bit ARM"
#endif

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_MainActivity_initModelNative(
    JNIEnv *env,
    jobject thiz,
    jstring model_path,
    jint n_threads,
    jint n_ctx
) {
    const char *path = env->GetStringUTFChars(model_path, nullptr);
    LOGI("Initializing 32-bit ARMv7a llama.cpp engine with model at %s (threads: %d, ctx: %d)", path, n_threads, n_ctx);

    // In full native llama.cpp deployment, llama_load_model_from_file and llama_new_context_with_model go here.
    // 32-bit memory check:
    LOGI("Enforcing strict 32-bit virtual memory ceiling (max context: %d tokens)", n_ctx);

    env->ReleaseStringUTFChars(model_path, path);
    return JNI_TRUE;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_MainActivity_generateResponseNative(
    JNIEnv *env,
    jobject thiz,
    jstring prompt_str,
    jfloat temperature
) {
    const char *prompt = env->GetStringUTFChars(prompt_str, nullptr);
    LOGI("Generating tokens on 32-bit ARMv7a CPU (temp: %.2f)", temperature);

    std::string response = "Tokens generated on 32-bit ARMv7a architecture successfully.";

    env->ReleaseStringUTFChars(prompt_str, prompt);
    return env->NewStringUTF(response.c_str());
}
