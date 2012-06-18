#include "CyclusSolverInterface.h"
#include "CyclusSolverTools.h"

#include <vector>

using namespace std;
using namespace CyclusOptimization;

// -----------------------------------------------------------------------------------
CyclusSolverInterface::CyclusSolverInterface(SolverPtr& s) : solver_(s) {
  constraints_ = vector<ConstraintPtr>();
  variables_ = vector<VariablePtr>();
};

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::registerVariable(VariablePtr& v) {
  variables_.push_back(v);
}

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::registerObjFunction(ObjFuncPtr obj) {
  obj_ = obj;
}

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::addVarToObjFunction(VariablePtr& v, double& modifier) {
  // need to check that v is in variables_
  obj_->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::registerConstraint(ConstraintPtr& c) {
  constraints_.push_back(c);
}

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::addVarToConstraint(VariablePtr& v, double& modifier, 
                                               ConstraintPtr& c) {
  // need to check that v is in variables_ and c is in constraints_
  vector<ConstraintPtr>::iterator it;
  it = find(constraints_.begin(),constraints_.end(),c);
  it->get()->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void CyclusSolverInterface::solve() {
  solver_->solve(variables_,obj_,constraints_);
}
