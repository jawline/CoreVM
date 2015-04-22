#ifndef _CORE_STATE_DEF_H_
#define _CORE_STATE_DEF_H_
#include <cstdint>

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

  public:
    CoreState();
    CoreState(uint8_t* data, unsigned int size);
    CoreState(CoreState const& existing);
    
    void setData(uint8_t* data, unsigned int size);

    inline uint32_t getRegister(unsigned int num) const {
      return _registers[num];
    }

    void setRegister(unsigned int num, uint32_t value) {
      _registers[num] = value;
    }
  };
}

#endif //_CORE_STATE_DEF_H_
