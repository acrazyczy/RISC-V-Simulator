//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "inc.hpp"

namespace riscv_sim
{
	formatType getformatType(uint code)
	{
		switch (code)
		{
			case 51 : return R_TYPE;
			case 19 : case 3 : case 103 : return I_TYPE;
			case 35 : return S_TYPE;
			case 99 : return B_TYPE;
			case 111 : return J_TYPE;
			case 23 : case 55 : return U_TYPE;
		}
	}

	uint bitsrange(uint value , int l , int r)
	{
		return (r < 31 ? (value & ((1u << r + 1) - 1u)) : value) >> l;
	}

	uint sign_extend(uint value , int w)
	{
		return static_cast<uint>((static_cast<int>(value)) << w >> w);
	}
}