package apps.gen.lib;

import android.os.Bundle;
import android.os.PersistableBundle;
import android.support.v7.app.AppCompatActivity;
import android.view.KeyEvent;

/**
 * Created by gen on 16/5/8.
 */
public class Activity extends AppCompatActivity {
    static Activity currentActivity;
    @Override
    public void onCreate(Bundle savedInstanceState, PersistableBundle persistentState) {
        super.onCreate(savedInstanceState, persistentState);
        currentActivity = this;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        currentActivity = this;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (currentActivity  == this) {
            currentActivity = null;
        }
    }
    public static Activity current() {return currentActivity;}

}
