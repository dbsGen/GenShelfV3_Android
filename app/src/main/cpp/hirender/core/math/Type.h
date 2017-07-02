//
// Created by gen on 16/5/30.
//

#ifndef HIRENDER_VECTOR_H
#define HIRENDER_VECTOR_H

#include <math.h>
#include "core/Object.h"
#include <core/core_define.h>

namespace hicore {
#define VECTOR_DEF(T, S, current_type) \
BASE_FINAL_CLASS_DEFINE \
public: \
T v[S]; \
_FORCE_INLINE_ T e(int idx) { \
    if (idx > S) { \
        return 0; \
    } \
    return v[idx]; \
} \
_FORCE_INLINE_ T length() const { \
    T t = 0; \
    for (int i = 0; i < S; ++i) { \
        t += v[i] * v[i]; \
    } \
    return (T)sqrtf(t); \
} \
_FORCE_INLINE_ bool operator==(const current_type &other) const { \
    for (int i = 0; i < S; ++i) { \
        if (v[i] != other.v[i]) { \
            return false; \
        } \
    } \
    return true; \
} \
_FORCE_INLINE_ bool operator!=(const current_type &other) const { \
    return !operator==(other); \
} \
_FORCE_INLINE_ current_type &operator+=(const current_type &other) { \
    for (int i = 0; i < S; ++i) { \
        v[i] += other.v[i]; \
    } \
    return *(current_type*)this; \
} \
_FORCE_INLINE_ current_type &operator*=(float scale) { \
    for (int i = 0; i < S; ++i) { \
        v[i] *= scale; \
    } \
    return *(current_type*)this; \
} \
_FORCE_INLINE_ current_type scale(float scale) const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = v[i] * scale; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type &operator-=(const current_type &other) { \
    for (int i = 0; i < S; ++i) { \
        v[i] -= other.v[i]; \
    } \
    return *(current_type*)this; \
} \
_FORCE_INLINE_ current_type operator+(const current_type &other) const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = v[i] + other.v[i]; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type operator-() const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = -v[i]; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type operator*(const current_type &other) const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = v[i] * other.v[i]; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type operator*(float scale) const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = v[i] * scale; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type operator-(const current_type &other) const { \
    current_type n; \
    for (int i = 0; i < S; ++i) { \
        n.v[i] = v[i] - other.v[i]; \
    } \
    return n; \
} \
_FORCE_INLINE_ current_type &operator=(const current_type &other) { \
    for (int i = 0; i < S; ++i) { \
        v[i] = other.v[i]; \
    } \
    return *this; \
} \
_FORCE_INLINE_ T &operator[](int idx) { \
    return v[idx]; \
} \
_FORCE_INLINE_ const T &operator[](int idx) const {\
    return v[idx];\
}\
_FORCE_INLINE_ current_type normalize() const { \
    if (length() == 0) { \
        return current_type(); \
    } \
    float scale = 1.0f/length(); \
    current_type ret; \
    for (int i = 0; i < S; ++i) { \
        ret.v[i] = v[i] * scale; \
    } \
    return ret; \
} \
_FORCE_INLINE_ T dot(const current_type &other) const { \
    T ret = 0; \
    for (int i = 0; i < S; ++i) { \
        ret += v[i] * other.v[i]; \
    } \
    return ret; \
} \
_FORCE_INLINE_ void set(const T *vs) { \
    for (int i = 0; i < S; ++i) { \
        v[i] = vs[i]; \
    } \
} \
_FORCE_INLINE_ void setZero() { \
    for (int i = 0; i < S; ++i) { \
        v[i] = 0; \
    } \
} \
_FORCE_INLINE_ current_type() { \
    for (int i = 0; i < S; ++i) { \
        v[i] = 0; \
    } \
} \
_FORCE_INLINE_ current_type(const T *src) { \
    for (int i = 0; i < S; ++i) { \
        v[i] = src[i]; \
    } \
} \
protected: \
_FORCE_INLINE_ void _copy(const HObject *other) { \
    operator=(*(current_type*)other); \
} \
private:
    
    class Vector2i {
        VECTOR_DEF(int, 2, Vector2i);
    public:
        _FORCE_INLINE_ Vector2i(int x, int y) {
            v[0] = x;
            v[1] = y;
        }
        _FORCE_INLINE_ Vector2i(int x) : Vector2i(x, x) {}
        _FORCE_INLINE_ int x() const {return v[0];}
        _FORCE_INLINE_ int y() const {return v[1];}
        _FORCE_INLINE_ void x(int x) {v[0] = x;}
        _FORCE_INLINE_ void y(int y) {v[1] = y;}
        
