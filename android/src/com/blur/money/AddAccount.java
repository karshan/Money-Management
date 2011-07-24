package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.view.View;

import android.widget.TextView;

public class AddAccount extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        TextView tv = new TextView(this);
        tv.setText("Activity: AddAccount\nWIP...");
        setContentView(tv);
    }
}
