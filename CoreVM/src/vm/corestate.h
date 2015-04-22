#ifndef _CORE_STATE_DEF_H_
#define _CORE_STATE_DEF_H_
#include <cstdint>
#include "registers.h"

namespace VM {
  class CoreState {
  private:
	/**
	 * Current register data
	 */
	uint32_t* _registers;
		
	/**
	 * RAM contents
	 */
	uint8_t* _data;
	unsigned int _dataSize;
	
	/**
	 * Should the state be copied on write
	 */
	bool _copyRegistersOnWrite;
	bool _copyDataOnWrite;

	void copyRegisters();
	void copyData();

  public:
    CoreState();
    CoreState(uint8_t* data, unsigned int size);
    CoreState(CoreState const& existing);
    
    void setData(uint8_t* data, unsigned int size);

    inline uint32_t getRegister(uint8_t registerId) const {
      return _registers[registerId];
    }

    inline void setRegister(uint8_t registerId, uint32_t value) {
    	if (_copyRegistersOnWrite) {
    		copyRegisters();
    	}
    	_registers[registerId] = value;
    }
    
    inline uint8_t getDataByte(size_t location) const {
    	return _data[location];
    }
    
    inline void setDataByte(size_t location, uint8_t val) const {
    	if (_copyDataOnWrite) {
    		copyData();
    	}
    	_data[location] = val;
    }
  };
}

#endif //_CORE_STATE_DEF_H_
