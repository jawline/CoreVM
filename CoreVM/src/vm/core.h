#ifndef _VM_CORE_DEF_H_
#define _VM_CORE_DEF_H_
#include <cstdint>
#include <functional>
#include "instructions.h"
#include "registers.h"
#include "corestate.h"

namespace VM {
	class Core {
	private:
		/**
		 * The VM state
		 */
		 CoreState* _state;

		/**
		 * Instruction jump table
		 */
		std::function<void(Core*)>* _jumpTable;
		
		/**
		 * Instruction interrupt table
		 */
		std::function<void(Core*)>* _intTable;

		void setupJumpTable();
		void setupIntTable();
	public:
		Core();
		~Core();

		inline uint32_t getProgramCounter() {
			return state->getRegisterUInt(ProgramCounter);
		}
		
		inline void setProgramCounter(uint32_t pc) {
			state->setRegisterUInt(pc);
		}

		void setData(CoreState* state);
		void run();
		void registerInterrupt(uint8_t interruptNumber, std::function<void(Core*)> callback);

		/**
		 * Instruction functions
		 */
		static void noOp(Core*);
		static void loadImmediate(Core*);
		static void move(Core*);

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
		static void setMemoryIntRegister(Core*);
		static void getMemoryIntRegister(Core*);

		/**
		 * Unconditional jumps
		 */
		static void jumpImmediate(Core*);
		static void jumpRegister(Core*);

		/**
		 * Branching conditions
		 */
		static void jumpEqualImmediateImmediate(Core*);
		static void jumpNotEqualImmediateImmediate(Core*);
		static void jumpEqualRegisterImmediate(Core*);
		static void jumpNotEqualRegisterImmediate(Core*);

		static void jumpEqualImmediateRegister(Core*);
		static void jumpNotEqualImmediateRegister(Core*);
		static void jumpEqualRegisterRegister(Core*);
		static void jumpNotEqualRegisterRegister(Core*);
		
		static void interrupt(Core*);
	};
}

#endif //_VM_CORE_DEF_H_
