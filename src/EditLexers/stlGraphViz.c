#include "EditLexer.h"
#include "EditStyleX.h"

static KEYWORDLIST Keywords_Dot = {{
//++Autogenerated -- start of section automatically generated
"digraph edge false graph node strict subgraph true "

, // 1 html labels
"B BR FONT HR I IMG O S SUB SUP TABLE TD TR U VR "

, // 2 attributes
"ALIGN BALIGN BGCOLOR BORDER CELLBORDER CELLPADDING CELLSPACING COLOR COLSPAN COLUMNS Damping FACE FIXEDSIZE "
"GRADIENTANGLE HEIGHT HREF ID K POINT-SIZE PORT ROWS ROWSPAN SCALE SIDES SRC STYLE TARGET TITLE TOOLTIP URL VALIGN WIDTH "
"_background area arrowhead arrowsize arrowtail bb bgcolor "
"center charset class clusterrank color colorscheme comment compound concentrator constraint "
"decorate defaultdist dim dimen dir diredgeconstraints distortion dpi "
"edgeURL edgehref edgetarget edgetooltip epsilon esep "
"fillcolor fixedsize fontcolor fontname fontnames fontpath fontsize forcelabels gradientangle group "
"headURL head_lp headclip headhref headlabel headport headtarget headtooltip height href "
"id image imagepath imagepos imagescale inputscale "
"label labelURL label_scheme labelangle labeldistance labelfloat labelfontcolor labelfontname labelfontsize labelhref "
"labeljust labelloc labeltarget labeltooltip landscape layer layerlistsep layers layerselect layersep layout "
"len levels levelsgap lhead lheight lp ltail lwidth "
"margin maxiter mclimit mindist minlen mode model mosek newrank nodesep nojustify normalize notranslate nslimit nslimit1 "
"ordering orientation outputorder overlap overlap_scaling overlap_shrink "
"pack packmode pad page pagedir pencolor penwidth peripheries pin pos quadtree quantum "
"rank rankdir ranksep ratio rects regular remincross repulsiveforce resolution root rotate rotation "
"samehead sametail samplepoints scale searchsize sep shape shapefile showboxes sides size skew smoothing sortv splines "
"start style stylesheet "
"tailURL tail_lp tailclip tailhref taillabel tailport tailtarget tailtooltip target tooltip truecolor "
"vertices viewport voro_margin weight width xdotversion xlabel xlp "

, // 3 node shapes
"Mcircle Mdiamond Msquare assembly box box3d cds circle component crow curve cylinder "
"diamond dot doublecircle doubleoctagon egg ellipse fivepoverhang folder hexagon house "
"icurve insulator inv invhouse invtrapezium invtriangle "
"larrow lbox lcrow lcurve ldiamond licurve linv lnormal lpromoter ltee lvee normal note noverhang "
"obox octagon odiamond odot oinv olbox oldiamond olinv olnormal onormal orbox ordiamond orinv ornormal oval "
"parallelogram pentagon plain plaintext point polygon primersite promoter proteasesite proteinstab "
"rarrow rbox rcrow rcurve rdiamond rect rectangle restrictionsite ribosite ricurve rinv rnastab rnormal rpromoter rtee "
"rvee "
"septagon signature square star tab tee terminator threepoverhang trapezium triangle tripleoctagon underline utr vee "

, // 4 color names
"aliceblue antiquewhite aqua aquamarine azure beige bisque black blanchedalmond blue blueviolet brown burlywood "
"cadetblue chartreuse chocolate coral cornflowerblue cornsilk crimson cyan "
"darkblue darkcyan darkgoldenrod darkgray darkgreen darkgrey darkkhaki darkmagenta darkolivegreen darkorange darkorchid "
"darkred darksalmon darkseagreen darkslateblue darkslategray darkslategrey darkturquoise darkviolet deeppink deepskyblue "
"dimgray dimgrey dodgerblue "
"firebrick floralwhite forestgreen fuchsia gainsboro ghostwhite gold goldenrod gray green greenyellow grey "
"honeydew hotpink indianred indigo invis ivory khaki "
"lavender lavenderblush lawngreen lemonchiffon lightblue lightcoral lightcyan "
"lightgoldenrod lightgoldenrodyellow lightgray lightgreen lightgrey lightpink "
"lightsalmon lightseagreen lightskyblue lightslateblue lightslategray lightslategrey lightsteelblue lightyellow "
"lime limegreen linen "
"magenta maroon mediumaquamarine mediumblue mediumorchid mediumpurple mediumseagreen mediumslateblue mediumspringgreen "
"mediumturquoise mediumvioletred midnightblue mintcream mistyrose moccasin "
"navajowhite navy navyblue none oldlace olive olivedrab orange orangered orchid "
"palegoldenrod palegreen paleturquoise palevioletred papayawhip peachpuff peru pink plum powderblue purple "
"rebeccapurple red rosybrown royalblue "
"saddlebrown salmon sandybrown seagreen seashell sienna silver skyblue slateblue slategray slategrey snow springgreen "
"steelblue "
"tan teal thistle tomato transparent turquoise violet violetred "
"webgray webgreen webgrey webmaroon webpurple wheat white whitesmoke x11gray x11green x11grey x11maroon x11purple "
"yellow yellowgreen "

, // 5 values
"BL BOTH BOTTOM BR BT CENTER FALSE KK LB LEFT LR LT MIDDLE POINT RB RIGHT RL RT SIZE TB TEXT TL TOP TR TRUE _graphviz "
"avg_dist back bold both breadthfirst circuit clust curved dashed diagonals dotted edgesfirst ediamond empty "
"fast filled forward global graph_dist halfopen hier invdot invempty invodot ipsep line local major max maxent mds min "
"nodesfirst open ortho polyline power_dist random rng rounded "
"same self sgd shortpath sink solid source spline spring striped subset tapered wedged "

, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
//--Autogenerated -- end of section automatically generated
}};

