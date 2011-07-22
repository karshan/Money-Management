#include "com_blur_money_maingui.h"

#include <cstdio>
#include <cstdarg>
#include <string>
#include <ctime>

#include <pthread.h>

#include "file_bank.h"

#define JPRINTF_BUFSIZ 100
#define JSCANF_BUFSIZ 100

/*
 * This function assumes the object calling has a field named tv which is of
 * type TextView to which the printing will be done, using the append method
 * TODO: error handling/reporting
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

    char buf[JPRINTF_BUFSIZ];
    int n = vsprintf(buf, fmt, va);

    jstr = env->NewStringUTF(buf);
    cls = env->GetObjectClass(thiz);
    fid = env->GetFieldID(cls, "tv", "Landroid/widget/TextView;");
    textView = env->GetObjectField(thiz, fid);
    textCls = env->GetObjectClass(textView);

    mid = env->GetMethodID(textCls, "append", "(Ljava/lang/CharSequence;)V");
    env->CallVoidMethod(textView, mid, jstr);

    va_end(va);
    return n;
}

char jscanf_buf[JSCANF_BUFSIZ];
pthread_mutex_t jscanf_sleep_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t jscanf_sleep_cond = PTHREAD_COND_INITIALIZER;
void Java_com_blur_money_maingui_jni_1notify_1input(JNIEnv *env, jobject thiz,
                                                    jstring input)
{
    const char *str;
    str = env->GetStringUTFChars(input, NULL);

    jprintf(env, thiz, "%s\n", str); //everything will die if you don't print something here everytime.
                                     //also its kinda hard to figure out why... so this is a _HACK_

    pthread_mutex_lock(&jscanf_sleep_mutex);
        strncpy(jscanf_buf, str, JSCANF_BUFSIZ);
        pthread_cond_signal(&jscanf_sleep_cond);
    pthread_mutex_unlock(&jscanf_sleep_mutex);
}

int jscanf(JNIEnv *env, jobject thiz, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    char local_buf[JSCANF_BUFSIZ];

    pthread_mutex_lock(&jscanf_sleep_mutex);
        pthread_cond_wait(&jscanf_sleep_cond, &jscanf_sleep_mutex);
        strncpy(local_buf, jscanf_buf, JSCANF_BUFSIZ);
    pthread_mutex_unlock(&jscanf_sleep_mutex);
    int n = vsscanf(local_buf, fmt, va);
    va_end(va);

    return n;
}

void account_menu(JNIEnv *env, jobject thiz, account & acc)
{
    jprintf(env, thiz, "Account Menu isn't yet available\n");
}

void Java_com_blur_money_maingui_jni_1main(JNIEnv *env, jobject thiz)
{
    int chc;
    std::string fname("/sdcard/data.bin");
    file_bank bank(fname);

    do {
        jprintf(env, thiz, "Main Menu: (file: %s)\n", fname.c_str());
        jprintf(env, thiz, "accounts:\n\tid\tname\n");
        for (std::vector<account>::const_iterator it = bank.accounts_begin();
             it != bank.accounts_end(); it++)
            jprintf(env, thiz, "\t%u\t%s\n", (*it).get_id(), (*it).name.c_str());

        jprintf(env, thiz, "0)exit\n"
                           "1)load\n"
                           "2)save\n"
                           "3)add account\n"
                           "4)edit account\n"
                           "5)delete account\n"
                           "enter choice: ");
        chc = 0;
        jscanf(env, thiz, "%d", &chc);

        jprintf(env, thiz, "Yowza\n");

        char acc[100];
        unsigned int id;
        switch(chc) {
        case 0:
            break;
        case 1:
            bank.load();
            break;
        case 2:
            bank.save();
            break;
        case 3:
            jprintf(env, thiz, "enter account name: ");
            jscanf(env, thiz, "%s", acc);
            jprintf(env, thiz, "Yowza\n");
            bank.add_account(account(std::string(acc)));
            break;
        case 4:
            jprintf(env, thiz, "enter account id: ");
            id = 0;
            jscanf(env, thiz, "%u", &id);
            jprintf(env, thiz, "Yowza\n");
            try {
                account_menu(env, thiz, bank.get_account(id));
            }
            catch (bad_id & e) {
                jprintf(env, thiz, "%s\n", e.what());
            }
            break;
        case 5:
            jprintf(env, thiz, "enter account id: ");
            jscanf(env, thiz, "%u", &id);
            jprintf(env, thiz, "Yowza\n");
            if (!bank.delete_account(id))
                jprintf(env, thiz, "Failed! bad id\n");
            break;
        default:
            jprintf(env, thiz, "bad choice\n");
        }
    } while(chc != 0);
    jprintf(env, thiz, "Goodbye\n");
}
