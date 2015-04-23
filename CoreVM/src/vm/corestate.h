#ifndef _CORE_STATE_DEF_H_
#define _CORE_STATE_DEF_H_
#include <cstdint>
#include <memory>
#include "registers.h"

using namespace std;

namespace VM {
  class CoreState {
  private:
	/**
	 * Current register data
	 */
	shared_ptr<uint32_t> _registers;
		
	/**
	 * RAM contents
	 */
	shared_ptr<uint8_t> _data;
	unsigned int _dataSize;
	
	/**
	 * Should the state be copied on write
	 */
	bool _copyRegistersOnWrite;
	bool _copyDataOnWrite;

	void copyRegisters();
	void copyData();

  public:
	CoreState(uint8_t* data, unsigned int size);
  	CoreState(CoreState const& existing);

  	inline uint32_t getRegisterUInt(uint8_t registerId) const {
    		return _registers.get()[registerId];
  	}

  	inline void setRegisterUInt(uint8_t registerId, uint32_t value) {
  		if (_copyRegistersOnWrite) {
    			copyRegisters();
    		}
    		_registers.get()[registerId] = value;
    	}
    
    	inline int32_t getRegisterInt(int8_t registerId) const {
      		return _registers.get()[registerId];
    	}

    	inline void setRegisterInt(int8_t registerId, int32_t value) {
    		if (_copyRegistersOnWrite) {
    			copyRegisters();
    		}
    		_registers.get()[registerId] = value;
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
    	
    	uint32_t const* getRegisters() {
    		return _registers.get();
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
