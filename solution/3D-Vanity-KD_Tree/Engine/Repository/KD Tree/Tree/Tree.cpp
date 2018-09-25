#include "pch.h"

#include "Tree.h"

#include "../Macros/KDTreeMacros.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

namespace vxe
{
#pragma region Private

    /// Allocate new node
    Node* Tree::CreateNewNode(const DirectX::VertexPosition& targetPoint)
    {
        try
        {
            Node *target = new Node{ targetPoint };

            return target;
        }
        catch (std::bad_alloc& ba)
        {
            UNREFERENCED_PARAMETER(ba);

            std::cout << "ERROR!!!" << std::endl;
            std::cout << "Allocation Error!!!" << std::endl;

            return nullptr;
        }
    }

    /// Initialize tree with multiple nodes
    void Tree::InitTreeWithMultiplePoints(std::vector<DirectX::VertexPosition> points)
    {
        // Get index of median point
        auto firstNodeIndex{ GetIndexOfMedianNode(points) };
        
        // Allocate node with median point and insert it to tree
        Node *node = CreateNewNode(points[firstNodeIndex]);
        if (!node)
            return;

        root.next = node;

        // Remove median point from vector
        points.erase(points.begin() + firstNodeIndex);

        // Insert remaining nodes
        Insert(points);
    }

    /// Sort points by X-value and return median node index
    unsigned int Tree::GetIndexOfMedianNode(std::vector<DirectX::VertexPosition>& points)
    {
        Tree::SortPointsByXValue(points);

        return ((unsigned int) points.size() / 2);
    }

    /// Read points from file
    void Tree::ReadFromFile(std::string& fileName)
    {
        // Open file
        std::ifstream file(fileName);

        // Coordinate buffers
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        std::vector<DirectX::VertexPosition> points;

        // Read points' data from file
        while (!file.eof())
        {
            file >> x >> y >> z;
            points.push_back(DirectX::VertexPosition{ x, y, z });
        }

        // Close file
        file.close();

        // Init tree
        InitTreeWithMultiplePoints(points);
    }

    /// Shift current dimension to next one
    /// X->Y, Y->Z, Z->X
    /// Note: X=0, Y=1, Z=2
    void Tree::IncrementDimension(unsigned int& dimension)
    {
        dimension = (dimension + 1) % NUMBER_OF_DIMENSIONS;
    }

    /// Delete the node provided as argument
    /// and all of his children
    void Tree::DeleteAll(Node* current)
    {
        if (current)
        {
            DeleteAll(current->left);
            DeleteAll(current->right);
            delete current;
        }
    }
    
    /// Delete node (if it exists) inside subtree with target data
    int Tree::Delete(DirectX::VertexPosition& targetPoint, Node* current,
                         unsigned int currentDimension)
    {
        // Get next dimension
        unsigned int nextDimension{ currentDimension };
        IncrementDimension(nextDimension);

        if (!current)
        {
            // Point not found
            return RETURN_DELETE_POINT_NOT_FOUND;
        }

        if (AreEqual(targetPoint, current->point))
        {
            // Point to delete found

            if (current->right)
            {
                // Right subtree exists

                // Set the point of current node to be
                // min(current dimension) of right subtree
                // and delete that point
                current->point = FindMin(current->right, currentDimension, nextDimension);
                return Delete(current->point, current->right, nextDimension);
            }
            else if (current->left)
            {
                // Left subtree exists

                // Set the point of current node to be
                // max(current dimension) of left subtree
                // and delete that point
                current->point = FindMax(current->left, currentDimension, nextDimension);
                return Delete(current->point, current->left, nextDimension);
            }
            else
            {
                // Target node is a leaf
                DeleteAll(current);
                return RETURN_DELETE_OK;
            }
        }
        
        // Continue the search
        if (targetPoint[currentDimension] < current->point[currentDimension])
        {
            // Search left subtree
            return Delete(targetPoint, current->left, nextDimension);
        }
        else
        {
            // Search right subtree
            return Delete(targetPoint, current->right, nextDimension);
        }
    }

    /// Find point in subtree that contains point with minimum value
    /// in given target dimension
    DirectX::VertexPosition Tree::FindMin(Node* current,
        unsigned int targetDimension,
        unsigned int currentDimension)
    {
        if (!current)
        {
            // Subtree is empty

            // Note: as FindMin returns a float4 object,
            // it is not possible to return nullptr,
            // so we are returning a float point with
            // coordinates x = y = z = max_float_value
            float returnBuffer{ std::numeric_limits<float>::max() };
            return DirectX::VertexPosition(returnBuffer, returnBuffer, returnBuffer);
        }

        if (currentDimension == targetDimension)
        {
            // We are searching in the correct dimension

            if (!current->left)
            {
                // Current node contains the min value
                return current->point;
            }

            // Increment dimension and continue search in left subtree
            IncrementDimension(currentDimension);
            return FindMin(current->left, targetDimension, currentDimension);
        }

        // Increment dimension and return minimum value of 
        // current node data, left subtree minimum and 
        // right subtree minimum
        IncrementDimension(currentDimension);

        DirectX::VertexPosition left{ FindMin(current->left, targetDimension, currentDimension) };
        DirectX::VertexPosition right{ FindMin(current->right, targetDimension, currentDimension) };

        if (left[targetDimension] <= right[targetDimension] &&
            left[targetDimension] <= current->point[targetDimension])
            return left;

        if (right[targetDimension] <= left[targetDimension] &&
            right[targetDimension] <= current->point[targetDimension])
            return right;

        return current->point;
    }

