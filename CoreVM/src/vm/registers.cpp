#include "registers.h"
#include <string.h>

using namespace VM;

RegisterID RegisterUtils::getRegisterId(char const* name) {
  switch (*name) {
    case 'A':
      return RegisterA;
    case 'B':
      return RegisterB;
    case 'C':
      return RegisterC;
    case 'D':
      return RegisterD;
    case 'E':
      return RegisterE;
    case 'F':
      return RegisterF;
    case 'G':
      return RegisterG;
    case 'H':
      return RegisterH;
    case 'I':
      return RegisterI;
    case 'J':
      return RegisterJ;
    case 'K':
      return RegisterK;
    case 'L':
      return RegisterL;
    case 'M':
      return RegisterM;
    case 'N':
      return RegisterN;
    case 'O':
      return RegisterO;
    case 'P':
      return RegisterP;
    case 'Q':
      return RegisterQ;
    default:
      return InvalidRegister;
  }
}
