package com.blur.money;

import android.app.Activity;

import android.os.Bundle;

import android.view.KeyEvent;
import android.view.View;

import android.widget.EditText;
import android.widget.Button;
import android.widget.Toast;

import com.blur.money.file_bank;
import com.blur.money.cur_file_bank;
import com.blur.money.account;

public class EditTransaction extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_transaction);

        final transaction t = getIntent().getParcelableExtra("transaction");

        final EditText inName = (EditText)findViewById(R.id.name);
        final EditText inAmount = (EditText)findViewById(R.id.amount);

        inName.setText(t.get_name());
        inAmount.setText((new Float(t.get_amount()).toString()));

        Button button = (Button) findViewById(R.id.save);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                float amt;
                try {
                    amt = (new Float(inAmount.getText().toString())).floatValue();
                } catch(NumberFormatException e) {
                    Toast.makeText(getApplicationContext(), "Bad Amount", Toast.LENGTH_SHORT).show();
                    return;
                }
                t.set_name((inName.getText().toString()));
                t.set_amount(amt);
                setResult(RESULT_OK, getIntent());
                finish();
            }
        });
    }
}

