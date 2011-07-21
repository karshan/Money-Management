package com.blur.money;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.ScrollView;

/* 
 * This is horribly written, and is just to emulate the commandline
 * so I can test that the basic framework will compile and run on
 * android and pc, the class organization is abysmal the names are
 * bad, and the way I use the class to run the jni_main as a thread
 * is pretty hacky, but as soon as I see that everything basic works
 * all this will change and it will be a nice gui and well maintained
 * class structure with good names :) I Solemnly Swear That I'm Upto
 * No Good
 */

public class maingui extends Activity implements Runnable
{
    TextView tv; /* For easy access from jni... */
    String inputText;

    public void run() {
        jni_main();
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        tv = (TextView) findViewById(R.id.showtext);

        inputText = "";

        final EditText edittext = (EditText) findViewById(R.id.edittext);
        final ScrollView scrolltext = (ScrollView) findViewById(R.id.scrolltext);

        edittext.setOnKeyListener(new OnKeyListener() {
            synchronized public boolean onKey(View v, int keycode, KeyEvent event) {
                if ((event.getAction() == KeyEvent.ACTION_DOWN) &&
                    (keycode == KeyEvent.KEYCODE_ENTER)) {

                    inputText = edittext.getText().toString();
                    scrolltext.fullScroll(View.FOCUS_DOWN);
                    edittext.setText("");

                    scrolltext.fullScroll(View.FOCUS_DOWN);
                    edittext.requestFocus();

                    jni_notify_input(inputText);

                    return true;
                }
                return false;
            }
        });

        (new Thread(this)).start(); //run jni main in a seperate thread so onkeylistener works
    }

    native void jni_main();
    native void jni_notify_input(String input); //calling this wakes jscanf up.

    static {
        System.loadLibrary("money");
    }
}
