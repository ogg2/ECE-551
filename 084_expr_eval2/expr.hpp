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
  protected:
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

class MathExpression : public Expression {
  protected:
    Expression * left;
    Expression * right;
    char operation;
  public:
    MathExpression (Expression * lhs, Expression * rhs, char o) : left (lhs),
                                                                  right (rhs),
                                                                  operation (o) {}
    virtual ~MathExpression() {
      delete left;
      delete right;
    }
    virtual std::string toString() const {
      std::stringstream s;
      s << "(" << left->toString() << " " << operation << " " << right->toString() << ")";
      return s.str();
    }
};

class PlusExpression : public MathExpression {
  public:
    PlusExpression (Expression * lhs, Expression * rhs) : MathExpression (lhs, rhs, '+') {}
    virtual ~PlusExpression() {}
};

class MinusExpression : public MathExpression {
  public:
    MinusExpression (Expression * lhs, Expression * rhs) : MathExpression (lhs, rhs, '-') {}
    virtual ~MinusExpression() {}
};

class TimesExpression : public MathExpression {
  public:
    TimesExpression (Expression * lhs, Expression * rhs) : MathExpression (lhs, rhs, '*') {}
    virtual ~TimesExpression() {}
};

class DivExpression : public MathExpression {
  public:
    DivExpression (Expression * lhs, Expression * rhs) : MathExpression (lhs, rhs, '/')
{}
    virtual ~DivExpression() {}
};

#endif
