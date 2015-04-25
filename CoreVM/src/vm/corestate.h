#ifndef _CORE_STATE_DEF_H_
#define _CORE_STATE_DEF_H_
#include <cstdint>
#include <memory>
#include <CoreCS/solver.h>
#include "registers.h"

using namespace std;

namespace VM {

    /**
     * RegisterState is used to store registers.
     */
    struct RegisterState {
        RegisterState() {
            value = 0;
            symbolic = false;
        }
        uint32_t value;
        bool symbolic;
        Constraints::Variable variable;
    };

    class CoreState {
    private:

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

        Constraints::Problem _symState;

    	void copyData();

    public:
    	CoreState(uint8_t* data, unsigned int size);
        CoreState(CoreState* existing);
      	CoreState(CoreState& existing);
        ~CoreState();

        void makeSymbolic(uint8_t registerId);

        Constraints::Problem* getProblem() {
            return &_symState;
        }
        
        inline bool isSymbolic(uint8_t registerId) {
            return _registers[registerId].symbolic;
        }

        inline Constraints::Variable getVariable(uint8_t registerId) {
            return _registers[registerId].variable;
        }

        inline void moveRegister(uint8_t dstId, uint8_t srcId) {
            _registers[dstId] = _registers[srcId];
        }

      	inline uint32_t getRegisterUInt(uint8_t registerId) const {
        		return _registers[registerId].value;
      	}

      	inline void setRegisterUInt(uint8_t registerId, uint32_t value) {
        	_registers[registerId].value = value;
            _registers[registerId].symbolic = false;
        }
        
        inline int32_t getRegisterInt(int8_t registerId) const {
          	return _registers[registerId].value;
        }
        
        inline void setRegisterInt(int8_t registerId, int32_t value) {
        	_registers[registerId].value = value;
            _registers[registerId].symbolic = false;
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
        	
        RegisterState const* getRegisters() {
        	return _registers;
        }
        	
        uint8_t const* getData() {
        	return _data.get();
        }
        	
        unsigned int getDataSize() {
        	return _dataSize;
        }
  };
}

#endif //_CORE_STATE_DEF_H_
