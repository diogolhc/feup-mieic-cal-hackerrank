#include <iostream>
#include <vector>
#include <list>


using namespace std;


bool recur(const vector<pair<int,int>> &weights, int toMake, int weightLeft, int weightIndex, list<pair<int,int>> &sol) {
    int weightSize = (int)weights.size();

    if (weightIndex >= weightSize)
        return false;

    bool res = false;

    int weight = weights[weightIndex].first;
    int quantity = weights[weightIndex].second;
    int newWeightLeft = weightLeft - weight*quantity;

    for (int i = quantity; i > 0 ; i--) {
        int val = weight * i;

        if (val > toMake) {
            continue;

        } else if (val == toMake) {
            // 1 solution found

            for (const pair<int,int> &p : sol) {
                for (int j = 0; j < p.second; j++) {
                    cout << p.first << " + ";
                }
            }
            for (int j = 1; j < i; j++) {
                cout << weight << " + ";
            }
            cout << weight << '\n';
            res = true;

        } else { // if (val < toMake)
            // recursive call

            int newToMake = toMake-val;

            if (newToMake > newWeightLeft) {
                break; // prunning
            } else if (newToMake == newWeightLeft) { // avoid more recursive calls
                // 1 solution found

                for (const pair<int,int> &p : sol) {
                    for (int j = 0; j < p.second; j++) {
                        cout << p.first << " + ";
                    }
                }
                for (int j = 0; j < i; j++) {
                    cout << weight << " + ";
                }
                
                for (int j = weightIndex+1; j < weightSize-1; j++) {
                    for (int k = 0; k < weights[j].second; k++) {
                        cout << weights[j].first << " + ";
                    }
                }
                for (int j = 1; j < weights[weightSize-1].second; j++) {
                    cout << weights[weightSize-1].first << " + ";
                }
                cout << weights[weightSize-1].first << '\n';

                res = true;

            } else {
                list<pair<int,int>> tmp(sol);
                tmp.push_back({weight, i});
                res = recur(weights, toMake-val, newWeightLeft, weightIndex+1, tmp) || res;
            }
        } 
        // else continue;
    }

    // recursive call with no added
    return recur(weights, toMake, newWeightLeft, weightIndex+1, sol) || res;
}



int main() {
    int M;
    while (true) {
        cin >> M;
        if (M == 0)
            break;

        vector<pair<int,int>> vals;
        vals.reserve(12);
        int last = 101, count = 0;

        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int d;
            cin >> d;

            if (d == last)
                count++;
            else {
                if (count > 0) {
                    vals.push_back({last, count});
                }
                count = 1;
                last = d;
            }
        }
        vals.push_back({last, count});

        // process combinations
        cout << "Weights for " << M << ":\n";

        int acum = 0;
        for (pair<int,int> p : vals)
            acum += p.first*p.second;

        list<pair<int,int>> sol;

        if (acum < M || !recur(vals, M, acum, 0, sol))
            cout << "No solutions\n";
    }

    return 0;
}
