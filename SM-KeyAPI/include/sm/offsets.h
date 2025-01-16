#pragma once

#include <cstdint>

namespace SM::Offsets {
	constexpr uintptr_t loadLuaEnv = 0x54A7F0;

	namespace Rebased {
		const uintptr_t loadLuaEnv = (uintptr_t)GetModuleHandle(NULL) + SM::Offsets::loadLuaEnv;
	} // namespace Rebased
} // namespace SM::Offsets
