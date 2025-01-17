#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include <fmt/format.h>

#include "utils.h"
#include "contraption.h"

// LOG template fn that takes in a colour and message and uses fmt::format to format the message
template <typename... Args>
void LOG(Carbon::SM::UTILS::Colour colour, Carbon::SM::UTILS::LogType type, const std::string& message, Args&&... args) {
	Carbon::SM::UTILS::Console* console = Carbon::SM::Contraption::GetInstance()->console;

	if (console) {
		console->Log(fmt::format(fmt::runtime(message), std::forward<Args>(args)...), colour, type);
	}
}

#define INFO(...) LOG(Carbon::SM::UTILS::Colour::GREEN, Carbon::SM::UTILS::LogType::Default, __VA_ARGS__)
#define WARN(...) LOG(Carbon::SM::UTILS::Colour::YELLOW, Carbon::SM::UTILS::LogType::Default, __VA_ARGS__)
#define WARN(...) LOG(Carbon::SM::UTILS::Colour::RED, Carbon::SM::UTILS::LogType::Default, __VA_ARGS__)
