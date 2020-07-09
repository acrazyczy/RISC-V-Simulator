//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "ISA.hpp"

namespace riscv_sim
{
	void R_type::execute()
	{
		++ stage;
		if (stage == 2)
			switch (opt)
			{
				case ADD : case SUB :
					opt == ADD ? alu -> add(reg -> A , reg -> B) : alu -> sub(reg -> A , reg -> B);
					break;
				case SLT : case SLTU :
					opt == SLT ? alu -> lt(reg -> A , reg -> B) : alu -> ltu(reg -> A , reg -> B);
					break;
				case AND :
					alu -> __and(reg -> A , reg -> B);
					break;
				case OR :
					alu -> __or(reg -> A , reg -> B);
					break;
				case XOR :
					alu -> __xor(reg -> A , reg -> B);
					break;
				case SLL :
					alu -> sll(reg -> A , reg -> B & 31u);
					break;
				case SRL :
					alu -> srl(reg -> A , reg -> B & 31u);
					break;
				case SRA :
					alu -> sra(reg -> A , reg -> B & 31u);
					break;
			}
		else if (stage == 3) reg -> pc = reg -> npc;
		else if (stage == 4) reg -> access(rd) = reg -> ALU;
	}

	void I_type::execute()
	{
		++ stage;
		switch (opt)
		{
			case ADDI :
				if (stage == 2) alu -> add(reg -> A , reg -> Imm);
				else if (stage == 3) reg -> pc = reg -> npc;
				else if (stage == 4) reg -> access(rd) = reg -> ALU;
				break;
			case SLTI : case SLTIU :
				if (stage == 2) opt == SLTI ? alu -> lt(reg -> A , reg -> Imm) : alu -> ltu(reg -> A , reg -> Imm);
				else if (stage == 3) reg -> pc = reg -> npc;
				else if (stage == 4) reg -> access(rd) = reg -> ALU;
				break;
			case ANDI : case ORI : case XORI :
				if (stage == 2) opt == ANDI ? alu -> __and(reg -> A , reg -> Imm) : (opt == ORI ? alu -> __or(reg -> A , reg -> Imm) : alu -> __xor(reg -> A , reg -> Imm));
				else if (stage == 3) reg -> pc = reg -> npc;
				else if (stage == 4) reg -> access(rd) = reg -> ALU;
				break;
			case SLLI : case SRLI : case SRAI :
				if (stage == 2) opt == SLLI ? alu -> sll(reg -> A , reg -> Imm & 31u) : (opt == SRLI ? alu -> srl(reg -> A , reg -> Imm & 31u) : alu -> sra(reg -> A , reg -> Imm & 31u));
				else if (stage == 3) reg -> pc = reg -> npc;
				else if (stage == 4) reg -> access(rd) = reg -> ALU;
				break;
			case JALR :
				if (stage == 2) alu -> add(reg -> A , reg -> Imm) , reg -> ALU ^= reg -> ALU & 1;
				else if (stage == 3) reg -> pc = reg -> ALU;
				else if (stage == 4) reg -> access(rd) = reg -> npc;
				break;
			default :
				if (stage == 2) alu -> add(reg -> A , reg -> Imm);
				else if (stage == 3)
				{
					switch (opt)
					{
						case LB : case LBU :
							mem -> load_8bits(reg -> ALU , reg -> LMD);
							if (opt == LBU) reg -> LMD = sign_extend(reg -> LMD , 24);
							break;
						case LH : case LHU :
							mem -> load_16bits(reg -> ALU , reg -> LMD);
							if (opt == LHU) reg -> LMD = sign_extend(reg -> LMD , 16);
							break;
						case LW : mem -> getcode(reg -> ALU , reg -> LMD);break;
					}
					reg -> pc = reg -> npc;
				}
				else if (stage == 4) reg -> access(rd) = reg -> LMD;
		}
	}

	void B_type::execute()
	{
		++ stage;
		if (stage == 2)
		{
			switch (opt)
			{
				case BEQ : reg -> Cond = reg -> A == reg -> B;break;
				case BNE : reg -> Cond = reg -> A != reg -> B;break;
				case BLT : reg -> Cond = static_cast<int>(reg -> A) < static_cast<int>(reg -> B);break;
				case BLTU : reg -> Cond = reg -> A < reg -> B;break;
				case BGE : reg -> Cond = static_cast<int>(reg -> A) >= static_cast<int>(reg -> B);break;
				case BGEU : reg -> Cond = reg -> A >= reg -> B;break;
			}
			alu -> add(reg -> pc , reg -> Imm);
		}
		else if (stage == 3)
			if (reg -> Cond) reg -> pc = reg -> ALU;
			else reg -> pc = reg -> npc;
	}

	void U_type::execute()
	{
		++ stage;
		if (stage == 2) alu -> add(opt == LUI ? 0 : reg -> pc , reg -> Imm);
		else if (stage == 3) reg -> pc = reg -> npc;
		else if (stage == 4) reg -> access(rd) = reg -> ALU;
	}

	void S_type::execute()
	{
		++ stage;
		if (stage == 2) alu -> add(reg -> A , reg -> Imm);
		else if (stage == 3)
		{
			switch (opt)
			{
				case SB : mem -> store_8bits(reg -> ALU , reg -> B & 255u);break;
				case SH : mem -> store_16bits(reg -> ALU , reg -> B & 65535u);break;
				case SW : mem -> store_32bits(reg -> ALU , reg -> B);break;
			}
			reg -> pc = reg -> npc;
		}
	}

	void J_type::execute()
	{
		++ stage;
		if (stage == 2) alu -> add(reg -> pc , reg -> Imm);
		else if (stage == 3) reg -> pc = reg -> ALU;
		else if (stage == 4) reg -> access(rd) = reg -> npc;
	}
}