package cn.gen.gsv2.controllers;


import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.CookieManager;
import android.webkit.WebResourceRequest;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;

/**
 * A simple {@link Controller} subclass.
 */
public class WebViewController extends Controller {

    public interface OnCompleteListener {
        void onComplete(WebViewController webViewController, String cookies);
    }
    WebView webView;
    OnCompleteListener onComplete;
    String url;

    public WebViewController() {
    }

    public void setOnComplete(OnCompleteListener onComplete) {
        this.onComplete = onComplete;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.done), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = webView.getUrl();
                String cookies = CookieManager.getInstance().getCookie(url);
                Log.i("cookies", cookies);
                if (onComplete != null)
                    onComplete.onComplete(WebViewController.this, cookies);
                H.navC(WebViewController.this).pop(true);
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_web_view, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        webView = (WebView)view.findViewById(R.id.web_view);
        webView.loadUrl(url);
    }
}
