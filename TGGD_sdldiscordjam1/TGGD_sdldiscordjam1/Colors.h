#pragma once
#include <tuple>
struct Colors
{
	Colors() = delete;
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> BLACK = std::make_tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0);
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> WHITE = std::make_tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255);
};
