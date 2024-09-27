#include "EditLexer.h"
#include "EditStyleX.h"

static KEYWORDLIST Keywords_Bash = {{
//++Autogenerated -- start of section automatically generated
"alias alloc ar asa awk "
"banner basename bash bc bdiff bg bind bindkey break breaksw bs2cmd builtin builtins bunzip2 bye bzip2 "
"cal calendar caller case cat cc cd chdir chgrp chmod chown chroot cksum clear cmp "
"col comm command complete compress continue coproc cp cpio crypt csplit ctags cut "
"date dc dd declare default deroff dev df diff diff3 dir dircmp dircolors dirname dirs disown dnl do done du "
"echo echotc ed egrep elif else enable end endif endsw env esac eval ex exec exit expand export expr "
"factor false fc fg fgrep fi file filetest find fmt fold for foreach function "
"getconf getopt getopts getspath getxvers glob goto grep gres groups hash hashstat head help history hostid hup "
"iconv id if in inlib install integer jobs join kill lc let limit line link ln local log login logname logout look ls "
"m4 mail mailx make man mapfile md5sum migrate mkdir mkfifo mknod more mt mv newgrp nice nl nm no nohup notify ntps "
"od onintr pack paste patch pathchk pax pcat perl pg pinky popd pr print printenv printf ps ptx pushd pwd "
"read readarray readlink readonly red rehash repeat return rev rm rmdir rootnode "
"sched sed select seq set setenv setpath setspath settc setty setxvers sh sha1sum shift shopt shred size sleep "
"sort source spell split start stat stop strings strip stty su sum suspend switch sync "
"tac tail tar tee telltc termname test then time times touch tr trap true tsort tty type typeset "
"ulimit umask "
"unalias uname uncomplete uncompress unexpand unhash uniq universe unlimit unlink unpack unset unsetenv until users "
"uudecode uuencode "
"vdir ver vi vim vpax wait warp watchlog wc whence where which while who whoami wpaste wstart xargs yes zcat "

, // 1 bash struct
"do done elif else esac eval fi if then until while "

, // 2 variables
"AFSUSER "
"BASH BASHOPTS BASHPID BASH_ALIASES BASH_ARGC BASH_ARGV BASH_ARGV0 BASH_CMDS BASH_COMMAND BASH_COMPAT "
"BASH_ENV BASH_EXECUTION_STRING BASH_LINENO BASH_LOADABLES_PATH BASH_REMATCH BASH_SOURCE BASH_SUBSHELL "
"BASH_VERSINFO BASH_VERSION BASH_XTRACEFD "
"CATALINA_BASE CATALINA_HOME CATALINA_OPTS CDPATH CHILD_MAX CLICOLOR_FORCE "
"COLUMNS COMMAND_LINE COMPREPLY COMP_CWORD COMP_KEY COMP_LINE COMP_POINT COMP_TYPE COMP_WORDBREAKS COMP_WORDS COPROC "
"DIRSTACK DISPLAY EDITOR EMACS ENV EPOCHREALTIME EPOCHSECONDS EUID EXECIGNORE FCEDIT FIGNORE FUNCNAME FUNCNEST "
"GLOBIGNORE GROUP GROUPS "
"HISTCMD HISTCONTROL HISTFILE HISTFILESIZE HISTIGNORE HISTSIZE HISTTIMEFORMAT HOME HOST HOSTFILE HOSTNAME HOSTTYPE HPATH "
"IFS IGNOREEOF INPUTRC INSIDE_EMACS JAVA_HOME JAVA_OPTS "
"LANG LC_ALL LC_COLLATE LC_CTYPE LC_MESSAGES LC_NUMERIC LC_TIME LINENO LINES LSCOLORS LS_COLORS "
"MACHTYPE MAIL MAILCHECK MAILPATH MAPFILE NOREBIND OLDPWD OPTARG OPTERR OPTIND OSTYPE "
"PATH PIPESTATUS POSIXLY_CORRECT PPID PROMPT_COMMAND PROMPT_DIRTRIM PS0 PS1 PS2 PS3 PS4 PWD "
"RANDOM READLINE_ARGUMENT READLINE_LINE READLINE_MARK READLINE_POINT REMOTEHOST REPLY "
"SECONDS SHELL SHELLOPTS SHLVL SRANDOM SYSTYPE TERM TERMCAP TIMEFORMAT TMOUT TMPDIR UID USER VENDOR VISUAL "

, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
//--Autogenerated -- end of section automatically generated
}};

static EDITSTYLE Styles_Bash[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_SH_WORD, NP2StyleX_Keyword, L"bold; fore:#FF8000" },
	{ SCE_SH_FUNCTION, NP2StyleX_Function, L"fore:#A46000" },
	{ SCE_SH_COMMENTLINE, NP2StyleX_Comment, L"fore:#608060" },
	{ SCE_SH_STRING_DQ, NP2StyleX_DoubleQuotedString, L"fore:#008080" },
	{ SCE_SH_STRING_SQ, NP2StyleX_SingleQuotedString, L"fore:#008000" },
	{ SCE_SH_SCALAR, NP2StyleX_ScalarVar, L"fore:#808000" },
	{ SCE_SH_PARAM, NP2StyleX_ParameterExpansion, L"fore:#9E4D2A" },
	{ SCE_SH_BACKTICKS, NP2StyleX_Backticks, L"fore:#FF0080" },
	{ SCE_SH_HERE_DELIM, NP2StyleX_HeredocDelimiter, L"fore:#A46000; back:#FFFFC0; eolfilled" },
	{ SCE_SH_HERE_Q, NP2StyleX_HeredocSingleQuoted, L"fore:#A46000; back:#FFFFC0; eolfilled" },
	{ SCE_SH_NUMBER, NP2StyleX_Number, L"fore:#FF0000" },
	{ SCE_SH_OPERATOR, NP2StyleX_Operator, L"fore:#B000B0" },
	{ SCE_SH_ERROR, NP2StyleX_ParsingError, L"fore:#C80000; back:#FFFF80" },
};

EDITLEXER lexBash = {
	SCLEX_BASH, NP2LEX_BASH,
//Settings++Autogenerated -- start of section automatically generated
		LexerAttr_NoBlockComment,
		TAB_WIDTH_4, INDENT_WIDTH_4,
		(1 << 0) | (1 << 1), // level1, level2
		0,
		'\\', 0, 0,
		SCE_SH_WORD,
		0, 0,
		SCE_SH_OPERATOR, 0
		, KeywordAttr32(0, KeywordAttr_PreSorted) // keywords
		| KeywordAttr32(1, KeywordAttr_PreSorted | KeywordAttr_NoAutoComp) // bash struct
		| KeywordAttr32(2, KeywordAttr_NoLexer) // variables
		, SCE_SH_COMMENTLINE,
		SCE_SH_HERE_DELIM, SCE_SH_STRING_DQ,
//Settings--Autogenerated -- end of section automatically generated
	EDITLEXER_HOLE(L"Shell Script", Styles_Bash),
	L"sh; csh; zsh; bash; tcsh; m4; in; ac",
	&Keywords_Bash,
	Styles_Bash
};
