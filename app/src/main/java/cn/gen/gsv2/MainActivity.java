package cn.gen.gsv2;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;
import android.transition.Transition;
import android.transition.TransitionInflater;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.animation.AlphaAnimation;
import android.widget.ImageView;
import android.widget.Toast;

import com.gr.Activity;
import com.gr.Helper;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.gr.classes.Map;
import com.gr.classes.NotificationCenter;

import junit.framework.Assert;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.annotation.Annotation;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.controllers.NavigationController;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.controllers.HistoryController;
import cn.gen.gsv2.controllers.LibraryController;
import cn.gen.gsv2.controllers.LikesController;
import cn.gen.gsv2.controllers.ShelfController;
import cn.gen.gsv2.controllers.ShopsController;
import cn.gen.gsv2.controllers.SocialController;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.HTTPClient;
import cn.gen.gsv2.models.History;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.models.Page;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.utils.Analysis;
import cn.gen.gsv2.utils.ExceptionHandler;
import cn.nekocode.badge.BadgeDrawable;

import static android.Manifest.permission.READ_CONTACTS;
import static android.Manifest.permission.READ_EXTERNAL_STORAGE;
import static android.Manifest.permission.WRITE_EXTERNAL_STORAGE;
import static android.support.v7.graphics.drawable.DrawerArrowDrawable.ARROW_DIRECTION_LEFT;
import static android.view.View.GONE;
import static java.security.AccessController.getContext;

