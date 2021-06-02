#pragma once

#define _USE_FMT

// use which fp-precision? 1=float, 2=double
#define _FLOATINGPOINT_PRECISION 1

// VECTOR_EPSILON is the minimal vector length
// In order to be able to discriminate floating point values near zero, and
// to be sure not to fail a comparison because of roundoff errors, use this
// value as a threshold.
#if _FLOATINGPOINT_PRECISION==1
    typedef float Real;
#   define VECTOR_EPSILON (1e-6f)
#else
    typedef double Real;
#   define VECTOR_EPSILON (1e-10)
#endif

#include <cmath>

template<class T>
class Vector3D
{
public:
    // Constructor
    constexpr Vector3D() noexcept : x(0), y(0), z(0) {}
    constexpr Vector3D( const T s ) noexcept : x(s), y(s), z(s) {}
    constexpr Vector3D( const T vx, const T vy, const T vz ) noexcept : x(vx), y(vy), z(vz) {}

    // Copy-Constructor
    constexpr Vector3D( const Vector3D<T>& v ) noexcept : x(v.x), y(v.y), z(v.z) {}
    constexpr Vector3D( const int* v ) noexcept : x( static_cast<T>(v[0]) ), y( static_cast<T>(v[1]) ), z( static_cast<T>(v[2]) ) {}
    constexpr Vector3D( const float* v ) noexcept : x( static_cast<T>(v[0]) ), y( static_cast<T>(v[1]) ), z( static_cast<T>(v[2]) ) {}
    constexpr Vector3D( const double* v ) noexcept : x( static_cast<T>(v[0]) ), y( static_cast<T>(v[1]) ), z( static_cast<T>(v[2]) ) {}

    // Assignment Operators
    // assignment
    constexpr Vector3D<T>& operator=( const Vector3D<T>& v ) noexcept
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    constexpr Vector3D<T>& operator=( const T s ) noexcept
    {
        x = y = z = s
        return *this;
    }

    // incrementation
    constexpr Vector3D<T>& operator+=( const Vector3D<T>& v ) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    constexpr Vector3D<T>& operator+=( const T s ) noexcept
    {
        x += s;
        y += s;
        z += s;
        return *this;
    }

    // decrementation
    constexpr Vector3D<T>& operator-=( const Vector3D<T>& v ) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    constexpr Vector3D<T>& operator-=( const T s ) noexcept
    {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }

    // multiplication
    constexpr Vector3D<T>& operator*=( const Vector3D<T>& v ) noexcept
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    constexpr Vector3D<T>& operator*=( const T s ) noexcept
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // division
    constexpr Vector3D<T>& operator/=( const Vector3D<T>& v ) noexcept
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    constexpr Vector3D<T>& operator/=( const T s ) noexcept
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // Operators
    constexpr Vector3D<T> operator+() const noexcept
    {
        return *this;
    }

    constexpr Vector3D<T> operator-() const noexcept
    {
        return {-x, -y, -z};
    }

    // addition
    constexpr Vector3D<T> operator+(const Vector3D<T>& v) const noexcept
    {
        return {x + v.x, y + v.y, z + v.z};
    }

    // subtraction
    constexpr Vector3D<T> operator-(const Vector3D<T>& v) const noexcept
    {
        return {x - v.x, y - v.y, z - v.z};
    }

    // multiplication
    constexpr Vector3D<T> operator*(const Vector3D<T>& v) const noexcept
    {
        return {x * v.x, y * v.y, z * v.z};
    }
    constexpr Vector3D<T> operator*(const T s) const noexcept
    {
        return {x * s, y * s, z * s};
    }
    friend constexpr Vector3D<T> operator*(const T s, const Vector3D<T>& v) noexcept
    {
        return v * s;
    }

    // division
    constexpr Vector3D<T> operator/(const Vector3D<T>& v) const noexcept
    {
        return {x / v.x, y / v.y, z / v.z};
    }
    constexpr Vector3D<T> operator/(const T s) const noexcept
    {
        return {x / s, y / s, z / s};
    }

    constexpr bool operator==(const Vector3D<T>& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }
    constexpr bool operator!=(const Vector3D<T>& v) const noexcept
    {
        return !(*this == v);
    }

    // Access Operators
    inline T &operator[]( unsigned int i ) noexcept { return value[i]; };
    inline const T &operator[]( unsigned int i ) const noexcept { return value[i]; };

    // Check components
    constexpr T min() const noexcept { return (x<y) ? ( (x<z) ? x:z ) : ( (y<z) ? y:z ); }
    constexpr T max() const noexcept { return (x>y) ? ( (x>z) ? x:z ) : ( (y>z) ? y:z ); }
    constexpr bool isEmpty() const noexcept { return x==0 && y==0 && z==0; }

    // Special functions
    constexpr T normSquare() const noexcept
    {
        return x * x + y * y + z * z;
    }
    constexpr T norm() const noexcept
    {
        T square = normSquare();
        if( square <= VECTOR_EPSILON*VECTOR_EPSILON ) return(0.);
        return ( std::abs( square-1. ) <  VECTOR_EPSILON*VECTOR_EPSILON ) ? 1. : std::sqrt( square );
    }

    constexpr Vector3D<T> getNormalized() const noexcept
    {
        T square = normSquare();

        if( std::abs( square-1. ) < VECTOR_EPSILON*VECTOR_EPSILON )
            return *this;
        else if( square > VECTOR_EPSILON*VECTOR_EPSILON )
        {
            T fac = 1./std::sqrt( square );
            return Vector3D<T>( x*fac, y*fac, z*fac );
        }
        else
            return Vector3D<T>();
    }

