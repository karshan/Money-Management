package com.blur.money;

import java.util.Date;
import java.util.Calendar;
import java.util.GregorianCalendar;

import android.app.Activity;
import android.app.Dialog;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;

import android.os.Bundle;

import android.view.KeyEvent;
import android.view.View;

import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TimePicker;
import android.widget.Toast;

import com.blur.money.file_bank;
import com.blur.money.cur_file_bank;
import com.blur.money.account;

public class EditTransaction extends Activity
{
    static final int DATE_DIALOG_ID = 0;
    static final int TIME_DIALOG_ID = 1;

    private int day, month, year, hour, minute;
    private TextView dateText;
    private TextView timeText;

    private String zeroPad(int a) {
        if (a >= 10)
            return String.valueOf(a);
        else
            return "0" + String.valueOf(a);
    }

    private void updateDate() {
        dateText.setText(
            new StringBuilder()
                // Month is 0 based so add 1
                .append(month + 1).append("-")
                .append(day).append("-")
                .append(year).append(" ")
        );
    }

    private void updateTime() {
        timeText.setText(
            new StringBuilder()
                .append(zeroPad(hour)).append(":")
                .append(zeroPad(minute)).append(" ")
        );
    }

    // the callback received when the user "sets" the date in the dialog
    private DatePickerDialog.OnDateSetListener DateSetListener =
        new DatePickerDialog.OnDateSetListener() {
            public void onDateSet(DatePicker view, int y,
                                  int m, int d) {
                year = y;
                month = m;
                day = d;
                updateDate();
            }
        };

    private TimePickerDialog.OnTimeSetListener TimeSetListener =
        new TimePickerDialog.OnTimeSetListener() {
            public void onTimeSet(TimePicker view, int h,
                                  int m) {
                hour = h;
                minute = m;
                updateTime();
            }
        };


    @Override
    protected Dialog onCreateDialog(int id)
    {
        switch (id) {
        case DATE_DIALOG_ID:
            return new DatePickerDialog(this, DateSetListener, year, month, day);
        case TIME_DIALOG_ID:
            return new TimePickerDialog(this, TimeSetListener, hour, minute, false);
        }
        return null;
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edit_transaction);

        final transaction t = getIntent().getParcelableExtra("transaction");

        final EditText inName = (EditText)findViewById(R.id.name);
        final EditText inAmount = (EditText)findViewById(R.id.amount);

        dateText = (TextView)findViewById(R.id.date_text);
        Button dateButton = (Button)findViewById(R.id.date_button);

        timeText = (TextView)findViewById(R.id.time_text);
        Button timeButton = (Button)findViewById(R.id.time_button);

        inName.setText(t.get_name());
        inAmount.setText((new Float(t.get_amount()).toString()));

        Button saveButton = (Button) findViewById(R.id.save);

        Date when = new Date(t.get_when());

        Calendar c = Calendar.getInstance();
        c.setTime(when);
        year = c.get(Calendar.YEAR);
        month = c.get(Calendar.MONTH);
        day = c.get(Calendar.DAY_OF_MONTH);

        // display the current date (this method is below)
        updateDate();

        dateButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                showDialog(DATE_DIALOG_ID);
            }
        });

        hour = c.get(Calendar.HOUR_OF_DAY);
        minute = c.get(Calendar.MINUTE);

        updateTime();

        timeButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                showDialog(TIME_DIALOG_ID);
            }
        });

        saveButton.setOnClickListener(new View.OnClickListener() {
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
                t.set_when((new GregorianCalendar(year, month, day, hour, minute)).getTimeInMillis());
                setResult(RESULT_OK, getIntent());
                finish();
            }
        });
    }
}

