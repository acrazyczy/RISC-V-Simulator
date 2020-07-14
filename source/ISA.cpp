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
		{
			switch (opt)
			{
				case ADD : case SUB :
					opt == ADD ? alu -> add(ID_EX.A , ID_EX.B) : alu -> sub(ID_EX.A , ID_EX.B);
					break;
				case SLT : case SLTU :
					opt == SLT ? alu -> lt(ID_EX.A , ID_EX.B) : alu -> ltu(ID_EX.A , ID_EX.B);
					break;
				case AND :
					alu -> __and(ID_EX.A , ID_EX.B);
					break;
				case OR :
					alu -> __or(ID_EX.A , ID_EX.B);
					break;
				case XOR :
					alu -> __xor(ID_EX.A , ID_EX.B);
					break;
				case SLL :
					alu -> sll(ID_EX.A , ID_EX.B & 31u);
					break;
				case SRL :
					alu -> srl(ID_EX.A , ID_EX.B & 31u);
					break;
				case SRA :
					alu -> sra(ID_EX.A , ID_EX.B & 31u);
					break;
			}
			EX_MEM.Cond = 0 , EX_MEM.npc = ID_EX.npc;
		}
		else if (stage == 3) MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
		else if (stage == 4) reg -> access(rd) = MEM_WB.ALU;
	}

	void I_type::execute()
	{
		++ stage;
		switch (opt)
		{
			case ADDI : if (stage == 2) alu -> add(ID_EX.A , ID_EX.Imm);break;
			case SLTI : case SLTIU : if (stage == 2) opt == SLTI ? alu -> lt(ID_EX.A , ID_EX.Imm) : alu -> ltu(ID_EX.A , ID_EX.Imm);break;
			case ANDI : case ORI : case XORI : if (stage == 2) opt == ANDI ? alu -> __and(ID_EX.A , ID_EX.Imm) : (opt == ORI ? alu -> __or(ID_EX.A , ID_EX.Imm) : alu -> __xor(ID_EX.A , ID_EX.Imm));break;
			case SLLI : case SRLI : case SRAI : if (stage == 2) opt == SLLI ? alu -> sll(ID_EX.A , ID_EX.Imm & 31u) : (opt == SRLI ? alu -> srl(ID_EX.A , ID_EX.Imm & 31u) : alu -> sra(ID_EX.A , ID_EX.Imm & 31u));break;
			case JALR : if (stage == 2) alu -> add(ID_EX.A , ID_EX.Imm) , EX_MEM.ALU ^= EX_MEM.ALU & 1;break;
			default :
				if (stage == 2) alu -> add(ID_EX.A , ID_EX.Imm);
				else if (stage == 3)
				{
					if (mem -> access(reinterpret_cast<ISA_base *>(this)))
						switch (opt)
						{
							case LB : case LBU :
								mem -> load_8bits(EX_MEM.ALU , MEM_WB.LMD);
								if (opt == LBU) MEM_WB.LMD = sign_extend(MEM_WB.LMD , 24);
								break;
							case LH : case LHU :
								mem -> load_16bits(EX_MEM.ALU , MEM_WB.LMD);
								if (opt == LHU) MEM_WB.LMD = sign_extend(MEM_WB.LMD , 16);
								break;
							case LW : mem -> getcode(EX_MEM.ALU , MEM_WB.LMD);break;
						}
					else -- stage;
				}
				else if (stage == 4) reg -> access(rd) = MEM_WB.LMD;
		}
		if (stage == 2) EX_MEM.Cond = 0 , EX_MEM.npc = ID_EX.npc;
		else if (stage == 3) MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
		else if (stage == 4 && opt != LB && opt != LBU && opt != LH && opt != LHU && opt != LW) reg -> access(rd) = opt == JALR ? MEM_WB.npc : MEM_WB.ALU;
	}

	void B_type::execute()
	{
		++ stage;
		if (stage == 2)
		{
			switch (opt)
			{
				case BEQ : EX_MEM.Cond = ID_EX.A == ID_EX.B;break;
				case BNE : EX_MEM.Cond = ID_EX.A != ID_EX.B;break;
				case BLT : EX_MEM.Cond = static_cast<int>(ID_EX.A) < static_cast<int>(ID_EX.B);break;
				case BLTU : EX_MEM.Cond = ID_EX.A < ID_EX.B;break;
				case BGE : EX_MEM.Cond = static_cast<int>(ID_EX.A) >= static_cast<int>(ID_EX.B);break;
				case BGEU : EX_MEM.Cond = ID_EX.A >= ID_EX.B;break;
			}
			EX_MEM.Cond ^= ID_EX.Cond , EX_MEM.npc = ID_EX.npc , alu -> add(ID_EX.pc , ID_EX.Imm);
		}
		else if (stage == 3) MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
	}

	void U_type::execute()
	{
		++ stage;
		if (stage == 2) EX_MEM.Cond = 0 , EX_MEM.npc = ID_EX.npc , alu -> add(opt == LUI ? 0 : ID_EX.pc , ID_EX.Imm);
		else if (stage == 3) MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
		else if (stage == 4) reg -> access(rd) = MEM_WB.ALU;
	}

	void S_type::execute()
	{
		++ stage;
		if (stage == 2) alu -> add(ID_EX.A , ID_EX.Imm) , EX_MEM.Cond = 0 , EX_MEM.npc = ID_EX.npc , EX_MEM.B = ID_EX.B;
		else if (stage == 3)
		{
			if (mem -> access(reinterpret_cast<ISA_base *>(this)))
			{
				switch (opt)
				{
					case SB : mem -> store_8bits(EX_MEM.ALU , EX_MEM.B & 255u);break;
					case SH : mem -> store_16bits(EX_MEM.ALU , EX_MEM.B & 65535u);break;
					case SW : mem -> store_32bits(EX_MEM.ALU , EX_MEM.B);break;
				}
				MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
			}else -- stage;
		}
	}

	void J_type::execute()
	{
		++ stage;
		if (stage == 2) alu -> add(ID_EX.pc , ID_EX.Imm) , EX_MEM.Cond = 0 , EX_MEM.npc = ID_EX.npc;
		else if (stage == 3) MEM_WB.ALU = EX_MEM.ALU , MEM_WB.npc = EX_MEM.npc;
		else if (stage == 4) reg -> access(rd) = MEM_WB.npc;
	}
}