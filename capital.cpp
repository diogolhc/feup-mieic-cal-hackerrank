#include <iostream>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    char cities[26][11];
    int dist[26][26];
    int C, R;
    while (!cin.eof()) {
        cin >> C >> R;

        for (int i = 1; i <= C; i++) {
            cin >> cities[i];
        }

        for (int i = 1; i <= C; i++) {
            for (int j = 1; j <= C; j++) {
                dist[i][j] = (i != j) * INT_MAX;
            }
        }

        for (int i = 0; i < R; i++) {
            int n, m, d;
            cin >> n >> m >> d;
            dist[n][m] = dist[m][n] = d;
        }

        for (int i = 1; i <= C; i++) {
            for (int j = 1; j <= C; j++) {
                for (int k = 1; k <= C; k++) {
                    if (!(dist[j][i] == INT_MAX || dist[i][k] == INT_MAX))
                        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
            }
        }

        int bestI = -1;
        int minBest = INT_MAX;
        for (int i = 1; i <= C; i++) {
            int acum = 0;
            for (int j = 1; j <= C; j++) {
                if (dist[i][j] == INT_MAX) {
                    acum = INT_MAX;
                    break;
                }
                acum += dist[i][j];
            }
            if (acum < minBest) {
                bestI = i;
                minBest = acum;
            }
        }

        cout << cities[bestI] << '\n';
    }
    
    return 0;
}
