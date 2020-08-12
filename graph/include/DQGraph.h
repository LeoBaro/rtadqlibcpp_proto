#include <iostream>

namespace dqgraph {


    // Data structure to store Adjacency list nodes
    struct Node {
        int val;
        Node* next;
    };

    // Data structure to store graph edges
    struct Edge {
        int src, dest;
    };

    class DQGraph
    {
        // Function to allocate new node of Adjacency List
        Node* getAdjListNode(int dest, Node* head)
        {
            Node* newNode = new Node;
            newNode->val = dest;

            // point new node to current head
            newNode->next = head;

            return newNode;
        }

        int N;  // number of nodes in the graph

    public:

        // An array of pointers to Node to represent
        // adjacency list
        Node **head;

        // Constructor
        Graph(Edge edges[], int n, int N);

        // Destructor
        ~Graph();
    };

    // print all neighboring vertices of given vertex
    void printList(Node* ptr);
}
