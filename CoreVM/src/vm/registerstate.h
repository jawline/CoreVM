#ifndef _REGISTER_STATE_DEF_H_
#define _REGISTER_STATE_DEF_H_
#include <CoreCS/problem.h>
#include <z3++.h>

namespace VM {

    /**
     * RegisterState is used to store registers.
     */
    class RegisterState {
public:
        RegisterState() : 
            _symbol(z3::context().bool_const("dummy_symbol")) {
            _value = 0;
            _isSymbol = false;
        }

        ~RegisterState() {}

        z3::expr getSymbol() const {
            return _symbol;
        }

        void setSymbol(z3::expr const& symbol) {
            _symbol = symbol;
            _isSymbol = true;
        }

        void clearSymbol() {
            _isSymbol = false;
        }

        uint32_t getValue() const {
            return _value;
        }

        void setValue(uint32_t v) {
            _value = v;
        }

        bool isSymbolic() const {
            return _isSymbol;
        }

    private:
        uint32_t _value;
        bool _isSymbol;
        z3::expr _symbol;
    };
}

#endif //_REGISTER_STATE_DEF_H_
