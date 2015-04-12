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
		
		inline int rAsInt(unsigned int registerNumber) {
			return *((int*)&_registers[registerNumber]);
		}
	public:
		Core();
		~Core();

		void setData(uint8_t* data, unsigned int dataSize);
		void run();

		static void noOp(Core*);
		static void loadImmediate(Core*);
		static void jumpImmediate(Core*);
		static void addImmediate(Core*);
		static void subtractImmediate(Core*);
	};
}

#endif //_VM_CORE_DEF_H_