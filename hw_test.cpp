#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <ranges>


using namespace std;
using namespace std::ranges;

void insert_a(int node_a, map<int, list<int>>& myMap, int& line) {
    vector<int> empty;
    auto is_lt_a = [node_a](auto i) { return i < node_a; };
    for (auto key : myMap | views::keys | views::filter(is_lt_a)) {
        if (myMap[key].front() == node_a) {
            myMap[key].pop_front();
            if(myMap[key].empty()) {
                empty.push_back(key);
            }
            cout << "Node A: " << node_a << ", Node B: " << key << endl;
            line++;
        }
    }
    for (auto key : empty) {
        myMap.erase(key);
    }
}

int main() {
    ifstream fin("edges.txt");
    int n;
    cin >> n;
    map<int, list<int>> myMap;
    int line = 0;
    int node_a, node_b;
    int node_t = 0;
    while (line < n && fin >> node_a >> node_b) {
        if (node_a > node_t) {
            insert_a(node_a, myMap, line);
        }
        node_t = node_a;
        myMap[node_a].push_back(node_b);    
        cout << "Node A: " << node_a << ", Node B: " << node_b << endl;
        line++;
    }
    fin.close();

    set<int> mySet;
    for (auto key : myMap | views::keys) { 
        cout << "Key: " << key << ", Count: " << myMap[key].size() << endl;
        for (auto node : myMap[key]) {
            mySet.insert(node);
        }
    }

    for (auto node : mySet) {
        insert_a(node, myMap, line);
    }

    return 0;
}