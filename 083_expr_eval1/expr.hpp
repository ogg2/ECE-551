#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Expression {
  public:
    //Expression() {}
    virtual ~Expression() {}
    virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
  private:
    long n;
  public:
    explicit NumExpression (long num) : n (num) {}
    virtual ~NumExpression() {}
    virtual std::string toString() const {
      std::stringstream s;
      s << n;
      return s.str();
    }
};

class PlusExpression : public Expression {
  private:
    Expression * left;
    Expression * right;
  public:
    PlusExpression (Expression * lhs, Expression * rhs) : left (lhs),
                                                          right (rhs) {}
    virtual ~PlusExpression() {
      delete left;
      delete right;  
    }
    virtual std::string toString() const {
      std::stringstream s;
      s << "(" << left->toString() << " + " << right->toString() << ")";
      return s.str();
    }
};

#endif