    /// Find point in subtree that contains point with maximum value
    /// in given target dimension
    DirectX::VertexPosition Tree::FindMax(Node* current, unsigned int targetDimension,
                         unsigned int currentDimension)
    {
        if (!current)
        {
            // Subtree is empty

            // Note: as FindMin returns a float4 object,
            // it is not possible to return nullptr,
            // so we are returning a float point with
            // coordinates x = y = z = min_float_value
            float returnBuffer{ std::numeric_limits<float>::min() };
            return DirectX::VertexPosition(returnBuffer, returnBuffer, returnBuffer);
        }

        if (currentDimension == targetDimension)
        {
            // We are searching in the correct dimension

            if (!current->right)
            {
                // Current node contains the max value
                return current->point;
            }

            // Increment dimension and continue search in right subtree
            IncrementDimension(currentDimension);
            return FindMax(current->right, targetDimension, currentDimension);
        }

        // Increment dimension and return maximum value of 
        // current node data, left subtree maximum and 
        // right subtree maximum
        IncrementDimension(currentDimension);

        DirectX::VertexPosition left{ FindMin(current->left, targetDimension, currentDimension) };
        DirectX::VertexPosition right{ FindMin(current->right, targetDimension, currentDimension) };

        if (left[targetDimension] >= right[targetDimension] &&
            left[targetDimension] >= current->point[targetDimension])
            return left;

        if (right[targetDimension] >= left[targetDimension] &&
            right[targetDimension] >= current->point[targetDimension])
            return right;

        return current->point;
    }

    /// Search the tree for the nearest neighbour
    /// (the node containing the closest point of
    /// the target point)
    void Tree::NearestNeighbourSearch(DirectX::VertexPosition& targetPoint,
        Node* current,
        unsigned int dimension, 
        DirectX::VertexPosition& nearestPoint, 
        float& nearestDistance)
    {
        // Get distance between target and current
        float distance{ Distance(targetPoint, current->point) };
        if (distance < nearestDistance)
        {
            // Found new nearest point

            nearestDistance = distance;
            nearestPoint = current->point;
        }

        if (!current->left && !current->right)
        {
            // Current node is a leaf
            return;
        }

        const float targetDimensionValue{ targetPoint[dimension] };

        if (targetDimensionValue <= current->point[dimension])
        {
            // First search left subtree

            if (current->left && 
                (targetDimensionValue - nearestDistance) <=
                current->point[dimension])
            {
                // There is a possibility that the nearest point is
                // in the left subtree

                IncrementDimension(dimension);

                NearestNeighbourSearch(targetPoint, current->left,
                    dimension, nearestPoint, nearestDistance);
            }

            if (current->right &&
                (targetDimensionValue + nearestDistance) >
                current->point[dimension])
            {
                // There is a possibility that the nearest point is
                // in the right subtree

                IncrementDimension(dimension);

                NearestNeighbourSearch(targetPoint, current->right,
                    dimension, nearestPoint, nearestDistance);
            }
        }
        else
        {
            // First search right subtree

            if (current->right &&
                (targetDimensionValue + nearestDistance) >
                current->point[dimension])
            {
                // There is a possibility that the nearest point is
                // in the right subtree

                IncrementDimension(dimension);

                NearestNeighbourSearch(targetPoint, current->right,
                    dimension, nearestPoint, nearestDistance);
            }

            if (current->left &&
                (targetDimensionValue - nearestDistance) <=
                current->point[dimension])
            {
                // There is a possibility that the nearest point is
                // in the left subtree

                IncrementDimension(dimension);

                NearestNeighbourSearch(targetPoint, current->left,
                    dimension, nearestPoint, nearestDistance);
            }
        }
    }

    /// Print current node data and all of his children data
    std::string Tree::ToString(Node* current)
    {
        std::stringstream ss{};

        if (current)
        {
            ss << current->ToString();
            ss << ToString(current->left);
            ss << ToString(current->right);
        }
        
        return ss.str();
    }

#pragma endregion

#pragma region Public

    /// Default constructor
    /// Initializes empty tree
    Tree::Tree(void)
        : root{}
    {
    }

