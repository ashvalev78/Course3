#include <iostream>
#include <list>
#include <stack>

using namespace std;

// Class to represent a graph
class Graph
{
    int V;    // No. of vertices&#039;

    // Pointer to an array containing adjacency listsList
    list <int> *adj;

    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack <int> &Stack);
public:
    Graph(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);

    // prints a Topological Sort of the complete graph
    void topologicalSort();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack <int> &Stack)
{
// Mark the current node as visited.
visited[v] = true;

// Recur for all the vertices adjacent to this vertex
list <int>::iterator i;
for (i = adj[v].begin(); i != adj[v].end(); ++i)
if (!visited[*i])
topologicalSortUtil(*i, visited, Stack);

// Push current vertex to stack which stores result
Stack.push(v);
}

// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
void Graph::topologicalSort()
{
    stack <int> Stack;

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
    if (visited[i] == false)
        topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Following is a Topological Sort of the given graph \n" << endl;
    g.topologicalSort();

    return 0;
}


//#include<iostream> #include <list> #include <stack> using namespace std; Class to represent a graph class Graph { int V;  No. of vertices'  Pointer to an array containing adjacency listsList list<int> *adj;  A function used by topologicalSort void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); public: Graph(int V);  Constructor  function to add an edge to graph void addEdge(int v, int w);  prints a Topological Sort of the complete graph void topologicalSort(); }; Graph::Graph(int V) { this->V = V; adj = new list<int>[V]; } void Graph::addEdge(int v, int w) { adj[v].push_back(w);  Add w to v’s list. }  A recursive function used by topologicalSort void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {  Mark the current node as visited. visited[v] = true;  Recur for all the vertices adjacent to this vertex list<int>::iterator i; for (i = adj[v].begin(); i != adj[v].end(); ++i) if (!visited[*i]) topologicalSortUtil(*i, visited, Stack);  Push current vertex to stack which stores result Stack.push(v); }  The function to do Topological Sort. It uses recursive  topologicalSortUtil() void Graph::topologicalSort() { stack<int> Stack;  Mark all the vertices as not visited bool *visited = new bool[V]; for (int i = 0; i < V; i++) visited[i] = false;  Call the recursive helper function to store Topological  Sort starting from all vertices one by one for (int i = 0; i < V; i++) if (visited[i] == false) topologicalSortUtil(i, visited, Stack);  Print contents of stack while (Stack.empty() == false) { cout << Stack.top() << " "; Stack.pop(); } }  Driver program to test above functions int main() {  Create a graph given in the above diagram Graph g(6); g.addEdge(5, 2); g.addEdge(5, 0); g.addEdge(4, 0); g.addEdge(4, 1); g.addEdge(2, 3); g.addEdge(3, 1); cout << "Following is a Topological Sort of the given graph \n"; g.topologicalSort(); return 0; }





//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <stack>
//
////class Node {
////
////    friend class Graph;
////
////    int tag;
////    vector<Node*> sonsPaths;
////    Node *parent;
////
////public:
////    Node(): tag(0), sonsPaths(1), parent(nullptr) {sonsPaths[0] = nullptr;};
////    ~Node() {
////        sonsPaths.clear();
////    }
////};
////
////class Graph {
////
////    Node *root;
////    int numberOfNodes;
////
////
////public:
////    Graph(): root(nullptr), numberOfNodes(0) {};
////    ~Graph() {
////        free(root);
////    }
////
//////    void printGraphElement(Node *item) {
//////        cout << item->tag;
//////    }
////
////    Node *CreateGraph () {
////        auto *newItem = new Node;
////        newItem->tag = rand();
////        int numberOfSons = rand()%2;
////        for (int i = 0; i < numberOfSons; i++) {
////            (newItem->sonsPaths).push_back(CreateGraph());
////        }
////        cout << newItem->sonsPaths.size();
////        return newItem;
////    };
////
////    void CreateRoot() {
////        root = CreateGraph();
////    }
////};
//
//bool dfs(int v) {
//    if (Color[v] == 1)return true;
//    if (Color[v] == 2)return false;
//    Color[v] = 1;
//    for (int i = 0; i < Edges[v].size(); i++) {
//        if (dfs(Edges[v].get(i)))return true;
//    }
//    Stack.push(v);
//    Color[v] = 2;
//    return false;
//}
//
//bool topological_sort() {
//    bool Cycle;
//    for (int i = 1; i <= N; i++) {
//        Cycle = dfs(i);
//        if (Cycle)return false;
//    }
//    for (int i = 1; i <= Stack.size(); i++) {
//        Numbers[Stack.pop()] = i;
//    }
//    return true;
//}
//
//int main() {
//    using namespace std;
//    // Declares stacks with default deque base container
//    stack<int> s1, s2;
//
//    s1.push(1);
//    s1.push(3);
//
//    if (s1.empty())
//        cout << "The stack s1 is empty." << endl;
//    else
//        cout << "The stack s1 is not empty." << endl;
//    cout << s1.top() << endl;
//    cout << s1.size() << endl;
//
//    if (s2.empty())
//        cout << "The stack s2 is empty." << endl;
//    else
//        cout << "The stack s2 is not empty." << endl;
//}
//
////int main() {
////    srand((unsigned int)time(nullptr));
////    return 0;
////}