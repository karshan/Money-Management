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

import com.blur.money.file_bank;

public class AccountList extends ListActivity
{
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
            startActivity(new Intent(Intent.ACTION_INSERT, getIntent().getData()));
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

        file_bank bank = new file_bank("/sdcard/data.bin");

        if (bank.load() == false) {
            //TODO: save() and launch AddAccount, or maybe a welcom ?
            Toast.makeText(getApplicationContext(), "load failed", Toast.LENGTH_SHORT).show();
        }
        String[] accounts = bank.get_accounts();

        setListAdapter(new ArrayAdapter<String>(this, R.layout.list_item, accounts));
        ListView lv = getListView();
        lv.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, 
                                    int position, long id) {
                Toast.makeText(getApplicationContext(), ((TextView) view).getText(),
                    Toast.LENGTH_SHORT).show();
            }
        });
    }
}
