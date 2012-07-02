#include "Function.h"

#include "Variable.h"

#include <map>
#include <utility>
#include <string>
#include <sstream>

using namespace std;
using namespace Cyclopts;

// +++ Function methods ++
// -----------------------------------------------------------------------------------
Function::Function() {
  constituents_ = map<VariablePtr,double>();
}

// -----------------------------------------------------------------------------------
void Function::addConstituent(VariablePtr& v, double& modifier) {
  constituents_.insert(pair<VariablePtr,double>(v,modifier));
}

// -----------------------------------------------------------------------------------
double Function::getModifier(VariablePtr& v) {
  return constituents_[v];
}

// -----------------------------------------------------------------------------------
std::map<VariablePtr,double>::iterator Function::begin() {
  return constituents_.begin();
}

// -----------------------------------------------------------------------------------
std::map<VariablePtr,double>::iterator Function::end() {
  return constituents_.end();
}

// -----------------------------------------------------------------------------------
int Function::nConstituents() { 
  return constituents_.size(); 
}

// -----------------------------------------------------------------------------------
std::string Function::print() { 
  stringstream ss;
  int count = 0;
  map<VariablePtr,double>::iterator it;
  for (it = constituents_.begin(); it != constituents_.end(); it++) {
    ss << it->second << it->first->name();
    if (count < constituents_.size()-1) {
      ss << " + ";
    }
    count++;
  }
  return ss.str();
}

// +++ Constraint methods ++
// -----------------------------------------------------------------------------------
Constraint::Constraint(Constraint::equality_relation eq_r, double rhs) : 
  eq_r_(eq_r), rhs_(rhs) {};

// -----------------------------------------------------------------------------------
Constraint::equality_relation Constraint::equalityRelation() { 
  return eq_r_; 
}

// -----------------------------------------------------------------------------------
double Constraint::rhs() { 
  return rhs_; 
}

// -----------------------------------------------------------------------------------
std::string Constraint::print() {
  stringstream ss;
  ss << "s.t. " << Function::print() << " " << eq_rToStr() << " " << rhs_;
  return ss.str();
}

// -----------------------------------------------------------------------------------
std::string Constraint::eq_rToStr() {
  switch(eq_r_) {
  case EQ:
    return "=";
    break;
  case GT:
    return ">";
    break;
  case GTEQ:
    return ">=";
    break;
  case LT:
    return "<";
    break;
  case LTEQ:
    return "<=";
    break;
  }
}

// +++ ObjectiveFunction methods ++
// -----------------------------------------------------------------------------------
ObjectiveFunction::ObjectiveFunction(ObjectiveFunction::direction dir) : 
  dir_(dir) {};

// -----------------------------------------------------------------------------------
ObjectiveFunction::direction ObjectiveFunction::dir() {
  return dir_;
}

// -----------------------------------------------------------------------------------
std::string ObjectiveFunction::print() {
  stringstream ss;
  ss << dirToStr() << " " << Function::print();
  return ss.str();
}

// -----------------------------------------------------------------------------------
std::string ObjectiveFunction::dirToStr() {
  switch(dir_) {
  case MIN:
    return "min";
    break;
  case MAX:
    return "max";
    break;
  }
}
