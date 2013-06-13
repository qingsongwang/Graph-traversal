/******************************************************
 * EasyX Library for C++ (Ver:v20120603(beta))
 * http://www.easyx.cn
 *
 * graphics.h
 * 在 VC 下模拟 Borland BGI 绘图库，实现简单的绘图
 ******************************************************/

#pragma once

#ifndef WINVER
#define WINVER 0x0400  		// Specifies that the minimum required platform is Windows 95 and Windows NT 4.0.
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500		// Specifies that the minimum required platform is Windows 2000.
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410	// Specifies that the minimum required platform is Windows 98.
#endif

#if defined(UNICODE) && (_MSC_VER > 1200)
	#pragma comment(lib,"graphicswu.lib")
#elif !defined(UNICODE) && (_MSC_VER > 1200)
	#pragma comment(lib,"graphicsw.lib")
#elif defined(UNICODE)
	#pragma comment(lib,"graphicsu.lib")
#elif !defined(UNICODE)
	#pragma comment(lib,"graphics.lib")
#endif


#ifndef __cplusplus
#error EasyX(graphics.h) is only for C++
#endif

#include <windows.h>
#include <tchar.h>

// 为了兼容 Borland C++ 3.1 而做的无意义定义
#define DETECT 0
#define VGA	0
#define VGAHI 0

// 绘图环境初始化参数
#define SHOWCONSOLE		1		// 进入图形模式时，保留控制台的显示

// 颜色
#define	BLACK			0
#define	BLUE			0xA80000
#define	GREEN			0x00A800
#define	CYAN			0xA8A800
#define	RED				0x0000A8
#define	MAGENTA			0xA800A8
#define	BROWN			0x0054A8
#define	LIGHTGRAY		0xA8A8A8
#define	DARKGRAY		0x545454
#define	LIGHTBLUE		0xFC5454
#define	LIGHTGREEN		0x54FC54
#define	LIGHTCYAN		0xFCFC54
#define	LIGHTRED		0x5454FC
#define	LIGHTMAGENTA	0xFC54FC
#define	YELLOW			0x54FCFC
#define	WHITE			0xFCFCFC

// 定义颜色转换宏
#define BGR(color)	( (((color) & 0xFF) << 16) | ((color) & 0xFF00FF00) | (((color) & 0xFF0000) >> 16) )

// 填充模式
#define	NULL_FILL			1		// 不填充
#define	SOLID_FILL			2		// 用指定颜色完全填充
#define	BDIAGONAL_FILL		3		// /// 填充 (普通一组)
#define	CROSS_FILL			4		// +++ 填充
#define	DIAGCROSS_FILL		5		// xxx 填充
#define	DOT_FILL			6		// ... 填充
#define	FDIAGONAL_FILL		7		// \\\ 填充
#define	HORIZONTAL_FILL		8		// --- 填充
#define	VERTICAL_FILL		9		// ||| 填充
#define	BDIAGONAL2_FILL		10		// /// 填充 (密集一组)
#define	CROSS2_FILL			11		// +++ 填充
#define	DIAGCROSS2_FILL		12		// xxx 填充
#define	DOT2_FILL			13		// ... 填充
#define	FDIAGONAL2_FILL		14		// \\\ 填充
#define	HORIZONTAL2_FILL	15		// --- 填充
#define	VERTICAL2_FILL		16		// ||| 填充
#define	BDIAGONAL3_FILL		17		// /// 填充 (粗线一组)
#define	CROSS3_FILL			18		// +++ 填充
#define	DIAGCROSS3_FILL		19		// xxx 填充
#define	DOT3_FILL			20		// ... 填充
#define	FDIAGONAL3_FILL		21		// \\\ 填充
#define	HORIZONTAL3_FILL	22		// --- 填充
#define	VERTICAL3_FILL		23		// ||| 填充
#define	INTERLEAVE_FILL		24		// xxx 填充 (十分密)
#define	PATTERN_FILL		25		// 用指定图案填充



// 绘图模式相关函数

HWND initgraph(int Width, int Height, int Flag = NULL);	// 初始化图形环境
HWND initgraph(int* gdriver, int* gmode, char* path);	// 兼容 Borland C++ 3.1 的重载，默认 640x480
void closegraph();										// 关闭图形环境



// 绘图环境设置

void cleardevice();					// 清屏
void setcliprgn(HRGN hrgn);			// 设置当前绘图设备的裁剪区
void clearcliprgn();				// 清除裁剪区的屏幕内容

void getlinestyle(int *plinestyle, WORD *pupattern = NULL, int *pthickness = NULL);	// 获取当前线形
void setlinestyle(int linestyle, WORD upattern = NULL, int thickness = 1);			// 设置当前线形
void getfillstyle(COLORREF *pcolor, int *ppattern = NULL, char *pupattern = NULL);			// 获取填充类型
void setfillstyle(COLORREF color, int pattern = SOLID_FILL, const char *pupattern = NULL);	// 设置填充类型

