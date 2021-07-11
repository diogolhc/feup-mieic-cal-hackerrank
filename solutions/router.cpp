#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF UINT64_MAX;

struct Edge;

struct Node {
    unsigned long long id;
    vector<Edge *> incoming;
    vector<Edge *> outgoing;
    bool visited;
    Edge *path;
    Node()=default;
    Node(unsigned long long id) {
        this->id = id;
        this->visited = false;
        this->path = NULL;
    }
};

struct Edge {
    unsigned long long flow;
    unsigned long long capacity;
    Node *orig;
    Node *dest;
    Edge(unsigned long long capacity, Node *orig, Node *dest) {
        this->flow = 0;
        this->capacity = capacity;
        this->orig = orig;
        this->dest = dest;
        orig->outgoing.push_back(this);
        dest->incoming.push_back(this);
    }
};

struct Graph {
    vector<Node *> nodes;
    vector<Edge *> edges;
    unsigned long long M;

    // use with (1 < id && id < M)
    Node *addNode(unsigned long long id) {
        if (id >= M+2) {
            nodes[id-2] = new Node(id);
            return nodes[id-2];
        } else {
            nodes[id] = new Node(id);
            return nodes[id];
        }
    }
    
    Node *getNode(unsigned long long id) {
        if (id == 1)
            return nodes[0];
        else if (id == M)
            return nodes[1];
        else if (id >= M+2)
            return nodes[id-2];

        return nodes[id];
    }
};

void testAndVisit(queue<Node*> &q, Edge *e, Node *w, unsigned long long residual) {
    if (!w->visited && residual > 0) {
        w->visited = true;
        w->path = e;
        q.push(w);
    }
}

bool findAugmentationPath(Graph *g, Node *s, Node *t) {
    for (Node *n: g->nodes) {
        n->visited = false;
    }
    s->visited = true;
    queue<Node *> q;
    q.push(s);
    while(!q.empty() && !t->visited) {
        Node * v = q.front();
        q.pop();
        for (Edge *e: v->outgoing) {
            testAndVisit(q, e, e->dest, e->capacity - e->flow);
        }
        for (Edge *e: v->incoming) {
            testAndVisit(q, e, e->orig, e->flow);
        }
    }
    return t->visited;
}

unsigned long long findMinResidualAlongPath(Graph *g, Node *s, Node *t) {
    unsigned long long f = INF;
    Node *v =  t;
    while (v != s) {
        Edge *e = v->path;
        if (e->dest == v) {
            f = min(f, e->capacity - e->flow);
            v = e->orig;
        } else {
            f = min(f, e->flow);
            v = e->dest;
        }
    }
    return f;
}

void augmentFlowAlongPath(Graph *g, Node *s, Node *t, unsigned long long f) {
    Node *v = t;
    while (v != s) {
        Edge *e = v->path;
        if (e->dest == v) {
            e->flow += f;
            v = e->orig;
        } else {
            e->flow -= f;
            v = e->dest;
        }
    }
}

unsigned long long fordFulkerson(Graph *g, Node *s, Node *t) {
    for (Edge *e: g->edges) {
        e->flow = 0;
    }
    unsigned long long tot = 0;
    while (findAugmentationPath(g, s, t)) {
        unsigned long long f = findMinResidualAlongPath(g, s, t);
        augmentFlowAlongPath(g, s, t, f);
        tot += f;
    }
    return tot;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        Graph g;
        int M = -1, C = -1;
        cin >> M >> C;
        if (M == 0 && C == 0) {
            break;
        }
        g.edges.reserve(2*C+2*M);
        g.M = M;

        //add s & t
        g.nodes.push_back(new Node(1)); // node s
        g.nodes.push_back(new Node(M)); // node t
        Node *node_s = g.nodes[0];
        Node *node_t = g.nodes[1];

        g.nodes.resize(2*M-2);

        for (int i = 0; i < M-2; i++) {
            int id;
            unsigned long long h;
            cin >> id >> h;

            Node *in = g.addNode(id); //in node
            Node *out = g.addNode(M+id); //out node
            g.edges.push_back(new Edge(h, in, out));
        }

        for (int i = 0; i < C; i++) {
            int id1, id2;
            unsigned long long h;
            cin >> id1 >> id2 >> h;

            //add 2x each conection except for s & t
            if (id1 == 1 || id2 == 1) { // node s
                g.edges.push_back(new Edge(h, node_s, g.getNode(id2*(id1==1) + id1*(id2==1))));
            } else if (id1 == M || id2 == M) { // node t
                g.edges.push_back(new Edge(h, g.getNode((M+id1)*(id2==M) + (M+id2)*(id1==M)), node_t));
            } else {
                g.edges.push_back(new Edge(h, g.getNode(M+id1), g.getNode(id2)));
                g.edges.push_back(new Edge(h, g.getNode(M+id2), g.getNode(id1)));
            }
        }

        unsigned long long res =  fordFulkerson(&g, node_s, node_t);
        cout << res << " hour";
        if (res != 1)
            cout << 's';
        cout << '\n';
    }

    return 0;
}
