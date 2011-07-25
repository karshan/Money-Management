package com.blur.money;

public class account
{
    int nptr; //HACK this is actually an account pointer (in C++)

    public account(String name)
    {
        nptr = new_account(name);
    }

    public account()
    {
        nptr = 0;
    }

    public native int new_account(String name);
    public native transaction[] get_transactions();
    public native String get_name();
    public native int get_id();

    static {
        System.loadLibrary("money");
    }
}
