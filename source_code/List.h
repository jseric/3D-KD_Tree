#pragma once

#include "Vertex.h"

#include <string>
#include <vector>

/// Namespace KD-Tree
namespace kdt
{
    class List
    {
    private:
#pragma region Private members

        std::vector<Vertex> points;

#pragma endregion

#pragma region Private helper methods

        void ReadFromFile(std::string&);

#pragma endregion

    public:
#pragma region Constructors and destructor

        List(void);
        List(const Vertex&);
        List(const std::vector<Vertex>&);
        List(std::string&);

        ~List(void);

#pragma endregion

#pragma region Public list methods

        void Insert(const Vertex&);
        void Insert(const std::vector<Vertex>&);

        int Delete(Vertex&);

        Vertex NearestNeighbourSearch(Vertex&);

        bool Find(Vertex&);

#pragma endregion

#pragma region Print methods

        std::string ToString(void);

#pragma endregion
    };
}
