//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_REGISTER_MANAGER_HPP
#define CODE_REGISTER_MANAGER_HPP

#include "inc.hpp"

namespace riscv_sim
{
	class register_manager
	{
	private:
		uint x[32];
	public:
		uint pc , npc , A , B , Imm , ALU , LMD , Cond , x0shadow , IR;

		register_manager() : pc(0) , x0shadow(0) {memset(x , 0 , sizeof x);}

		uint &access(uint id){return id ? x[id] : (x0shadow = 0);}

		uint getpc();
	};
}

#endif //CODE_REGISTER_MANAGER_HPP
