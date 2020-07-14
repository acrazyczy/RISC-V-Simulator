//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "simulator.hpp"

namespace riscv_sim
{
	ISA_base *simulator::decode(uint code)
	{
		formatType fmt = getformatType(code & 127u);
		switch (fmt)
		{
			case R_TYPE : return new R_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
			case I_TYPE : return new I_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
			case S_TYPE : return new S_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
			case B_TYPE : return new B_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
			case U_TYPE : return new U_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
			case J_TYPE : return new J_type(code , mem , reg , alu , IF_ID , ID_EX , EX_MEM , MEM_WB);
		}
		return nullptr;
	}

	void simulator::run()
	{
		ISA_base *pipeline[5] = {nullptr , nullptr , nullptr , nullptr , nullptr} , *if_ptr = new NO_type(IF_ID , ID_EX , EX_MEM , MEM_WB);
		predictor pd;
		while (true)
		{
			if (pipeline[0] != nullptr && pipeline[0] -> is_exit()) break;
			for (int i = 0;i < 5;++ i)
				if (pipeline[i] == nullptr)
				{
					IF() , pipeline[i] = if_ptr;
					if (getformatType(IF_ID.IR) == B_TYPE && (IF_ID.Cond = pd(IF_ID.pc))) IF_ID.npc = sign_extend((IF_ID.IR >> 7 & 1) << 11 | bitsrange(IF_ID.IR , 8 , 11) << 1 | bitsrange(IF_ID.IR , 25 , 30) << 5 | (IF_ID.IR >> 31 & 1) << 12 , 19);
					break;
				}
				else if (pipeline[i] == if_ptr)
				{
					ID(pipeline[i] = nullptr);
					if (!forwarding(pipeline , i))
					{
						delete pipeline[i] , pipeline[i] = if_ptr;
						break;
					}
					ID_EX.Cond = IF_ID.Cond , ID_EX.pc = IF_ID.pc , ID_EX.npc = IF_ID.npc;
				}
				else if (pipeline[i] -> is_exit()) break;
				else
				{
					if (pipeline[i] -> fmt == B_TYPE && pipeline[i] -> stage == 2)
					{
						if (EX_MEM.Cond == true)
						{
							for (int j = i + 1;j < 5 && pipeline[j];++ j)
							{
								if (pipeline[j] != if_ptr) delete pipeline[j];
								pipeline[j] = nullptr;
							}
							IF_ID.npc = EX_MEM.ALU;
							predictor::fail(pipeline[i] -> code_);
						}else predictor::success(pipeline[i] -> code_);
					}
					if ((pipeline[i] -> opt == JAL || pipeline[i] -> opt == JALR) && pipeline[i] -> stage == 2)
					{
						for (int j = i + 1;j < 5 && pipeline[j];++ j)
						{
							if (pipeline[j] != if_ptr) delete pipeline[j];
							pipeline[j] = nullptr;
						}
						IF_ID.npc = EX_MEM.ALU;
					}
					pipeline[i] -> execute();
					if (mem -> lock == pipeline[i]) break;
				}
			if (pipeline[0] != nullptr && pipeline[0] -> is_finished())
			{
				delete pipeline[0];
				for (int i = 1;i < 5;++ i) pipeline[i - 1] = pipeline[i];
				pipeline[4] = nullptr;
			}
		}
		delete if_ptr;
	}

	bool simulator::forwarding(ISA_base *cur , uint &result)
	{
		switch (cur -> fmt)
		{
			case R_TYPE : case I_TYPE : case U_TYPE :
				if (cur -> opt == LB || cur -> opt == LBU || cur -> opt == LH || cur -> opt == LHU || cur -> opt == LW)
					if (cur -> stage == 3) result = MEM_WB.LMD;
					else if (cur -> stage == 4) result = reg -> access(bitsrange(cur -> code_ , 7 , 11));
					else return false;
				else if (cur -> opt == JALR)
					if (cur -> stage == 0) result = IF_ID.npc;
					else if (cur -> stage == 1) result = ID_EX.npc;
					else if (cur -> stage == 2) result = EX_MEM.npc;
					else if (cur -> stage == 3) result = MEM_WB.npc;
					else result = reg -> access(bitsrange(cur -> code_ , 7 , 11));
				else if (cur -> stage == 2) result = EX_MEM.ALU;
				else if (cur -> stage == 3) result = MEM_WB.ALU;
				else if (cur -> stage == 4) result = reg -> access(bitsrange(cur -> code_ , 7 , 11));
				else return false;
				break;
			case J_TYPE :
				if (cur -> stage == 0) result = IF_ID.npc;
				else if (cur -> stage == 1) result = ID_EX.npc;
				else if (cur -> stage == 2) result = EX_MEM.npc;
				else if (cur -> stage == 3) result = MEM_WB.npc;
				else result = reg -> access(bitsrange(cur -> code_ , 7 , 11));
				break;
		}
		return true;
	}

	bool simulator::forwarding(ISA_base **pipeline , int id)
	{
		if (pipeline[id] -> fmt == U_TYPE || pipeline[id] -> fmt == J_TYPE) return true;
		bool found[2] = {false , false};uint result[2] = {ID_EX.A , ID_EX.B};
		for (int i = id - 1;i >= 0;-- i)
			if (pipeline[i] -> fmt != S_TYPE && pipeline[i] -> fmt != B_TYPE)
			{
				uint rd = bitsrange(pipeline[i] -> code_ , 7 , 11);
				if (!rd) continue;
				if (!found[0] && rd == bitsrange(pipeline[id] -> code_ , 15 , 19))
					if (forwarding(pipeline[i] , result[0])) found[0] = true;
					else return false;
				if (pipeline[id] -> fmt != I_TYPE && !found[1] && rd == bitsrange(pipeline[id] -> code_ , 20 , 24))
					if (forwarding(pipeline[i] , result[1])) found[1] = true;
					else return false;
			}
		if (found[0]) ID_EX.A = result[0];
		if (found[1]) ID_EX.B = result[1];
		return true;
	}

	void simulator::IF() {mem -> getcode(reg -> getpc() , IF_ID.IR);}

	void simulator::ID(ISA_base *&cur) {cur = decode(IF_ID.IR);}
}