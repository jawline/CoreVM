#ifndef _VM_CORE_DEF_H_
#define _VM_CORE_DEF_H_
#include <cstdint>
#include <vector>
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
		 * List of VM states waiting to be processed
		 */
		std::vector<CoreState*> _states;

		/**
		 * Instruction jump table
		 */
		std::function<void()>* _jumpTable;
		
		/**
		 * Instruction interrupt table
		 */
		std::function<void(Core*)>* _intTable;

		/**
		 * Setup the default jump table
		 */
		void setupJumpTable();
		
		/**
		 * Setup the default interrupt table
		 */
		void setupIntTable();
		
		/**
		 * Fork the current state into two states, place a pointer to
		 * one state in left and another state in right
		 */
		void forkState(CoreState*& left, CoreState*& right);
	public:
		Core(uint8_t* data, unsigned int dataSize);
		~Core();

		inline uint32_t getProgramCounter() const {
			return getProgramCounter(_state);
		}
		
		inline uint32_t getProgramCounter(CoreState* st) const {
			return st->getRegisterUInt(ProgramCounter);
		}

		inline void setProgramCounter(uint32_t pc) {
			setProgramCounter(_state, pc);
		}

		inline void setProgramCounter(CoreState* st, uint32_t pc) {
			st->setRegisterUInt(ProgramCounter, pc);
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