    constexpr void normalize() noexcept
    {
        T square = normSquare();

        if( std::abs( square-1. ) < VECTOR_EPSILON*VECTOR_EPSILON ) return;
        else if( square > VECTOR_EPSILON*VECTOR_EPSILON )
        {
            T fac = 1./std::sqrt( square );
            x *= fac;
            y *= fac;
            z *= fac;
        }
        return;
    }

    // Friends
    friend constexpr T dot(const Vector3D<T>& a, const Vector3D<T>& b) noexcept
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    friend constexpr Vector3D<T> cross(const Vector3D<T>& a, const Vector3D<T>& b) noexcept
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }

    /*! Compute a vector parallel to a surface with a normal vector.
    \param t The vector to be projected
    \param n The surface normal
    \return The projected vector
    */
    friend constexpr Vector3D<T> projectToPlane(const Vector3D<T>& v, const Vector3D<T>& n) noexcept
    {
        return v - dot(v, n) * n;
    }

    /*! Compute a vector reflected at a surface with a normal vector. 
    \param t The incoming vector
    \param n The surface normal
    \return The reflected vector
    */
    friend constexpr Vector3D<T> reflectVector(const Vector3D<T>& t, const Vector3D<T>& n) noexcept
    {
        return t - 2.0 * dot(t, n) * n;
    }

    /*! Compute vector refracted at a surface
    \param t The incoming vector
    \param normal The surface normal
    \param n1 The refractive index of the medium on the "incident" side
    \param n2 The refractive index of the medium on the "refractive" side
    \param refRefl Set to 1 on total reflection
    \return The refracted vector
    */
    friend constexpr Vector3D<T> refractVector(const Vector3D<T> &t, const Vector3D<T> &normal, const T n1, const T n2, int &refRefl ) noexcept
    {
        T eta = n1 / n2;
        T n = -dot( t, normal );
        T tt = 1.0 + eta*eta* ( n*n-1.0 );
        if( tt<0.0 )
        {
            // we have total reflection!
            refRefl = 1;
        }
        else 
        {
            // normal reflection
            tt = eta*n - std::sqrt( tt );
            return t*eta + normal*tt;
        }
        return t;
    }

    union {
        T value[3];
        #pragma warning(disable : 4201)
        struct {
            T x;
            T y;
            T z;
        };
        #pragma warning(disable : 4201)
        struct {
            T X;
            T Y;
            T Z;
        };
    };
};


//! 3D vector class of type Real (typically float)
typedef Vector3D<Real> Vec3;

//! 3D vector class of type int
typedef Vector3D<int> Vec3i;


#ifdef _USE_FMT
#include <fmt/format.h>

template <>
struct fmt::formatter<Vec3> {
  // Presentation format: 'f' - fixed, 'e' - exponential.
  char presentation = 'f';

  // Parses format specifications of the form ['f' | 'e'].
  constexpr auto parse(format_parse_context& ctx) {
  // auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) // c++11
    // [ctx.begin(), ctx.end()) is a character range that contains a part of
    // the format string starting from the format specifications to be parsed,
    // e.g. in
    //
    //   fmt::format("{:f} - point of interest", point{1, 2});
    //
    // the range will contain "f} - point of interest". The formatter should
    // parse specifiers until '}' or the end of the range. In this example
    // the formatter should parse the 'f' specifier and return an iterator
    // pointing to '}'.

    // Parse the presentation format and store it in the formatter:
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

    // Check if reached the end of the range:
    if (it != end && *it != '}')
      throw format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return it;
  }

  // Formats the point p using the parsed format specification (presentation)
  // stored in this formatter.
  template <typename FormatContext>
  auto format(const Vec3& v, FormatContext& ctx) {
  // auto format(const point &p, FormatContext &ctx) -> decltype(ctx.out()) // c++11
    // ctx.out() is an output iterator to write to.
    return format_to(
        ctx.out(),
        presentation == 'f' ? "({:+4.6f}, {:+4.6f}, {:+4.6f})" : "({:+4.6e}, {:+4.6e}, {:+4.6e})",
        v.x, v.y, v.z);
  }
};

template <>
struct fmt::formatter<Vec3i> {
  char presentation = 'd';

  // Parses format specifications of the form ['f' | 'e'].
  constexpr auto parse(format_parse_context& ctx) {
  // auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) // c++11
    // [ctx.begin(), ctx.end()) is a character range that contains a part of
    // the format string starting from the format specifications to be parsed,
    // e.g. in
    //
    //   fmt::format("{:f} - point of interest", point{1, 2});
    //
    // the range will contain "f} - point of interest". The formatter should
    // parse specifiers until '}' or the end of the range. In this example
    // the formatter should parse the 'f' specifier and return an iterator
    // pointing to '}'.

    // Parse the presentation format and store it in the formatter:
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it == 'd') presentation = *it++;

    // Check if reached the end of the range:
    if (it != end && *it != '}')
      throw format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return it;
  }

  // Formats the point p using the parsed format specification (presentation)
  // stored in this formatter.
  template <typename FormatContext>
  auto format(const Vec3i& v, FormatContext& ctx) {
  // auto format(const point &p, FormatContext &ctx) -> decltype(ctx.out()) // c++11
    // ctx.out() is an output iterator to write to.
    return format_to(
        ctx.out(),
        "({:+d}, {:+d}, {:+d})",
        v.x, v.y, v.z);
  }
};
#endif