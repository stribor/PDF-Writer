#pragma once

#include "IOBasicTypes.h"

#include <string>

#include <ios>

namespace IOBasicTypes
{
struct Byte_traits
{
	using char_type = unsigned char;
	using int_type = int;
	using off_type = std::streamoff;
	using pos_type = std::fpos<std::mbstate_t>;
	using state_type = std::mbstate_t;

	static void assign(char_type &r, char_type const &a) noexcept { r = a; }
	static constexpr bool eq(char_type a, char_type b) noexcept { return a == b; }
	static constexpr bool lt(char_type a, char_type b) noexcept { return a < b; }

	static int compare(char_type const *s1,
		char_type const *s2,
		size_t n
	) noexcept
	{
		for (; n != 0; --n, ++s1, ++s2) {
			if (lt(*s1, *s2)) return -1;
			if (lt(*s2, *s1)) return 1;
		}
		return 0;
	}

	static size_t length(char_type const *s) noexcept
	{
		size_t len = 0;
		while (*s++ != 0) ++len;
		return len;
	}

	static char_type const* find(char_type const *s,
		size_t n,
		char_type a
	) noexcept
	{
		for (; n != 0; --n, ++s) {
			if (eq(*s, a)) return s;
		}
		return nullptr;
	}

	static char_type* move(char_type *dest,
		char_type const *src,
		size_t n
	) noexcept
	{
		if (n != 0) {
			std::memmove(dest, src, n * sizeof(char_type));
		}
		return dest;
	}

	static char_type* copy(char_type *dest,
		char_type const *src,
		size_t n
	) noexcept
	{
		if (n != 0) {
			std::memcpy(dest, src, n * sizeof(char_type));
		}
		return dest;
	}

	static char_type* assign(char_type *dest,
		size_t n,
		char_type a
	) noexcept
	{
		for (; n != 0; --n, ++dest) *dest = a;
		return dest;
	}

	static constexpr int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}

	static constexpr char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static constexpr bool eq_int_type(int_type x,
		int_type y
	) noexcept
	{
		return x == y;
	}

	static constexpr int_type eof() noexcept
	{
		return static_cast<int_type>(EOF);
	}

	static constexpr int_type not_eof(int_type e) noexcept
	{
		return eq_int_type(e, eof()) ? 0 : e;
	}
};
}

typedef std::basic_string<IOBasicTypes::Byte, IOBasicTypes::Byte_traits> ByteList;


ByteList stringToByteList(const std::string& inString);
ByteList substr(const ByteList& inList, IOBasicTypes::LongBufferSizeType inStart, IOBasicTypes::LongBufferSizeType inLength);
void append(ByteList& ioTargetList, const ByteList& inSource);
ByteList concat(const ByteList& inA, const ByteList& inB);
std::string ByteListToString(const ByteList& inByteList);

