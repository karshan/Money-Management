package com.blur.money;

import android.app.ListActivity;

import android.os.Bundle;

import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuInflater;

import android.widget.ArrayAdapter;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import android.content.Intent;
import android.content.ComponentName;

import com.blur.money.file_bank;
import com.blur.money.file_bank_helper;

public class AccountList extends ListActivity
{
    file_bank bank;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.account_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
        case R.id.new_account:
            Intent intent = new Intent(Intent.ACTION_INSERT, getIntent().getData());
            intent.setComponent(new ComponentName("com.blur.money", "com.blur.money.AddAccount"));
            startActivity(new Intent(intent));
            return true;
        case R.id.save:
            String out = "Saved";
            if (bank.save() == false)
                out = "Save Failed";
            Toast.makeText(getApplicationContext(), out, Toast.LENGTH_SHORT).show();
            return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        bank = file_bank_helper.getInstance();
        if (bank.load() == false) {
            //TODO: save() and launch AddAccount, or maybe a welcome ?
            Toast.makeText(getApplicationContext(), "load failed", Toast.LENGTH_SHORT).show();
        }
    }

    public void onResume()
    {
        super.onResume();

        String[] accounts = bank.get_accounts();
        setListAdapter(new ArrayAdapter<String>(this, R.layout.account_list_item, accounts));
        ListView lv = getListView();
        lv.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, 
                                    int position, long id) {
                Intent intent = new Intent(Intent.ACTION_EDIT, getIntent().getData());
                intent.setComponent(new ComponentName("com.blur.money", "com.blur.money.EditAccount"));
                intent.putExtra("account_name", ((TextView) view).getText().toString());
                startActivity(intent);
            }
        });
    }
}
