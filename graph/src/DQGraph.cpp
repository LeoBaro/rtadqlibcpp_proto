#include "DQGraph.h"

DQGraph::DQGraph(Edge edges[], int n, int N) 
{
    // allocate memory
    head = new Node*[N]();
    this->N = N;

    // initialize head pointer for all vertices
    for (int i = 0; i < N; i++)
        head[i] = nullptr;

    // add edges to the directed graph
    for (unsigned i = 0; i < n; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;

        // insert in the beginning
        Node* newNode = getAdjListNode(dest, head[src]);

        // point head pointer to new node
        head[src] = newNode;

        // Uncomment below lines for undirected graph

        /*
        newNode = getAdjListNode(src, head[dest]);

        // change head pointer to point to the new node
        head[dest] = newNode;
        */
    }
}

DQGraph::~DQGraph() {
    for (int i = 0; i < N; i++)
        delete[] head[i];

    delete[] head;
}

Node* DQGraph::getAdjListNode(int dest, Node* head) 
{
    Node* newNode = new Node;
    newNode->val = dest;

    // point new node to current head
    newNode->next = head;

    return newNode;
}

DQGraph::printList(Node * ptr) 
{
    while (ptr != nullptr) 
    {
        std::cout << " -> " << ptr->val << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}