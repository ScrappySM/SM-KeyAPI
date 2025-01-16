#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include <unordered_map>
#include <algorithm>

enum KeyState {
	IDLE = 0,
	JUST_PRESSED = 1,
	HELD = 2,
	RELEASED = 3
};

int GetVirtualKeyCode(const std::string& keyName) {
    static const std::unordered_map<std::string, int> keyMap = {
        {"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'},
        {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},
        {"enter", VK_RETURN}, {"space", VK_SPACE}, {"shift", VK_SHIFT},
        {"ctrl", VK_CONTROL}, {"alt", VK_MENU}, {"tab", VK_TAB},
        {"escape", VK_ESCAPE}, {"backspace", VK_BACK}, {"delete", VK_DELETE},
        {"left", VK_LEFT}, {"right", VK_RIGHT}, {"Up", VK_UP}, {"Down", VK_DOWN},
		{"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4}, {"f5", VK_F5},
		{"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8}, {"f9", VK_F9}, {"f10", VK_F10},
		{"f11", VK_F11}, {"f12", VK_F12},
		{"num0", VK_NUMPAD0}, {"num1", VK_NUMPAD1}, {"num2", VK_NUMPAD2}, {"num3", VK_NUMPAD3}, {"num4", VK_NUMPAD4},
		{"num5", VK_NUMPAD5}, {"num6", VK_NUMPAD6}, {"num7", VK_NUMPAD7}, {"num8", VK_NUMPAD8}, {"num9", VK_NUMPAD9},
		{"num*", VK_MULTIPLY}, {"num+", VK_ADD}, {"num-", VK_SUBTRACT}, {"num.", VK_DECIMAL}, {"num/", VK_DIVIDE},
		{"numLock", VK_NUMLOCK}, {"scrolllock", VK_SCROLL},
		{"capsLock", VK_CAPITAL}, {"printscreen", VK_SNAPSHOT}, {"pause", VK_PAUSE},
		{"insert", VK_INSERT}, {"home", VK_HOME}, {"end", VK_END}, {"pageup", VK_PRIOR}, {"pagedown", VK_NEXT},
		{"lshift", VK_LSHIFT}, {"rshift", VK_RSHIFT}, {"lctrl", VK_LCONTROL}, {"rctrl", VK_RCONTROL},
		{"lalt", VK_LMENU}, {"ralt", VK_RMENU}, {"lwin", VK_LWIN}, {"rwin", VK_RWIN}
    };

	std::string localKeyName = keyName;
	std::transform(localKeyName.begin(), localKeyName.end(), localKeyName.begin(), ::tolower);

	// If it's 1 letter, it's probably a character, just return the ASCII value
	if (localKeyName.size() == 1) {
		std::transform(localKeyName.begin(), localKeyName.end(), localKeyName.begin(), ::toupper);
		return localKeyName[0];
	}

	auto it = keyMap.find(localKeyName);
    if (it != keyMap.end()) {
        return it->second;
    }

    return 0; // Invalid key
}

// perf: need to optimize this (use game InputManager?)
KeyState getKeyState(const std::string& key) {
	static std::unordered_map<int, bool> keyStates = {};

	int keyCode = GetVirtualKeyCode(key);
	SHORT keyState = GetAsyncKeyState(keyCode);
	bool currentlyPressed = (keyState & 0x8000) != 0; // MSB is set if key is down
	
	KeyState state = IDLE;
	if (keyStates.find(keyCode) == keyStates.end()) {
		if (currentlyPressed) {
			keyStates[keyCode] = true;
			state = JUST_PRESSED;
		}
	}
	else {
		if (currentlyPressed) {
			if (keyStates[keyCode]) {
				state = HELD;
			}
			else {
				keyStates[keyCode] = true;
				state = JUST_PRESSED;
			}
		}
		else {
			if (keyStates[keyCode]) {
				keyStates[keyCode] = false;
				state = RELEASED;
			}
		}
	}

	return state;
}
