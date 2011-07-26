package com.blur.money;

import com.blur.money.file_bank;

//This is basically what would be a global variable in C/C++
//Sigh...

public class cur_file_bank
{
    private static file_bank bank = null;

    public static file_bank get() {
        return bank;
    }

    public static void set(file_bank b) {
        bank = b;
    }
}
