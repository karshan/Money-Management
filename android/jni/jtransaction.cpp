#include "com_blur_money_transaction.h"
#include "account.h"
#include "transaction.h"

/*
 * Class:     com_blur_money_transaction
 * Method:    new_transaction
 * Signature: (Ljava/lang/String;F)V
 */
void Java_com_blur_money_transaction_new_1transaction__Ljava_lang_String_2F
(JNIEnv *env, jobject thiz, jstring jname, jfloat jamt)
{
    const char *name = env->GetStringUTFChars(jname, NULL);
    transaction *t = new transaction(std::string(name), (float)jamt);
    env->SetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"), (jint)t);
    env->ReleaseStringUTFChars(jname, name);
}

/*
 * Class:     com_blur_money_transaction
 * Method:    new_transaction
 * Signature: ()V
 */
void Java_com_blur_money_transaction_new_1transaction__(JNIEnv *env, jobject thiz)
{
    transaction *t = new transaction();
    env->SetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"), (jint)t);
}

/*
 * Class:     com_blur_money_transaction
 * Method:    del
 * Signature: ()V
 * Free's memory alloced by new_transaction
 */
void Java_com_blur_money_transaction_del(JNIEnv *env, jobject thiz)
{
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    delete t;
    env->SetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"), (jint)0);
}

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

/*
 * Class:     com_blur_money_transaction
 * Method:    get_amount
 * Signature: ()F
 */
jfloat Java_com_blur_money_transaction_get_1amount(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    return (jfloat)t->amount;
}

/*
 * Class:     com_blur_money_transaction
 * Method:    get_time
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_blur_money_transaction_get_1time(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    return env->NewStringUTF(ctime(&t->when));
}

/*
 * Class:     com_blur_money_transaction
 * Method:    get_comment
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_blur_money_transaction_get_1comment(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    return env->NewStringUTF(t->comment.c_str());
}

/*
 * Class:     com_blur_money_transaction
 * Method:    set_name
 * Signature: (Ljava/lang/String;)V
 */
void Java_com_blur_money_transaction_set_1name(JNIEnv *env, jobject thiz, jstring jname)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    const char *name = env->GetStringUTFChars(jname, NULL);
    t->name = name;
    env->ReleaseStringUTFChars(jname, name);
}

/*
 * Class:     com_blur_money_transaction
 * Method:    set_amount
 * Signature: (F)V
 */
void Java_com_blur_money_transaction_set_1amount
(JNIEnv *env, jobject thiz, jfloat amt)
{
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    transaction *t = (transaction *)nptr;
    t->amount = amt;
}
