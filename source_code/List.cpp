#include "List.h"

#include "Macros.h"

#include <fstream>
#include <sstream>

/// Namespace KD-Tree
namespace kdt
{
#pragma region Private

    /// Read points from file
    void List::ReadFromFile(std::string& fileName)
    {
        // Open file
        std::ifstream file(fileName);

        // Coordinate buffers
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        // Read points' data from file
        while (!file.eof())
        {
            file >> x >> y >> z;
            Insert(float4{ x, y, z });
        }

        // Close file
        file.close();
    }

#pragma endregion

#pragma region Public

    /// Default constructor
    List::List(void)
    {
    }

    /// Overloaded constructor 1
    /// Takes 1 point and inserts it in list
    List::List(const float4& target)
    {
        Insert(target);
    }

    /// Overloaded constructor 2
    /// Takes a vector of points and inserts
    /// them inside list
    List::List(const std::vector<float4>& targets)
    {
        Insert(targets);
    }

    /// Overloaded constructor 3
    /// Takes a string containing name of file
    /// Reads points from file, and inserts
    /// the points into list
    List::List(std::string& fileName)
    {
        ReadFromFile(fileName);
    }

    /// Destructor
    /// Remove all points from list
    List::~List(void)
    {
        points.clear();
    }

    /// Insert point to list
    void List::Insert(const float4& target)
    {
        points.push_back(target);
    }

    /// Insert multiple points to list
    void List::Insert(const std::vector<float4>& targets)
    {
        for (unsigned int i{ 0 }; i < targets.size(); i++)
            points.push_back(targets[i]);
    }

    /// Find (and if found) delete the node
    /// with target coordinates
    int List::Delete(float4& target)
    {
        for (unsigned int i{ 0 }; i < points.size(); i++)
        {
            if (AreEqual(target, points[i]))
            {
                points.erase(points.begin() + i);
                
                return RETURN_DELETE_OK;
            }
        }
        
        return RETURN_DELETE_POINT_NOT_FOUND;
    }

    /// Search the list for the nearest neighbour
    /// (the closest point of the target point)   
    float4 List::NearestNeighbourSearch(const float4& target)
    {
        if (points.empty())
            return float4{};

        float4 nearestPoint{ points[0] };
        float nearestDistance{ Distance(target, nearestPoint) };

        for (unsigned int i{ 1 }; i < points.size(); i++)
        {
            float bufferDistance{ Distance(target, points[i]) };
            if (bufferDistance < nearestDistance)
            {
                nearestDistance = bufferDistance;
                nearestPoint = points[i];
            }
        }

        return nearestPoint;
    }

    /// Search for point inside list
    /// If found, return true, else false
    bool List::Find(float4& target)
    {
        for (unsigned int i{ 0 }; i < points.size(); i++)
            if (AreEqual(target, points[i]))
                return true;

        return false;
    }

    /// Return list data as a string.
    /// Often used for displaying object information
    /// in console
    std::string List::ToString(void)
    {
        std::stringstream ss{};

        for (unsigned int i{ 0 }; i < points.size(); i++)
        {
            ss << points[i].ToString();

            if ((i + 1) % 10)
                ss << "\t";
            else
                ss << std::endl;
        }

        return ss.str();
    }

#pragma endregion
}
