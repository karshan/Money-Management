package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.widget.TextView;

import com.blur.money.file_bank;
import com.blur.money.file_bank_helper;

public class EditAccount extends Activity
{
    file_bank bank;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Bundle extras = getIntent().getExtras();
        String acc_name = extras.getString("account_name");

        bank = file_bank_helper.getInstance();

        TextView tv = new TextView(this);
        tv.setText("EditAccount Activity\n" + acc_name);

        setContentView(tv);
    }
}
