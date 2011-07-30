package com.blur.money;

import android.os.Parcelable;
import android.os.Parcel;

//This class implements Parcelable so that "references" to
//objects of this class can be passed around between activities
//"references" since nptr is a pointer and that is the only
//data contained in this class, thus two objects of transaction
//with the same nptr are essentially refering to the same underlying
//(C++) transaction
public class transaction implements Parcelable {
    private int nptr; //A pointer to a (C++) transaction used by native (C++) code

    //Parcelable interface {
    public int describeContents() {
        return 0;
    }

    public void writeToParcel(Parcel out, int flags) {
        out.writeInt(nptr);
    }

    public static final Parcelable.Creator<transaction> CREATOR
        = new Parcelable.Creator<transaction>() {
        public transaction createFromParcel(Parcel in) {
            return new transaction(in);
        }

        public transaction[] newArray(int size) {
            return new transaction[size];
        }
    };

    private transaction(Parcel in) {
        nptr = in.readInt();
    }
    //} Parcelable interface

    //for jni to create objects
    private transaction(int i) {
        nptr = i;
    }

    //All constructors here should mimic those in the C++ class
    //TODO: public transaction(String name, float amount, long when)

    public transaction(String name, float amount) {
        new_transaction(name, amount);
    }

    public transaction() {
        new_transaction();
    }

    //TODO: how do we pass in the time...
    //public native void new_transaction(String name, float amount, long when)

    public native void new_transaction(String name, float amount);

    public native void new_transaction();

    public native String get_name();
    public native int get_id();
    public native float get_amount();
    //TODO: better way to pass around time...
    public native String get_time();
    public native String get_comment();

    //TODO: set_ functions for all public fields in the C++ class
    public native void set_name(String name);
    public native void set_amount(float amt);
}
