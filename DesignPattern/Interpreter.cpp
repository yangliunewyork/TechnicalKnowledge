/* 
Interpreter Design Pattern: Interpreter pattern provides a way to evaluate language grammar or expression. 
This pattern involves implementing an expression interface which tells to interpret a particular context. 
In computer programming, the interpreter pattern is a design pattern that specifies how to evaluate sentences 
in a language. The basic idea is to have a class for each symbol (terminal or nonterminal) in a specialized 
computer language. The syntax tree of a sentence in the language is an instance of the composite pattern and 
is used to evaluate (interpret) the sentence for a client. In computer science, an abstract syntax tree (AST), 
or just syntax tree, is a tree representation of the abstract syntactic structure of source code written in 
a programming language. Each node of the tree denotes a construct occurring in the source code. 
The syntax is "abstract" in not representing every detail appearing in the real syntax.
A parse tree or parsing tree or derivation tree or (concrete) syntax tree is an ordered, 
rooted tree that represents the syntactic structure of a string according to some context-free grammar. 
The term parse tree itself is used primarily in computational linguistics; in theoretical syntax 
the term syntax tree is more common. Parse trees are distinct from the abstract syntax trees used in computer programming, 
in that their structure and elements more concretely reflect the syntax of the input language. 
*/

#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <memory>

class IExpression {
public:
  virtual double Interpret() = 0;
};
typedef std::shared_ptr<IExpression> IExpressionPtr;

class TerminalExpression : public IExpression{
};

class NonTerminalExpression: public IExpression {
};
typedef std::shared_ptr<NonTerminalExpression> NonTerminalExpressionPtr;

class BinaryOperator : public NonTerminalExpression {
public:
  BinaryOperator(const IExpressionPtr & left, const IExpressionPtr & right)
    : m_left(left),m_right(right){}
protected:
  IExpressionPtr m_left,m_right;
};
typedef std::shared_ptr<BinaryOperator> BinaryOperatorPtr;

class UnaryOperator : public NonTerminalExpression {
public:
  UnaryOperator(const IExpressionPtr & exp)
    : m_operand(exp){}
protected:
  IExpressionPtr m_operand;
};

typedef std::shared_ptr<UnaryOperator> UnaryOperatorPtr;

class AddTenExpression : public UnaryOperator {
public:
  AddTenExpression(const IExpressionPtr & exp) : UnaryOperator(exp) {}
  virtual double Interpret() {return m_operand->Interpret() + 10;}
};

class NumberExpression : public TerminalExpression {
public:
  NumberExpression(double val):m_val(val){}
  virtual double  Interpret(){ return m_val;}
private:
  double m_val;
};
typedef std::shared_ptr<NumberExpression> NumberExpressionPtr;

class AddExpression : public BinaryOperator {
public:
  AddExpression(const IExpressionPtr & left, const IExpressionPtr & right):BinaryOperator(left,right){}
  virtual double Interpret(){return m_left->Interpret() + m_right->Interpret();}
};

class SubExpression : public BinaryOperator {
public:
  SubExpression(const IExpressionPtr & left, const IExpressionPtr & right):BinaryOperator(left,right){}
  virtual double Interpret(){return m_left->Interpret() - m_right->Interpret();}
};

class MulExpression : public BinaryOperator {
public:
  MulExpression(const IExpressionPtr & left, const IExpressionPtr & right):BinaryOperator(left,right){}
  virtual double Interpret(){return m_left->Interpret() * m_right->Interpret();}
};

class DivExpression : public BinaryOperator {
public:
  DivExpression(const IExpressionPtr & left, const IExpressionPtr & right):BinaryOperator(left,right){}
  virtual double Interpret(){return m_left->Interpret() / m_right->Interpret();}
};


class Token {
public:
  Token(const std::string & str):m_str(str){}
  std::string GetValue() const { return m_str;}
private:
  std::string m_str;
};

