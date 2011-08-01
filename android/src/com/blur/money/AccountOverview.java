package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.widget.TextView;

import com.blur.money.transaction;
import com.blur.money.account;
import com.blur.money.file_bank;
import com.blur.money.cur_file_bank;

public class AccountOverview extends Activity
{
    account acc;
    TextView v;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        v = new TextView(this);

        file_bank bank = cur_file_bank.get();
        acc = bank.get_account((int)getIntent().getExtras().getLong("account_id"));

        setContentView(v);
    }

    @Override
    public void onResume()
    {
        super.onResume();

        transaction[] ts = acc.get_transactions();

        float bal = 0;
        for (int i = 0; i < ts.length; i++)
            bal += ts[i].get_amount();

        v.setText("Balance: " + bal);
    }
}
