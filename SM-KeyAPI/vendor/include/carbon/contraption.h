#pragma once

#include <memory>
#include <chrono>
#include <thread>

#include "utils.h"
#include "offsets.h"

#include "console.h"

namespace Carbon::SM {
	enum GameStateType : uint32_t {
		Null,
		Load,
		Play,
		Menu,
		TileEditor,
		WorldBuilder,
	};

	class Contraption {
		SINGLETON(Contraption);

		/* 0x0000 */ PAD(0x58);
		/* 0x0058 */ PUB UTILS::Console* console;
		/* 0x0060 */ PAD(0x11C);
		/* 0x017C */ PUB GameStateType gameState;

	public:
		static bool IsPlaying() {
			while (Contraption::GetInstance()->gameState <= Null || Contraption::GetInstance()->gameState > WorldBuilder) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}

			return Contraption::GetInstance()->gameState == Play;
		}
	};
} // namespace Carbon::SM
