#include "labeltable.h"

using namespace Assembler;

void LabelTable::setLabel(std::string const& labelName, size_t position) {
  _currentLabels[labelName] = position;
}

bool LabelTable::getLabel(std::string const& labelName, size_t& position) {
  if (_currentLabels.find(labelName) != _currentLabels.end()) {
    position = _currentLabels[labelName];
  }
}
