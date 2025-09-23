#include <iostream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

auto pop_front_value(list<string>& tokens) { 
        auto token = tokens.front(); 
        tokens.pop_front();
        return token;
}

int eval_modify(list<string>& tokens) {
    string n;
    int result = 0;
    int product;

    // first term
    n= pop_front_value(tokens);
    if (n == "(") {
        product = eval_modify(tokens);
    } else {
        product = stoi(n);
    }

    // process rest
    n= pop_front_value(tokens);  // different from eval(): >> vs pop
    while (n != ")") {           // different from eval(): >> vs pop
        if (n == "+") {
            result += product;
            n= tokens.front();
            tokens.pop_front();
            if (n == "(") {
                product = eval_modify(tokens);
            } else {
                product = stoi(n);
            }
        } else if (n == "*") {
            n= tokens.front();
            tokens.pop_front();
            if (n == "(") {
                product *= eval_modify(tokens);
            } else {
                product *= stoi(n);
            }
        }
        n= pop_front_value(tokens);  // different from eval(): >> vs pop
    }

    result += product;
    return result;
}

int eval(stringstream& sin) {
    string n;
    int result = 0;
    int product;

    // first term
    sin >> n;
    if (n == "(") {
        product = eval(sin);
    } else {
        product = stoi(n);
    }

    // process rest
    while (sin >> n && n != ")") {
        if (n == "+") {
            result += product;
            sin >> n;
            if (n == "(") {
                product = eval(sin);
            } else {
                product = stoi(n);
            }
        } else if (n == "*") {
            sin >> n;
            if (n == "(") {
                product *= eval(sin);
            } else {
                product *= stoi(n);
            }
        }
    }

    result += product;
    return result;
}

int calc_expression(const vector<string>& tokens) {
    int tmp_val;
    list<int> mul_vals;
    list<int> add_vals;
    for (const auto& token : tokens) {
        if (isdigit(token[0])) {
            tmp_val = stoi(token);
        } else {
            switch (token[0]) {
                case '+': {
                    if(mul_vals.empty()) {
                        for(const auto& v : add_vals) {
                            tmp_val += v;
                        }
                        add_vals.clear();
                        add_vals.push_back(tmp_val);
                    } else {
                        add_vals.push_back(tmp_val *= mul_vals.back());
                        mul_vals.clear();
                    }
                    break;
                }
                case '*': {
                    if(mul_vals.empty()) {
                        mul_vals.push_back(tmp_val);
                    } else {
                        mul_vals.push_back(tmp_val *= mul_vals.back());
                        mul_vals.pop_front();
                    }
                    break;
                }
            }
        }
    }

    if(mul_vals.size()) {                
        tmp_val *= mul_vals.back();
    }

    for(const auto& v : add_vals) {
        tmp_val += v;
    }

    return tmp_val;
}


int main() {
    
    string sample = "(3 + 4 ) * 5 + 6 + 7 * 8";

    // Tokenize the string
    istringstream iss(sample);
    string token;
    vector<string> tokens;
    while (iss >> token) {
        if(token.back()==')' && token.size()>1) {
            int count = 1;
            token = token.substr(0, token.size()-1);

            while(token.back()==')' && token.size()>1) {
                count++;
                token = token.substr(0, token.size()-1);
            }

            tokens.push_back(token);
            for(int i=0; i<count; i++) {
                tokens.push_back(")");
            }
            continue;
        }

        while(token.front()=='(' && token.size()>1) {
            tokens.push_back("(");
            token = token.substr(1);
        }
        tokens.push_back(token);
    }

    vector<string> working_tokens;
    list<vector<string>> stack_tokens;
    // Print the tokens
    for (const auto& token : tokens) {
        switch (token[0]) {
            case '(': {
                stack_tokens.push_back(working_tokens);
                working_tokens.clear();
                break;
            }
            case ')': {
                int result = calc_expression(working_tokens);
                working_tokens = stack_tokens.back();
                stack_tokens.pop_back();
                working_tokens.push_back(to_string(result));
                break;
            }
        }
        working_tokens.push_back(token);
        cout << "Token: " << token << endl;
    }

    cout << "Result: " << calc_expression(tokens) << endl;
    cout << "Result: " << calc_expression(working_tokens) << endl;

    // method 1: stringstream
    std::stringstream sin;
    for (const auto& t : tokens) sin << t << " ";
    std::cout << "Andy: " << eval(sin) << endl;

    // method 2: list<string>
    list<string> list_tokens(tokens.begin(), tokens.end());
    cout << "Andy:" << eval_modify(list_tokens) << endl;

    return 0;
}
