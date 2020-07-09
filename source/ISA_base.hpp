//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_ISA_BASE_HPP
#define CODE_ISA_BASE_HPP

#include "memory.hpp"
#include "register_manager.hpp"
#include "ALU.hpp"
#include "inc.hpp"

namespace riscv_sim
{
	class ISA_base
	{
	protected:
		opType opt;
		uint code_;
		int stage;
		memory *mem;
		register_manager *reg;
		ALU *alu;
	public:
		ISA_base(uint &code , memory *mem_ , register_manager *reg_ , ALU *alu_) : code_(code) , stage(1) , mem(mem_) , reg(reg_) , alu(alu_) {}

		virtual void execute() = 0;

		bool is_exit() const {return code_ == 0x0ff00513;}
	};
}

#endif //CODE_ISA_BASE_HPP
