//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_ISA_HPP
#define CODE_ISA_HPP

#include "ISA_base.hpp"

namespace riscv_sim
{
	class R_type : public ISA_base
	{
	public:
		uint rs1 , rs2 , rd;
		R_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
		rs1(bitsrange(code , 15 , 19)) , rs2(bitsrange(code , 20 , 24)) , rd(bitsrange(code , 7 , 11)) ,
		ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			switch (bitsrange(code , 12 , 14))
			{
				case 0 : opt = bitsrange(code , 25 , 31) ? SUB : ADD;break;
				case 1 : opt = SLL;break;
				case 2 : opt = SLT;break;
				case 3 : opt = SLTU;break;
				case 4 : opt = XOR;break;
				case 5 : opt = bitsrange(code , 25 , 31) ? SRA : SRL;break;
				case 6 : opt = OR;break;
				case 7 : opt = AND;break;
			}
			ID_EX.A = reg -> access(rs1) , ID_EX.B = reg -> access(rs2);
		}

		void execute() override;
	};

	class I_type : public ISA_base
	{
	public:
		uint rs1 , rd , imm;

		I_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			rs1(bitsrange(code , 15 , 19)) , rd(bitsrange(code , 7 , 11)) ,
			imm(sign_extend(bitsrange(code , 20 , 31) , 20)) ,
			ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			switch (code & 127u)
			{
				case 19 :
					switch (bitsrange(code , 12 , 14))
					{
						case 0 : opt = ADDI;break;
						case 2 : opt = SLTI;break;
						case 3 : opt = SLTIU;break;
						case 4 : opt = XORI;break;
						case 6 : opt = ORI;break;
						case 7 : opt = ANDI;break;
						case 1 : opt = SLLI;break;
						case 5 : opt = bitsrange(code , 25 , 31) ? SRAI : SRLI;break;
					}
					break;
				case 3 :
					switch (bitsrange(code , 12 , 14))
					{
						case 0 : opt = LB;break;
						case 1 : opt = LH;break;
						case 2 : opt = LW;break;
						case 4 : opt = LBU;break;
						case 5 : opt = LHU;break;
					}
					break;
				case 103 : opt = JALR;break;
			}
			ID_EX.A = reg -> access(rs1) , ID_EX.Imm = imm;
		}

		void execute() override;
	};

	class S_type : public ISA_base
	{
	public:
		uint rs1 , rs2 , imm;

		S_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			rs1(bitsrange(code , 15 , 19)) , rs2(bitsrange(code , 20 , 24)) ,
			imm(sign_extend(bitsrange(code , 7 , 11) | bitsrange(code , 25 , 31) << 5 , 20)) ,
			ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			switch (bitsrange(code , 12 , 14))
			{
				case 0 : opt = SB;break;
				case 1 : opt = SH;break;
				case 2 : opt = SW;break;
			}
			ID_EX.A = reg -> access(rs1) , ID_EX.B = reg -> access(rs2) , ID_EX.Imm = imm;
		}

		void execute() override;
	};

	class B_type : public ISA_base
	{
	public:
		uint rs1 , rs2 , imm;

		B_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			rs1(bitsrange(code , 15 , 19)) , rs2(bitsrange(code , 20 , 24)) ,
			imm(sign_extend((code >> 7 & 1) << 11 | bitsrange(code , 8 , 11) << 1 | bitsrange(code , 25 , 30) << 5 | (code >> 31 & 1) << 12 , 19)) ,
			ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			switch (bitsrange(code , 12 , 14))
			{
				case 0 : opt = BEQ;break;
				case 1 : opt = BNE;break;
				case 4 : opt = BLT;break;
				case 5 : opt = BGE;break;
				case 6 : opt = BLTU;break;
				case 7 : opt = BGEU;break;
			}
			ID_EX.A = reg -> access(rs1) , ID_EX.B = reg -> access(rs2) , ID_EX.Imm = imm;
		}

		void execute() override;
	};

	class U_type : public ISA_base
	{
	public:
		uint rd , imm;

		U_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			rd(bitsrange(code , 7 , 11)) ,
			imm(bitsrange(code , 12 , 31) << 12) ,
			ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			opt = (code & 127u) == 55 ? LUI : AUIPC;
			ID_EX.Imm = imm;
		}

		void execute() override;
	};

	class J_type : public ISA_base
	{
	public:
		uint rd , imm;

		J_type(uint code , memory *mem_ , register_manager *reg_ , ALU *alu_ , IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) :
			rd(bitsrange(code , 7 , 11)) ,
			imm(sign_extend(bitsrange(code , 12 , 19) << 12 | (code >> 20 & 1) << 11 | bitsrange(code , 21 , 30) << 1 | (code >> 31 & 1) << 20 , 11)) ,
			ISA_base(code , mem_ , reg_ , alu_ , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_)
		{
			opt = JAL;
			ID_EX.Imm = imm;
		}

		void execute() override;
	};

	class NO_type : public ISA_base
	{
	public:
		NO_type(IF_ID_reg &IF_ID_ , ID_EX_reg &ID_EX_ , EX_MEM_reg &EX_MEM_ , MEM_WB_reg &MEM_WB_) : ISA_base(0 , nullptr , nullptr , nullptr , IF_ID_ , ID_EX_ , EX_MEM_ , MEM_WB_) {}

		void execute() override {}
	};
}

#endif //CODE_ISA_HPP
