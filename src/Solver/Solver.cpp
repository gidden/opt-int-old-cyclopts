#include "Solver.h"

#include "SolverTools.h"

#include <map>
#include <vector>

using namespace std;
using namespace Cyclopts;

// -----------------------------------------------------------------------------------
Solver::Solver() {
  index_ = map<VariablePtr,int>();
}

// -----------------------------------------------------------------------------------
void Solver::populateIndices(std::vector<VariablePtr>& variables) {
  for (int i = 0; i < variables.size(); i++) {
    index_[variables.at(i)] = i;
  }
}
