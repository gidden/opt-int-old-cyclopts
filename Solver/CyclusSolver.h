#ifndef CYCLUSSOLVER_H
#define CYCLUSSOLVER_H

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

namespace CyclusOptimization{
  class CyclusSolver;
  /// a smart pointer to the base class
  typedef boost::shared_ptr<CyclusSolver> SolverPtr;
}

#include "CyclusSolverTools.h"

namespace CyclusOptimization {
  /// abstract base class for different types of constraint program solvers
  class CyclusSolver {
  public:
    /// constructor
    CyclusSolver();
    /// virtual destructor
    virtual ~CyclusSolver() {};
    /// solve method to be overloaded by derived classes
    virtual void solve(std::vector<VariablePtr>& variables, ObjFuncPtr& obj, 
                       std::vector<ConstraintPtr>& constraints) = 0;
  protected:
    /// the indices used for each variable
    std::map<VariablePtr,int> index_;
    /// match variable pointers to indices, populating indicies_
    void populateIndices(std::vector<VariablePtr>& variables);
  };
}

#include "Variable.h"
#include "Function.h"
#include "CoinModel.hpp"
#include "CbcModel.hpp"
#include "OsiClpSolverInterface.hpp"

#include <boost/shared_ptr.hpp>

namespace CyclusOptimization {
  /// the coin branch-and-cut solver
  class CBCSolver : public CyclusSolver {
  public:
    /// solve an MIP
    virtual void solve(std::vector<VariablePtr>& variables, ObjFuncPtr& obj, 
                       std::vector<ConstraintPtr>& constraints);
  private:
    /// the model builder
    CoinModel builder_;
    /// return +/- COIN_DBL_MAX 
    double doubleBound(Variable::bound b);
    /// return +/- COIN_INT_MAX 
    int intBound(Variable::bound b);
    /// get coin-specific bound for a constraint
    std::pair<double,double> constraintBounds(ConstraintPtr& c);
    /// set variable/objective function values
    void setUpVariablesAndObj(std::vector<VariablePtr>& variables, ObjFuncPtr& obj);
    /// set up constraints
    void setUpConstraints(std::vector<ConstraintPtr>& constraints);
    /// set the objective direction
    double objDirection(ObjFuncPtr& obj);
    /// solve the model
    void solveModel(CbcModel& model);
    /// populate the solution in the variable vector
    void populateSolution(CbcModel& model,std::vector<VariablePtr>& variables);
    /// print variables info
    void printVariables(int n_const);
    /// print objective function info
    void printObjFunction(int n_vars);
    /// print constraint info
    void printConstraints(int n_const, int n_vars);
    /// prints each other printing function
    void print(int n_const, int n_vars);
  };
}

#endif
