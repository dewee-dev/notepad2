#include "EditLexer.h"
#include "EditStyleX.h"

// https://www.latex-project.org/

static KEYWORDLIST Keywords_TEX = {{
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL

, NULL, NULL, NULL, NULL, NULL, NULL, NULL
}};

static EDITSTYLE Styles_TEX[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_L_COMMAND, NP2StyleX_Command, L"fore:#0000FF" },
	{ MULTI_STYLE(SCE_L_COMMENT, SCE_L_COMMENT2, 0, 0), NP2StyleX_Comment, L"fore:#608060" },
	{ SCE_L_TITLE, NP2StyleX_Title, L"fore:#008000" },
	{ SCE_L_CHAPTER, NP2StyleX_Chapter, L"fore:#008000" },
	{ MULTI_STYLE(SCE_L_SECTION, SCE_L_SECTION1, SCE_L_SECTION2, 0), NP2StyleX_Section, L"fore:#008000" },
	{ MULTI_STYLE(SCE_L_MATH, SCE_L_MATH2, 0, 0), NP2StyleX_Math, L"fore:#FF0000" },
	{ SCE_L_SPECIAL, NP2StyleX_SpecialCharacter, L"fore:#3A6EA5" },
	{ MULTI_STYLE(SCE_L_TAG, SCE_L_TAG2, 0, 0), NP2StyleX_Tag, L"fore:#FF8000" },
	{ SCE_L_CMDOPT, NP2StyleX_Option, L"fore:#1E90FF" },
	{ SCE_L_STRING, NP2StyleX_String, L"fore:#008000" },
	{ MULTI_STYLE(SCE_L_QUOTE1, SCE_L_QUOTE2, 0, 0), NP2StyleX_Quote, L"fore:#408080" },
	{ MULTI_STYLE(SCE_L_VERBATIM, SCE_L_VERBATIM2, 0, 0), NP2StyleX_VerbatimSegment, L"fore:#666666" },
	{ SCE_L_LISTCODE, NP2StyleX_ListCode, L"fore:#808080" },
	{ SCE_L_OPERATOR, NP2StyleX_Operator, L"fore:#B000B0" },
};

EDITLEXER lexLaTeX = {
	SCLEX_LATEX, NP2LEX_LATEX,
	SCHEME_SETTINGS_DEFAULT,
	EDITLEXER_HOLE(L"LaTeX File", Styles_TEX),
	L"tex; latex; sty; cls; tpx; bbl; bib; ltx; dtx; ins; toc; info",
	&Keywords_TEX,
	Styles_TEX
};
