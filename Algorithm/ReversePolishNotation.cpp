// https://en.wikipedia.org/wiki/Shunting-yard_algorithm
// http://quiz.geeksforgeeks.org/stack-set-2-infix-to-postfix/
// http://www.geeksforgeeks.org/expression-evaluation/

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stack>
#include <vector>
#include <unordered_map>


class OperatorFactory {
public:
  OperatorFactory() {}

  void RegisterOperator(const std::string & op_str, unsigned int priority) {
    m_operator_to_priority[op_str] = priority;
  }

  unsigned int GetPriority(const std::string & op_str) {
    return m_operator_to_priority.count(op_str) == 0? 0 : m_operator_to_priority[op_str];
  }

private:
  std::unordered_map<std::string, unsigned int> m_operator_to_priority;
};

std::vector<std::string> ConvertToReversePolishNotation(const std::vector<std::string> & infix_tokens) {
  OperatorFactory op_factory;
  op_factory.RegisterOperator("+", 1);
  op_factory.RegisterOperator("-", 1);
  op_factory.RegisterOperator("*", 2);
  op_factory.RegisterOperator("/", 2);

  std::vector<std::string> reval;
  std::vector<std::string> operators; // we use the vector like a stack, =P
  for (const std::string & token : infix_tokens) {
    if (token.empty()) continue;

    if ( std::isdigit(token[0]) ) {
      // If the token is a number, then push it to the output
      reval.push_back(token);
    } else {

      if (token == "(") {
        operators.push_back(token);
      } else if (token == ")") {
        // keep popping operators out from the stack until a "(" get popped out
        while (!operators.empty() && operators.back() != "(") {
          reval.push_back(operators.back());
          operators.pop_back();
        }

        operators.pop_back(); // pop out "("
      } else {
        // keep popping operators out from the stack as long as the top operator's priority >= current token
        while (!operators.empty() && op_factory.GetPriority( operators.back() ) >=  op_factory.GetPriority(token) ) {
          reval.push_back(operators.back());
          operators.pop_back();
        }

        operators.push_back(token);
      }
    }
  }

 while (!operators.empty()) {
    reval.push_back(operators.back());
    operators.pop_back();
  }
  return reval;
}

std::vector<std::string> StringToTokens(const std::string & str) {
  std::vector<std::string> tokens;
  std::istringstream iss(str);
  std::string token("");
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string TokensToString(const std::vector<std::string> & tokens) {
  std::ostringstream oss;
  const std::size_t tokens_size(tokens.size());
  for (std::size_t i = 0; i < tokens_size; ++i) {
    if (i != tokens_size - 1) oss << tokens[i] << ' ';
    else oss << tokens[i];
  }
  return oss.str();
}

void UnitTest() {
  std::vector<std::string> infix_tokens = StringToTokens("3 + 4 * 2 / ( 1 - 5 )");
  std::vector<std::string> rpn_tokens = ConvertToReversePolishNotation(infix_tokens);
  assert( TokensToString(rpn_tokens) == "3 4 2 * 1 5 - / +" );

  infix_tokens = StringToTokens("100 * ( 2 + 12 ) / 14");
  rpn_tokens = ConvertToReversePolishNotation(infix_tokens);
  assert( TokensToString(rpn_tokens) == "100 2 12 + * 14 /" );
}

int main() {
  UnitTest();
  return 0;
}
