#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define REBASE_IMPL(name) const uintptr_t name = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + Raw::name

namespace Carbon::Offsets {
	namespace Raw {
		constexpr uintptr_t Contraption = 0x1267538; // names -> contraption::`vftable` -> xref -> xref -> qword
	} // namespace Raw

	namespace Rebased {
		REBASE_IMPL(Contraption);
	} // namespace Rebased
} // namespace Carbon::Offsets
