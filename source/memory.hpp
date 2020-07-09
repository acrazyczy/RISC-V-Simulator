//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_MEMORY_HPP
#define CODE_MEMORY_HPP

#include "inc.hpp"

namespace riscv_sim
{
	class memory
	{
	private:
		unsigned char pool[0x20000];
	public:
		memory();

		void getcode(const uint & , uint &);
		void load_8bits(const uint & , uint &);
		void load_16bits(const uint & , uint &);

		void store_8bits(const uint & , const uint &);
		void store_16bits(const uint & , const uint &);
		void store_32bits(const uint & , const uint &);
	};
}

#endif //CODE_MEMORY_HPP
