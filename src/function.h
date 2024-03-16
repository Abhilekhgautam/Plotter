#pragma once
#include <cctype>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

class Function {
private:
  // callable function 
  std::function<double(int)> m_function;
  char m_variable;

  std::vector<std::string> m_params;

public:
  Function() = default;
  // no mechanism to confirm a single variable
  Function(char *str) { assign_lamdda(str); }

  // todo: look a way with modern C++.. 
  void assign_lamdda(char *str) {
    char *current = str;
    char *next = str;
    // error prone .. walk carefully
    while (*current != '\0') {
      if (isspace(*current)) {
        next++;
        current++;
      } else if (isdigit(*current)) {
        int num = int(*current) - 48;
        while (isdigit(*(++next))) {
          num = num * 10 + (*next - 48);
          current++;
        }
        current = next;
        m_params.emplace_back(std::to_string(num));
      } else if (isalpha(*current)) {
        // for future to check if its a single var or not
        m_variable = *current;
        // std::string temp(m_variable);
        m_params.emplace_back("x");
        current++;
        next++;
      } else if ((*current) == '+') {
        m_params.emplace_back("+");
        current++;
        next++;
      } else if ((*current) == '-') {
        m_params.emplace_back("-");
        current++;
        next++;
      } else if ((*current) == '*') {
        m_params.emplace_back("*");
        current++;
        next++;
      } else if ((*current) == '/') {
        m_params.emplace_back("/");
        current++;
        next++;
      }
    }
    m_function = [&](int x) -> double {
      double result = 0;
      char current_op = '*';
      bool no_op_read = true;
      for (const auto &elt : m_params) {
        if (isdigit(elt[0])) {
          if (no_op_read)
            result = std::stoi(elt);
          else {
            result = perform_operation(result, std::stoi(elt), current_op);
          }
        } else if (elt == "+") {
          current_op = '+';
          no_op_read = false;
        } else if (elt == "-") {
          no_op_read = false;
          current_op = '-';
        } else if (elt == "/") {
          no_op_read = false;
          current_op = '/';
        } else if (elt == "*") {
          no_op_read = false;
          current_op = '*';
        } else if (isalpha(elt[0])) {
          if (no_op_read)
            result = 1;
          result = perform_operation(result, x, current_op);
        }
      }
      return result;
    };
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
