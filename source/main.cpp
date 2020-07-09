//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "simulator.hpp"
#include <fstream>

riscv_sim::simulator *sim;

int main()
{
//	std::ifstream in("/mnt/d/Academy/course/PPCA/2020/RISCV/riscv-testcases/testcases/array_test1.data");
//	std::cin.rdbuf(in.rdbuf());
	sim = new riscv_sim::simulator;
	sim -> run() , sim -> answer();
	delete sim;
	return 0;
}