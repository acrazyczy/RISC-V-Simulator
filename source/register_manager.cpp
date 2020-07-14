//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "register_manager.hpp"

namespace riscv_sim
{
	uint register_manager::getpc()
	{
		IF_ID.pc = IF_ID.npc , IF_ID.npc += 4;
		return IF_ID.pc;
	}
}