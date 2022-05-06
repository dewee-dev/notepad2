#include "EditLexer.h"
#include "EditStyleX.h"

static KEYWORDLIST Keywords_Swift = {{
//++Autogenerated -- start of section automatically generated
"Any Protocol Self Type as associatedtype associativity async await break case catch class continue convenience "
"default defer deinit didSet do dynamic else enum extension fallthrough false fileprivate final for func get guard "
"if import in indirect infix init inout internal is lazy left let mutating nil none nonmutating "
"open operator optional override postfix precedence precedencegroup prefix private protocol public "
"repeat required rethrows return right self set some static struct subscript super switch "
"throw throws true try typealias unowned var weak where while willSet "

, // 1 directive
"available( colorLiteral( column dsohandle else elseif endif error( file fileID fileLiteral( filePath function "
"if imageLiteral( keyPath( line selector( sourceLocation( warning( "

, // 2 attribute
"GKInspectable NSApplicationMain NSCopying NSManaged UIApplicationMain autoclosure available( convention "
"discardableResult dynamicCallable dynamicMemberLookup escaping frozen inlinable main nonobjc objc objcMembers "
"propertyWrapper requires_stored_property_inits resultBuilder testable unknown usableFromInline warn_unqualified_access "

, // 3 class
"AnyClass AnyKeyPath AnyObject KeyPath PartialKeyPath WritableKeyPath "

, // 4 struct
"Array Bool Character ClosedRange Dictionary Double Float Float32 Float64 Hasher Int Int16 Int32 Int64 Int8 Mirror Range "
"Set Slice StaticString String SystemRandomNumberGenerator UInt UInt16 UInt32 UInt64 UInt8 Void "

, // 5 protocol
"Collection Comparable Equatable Error Hashable Identifiable MutableCollection OptionSet RandomNumberGenerator Sequence "
"TextOutputStream "

, // 6 enumeration
"CommandLine Never Optional Result Unicode "

, // 7 function
"abs( assert( fatalError( max( min( print( readLine( repeatElement( sequence( stride( type( zip( "

, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
//--Autogenerated -- end of section automatically generated
}};

static EDITSTYLE Styles_Swift[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_SWIFT_WORD, NP2StyleX_Keyword, L"fore:#0000FF" },
	{ SCE_SWIFT_DIRECTIVE, NP2StyleX_Directive, L"fore:#FF8000" },
	{ SCE_SWIFT_ATTRIBUTE, NP2StyleX_Attribute, L"fore:#FF8000" },
	{ SCE_SWIFT_CLASS, NP2StyleX_Class, L"fore:#0080FF" },
	{ SCE_SWIFT_STRUCT, NP2StyleX_Structure, L"fore:#0080FF" },
	{ SCE_SWIFT_PROTOCOL, NP2StyleX_Protocol, L"bold; fore:#1E90FF" },
	{ SCE_SWIFT_ENUM, NP2StyleX_Enumeration, L"fore:#FF8000" },
	{ SCE_SWIFT_FUNCTION_DEFINITION, NP2StyleX_FunctionDefinition, L"bold; fore:#A46000" },
	{ SCE_SWIFT_FUNCTION, NP2StyleX_Function, L"fore:#A46000" },
	{ MULTI_STYLE(SCE_SWIFT_COMMENTBLOCK, SCE_SWIFT_COMMENTLINE, 0, 0), NP2StyleX_Comment, L"fore:#608060" },
	{ MULTI_STYLE(SCE_SWIFT_COMMENTBLOCKDOC, SCE_SWIFT_COMMENTLINEDOC, 0, 0), NP2StyleX_DocComment, L"fore:#408040" },
	{ SCE_SWIFT_TASKMARKER, NP2StyleX_TaskMarker, L"bold; fore:#408080" },
	{ SCE_SWIFT_STRING, NP2StyleX_String, L"fore:#008000" },
	{ SCE_SWIFT_TRIPLE_STRING, NP2StyleX_TripleQuotedString, L"fore:#F08000" },
	{ MULTI_STYLE(SCE_SWIFT_STRING_ED, SCE_SWIFT_TRIPLE_STRING_ED, 0, 0), NP2StyleX_DelimitedString, L"fore:#F08000" },
	{ SCE_SWIFT_ESCAPECHAR, NP2StyleX_EscapeSequence, L"fore:#0080C0" },
	{ SCE_SWIFT_LABEL, NP2StyleX_Label, L"back:#FFC040" },
	{ SCE_SWIFT_NUMBER, NP2StyleX_Number, L"fore:#FF0000" },
	{ SCE_SWIFT_VARIABLE, NP2StyleX_Variable, L"fore:#9E4D2A" },
	{ MULTI_STYLE(SCE_SWIFT_OPERATOR, SCE_SWIFT_OPERATOR2, 0, 0), NP2StyleX_Operator, L"fore:#B000B0" },
};

EDITLEXER lexSwift = {
	SCLEX_SWIFT, NP2LEX_SWIFT,
//Settings++Autogenerated -- start of section automatically generated
	{
		LexerAttr_Default,
		TAB_WIDTH_4, INDENT_WIDTH_4
		, KeywordAttr32(0, KeywordAttr_PreSorted) // keywords
		| KeywordAttr32(1, KeywordAttr_PreSorted) // directive
		| KeywordAttr32(2, KeywordAttr_PreSorted) // attribute
		| KeywordAttr32(3, KeywordAttr_PreSorted) // class
		| KeywordAttr32(4, KeywordAttr_PreSorted) // struct
		| KeywordAttr32(5, KeywordAttr_PreSorted) // protocol
		| KeywordAttr32(6, KeywordAttr_PreSorted) // enumeration
		| KeywordAttr32(7, KeywordAttr_NoLexer) // function
	},
//Settings--Autogenerated -- end of section automatically generated
	EDITLEXER_HOLE(L"Swift Source", Styles_Swift),
	L"swift",
	&Keywords_Swift,
	Styles_Swift
};
