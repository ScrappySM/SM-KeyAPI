#pragma once

#include <string>

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define PAD(size) \
	private: \
    char CONCAT(pad_, __LINE__)[size];

#define PUB \
	public:

#define SINGLETON(type) \
	private: \
		void operator=(const type&) = delete; \
		type(const type&) = delete; \
	public: \
		[[nodiscard]] static type* GetInstance() { \
			return *reinterpret_cast<type**>(Carbon::Offsets::Rebased::type); \
		}