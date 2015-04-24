#include "registers.h"
#include <string.h>

using namespace VM;

char const* mapping[] = {
  "PC",
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q"
};

char const* RegisterUtils::getRegisterName(unsigned int id) {
  return mapping[id];
}

RegisterID RegisterUtils::getRegisterId(char const* name) {
  for (unsigned int i = 0; i < NumRegisters; i++) {
    if (strcmp(name, mapping[i]) == 0) {
      return (RegisterID) i;
    }
  }
  return InvalidRegister;
}
