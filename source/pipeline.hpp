//
// Created by crazy_cloud on 2020/7/14.
// @formatter:off
//

#ifndef CODE_PIPELINE_HPP
#define CODE_PIPELINE_HPP

namespace riscv_sim
{
	struct IF_ID_reg
	{
		uint pc = 0 , npc , IR , Cond;
	};

	struct ID_EX_reg
	{
		uint A , B , Imm , pc , npc , Cond;
	};

	struct EX_MEM_reg
	{
		uint ALU , Cond , npc , B;
	};

	struct MEM_WB_reg
	{
		uint ALU , LMD , npc;
	};
}

#endif //CODE_PIPELINE_HPP
