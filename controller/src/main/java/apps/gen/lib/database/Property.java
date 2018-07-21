package apps.gen.lib.database;

/**
 * Created by gen on 16/5/11.
 */
public @interface Property {
    String value() default "";
    int version() default 0;
    boolean index() default false;
    String limit() default "";
    String type() default "";
}
