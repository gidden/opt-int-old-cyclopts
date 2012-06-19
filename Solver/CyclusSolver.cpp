#include "CyclusSolver.h"

#include "Variable.h"

#include <map>
#include <vector>

using namespace std;
using namespace CyclusOptimization;

// -----------------------------------------------------------------------------------
CyclusSolver::CyclusSolver() {
  index_ = map<VariablePtr,int>();
}

// -----------------------------------------------------------------------------------
void CyclusSolver::populateIndices(std::vector<VariablePtr>& variables) {
  for (int i = 0; i < variables.size(); i++) {
    index_[variables.at(i)] = i;
  }
}
