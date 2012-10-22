#include "SolverInterface.h"
#include "SolverTools.h"
#include "CycloptsLimits.h"

#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Cyclopts;

// -----------------------------------------------------------------------------------
SolverInterface::SolverInterface(SolverPtr& s) : solver_(s) {
  constraints_ = vector<ConstraintPtr>();
  variables_ = vector<VariablePtr>();
  modifier_limit_ = Limits::modifier_limit; // this is a bandaid, I don't know why it has to happen... somethings up with cbc
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
  checkModifierBounds(modifier);
  obj_->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void SolverInterface::registerConstraint(ConstraintPtr& c) {
  constraints_.push_back(c);
}

// -----------------------------------------------------------------------------------
void SolverInterface::addVarToConstraint(VariablePtr& v, double& modifier, 
                                         ConstraintPtr& c) {
  checkModifierBounds(modifier);
  // need to check that v is in variables_ and c is in constraints_
  vector<ConstraintPtr>::iterator it;
  it = find(constraints_.begin(),constraints_.end(),c);
  it->get()->addConstituent(v,modifier);
}

// -----------------------------------------------------------------------------------
void SolverInterface::solve() {
  solver_->solve(variables_,obj_,constraints_);
}

// -------------------------------------------------------------------
void SolverInterface::checkModifierBounds(double& modifier)
{
  if (modifier > modifier_limit_)
    {
      stringstream msg;
      msg << "Cannot add modifier " 
          << modifier
          << " which is greater than the modifier limit " 
          << modifier_limit_;
      throw runtime_error(msg.str());
    }
}
