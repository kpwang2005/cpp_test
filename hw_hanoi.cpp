#include <vector>

using namespace std;

auto rotate_lf = [](auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            result[i][j] = sample[j][n-1-i];
        }
    }

    return result;
};

auto mirror = [](auto sample) {
    int n = sample.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            result[i][j] = sample[i][n-1-j];
        }
    }

    return result;
};

auto align_lf = [](auto sample) {
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

int main() {
    vector<vector<int>> sample = {{1,0,0}, {1, 1, 0}, {1, 0, 1}};
    auto rotated = rotate_lf(sample);
    auto mirrored = mirror(rotated);
    auto aligned = align_lf(rotated);
    return 0;
}