#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    char str[1001];
    int aux[1001];
    int n;
    while (scanf("%s%n", str, &n) != EOF) {
        getchar_unlocked(); // '\n'

        for (int i = 0; i <= n; i++) {
            aux[i] = i;
        }

        for (int i = n-1; i >= 0; i--) { // reversed string
            int old = aux[0];
            aux[0] = n - i;
            for (int j = 0; j < n; j++) { // actual string
                int temp = aux[j+1];
                aux[j+1] = 1 + min({old - (str[i] == str[j]), aux[j], aux[j+1]});
                old = temp;
            }
        }
        
        printf("%d\n", aux[n]/2);
    }
    return 0;
}
