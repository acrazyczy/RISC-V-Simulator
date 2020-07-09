//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_SIMULATOR_HPP
#define CODE_SIMULATOR_HPP

#include "register_manager.hpp"
#include "memory.hpp"
#include "ISA.hpp"
#include "inc.hpp"

namespace riscv_sim
{
	class simulator
	{
	private:
		memory *mem;
		register_manager *reg;
		ALU *alu;

		ISA_base *decode(uint);
	public:
		simulator() : mem(new memory) , reg(new register_manager) , alu(new ALU(reg)) {}

		void run();
		void answer() {std::cout << (reg -> access(10) & 255u) << std::endl;}

		void IF();
		void ID(ISA_base *&);

		~simulator() {delete mem , delete reg , delete alu;}
	};
}

#endif //CODE_SIMULATOR_HPP
