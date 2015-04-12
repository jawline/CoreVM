#ifndef _VM_CORE_DEF_H_
#define _VM_CORE_DEF_H_
#include <cstdint>
#include <functional>
#include "instructions.h"
#include "registers.h"

namespace VM {
	class Core {
	private:
		uint32_t* _registers;

		std::function<void(Core*)>* _jumpTable;

		uint8_t* _data;
		unsigned int _maxData;

		void setupJumpTable();
		
		inline int rAsInt(unsigned int const& registerNumber) {
			return *((int*)&_registers[registerNumber]);
		}

		inline void rSetInt(unsigned int const& registerNumber, int const& val) {
			*((int*)&_registers[registerNumber]) = val;
		}

	public:
		Core();
		~Core();

		void setData(uint8_t* data, unsigned int dataSize);
		void run();

		static void noOp(Core*);
		static void loadImmediate(Core*);
		static void jumpImmediate(Core*);
		static void addRegister(Core*);
		static void subtractRegister(Core*);
		static void multiplyRegister(Core*);
		static void divideRegister(Core*);
	};
}

#endif //_VM_CORE_DEF_H_