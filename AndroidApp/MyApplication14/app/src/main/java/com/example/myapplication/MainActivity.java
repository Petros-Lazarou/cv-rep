package com.example.myapplication;

import android.content.res.Configuration;
import android.os.Bundle;
import android.view.View;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class MainActivity extends AppCompatActivity {
    public static boolean easter;
    private static int lastOrientation = Configuration.ORIENTATION_UNDEFINED;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate((Bundle) null);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        easter=false;
        View root = getWindow().getDecorView();
        int currentOrientation = getResources().getConfiguration().orientation;

        if (currentOrientation == Configuration.ORIENTATION_PORTRAIT &&
                lastOrientation == Configuration.ORIENTATION_LANDSCAPE) {

            getSupportFragmentManager()
                    .beginTransaction()
                    .replace(R.id.fragment_container, new MainFragment())
                    .commit();
             }



        if (savedInstanceState == null &&
                currentOrientation == Configuration.ORIENTATION_PORTRAIT) {

            getSupportFragmentManager()
                    .beginTransaction()
                    .replace(R.id.fragment_container, new MainFragment())
                    .commit();
        }

        lastOrientation = currentOrientation;

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }


}
