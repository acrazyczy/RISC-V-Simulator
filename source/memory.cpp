//
// Created by crazy_cloud on 2020/7/7.
// @formatter:off
//

#include "memory.hpp"

namespace riscv_sim
{
	memory::memory()
	{
		for (uint offset;!std::cin.eof();)
		{
			int shift = 0;
			for (std::string str;std::cin >> str;)
				if (str[0] == '@')
				{
					offset = std::stoi(str.substr(1 , str.length() - 1) , nullptr , 16);
					break;
				}
				else pool[offset + (shift ++)] = std::stoi(str , nullptr , 16);
		}
	}

	void memory::getcode(const uint &address , uint &code) {code = *reinterpret_cast<uint *>(pool + address);}

	void memory::load_8bits(const uint &address , uint &code) {code = pool[address];}

	void memory::load_16bits(const uint &address , uint &code) {code = *reinterpret_cast<unsigned short *>(pool + address);}

	void memory::store_8bits(const uint &address , const uint &code) {pool[address] = code;}

	void memory::store_16bits(const uint &address , const uint &code) {*reinterpret_cast<unsigned short *>(pool + address) = static_cast<unsigned short>(code);}

	void memory::store_32bits(const uint &address , const uint &code) {*reinterpret_cast<uint *>(pool + address) = code;}
}