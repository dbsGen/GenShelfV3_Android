package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.gr.Request;
import com.gr.classes.Callback;
import com.gr.classes.NotificationCenter;
import com.nhaarman.listviewanimations.itemmanipulation.DynamicListView;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Shop;

/**
 * A simple {@link Fragment} subclass.
 */
public class ShopController extends Controller {

    Shop onlineShop;
    Shop localShop;

    cn.gen.gsv2.views.ImageView imageView;
    TextView titleView;
    TextView urlView;
    TextView descriptionView;
    Button hostButton;
    Button settingButton;
    Button installButton;

    Callback installedListener;
    Callback removedListener;
    Shop installShop;

    public void setOnlineShop(Shop onlineShop) {
        this.onlineShop = onlineShop;
    }

    public void setLocalShop(Shop localShop) {
        this.localShop = localShop;
    }

    public ShopController() {
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.shop));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_shop, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        imageView = (cn.gen.gsv2.views.ImageView) view.findViewById(R.id.image);
        titleView = (TextView)view.findViewById(R.id.title);
        urlView = (TextView)view.findViewById(R.id.url_label);
        hostButton = (Button)view.findViewById(R.id.host_button);
        settingButton = (Button)view.findViewById(R.id.setting_button);
        installButton = (Button)view.findViewById(R.id.install_button);
        descriptionView = (TextView)view.findViewById(R.id.description);

        Shop cs = null;
        if (onlineShop != null && localShop != null) {
            cs = onlineShop.getVersion() > localShop.getVersion() ? onlineShop : localShop;
        }else if (onlineShop != null) {
            cs = onlineShop;
        }else {
            cs = localShop;
        }
        final Shop shop = cs;

        hostButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(shop.getHost()));
                    startActivity(browserIntent);
                }catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        titleView.setText(shop.getName());
        urlView.setText(shop.getHost());
        descriptionView.setText(shop.getDescription().replace("<p>", "\n"));

        imageView.setUrl(shop.getIcon());
        checkState();

        installedListener = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Shop shop = (Shop) args[0];
                if (localShop != null) {
                    localShop.setVersion(shop.getVersion());
                }
                checkState();
                return null;
            }
        };
        removedListener = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Shop shop = (Shop) args[0];
                checkState();
                return null;
            }
        };
        NotificationCenter.getInstance().listen("SHOP_INSTALLED", installedListener);
        NotificationCenter.getInstance().listen("SHOP_REMOVED", removedListener);

        installButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (installShop.isLocalize()) {
                    installShop.remove();
                }else {
                    Toast.makeText(getContext(), getString(R.string.start_install),
                            Toast.LENGTH_SHORT).show();
                    installShop.install();
                }
            }
        });
        settingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Shop s = shop;
                if (!s.isLocalize()) {
                    s = localShop;
                }
                if (s != null && s.isLocalize()) {
                    SettingsController ctrl = Controller.instantiate(getContext(), SettingsController.class);
                    ctrl.setTitle(s.getName());
                    ctrl.setSettings(s.getSettings());
                    ctrl.setShop(s);
                    ctrl.showRightItems(getContext());
                    H.navC(ShopController.this).push(ctrl, true);
                }
            }
        });
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        NotificationCenter.getInstance().remove("SHOP_INSTALLED", installedListener);
        NotificationCenter.getInstance().remove("SHOP_REMOVED", removedListener);
    }

    void checkState() {
        int status;
        if (onlineShop != null && localShop != null) {
            if (onlineShop.getVersion() > localShop.getVersion()) {
                installShop = onlineShop;
                status = 2;
            }else {
                installShop = localShop.isLocalize() ? localShop : onlineShop;
                status = installShop.isLocalize() ? 1 : 0;
            }
        }else if (onlineShop != null) {
            installShop = onlineShop;
            status = installShop.isLocalize() ? 1 : 0;
        }else {
            installShop = localShop;
            status = installShop.isLocalize() ? 1 : 0;
        }
        if (status == 1) {
            installButton.setText(getString(R.string.uninstall));
            settingButton.setEnabled(true);
            settingButton.setTextColor(ContextCompat.getColor(getContext(), R.color.blue));
        }else if (status == 0) {
            installButton.setText(getString(R.string.install));
            settingButton.setEnabled(false);
            settingButton.setTextColor(ContextCompat.getColor(getContext(), R.color.gray));
        }else if (status == 2) {
            installButton.setText(getString(R.string.update));
            settingButton.setEnabled(true);
            settingButton.setTextColor(ContextCompat.getColor(getContext(), R.color.blue));
        }
    }
}
