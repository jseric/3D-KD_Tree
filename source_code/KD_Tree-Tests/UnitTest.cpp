#include "pch.h"
#include "CppUnitTest.h"

#include "../Engine/Repository/KD Tree/Vertex/Vertex.h"
#include "../Engine/Repository/KD Tree/Root/Root.h"
#include "../Engine/Repository/KD Tree/Node/Node.h"
#include "../Engine/Repository/KD Tree/Tree/Tree.h"

#include "../Engine/Repository/Repository.h"

#include <DirectXMath.h>

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KD_Tree_Tests
{
    TEST_CLASS(KDTree_Test)
    {
    public:
        TEST_METHOD(VertexTests)
        {
            using namespace vxe;

            DirectX::VertexPosition* v1 = new DirectX::VertexPosition{};
            DirectX::VertexPosition* v2 = new DirectX::VertexPosition{ 0, 0, 0 };

            // Check if default constructor is ok
            Assert::IsTrue(AreEqual(*v1, *v2));

            delete v1;
            delete v2;

            v1 = new DirectX::VertexPosition{ 
                DirectX::XMFLOAT3{10, 20, 0} };
            v2 = new DirectX::VertexPosition{ 10, 20, 0 };

            // Check if different constructors give the same object
            Assert::IsTrue(AreEqual(*v1, *v2));

            delete v1;
            delete v2;

            DirectX::VertexPosition v3{ 10, 20 };
            DirectX::VertexPosition v4;

            v4 = v3;

            // Check if operator = is ok
            Assert::IsTrue(AreEqual(v3, v4));

            // Check if distance between the same vertex is 0
            Assert::AreEqual(0.0f, Distance(v3, v3));
        }
        
        TEST_METHOD(RootTests)
        {
            using namespace vxe;

            Root* r = new Root{};
            
            // Check for default constructor preassigned value
            Assert::IsNull(r->next);
        
            delete r;
        }
        
        TEST_METHOD(NodeTests)
        {
            using namespace vxe;

            Node* n = new Node{};

            // Check if default constructor is ok
            Assert::IsTrue(AreEqual(n->point, DirectX::VertexPosition{}));
            Assert::IsNull(n->left);
            Assert::IsNull(n->right);

            delete n;
            
            DirectX::VertexPosition* v = new DirectX::VertexPosition{ 10, 20 };
            n = new Node{ *v };

            // Check if overloaded constructor 1 is ok
            Assert::IsTrue(AreEqual(n->point, *v));

            delete n;

            n = new Node{ *v };

            Assert::IsTrue(AreEqual(n->point, *v));

            delete n;
            delete v;
        }

        TEST_METHOD(TreeTests)
        {
            using namespace vxe;

            DirectX::VertexPosition* v1 = new DirectX::VertexPosition{ 10, 20 };
            Tree* tree = new Tree{ *v1 };

            // Check Tree::Find()
            Assert::IsTrue(tree->Find(*v1));

            delete tree;

            std::vector<DirectX::VertexPosition> vertices{ *v1 };
            tree = new Tree{ vertices };

            // Check Tree::Find()
            Assert::IsTrue(tree->Find(*v1));
            
            vertices.clear();
            delete v1;

            v1 = new DirectX::VertexPosition{ 20, 10 };
            vertices.push_back(*v1);
            delete v1;
            
            v1 = new DirectX::VertexPosition{ 10, 20 };
            vertices.push_back(*v1);
            delete v1;

            v1 = new DirectX::VertexPosition{ 20, 20 };
            vertices.push_back(*v1);
            delete v1;

            v1 = new DirectX::VertexPosition{ 10, 10 };
            vertices.push_back(*v1);
            delete v1;

            tree->Insert(vertices);

            // Check Tree::Find() and Tree::Insert()
            Assert::IsTrue(tree->Find(*v1));
            
            vertices.clear();

            delete v1;
            v1 = new DirectX::VertexPosition{ 30, 20 };
            tree->Insert(*v1);

            // Check Tree::Find() and Tree::Insert()
            Assert::IsTrue(tree->Find(*v1));
            
            // Check Tree::NearestNeighbourSearch()
            Assert::IsTrue(AreEqual(*v1, tree->NearestNeighbourSearch(*v1)));

            delete v1;
            delete tree;

            std::vector<DirectX::VertexPosition> v2{ 
                DirectX::VertexPosition{30},
                DirectX::VertexPosition{20},
                DirectX::VertexPosition{40},
                DirectX::VertexPosition{10} };
            std::vector<DirectX::VertexPosition> v3{
                DirectX::VertexPosition{10},
                DirectX::VertexPosition{20},
                DirectX::VertexPosition{30},
                DirectX::VertexPosition{40} };

            Tree::SortPointsByXValue(v2);
            
            // Check Tree::SortPointsByXValue()
            for (unsigned int i{ 0 }; i < v2.size(); i++)
                Assert::IsTrue(AreEqual(v2[i], v3[i]));

            v2.clear();
            v3.clear();

            DirectX::VertexPosition v4{ 50 };
            DirectX::VertexPosition v5{ 100 };
            DirectX::VertexPosition v6{ 25 };
            
            // Check Tree::SortByXCriterion
            Assert::IsTrue(Tree::SortByXCriterion(v4, v5));
            Assert::IsFalse(Tree::SortByXCriterion(v4, v6));
            Assert::IsFalse(Tree::SortByXCriterion(v5, v6));
            
        }

        TEST_METHOD(RepositoryTests)
        {
            using namespace kdt;

            std::string name1{ CreateNewTree("tree") };

            // Check GetTree()
            Assert::IsNotNull(GetTree(name1));
            Assert::IsNull(GetTree(std::string{ name1 + "23" }));

            std::vector<DirectX::VertexPosition> vertices{ DirectX::VertexPosition{ 10 } };
            std::string name2{ CreateNewTree("tree") };

            InsertVertexToTree(name2, vertices);

            // Check GetTree()
            Assert::IsNotNull(GetTree(name1));
            Assert::IsNull(GetTree(std::string{ name1 + "23" }));

        }
    };
}
