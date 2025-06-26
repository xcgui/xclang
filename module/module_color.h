#ifndef  XCL_COLOR_H
//@隐藏{
#define  XCL_COLOR_H
//@隐藏}

//@模块名称  常用颜色
//@版本  1.0
//@日期  2023-04-07
//@作者  XCGUI  
//@模块备注 常用颜色模块
//@依赖  module_base.h


//@分组{  常用颜色宏

//@别名 浅粉红
#define LIGHTPINK				RGBA(255, 182, 193, 255)	
//@别名 粉红
#define PINK					RGBA(255, 192, 203, 255)
//@别名	深红	
#define CRIMSON					RGBA(220,  20,  60, 255)		// 猩红 (深红)
//@别名 淡紫红
#define LAVENDERBLUSH			RGBA(255, 240, 245, 255)		// 淡紫红
//@别名 紫罗兰红
#define PALEVIOLETRED			RGBA(219, 112, 147, 255)		// 弱紫罗兰红
//@别名 热情的粉红
#define HOTPINK					RGBA(255, 105, 180, 255)		// 热情的粉红
//@别名 深粉红
#define DEEPPINK				RGBA(255,  20, 147, 255)		// 深粉红
//@别名 中紫罗兰红
#define MEDIUMVIOLETRED			RGBA(199,  21, 133, 255)		// 中紫罗兰红
//@别名 兰花紫
#define ORCHID					RGBA(218, 112, 214, 255)		// 兰花紫
//@别名 蓟
#define THISTLE					RGBA(216, 191, 216, 255)		// 蓟(花呈紫色、黄色或白色)
//@别名 李子紫
#define PLUM					RGBA(221, 160, 221, 255)		// 李子紫
//@别名 紫罗兰
#define VIOLET					RGBA(238, 130, 238, 255)		// 紫罗兰
//@别名 洋红
#define MAGENTA					RGBA(255,   0, 255, 255)		// 洋红 (品红 玫瑰红)
//@别名 紫红色
#define FUCHSIA					RGBA(255,   0, 255, 255)		// 灯笼海棠(紫红色)
//@别名 深洋红
#define DARKMAGENTA				RGBA(139,   0, 139, 255)		// 深洋红
//@别名 紫色
#define PURPLE					RGBA(128,   0, 128, 255)		// 紫色
//@别名 中兰花紫
#define MEDIUMORCHID			RGBA(186,  85, 211, 255)		// 中兰花紫
//@别名 暗紫罗兰
#define DARKVIOLET				RGBA(148,   0, 211, 255)		// 暗紫罗兰
//@别名 暗兰花紫
#define DARKORCHID				RGBA(153,  50, 204, 255)		// 暗兰花紫
//@别名 紫兰色
#define INDIGO					RGBA( 75,   0, 130, 255)		// 靛青 (紫兰色)
//@别名 蓝紫罗兰
#define BLUEVIOLET				RGBA(138,  43, 226, 255)		// 蓝紫罗兰
//@别名 中紫色
#define MEDIUMPURPLE			RGBA(147, 112, 219, 255)		// 中紫色
//@别名 中板岩蓝
#define MEDIUMSLATEBLUE			RGBA(123, 104, 238, 255)		// 中板岩蓝
//@别名 板岩蓝
#define SLATEBLUE				RGBA(106,  90, 205, 255)		// 板岩蓝
//@别名 暗板岩蓝
#define DARKSLATEBLUE			RGBA( 72,  61, 139, 255)		// 暗板岩蓝
//@别名 熏衣草淡紫
#define LAVENDER				RGBA(230, 230, 250, 255)		// 熏衣草淡紫
//@别名 幽灵白
#define GHOSTWHITE				RGBA(248, 248, 255, 255)		// 幽灵白
//@别名 蓝色
#define BLUE					RGBA(  0,   0, 255, 255)		// 纯蓝
//@别名 中蓝色
#define MEDIUMBLUE				RGBA(  0,   0, 205, 255)		// 中蓝色
//@别名 午夜蓝
#define MIDNIGHTBLUE			RGBA( 25,  25, 112, 255)		// 午夜蓝
//@别名 暗蓝色
#define DARKBLUE				RGBA(  0,   0, 139, 255)		// 暗蓝色
//@别名 海军蓝
#define NAVY					RGBA(  0,   0, 128, 255)		// 海军蓝
//@别名 宝蓝
#define ROYALBLUE				RGBA( 65, 105, 225, 255)		// 皇家蓝 (宝蓝)
//@别名 矢车菊蓝
#define CORNFLOWERBLUE			RGBA(100, 149, 237, 255)		// 矢车菊蓝
//@别名 亮钢蓝
#define LIGHTSTEELBLUE			RGBA(176, 196, 222, 255)		// 亮钢蓝
//@别名 亮石板灰
#define LIGHTSLATEGRAY			RGBA(119, 136, 153, 255)		// 亮石板灰
//@别名 石板灰
#define SLATEGRAY				RGBA(112, 128, 144, 255)		// 石板灰
//@别名 道奇蓝
#define DODGERBLUE				RGBA( 30, 144, 255, 255)		// 道奇蓝
//@别名 爱丽丝蓝
#define ALICEBLUE				RGBA(240, 248, 255, 255)		// 爱丽丝蓝
//@别名 钢蓝
#define STEELBLUE				RGBA( 70, 130, 180, 255)		// 钢蓝 (铁青)
//@别名 亮天蓝色
#define LIGHTSKYBLUE			RGBA(135, 206, 250, 255)		// 亮天蓝色
//@别名 天蓝色
#define SKYBLUE					RGBA(135, 206, 235, 255)		// 天蓝色
//@别名 深天蓝
#define DEEPSKYBLUE				RGBA(  0, 191, 255, 255)		// 深天蓝
//@别名 亮蓝
#define LIGHTBLUE				RGBA(173, 216, 230, 255)		// 亮蓝
//@别名 火药青
#define POWDERBLUE				RGBA(176, 224, 230, 255)		// 火药青
//@别名 军服蓝
#define CADETBLUE				RGBA( 95, 158, 160, 255)		// 军服蓝
//@别名 蔚蓝色
#define AZURE					RGBA(240, 255, 255, 255)		// 蔚蓝色
//@别名 淡青色
#define LIGHTCYAN				RGBA(224, 255, 255, 255)		// 淡青色
//@别名 弱绿宝石
#define PALETURQUOISE			RGBA(175, 238, 238, 255)		// 弱绿宝石
//@别名 青色
#define CYAN					RGBA(  0, 255, 255, 255)		// 青色
//@别名 水色
#define AQUA					RGBA(  0, 255, 255, 255)		// 水色
//@别名 暗绿宝石
#define DARKTURQUOISE			RGBA(  0, 206, 209, 255)		// 暗绿宝石
//@别名 暗石板灰
#define DARKSLATEGRAY			RGBA( 47,  79,  79, 255)		// 暗石板灰
//@别名 暗青色
#define DARKCYAN				RGBA(  0, 139, 139, 255)		// 暗青色
//@别名 水鸭色
#define TEAL					RGBA(  0, 128, 128, 255)		// 水鸭色
//@别名 中绿宝石
#define MEDIUMTURQUOISE			RGBA( 72, 209, 204, 255)		// 中绿宝石
//@别名 浅海洋绿
#define LIGHTSEAGREEN			RGBA( 32, 178, 170, 255)		// 浅海洋绿
//@别名 绿宝石
#define TURQUOISE				RGBA( 64, 224, 208, 255)		// 绿宝石
//@别名 宝石碧绿
#define AQUAMARINE				RGBA(127, 255, 212, 255)		// 宝石碧绿
//@别名 中宝石碧绿
#define MEDIUMAQUAMARINE		RGBA(102, 205, 170, 255)		// 中宝石碧绿
//@别名 中春绿色
#define MEDIUMSPRINGGREEN		RGBA(  0, 250, 154, 255)		// 中春绿色
//@别名 薄荷奶油
#define MINTCREAM				RGBA(245, 255, 250, 255)		// 薄荷奶油
//@别名 春绿色
#define SPRINGGREEN				RGBA(  0, 255, 127, 255)		// 春绿色
//@别名 中海洋绿
#define MEDIUMSEAGREEN			RGBA( 60, 179, 113, 255)		// 中海洋绿
//@别名 海洋绿
#define SEAGREEN				RGBA( 46, 139,  87, 255)		// 海洋绿
//@别名 蜜瓜色
#define HONEYDEW				RGBA(240, 255, 240, 255)		// 蜜瓜色
//@别名 淡绿色
#define LIGHTGREEN				RGBA(144, 238, 144, 255)		// 淡绿色
//@别名 弱绿色
#define PALEGREEN				RGBA(152, 251, 152, 255)		// 弱绿色
//@别名 暗海洋绿
#define DARKSEAGREEN			RGBA(143, 188, 143, 255)		// 暗海洋绿
//@别名 闪光深绿
#define LIMEGREEN				RGBA( 50, 205,  50, 255)		// 闪光深绿
//@别名 闪光绿
#define LIME					RGBA(  0, 255,   0, 255)		// 闪光绿
//@别名 森林绿
#define FORESTGREEN				RGBA( 34, 139,  34, 255)		// 森林绿
//@别名 绿色
#define GREEN					RGBA(  0, 128,   0, 255)		// 纯绿
//@别名 暗绿色
#define DARKGREEN				RGBA(  0, 100,   0, 255)		// 暗绿色
//@别名 查特酒绿
#define CHARTREUSE				RGBA(127, 255,   0, 255)		// 查特酒绿 (黄绿色)
//@别名 草坪绿
#define LAWNGREEN				RGBA(124, 252,   0, 255)		// 草坪绿
//@别名 绿黄色
#define GREENYELLOW				RGBA(173, 255,  47, 255)		// 绿黄色
//@别名 暗橄榄绿
#define DARKOLIVEGREEN			RGBA( 85, 107,  47, 255)		// 暗橄榄绿
//@别名 黄绿色
#define YELLOWGREEN				RGBA(154, 205,  50, 255)		// 黄绿色
//@别名 橄榄褐色
#define OLIVEDRAB				RGBA(107, 142,  35, 255)		// 橄榄褐色
//@别名 米色
#define BEIGE					RGBA(245, 245, 220, 255)		// 米色(灰棕色)
//@别名 亮菊黄
#define LIGHTGOLDENRODYELLOW	RGBA(250, 250, 210, 255)		// 亮菊黄
//@别名 象牙
#define IVORY					RGBA(255, 255, 240, 255)		// 象牙
//@别名 浅黄色
#define LIGHTYELLOW				RGBA(255, 255, 224, 255)		// 浅黄色
//@别名 黄色
#define YELLOW					RGBA(255, 255,   0, 255)		// 纯黄
//@别名 橄榄
#define OLIVE					RGBA(128, 128,   0, 255)		// 橄榄
//@别名 深卡叽布
#define DARKKHAKI				RGBA(189, 183, 107, 255)		// 深卡叽布
//@别名 柠檬绸
#define LEMONCHIFFON			RGBA(255, 250, 205, 255)		// 柠檬绸
//@别名 灰菊黄
#define PALEGOLDENROD			RGBA(238, 232, 170, 255)		// 灰菊黄
//@别名 卡叽布
#define KHAKI					RGBA(240, 230, 140, 255)		// 卡叽布
//@别名 金色
#define GOLD					RGBA(255, 215,   0, 255)		// 金色
//@别名 玉米丝色
#define CORNSILK				RGBA(255, 248, 220, 255)		// 玉米丝色
//@别名 金菊黄
#define GOLDENROD				RGBA(218, 165,  32, 255)		// 金菊黄
//@别名 暗金菊黄
#define DARKGOLDENROD			RGBA(184, 134,  11, 255)		// 暗金菊黄
//@别名 花的白色
#define FLORALWHITE				RGBA(255, 250, 240, 255)		// 花的白色
//@别名 旧蕾丝
#define OLDLACE					RGBA(253, 245, 230, 255)		// 旧蕾丝
//@别名 小麦色
#define WHEAT					RGBA(245, 222, 179, 255)		// 小麦色
//@别名 鹿皮靴
#define MOCCASIN				RGBA(255, 228, 181, 255)		// 鹿皮靴
//@别名 橙色
#define ORANGE					RGBA(255, 165,   0, 255)		// 橙色
//@别名 番木瓜
#define PAPAYAWHIP				RGBA(255, 239, 213, 255)		// 番木瓜
//@别名 杏仁色
#define BLANCHEDALMOND			RGBA(255, 235, 205, 255)		// 发白的杏仁色
//@别名 土著白
#define NAVAJOWHITE				RGBA(255, 222, 173, 255)		// 土著白
//@别名 古董白
#define ANTIQUEWHITE			RGBA(250, 235, 215, 255)		// 古董白
//@别名 茶色
#define TAN						RGBA(210, 180, 140, 255)		// 茶色
//@别名 硬木色
#define BURLYWOOD				RGBA(222, 184, 135, 255)		// 硬木色
//@别名 陶坯黄
#define BISQUE					RGBA(255, 228, 196, 255)		// 陶坯黄
//@别名 深橙色
#define DARKORANGE				RGBA(255, 140,   0, 255)		// 深橙色
//@别名 亚麻布
#define LINEN					RGBA(250, 240, 230, 255)		// 亚麻布
//@别名 秘鲁
#define PERU					RGBA(205, 133,  63, 255)		// 秘鲁
//@别名 桃肉色
#define PEACHPUFF				RGBA(255, 218, 185, 255)		// 桃肉色
//@别名 沙棕色
#define SANDYBROWN				RGBA(244, 164,  96, 255)		// 沙棕色
//@别名 巧克力
#define CHOCOLATE				RGBA(210, 105,  30, 255)		// 巧克力
//@别名 马鞍棕色
#define SADDLEBROWN				RGBA(139,  69,  19, 255)		// 马鞍棕色
//@别名 海贝壳
#define SEASHELL				RGBA(255, 245, 238, 255)		// 海贝壳
//@别名 黄土赭色
#define SIENNA					RGBA(160,  82,  45, 255)		// 黄土赭色
//@别名 浅鲑鱼肉色
#define LIGHTSALMON				RGBA(255, 160, 122, 255)		// 浅鲑鱼肉色
//@别名 珊瑚
#define CORAL					RGBA(255, 127,  80, 255)		// 珊瑚
//@别名 橙红色
#define ORANGERED				RGBA(255,  69,   0, 255)		// 橙红色
//@别名 深鲜肉色
#define DARKSALMON				RGBA(233, 150, 122, 255)		// 深鲜肉(鲑鱼)色
//@别名 番茄红
#define TOMATO					RGBA(255,  99,  71, 255)		// 番茄红
//@别名 薄雾玫瑰
#define MISTYROSE				RGBA(255, 228, 225, 255)		// 薄雾玫瑰
//@别名 鲜肉色
#define SALMON					RGBA(250, 128, 114, 255)		// 鲜肉(鲑鱼)色
//@别名 雪色
#define SNOW					RGBA(255, 250, 250, 255)		// 雪
//@别名 淡珊瑚色
#define LIGHTCORAL				RGBA(240, 128, 128, 255)		// 淡珊瑚色
//@别名 玫瑰棕色
#define ROSYBROWN				RGBA(188, 143, 143, 255)		// 玫瑰棕色
//@别名 印度红
#define INDIANRED				RGBA(205,  92,  92, 255)		// 印度红
//@别名 红色
#define RED						RGBA(255,   0,   0, 255)		// 纯红
//@别名 棕色
#define BROWN					RGBA(165,  42,  42, 255)		// 棕色
//@别名 耐火砖
#define FIREBRICK				RGBA(178,  34,  34, 255)		// 耐火砖
//@别名 深红色
#define DARKRED					RGBA(139,   0,   0, 255)		// 深红色
//@别名 栗色
#define MAROON					RGBA(128,   0,   0, 255)		// 栗色
//@别名 白色
#define WHITE					RGBA(255, 255, 255, 255)		// 纯白
//@别名 白烟
#define WHITESMOKE				RGBA(245, 245, 245, 255)		// 白烟
//@别名 罗灰色
#define GAINSBORO				RGBA(220, 220, 220, 255)		// 庚斯博罗灰色
//@别名 浅灰色
#define LIGHTGREY				RGBA(211, 211, 211, 255)		// 浅灰色
//@别名 银灰色
#define SILVER					RGBA(192, 192, 192, 255)		// 银灰色
//@别名 深灰色
#define DARKGRAY				RGBA(169, 169, 169, 255)		// 深灰色
//@别名 灰色
#define GRAY					RGBA(186, 183, 186, 255)		// 灰色(*)
//@别名 暗淡的灰色
#define DIMGRAY					RGBA(105, 105, 105, 255)		// 暗淡的灰色
//@别名 黑色
#define BLACK					RGBA(  0,   0,   0, 255)		// 纯黑

//@分组}

#endif //XC_BASE_H