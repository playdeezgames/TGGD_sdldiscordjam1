#pragma once
#include <tuple>
struct Colors
{
	Colors() = delete;
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> BLACK = std::make_tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0);
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> GREEN = std::make_tuple<uint8_t, uint8_t, uint8_t>(0, 170, 0);
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> GRAY = std::make_tuple<uint8_t, uint8_t, uint8_t>(170, 170, 170);
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> YELLOW = std::make_tuple<uint8_t, uint8_t, uint8_t>(255, 255, 0);
	static constexpr std::tuple<uint8_t, uint8_t, uint8_t> WHITE = std::make_tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255);
};