class Tokenizer {
public:
  Tokenizer(const std::string & input) : m_pos(0) {
    std::istringstream iss(input);
    std::string temp("");
    while(std::getline(iss,temp,',')) {
      m_tokens.push_back(Token(temp));
    }
  }
  bool HasNext() {return m_pos!=m_tokens.size();}
  Token Next() {return m_tokens[m_pos++];}
private:
  int m_pos;
  std::vector<Token> m_tokens;
};

class OperatorFactory {
public:
  static OperatorFactory & Instance(){
    static OperatorFactory instance;
    return instance;
  }
  
  bool IsBinaryOperator(const std::string & str) const {
    return m_binary_operators_set.count(str) != 0;
  }

  bool IsUnaryOperator(const std::string & str) const {
    return m_unary_operators_set.count(str) != 0;
  }
  
  BinaryOperatorPtr GetBinaryOperator(const std::string &  str, const IExpressionPtr & left, const IExpressionPtr & right) const {
    if (str=="+") return std::make_shared<AddExpression>(left,right);
    else if (str =="-") return std::make_shared<SubExpression>(left,right);
    else if (str== "*") return std::make_shared<MulExpression>(left,right);
    else if (str== "/")  return std::make_shared<DivExpression>(left,right);
    else return nullptr;
  }

  UnaryOperatorPtr GetUnaryOperator(const std::string &  str, const IExpressionPtr & operand) const {
    if (str=="AddTen") return std::make_shared<AddTenExpression>(operand);
    else return nullptr;
  }
  
private:
  OperatorFactory(){
    // Add unary operators
    m_unary_operators_set.insert("AddTen");
    // Add binary operators
    m_binary_operators_set.insert("+");
    m_binary_operators_set.insert("-");
    m_binary_operators_set.insert("*");
    m_binary_operators_set.insert("/");
  }
  OperatorFactory(const OperatorFactory& other) = delete;
  OperatorFactory& operator=(const OperatorFactory& other) = delete;
  std::unordered_set<std::string> m_binary_operators_set;
  std::unordered_set<std::string> m_unary_operators_set;
};

class Interpreter {
public:
  Interpreter() {}
  double Interpret(Tokenizer & tokenizer) {
    const OperatorFactory & op_factory = OperatorFactory::Instance();
    while(tokenizer.HasNext()) {
      const Token & cur_token = tokenizer.Next();
      if ( op_factory.IsBinaryOperator(cur_token.GetValue()) ) {
        IExpressionPtr right = m_operands.top();
        m_operands.pop();
        IExpressionPtr left = m_operands.top();
        m_operands.pop();
        BinaryOperatorPtr op = op_factory.GetBinaryOperator(cur_token.GetValue(),left,right);
        m_operands.push( std::make_shared<NumberExpression>(op->Interpret()));
      } else if(op_factory.IsUnaryOperator(cur_token.GetValue()) ) {
        IExpressionPtr operand = m_operands.top();
        m_operands.pop();
        UnaryOperatorPtr op = op_factory.GetUnaryOperator(cur_token.GetValue(),operand);
        m_operands.push( std::make_shared<NumberExpression>(op->Interpret()));
      } else {
        m_operands.push( std::make_shared<NumberExpression>(std::stod(cur_token.GetValue()) ) ) ;
      }
    }
    return m_operands.top()->Interpret();
  }
private:
  std::stack<NumberExpressionPtr> m_operands;
};

void UnitTest_Interpreter() {
  Tokenizer tk("4,3,2,-,1,+,*");
  Interpreter itp;
  double value = itp.Interpret(tk);
  assert(value==8);

  Tokenizer tk2("3,2,5,/,+,2,4,*,-");//3+2/5-2*4
  value = itp.Interpret(tk2);
  assert(value==-4.6);
  
  Tokenizer tk3("3,2,5,/,+,2,4,*,-,AddTen");// AddTen(3+2/5-2*4)
  value = itp.Interpret(tk3);
  assert(value==5.4);
}
int main() {
  UnitTest_Interpreter();
  return 0;
}
