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
			case R_TYPE : return new R_type(code , mem , reg , alu);
			case I_TYPE : return new I_type(code , mem , reg , alu);
			case S_TYPE : return new S_type(code , mem , reg , alu);
			case B_TYPE : return new B_type(code , mem , reg , alu);
			case U_TYPE : return new U_type(code , mem , reg , alu);
			case J_TYPE : return new J_type(code , mem , reg , alu);
		}
	}

	void simulator::run()
	{
		ISA_base *cur;
		while (true)
		{
			IF() , ID(cur);
			if (cur -> is_exit()) break;
			for (int i = 0;i < 3;++ i) cur -> execute();
		}
	}

	void simulator::IF() {mem -> getcode(reg -> getpc() , reg -> IR);}

	void simulator::ID(ISA_base *&cur) {cur = decode(reg -> IR);}
}