// Scintilla source code edit control
/** @file CharClassify.h
 ** Character classifications used by Document and RESearch.
 **/
// Copyright 2006-2009 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.
#pragma once

namespace Scintilla::Internal {

bool DBCSIsLeadByte(int codePage, unsigned char uch) noexcept;

constexpr bool IsDBCSCodePage(int codePage) noexcept {
	return codePage == 932
		|| codePage == 936
		|| codePage == 949
		|| codePage == 950
		|| codePage == 1361;
}

constexpr bool IsDBCSValidSingleByte(int codePage, int ch) noexcept {
	switch (codePage) {
	case 932:
		return ch == 0x80
			|| (ch >= 0xA0 && ch <= 0xDF)
			|| (ch >= 0xFD);

	default:
		return false;
	}
}

//grapheme type++Autogenerated -- start of section automatically generated
enum class GraphemeBreakProperty {
	Other = 0,
	CR = 1,
	LF = 2,
	Control = 3,
	Extend = 4,
	RegionalIndicator = 5,
	Prepend = 6,
	SpacingMark = 7,
	HangulL = 8,
	HangulV = 9,
	HangulT = 10,
	HangulLV = 11,
	HangulLVT = 12,
	ExtendedPictographic = 13,
	ZeroWidthJoiner = 14,
	Sentinel = Prepend,
};

constexpr int maxUnicodeGraphemeBreakCharacter = 0xe1000;
constexpr int longestUnicodeCharacterSequenceCount = 10;
constexpr int longestUnicodeCharacterSequenceBytes = 35;

constexpr uint16_t graphemeClusterBoundary[] = {
0b10111111'01101111, // Other
0b11111111'11111011, // CR
0b11111111'11111111, // LF
0b11111111'11111111, // Control
0b10111111'01101111, // Extend
0b10111111'01001111, // RegionalIndicator
0b10000000'00001110, // Prepend
0b10111111'01101111, // SpacingMark
0b10100100'01101111, // HangulL
0b10111001'01101111, // HangulV
0b10111011'01101111, // HangulT
0b10111001'01101111, // HangulLV
0b10111011'01101111, // HangulLVT
0b10111111'01101111, // ExtendedPictographic
0b10011111'01101111, // ZeroWidthJoiner
};

constexpr bool IsGraphemeClusterBoundary(GraphemeBreakProperty prev, GraphemeBreakProperty current) noexcept {
	return (graphemeClusterBoundary[static_cast<int>(prev)] >> (static_cast<int>(current))) & true;
}
//grapheme type--Autogenerated -- end of section automatically generated

class CharClassify {
public:
	CharClassify() noexcept;

	void SetDefaultCharClasses(bool includeWordClass) noexcept;
	void SetCharClasses(const unsigned char *chars, CharacterClass newCharClass) noexcept;
	void SetCharClassesEx(const unsigned char *chars, size_t length) noexcept;
	int GetCharsOfClass(CharacterClass characterClass, unsigned char *buffer) const noexcept;
	CharacterClass GetClass(unsigned char ch) const noexcept {
		return static_cast<CharacterClass>(charClass[ch]);
	}
	bool IsWord(unsigned char ch) const noexcept {
		return GetClass(ch) == CharacterClass::word;
	}

	static void InitUnicodeData() noexcept;

//++Autogenerated -- start of section automatically generated
// Created with Python 3.13.0, Unicode 15.1.0
	static CharacterClass ClassifyCharacter(uint32_t ch) noexcept {
		if (ch < sizeof(classifyMap)) {
			return static_cast<CharacterClass>(classifyMap[ch]);
		}
		if (ch > maxUnicode) {
			// Cn
			return CharacterClass::space;
		}

		ch -= sizeof(classifyMap);
		ch = (CharClassifyTable[ch >> 11] << 8) | (ch & 2047);
		ch = (CharClassifyTable[(ch >> 6) + 512] << 6) | (ch & 63);
		ch = (CharClassifyTable[(ch >> 3) + 1536] << 3) | (ch & 7);
		return static_cast<CharacterClass>(CharClassifyTable[ch + 3056]);
	}
//--Autogenerated -- end of section automatically generated

//grapheme function++Autogenerated -- start of section automatically generated
	static GraphemeBreakProperty GetGraphemeBreakProperty(uint32_t ch) noexcept {
		if (ch >= maxUnicodeGraphemeBreakCharacter) {
			return GraphemeBreakProperty::Other;
		}
		ch = (GraphemeBreakTable[ch >> 11] << 8) | (ch & 2047);
		ch = (GraphemeBreakTable[(ch >> 6) + 450] << 6) | (ch & 63);
		ch = (GraphemeBreakTable[(ch >> 3) + 1474] << 3) | (ch & 7);
		return static_cast<GraphemeBreakProperty>(GraphemeBreakTable[ch + 3146]);
	}
//grapheme function--Autogenerated -- end of section automatically generated

private:
	static constexpr uint32_t maxUnicode = 0x10ffff;
	static const uint8_t CharClassifyTable[];
	static const uint8_t GraphemeBreakTable[];
	static uint8_t classifyMap[0xffff + 1];

	static constexpr int maxChar = 256;
	uint8_t charClass[maxChar];
};

class DBCSCharClassify {
public:
	explicit DBCSCharClassify(int codePage_) noexcept;

	bool IsLeadByte(unsigned char ch) const noexcept {
		return leadByte[ch] & true;
	}
	bool IsTrailByte(unsigned char ch) const noexcept {
		return leadByte[ch] & 2;
	}

	CharacterClass ClassifyCharacter(uint32_t ch) const noexcept {
		if (ch < sizeof(classifyMap)) {
			return static_cast<CharacterClass>(classifyMap[ch]);
		}
		// Cn
		return CharacterClass::space;
	}

private:
	uint8_t leadByte[256];
	unsigned char classifyMap[0xffff + 1];
};

}
