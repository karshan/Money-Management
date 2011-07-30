package com.blur.money;

import android.app.ListActivity;

import android.os.Bundle;

import android.widget.TextView;
import android.widget.ListView;
import android.widget.BaseAdapter;
import android.widget.AdapterView;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Toast;

import android.view.View;
import android.view.ViewGroup;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuInflater;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;

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
        super.setText("id: " + t.get_id() + "\nname: " + t.get_name() +
                        "\namount: " + t.get_amount() + "\ntime: " + t.get_time());
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

//TODO: this class needs to be renamed... it is the activity that represents the
//tab "overview" in the EditAccount TabActivity
public class AccountOverview extends ListActivity
{
    private static final int NEW_TRANSACTION = 1;
    private static final int EDIT_TRANSACTION = 2;

    file_bank bank;
    account acc;

    long id_for_context_menu; //I don't know if this is the "good" way to do it...

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v,
                                    ContextMenuInfo menuInfo)
    {
        super.onCreateContextMenu(menu, v, menuInfo);

        AdapterContextMenuInfo info = (AdapterContextMenuInfo) menuInfo;
        id_for_context_menu = info.id;

        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.transaction_list_context_menu, menu);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterContextMenuInfo info = (AdapterContextMenuInfo) item.getMenuInfo();
        switch (item.getItemId()) {
            case R.id.delete_transaction:
                //this shouldn't fail because we're trying to delete a transaction
                //that has to have been in the list being displayed.
                if (acc.delete_transaction((int)id_for_context_menu) == false) {
                    Toast.makeText(getApplicationContext(), "delete failed", Toast.LENGTH_SHORT).show();
                    return true;
                }

                //TODO: there has to be a better way to do this...
                //this is basically updating the items in the list
                transaction[] transactions = acc.get_transactions();
                setListAdapter(new TransactionAdapter(this, transactions));

                return true;
            default:
                return super.onContextItemSelected(item);
        }
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.account_overview_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
        case R.id.new_transaction:
            transaction t = new transaction("", 0);
            Intent intent = new Intent();
            intent.setComponent(new ComponentName("com.blur.money", "com.blur.money.EditTransaction"));
            intent.putExtra("transaction", t);
            startActivityForResult(new Intent(intent), NEW_TRANSACTION);
            return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (requestCode == NEW_TRANSACTION) {
            transaction t = data.getParcelableExtra("transaction");
            acc.add_transaction(t);
        } else if (requestCode == EDIT_TRANSACTION) {
            //Nothing to do...
        } else {
            Toast.makeText(getApplicationContext(), "AccOverview: onActivityResult unknown request code: " + requestCode, Toast.LENGTH_SHORT).show();
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
                intent.setComponent(new ComponentName("com.blur.money", "com.blur.money.EditTransaction"));
                //TODO: make all id's long!!!
                transaction t = acc.get_transaction((int)id);
                intent.putExtra("transaction", t);
                startActivityForResult(new Intent(intent), EDIT_TRANSACTION);
            }
        });

        registerForContextMenu(lv);

        bank = cur_file_bank.get();

        Bundle extras = getIntent().getExtras();
        long acc_id = extras.getLong("account_id");
        acc = bank.get_account((int)acc_id);
    }

    public void onResume()
    {
        super.onResume();

        transaction transactions[] = acc.get_transactions();
        setListAdapter(new TransactionAdapter(this, transactions));
    }
}
