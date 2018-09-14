#pragma once

#include <cmath>
#include <string>
#include <sstream>

/// Namespace KD-Tree
namespace kdt
{
    template <typename T>
    struct Vector4 {
        union
        {
            T v[4];

            /// Coordinates
            struct
            {
                T x;
                T y;
                T z;
                T w;
            };
        };

        /// Constructor taking (up to) 4 arguments 
        Vector4(T v0 = 0, T v1 = 0, T v2 = 0, T v3 = 1)
            : x{ v0 }, y{ v1 }, z{ v2 }, w{ v3 }
        {
        }

        /// Overloaded operator []
        ///
        /// Allows the members of object to be
        /// accessible as array members
        ///
        /// Example: obj.x is the same as obj[0]
        T& operator[](unsigned int index)
        {
            return reinterpret_cast<T*>(this)[index];
        }

        /// Function returning object data in a string.
        /// Often used for displaying object information
        /// in console
        std::string ToString(void)
        {
            std::stringstream ss;
            ss << "[ " << x << " " << y << " " << z << " " << w << "]";
            return ss.str();
        }

        /// Overloaded operator =
        void operator =(const Vector4<T> &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

    };

    /// Compare 2 vectors
    template <typename T>
    bool AreEqual(Vector4<T>& vec1, Vector4<T>& vec2)
    {
        for (unsigned int i{ 0 }; i < 4; i++)
            if (vec1[i] != vec2[i])
                return false;

        return true;
    }


    /// Get distance between 2 vectors
    template <typename T>
    T Distance(const Vector4<T>& vec1, const Vector4<T>& vec2)
    {
        T target{ 0 };

        for (unsigned int i{ 0 }; i < 4; i++)
            target += pow(vec1.v[i] - vec2.v[i], 2.0f);

        return sqrt(target);;
    }

    /// Alias for easier declaration of a vector
    /// containing floats
    using float4 = Vector4<float>;
}
