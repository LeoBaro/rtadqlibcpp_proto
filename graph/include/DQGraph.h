#include <iostream>

namespace dqlib {

    class Node
    {
        public:
            Node();
            virtual ~Node();
            int val;
            Node* next;
    };


    // Data structure to store graph edges
    struct Edge 
    {
        int src, dest;
    };

    class DQGraph
    {

    public:

        // Constructor for dynamic allocation
        DQGraph();

        // Constructor for static allocation
        DQGraph(Edge edges[], int n, int N);

        // Destructor
        virtual ~DQGraph();

        // print adjacency list representation of graph
        void printAdjList();

        // print all neighboring vertices of given vertex
        void printList(Node* ptr);
    
    private:

        // An array of pointers to Node to represent adjacency list
        Node **head;

        // Function to allocate new node of Adjacency List
        Node* getAdjListNode(int dest, Node* head);

        int N;  // number of nodes in the graph

    };


}
