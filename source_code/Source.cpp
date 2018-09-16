#include "List.h"
#include "Macros.h"
#include "Timer.h"
#include "Tree.h"
#include "Vertex.h"

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

void RunTest1(void);
void RunTest2(void);

kdt::Vertex AskUserForCoordinates(void);

void GenerateRandomPoints(std::vector<kdt::Vertex>&,
                          const unsigned int, 
                          const float, const float);

float GetRandomFloat(const float, const float);

int main(void)
{
    // Init random seed
    srand(time(NULL));

    RunTest1();
    RunTest2();

    system("pause");

    return RETURN_EXIT_SUCCESS;
}

/// Test 1:
/// Read points from file
void RunTest1(void)
{
    // Path and name of file containing points
    std::string filePath{ 
        "D:\\Josip\\Development\\Visual Studio 2017\\3D_KD-Tree\\Main\\points1.txt" };

    // Create and init Tree and List objects
    kdt::Tree tree{ filePath };
    kdt::List list{ filePath };

    // Print all tree points
    std::cout << "##############################" << std::endl;
    std::cout << "TREE:" << std::endl;
    std::cout << tree.ToString() << std::endl;
    
    // Print all list points
    std::cout << "##############################" << std::endl;
    std::cout << "LIST:" << std::endl;
    std::cout << list.ToString() << std::endl;

    // Get point from user
    kdt::Vertex targetPoint{ AskUserForCoordinates() };
    
    // Create Timer object
    kdt::Timer timer{ false };

    // Find the nearest neighbour in tree
    timer.Start();
    kdt::Vertex neighbour{ tree.NearestNeighbourSearch(targetPoint) };
    timer.Stop();

    // Print the nearest neighbour from tree
    std::cout << "##############################" << std::endl;
    std::cout << "Nearest neighbour in tree is point:" << std::endl;
    std::cout << neighbour.ToString() << std::endl;
    std::cout << "Time is: " << timer.ToString() << std::endl;

    // Find the nearest neighbour in list
    timer.Start();
    kdt::Vertex neighbour2{ list.NearestNeighbourSearch(targetPoint) };
    timer.Stop();

    // Print the nearest neighbour from list
    std::cout << "##############################" << std::endl;
    std::cout << "Nearest neighbour in list is point:" << std::endl;
    std::cout << neighbour.ToString() << std::endl;
    std::cout << "Time is: " << timer.ToString() << std::endl;
}

/// Test 2:
/// Randomly generate 1,000,000 points
void RunTest2(void)
{
    // Number of points to be generated
    const unsigned int numberOfPoints{ 1000000 };
    
    // Min and max values of X, Y and Z
    const float minValue{ -1000 };
    const float maxValue{  1000 };

    std::vector<kdt::Vertex> points{};

    // Randomly generate points
    GenerateRandomPoints(points, numberOfPoints, minValue, maxValue);

    // Create and init Tree and list objects
    kdt::Tree tree{ points };
    kdt::List list{ points };
    /*
    // Print all tree points
    std::cout << "##############################" << std::endl;
    std::cout << "TREE:" << std::endl;
    std::cout << tree.ToString() << std::endl;

    // Print all list points
    std::cout << "##############################" << std::endl;
    std::cout << "LIST:" << std::endl;
    std::cout << list.ToString() << std::endl;
    */
    // Get point from user
    kdt::Vertex targetPoint{ AskUserForCoordinates() };

    // Create Timer object
    kdt::Timer timer{ false };

    // Find the nearest neighbour in tree
    timer.Start();
    kdt::Vertex neighbour{ tree.NearestNeighbourSearch(targetPoint) };
    timer.Stop();

    // Print the nearest neighbour from tree
    std::cout << "##############################" << std::endl;
    std::cout << "Nearest neighbour in tree is point:" << std::endl;
    std::cout << neighbour.ToString() << std::endl;
    std::cout << "Time is: " << timer.ToString() << " ns" << std::endl;

    // Find the nearest neighbour in list
    timer.Start();
    kdt::Vertex neighbour2{ list.NearestNeighbourSearch(targetPoint) };
    timer.Stop();

    // Print the nearest neighbour from list
    std::cout << "##############################" << std::endl;
    std::cout << "Nearest neighbour in list is point:" << std::endl;
    std::cout << neighbour.ToString() << std::endl;
    std::cout << "Time is: " << timer.ToString() << " ns" << std::endl;
}

/// Get point coordinates from user
kdt::Vertex AskUserForCoordinates(void)
{
    float x{ 0.0f };
    float y{ 0.0f };
    float z{ 0.0f };

    std::cout << "Please enter the coordinates:" << std::endl;
    std::cin >> x >> y >> z;

    return kdt::Vertex{ x, y, z };
}

/// Generate number of points randomly
void GenerateRandomPoints(std::vector<kdt::Vertex>& points,
                          const unsigned int counter,
                          const float min, const float max)
{
    float x{ 0.0f };
    float y{ 0.0f };
    float z{ 0.0f };

    for (unsigned int i{ 0 }; i < counter; i++)
    {
        x = GetRandomFloat(min, max);
        y = GetRandomFloat(min, max);
        z = GetRandomFloat(min, max);

        points.push_back(kdt::Vertex{ x, y, z });
    }
}

/// Generate a random floating point number in range [min, max]
float GetRandomFloat(const float min, const float max)
{
    float random{ ((float)rand()) / (float)RAND_MAX };
    float diff{ max - min };

    random *= diff;

    return (min + random);
}
