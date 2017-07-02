//
// Created by gen on 03/03/2017.
//

#ifndef NEXTLAUNCHER_GIT_ANDROIDFONT_H
#define NEXTLAUNCHER_GIT_ANDROIDFONT_H

#include <core/Data.h>
#include <font/Font.h>
#include <jni.h>
#include "../../render_define.h"

namespace hirender {
    CLASS_BEGIN_N(AndroidFont, Font)

        string font_name;
        static jclass android_font_class;
        static jmethodID create_bitmap_method;
        static jmethodID destroy_bitmap_method;
        static jmethodID create_typeface_method;
        static jmethodID draw_text_method;

        static jclass android_rect_class;
        static jfieldID rect_left_field;
        static jfieldID rect_right_field;
        static jfieldID rect_top_field;
        static jfieldID rect_bottom_field;

        jobject bitmap;
        jobject typeface;

        static jclass getAndroidFontClass(JNIEnv *env);
        jobject getBitmap(JNIEnv *env);
        jobject getTypeface(JNIEnv *env);

    protected:
        virtual void calculateTextureSize(unsigned int &width,
                                          unsigned int &height);
        virtual void drawCharacter(unsigned int ch,
                                   const Vector2i &off,
                                   const Ref<Texture> &tex,
                                   int &width, int &height,
                                   Vector2i &corner);

    public:
        AndroidFont();
        AndroidFont(int size);
        AndroidFont(string name, int size);

        ~AndroidFont();

    CLASS_END
}


#endif //NEXTLAUNCHER_GIT_ANDROIDFONT_H
