//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "register_manager.hpp"

namespace riscv_sim
{
	uint register_manager::getpc() {return npc = pc + 4 , pc;}
}