void setorigin(int x, int y);							// 设置坐标原点
void getaspectratio(float *pxasp, float *pyasp);		// 获取当前缩放因子
void setaspectratio(float xasp, float yasp);			// 设置当前缩放因子

void setwritemode(int mode);				// 设置绘图位操作模式

void graphdefaults();						// 重置所有绘图设置为默认值

COLORREF getcolor();				// 获取当前绘图前景色
void setcolor(COLORREF color);		// 设置当前绘图前景色
COLORREF getbkcolor();				// 获取当前绘图背景色
void setbkcolor(COLORREF color);	// 设置当前绘图背景色
void setbkmode(int iBkMode);		// 设置背景混合模式

// 颜色模型转换函数
COLORREF RGBtoGRAY(COLORREF rgb);
void RGBtoHSL(COLORREF rgb, float *H, float *S, float *L);
void RGBtoHSV(COLORREF rgb, float *H, float *S, float *V);
COLORREF HSLtoRGB(float H, float S, float L);
COLORREF HSVtoRGB(float H, float S, float V);


// 绘图函数

COLORREF getpixel(int x, int y);				// 获取点的颜色
void putpixel(int x, int y, COLORREF color);	// 画点

void moveto(int x, int y);						// 移动当前点(绝对坐标)
void moverel(int dx, int dy);					// 移动当前点(相对坐标)

void line(int x1, int y1, int x2, int y2);		// 画线
void linerel(int dx, int dy);					// 画线(至相对坐标)
void lineto(int x, int y);						// 画线(至绝对坐标)

void rectangle(int left, int top, int right, int bottom);	// 画矩形

void circle(int x, int y, int radius);													// 画圆
void ellipse(int left, int top, int right, int bottom);									// 画椭圆
void arc(int left, int top, int right, int bottom, double stangle, double endangle);	// 画椭圆弧(起始角度和终止角度为弧度制)
void fillcircle(int x, int y, int radius);												// 画填充圆
void fillellipse(int left, int top, int right, int bottom);								// 画填充椭圆
void pie(int left, int top, int right, int bottom, double stangle, double endangle);	// 画填充椭圆扇形(起始角度和终止角度为弧度制)

void bar(int left, int top, int right, int bottom);										// 画无边框填充矩形
void bar3d(int left, int top, int right, int bottom, int depth, bool topflag);			// 画有边框三维填充矩形

void drawpoly(int numpoints, const int *polypoints);	// 画多边形
void fillpoly(int numpoints, const int *polypoints);	// 画填充的多边形
void floodfill(int x, int y, int border);				// 填充区域



// 文字相关函数

void outtext(LPCTSTR str);					// 在当前位置输出字符串
void outtext(TCHAR c);						// 在当前位置输出字符
void outtextxy(int x, int y, LPCTSTR str);	// 在指定位置输出字符串
void outtextxy(int x, int y, TCHAR c);		// 在指定位置输出字符
int textwidth(LPCTSTR str);					// 获取字符串占用的像素宽
int textwidth(TCHAR c);						// 获取字符占用的像素宽
int textheight(LPCTSTR str);				// 获取字符串占用的像素高
int textheight(TCHAR c);					// 获取字符占用的像素高
int drawtext(LPCTSTR str, RECT* pRect, UINT uFormat);	// 在指定区域内以指定格式输出字符串
int drawtext(TCHAR c, RECT* pRect, UINT uFormat);		// 在指定区域内以指定格式输出字符

// 设置当前字体样式(详见帮助)
//		nHeight: 字符的平均高度；
//		nWidth: 字符的平均宽度(0 表示自适应)；
//		lpszFace: 字体名称；
//		nEscapement: 字符串的书写角度(单位 0.1 度)；
//		nOrientation: 每个字符的书写角度(单位 0.1 度)；
//		nWeight: 字符的笔画粗细(0 表示默认粗细)；
//		bItalic: 是否斜体；
//		bUnderline: 是否下划线；
//		bStrikeOut: 是否删除线；
//		fbCharSet: 指定字符集；
//		fbOutPrecision: 指定文字的输出精度；
//		fbClipPrecision: 指定文字的剪辑精度；
//		fbQuality: 指定文字的输出质量；
//		fbPitchAndFamily: 指定以常规方式描述字体的字体系列。
void setfont(int nHeight, int nWidth, LPCTSTR lpszFace);
void setfont(int nHeight, int nWidth, LPCTSTR lpszFace, int nEscapement, int nOrientation, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut);
void setfont(int nHeight, int nWidth, LPCTSTR lpszFace, int nEscapement, int nOrientation, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut, BYTE fbCharSet, BYTE fbOutPrecision, BYTE fbClipPrecision, BYTE fbQuality, BYTE fbPitchAndFamily);
void setfont(const LOGFONT *font);	// 设置当前字体样式
void getfont(LOGFONT *font);		// 获取当前字体样式



// 图像处理函数

