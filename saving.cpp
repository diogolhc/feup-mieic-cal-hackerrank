#include <iostream>
#include <list>
#include <climits>

using namespace std;

#define INF INT_MAX;
#define NODES_PER_NODE 101 // 1 + 100
#define MAX_NODES 101000 // NODES_PER_NODE*1000
#define MAX_CAPACITY 100 // 1 <= F <= 100


struct Edge;

struct Node {
    int id;
    list<Edge *> incoming;
    list<Edge *> outgoing;
    int dist;
    int index;
    int stateIndex;

    Node(int id, int stateIndex) {
        this->id = id;
        this->stateIndex = stateIndex;
        this->dist = INF;
        this->index = 0;
    }
};

struct Edge {
    int weight;
    Node *orig;
    Node *dest;

    Edge(int weight, Node *orig, Node *dest) {
        this->weight = weight;
        this->orig = orig;
        this->dest = dest;
        orig->outgoing.push_back(this);
        dest->incoming.push_back(this);
    }
};

struct Graph {
    Node* nodes[MAX_NODES];
    int i;

    Graph() {
        this->i = 0;
    }

    Node *addNode(int id, int stateIndex) {
        nodes[i] = new Node(id, stateIndex);
        return nodes[i++];
    }

    void resetNodes() {
        for (int j = 1; j < i; j++) {
            nodes[j]->dist = INF;
            nodes[j]->index = 0;
        }
    }
};

struct MPQueue {
    Node *nodes[MAX_NODES];
    int index = 1;

    void heapUp(int i) {
        Node *current = nodes[i];
        while (i > 1 && current->dist < nodes[i/2]->dist) {
            nodes[i] = nodes[i/2];
            nodes[i]->index = i;
            i /= 2;
        }
        nodes[i] = current;
        nodes[i]->index = i;
    }

    void heapDown(int i) {
        Node *current = nodes[i];
        while (true) {
            int j = i*2;
            if (j >= index) break;
            if (j+1 < index && nodes[j+1]->dist < nodes[j]->dist) ++j;
            if (nodes[j]->dist >= current->dist) break;
            nodes[i] = nodes[j];
            nodes[i]->index = i;
            i = j;
        }
        nodes[i] = current;
        nodes[i]->index = i;
    }

    void insert(Node * node) {
        nodes[index++] = node;
        heapUp(index-1);
    }

    Node * extractMin() {
        Node * ret = nodes[1];
        nodes[1] = nodes[--index];
        if (index > 1) heapDown(1);
        ret->index = 0;
        return ret;
    }

    void insertOrDecreaseKey(Node *node) {
        if (node->index == 0) insert(node);
        else heapUp(node->index);
    }
    
    bool empty() {
        return index == 1;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    
    Graph graph;
    MPQueue queue;

    int V, E, Q;
    while(!cin.eof()) {
        graph.i = 0;
        cin >> V >> E;

        int cost;
        for (int i = 0; i < V; i++) {
            cin >> cost;

            Node *prev = graph.addNode(i*NODES_PER_NODE, 0);

            for (int j = 1; j <= MAX_CAPACITY; j++) {
                Node *current = graph.addNode(i*NODES_PER_NODE+j, j);
                new Edge(cost, prev, current);
                prev = current;
            }
        }

        int v1, v2, w;
        for (int i = 0; i < E; i++) {
            cin >> v1 >> v2 >> w;

            for (int j = w; j < NODES_PER_NODE; j++) {
                Node *start1 = graph.nodes[v1*NODES_PER_NODE + j];
                Node *start2 = graph.nodes[v2*NODES_PER_NODE + j];
                new Edge(0, start1, graph.nodes[v2*NODES_PER_NODE + j - w]);
                new Edge(0, start2, graph.nodes[v1*NODES_PER_NODE + j - w]);
            }
        }

        cin >> Q;
        int F, v0, vf;
        for (int i = 0; i < Q; i++) {
            cin >> F >> v0 >> vf;

            // reset
            graph.resetNodes();
            queue.index = 1;

            Node *start = graph.nodes[v0*NODES_PER_NODE];
            start->dist = 0;
            queue.insert(start);

            bool notFound = true;
            while (!queue.empty()) {
                Node *min = queue.extractMin();

                if ((min->id - min->stateIndex) == (vf*NODES_PER_NODE)) {
                    // found path
                    cout << min->dist << ' ';
                    notFound = false;
                    break;
                }

                for (Edge *e: min->outgoing) {
                    if (e->dest->stateIndex > F) {
                        // cannot refuell more
                        continue;
                    }

                    if (min->dist + e->weight < e->dest->dist) {
                        e->dest->dist = min->dist + e->weight;
                        queue.insertOrDecreaseKey(e->dest);
                    }
                }
            }

            if (notFound)
            cout << 'X' << ' ';
        }
        cout << '\n';
    }

    return 0;
}
