#ifndef _REGISTER_STATE_DEF_H_
#define _REGISTER_STATE_DEF_H_
#include <CoreCS/problem.h>

namespace VM {

    /**
     * RegisterState is used to store registers.
     */
     //TODO: Seperate impl into file
    class RegisterState {

        RegisterState() {
            value = 0;
            _isSymbol = false;

        }

        ~RegisterState() {}

        Constraints::Constraint getSymbol() const {
            return _symbol;
        }

        void setSymbol(Constraints::Constraint const& symbol) {
            _symbol = symbol;
        }

        uint32_t getValue() const {
            return _value;
        }

        void setValue(uint32_t v) {
            _value = v;
        }

    private:
        uint32_t _value;
        bool _isSymbol;
        Constraints::Constraint _symbol;
    };
}

#endif //_REGISTER_STATE_DEF_H_
