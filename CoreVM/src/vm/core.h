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
		std::function<void()>* _jumpTable;
		
		/**
		 * Instruction interrupt table
		 */
		std::function<void(Core*)>* _intTable;

		void setupJumpTable();
		void setupIntTable();
	public:
		Core(uint8_t* data, unsigned int dataSize);
		~Core();

		inline uint32_t getProgramCounter() {
			return _state->getRegisterUInt(ProgramCounter);
		}
		
		inline void setProgramCounter(uint32_t pc) {
			_state->setRegisterUInt(ProgramCounter, pc);
		}

		CoreState* getState();
		
		void run();
		void registerInterrupt(uint8_t interruptNumber, std::function<void(Core*)> callback);

		/**
		 * Instruction functions
		 */
		void noOp();
		void loadImmediate();
		void move();

		/**
		 * Immediate op implementation
		 */
		void addImmediate();
		void subtractImmediate();
		void multiplyImmediate();
		void divideImmediate();
		void greaterThanImmediate();
		void lessThanImmediate();

		/**
		 * Register op implementations
		 */
		void addRegister();
		void subtractRegister();
		void multiplyRegister();
		void divideRegister();
		void greaterThanRegister();
		void lessThanRegister();

		/**
		 * Memory op implementations
		 */
		void setMemoryInt();
		void getMemoryInt();
		void setMemoryIntRegister();
		void getMemoryIntRegister();

		/**
		 * Unconditional jumps
		 */
		void jumpImmediate();
		void jumpRegister();

		/**
		 * Branching conditions
		 */
		void jumpEqualImmediateImmediate();
		void jumpNotEqualImmediateImmediate();
		void jumpEqualRegisterImmediate();
		void jumpNotEqualRegisterImmediate();

		void jumpEqualImmediateRegister();
		void jumpNotEqualImmediateRegister();
		void jumpEqualRegisterRegister();
		void jumpNotEqualRegisterRegister();
		
		void interrupt();
	};
}

#endif //_VM_CORE_DEF_H_
