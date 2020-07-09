//
// Created by crazy_cloud on 2020/7/8.
// @formatter:off
//

#ifndef CODE_ALU_HPP
#define CODE_ALU_HPP

#include "register_manager.hpp"

namespace riscv_sim
{
	class ALU
	{
	private:
		register_manager *reg;
	public:
		ALU(register_manager *reg_) : reg(reg_) {}

		void add(uint , uint);
		void sub(uint , uint);
		void lt(uint , uint);
		void ltu(uint , uint);
		void __and(uint , uint);
		void __or(uint , uint);
		void __xor(uint , uint);
		void sll(uint , uint);
		void srl(uint , uint);
		void sra(uint , uint);
	};
}

#endif //CODE_ALU_HPP
