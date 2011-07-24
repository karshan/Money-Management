package com.blur.money;

import com.blur.money.file_bank;

public class file_bank_helper
{
    private static file_bank bank = null;

    public static file_bank getInstance()
    {
        if (bank == null)
            bank = new file_bank("/sdcard/data.bin");
        return bank;
    }
}
