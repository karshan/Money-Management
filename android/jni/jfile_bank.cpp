#include "com_blur_money_file_bank.h"
#include "file_bank.h"

/*
 * Class:     com_blur_money_file_bank
 * Method:    new_file_bank
 * Signature: (Ljava/lang/String;)I
 */
jint Java_com_blur_money_file_1bank_new_1file_1bank
(JNIEnv *env, jobject thiz, jstring jfname)
{
    const char *jutf_fname = env->GetStringUTFChars(jfname, NULL);
    file_bank *bank = new file_bank(std::string(jutf_fname));
    env->ReleaseStringUTFChars(jfname, jutf_fname);
    return (jint)bank;
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    load
 * Signature: ()Z
 */
jboolean JNICALL Java_com_blur_money_file_1bank_load(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    try {
        bank->load();
    }
    catch(...) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    save
 * Signature: ()Z
 */
jboolean Java_com_blur_money_file_1bank_save(JNIEnv *env, jobject thiz)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    try {
        bank->save();
    }
    catch(...) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    get_accounts
 * Signature: ()[Lcom/blur/money/account;
 */
jobjectArray Java_com_blur_money_file_1bank_get_1accounts(JNIEnv *env, jobject thiz)
{
    jobject array_initer;

    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    const std::vector<account> accounts(bank->get_accounts());

    jclass account_cls = env->FindClass("com/blur/money/account");
    array_initer = env->NewObject(account_cls, env->GetMethodID(account_cls, "<init>", "()V"));
    jobjectArray jaccounts = env->NewObjectArray(accounts.size(), account_cls, array_initer);

    int i = 0; // Why do I have to do this ? g++ doesn't seem to be happy with this in the for loop initializer
    for (std::vector<account>::const_iterator it = accounts.begin(); it != accounts.end(); it++, i++) {
        array_initer = env->NewObject(account_cls, env->GetMethodID(account_cls, "<init>", "()V"));
        account *a = new account(*it);
        env->SetIntField(array_initer, env->GetFieldID(account_cls, "nptr", "I"), (jint)a);
        env->SetObjectArrayElement(jaccounts, i, array_initer);
    }

    return jaccounts;
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    add_account
 * Signature: (Ljava/lang/String;)V
 */
void Java_com_blur_money_file_1bank_add_1account
(JNIEnv *env, jobject thiz, jstring jname)
{
     //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    const char *jutf_name = env->GetStringUTFChars(jname, NULL);
    bank->add_account(account(std::string(jutf_name)));
    env->ReleaseStringUTFChars(jname, jutf_name);
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    get_account
 * Signature: (I)Lcom/blur/money/account;
 */
jobject Java_com_blur_money_file_1bank_get_1account(JNIEnv *env, jobject thiz, jint acc_id)
{
     //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    account *a = NULL;
    jclass account_cls = env->FindClass("com/blur/money/account");
    jobject jacc = env->NewObject(account_cls, env->GetMethodID(account_cls, "<init>", "()V"));

    //TODO: this should change when I mak get_account return a pointer and NULL means error
    //it won't throw any exceptions then...
    try {
        a = new account(bank->get_account((unsigned int)acc_id));
    }
    catch(...) {
        return (jobject)NULL;
    }

    env->SetIntField(jacc, env->GetFieldID(account_cls, "nptr", "I"), (jint)a);

    return jacc;
}

/*
 * Class:     com_blur_money_file_bank
 * Method:    delete_account
 * Signature: (I)Z
 */
jboolean Java_com_blur_money_file_1bank_delete_1account(JNIEnv *env, jobject thiz, jint id)
{
    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    if (bank->delete_account((unsigned int)id))
        return JNI_TRUE;
    return JNI_FALSE;
}

