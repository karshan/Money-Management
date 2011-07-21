#include "com_blur_money_maingui.h"

#include <cstdio>
#include <cstdarg>
#include <string>
#include <ctime>

#include "file_bank.h"

/*
 * This function assumes the object calling has a field named tv which is of
 * type TextView to which the printing will be done, using the append method
 * TODO: error checking/handling
 */
int jprintf(JNIEnv *env, jobject thiz, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    jstring jstr;
    jclass cls;
    jfieldID fid;
    jmethodID mid;
    jclass textCls;
    jobject textView;

    char buf[100];
    int n = vsprintf(buf, fmt, va);

    jstr = env->NewStringUTF(buf);
    cls = env->GetObjectClass(thiz);
    fid = env->GetFieldID(cls, "tv", "Landroid/widget/TextView;");
    textView = env->GetObjectField(thiz, fid);
    textCls = env->GetObjectClass(textView);

    mid = env->GetMethodID(textCls, "append", "(Ljava/lang/CharSequence;)V");
    env->CallVoidMethod(textView, mid, jstr);

    va_end(va);
}

void Java_com_blur_money_maingui_jni_1main(JNIEnv *env, jobject thiz)
{
    std::string fname("data.bin");
    file_bank bank(fname);

    jprintf(env, thiz, "test = %d\n", 42);
}
