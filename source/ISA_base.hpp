//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_ISA_BASE_HPP
#define CODE_ISA_BASE_HPP

#include "memory.hpp"
#include "register_manager.hpp"
#include "pipeline.hpp"
#include "ALU.hpp"
#include "inc.hpp"

namespace riscv_sim
{
	class memory;

	class ISA_base
	{
	protected:
		memory *mem;
		register_manager *reg;
		ALU *alu;
	public:
		uint code_;
		formatType fmt;
		opType opt;
		int stage;
		IF_ID_reg &IF_ID;
		ID_EX_reg &ID_EX;
		EX_MEM_reg &EX_MEM;
		MEM_WB_reg &MEM_WB;

		ISA_base(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			code_(code) , fmt(getformatType(code & 127u)) , stage(1) , mem(mem_) , reg(reg_) , alu(alu_) ,
			IF_ID(IF_ID_) , ID_EX(ID_EX_) , EX_MEM(EX_MEM_) , MEM_WB(MEM_WB_)
			{}

		virtual void execute() = 0;

		bool is_exit() const {return code_ == 0x0ff00513;}
		bool is_finished() const {return stage == 4;}
	};
}

#endif //CODE_ISA_BASE_HPP