        _FORCE_INLINE_ int loc() const {return v[0];}
        _FORCE_INLINE_ int len() const {return v[1];}
        _FORCE_INLINE_ int end() const {return v[0] + v[1] - 1;}
        
        _FORCE_INLINE_ void loc(int loc) {v[0] = loc;}
        _FORCE_INLINE_ void len(int len) {v[1] = len;}
        SUPPORT_VARIANT(Vector2i);
    };
    class Vector3i{
        VECTOR_DEF(int, 3, Vector3i);
    public:
        INITIALIZE(Vector3i, PARAMS(int x, int y, int z),
                   v[0] = x;
                   v[1] = y;
                   v[2] = z;
                   )
        _FORCE_INLINE_ int x() const {return v[0];}
        _FORCE_INLINE_ int y() const {return v[1];}
        _FORCE_INLINE_ int z() const {return v[2];}
        
        _FORCE_INLINE_ void x(int x) { v[0] = x;}
        _FORCE_INLINE_ void y(int y) { v[1] = y;}
        _FORCE_INLINE_ void z(int z) { v[2] = z;}
        SUPPORT_VARIANT(Vector3i);
    };
    class Vector4i {
        VECTOR_DEF(int, 4, Vector4i);
    public:
        INITIALIZE(Vector4i, PARAMS(int x, int y, int z, int w),
                   v[0] = x;
                   v[1] = y;
                   v[2] = z;
                   v[3] = w;
                   )
        _FORCE_INLINE_ int x() const {return v[0];}
        _FORCE_INLINE_ int y() const {return v[1];}
        _FORCE_INLINE_ int z() const {return v[2];}
        _FORCE_INLINE_ int w() const {return v[3];}
        
        _FORCE_INLINE_ void x(int x) { v[0] = x;}
        _FORCE_INLINE_ void y(int y) { v[1] = y;}
        _FORCE_INLINE_ void z(int z) { v[2] = z;}
        _FORCE_INLINE_ void w(int w) { v[3] = w;}
        SUPPORT_VARIANT(Vector4i);
    };
    class Vector2f {
        VECTOR_DEF(float, 2, Vector2f);
        static Vector2f _zero;
    public:
        INITIALIZE(Vector2f, PARAMS(float x, float y),
                   v[0] = x;
                   v[1] = y;
                   )
        _FORCE_INLINE_ float x() const {return v[0];}
        _FORCE_INLINE_ float y() const {return v[1];}
        
        _FORCE_INLINE_ float width() const {return v[0];}
        _FORCE_INLINE_ float height() const {return v[1];}
        
        _FORCE_INLINE_ void x(float x) { v[0] = x;}
        _FORCE_INLINE_ void y(float y) { v[1] = y;}
        
        _FORCE_INLINE_ static const Vector2f &zero() {
            return _zero;
        }
        
        SUPPORT_VARIANT(Vector2f);
    };
    
    class Matrix4;
    class Vector4f;
    class Vector3f {
        VECTOR_DEF(float, 3, Vector3f);
    public:
        INITIALIZE(Vector3f, PARAMS(float x, float y, float z),
                   v[0] = x;
                   v[1] = y;
                   v[2] = z;
                   )
        _FORCE_INLINE_ float x() const {return v[0];}
        _FORCE_INLINE_ float y() const {return v[1];}
        _FORCE_INLINE_ float z() const {return v[2];}
        
        _FORCE_INLINE_ void x(float x) { v[0] = x;}
        _FORCE_INLINE_ void y(float y) { v[1] = y;}
        _FORCE_INLINE_ void z(float z) { v[2] = z;}
        _FORCE_INLINE_ Vector3f cross(const Vector3f &other) const {
            return Vector3f(v[1] * other.v[2] - v[2] * other.v[1],
                            v[2] * other.v[0] - v[0] * other.v[2],
                            v[0] * other.v[1] - v[1] * other.v[0]);
        }
        Vector3f &operator*=(const Matrix4 &other);
        Vector3f operator*(const Matrix4 &other) const;
        Vector3f operator*(const Vector4f &q) const;
        int largestAbsComponent() const;
        Vector3f ortho() const;
        
