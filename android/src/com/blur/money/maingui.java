package com.blur.money;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class maingui extends Activity
{
    TextView tv; /* For easy access from jni... */

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        tv = (TextView) findViewById(R.id.text);
        jni_main();
    }

    native void jni_main();

    static {
        System.loadLibrary("money");
    }
}
