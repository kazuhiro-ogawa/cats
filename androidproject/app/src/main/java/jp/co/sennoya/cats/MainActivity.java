package jp.co.sennoya.cats;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnConfirmation = findViewById(R.id.btnConfirmation);
        btnConfirmation.setOnClickListener(view -> {
            Intent i = new Intent(this, ConfirmationActivity.class);
            startActivity(i);
        });

        Button btnSetting = findViewById(R.id.btnSetting);
        btnConfirmation.setOnClickListener(view -> {
            Intent i = new Intent(this, SettingActivity.class);
            startActivity(i);
        });
    }
}