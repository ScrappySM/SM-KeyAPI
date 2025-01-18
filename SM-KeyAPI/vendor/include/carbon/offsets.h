#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define REBASE_IMPL(name) const uintptr_t name = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + Raw::name

namespace Carbon::Offsets {
	namespace Raw {
		constexpr uintptr_t Contraption = 0x1267538; // names -> contraption::`vftable` -> xref -> xref -> qword
		constexpr uintptr_t LuaManager = 0x1267620;
		constexpr uintptr_t UpdateFunc = 0x343030;
		constexpr uintptr_t LoadLuaEnvFunc = 0x54A7F0;
	} // namespace Raw

	namespace Rebased {
		REBASE_IMPL(Contraption);
		REBASE_IMPL(LuaManager);
		REBASE_IMPL(UpdateFunc);
		REBASE_IMPL(LoadLuaEnvFunc);
	} // namespace Rebased
} // namespace Carbon::Offsets
