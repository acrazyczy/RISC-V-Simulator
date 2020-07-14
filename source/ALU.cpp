//
// Created by crazy_cloud on 2020/7/8.
// @formatter:off
//

#include "ALU.hpp"

namespace riscv_sim
{
	void ALU::add(uint lhs , uint rhs) {EX_MEM.ALU = lhs + rhs;}

	void ALU::sub(uint lhs , uint rhs) {EX_MEM.ALU = lhs - rhs;}

	void ALU::lt(uint lhs , uint rhs) {EX_MEM.ALU = static_cast<int>(lhs) < static_cast<int>(rhs);}

	void ALU::ltu(uint lhs , uint rhs) {EX_MEM.ALU = lhs < rhs;}

	void ALU::__and(uint lhs , uint rhs) {EX_MEM.ALU = lhs & rhs;}

	void ALU::__or(uint lhs , uint rhs) {EX_MEM.ALU = lhs | rhs;}

	void ALU::__xor(uint lhs , uint rhs){EX_MEM.ALU = lhs ^ rhs;}

	void ALU::sll(uint lhs , uint rhs) {EX_MEM.ALU = lhs << rhs;}

	void ALU::srl(uint lhs , uint rhs) {EX_MEM.ALU = lhs >> rhs;}

	void ALU::sra(uint lhs , uint rhs) {EX_MEM.ALU = static_cast<int>(lhs) >> rhs;}
}