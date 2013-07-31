#include "Solver.h"

#include <map>
#include <vector>

#include "SolverTools.h"

using namespace std;
using namespace cyclopts;

// -----------------------------------------------------------------------------
Solver::Solver() {
  index_ = map<VariablePtr,int>();
}

// -----------------------------------------------------------------------------
void Solver::populateIndices(std::vector<VariablePtr>& variables) {
  for (int i = 0; i < variables.size(); i++) {
    index_[variables.at(i)] = i;
  }
}