public class MainActivity extends Activity
        implements NavigationView.OnNavigationItemSelectedListener, View.OnClickListener {

    private native void init(String rpath, String spath);
    private native void update();

    NavigationController navigationController;
    DrawerArrowDrawable arrowDrawable;
    DrawerLayout drawerLayout;
    LibraryController libraryController;
    ShelfController shelfController;
    ShopsController shopsController;
    SocialController socialController;
    HistoryController historyController;
    NavigationView navigationView;
    ImageView badgeView;

    Callback toastCallback;

    public String getVersion() {
        try {
            PackageManager manager = this.getPackageManager();
            PackageInfo info = manager.getPackageInfo(this.getPackageName(), 0);
            String version = info.versionName;
            return version;
        } catch (Exception e) {
            e.printStackTrace();
            return "0.0";
        }
    }

    public LibraryController getLibraryController() {
        if (libraryController == null) {
            libraryController = Controller.instantiate(this, LibraryController.class);

            Controller.NavigationItem item = new Controller.NavigationItem(arrowDrawable, this);
            libraryController.setLeftItems(item);
        }
        return libraryController;
    }

    public HistoryController getHistoryController() {
        if (historyController == null) {
            historyController = Controller.instantiate(this, HistoryController.class);

            Controller.NavigationItem item = new Controller.NavigationItem(arrowDrawable, this);
            historyController.setLeftItems(item);
        }
        return historyController;
    }

    public DrawerLayout getDrawerLayout() {
        return drawerLayout;
    }

    public ShelfController getShelfController() {
        if (shelfController == null) {
            shelfController = Controller.instantiate(this, ShelfController.class);

            Controller.NavigationItem item = new Controller.NavigationItem(arrowDrawable, this);
            shelfController.setLeftItems(item);
        }
        return shelfController;
    }

    public ShopsController getShopsController() {
        if (shopsController == null) {
            shopsController = Controller.instantiate(this, ShopsController.class);

            Controller.NavigationItem item = new Controller.NavigationItem(arrowDrawable, this);
            shopsController.setLeftItems(item);
        }
        return shopsController;
    }

    public SocialController getSocialController() {
        if (socialController == null) {
            socialController = Controller.instantiate(this, SocialController.class);
            Controller.NavigationItem item = new Controller.NavigationItem(arrowDrawable, this);
            socialController.setLeftItems(item);
        }
        return socialController;
    }

    boolean greaterVersion(String v1, String v2) {
        String[] vs1 = v1.split("\\."), vs2 = v2.split("\\.");
        for (int i = 0, t = vs1.length; i < t; ++i) {
            int vi1 = Integer.parseInt(vs1[i]);
            int vi2 = 0;
            if (vs2.length > i) {
                vi2 = Integer.parseInt(vs2[i]);
            }
            if (vi1 > vi2) {
                return true;
            }else if (vi1 < vi2) {
                return false;
            }
        }
        return false;
    }

    private void copyAssetsPath(String path, String root) {
        try {
            AssetManager as = getAssets();
            String[] list = as.list(path);
            if (list.length > 0) {
                File dir = new File(root + '/' + path);
                if (!dir.exists()) {
                    dir.mkdir();
                }
                for (int i = 0, t = list.length; i < t; ++i) {
                    copyAssetsPath(path + '/' + list[i], root);
                }
            }else {
                InputStream in = as.open(path);
                FileOutputStream out = new FileOutputStream(root + '/' + path);

                byte[] buffer = new byte[1024];
                int read;
                while ((read = in.read(buffer)) != -1) {
                    out.write(buffer, 0, read);
                }
                in.close();
                out.flush();
                out.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    apps.gen.lib.utils.NotificationCenter.Runnable runnable;
    Handler handler = new Handler();

    Runnable fixedCallback;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(null);

        if (!SplashActivity.isLoaded()) {
            String genPath = SplashActivity.libPath(this) + "libgsv2.so";
//            System.load(genPath);
            System.loadLibrary("gsv2");
            SplashActivity.setLoaded(true);

            Helper.registerClass(Chapter.class);

            Array.register();
            Map.register();
            Page.register();
            HTTPClient.register();
        }
        LikesController.likeStatus = -1;

        String resourcePath = getFilesDir().toString() + "/resources";
        File file = new File(resourcePath);
        if (!file.exists()) file.mkdir();

        copyAssetsPath("resources", getFilesDir().toString());

        String storagePath = getFilesDir().toString() + "/storage";
        file = new File(storagePath);
        if (!file.exists()) file.mkdir();

        init(resourcePath, storagePath);
        arrowDrawable = new DrawerArrowDrawable(this);
        arrowDrawable.setColor(Color.WHITE);
        arrowDrawable.setDirection(ARROW_DIRECTION_LEFT);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawerLayout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawerLayout.setDrawerListener(toggle);
        toggle.syncState();

        navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        badgeView = new ImageView(this);
        badgeView.setVisibility(GONE);
        navigationView.getMenu().getItem(2).setActionView(badgeView);

        navigationController = (NavigationController)getSupportFragmentManager().findFragmentById(R.id.navigation_controller);
        // navigationController.setNavBarHidden(true);
        navigationController.getNavigationBar().setBackgroundResource(R.color.blue);

        Array books = Book.localBooks();
        if (books.size() != 0) {
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    navigationView.setCheckedItem(R.id.shelf);
                }
            }, 1);
            navigationController.push(getShelfController(), false);
        }else {
            Array shops = Shop.getLocalShops();
            if (shops.size() == 0) {
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        navigationView.setCheckedItem(R.id.settins);
                    }
                }, 1);
                navigationController.push(getShopsController(), false);
            }else {
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        navigationView.setCheckedItem(R.id.library);
                    }
                }, 1);
                navigationController.push(getLibraryController(), false);
            }
        }

        runnable = new apps.gen.lib.utils.NotificationCenter.Runnable() {
            @Override
            public void run(apps.gen.lib.utils.NotificationCenter.Notification notification) {
                int count = (int)notification.getPostObject();
                if (count == 0) {
                    badgeView.setVisibility(GONE);
                }else {
                    badgeView.setVisibility(View.VISIBLE);
                    badgeView.setImageDrawable(new BadgeDrawable.Builder()
                            .type(BadgeDrawable.TYPE_NUMBER)
                            .number(count)
                            .build());
                }
            }
        };
        H.NC().addListener(ShopsController.NOTIFICATION_UPDATE_BADGE, runnable);

        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                getShopsController().startRequest();
            }
        }, 0);

        fixedCallback = new Runnable() {
            @Override
            public void run() {
                update();
                handler.postDelayed(fixedCallback, 500);
            }
        };
        fixedCallback.run();

        int REQUEST_READ_STORAGE = 0x99002;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED ||
                    checkSelfPermission(WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{
                        READ_EXTERNAL_STORAGE,
                        WRITE_EXTERNAL_STORAGE
                }, REQUEST_READ_STORAGE);
            }
        }

        toastCallback = new Callback(true) {
            @Override
            public Object run(Object... args) {
                String msg = (String) args[0];
                Toast.makeText(MainActivity.this, msg, Toast.LENGTH_LONG).show();
                return null;
            }
        };
        NotificationCenter.getInstance().listen("SHOW_MSG", toastCallback);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        H.NC().removeListener(ShopsController.NOTIFICATION_UPDATE_BADGE, runnable);
        handler.removeCallbacks(fixedCallback);
        NotificationCenter.getInstance().remove("SHOW_MSG", toastCallback);
    }

    static boolean first = true;
    @Override
    protected void onResume() {
        super.onResume();

        if (!first) return;
        first = false;

        Request.setup();

        Analysis.run(this);
        Request versionCheck = Request.get("https://coding.net/u/dbsGen/p/GenShelf_Versions/git/raw/master/index.json");
        versionCheck.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                File file = new File(request.getPath());
                try {

                    InputStream inputStream = new FileInputStream(file);
                    InputStreamReader inputReader = new InputStreamReader(inputStream);
                    BufferedReader bufferReader = new BufferedReader(inputReader);

                    // 读取一行
                    String line = null;
                    StringBuffer strBuffer = new StringBuffer();

                    while ((line = bufferReader.readLine()) != null)
                    {
                        strBuffer.append(line);
                    }

                    JSONObject jObject = new JSONObject(strBuffer.toString());
                    JSONObject a = (JSONObject)jObject.get("android");
                    String v = (String)a.get("version");
                    if (greaterVersion(v, getVersion())) {

                        final String url = (String)a.get("url");
                        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                        builder.setTitle(getString(R.string.will_upgrade));
                        builder.setMessage(((String)a.get("des")).replace("<p>", "\n"));
                        builder.setPositiveButton(getString(R.string.yes), new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                Intent downloadIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
                                startActivity(downloadIntent);

                                dialog.dismiss();
                            }
                        });
                        builder.setNegativeButton(getString(R.string.no), new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                            }
                        });
                        builder.create().show();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(Exception e) {

            }

            @Override
            public void onCancel(Request request) {

            }
        });
        versionCheck.start();

        Array<Book> books = new Array<>(true);
        Array<Chapter> chapters = new Array<>(true);
        Chapter.downloadingChapters(books, chapters);
        ConnectivityManager conMan = null;
        try {
            conMan = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo.State mobile = conMan.getNetworkInfo(0).getState();
            NetworkInfo.State wifi = conMan.getNetworkInfo(1).getState();
            if (wifi != NetworkInfo.State.CONNECTED && wifi != NetworkInfo.State.CONNECTING) {
                for (Chapter cha : chapters) {
                    cha.stopDownload();
                }
            }
        }catch (Exception e) {
            e.printStackTrace();
        }

        getSocialController().reload();
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            if (!navigationController.onBackPressed())
                super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();
        if (item.isChecked()) {
            return false;
        }

        if (id == R.id.shelf) {
            Controller ctrl = null;
            if (LikesController.likeStatus == -1) {
                if (Book.likedBooks().size() != 0 && Book.localBooks().size() == 0) {
                    LikesController.likeStatus = 1;
                    ctrl = getShelfController().getLikesController(this);
                }else {
                    LikesController.likeStatus = 0;
                    ctrl = getShelfController();
                }
            }else if (LikesController.likeStatus == 0) {
                ctrl = getShelfController();
            }else {
                ctrl = getShelfController().getLikesController(this);
            }
            navigationController.setControllers(new Controller[]{ctrl}, true);
        } else if (id == R.id.library) {
            navigationController.setControllers(new Controller[]{getLibraryController()}, true);
        } else if (id == R.id.settins) {
            navigationController.setControllers(new Controller[]{getShopsController()}, true);
        }else if (id == R.id.social) {
            navigationController.setControllers(new Controller[]{getSocialController()}, true);
        }else if (id == R.id.history) {
            navigationController.setControllers(new Controller[]{getHistoryController()}, true);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    @Override
    public void onClick(View v) {
        if (!drawerLayout.isDrawerOpen(GravityCompat.START)) {
            drawerLayout.openDrawer(GravityCompat.START);
        }
    }

    public void setNavItem(int res) {
        MenuItem item = navigationView.getMenu().findItem(res);
        if (!item.isChecked()) {
            switch (res) {
                case R.id.shelf: {
                    Controller ctrl = null;
                    if (LikesController.likeStatus == -1) {
                        if (Book.likedBooks().size() != 0 && Book.localBooks().size() == 0) {
                            LikesController.likeStatus = 1;
                            ctrl = getShelfController().getLikesController(this);
                        }else {
                            LikesController.likeStatus = 0;
                            ctrl = getShelfController();
                        }
                    }else if (LikesController.likeStatus == 0) {
                        ctrl = getShelfController();
                    }else {
                        ctrl = getShelfController().getLikesController(this);
                    }
                    navigationController.setControllers(new Controller[]{ctrl}, true);
                    break;
                }
                case R.id.library: {
                    navigationController.setControllers(new Controller[]{getLibraryController()}, true);
                    break;
                }
                case R.id.settins: {
                    navigationController.setControllers(new Controller[]{getShopsController()}, true);
                    break;
                }
            }
            navigationView.setCheckedItem(res);
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return navigationController.onKeyDown(keyCode, event) || super.onKeyDown(keyCode, event);
    }
}
