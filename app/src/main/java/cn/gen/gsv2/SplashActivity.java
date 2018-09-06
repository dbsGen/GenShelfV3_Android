package cn.gen.gsv2;

import android.animation.Animator;
import android.animation.ObjectAnimator;
import android.app.Activity;
import android.app.ActivityOptions;
import android.content.Intent;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.ActivityCompat;
import android.transition.Transition;
import android.transition.TransitionInflater;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.fichardu.interpolator.EaseInOutCubicInterpolator;
import com.fichardu.interpolator.EaseOutCubicInterpolator;
import com.gr.Request;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import app.dinus.com.loadingdrawable.render.LoadingDrawable;
import app.dinus.com.loadingdrawable.render.circle.rotate.MaterialLoadingRenderer;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.utils.ExceptionHandler;

public class SplashActivity extends com.gr.Activity {

    LinearLayout loadingView;
    ImageView launchImage;
    ImageView loadingImage;
    TextView loadingLabel;
    LoadingDrawable loadingDrawable;

    Handler handler = new Handler();

    public static final int LIB_VERSION = 16;
    static boolean loaded = false;

    public static boolean isLoaded() {
        return loaded;
    }

    public static void setLoaded(boolean loaded) {
        SplashActivity.loaded = loaded;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ExceptionHandler.setup(getFilesDir().toString() + "/exception.log");
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_splash);

        loadingView = (LinearLayout)findViewById(R.id.loading_view);
        loadingView.setAlpha(0);
        launchImage = (ImageView)findViewById(R.id.launch_image);
        loadingImage = (ImageView)findViewById(R.id.loading_image);
        loadingLabel = (TextView)findViewById(R.id.loading_label);

        loadingDrawable = new LoadingDrawable(new MaterialLoadingRenderer.Builder(this).setWidth(32).setHeight(32).setColors(new int[]{ActivityCompat.getColor(this, R.color.blue)}).build());
        loadingImage.setImageDrawable(loadingDrawable);


        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                String genPath = libPath(SplashActivity.this) + "libgsv2.so";
                if (loaded || new File(genPath).exists()) {
                    TranslateAnimation ani = new TranslateAnimation(0,0,0, H.dip2px(SplashActivity.this, -40));
                    ani.setInterpolator(new EaseInOutCubicInterpolator());
                    ani.setDuration(300);
                    ani.setFillAfter(true);
                    launchImage.startAnimation(ani);

                    ani.setAnimationListener(new Animation.AnimationListener() {
                        @Override
                        public void onAnimationStart(Animation animation) {

                        }

                        @Override
                        public void onAnimationEnd(Animation animation) {
                            goMainActivity();
                        }

                        @Override
                        public void onAnimationRepeat(Animation animation) {

                        }
                    });
                }else {
                    TranslateAnimation ani = new TranslateAnimation(0,0,0, H.dip2px(SplashActivity.this, -40));
                    ani.setInterpolator(new EaseInOutCubicInterpolator());
                    ani.setDuration(1400);
                    ani.setFillAfter(true);
                    launchImage.startAnimation(ani);

                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            ObjectAnimator ani = ObjectAnimator.ofFloat(loadingView, "alpha", 0, 1);
                            ani.setInterpolator(new EaseOutCubicInterpolator());
                            ani.setDuration(600);
                            ani.start();
                            loadingDrawable.start();
                        }
                    }, 800);
                    requestShelfLib();
                }
            }
        }, 50);
    }

    String findAbi() {
        String[] abis;
        if(Build.VERSION.SDK_INT>= Build.VERSION_CODES.LOLLIPOP)
        {
            abis = Build.SUPPORTED_ABIS;
        } else {
            abis = new String[]{Build.CPU_ABI,Build.CPU_ABI2};
        }

        if (isIn(abis, "arm64-v8a")) {
            return "arm64-v8a";
        }else if (isIn(abis, "x86_64")) {
            return "x86_64";
        }else if (isIn(abis, "armeabi-v7a")) {
            return "armeabi-v7a";
        }else if (isIn(abis, "x86")) {
            return "x86";
        }else if (isIn(abis, "armeabi")) {
            return "armeabi";
        }
        return null;
    }

    boolean isIn(String[] strings, String str) {
        for (String s :
                strings) {
            if (s.equals(str)) return true;
        }
        return false;
    }

    String shelfUrl() {
        String abi = findAbi();
        if (abi != null) {
            return "https://coding.net/u/dbsGen/p/gs_libs/git/raw/master/gv2_"+LIB_VERSION+"/"+abi +"/libgsv2.so.zip";
        }else {
            return null;
        }
    }

    public static String libPath(Activity activity) {
        return activity.getFilesDir().toString() + "/libs/" + LIB_VERSION + "/";
    }

    void requestShelfLib() {
        String url = shelfUrl();
        if (url != null) {
            loadingLabel.setText("Loading gen_shelf");
        }else {
            loadingLabel.setText("Unsupported system");
            loadingDrawable.stop();
            return;
        }
        Request request = Request.get(shelfUrl());
        request.setReadCache(true);
        request.setTimeout(30000);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, final float percent) {
                loadingLabel.setText(String.format("Loading gen_shelf %d%%", (int)(percent*100)));
            }

            @Override
            public void onComplete(final Request request) {
                loadingLabel.setText("Extra gen_shelf");
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            ZipFile zip = new ZipFile(request.getPath());
                            ZipEntry entry = zip.getEntry("libgsv2.so");
                            new File(libPath(SplashActivity.this)).mkdirs();
                            File file = new File(libPath(SplashActivity.this) + "libgsv2.so");
                            file.deleteOnExit();
                            InputStream is = zip.getInputStream(entry);
                            FileOutputStream os = new FileOutputStream(file);
                            int count = 0, bufferSize = 1024;
                            byte[] buffer = new byte[bufferSize];
                            while ((count = is.read(buffer, 0, bufferSize)) != -1)
                            {
                                os.write(buffer, 0, count);
                            }
                            os.write(entry.getExtra());
                            is.close();
                            os.close();
                            zip.close();
                            handler.post(new Runnable() {
                                @Override
                                public void run() {
                                    complete();
                                }
                            });
                        } catch (Exception e) {
                            e.printStackTrace();
                            handler.post(new Runnable() {
                                @Override
                                public void run() {
                                    loadingLabel.setText("Error");
                                }
                            });
                        }
                    }
                }).start();
            }

            @Override
            public void onFailed(Exception e) {
                loadingLabel.setText("Net work error.");
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }

    void complete(){
        loadingLabel.setText("OK");
        ObjectAnimator ani = ObjectAnimator.ofFloat(loadingView, "alpha", 1, 0);
        ani.setInterpolator(new EaseOutCubicInterpolator());
        ani.setDuration(600);
        ani.start();
        loadingDrawable.stop();
        ani.addListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {

            }

            @Override
            public void onAnimationEnd(Animator animation) {
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        goMainActivity();
                    }
                }, 100);
            }

            @Override
            public void onAnimationCancel(Animator animation) {

            }

            @Override
            public void onAnimationRepeat(Animator animation) {

            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        ExceptionHandler.post(this);
    }

    void goMainActivity() {
        try {
            Intent intent = new Intent(SplashActivity.this, MainActivity.class);
            startActivity(intent);
            SplashActivity.this.finish();
        }catch (Exception e) {
            e.printStackTrace();
        }
    }
}
