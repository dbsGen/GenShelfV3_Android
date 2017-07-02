package com.hiar.render;

import java.lang.annotation.Inherited;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * Created by gen on 16/9/6.
 */
@Inherited
@Retention(RetentionPolicy.RUNTIME)
public @interface NativeClass {
    String value();
}
