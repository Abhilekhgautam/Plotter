#pragma once

#include <algorithm>
#include <string_view>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

bool IsOperator(char c){
  if(c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '(' || c == ')') return true;
  else return false;
}

template <char Var>
class Function {
private:
  // callable function 
  std::function<double(int)> m_function;
  char m_variable;
  std::string m_function_str;
  // 0 -> Variable
  // 1 -> digit
  // 2 -> op
  // 3 -> space
  std::map<char, int> m_lookup_table;

public:
  // no mechanism to confirm a single variable
  Function(std::string str) {
    m_function_str = str;
    lexer(); 
  }

  // todo: look a way with modern C++.. 

  void lexer(){
   // trim spaces from the beginning
   m_function_str.erase(m_function_str.begin(), std::find_if(m_function_str.begin(), m_function_str.end(), [](char ch){
      return !std::isspace(ch);			   
    })); 
   // trim spaces from the end 
   m_function_str.erase(std::find_if(m_function_str.rbegin(), m_function_str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), m_function_str.end());
   for(const auto& elt: m_function_str){
      // ignore whitespaces	   
      if(std::isspace(elt)){
	 m_lookup_table.insert({elt, 3});     
      }
      else if(std::isdigit(elt)){
	 m_lookup_table.insert({elt, 1});    
      }
      else if(std::isalpha(elt)){
	 m_lookup_table.insert({elt, 0});     
      }
      else if(IsOperator(elt)){
	 m_lookup_table.insert({elt, 2});     
      }
   }
  }

   void parse(){
     
   }

  void assign_lamdda(std::string str) {
    	  
  }

  double Evaluate(int input) { return m_function(input); }

  void debug() {
    for (const auto &elt : m_params)
      std::cout << elt << '\n';
  }
private:
  double perform_operation(const double &a, const double &b, const char op) {
    if (op == '+')
      return a + b;
    if (op == '-')
      return a - b;
    if (op == '*')
      return a * b;
    if (op == '/')
      return a / b;
  }
};
