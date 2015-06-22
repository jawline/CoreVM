#ifndef _CORE_STATE_DEF_H_
#define _CORE_STATE_DEF_H_
#include <cstdint>
#include <memory>
#include <z3++.h>
#include "registerstate.h"
#include "registers.h"

using namespace std;

namespace VM {
    class CoreState {
        private:
        
        /**
         * Last symbol created
         */
        static unsigned long _lastSymbol;

        /**
         * Constraint solver context
         */
        z3::context _z3Context;
        
        /**
         * Current register data
         */
        RegisterState* _registers;
        
        /**
         * RAM contents
         */
        shared_ptr<uint8_t> _data;
        unsigned int _dataSize;
        
        /**
         * Should the state be copied on write
         */
        bool _copyDataOnWrite;
        
        void copyData();
        
        public:
        CoreState(uint8_t* data, unsigned int size);
        CoreState(CoreState* existing);
        CoreState(CoreState& existing);
        ~CoreState();
        
        void makeSymbolic(uint8_t registerId);
        
        inline bool isSymbolic(uint8_t registerId) {
            return _registers[registerId].isSymbolic();
        }

        inline void addSymbol(uint8_t registerId, int32_t val) {
            auto c = _registers[registerId].getSymbol() + val;
            _registers[registerId].setSymbol(c);
        }

        inline void multiplySymbol(uint8_t registerId, int scalar) {
            _registers[registerId].setSymbol(_registers[registerId].getSymbol() * scalar);
        }

        inline void divideSymbol(uint8_t registerId, int scalar) {
            _registers[registerId].setSymbol(_registers[registerId].getSymbol() / scalar);
        }

        inline z3::expr getSymbol(uint8_t registerId) const {
            return _registers[registerId].getSymbol();
        }
        
        inline void moveRegister(uint8_t dstId, uint8_t srcId) {
            _registers[dstId] = _registers[srcId];
        }
        
        inline uint32_t getRegisterUInt(uint8_t registerId) const {
            return _registers[registerId].getValue();
        }
        
        inline void setRegisterUInt(uint8_t registerId, uint32_t value) {
            _registers[registerId].setValue(value);
            _registers[registerId].clearSymbol();
        }
        
        inline int32_t getRegisterInt(int8_t registerId) const {
            return _registers[registerId].getValue();
        }
        
        inline void setRegisterInt(int8_t registerId, int32_t value) {
            _registers[registerId].setValue(value);
            _registers[registerId].clearSymbol();
        }
        
        inline uint8_t getDataByte(size_t location) const {
            return _data.get()[location];
        }
        
        inline void setDataByte(size_t location, uint8_t val) {
            if (_copyDataOnWrite) {
                copyData();
            }
            _data.get()[location] = val;
        }
        
        inline uint32_t getDataUInt(size_t location) const {
            return *((uint32_t*) &_data.get()[location]);
        }
        
        inline void setDataUInt(size_t location, uint32_t val) {
            *((uint32_t*) &_data.get()[location]) = val;
        }
        
        inline int32_t getDataInt(size_t location) const {
            return *((int32_t*) &_data.get()[location]);
        }
        
        inline void setDataInt(size_t location, int32_t val) {
            *((int32_t*) &_data.get()[location]) = val;
        }
        
        RegisterState const* getRegisters() const;
        uint8_t const* getData() const;
        unsigned int getDataSize() const;
    };
}

#endif //_CORE_STATE_DEF_H_
