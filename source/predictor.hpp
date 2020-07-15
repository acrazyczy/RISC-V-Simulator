//
// Created by crazy_cloud on 2020/7/14.
// @formatter:off
//

#ifndef CODE_PREDICTOR_HPP
#define CODE_PREDICTOR_HPP

namespace riscv_sim
{
	static const uint mask = (1u << 7) - 1;
	static unsigned char bin[mask + 1];
	static int total = 0 , succ = 0;

	struct predictor
	{
		predictor() {memset(bin , 2 , mask + 1);}

		bool operator()(uint w) const {return bin[(w >> 2) & mask] > 1u;}

		static void success(uint w)
		{
			w >>= 2;
			static unsigned char nxt[] = {0 , 0 , 3 , 3};
			bin[w & mask] = nxt[bin[w & mask]];
			++ total , ++ succ;
		}

		static void fail(uint w)
		{
			w >>= 2;
			static unsigned char nxt[] = {1 , 2 , 1 , 2};
			bin[w & mask] = nxt[bin[w & mask]];
			++ total;
		}

		~predictor() {std::cerr << "total predictions: " << total << std::endl << "successful attempts: " << succ << std::endl << "hit rate: " << (static_cast<long double>(succ) / total) << std::endl;}
	};
}


#endif //CODE_PREDICTOR_HPP
