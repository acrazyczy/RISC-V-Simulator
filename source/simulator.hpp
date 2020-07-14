//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_SIMULATOR_HPP
#define CODE_SIMULATOR_HPP

#include "register_manager.hpp"
#include "memory.hpp"
#include "predictor.hpp"
#include "pipeline.hpp"
#include "ISA.hpp"
#include "inc.hpp"

namespace riscv_sim
{
	class simulator
	{
	private:
		IF_ID_reg IF_ID;
		ID_EX_reg ID_EX;
		EX_MEM_reg EX_MEM;
		MEM_WB_reg MEM_WB;
		memory *mem;
		register_manager *reg;
		ALU *alu;

		ISA_base *decode(uint);

		bool forwarding(ISA_base * , uint &);
		bool forwarding(ISA_base ** , int);
		void IF();
		void ID(ISA_base *&);

	public:
		simulator() : mem(new memory) , reg(new register_manager(IF_ID)) , alu(new ALU(reg , EX_MEM)) {}

		void run();
		void answer() {std::cout << (reg -> access(10) & 255u) << std::endl;}

		~simulator() {delete mem , delete reg , delete alu;}
	};
}

#endif //CODE_SIMULATOR_HPP
