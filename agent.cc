#include <jvmti.h>

void JNICALL
OnClassLoad(jvmtiEnv *jvmti,
    JNIEnv *jni, jthread thread, jclass klass) {
  char *sig, *generic;
  jvmti->GetClassSignature(klass, &sig, &generic);
  printf("on class load: %s %s\n", sig, generic);
}

void JNICALL
OnThreadStart(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread) {
    jvmtiThreadInfo thread_info;
    int error = jvmti_env->GetThreadInfo(thread, &thread_info);
    if (error == JNI_OK) {
      printf("on thread start: %s", thread_info.name);
    } else {
      printf("on thread start failed to get thread info (%d)", error);
    }
}

void JNICALL
OnThreadEnd(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread) {
    jvmtiThreadInfo thread_info;
    int error = jvmti_env->GetThreadInfo(thread, &thread_info);
    if (error == JNI_OK) {
      printf("on thread end: %s", thread_info.name);
    } else {
      printf("on thread end failed to get thread info (%d)", error);
    }
}

JNIEXPORT jint JNICALL
Agent_OnLoad(JavaVM *jvm, char *options, void *reserved)
{
  printf("on load\n");

  jvmtiEnv *jvmti;
  jvm->GetEnv((void **)&jvmti, JVMTI_VERSION);
  jvmtiEventCallbacks *callbacks = new jvmtiEventCallbacks();
  callbacks->ClassLoad = &OnClassLoad;
  callbacks->ThreadStart = &OnThreadStart;
  callbacks->ThreadEnd = &OnThreadEnd;
  jvmti->SetEventCallbacks(callbacks, sizeof(jvmtiEventCallbacks));
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_LOAD, NULL);
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_THREAD_START, NULL);
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_THREAD_END, NULL);

  return JNI_OK;
}

JNIEXPORT jint JNICALL
Agent_OnAttach(JavaVM* vm, char *options, void *reserved) {
    printf("on attach\n");
    return JNI_OK;
}

JNIEXPORT void
Agent_OnUnload(JavaVM *vm) {
    printf("on unload\n");
}

