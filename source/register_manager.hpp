//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_REGISTER_MANAGER_HPP
#define CODE_REGISTER_MANAGER_HPP

#include "inc.hpp"
#include "pipeline.hpp"

namespace riscv_sim
{
	class register_manager
	{
	private:
		uint x[32];
		IF_ID_reg &IF_ID;
	public:
		uint x0shadow;

		register_manager(IF_ID_reg &IF_ID_) : IF_ID(IF_ID_) , x0shadow(0) {memset(x , 0 , sizeof x);}

		uint &access(uint id){return id ? x[id] : (x0shadow = 0);}

		uint getpc();
	};
}

#endif //CODE_REGISTER_MANAGER_HPP
