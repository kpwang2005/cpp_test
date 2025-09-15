#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <ranges>

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

  for (auto vec : myMap | views::transform( [] (auto i) { auto [key,value] = i; return key * key; } )) {                          
    cout << "Vec: " << vec << endl;
  }

  for (auto [key, value] : myMap | views::filter( [] (auto i) { auto [key,value] = i; return key > 1; } )) {                          
    cout << "Key: " << key << ", Value: " << value << endl;
  }



  map<int,list<int>> myMap2;
  myMap2[1].push_back(6);
  myMap2[1].push_back(7);
  myMap2[1].push_back(8);
  myMap2[1].pop_front();                                
   
  cout << myMap2[1].front() << endl << myMap2[1].back() << endl;

  return 0;
}