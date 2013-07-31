#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <map>
#include <utility>
#include <string>

#include <boost/shared_ptr.hpp>

#include "Variable.h"

namespace cyclopts {
  class Function;
  class Constraint;
  typedef boost::shared_ptr<Constraint> ConstraintPtr;
  class ObjectiveFunction;
  typedef boost::shared_ptr<ObjectiveFunction> ObjFuncPtr;
}

#include "SolverInterface.h"

namespace cyclopts {
  /// function base class
  class Function {
   public:
    /// constructor
    Function();

    /// virtual destructor for base class
    virtual ~Function() {};

    /// get a modifier
    double getModifier(VariablePtr& v);

    /// get the beginning iterator to constituents_
    std::map<VariablePtr,double>::iterator begin();

    /// get the ending iterator to constituents_
    std::map<VariablePtr,double>::iterator end();

    /// get number of constituents
    int nConstituents();

    /// print the function
    virtual std::string print();

   private:
    /// a container of all variables and their corresponding constant
    std::map<VariablePtr,double> constituents_;    

    /// add a constituent
    void addConstituent(VariablePtr& v, double& modifer);

    /// the solver interface builds functions knowing what variables exist
    friend class SolverInterface;
  };

  /// derived class for constraints
  class Constraint : public Function {
   public:
    /// the equality relation
    enum equality_relation {EQ,GT,GTEQ,LT,LTEQ};

    /// constructor
    Constraint(equality_relation eq_r, double rhs);

    /// get the equality relation
    equality_relation equalityRelation();

    /// get the rhs
    double rhs();

    /// print the constraint
    virtual std::string print();

   private:
    /// the type of equality relation
    equality_relation eq_r_;

    /// the rhs value
    double rhs_;

    /// turn eq_r_ into a string
    std::string eq_rToStr();
  };
  
  /// derived class for objective functions
  class ObjectiveFunction : public Function {
  public: 
    /// the possible direction
    enum direction {MIN,MAX};

    /// constructor
    ObjectiveFunction(direction);

    /// get the direction
    direction dir();

    /// print the objective function
    virtual std::string print();

  private:
    /// the direction
    direction dir_;

    /// turn dir_ into a string
    std::string dirToStr();
  };
}

#endif
