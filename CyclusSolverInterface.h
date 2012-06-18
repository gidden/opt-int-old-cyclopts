#ifndef CYCLUSSOLVERINTERFACE_H
#define CYCLUSSOLVERINTERFACE_H

#include "CyclusSolver.h"
#include "CyclusSolverTools.h"

#include <vector>

namespace CyclusOptimization{
  /// interface class to set up and solve a constraint program
  class CyclusSolverInterface {
  public:
    /// constructor, sets the solver to use
    CyclusSolverInterface(SolverPtr& solver);
    /// add a constraint
    void registerVariable(VariablePtr& v);
    /// set the objective function
    void registerObjFunction(ObjFuncPtr obj);
    /// add a variable to the objective function
    void addVarToObjFunction(VariablePtr& v, double& modifier);
    /// add a constraint
    void registerConstraint(ConstraintPtr& c);
    /// add a variable to a constraint
    void addVarToConstraint(VariablePtr& v, double& modifier, ConstraintPtr& c);
    /// solve the constraint program
    void solve();
  private:
    /// the solver
    SolverPtr solver_;
    /// the variables
    std::vector<VariablePtr> variables_;
    /// the objective function
    ObjFuncPtr obj_;
    /// the constraints
    std::vector<ConstraintPtr> constraints_;
  };
}

#endif
