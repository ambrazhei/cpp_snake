#pragma once

namespace FieldParams
{
	enum class Direction
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	enum FieldType
	{
		EMPTY_CELL_TYPE = 0,
		FRUIT_CELL_TYPE = -1,
	};

	constexpr int FIELD_SIZE_X = 35;
	constexpr int FIELD_SIZE_Y = 25;
	constexpr int CELL_SIZE = 32;

	constexpr int WINDOW_WIDTH = FIELD_SIZE_X * CELL_SIZE;
	constexpr int WINDOW_HEIGHT = FIELD_SIZE_Y * CELL_SIZE;
};