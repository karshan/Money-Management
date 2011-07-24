package com.blur.money;

public class file_bank
{
    int nptr; //HACK this is actuall a file_bank pointer (in C++)
    public file_bank(String fname)
    {
        nptr = new_file_bank(fname);
    }

    public native int new_file_bank(String fname);
    public native boolean load();
    public native String[] get_accounts();

    static {
        System.loadLibrary("money");
    }
}