        _FORCE_INLINE_ static const Vector3f &one() {
            static Vector3f _one(1,1,1);
            return _one;
        }
        
        SUPPORT_VARIANT(Vector3f);
    };
    class Vector4f {
        VECTOR_DEF(float, 4, Vector4f);
    public:
        INITIALIZE(Vector4f, PARAMS(float x, float y, float z, float w),
                   v[0] = x;
                   v[1] = y;
                   v[2] = z;
                   v[3] = w;
                   )
        Vector4f(long color) {
            v[0] = ((color >> 24) & 0xff)/(float)0xff;
            v[1] = ((color >> 16) & 0xff)/(float)0xff;
            v[2] = ((color >> 8) & 0xff)/(float)0xff;
            v[3] = (color & 0xff)/(float)0xff;
        }
        
        _FORCE_INLINE_ float x() const {return v[0];}
        _FORCE_INLINE_ float y() const {return v[1];}
        _FORCE_INLINE_ float z() const {return v[2];}
        _FORCE_INLINE_ float w() const {return v[3];}
        
        _FORCE_INLINE_ float left() const {return v[0];}
        _FORCE_INLINE_ float top() const {return v[1];}
        _FORCE_INLINE_ float width() const {return v[2];}
        _FORCE_INLINE_ float height() const {return v[3];}
        
        _FORCE_INLINE_ float red() const {return v[0];}
        _FORCE_INLINE_ float green() const {return v[1];}
        _FORCE_INLINE_ float blue() const {return v[2];}
        _FORCE_INLINE_ float alpha() const {return v[3];}
        
        _FORCE_INLINE_ void x(float x) { v[0] = x;}
        _FORCE_INLINE_ void y(float y) { v[1] = y;}
        _FORCE_INLINE_ void z(float z) { v[2] = z;}
        _FORCE_INLINE_ void w(float w) { v[3] = w;}
        
        Vector4f &operator*=(const Matrix4 &other);
        Vector4f operator*(const Matrix4 &other) const;
        
        _FORCE_INLINE_ bool contain(const Vector2f &point) const {
            return point.x()>=left() && point.x()<(left()+width()) && point.y() >= top() && point.y() < (top() + height());
        }
        static Vector4f fromEuler(const Vector3f &euler);
        static const Vector4f &identity();
        Vector3f euler() const;
        
        SUPPORT_VARIANT(Vector4f);
        
    };
    class Matrix2 {
        BASE_FINAL_CLASS_DEFINE
    public:
        union {
            struct {
                float m00, m01;
                float m10, m11;
            };
            float m2[2][2];
            float m[4];
        };
        _FORCE_INLINE_ Matrix2(){}
        INITIALIZE(Matrix2, float *m,
                   memcpy(&this->m, m, sizeof(this->m));
                   )
        _FORCE_INLINE_ Matrix2& operator=(const Matrix2 &other) {
            memcpy(&m, &other.m, sizeof(m));
            return *this;
        }
        SUPPORT_VARIANT(Matrix2);
    };
    class Matrix3 {
        BASE_FINAL_CLASS_DEFINE
    public:
        union {
            struct
            {
                float m00, m01, m02;
                float m10, m11, m12;
                float m20, m21, m22;
            };
            float m[9];
        };
        _FORCE_INLINE_ Matrix3(){
            memset(&m, 0, sizeof(m));
        }
        INITIALIZE(Matrix3, float *m,
                   memcpy(&this->m, m, sizeof(this->m));
                   )
        _FORCE_INLINE_ void setIdentity() {
            m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0;
            m[0] = m[4] = m[8] = 1;
        }
        _FORCE_INLINE_ void setZero() {
            memset(&m, 0, sizeof(m));
        }
        _FORCE_INLINE_ void setSameDiagonal(float d) {
            m[0] = m[4] = m[8] = d;
        }
        _FORCE_INLINE_ float &operator[](int idx) {
            return m[idx];
        }
        _FORCE_INLINE_ const float &operator[](int idx) const {
            return m[idx];
        }
        Matrix3 operator*(const Matrix3 &other) const;
        Vector3f operator*(const Vector3f &other) const;
        Matrix3 &operator*=(float s);
        Matrix3 operator+(const Matrix3 &other);
        Matrix3 &operator+=(const Matrix3 &other);
        Matrix3 &operator-=(const Matrix3 &other);
        void setColumn(int col, const Vector3f &v);
        void getColumn(int col, Vector3f &v);
        Matrix3 transpose();
        float determinant();
        static Matrix3 fromEuler(const Vector3f &euler);
        Vector4f rotation() const;

