#pragma once
#include <infra/Config.h>

#define MUD_UNORDERED_MAP_TINYSTL
#ifndef MUD_UNORDERED_MAP_TINYSTL
#ifndef MUD_CPP_20
#include <unordered_map>
namespace mud
{
	export_ using std::unordered_map;
}
#endif
#else
#include <TINYSTL/unordered_map.h>
namespace mud
{
	template <class K, class T>
	export_ using unordered_map = tinystl::unordered_map<K, T>;
}
#endif
