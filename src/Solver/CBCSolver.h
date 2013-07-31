#ifndef CBCSOLVER_H
#define CBCSOLVER_H

#include "SolverTools.h"

// coin includes
#include "CoinModel.hpp"
#include "CbcModel.hpp"

/// an epsilon value to define strict inequalities
#define CONSTRAINT_EPS 1e-08

/// typedef cbc model to abstract away coin's library
typedef CbcModel CoinCbcModel;

namespace cyclopts {
  /// the coin branch-and-cut solver
  class CBCSolver : public Solver {
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
    void solveModel(CoinCbcModel& model);
    /// populate the solution in the variable vector
    void populateSolution(CoinCbcModel& model,std::vector<VariablePtr>& variables);
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
