#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <ctime>

using namespace std;

const string PATH = "C:/Users/mi/CLionProjects/Course3/graph.dot";
const string SNDPATH = "C:/Users/mi/CLionProjects/Course3/sortedGraph.dot";

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
    bool topologicalSortUtil(int v, int color[], stack<int> &Stack);

public:
    Graph() { V = 0; nodeArray = nullptr; };
    Graph(int V);
    void setVertices(int num);
    void addEdge(int v, int w);
    bool topologicalSort();
    void generator();
    void renum(int num, int change);
    void output(const string str);
    void fileOutput();
    void userInput();
    void reuse() {
        node *tmp = nodeArray;
        nodeArray = nullptr;
        delete [] tmp;
    }
    ~Graph() {
        delete [] nodeArray;
    };
};

Graph::Graph(int V) {
    setVertices(V);
}
void Graph::setVertices(int V) {
    this->V = V;
    nodeArray = new node[V];
    for (int i = 0; i < V; i++) {
        nodeArray[i].num = i;
    }
    ofstream fout;
    fout.open(PATH);
    if (!fout.is_open()) cout << "Cannot open the file\n";

    fout << "digraph {\n}";
    fout.close();
}

void Graph::addEdge(int v, int w) {
    nodeArray[v].siblings.push_back(&nodeArray[w]);
    ofstream fout;
    fout.open(PATH, ios::in);
    if (!fout.is_open()) cout << "Cannot open the file\n";

    fout.seekp(-1, ios::end);
    fout << "\t"<< v << " -> " << w << ";\n}";
    fout.close();
    //добавить строку в файл .dot
}

bool Graph::topologicalSortUtil(int v, int color[], stack<int> &Stack) {
    if (color[v] == GREY) {
        cout << "Cycle detected => ";
        return false;
    }
    color[v] = GREY;
    vector <node*> :: iterator i;
    for (i = nodeArray[v].siblings.begin(); i != nodeArray[v].siblings.end(); ++i)
        if (color[(*i)->num] != BLACK) {
            if (!topologicalSortUtil((*i)->num, color, Stack)) return false;
        }

    color[v] = BLACK;
    Stack.push(v);
    return true;
}

void Graph::renum(int num, int change) {
    nodeArray[num].num = change;
}

bool Graph::topologicalSort() {
    stack<int> Stack;

    int *color = new int[V];
    for (int i = 0; i < V; i++)
        color[i] = WHITE;

    for (int i = 0; i < V; i++) {
        if (color[i] == WHITE)
            if (!topologicalSortUtil(i, color, Stack)) {
                cout << "Topological sort of the given graph is impossible\n";
                while (!Stack.empty()) Stack.pop();
                return false;
            }
    }

    int change = 0;
    while (!Stack.empty()) {
        renum(Stack.top(), change);
        change++;
        Stack.pop();
    }
    return true;
}

void Graph :: generator ()
{
    const int PERCENT = 70;
    for (int j = 0; j < V; j++)
        for (int k = j + 1; k < V; k++)
            if ( (rand () % 100) < PERCENT) {
                addEdge(j, k);
            }
}

void Graph::output(const string str) {
    cout << str << endl;
    for (int i = 0; i < V; i++) {
        vector <node*> :: iterator j;
        for (j = nodeArray[i].siblings.begin(); j < nodeArray[i].siblings.end(); j++) {
            cout << nodeArray[i].num << " -> " << (*j)->num << endl;
        }
    }
    cout << endl;
};

void Graph::fileOutput() {
    ofstream fout;
    fout.open(SNDPATH);
    if (!fout.is_open()) cout << "Cannot open the file\n";
    fout << "digraph {\n";
    for (int i = 0; i < V; i++) {
        for (auto j = nodeArray[i].siblings.begin(); j < nodeArray[i].siblings.end(); j++) {
            fout << "\t" << nodeArray[i].num << " -> " << (*j)->num << ";" << endl;
        }
    }
    fout << "}";
    fout.close();
};

void Graph::userInput() {

    cout << "To end your input enter -1 into any of nodes" << endl;
    int node1, node2;
    cout << "Enter the nodes you want to connect" << endl;
    cin >> node1 >> node2;
    cout << node1 << "->" << node2 << endl;
    while (node1 >= 0 && node2 >=0 && node1 <= V && node2 <= V) {
        addEdge(node1, node2);
        cout << "Enter the nodes you want to connect" << endl;
        cin >> node1 >> node2;
        cout << node1 << "->" << node2 << endl;
    }
}

void Menu() {
    cout << "Press (1) to set vertices of the graph" << endl;
    cout << "Press (2) to generate edges" << endl;
    cout << "Press (3) to set edges by yourself" << endl;
    cout << "Press (4) to toposort graph" << endl;
    cout << "Press (5) to test the time of the program" << endl;
    cout << "Press (6) to delete old graph" << endl;
    cout << "Press (0) to finish the program" << endl;
}

int main() {
    srand(time(nullptr));
    Menu();
    Graph g;
    int V;
    char input = 1;
    bool verticesSet = false, edgesSet = false;
    while (input != '0') {
        cout << "Press any key to continue . . ." << endl;
        cin >> input;
        switch (input) {
            case '1': {
                cout << "Pressed 1. Enter the number of vertices in the graph" << endl;
                cin >> V;
                if (V <= 0) break;
                g.setVertices(V);
                verticesSet = true;
                break;
            }
            case '2': {
                if (!verticesSet || edgesSet) {
                    cout << "Graph cannot be generated" << endl;
                    break;
                }
                cout << "Pressed 2. The graph will be generated" << endl;
                g.generator();
                g.output("Generated graph");
                edgesSet = true;
                break;
            }
            case '3': {
                if (!verticesSet || edgesSet) {
                    cout << "Graph cannot be generated" << endl;
                    break;
                }
                cout << "Pressed 3. The graph will be entered by user" << endl;
                g.userInput();
                g.output("Entered graph");
                edgesSet = true;
                break;
            }
            case '4': {
                if (!edgesSet) {
                    cout << "Graph cannot be sorted" << endl;
                    break;
                }
                cout << "Pressed 4. The graph will be sorted" << endl;
                if (g.topologicalSort()) {
                    g.output("Sorted graph");
                    g.fileOutput();
                }
                break;
            }
            case '5': {
                const int q0 = 1000;
                const int v = 10;
                clock_t begin = clock();
                for (int i = 0; i < q0; i++) {
                    Graph e(v);
                    e.generator();
                    e.topologicalSort();
                }
                clock_t end = clock() - begin;
                cout << "Time = " << end << endl;
                break;
            }
            case '6': {
                g.reuse();
                verticesSet = false, edgesSet = false;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}