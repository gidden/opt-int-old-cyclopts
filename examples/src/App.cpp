#include <iostream>
#include <vector>
#include <boost/any.hpp>

#include "SolverTools.h"
#include "CBCSolver.h"
#include "SolverInterface.h"

using namespace std;
using boost::any_cast;
using namespace Cyclopts;

int main() {

  // set up solver and interface
  SolverPtr solver(new CBCSolver());
  SolverInterface csi(solver);

  // set up objective function
  ObjFuncPtr obj(new ObjectiveFunction(ObjectiveFunction::MIN));
  csi.registerObjFunction(obj);

  // set up constraint
  double unmet_demand = 5;
  ConstraintPtr c(new Constraint(Constraint::GTEQ,unmet_demand));
  csi.registerConstraint(c);

  // set up variables
  VariablePtr x(new IntegerVariable(0,Variable::INF));
  x->setName("x");
  csi.registerVariable(x);
  VariablePtr y(new IntegerVariable(0,Variable::INF));
  y->setName("y");
  csi.registerVariable(y);

  // configure constraint and objective function
  double cap_x = 1, cap_y = 2, cost_x = 2, cost_y = 3;
  csi.addVarToConstraint(x,cap_x,c);
  csi.addVarToConstraint(y,cap_y,c);
  csi.addVarToObjFunction(x,cost_x);
  csi.addVarToObjFunction(y,cost_y);

  cout << obj->print() << endl;
  cout << c->print() << endl;
  
  // solve and get solution
  csi.solve();

  // output
  cout << "value of x: " << any_cast<int>(x->value()) << endl;
  cout << "value of y: " << any_cast<int>(y->value()) << endl;

  return 0;
}
