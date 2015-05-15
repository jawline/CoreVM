#ifndef _REGISTER_STATE_DEF_H_
#define _REGISTER_STATE_DEF_H_
#include <CoreCS/problem.h>
#include "compositesymbol.h"

namespace VM {
    /**
     * RegisterState is used to store registers.
     */
    struct RegisterState {

        RegisterState() {
            value = 0;
            symbol = nullptr;
        }

        ~RegisterState() {
            if (symbol) {
                delete symbol;
            }
        }

        void freeSymbol() {
            if (symbol) {
                delete symbol;
                symbol = nullptr;
            }
        }

        uint32_t value;
        CompositeSymbol* symbol;
    };
}

#endif //_REGISTER_STATE_DEF_H_
