// This file is part of Notepad4.
// See License.txt for details about distribution and modification.
//! Lexer for WebAssembly.

#include <cassert>
#include <cstring>

#include <string>
#include <string_view>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "CharacterSet.h"
#include "LexerModule.h"

using namespace Lexilla;

namespace {

// https://webassembly.github.io/spec/core/text/values.html#strings
struct EscapeSequence {
	int digitsLeft = 0;
	bool brace = false;

	// highlight any character as escape sequence.
	void resetEscapeState(int chNext) noexcept {
		digitsLeft = 1;
		brace = false;
		if (IsHexDigit(chNext)) {
			digitsLeft = 2;
		}
	}
	bool atEscapeEnd(int ch) noexcept {
		--digitsLeft;
		return digitsLeft <= 0 || !IsHexDigit(ch);
	}
};

//KeywordIndex++Autogenerated -- start of section automatically generated
enum {
	KeywordIndex_Keyword = 0,
	KeywordIndex_Type = 1,
	KeywordIndex_Instruction = 2,
};
//KeywordIndex--Autogenerated -- end of section automatically generated

constexpr bool IsInvalidIdChar(int ch) noexcept {
	// https://webassembly.github.io/spec/core/text/values.html#text-id
	return ch <= 32 || ch >= 127
		|| AnyOf(ch, '"', '(', ')', ',', ';', '[', ']', '{', '}');
}

void ColouriseWASMDoc(Sci_PositionU startPos, Sci_Position lengthDoc, int initStyle, LexerWordList keywordLists, Accessor &styler) {
	int lineStateLineComment = 0;
	int commentLevel = 0;	// nested block comment level

	int visibleChars = 0;
	Sci_PositionU prefixLen = 0;

	EscapeSequence escSeq;

	StyleContext sc(startPos, lengthDoc, initStyle, styler);
	if (sc.currentLine > 0) {
		const int lineState = styler.GetLineState(sc.currentLine - 1);
		/*
		1: lineStateLineComment
		8: commentLevel
		*/
		commentLevel = lineState >> 1;
	}

	while (sc.More()) {
		switch (sc.state) {
		case SCE_WASM_OPERATOR:
			sc.SetState(SCE_WASM_DEFAULT);
			break;

		case SCE_WASM_NUMBER:
			if (!IsDecimalNumberEx(sc.chPrev, sc.ch, sc.chNext)) {
				if (IsInvalidIdChar(sc.ch)) {
					sc.SetState(SCE_WASM_DEFAULT);
				} else {
					sc.ChangeState(SCE_WASM_IDENTIFIER);
				}
			}
			break;

		case SCE_WASM_WORD:
			if (prefixLen == 0 && sc.ch == '.') {
				prefixLen = sc.LengthCurrent();
			} else if (IsInvalidIdChar(sc.ch)) {
				char s[128];
				sc.GetCurrent(s, sizeof(s));
				if (keywordLists[KeywordIndex_Keyword].InList(s)) {
					sc.ChangeState(SCE_WASM_KEYWORD);
				} else if (keywordLists[KeywordIndex_Type].InList(s)) {
					sc.ChangeState(SCE_WASM_TYPE);
				} else if (keywordLists[KeywordIndex_Instruction].InList(s)) {
					sc.ChangeState(SCE_WASM_INSTRUCTION);
				} else if (prefixLen != 0 && prefixLen < sizeof(s)) {
					s[prefixLen] = '\0';
					if (keywordLists[KeywordIndex_Type].InList(s)) {
						// instructions with type prefix
						sc.ChangeState(SCE_WASM_INSTRUCTION);
					}
				}
				sc.SetState(SCE_WASM_DEFAULT);
			}
			break;

		case SCE_WASM_IDENTIFIER:
			if (IsInvalidIdChar(sc.ch)) {
				sc.SetState(SCE_WASM_DEFAULT);
			}
			break;

		case SCE_WASM_STRING:
			if (sc.ch == '\\' && !IsEOLChar(sc.chNext)) {
				escSeq.resetEscapeState(sc.chNext);
				sc.SetState(SCE_WASM_ESCAPECHAR);
				sc.Forward();
				if (sc.Match('u', '{')) {
					escSeq.brace = true;
					escSeq.digitsLeft = 9; // Unicode code point
					sc.Forward();
				}
			} else if (sc.ch == '\"') {
				sc.ForwardSetState(SCE_WASM_DEFAULT);
			}
			break;

		case SCE_WASM_ESCAPECHAR:
			if (escSeq.atEscapeEnd(sc.ch)) {
				if (escSeq.brace && sc.ch == '}') {
					sc.Forward();
				}
				sc.SetState(SCE_WASM_STRING);
				continue;
			}
			break;

		case SCE_WASM_COMMENTLINE:
			if (sc.atLineStart) {
				sc.SetState(SCE_WASM_DEFAULT);
			}
			break;
		case SCE_WASM_COMMENTBLOCK:
			if (sc.Match(';', ')')) {
				sc.Forward();
				--commentLevel;
				if (commentLevel == 0) {
					sc.ForwardSetState(SCE_WASM_DEFAULT);
				}
			} else if (sc.Match('(', ';')) {
				sc.Forward();
				++commentLevel;
			}
			break;
		}

		if (sc.state == SCE_WASM_DEFAULT) {
			if (sc.Match(';', ';')) {
				sc.SetState(SCE_WASM_COMMENTLINE);
				if (visibleChars == 0) {
					lineStateLineComment = SimpleLineStateMaskLineComment;
				}
			} else if (sc.Match('(', ';')) {
				sc.SetState(SCE_WASM_COMMENTBLOCK);
				sc.Forward();
				commentLevel = 1;
			} else if (sc.ch == '\"') {
				sc.SetState(SCE_WASM_STRING);
			} else if (IsNumberStart(sc.ch, sc.chNext)) {
				sc.SetState(SCE_WASM_NUMBER);
			} else if (IsLowerCase(sc.ch)) {
				sc.SetState(SCE_WASM_WORD);
				prefixLen = 0;
			} else if (isoperator(sc.ch)) {
				sc.SetState(SCE_WASM_OPERATOR);
			} else if (!IsInvalidIdChar(sc.ch)) {
				sc.SetState(SCE_WASM_IDENTIFIER);
			}
		}

		if (visibleChars == 0 && !isspacechar(sc.ch)) {
			++visibleChars;
		}
		if (sc.atLineEnd) {
			const int lineState = (commentLevel << 1) | lineStateLineComment;
			styler.SetLineState(sc.currentLine, lineState);
			visibleChars = 0;
			lineStateLineComment = 0;
		}
		sc.Forward();
	}

	sc.Complete();
}

constexpr int GetLineCommentState(int lineState) noexcept {
	return lineState & SimpleLineStateMaskLineComment;
}

void FoldWASMDoc(Sci_PositionU startPos, Sci_Position lengthDoc, int /*initStyle*/, LexerWordList /*keywordLists*/, Accessor &styler) {
	const Sci_PositionU endPos = startPos + lengthDoc;
	Sci_Line lineCurrent = styler.GetLine(startPos);
	int levelCurrent = SC_FOLDLEVELBASE;
	int lineCommentPrev = 0;
	if (lineCurrent > 0) {
		levelCurrent = styler.LevelAt(lineCurrent - 1) >> 16;
		lineCommentPrev = GetLineCommentState(styler.GetLineState(lineCurrent - 1));
	}

	int levelNext = levelCurrent;
	int lineCommentCurrent = GetLineCommentState(styler.GetLineState(lineCurrent));
	Sci_PositionU lineStartNext = styler.LineStart(lineCurrent + 1);
	lineStartNext = sci::min(lineStartNext, endPos);

	char chNext = styler[startPos];
	int styleNext = styler.StyleAt(startPos);

	while (startPos < endPos) {
		const char ch = chNext;
		const int style = styleNext;
		chNext = styler[++startPos];
		styleNext = styler.StyleAt(startPos);

		switch (style) {
		case SCE_WASM_COMMENTBLOCK: {
			const int level = (ch == '(' && chNext == ';') ? 1 : ((ch == ';' && chNext == ')') ? -1 : 0);
			if (level != 0) {
				levelNext += level;
				startPos++;
				chNext = styler[startPos];
				styleNext = styler.StyleAt(startPos);
			}
		} break;

		case SCE_WASM_OPERATOR:
			if (ch == '{' || ch == '[' || ch == '(') {
				levelNext++;
			} else if (ch == '}' || ch == ']' || ch == ')') {
				levelNext--;
			}
			break;
		}

		if (startPos == lineStartNext) {
			const int lineCommentNext = GetLineCommentState(styler.GetLineState(lineCurrent + 1));
			levelNext = sci::max(levelNext, SC_FOLDLEVELBASE);
			if (lineCommentCurrent) {
				levelNext += lineCommentNext - lineCommentPrev;
			}

			const int levelUse = levelCurrent;
			int lev = levelUse | (levelNext << 16);
			if (levelUse < levelNext) {
				lev |= SC_FOLDLEVELHEADERFLAG;
			}
			styler.SetLevel(lineCurrent, lev);

			lineCurrent++;
			lineStartNext = styler.LineStart(lineCurrent + 1);
			lineStartNext = sci::min(lineStartNext, endPos);
			levelCurrent = levelNext;
			lineCommentPrev = lineCommentCurrent;
			lineCommentCurrent = lineCommentNext;
		}
	}
}

}

LexerModule lmWASM(SCLEX_WASM, ColouriseWASMDoc, "wasm", FoldWASMDoc);
