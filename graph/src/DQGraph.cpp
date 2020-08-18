#include "DQGraph.h"


dqlib::DQGraph::DQGraph(Edge edges[], int n, int N) 
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

    }
}

dqlib::DQGraph::~DQGraph() {
    for (int i = 0; i < N; i++)
        delete[] head[i];

    delete[] head;
}

dqlib::Node* dqlib::DQGraph::getAdjListNode(int dest, Node* head) 
{
    Node* newNode = new Node();
    newNode->val = dest;

    // point new node to current head
    newNode->next = head;

    return newNode;
}

void dqlib::DQGraph::printAdjList()
{
    for (int i = 0; i < N; i++)
	{
		// print given vertex
		std::cout << i << " --";

		// print all its neighboring vertices
		printList(head[i]);
	}
}

void dqlib::DQGraph::printList(Node * ptr) 
{
    while (ptr != nullptr) 
    {
        std::cout << " -> " << ptr->val << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}