#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <ranges>
#include <numeric>

using namespace std;
using namespace std::ranges;

int main() {
  vector<string> msg {"Hello", "C++", "world"};
  for(const auto& word : msg) {                                     //c++11
    cout << word << " ";
  }
  cout << endl;
 
  map<int, string> myMap {{1, "One"}, {2, "Two"}, {3, "Three"}};
  
  //c++14: (auto i)
  //c++17: [key,value]
  //c++20: views |

  auto op_sqr = [] (auto i) { return i * i; };
  for (auto vec : myMap | views::keys | views::transform(op_sqr)) {
    cout << "Vec: " << vec << endl;
  }

  auto is_gt1 = [] (auto i) { return i > 1; };
  for (auto key : myMap | views::keys | views::filter(is_gt1)) {                          
    cout << "Key: " << key << ", Value: " << myMap[key] << endl;
  }

  auto op_sum = [] (auto acc, auto i) { auto [key,value] = i; return acc + key; };
  cout << "Sum: " << reduce(myMap.begin(), myMap.end(), 0, op_sum) << endl;

  map<int,list<int>> myMap2;
  myMap2[1].push_back(6);
  myMap2[1].push_back(7);
  myMap2[1].push_back(8);
  myMap2[1].push_back(9);
  myMap2[1].pop_front();                                
   
  cout << myMap2[1].front() << endl << myMap2[1].back() << endl;

  return 0;
}
