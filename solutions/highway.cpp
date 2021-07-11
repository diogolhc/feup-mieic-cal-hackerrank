#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;


struct Edge {
    int c1, c2, weight;

    bool operator<(const Edge &edge) const {
        return weight < edge.weight;
    }
};


struct CitiesDisjointSets {
    int cities[100];
    int C; // 2 <= C <= 99

    void setup() {
        for (int i = 1; i <= C; i ++) {
            cities[i] = -1;
        }
    }

    int find(int n) {
        while (cities[n] > 0) {
            n = cities[n];
        }
        return n;
    }

    void rootUnion(int root1, int root2) {
        if (cities[root1] == cities[root2]) {
            cities[root1] = root2;
            cities[root2]--;

        } else if (cities[root1] < cities[root2]) {
            cities[root2] = root1;

        } else {
            cities[root1] = root2;
        }
    }

    int countSets() {
        int res = 0;
        for (int i = 1; i <= C; i++) {
            res += (cities[i] < 0);
        }
        return res;
    }
};


int main() {
    ios_base::sync_with_stdio(false);


    CitiesDisjointSets cities;
    int indexsUsedBest[3000];
    int indexUsedCount = 0;
    vector<Edge> roads(3000);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        indexUsedCount = 0;
        int R;

        cin >> cities.C >> R;

        for (int j = 0; j < R; j++) {
            cin >> roads[j].c1 >> roads[j].c2 >> roads[j].weight;
        }
        sort(roads.begin(), roads.begin() + R);

        cities.setup();


        int best[2] = {0, INT_MAX};
        
        ////////////////////////////////////////////////////
        for (int j = 0; j < R; j++) {
            int root1 = cities.find(roads[j].c1);
            int root2 = cities.find(roads[j].c2);

            if (root1 == root2) // cities already connected
                continue;
            
            cities.rootUnion(root1, root2);
            best[0] += roads[j].weight;
            indexsUsedBest[indexUsedCount++] = j;

            if (cities.countSets() == 1) {
                break;
            }
        }
        ////////////////////////////////////////////////////

        for (int j = 0; j < indexUsedCount; j++) {

            cities.setup();

            ////////////////////////////////////////////
            int acum = 0;
            int numRoots = 0;

            for (int k = 0; k < R; k++) {
                if (indexsUsedBest[j] == k)
                    continue;
                
                int root1 = cities.find(roads[k].c1);
                int root2 = cities.find(roads[k].c2);

                if (root1 == root2) // cities already connected
                    continue;
                
                cities.rootUnion(root1, root2);
                acum += roads[k].weight;

                if ((numRoots = cities.countSets()) == 1) {
                    break;
                }

            }

            if (numRoots == 1 && acum < best[1])
                best[1] = acum;
            ////////////////////////////////////////////
            
            if (best[0] == best[1]) {
                break;
            }
        }

        cout << best[0] << ' ' << best[1] << '\n';
    }

    return 0;
}
