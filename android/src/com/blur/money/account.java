package com.blur.money;

public class account
{
    int nptr; //HACK this is actually an account pointer (in C++)

    public account(String name)
    {
        nptr = new_account(name);
    }

    //for jni to create objects
    private account(int i)
    {
        nptr = i;
    }

    public native int new_account(String name);
    public native transaction[] get_transactions();
    public native String get_name();
    public native int get_id();
    public native boolean delete_transaction(int id);
    public native void add_transaction(transaction t);
    public native transaction get_transaction(int id);

    static {
        System.loadLibrary("money");
    }
}
