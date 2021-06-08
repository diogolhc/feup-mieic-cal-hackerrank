#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Scar_t {
    long double from, to;
    bool operator<(const Scar_t &s2) const {
        return from < s2.from;
    }
};


void solve(vector<Scar_t> &scars, int n, long double len) {
    long double last = 0;
    int count = 0;
    int fromIndex = 0;
    while (true) {
        long double best = last;
        int i = fromIndex;
        for ( ; i < n; i++) {
            if (scars[i].from > last)
                break;
    
            if (scars[i].to <= best)
                continue;
            
            best = scars[i].to;
        }
        
        if (best == last) {
            printf("X\n");
            return;
        }

        fromIndex = i;
        count++;
        last = best;
        
        if (last >= len) {
            printf("%d\n", count);
            return;
        }
    }
}


int main() {
    vector<Scar_t> scars;
    scars.reserve(100);

    int n, l, w, nValid;
    long double whalfsquared;
    while (!cin.eof()) {
        scars.clear();

        cin >> n >> l >> w;
        whalfsquared = pow(((long double)w/2), 2);
        int d, r;
        
        nValid = 0;
        for (int i = 0; i < n; i++) {
            cin >> d >>r;
            long double u = r*r - whalfsquared;
            if (u >= 0) {
                u = sqrt(u);
                scars[nValid++] = {d-u, d+u};
            }
        }

        sort(scars.begin(), scars.begin() + nValid);
        solve(scars, nValid, (long double)l);
    }

    return 0;
}
