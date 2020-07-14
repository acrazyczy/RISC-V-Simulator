//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#ifndef CODE_MEMORY_HPP
#define CODE_MEMORY_HPP

#include "inc.hpp"
#include "ISA_base.hpp"

namespace riscv_sim
{
	class ISA_base;

	class memory
	{
	private:
		unsigned char pool[0x20001];
	public:
		ISA_base *lock;
		int lockcnt;

		memory();

		bool access(ISA_base *);

		void getcode(const uint & , uint &);
		void load_8bits(const uint & , uint &);
		void load_16bits(const uint & , uint &);

		void store_8bits(const uint & , const uint &);
		void store_16bits(const uint & , const uint &);
		void store_32bits(const uint & , const uint &);
	};
}

#endif //CODE_MEMORY_HPP
