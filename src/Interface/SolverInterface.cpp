#include "SolverInterface.h"
#include "SolverTools.h"

#include <vector>

using namespace std;
using namespace Cyclopts;

// -----------------------------------------------------------------------------------
SolverInterface::SolverInterface(SolverPtr& s) : solver_(s) {
  constraints_ = vector<ConstraintPtr>();
  variables_ = vector<VariablePtr>();
};

// -----------------------------------------------------------------------------------
void SolverInterface::registerVariable(VariablePtr& v) {
  variables_.push_back(v);
}

// -----------------------------------------------------------------------------------
void SolverInterface::registerObjFunction(ObjFuncPtr obj) {
  obj_ = obj;
}

// -----------------------------------------------------------------------------------
void SolverInterface::addVarToObjFunction(VariablePtr& v, double& modifier) {
  // need to check that v is in variables_
  obj_->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void SolverInterface::registerConstraint(ConstraintPtr& c) {
  constraints_.push_back(c);
}

// -----------------------------------------------------------------------------------
void SolverInterface::addVarToConstraint(VariablePtr& v, double& modifier, 
                                               ConstraintPtr& c) {
  // need to check that v is in variables_ and c is in constraints_
  vector<ConstraintPtr>::iterator it;
  it = find(constraints_.begin(),constraints_.end(),c);
  it->get()->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void SolverInterface::solve() {
  solver_->solve(variables_,obj_,constraints_);
}