        Matrix3 invert();
        static Matrix3 identity();
        _FORCE_INLINE_ Matrix3& operator=(const Matrix3 &other) {
            memcpy(&m, &other.m, sizeof(m));
            return *this;
        }
        SUPPORT_VARIANT(Matrix3);
    };
    class Matrix4 {
        BASE_FINAL_CLASS_DEFINE
    public:
        union {
            struct
            {
                float m00, m10, m20, m30;
                float m01, m11, m21, m31;
                float m02, m12, m22, m32;
                float m03, m13, m23, m33;
            };
            float m44[4][4];
            float m[16];
        };
        _FORCE_INLINE_ Matrix4(){
            memset(&m, 0, sizeof(m));
        }
        INITIALIZE(Matrix4,
                   const float *m,
                   memcpy(&this->m, m, sizeof(this->m));
                   )
        INITIALIZE(Matrix4,
                   const Matrix4 &mat,
                   memcpy(&m, &mat.m, sizeof(m));
                   )
        INITIALIZE(Matrix4,
                   PARAMS(float radians, const Vector3f &axis),
                   Vector3f v = axis.normalize();
                   float cos = cosf(radians);
                   float cosp = 1.0f - cos;
                   float sin = sinf(radians);
                   m[0] = cos + cosp * v.v[0] * v.v[0];
                   m[1] = cosp * v.v[0] * v.v[1] + v.v[2] * sin;
                   m[2] = cosp * v.v[0] * v.v[2] - v.v[1] * sin;
                   m[3] = 0.0f;
                   m[4] = cosp * v.v[0] * v.v[1] - v.v[2] * sin;
                   m[5] = cos + cosp * v.v[1] * v.v[1];
                   m[6] = cosp * v.v[1] * v.v[2] + v.v[0] * sin;
                   m[7] = 0.0f;
                   m[8] = cosp * v.v[0] * v.v[2] + v.v[1] * sin;
                   m[9] = cosp * v.v[1] * v.v[2] - v.v[0] * sin;
                   m[10] = cos + cosp * v.v[2] * v.v[2];
                   m[11] = 0.0f;
                   m[12] = 0.0f;
                   m[13] = 0.0f;
                   m[14] = 0.0f;
                   m[15] = 1.0f;
                   )
        Matrix4 operator*(const Matrix4 &other) const;
        Matrix4 operator+(const Matrix4 &other) const;
        Matrix4 operator-(const Matrix4 &other) const;
        Matrix4 operator+(const Vector3f &trans) const;
        Matrix4 &operator+=(const Vector3f &trans);
        Matrix4 operator*(const Vector3f &scale) const;
        Matrix4 &operator*=(const Vector3f &scale);
        Matrix4 &operator=(const Matrix4 &other);
        Matrix4 &operator=(const float *other);
        _FORCE_INLINE_ float &operator[](int idx) {
            return m[idx];
        }
        _FORCE_INLINE_ const float &operator[](int idx) const {
            return m[idx];
        }
        
        Matrix4 rotate(float radians, const Vector3f &axis) const;
        Matrix4 rotate(float radians, float x, float y, float z) const;
        
        void setPosition(const Vector3f &pos);
        
        Matrix4 inverse() const;
        static const Matrix4 &identity();
        static Matrix4 ortho(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 perspective(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 lookAt(const Vector3f &target, const Vector3f &up = Vector3f(0,1,0));
        static Matrix4 lerp(const Matrix4 &from, const Matrix4 &to, float p);
        static Matrix4 fromQuaternion(const Vector4f &q);
        static Matrix4 fromEuler(const Vector3f &euler);
        static Matrix4 TRS(const Vector3f &position, const Vector4f &quaternion, const Vector3f &scale);
        
        Vector3f euler() const;
        Vector3f position() const;
        Vector4f rotation() const;
        Vector3f scale() const;
        Matrix4 transpose() const;
        
        SUPPORT_VARIANT(Matrix4);
    };

    typedef Vector4f HColor;
    typedef Vector4f HRect;
    typedef Vector4f HQuaternion;
    typedef Vector3f HPoint;
    typedef Vector2f HSize;
    typedef Vector2i HRange;
    typedef Vector3f VSize;
}


#endif //HIRENDER_VECTOR_H
