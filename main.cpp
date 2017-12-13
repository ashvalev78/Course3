#include <iostream>
#include <fstream>
#include <stack>
#include <ctime>
#include <vector>

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
    Graph(int V);
    void addEdge(int v, int w);
    bool topologicalSort();
    void generator();
    void renum(int num, int change);
    void output();
    void fileOutput();
    void userInput();
    ~Graph() {
        delete [] nodeArray;
    };
};

Graph::Graph(int V) {
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
    //очистить файл .dot
    //добавить инициализацию графа в файл .dot
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
    for (auto i = nodeArray[v].siblings.begin(); i != nodeArray[v].siblings.end(); ++i)
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
    int change = 0;
    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        renum(Stack.top(), change);
        change++;
        Stack.pop();
    }
    cout << endl;
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

void Graph::output() {
    for (int i = 0; i < V; i++) {
        cout << nodeArray[i].num << " ";
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
            cout << nodeArray[i].num << "->" << (*j)->num << endl;
            fout << "\t" << nodeArray[i].num << "->" << (*j)->num << endl;
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
    cout << "--------------------------------------------------------------" << endl;
    cout << "If you want to generate graph automatically, press 1" << endl;
    cout << "If you want to input your own graph, press 2" << endl;
//    cout << "If you want to sort the graph, press 3" << endl;
    cout << "If you want to check the time complexity, press 3" << endl;
    cout << "If you want to see menu again, press 4" << endl;
    cout << "If you want to exit, press q" << endl;
    cout << "--------------------------------------------------------------" << endl;
}

int main() {
    srand(time(nullptr));
    char ch = 0;
    Menu();
    while (ch != 'q') {
        cin >> ch;
        switch (ch) {
            case '1': {
                cout << "You have chosen to generate the graph" << endl;
                cout << "Enter the size of the graph" << endl;
                int size;
                cin >> size;
                cout << "Your size is " << size << endl;
                Graph g(size);
                g.generator();
                cout << "Do you want to sort this graph? y/n" << endl;
                char answer;
                cin >> answer;
                if (answer == 'y') {
                    g.topologicalSort();
                } else {
                    cout << "OK, leaving this paragraph" << endl;
                }
                cout << "--------------------------------------------------------------" << endl;
            } break;
            case '2': {
                cout << "You have chosen to enter the graph" << endl;
                cout << "Enter the size of the graph" << endl;
                int size;
                cin >> size;
                cout << "Your size is " << size << endl;
                Graph g(size);
                g.userInput();
                cout << "Do you want to sort this graph? y/n" << endl;
                char answer;
                cin >> answer;
                if (answer == 'y') {
                    g.topologicalSort();
                } else {
                    cout << "OK, leaving this paragraph" << endl;
                }
                cout << "--------------------------------------------------------------" << endl;
            } break;
            case '3':
                for (int i = 0; i < 1000; i++) {
                    Graph g(10);
                    g.generator();
                    g.topologicalSort();
                }
                break;
            case '4': Menu();
                break;
            default: {
                cout << "You have chosen the wrong option, please try again";
            } break;
        }
    }
    Graph g(8);
    g.generator();
    g.topologicalSort();
    g.output();
    g.fileOutput();

    return 0;
}