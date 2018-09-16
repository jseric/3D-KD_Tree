#pragma once

#include "Node.h"
#include "Root.h"
#include "Vertex.h"

#include <string>
#include <vector>

/// Namespace KD-Tree
namespace kdt
{
    class Tree
    {
    private:
#pragma region Private members

        Root root;

#pragma endregion

#pragma region Private helper methods

        Node* CreateNewNode(const Vertex&);

        void InitTreeWithMultiplePoints(std::vector<Vertex>);

        unsigned int GetIndexOfMedianNode(std::vector<Vertex>&);

        void ReadFromFile(std::string&);

        void IncrementDimension(unsigned int&);

        void DeleteAll(Node*);

        int Delete(Vertex&, Node*, unsigned int);

        Vertex FindMin(Node*, unsigned int, unsigned int);

        Vertex FindMax(Node*, unsigned int, unsigned int);

        void NearestNeighbourSearch(Vertex&, Node*,
            unsigned int, Vertex&, float&);

        std::string ToString(Node*);

#pragma endregion

    public:
#pragma region Constructors and destructor

        Tree(void);
        Tree(const Vertex&);
        Tree(std::vector<Vertex>);
        Tree(std::string&);

        ~Tree(void);

#pragma endregion

#pragma region Public tree methods

        int Insert(Vertex&);
        int Insert(std::vector<Vertex>&);

        int Delete(Vertex&);

        Vertex NearestNeighbourSearch(Vertex&);

        bool Find(Vertex&);

#pragma endregion

#pragma region Print methods

        std::string ToString(void);

#pragma endregion

#pragma region Static methods

        static void SortPointsByXValue(std::vector<Vertex>&);

        static bool SortByXCriterion(Vertex&, Vertex&);

#pragma endregion 

    };
}
