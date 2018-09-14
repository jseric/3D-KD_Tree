#pragma once

#include "Vector4.h"

#include <string>
#include <vector>

/// Namespace KD-Tree
namespace kdt
{
    class List
    {
    private:
#pragma region Private members

        std::vector<float4> points;

#pragma endregion

#pragma region Private helper methods

        void ReadFromFile(std::string&);

#pragma endregion

    public:
#pragma region Constructors and destructor

        List(void);
        List(const float4&);
        List(const std::vector<float4>&);
        List(std::string&);

        ~List(void);

#pragma endregion

#pragma region Public list methods

        void Insert(const float4&);
        void Insert(const std::vector<float4>&);

        int Delete(float4&);

        float4 NearestNeighbourSearch(const float4&);

        bool Find(float4&);

#pragma endregion

#pragma region Print methods

        std::string ToString(void);

#pragma endregion
    };
}
