#include "com_blur_money_file_bank.h"
#include "file_bank.h"

/*
 * Class:     com_blur_money_file_bank
 * Method:    new_file_bank
 * Signature: Object new_file_bank(String);
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
 * Signature: boolean load();
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
 * Class:     com.blur.money.file_bank
 * Signature: String[] get_accounts();
 * returns String[] of all the account names in the file_bank object thiz.
 */
jobjectArray Java_com_blur_money_file_1bank_get_1accounts(JNIEnv *env, jobject thiz)
{
    jstring array_initer;

    //HACK we use the nptr int field in the java class to store a file_bank ptr =)
    jint nptr = env->GetIntField(thiz, env->GetFieldID(env->GetObjectClass(thiz), "nptr", "I"));
    file_bank *bank = (file_bank *)nptr;

    const std::vector<account> accounts(bank->get_accounts());

    array_initer = env->NewStringUTF("");
    jobjectArray jaccounts = env->NewObjectArray(accounts.size(), env->GetObjectClass(array_initer), array_initer);

    int i = 0; // Why do I have to do this ? g++ doesn't seem to be happy with this in the for loop initializer
    for (std::vector<account>::const_iterator it = accounts.begin(); it != accounts.end(); it++, i++)
        env->SetObjectArrayElement(jaccounts, i, env->NewStringUTF((*it).name.c_str()));

    return jaccounts;
}
