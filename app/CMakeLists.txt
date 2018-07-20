# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
include_directories("." include src/main/cpp/grender src/main/cpp/grender/thirdparties)
include_directories(src/main/cpp/mruby/include src/main/cpp/mruby/mrbgems/mruby-http/include)
include_directories(src/main/cpp/onigmo src/main/cpp/gumbo src/main/cpp/sqlite3)
include_directories(src/main/cpp)

link_directories("src/main/jniLibs/${ANDROID_ABI}")
link_directories("libs/${ANDROID_ABI}")

add_definitions(-DDEBUG -DUSING_SCRIPT -DHAS_RUBY)
add_definitions(-DLIBXML_THREAD_ENABLED -DHAVE_ONIGMO_H)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

file(GLOB_RECURSE SOURCES src/main/cpp/program/*.cpp src/main/cpp/program/*.c)
add_library( # Sets the name of the library.
             gsv2

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SOURCES} )

file(GLOB_RECURSE RENDERER_SOURCES src/main/cpp/grender/*.cpp src/main/cpp/grender/*.c)
add_library( # Sets the name of the library.
             grender

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${RENDERER_SOURCES} )

file(GLOB_RECURSE MRUBY_SOURCES src/main/cpp/mruby/*.cpp src/main/cpp/mruby/*.c)
add_library( # Sets the name of the library.
             mruby

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${MRUBY_SOURCES} )

file(GLOB_RECURSE ICONV_SOURCES src/main/cpp/iconv/*.cpp src/main/cpp/iconv/*.c)
add_library( # Sets the name of the library.
             iconv

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${ICONV_SOURCES} )

file(GLOB_RECURSE DUKTAPE_SOURCES src/main/cpp/duktape/*.cpp src/main/cpp/duktape/*.c)
add_library( # Sets the name of the library.
             duktape

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${DUKTAPE_SOURCES} )

file(GLOB_RECURSE XML_SOURCES src/main/cpp/libxml2/*.cpp src/main/cpp/libxml2/*.c)
add_library( # Sets the name of the library.
             xml2

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${XML_SOURCES} )

file(GLOB_RECURSE ONIGMO_SOURCES src/main/cpp/onigmo/*.cpp src/main/cpp/onigmo/*.c)
add_library( # Sets the name of the library.
             onigmo

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${ONIGMO_SOURCES} )

file(GLOB_RECURSE GUMBO_SOURCES src/main/cpp/gumbo/*.cpp src/main/cpp/gumbo/*.c)
add_library( # Sets the name of the library.
             gumbo

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${GUMBO_SOURCES} )

file(GLOB_RECURSE GUMBO_QUERY_SOURCES src/main/cpp/gumbo-query/*.cpp src/main/cpp/gumbo-query/*.c)
add_library( # Sets the name of the library.
             gumbo-query

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${GUMBO_QUERY_SOURCES} )

file(GLOB_RECURSE SQLITE3_SOURCES src/main/cpp/sqlite3/*.cpp src/main/cpp/sqlite3/*.c)
add_library( # Sets the name of the library.
             sqlite3

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             ${SQLITE3_SOURCES} )

target_compile_definitions(sqlite3 PRIVATE _HAVE_SQLITE_CONFIG_H SQLITE_HAVE_ZLIB=1)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries( # Specifies the target library.
                       gsv2

                       # Links the target library to the log library
                       # included in the NDK.

                       grender
                       mruby
                       xml2
                       iconv
                       duktape
                       onigmo
                       gumbo-query
                       gumbo
                       sqlite3

                       GLESv2
                       android
                       jnigraphics
                       z

                       ${log-lib})