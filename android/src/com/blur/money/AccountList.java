package com.blur.money;

import android.app.ListActivity;

import android.os.Bundle;

import android.view.View;
import android.view.ViewGroup;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuInflater;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;

import android.widget.BaseAdapter;
import android.widget.AdapterView;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import android.content.Intent;
import android.content.ComponentName;
import android.content.Context;

import com.blur.money.file_bank;
import com.blur.money.cur_file_bank;
import com.blur.money.account;

class AccountAdapterView extends TextView
{
    public AccountAdapterView(Context c, account a) {
        super(c);
        //TODO: better way of displaying an item...
        super.setText("id: " + a.get_id() + "\nname: " + a.get_name());
        super.setPadding(20, 15, 20, 15);
    }
}

class AccountAdapter extends BaseAdapter
{
    private account[] accounts;
    private Context context;

    public AccountAdapter(Context c, account[] a) {
        context = c;
        accounts = a;
    }

    public void update(account[] a) {
        accounts = a;
    }

    public int getCount() {
        return accounts.length;
    }

    public Object getItem(int position) {
        return accounts[position];
    }

    public long getItemId(int position) {
        return accounts[position].get_id();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        return new AccountAdapterView(context, accounts[position]);
    }
}

public class AccountList extends ListActivity
{
    file_bank bank;

    long id_for_context_menu; //I don't know if this is the "good" way to do it...

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, 
                                    ContextMenuInfo menuInfo)
    {
        super.onCreateContextMenu(menu, v, menuInfo);

        AdapterContextMenuInfo info = (AdapterContextMenuInfo) menuInfo;
        id_for_context_menu = info.id;

        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.account_list_context_menu, menu);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterContextMenuInfo info = (AdapterContextMenuInfo) item.getMenuInfo();
        switch (item.getItemId()) {
            case R.id.delete_account:
                //this shouldn't fail because we're trying to delete an account
                //that has to have been in the list being displayed.
                if (bank.delete_account((int)id_for_context_menu) == false) {
                    Toast.makeText(getApplicationContext(), "delete failed", Toast.LENGTH_SHORT).show();
                    return true;
                }

                //TODO: there has to be a better way to do this...
                //this is basically updating the items in the list
                account[] accounts;
                accounts = bank.get_accounts();
                AccountAdapter accountAdapter = new AccountAdapter(this, accounts);
                setListAdapter(accountAdapter);

                return true;
            default:
                return super.onContextItemSelected(item);
        }
    }
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
            Intent intent = new Intent();
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

        ListView lv = getListView();
        lv.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, 
                                    int position, long id) {
                Intent intent = new Intent();
                intent.setComponent(new ComponentName("com.blur.money", "com.blur.money.EditAccount"));
                intent.putExtra("account_id", id);

                startActivity(intent);
            }
        });

        registerForContextMenu(lv);

        bank = new file_bank("/sdcard/data.bin");
        cur_file_bank.set(bank);

        if (bank.load() == false) {
            //TODO: save() and launch AddAccount, or maybe a welcome ?
            Toast.makeText(getApplicationContext(), "load failed", Toast.LENGTH_SHORT).show();
        }
    }

    public void onResume()
    {
        super.onResume();

        //TODO: there has to be a better way to do this...
        //this is basically updating the items in the list
        account[] accounts;
        accounts = bank.get_accounts();
        AccountAdapter accountAdapter = new AccountAdapter(this, accounts);
        setListAdapter(accountAdapter);
    }

    public void onDestroy()
    {
        //TODO: only save if dirty....
        super.onDestroy();
        String out = "Saved";
        if (bank.save() == false)
            out = "Save Failed";
        Toast.makeText(getApplicationContext(), out, Toast.LENGTH_SHORT).show();
    }
}
