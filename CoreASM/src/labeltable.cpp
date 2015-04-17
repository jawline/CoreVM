#include "labeltable.h"

using namespace std;
using namespace Assembler;

void LabelTable::setLabel(string const& labelName, size_t position) {
  _currentLabels[labelName] = position;
}

bool LabelTable::getLabel(string const& labelName, size_t& position) {
  if (_currentLabels.find(labelName) != _currentLabels.end()) {
    position = _currentLabels[labelName];
    return true;
  }
  return false;
}