// 定义图像对象
class IMAGE
{
public:
	int width, height;	// 对象的宽高

private:
	HBITMAP m_hBmp;
	HDC m_hMemDC;
	int m_MemCurX;			// 当前点X坐标
	int m_MemCurY;			// 当前点Y坐标
	float m_data[6];
	COLORREF	m_Color;			// 当前颜色
	COLORREF	m_BkColor;			// 当前背景颜色
	DWORD*		m_pBuffer;			// 绘图区的内存

	struct{
		int		linestyle;
		WORD	upattern;		// 自定义线形
		int		thickness;
	}	m_LineType;				// 线形

	struct{
		int pattern;
		char upattern[8];		// 自定义填充类型
		int color;
	}	m_FillType;									// 填充类型
	virtual void SetDefault();						// 设置为默认状态

public:
	IMAGE(int _width = 0, int _height = 0);			// 创建图像
	IMAGE(const IMAGE &img);						// 拷贝构造函数
	IMAGE& operator = (const IMAGE &img);			// 赋值运算符重载函数
	virtual ~IMAGE();
	virtual void Resize(int _width, int _height);	// 调整尺寸
};

void loadimage(IMAGE *pDstImg, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false);					// 从图片文件获取图像(bmp/jpg/gif/emf/wmf)
void loadimage(IMAGE *pDstImg, LPCTSTR pResType, LPCTSTR pResName, int nWidth = 0, int nHeight = 0, bool bResize = false);	// 从资源文件获取图像(bmp/jpg/gif/emf/wmf)
void saveimage(LPCTSTR pImgFile, IMAGE* pImg = NULL);																		// 保存图像
void getimage(IMAGE *pDstImg, int srcX, int srcY, int srcWidth, int srcHeight);												// 从当前绘图设备获取图像
void putimage(int dstX, int dstY, const IMAGE *pSrcImg, DWORD dwRop = SRCCOPY);												// 绘制图像到屏幕
void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE *pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);		// 绘制图像到屏幕(指定宽高)
void rotateimage(IMAGE *dstimg, IMAGE *srcimg, double radian, COLORREF bkcolor = BLACK, bool autosize = false, bool highquality = true);// 旋转图像
void Resize(IMAGE* pImg, int width, int height);	// 调整绘图设备的大小
DWORD* GetImageBuffer(IMAGE* pImg = NULL);			// 获取绘图设备的显存指针
IMAGE* GetWorkingImage();							// 获取当前绘图设备
void SetWorkingImage(IMAGE* pImg = NULL);			// 设置当前绘图设备
HDC GetImageHDC(IMAGE* pImg = NULL);				// 获取绘图设备句柄(HDC)


// 其它函数

int	getwidth();			// 获取绘图区宽度
int	getheight();		// 获取绘图区高度
int	getx();				// 获取当前 x 坐标
int	gety();				// 获取当前 y 坐标

void BeginBatchDraw();	// 开始批量绘制
void FlushBatchDraw();	// 执行未完成的绘制任务
void FlushBatchDraw(int left, int top, int right, int bottom);	// 执行指定区域内未完成的绘制任务
void EndBatchDraw();	// 结束批量绘制，并执行未完成的绘制任务
void EndBatchDraw(int left, int top, int right, int bottom);	// 结束批量绘制，并执行指定区域内未完成的绘制任务

HWND GetHWnd();								// 获取绘图窗口句柄(HWND)
TCHAR* GetEasyXVer();						// 获取 EasyX 当前版本

// 获取用户输入
bool InputBox(LPTSTR pString, int nMaxCount, LPCTSTR pPrompt = NULL, LPCTSTR pTitle = NULL, LPCTSTR pDefault = NULL, int width = 0, int height = 0, bool bOnlyOK = true);



// 鼠标消息
// 支持如下消息：
//		WM_MOUSEMOVE		鼠标移动
//		WM_MOUSEWHEEL		鼠标滚轮拨动
//		WM_LBUTTONDOWN		左键按下
//		WM_LBUTTONUP		左键弹起
//		WM_LBUTTONDBLCLK	左键双击
//		WM_MBUTTONDOWN		中键按下
//		WM_MBUTTONUP		中键弹起
//		WM_MBUTTONDBLCLK	中键双击
//		WM_RBUTTONDOWN		右键按下
//		WM_RBUTTONUP		右键弹起
//		WM_RBUTTONDBLCLK	右键双击
struct MOUSEMSG
{
	UINT uMsg;				// 当前鼠标消息
	bool mkCtrl;			// Ctrl 键是否按下
	bool mkShift;			// Shift 键是否按下
	bool mkLButton;			// 鼠标左键是否按下
	bool mkMButton;			// 鼠标中键是否按下
	bool mkRButton;			// 鼠标右键是否按下
	short x;				// 当前鼠标 x 坐标
	short y;				// 当前鼠标 y 坐标
	short wheel;			// 鼠标滚轮滚动值(120的倍数)
};

bool MouseHit();			// 检查是否存在鼠标消息
MOUSEMSG GetMouseMsg();		// 获取一个鼠标消息。如果没有，就等待
void FlushMouseMsgBuffer();	// 清空鼠标消息缓冲区
