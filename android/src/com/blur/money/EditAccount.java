package com.blur.money;

import android.app.TabActivity;

import android.os.Bundle;

import android.widget.TextView;
import android.widget.TabHost;

import android.view.View;

import android.content.Intent;
import android.content.ComponentName;

//import com.blur.money.file_bank;
//import com.blur.money.file_bank_helper;

public class EditAccount extends TabActivity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edit_account);

        TabHost tabhost = getTabHost();
        TabHost.TabSpec spec;
        spec = tabhost.newTabSpec("transaction_list").setIndicator("Transaction List");
        spec.setContent(new Intent().setComponent(new ComponentName("com.blur.money", "com.blur.money.TransactionList")).putExtras(getIntent().getExtras()));
        tabhost.addTab(spec);

        spec = tabhost.newTabSpec("account_overview").setIndicator("Overview");
        spec.setContent(new Intent().setComponent(new ComponentName("com.blur.money", "com.blur.money.AccountOverview")).putExtras(getIntent().getExtras()));
        tabhost.addTab(spec);
    }
}
