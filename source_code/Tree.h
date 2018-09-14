#pragma once

#include "Vector4.h"
#include "Node.h"
#include "Root.h"

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

        Node* CreateNewNode(const float4&);

        void InitTreeWithMultiplePoints(std::vector<float4>);

        unsigned int GetIndexOfMedianNode(std::vector<float4>&);

        void ReadFromFile(std::string&);

        void IncrementDimension(unsigned int&);

        void DeleteAll(Node*);

        int Delete(float4&, Node*, unsigned int);

        float4 FindMin(Node*, unsigned int, unsigned int);

        float4 FindMax(Node*, unsigned int, unsigned int);

        void NearestNeighbourSearch(const float4&, Node*,
            unsigned int, float4&, float&);

        std::string ToString(Node*);

#pragma endregion

    public:
#pragma region Constructors and destructor

        Tree(void);
        Tree(const float4&);
        Tree(const std::vector<float4>&);
        Tree(std::string&);

        ~Tree(void);

#pragma endregion

#pragma region Public tree methods

        int Insert(float4&);
        int Insert(std::vector<float4>&);

        int Delete(float4&);

        float4 NearestNeighbourSearch(const float4&);

        bool Find(float4&);

#pragma endregion

#pragma region Print methods

        std::string ToString(void);

#pragma endregion

#pragma region Static methods

        static void SortPointsByXValue(std::vector<float4>&);

        static bool SortByXCriterion(const float4, const float4);

#pragma endregion 

    };
}
