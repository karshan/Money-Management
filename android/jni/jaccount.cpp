#include "com_blur_money_account.h"
#include "account.h"
#include "transaction.h"

//TODO: maybe return jlong ??
/*
 * Class:     com_blur_money_account
 * Method:    get_id
 * Signature: ()I
 */
jint Java_com_blur_money_account_get_1id(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;
    return (jint)acc->get_id();
}

/*
 * Class:     com_blur_money_account
 * Method:    get_name
 * Signature: ()Ljava/lang/String;
 */
jstring Java_com_blur_money_account_get_1name(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;

    return env->NewStringUTF(acc->name.c_str());
}

/*
 * Class:     com_blur_money_account
 * Method:    get_transactions
 * Signature: ()[Lcom/blur/money/transaction;
 */
jobjectArray Java_com_blur_money_account_get_1transactions(JNIEnv *env, jobject thiz)
{
    jobject array_initer;

    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;

    const std::vector<transaction> transactions(acc->get_transactions());

    jclass transaction_cls = env->FindClass("com/blur/money/transaction");
    array_initer = env->NewObject(transaction_cls, env->GetMethodID(transaction_cls, "<init>", "(I)V"), (jint)0);
    jobjectArray jtransactions = env->NewObjectArray(transactions.size(), transaction_cls, array_initer);

    int i = 0; // Why do I have to do this ? g++ doesn't seem to be happy with this in the for loop initializer
    for (std::vector<transaction>::const_iterator it = transactions.begin(); it != transactions.end(); it++, i++) {
        transaction *a = acc->get_transaction((*it).get_id());
        array_initer = env->NewObject(transaction_cls, env->GetMethodID(transaction_cls, "<init>", "(I)V"), (jint)a);
        env->SetObjectArrayElement(jtransactions, i, array_initer);
    }

    return jtransactions;
}

/*
 * Class:     com_blur_money_account
 * Method:    delete_transaction
 * Signature: (I)Z
 */
jboolean Java_com_blur_money_account_delete_1transaction(JNIEnv *env, jobject thiz, jint id)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;
    if (acc->delete_transaction((unsigned int)id))
        return JNI_TRUE;
    return JNI_FALSE;
}

/*
 * Class:     com_blur_money_account
 * Method:    add_transaction
 * Signature: (Lcom/blur/money/transaction;)V
 */
void Java_com_blur_money_account_add_1transaction(JNIEnv *env, jobject thiz, jobject trans)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;

    jint tnptr = env->GetIntField(trans, env->GetFieldID(env->GetObjectClass(trans), "nptr", "I"));
    transaction *t = (transaction *)tnptr;

    acc->add_transaction(*t);
}

/*
 * Class:     com_blur_money_account
 * Method:    get_transaction
 * Signature: (I)Lcom/blur/money/transaction;
 */
jobject Java_com_blur_money_account_get_1transaction
(JNIEnv *env, jobject thiz, jint id)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    account *acc = (account *)nptr;

    transaction *a = acc->get_transaction((unsigned int)id);
    jclass transaction_cls = env->FindClass("com/blur/money/transaction");
    jobject jtn = env->NewObject(transaction_cls, env->GetMethodID(transaction_cls, "<init>", "(I)V"), (jint)a);

    return jtn;
}
