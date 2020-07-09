//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_INC_HPP
#define CODE_INC_HPP

#include <iostream>
#include <cstring>
#include <string>

namespace riscv_sim
{
	typedef unsigned int uint;

	enum formatType
	{
		R_TYPE , I_TYPE , S_TYPE , B_TYPE , U_TYPE , J_TYPE
	};

	enum opType
	{
		LUI ,
		AUIPC ,
		JAL ,
		JALR ,
		BEQ , BNE , BLT , BGE , BLTU , BGEU ,
		LB , LH , LW , LBU , LHU ,
		SB , SH , SW ,
		ADDI , SLTI , SLTIU , XORI , ORI , ANDI , SLLI , SRLI , SRAI ,
		ADD , SUB , SLL , SLT , SLTU , XOR , SRL , SRA , OR , AND
	};

	formatType getformatType(uint);

	uint bitsrange(uint , int , int);

	uint sign_extend(uint , int);
}

#endif //CODE_INC_HPP
