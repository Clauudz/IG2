#pragma once

static struct Config
{
	static constexpr int BLOCK_SIZE = 30;
	static constexpr int LIFES = 3;

	static constexpr char WALL_BLOCK = 'x';
	static constexpr char EMPTY_BLOCK = 'o';
	static constexpr char SINBAD_CHAR = 'h';
	static constexpr char VILLAIN_CHAR = 'v';
	static constexpr char SPECIAL_VILLAIN_CHAR = 'V';
	static constexpr char INVISIBLE_BLOCK = 'i';
	static constexpr char FAKE_BLOCK = 'f';
	static constexpr char BREAKABLE_BLOCK = 'b';

	static constexpr const char* SPECIAL_VILLAIN_MAT = "Skin";
	static constexpr const char* ROTATINGPART_1_MAT = "Ajedrez";
	static constexpr const char* ROTATINGPART_2_MAT = "Water";
};