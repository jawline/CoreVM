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
		
		inline int registerAsInt(unsigned int const& registerNumber) {
			return ((int*)&_registers[registerNumber])[0];
		}

		inline void registerSetInt(unsigned int const& registerNumber, int const& val) {
			((int*)&_registers[registerNumber])[0] = val;
		}

	public:
		Core();
		~Core();

		void setData(uint8_t* data, unsigned int dataSize);
		void run();

		/**
		 * Instruction functions
		 */
		static void noOp(Core*);
		static void loadImmediate(Core*);

		/**
		 * Immediate op implementation
		 */
		static void addImmediate(Core*);
		static void subtractImmediate(Core*);
		static void multiplyImmediate(Core*);
		static void divideImmediate(Core*);
		static void greaterThanImmediate(Core*);
		static void lessThanImmediate(Core*);

		/**
		 * Register op implementations
		 */
		static void addRegister(Core*);
		static void subtractRegister(Core*);
		static void multiplyRegister(Core*);
		static void divideRegister(Core*);
		static void greaterThanRegister(Core*);
		static void lessThanRegister(Core*);

		/**
		 * Memory op implementations
		 */
		static void setMemoryInt(Core*);
		static void getMemoryInt(Core*);

		/**
		 * Unconditional jumps
		 */
		static void jumpImmediate(Core*);
		static void jumpRegister(Core*);

		/**
		 * Branching conditions
		 */
		static void jumpIfEqualImmediate(Core*);
		static void jumpIfNotEqualImmediate(Core*);
		static void jumpIfEqualRegister(Core*);
		static void jumpIfNotEqualRegister(Core*);
	};
}

#endif //_VM_CORE_DEF_H_