package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.widget.TextView;

public class AccountOverview extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        TextView v = new TextView(this);
        v.setText("Overview:");
        setContentView(v);
    }
}