    /// Overloaded constructor 1
    /// Takes 1 point
    /// Initializes tree with 1 point
    Tree::Tree(const DirectX::VertexPosition& point)
        : root{ CreateNewNode(point) }
    {
    }

    /// Overloaded constructor 2
    /// Takes a vector of points
    /// Initializes tree with multiple points
    Tree::Tree(std::vector<DirectX::VertexPosition> points)
    {
        InitTreeWithMultiplePoints(points);
    }

    /// Overloaded constructor 3
    /// Takes a string containing name of file
    /// Reads points from file, and initializes the
    /// tree with those points
    Tree::Tree(std::string& fileName)
    {
        ReadFromFile(fileName);
    }

    /// Destructor
    /// Remove all nodes from tree
    Tree::~Tree(void)
    {
        delete root.next;
    }

    /// Insert node to tree
    int Tree::Insert(DirectX::VertexPosition& targetPoint)
    {
        // If tree is empty
        if (!root.next)
        {
            // Insert as first node
            Node* target = CreateNewNode(targetPoint);
            if (!target)
                return RETURN_BAD_ALLOCATION;

            root.next = target;

            return RETURN_INSERT_OK;
        }

        Node* previous{ nullptr };
        Node* current{ root.next };

        unsigned int dimension{ 0 };

        // Travel through tree
        while (current)
        {
            if (AreEqual(targetPoint, current->point))
            {
                // Point already exists 
                return RETURN_INSERT_DUPLICATE_POINT;
            }

            if (targetPoint[dimension] < current->point[dimension])
            {
                // Go left
                previous = current;
                current = current->left;
            }
            else
            {
                // Go right
                previous = current;
                current = current->right;
            }

            if (current)
                IncrementDimension(dimension);
        }

        // Allocate new node
        Node* target = CreateNewNode(targetPoint);
        if (!target)
            return RETURN_BAD_ALLOCATION;

        if (targetPoint[dimension] < previous->point[dimension])
        {
            // Insert left
            previous->left = target;
        }
        else
        {
            // Insert right
            previous->right = target;
        }
        
        return RETURN_INSERT_OK;
    }

    /// Insert multiple nodes to tree
    int Tree::Insert(std::vector<DirectX::VertexPosition>& points)
    {
        int returnValue{ 0 };

        for (unsigned int i{ 0 }; i < points.size(); i++)
        {
            returnValue = Insert(points[i]);
            if (returnValue != RETURN_INSERT_OK)
                return returnValue;
        }

        return RETURN_INSERT_OK;
    }

    /// Find (and if found) delete the node
    /// with target coordinates
    int Tree::Delete(DirectX::VertexPosition& targetPoint)
    {
        int returnValue{ Delete(targetPoint, root.next, 0) };
        return returnValue;
    }

    /// Search the tree for the nearest neighbour
    /// (the node containing the closest point of
    /// the target point)    
    DirectX::VertexPosition Tree::NearestNeighbourSearch(DirectX::VertexPosition& targetPoint)
    {
        // Set initial distance to be max float value and
        // set the target point to be (0, 0, 0, 1)
        float nearestDistance{ std::numeric_limits<float>::max() };
        DirectX::VertexPosition nearestPoint{ 0.0f, 0.0f, 0.0f };

        NearestNeighbourSearch(targetPoint, root.next,
            0, nearestPoint, nearestDistance);

        return nearestPoint;
    }

    /// Search for point inside tree
    /// If found, return true, else false
    bool Tree::Find(DirectX::VertexPosition& point)
    {   
        Node* current{ root.next };
        unsigned int dimension{ 0 };

        while (current)
        {
            if (AreEqual(point, current->point))
            {
                // Point Found
                return RETURN_FIND_POINT_FOUND;
            }

            // Continue search
            if (point[dimension] < current->point[dimension])
            {
                // Search left subtree
                current = current->left;
            }
            else
            {
                // Search right
                current = current->right;
            }

            IncrementDimension(dimension);
        }

        // Point not found
        return RETURN_FIND_POINT_NOT_FOUND;
    }

    /// For each method
    /// Execute target method on all points in tree
    void Tree::Foreach(std::function<void(DirectX::VertexPosition&)> targetMethod)
    {
        root.RunOnNode(targetMethod);
    }


    /// Return tree data as a string.
    /// Often used for displaying object information
    /// in console
    std::string Tree::ToString(void)
    {
        return ToString(root.next);
    }

#pragma endregion

#pragma region Static

    /// Sort points by X-value
    void Tree::SortPointsByXValue(std::vector<DirectX::VertexPosition>& points)
    {
        std::sort(points.begin(), points.end(), Tree::SortByXCriterion);
    }

    /// Criterion for sorting points by X-value
    bool Tree::SortByXCriterion(DirectX::VertexPosition& v1,
        DirectX::VertexPosition& v2)
    {
        return (v1[0] < v2[0]);
    }

#pragma endregion
}
