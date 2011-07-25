package com.blur.money;

import android.app.ListActivity;

import android.os.Bundle;

import android.widget.TextView;
import android.widget.ListView;
import android.widget.BaseAdapter;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Toast;

import android.view.View;
import android.view.ViewGroup;

import android.content.Intent;
import android.content.ComponentName;
import android.content.Context;

import com.blur.money.cur_file_bank;
import com.blur.money.file_bank;
import com.blur.money.account;
import com.blur.money.transaction;

class TransactionAdapterView extends TextView
{
    public TransactionAdapterView(Context c, transaction t) {
        super(c);
        super.setText(t.get_name());
        super.setPadding(20, 15, 20, 15);
    }
}

class TransactionAdapter extends BaseAdapter
{
    private transaction[] transactions;
    private Context context;

    public TransactionAdapter(Context c, transaction[] t) {
        context = c;
        transactions = t;
    }

    public int getCount() {
        return transactions.length;
    }

    public Object getItem(int position) {
        return transactions[position];
    }

    public long getItemId(int position) {
        return transactions[position].get_id();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        return new TransactionAdapterView(context, transactions[position]);
    }
}


public class AccountOverview extends ListActivity
{
    file_bank bank;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        bank = cur_file_bank.get();
    }

    public void onResume()
    {
        super.onResume();

        Bundle extras = getIntent().getExtras();
        long acc_id = extras.getLong("account_id");

        account acc = bank.get_account((int)acc_id);
        transaction transactions[] = acc.get_transactions();

        setListAdapter(new TransactionAdapter(this, transactions));
        ListView lv = getListView();
        lv.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view,
                                    int position, long id) {
                            Toast.makeText(getApplicationContext(), ((TextView)view).getText().toString(), Toast.LENGTH_SHORT).show();
            }
        });
    }
}
