package com.example.syahrulfadholi.simple_iot_project;

import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.google.firebase.FirebaseApp;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    DatabaseReference Dref;
    TextView mTempView, mHumidView, mTempValue, mHumidValue;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Dref = FirebaseDatabase.getInstance().getReference();
        mTempView = (TextView) findViewById(R.id.temp);
        mHumidView = (TextView) findViewById(R.id.humid);
        mTempValue = (TextView) findViewById(R.id.temp_value);
        mHumidValue = (TextView) findViewById(R.id.humid_value);

        Dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                mTempValue.setText(dataSnapshot.child("Temperature").getValue().toString());
                mHumidValue.setText(dataSnapshot.child("Humidity").getValue().toString());
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
                Log.w("file","Failed to read value", databaseError.toException());
            }
        });
    }
}