static EDITSTYLE Styles_Dot[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_GRAPHVIZ_WORD, NP2StyleX_Keyword, L"fore:#0000FF" },
	{ SCE_GRAPHVIZ_ATTRIBUTE, NP2StyleX_Attribute, L"fore:#FF8000" },
	{ SCE_GRAPHVIZ_VALUE, NP2StyleX_Value, L"fore:#008287" },
	{ SCE_GRAPHVIZ_HTML_TAG, NP2StyleX_Label, L"fore:#648000" },
	{ MULTI_STYLE(SCE_GRAPHVIZ_COMMENTLINE, SCE_GRAPHVIZ_COMMENTBLOCK, SCE_GRAPHVIZ_HTML_COMMENT, 0), NP2StyleX_Comment, L"fore:#608060" },
	{ SCE_GRAPHVIZ_STRING, NP2StyleX_String, L"fore:#008000" },
	{ SCE_GRAPHVIZ_ESCAPECHAR, NP2StyleX_EscapeSequence, L"fore:#0080C0" },
	{ SCE_GRAPHVIZ_NUMBER, NP2StyleX_Number, L"fore:#FF0000" },
	{ SCE_GRAPHVIZ_OPERATOR, NP2StyleX_Operator, L"fore:#B000B0" },
};

EDITLEXER lexGraphViz = {
	SCLEX_GRAPHVIZ, NP2LEX_GRAPHVIZ,
//Settings++Autogenerated -- start of section automatically generated
	{
		LexerAttr_Default,
		TAB_WIDTH_4, INDENT_WIDTH_4
		, KeywordAttr32(0, KeywordAttr_PreSorted) // keywords
		| KeywordAttr32(1, KeywordAttr_NoLexer) // html labels
		| KeywordAttr32(2, KeywordAttr_NoLexer) // attributes
		| KeywordAttr32(3, KeywordAttr_NoLexer) // node shapes
		| KeywordAttr32(4, KeywordAttr_NoLexer) // color names
		| KeywordAttr32(5, KeywordAttr_NoLexer) // values
	},
//Settings--Autogenerated -- end of section automatically generated
	EDITLEXER_HOLE(L"GraphViz Dot", Styles_Dot),
	L"dot; gv",
	&Keywords_Dot,
	Styles_Dot
};
