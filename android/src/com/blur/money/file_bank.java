package com.blur.money;

import com.blur.money.account;

public class file_bank
{
    int nptr; //HACK this is actually a file_bank pointer (in C++)
    public file_bank(String fname)
    {
        new_file_bank(fname);
    }

    //This native constructor allocates a C++ file_bank and stores a pointer to it in nptr
    //it must be free'd by calling del
    public native void new_file_bank(String fname);
    public native void del();

    public native boolean load();
    public native boolean save();
    public native account[] get_accounts();
    //TODO: make this return int (id) and take an account
    public native void add_account(String name);
    public native account get_account(int id);
    public native boolean delete_account(int id);

    static {
        System.loadLibrary("money");
    }
}
