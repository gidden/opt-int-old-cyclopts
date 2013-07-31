#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>

namespace cyclopts {
  class Variable;
  /// a smart pointer to the base class
  typedef boost::shared_ptr<Variable> VariablePtr;

  /// Variable base class
  class Variable {
  public:  
    /// enum for possible bound types
    enum bound {NEG_INF,INF,FINITE};
    /// enum for possible types
    enum var_type {INT,LINEAR};
    /// constructor, sets id_, lbound_, ubound_
    Variable(bound l, bound u, var_type t);
    /// virtual destructor for a base class
    virtual ~Variable() {};
    /// id getter
    int id();
    /// get value
    var_type type();
    /// lbound getter
    bound lbound();
    /// ubound getter
    bound ubound();
    /// get name
    std::string name();
    /// set name
    void setName(std::string name);
    /// get value
    boost::any value();
    /// set value
    void setValue(boost::any v);

  private:
    /// global id incrementor
    static int next_id_;
    /// id
    int id_;
    /// type
    var_type type_;
    /// lower bound
    bound lbound_;
    /// upper bound
    bound ubound_;
    /// name
    std::string name_;
    /// value
    boost::any value_;
  };

  /// derived class for linear variables
  class LinearVariable : public Variable {
  public:
    /// constructor for bounds NEG_INF : INF
    LinearVariable(bound lb, bound ub);
    /// constructor for bounds FINITE : INF
    LinearVariable(double lb_val, bound ub);
    /// constructor for NEG_INF : FINITE
    LinearVariable(bound lb, double ub_val);
    /// constructor for FINITE : FINITE
    LinearVariable(double lb_val, double ub_val);
    /// lbound value getter
    double lbound_val();
    /// ubound value getter
    double ubound_val();
  private:
    /// lower bound value
    double lbound_val_;
    /// upper bound value
    double ubound_val_;
  };

  /// derived class for integer variables
  class IntegerVariable : public Variable {
  public:
    /// constructor for bounds NEG_INF : INF
    IntegerVariable(bound lb, bound ub);
    /// constructor for bounds FINITE : INF
    IntegerVariable(int lb_val, bound ub);  
    /// constructor for NEG_INF : FINITE
    IntegerVariable(bound lb, int ub_val);
    /// constructor for FINITE : FINITE
    IntegerVariable(int lb_val, int ub_val);    
    /// lbound value getter
    int lbound_val();
    /// ubound value getter
    int ubound_val();
  private:
    /// lower bound value
    int lbound_val_;
    /// upper bound value
    int ubound_val_;
  };
}
#endif
