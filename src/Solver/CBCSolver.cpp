#include "CBCSolver.h"

#include "Function.h"
#include "Variable.h"

#include <iostream>
#include <utility>
#include <boost/any.hpp>

// Coin related
#include "CoinModel.hpp"
#include "CbcModel.hpp"
#include "OsiClpSolverInterface.hpp"

using namespace std;
using namespace boost;
using namespace Cyclopts;

// -----------------------------------------------------------------------------------
double CBCSolver::doubleBound(Variable::bound b) {
  double val;
  switch(b) {
  case Variable::NEG_INF:
    val = -COIN_DBL_MAX;
    break;
  case Variable::INF:
    val = COIN_DBL_MAX;
    break;
  }
  return val;
}

// -----------------------------------------------------------------------------------
int CBCSolver::intBound(Variable::bound b) {
  int val;
  switch(b) {
  case Variable::NEG_INF:
    val = -COIN_INT_MAX;
    break;
  case Variable::INF:
    val = COIN_INT_MAX;
    break;
  }
  return val;
}

// -----------------------------------------------------------------------------------
std::pair<double,double> CBCSolver::constraintBounds(ConstraintPtr& c) {
  double lval, rval;
  switch(c->equalityRelation()) {
  case Constraint::EQ:
    lval = c->rhs(); rval = c->rhs();
    break;
  case Constraint::GTEQ:
    lval = c->rhs(); rval = COIN_DBL_MAX;
  case Constraint::GT: // explicit fall through
    lval += CONSTRAINT_EPS; 
    break;
  case Constraint::LTEQ:
    lval = COIN_DBL_MAX; rval = c->rhs();
  case Constraint::LT: // explicit fall through
    rval -= CONSTRAINT_EPS; 
    break;
  }
  return pair<double,double>(lval,rval);
}

// -----------------------------------------------------------------------------------
void CBCSolver::setUpVariablesAndObj(std::vector<VariablePtr>& variables, 
                                     ObjFuncPtr& obj) {
  for (int i = 0; i < variables.size(); i++) {
    VariablePtr v = variables.at(i);
    switch(v->type()) {
    case Variable::INT:
      builder_.setColumnBounds(i,intBound(v->lbound()),intBound(v->ubound()));
      builder_.setInteger(i);
      break;
    case Variable::LINEAR:
      builder_.setColumnBounds(i,doubleBound(v->lbound()),doubleBound(v->ubound()));
      break;
    }
    builder_.setObjective(i,obj->getModifier(v));
  }
}

// -----------------------------------------------------------------------------------
void CBCSolver::setUpConstraints(std::vector<ConstraintPtr>& constraints) {
  for (int i = 0; i < constraints.size(); i++) {
    ConstraintPtr c = constraints.at(i);
    pair<double,double> bounds = constraintBounds(c);
    builder_.setRowBounds(i,bounds.first,bounds.second);
    std::map<VariablePtr,double>::iterator it;
    for (it = c->begin(); it != c->end(); it++) {
      builder_.setElement(i,index_[it->first],it->second);
    }
  }
}

// -----------------------------------------------------------------------------------
double CBCSolver::objDirection(ObjFuncPtr& obj) {
  double sense_value;
  switch(obj->dir()) {
  case ObjectiveFunction::MIN:
    sense_value = 1.0;
    break;
  case ObjectiveFunction::MAX:
    sense_value = -1.0;
    break;
  }
  return sense_value;
}

// -----------------------------------------------------------------------------------
void CBCSolver::solveModel(CbcModel& model) {
  model.messageHandler()->setLogLevel(0); // turn off all output
  model.solver()->messageHandler()->setLogLevel(0); // turn off all output
  model.branchAndBound();
}

// -----------------------------------------------------------------------------------
void CBCSolver::populateSolution(CbcModel& model, std::vector<VariablePtr>& variables) {
  int ncol = model.solver()->getNumCols();
  const double* solution = model.solver()->getColSolution();
  
  for (int i = 0; i < variables.size(); i++) {
    any value = solution[i]; 
    switch(variables.at(i)->type()) { 
    case Variable::INT:
      value = (int) solution[i];
      break;
    }
    variables.at(i)->setValue(value);
  }
}

// -----------------------------------------------------------------------------------
void CBCSolver::printVariables(int num) {
  cout << "Variables:" << endl;
  for (int i = 0; i < num; i++) {
    cout << "  lbound: " << builder_.getColLower(i) << " ubound: " << 
      builder_.getColUpper(i) << " integer: " << builder_.getColIsInteger(i) << endl;
  }
  cout << "note true = " << true << endl;
}

// -----------------------------------------------------------------------------------
void CBCSolver::printObjFunction(int num) {
  cout << "Objective Function:" << endl;
  cout << "  direction: " << builder_.optimizationDirection() << endl;
  cout << "    values: ";
  for (int i = 0; i < num; i++) {
    cout << builder_.getColumnObjective(i) <<  " ";
  }
  cout << endl;
}

// -----------------------------------------------------------------------------------
void CBCSolver::printConstraints(int n_const, int n_vars) {
  cout << "Constraints:" << endl;
  for (int i = 0; i < n_const; i++) {
    cout << "  lbound: " << builder_.getRowLower(i) << " ubound: " << 
      builder_.getRowUpper(i) << endl;
    cout << "    values: ";
    for (int j = 0; j < n_vars; j++) {
      cout << builder_.getElement(i,j) << " ";
    }
    cout << endl;
  }
}

// -----------------------------------------------------------------------------------
void CBCSolver::print(int n_const, int n_vars) {
  printVariables(n_vars);
  printObjFunction(n_vars);
  printConstraints(n_const,n_vars);
}

// -----------------------------------------------------------------------------------
void CBCSolver::solve(std::vector<VariablePtr>& variables, ObjFuncPtr& obj, 
                      std::vector<ConstraintPtr>& constraints) {
  // use builder_ to build constraint probelm
  Solver::populateIndices(variables);
  setUpConstraints(constraints);
  setUpVariablesAndObj(variables,obj);
  builder_.setOptimizationDirection(objDirection(obj));
  print(constraints.size(),variables.size());

  // solve constraint problem
  OsiClpSolverInterface solver1;
  OsiSolverInterface* solver = &solver1;
  solver->loadFromCoinModel(builder_);
  CbcModel model(*solver);
  solveModel(model);
  populateSolution(model,variables);
}
