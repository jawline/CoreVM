#ifndef _REGISTER_STATE_DEF_H_
#define _REGISTER_STATE_DEF_H_
#include <CoreCS/problem.h>

namespace VM {
    /**
     * RegisterState is used to store registers.
     */
    struct RegisterState {
        RegisterState() {
            value = 0;
            symbolic = false;
            symbolicMultiplier = 1;
        }
        uint32_t value;
        bool symbolic;
        int symbolicMultiplier;
        Constraints::Variable variable;
    };
}

#endif //_REGISTER_STATE_DEF_H_
