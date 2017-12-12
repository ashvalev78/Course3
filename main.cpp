#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <ctime>
#include <vector>

using namespace std;

const string PATH = "/Users/artemkaloev/Desktop/study/Course3/graph.dot";

enum color {
    WHITE,
    GREY,
    BLACK
};

struct node {
    int num;
    vector<node*> siblings;
};

class Graph {
    int V;
    node *nodeArray;
//    list<int> *adj;
    bool topologicalSortUtil(int v, int color[], stack<int> &Stack);

public:
    Graph(int V);
//    Graph(const Graph &old);
    void addEdge(int v, int w);
    bool topologicalSort();
    void generator();
    void renum(int num);
    //деструктор
};

Graph::Graph(int V) {
    this->V = V;
    nodeArray = new node[V];
    for (int i = 0; i < V; i++) {
        nodeArray[i].num = i;
    }
//    ofstream fout;
//    fout.open(PATH);
//    if (!fout.is_open()) cout << "Cannot open the file\n";
//
//    fout << "digraph {\n}";
//    fout.close();
    //очистить файл .dot
    //добавить инициализацию графа в файл .dot
}

void Graph::addEdge(int v, int w) {
    cout << v << "->" << w << endl;
    nodeArray[v].siblings.push_back(&nodeArray[w]);
//    for (auto i = nodeArray[v].siblings.begin(); i < nodeArray[v].siblings.end(); i++)
//        cout << (*i)->num;
//
//    ofstream fout;
//    fout.open(PATH, ios::in);
//    if (!fout.is_open()) cout << "Cannot open the file\n";
//
//    fout.seekp(-1, ios::end);
//    fout << "\t"<< v << " -> " << w << ";\n}";
//    fout.close();
    //добавить строку в файл .dot
}

bool Graph::topologicalSortUtil(int v, int color[], stack<int> &Stack) {
    cout << "v = " << v << endl;
    if (color[v] == GREY) {
        cout << "Cycle detected => ";
        return false;
    }
//    cout << "OK" << endl;
    color[v] = GREY;
//    cout << "OK2" << endl;
    for (auto i = nodeArray[v].siblings.begin(); i != nodeArray[v].siblings.end(); ++i)
        if (color[(*i)->num] != BLACK) {
            if (!topologicalSortUtil((*i)->num, color, Stack)) return false;
        }

    color[v] = BLACK;
    Stack.push(v);
    return true;
}

void Graph::renum(int num) {
    
}

bool Graph::topologicalSort() {
    stack<int> Stack;

    auto *color = new int[V];
    for (int i = 0; i < V; i++)
        color[i] = WHITE;

    for (int i = 0; i < V; i++) {
        if (color[i] == WHITE)
            if (!topologicalSortUtil(i, color, Stack)) {
                cout << "Topological sort of the given graph is impossible";
                while (!Stack.empty()) Stack.pop();
                return false;
            }
    }

    cout << "\nFollowing is a Topological Sort of the given graph:\n";

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
    return true;
}

void Graph :: generator ()
{
    const int PERCENT = 40;
    for (int j = 0; j < V; j++)
        for (int k = j + 1; k < V; k++)
            if ( (rand () % 100) < PERCENT) {
                addEdge(j, k);
            }
}

int main() {
    srand(time(nullptr));
    // Create a graph given in the above diagram
    Graph g(15);
    g.generator();
    g.topologicalSort();

//    Graph n(g);
//    n.topologicalSort();

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