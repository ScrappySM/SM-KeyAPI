#pragma once

#include <memory>

#include "utils.h"
#include "offsets.h"

#include "console.h"

namespace Carbon::SM {
	enum GameStateType;

	class Contraption {
		SINGLETON(Contraption);

		/* 0x0000 */ PAD(0x58);
		/* 0x0058 */ PUB UTILS::Console* console;
		/* 0x0060 */ PAD(0x11C);
		/* 0x017C */ PUB GameStateType gameState;
	};

	enum GameStateType : uint32_t {
		Null,
		Load,
		Play,
		Menu,
		TileEditor,
		WorldBuilder,
	};
} // namespace Carbon::SM
