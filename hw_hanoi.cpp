#include <vector>
#include <iostream>

using namespace std;

auto rotate_lf (auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            result[i][j] = sample[j][n-1-i];
        }
    }

    return result;
};

auto mirror (auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            result[i][j] = sample[i][n-1-j];
        }
    }

    return result;
};

auto zero_rt (auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    return result;
};

auto align_lf (auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(j>i) {
                result[i][j] = 0;
            } else {
                result[i][j] = sample[i][j-i+n-1];
            }
        }
    }

    return result;
};

auto connect_lr (auto lf, auto rt) {
    int n = lf.size();
    vector<vector<int>> result = lf;
    for(int i=0; i<n; i++) {
        result[i].push_back(0);
        result[i].insert(result[i].end(),rt[i].begin(),rt[i].end());
    }
    return result;
}
auto connect_ud (auto up, auto dn) {
    int n = up.size();
    vector<vector<int>> result = up;
    vector<int> row = {1};
    row.insert(row.end(),n-1,0);
    row.push_back(1);
    row.insert(row.end(),n,0);
    result.push_back(row);
    result.insert(result.end(),dn.begin(),dn.end());
    return result;
}

vector<vector<int>> sample = {{1,0,0}, {1, 1, 0}, {1, 0, 1}};

auto hanoi (int n) {
    if(n==1) return sample;

    auto last = hanoi(n-1);
    auto zero = zero_rt(last);
    auto rota = rotate_lf(last);
    auto dnlf = mirror(rota);
    auto dnrt = align_lf(rota);
    auto up_h = connect_lr(last, zero);
    auto dn_h = connect_lr(dnlf, dnrt);
    return connect_ud(up_h, dn_h);
}

void draw (auto sample) {
    int n = sample.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++)
            cout << " ";
        if(i%2 == 0) {
            for(int j=0; j<n; j++) {
                if(j%2 == 0)
                    cout << (sample[i][j] ? "@" : " ");
                else
                    cout << (sample[i][j] ? "---" : "   ");
            }

        } else {
            for(int j=0; j<n; j++) {
                if(j%2 == 0)
                    cout << (sample[i][j] ? "/ " : "  ");
                else
                    cout << (sample[i][j] ? "\\ " : "  ");
            }
        }    
        cout << endl;       
    }
}

int main() {
    int n;
    cin >> n;
    auto result = hanoi(n);
    draw(result);
    return 0;
}
