package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;

import android.widget.EditText;

import com.blur.money.file_bank;
import com.blur.money.file_bank_helper;

public class AddAccount extends Activity implements OnKeyListener
{
    file_bank bank;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_account);

        bank = file_bank_helper.getInstance();

        EditText name = (EditText)findViewById(R.id.name);
        name.setOnKeyListener(this);
    }
    public boolean onKey(View v, int keyCode, KeyEvent event)
    {
        if ((event.getAction() == KeyEvent.ACTION_DOWN) && (keyCode == KeyEvent.KEYCODE_ENTER)) {
            bank.add_account(((EditText)v).getText().toString());
            finish();
//            ((EditText)v).setText("");
            return true;
        }
        return false;
    }

}
