//
// Created by crazy_cloud on 2020/7/14.
// @formatter:off
//

#ifndef CODE_PREDICTOR_HPP
#define CODE_PREDICTOR_HPP

namespace riscv_sim
{
	static int bin[256];

	struct predictor
	{
		bool operator()(uint w) const {return bin[w & 255u] >= 2u;}//return predict value

		static void success(uint w)
		{
			bin[w & 255u] ^= ((bin[w & 255u] & 1u ^ 1u) ^ (bin[w & 255u] & 2u ^ 2u) << (bin[w & 255u] & 1u ^ 1u)) & 3u;
		}

		static void fail(uint w)
		{
			bin[w & 255u] ^= ((bin[w & 255u] & 1u) ^ (bin[w & 255u] & 2u) << (bin[w & 255u] & 1u)) & 3u;
		}
	};
}


#endif //CODE_PREDICTOR_HPP
