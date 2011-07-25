#include "com_blur_money_transaction.h"
#include "account.h"
#include "transaction.h"

/*
 * Class:     com_blur_money_transaction
 * Method:    get_name
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_blur_money_transaction_get_1name(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    return env->NewStringUTF(t->name.c_str());
}

/*
 * Class:     com_blur_money_transaction
 * Method:    get_id
 * Signature: ()I
 */
jint Java_com_blur_money_transaction_get_1id(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    return (jint)t->get_id();
}
