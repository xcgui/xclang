#pragma once


//@隐藏{



#include "module_base.h"


#define GDIPVER 0x0110 //定义高版本的GDI+(1.1)部分功能需要1.1版本才能使用

#include <Windows.h>
#include <gdiplus.h>


#pragma comment(lib, "Gdiplus.lib")
//@隐藏}
//@模块名称  XCGdiplus
//@版本  0.1  
//@日期  2024-11-14
//@作者  hxznhf
//@QQ  568415950
//@模块备注  基于【易团雪 Gdiplus模块 】修改而来（自用）


//@src "module_xcgdiplus.cpp"

using namespace Gdiplus;//使用Gdiplus命名空间
//@解析头文件
#include "gdiplus_color.h"
//@解析头文件
#include "gdiplus_enums.h"
//@解析头文件
#include "gdiplus_types.h"
//@解析头文件
#include "gdiplus_Matrix.h"
//@解析头文件
#include "gdiplus_Path.h"
//@解析头文件
#include "gdiplus_effects.h"
class GPGraphics ;
class GPCachedBitmap;
class GPFontFamily ;
class GPStringFormat;
class GPPen;

//@分组{  全局函数
//@别名 取编码器自图像格式(GP图像格式)
static GUID GetEncoderFormFormatId(const GUID* guid){
	GUID ret = GUID_NULL;
	UINT numDecoders, size;
	Gdiplus::Status result = Gdiplus::GetImageEncodersSize(&numDecoders, &size);
	if(result != Gdiplus::Ok) return ret;
	Gdiplus::ImageCodecInfo * ptrInfo = (Gdiplus::ImageCodecInfo *)malloc( size );
	if(!ptrInfo) return ret;
	result = Gdiplus::GetImageEncoders(numDecoders, size, ptrInfo);
	if(result != Gdiplus::Ok) {
		free(ptrInfo);
		return ret;
	}
	for(UINT i=0; i< numDecoders; i++) {
		if(IsEqualGUID(*guid, ptrInfo[i].FormatID)) {
			ret = ptrInfo[i].Clsid;
			break;
		}
	}
	free(ptrInfo);
	return ret;
}
//@备注 函数初始化 Windows GDI+。 在进行任何其他 GDI+ 调用之前调用 Gdiplus.初始化，并在使用完 GDI+ 后调用 Gdiplus.卸载
//@返回 返回一个令牌, 这个令牌在卸载时需要
//@别名 Gdiplus初始化()
static ULONG_PTR GdiplusInit(int Version=1){
	ULONG_PTR GdiToken = 0;//gdi标识
	Gdiplus::GdiplusStartupInput StartupInput;// 初始化GDI+
	StartupInput.GdiplusVersion = Version;
	StartupInput.DebugEventCallback = NULL;
	StartupInput.SuppressBackgroundThread = FALSE;
	StartupInput.SuppressExternalCodecs = FALSE;
	Gdiplus::GdiplusStartup(&GdiToken, &StartupInput, NULL); 
	return GdiToken;
}

//@备注 为一个 Windows GDI+ 对象分配内存
//@返回 返回内存地址
//@参数 内存大小 要申请的内存大小
//@别名 Gdiplus申请内存(内存大小)
static void* GdiplusAlloc(int nSize){
	return Gdiplus::DllExports::GdipAlloc(nSize);
}
//@备注 释放由 Gdiplus申请内存() 申请的内存
//@别名 Gdiplus释放内存()
static void GdiplusFree(void* buffer){
	Gdiplus::DllExports::GdipFree(buffer);
}
/*@声明
//@备注 卸载GDI+, 注意: 在此之前必须销毁其他所有GDI+对象
//@参数 令牌 由 Gdiplus.初始化 返回
//@别名 Gdiplus卸载()
extern "C" VOID WINAPI GdiplusShutdown(ULONG_PTR token);

//@参数 像素格式 GP像素格式 常量组合
//@返回 方法返回指定像素格式使用的每个像素的位数
//@别名 取像素格式大小(像素格式)
inline UINT
GetPixelFormatSize(PixelFormat pixfmt)
{
    return (pixfmt >> 8) & 0xff;
}
//@参数 像素格式 GP像素格式 常量组合
//@返回 方法确定指定的像素格式是否为索引格式。
//@别名 是否索引像素格式()
inline BOOL
IsIndexedPixelFormat(PixelFormat pixfmt)
{
    return (pixfmt & PixelFormatIndexed) != 0;
}
//@参数 像素格式 GP像素格式 常量组合
//@返回 方法确定指定的像素格式是否具有 alpha 分量
//@别名 是否透明像素格式()
inline BOOL
IsAlphaPixelFormat(PixelFormat pixfmt)
{
   return (pixfmt & PixelFormatAlpha) != 0;
}
//@参数 像素格式 GP像素格式 常量组合
//@返回 方法确定指定的像素格式是否使用每个颜色通道 16 位
//@别名 是否扩展像素格式()
inline BOOL
IsExtendedPixelFormat(PixelFormat pixfmt)
{
   return (pixfmt & PixelFormatExtended) != 0;
}
//@参数 像素格式 GP像素格式 常量组合
//@返回 方法确定指定的像素格式是否是规范格式之一：PixelFormat32bppARGB 或 PixelFormat64bppARGB
//@别名 是否规范像素格式()
inline BOOL
IsCanonicalPixelFormat(PixelFormat pixfmt)
{
   return (pixfmt & PixelFormatCanonical) != 0;
}
*/
//@分组}
//@分组{  Gdiplus
//@别名 GP基类
class GPbase {
	protected:
		Gdiplus::Status lastResult;
	public:
		//@隐藏{
		GPbase() {
		} //构造函数
		~GPbase() {
		}
		Gdiplus::Status SetStatus(Gdiplus::Status status) {
			 if (status != Gdiplus::Ok)
				 return (lastResult = status);
			 else
				 return status;
		}
		//@隐藏}
		//@备注 方法返回一个值，该值指示此 对象最近一次方法失败的性质
		//@别名 取最后状态()
		Gdiplus::Status GetStatus() {
			Gdiplus::Status lastStatus = lastResult;
			lastResult = Gdiplus::Ok;
			return lastStatus;
		}
};
//@分组}
//@分组{  图像操作
//@别名 GP图像类
class GPImage : public GPbase {
	//@隐藏{
	public:
	Gdiplus::GpImage *hImage;
	IStream* m_stream;
	public:
	GPImage(){
		hImage = nullptr;
		m_stream = nullptr;
	}
	~GPImage(){
		Destory();
	}

	inline static IStream* CreateStream(const CXBytes& bytes){
		INT len = bytes.size();
		HGLOBAL hMem = ::GlobalAlloc( GMEM_ZEROINIT | GMEM_MOVEABLE, len);
		if(!hMem) { return NULL; }
		IStream* spStream = NULL;
		HRESULT hr = ::CreateStreamOnHGlobal(hMem,TRUE,&spStream);
		if(hr < 0){
			::GlobalFree(hMem);
			return NULL;
		}
		if(len != 0){
			void* ptr = GlobalLock(hMem);
			if(!ptr){
				::GlobalFree(hMem);
				return NULL;  
			}
			memcpy(ptr, bytes.get(), len);
			::GlobalUnlock(hMem);
		}
		return spStream;
	}
	inline static bool GetStreamBytes(IStream* stream, CXBytes& bytes){
		HGLOBAL hMem = NULL;
		HRESULT hr = ::GetHGlobalFromStream(stream,&hMem);
		if(hr < 0){ return false; }
		SIZE_T len = ::GlobalSize(hMem);
		void* ptr = GlobalLock(hMem);
		if(!ptr){ return false; }
		BYTE* ptrBytes = bytes.alloc((int)len);
		if(!ptrBytes){
			::GlobalUnlock(hMem);
			return false;
		}
		memcpy(ptrBytes, ptr, len);
		::GlobalUnlock(hMem);
		return true; 
	}
	//@隐藏}
	//@别名 置指针()
	VOID SetNativeImage(GpImage* nativeImage){
		this->hImage = nativeImage;
	}
	//@别名 取指针()
	Gdiplus::GpImage* GetPtr(){
		return hImage;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(hImage) Gdiplus::DllExports::GdipDisposeImage(hImage);
		hImage = nullptr;
		if (m_stream){
			m_stream->Release();
		}
		m_stream = nullptr;
		lastResult = Gdiplus::Ok;
	}
	//@备注 创建一个新的 GP图像类 对象，该对象是本对象的副本
	//@别名 克隆(新画刷)
	bool Clone(GPImage& Image){
		Image.Destory();
		Gdiplus::GpImage* clone;
		SetStatus(Gdiplus::DllExports::GdipCloneImage(hImage, &clone));
		Image.hImage = clone;
		Image.lastResult = lastResult;
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取编码器参数列表大小()
	UINT GetEncoderParameterListSize(
		__in const CLSID* clsidEncoder
		) 
	{
		UINT size = 0;

		SetStatus(DllExports::GdipGetEncoderParameterListSize(hImage,
															  clsidEncoder,
															  &size));
		return size;
	}
	//@别名 取编码器参数列表()
	Status GetEncoderParameterList(
		__in const CLSID* clsidEncoder,
		__in UINT size,
		__out EncoderParameters* buffer
		)
	{
		return SetStatus(DllExports::GdipGetEncoderParameterList(hImage,
																 clsidEncoder,
																 size,
																 buffer));
	}
	//@别名 创建自文件(文件名,使用嵌入式色彩管理)
	bool FromFile(CXText text,BOOL IMC = TRUE){
		if(IMC) 
			lastResult = Gdiplus::DllExports::GdipLoadImageFromFileICM(text.get(),&hImage);
		else
			lastResult = Gdiplus::DllExports::GdipLoadImageFromFile(text.get(), &hImage);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自字节集(字节集,使用嵌入式色彩管理)
	bool FromStream(CXBytes &Bytes,BOOL IMC= TRUE){
		this->Destory();
		m_stream = CreateStream(Bytes); 
		if(IMC) 
			lastResult = Gdiplus::DllExports::GdipLoadImageFromStreamICM(m_stream,&hImage);
		else
			lastResult = Gdiplus::DllExports::GdipLoadImageFromStream(m_stream, &hImage);
		return lastResult == Gdiplus::Ok;
	}
	//@备注 将此图像保存到文件中
	//@别名 保存到文件(文件名,图像格式,编码器参数)
	bool SaveToFile(const WCHAR* filename, const GUID &formatID, const EncoderParameters *encoderParams = nullptr){
		CLSID clsid = GetEncoderFormFormatId((const GUID*)&formatID);
		SetStatus(Gdiplus::DllExports::GdipSaveImageToFile(hImage, filename, &clsid,encoderParams ));
		return lastResult == Gdiplus::Ok;
	}
	//@备注 将此图像保存到字节集中
	//@别名 保存到字节集(字节集,图像格式,编码器参数)
	bool SaveToStream(CXBytes &bytes, const GUID &formatID, const EncoderParameters *encoderParams = nullptr){
		CLSID clsid = GetEncoderFormFormatId((const GUID*)&formatID);
		IStream* pStream = CreateStream(bytes);
		SetStatus(Gdiplus::DllExports::GdipSaveImageToStream(hImage, pStream, &clsid,encoderParams ));
		GetStreamBytes(pStream, bytes);
		pStream->Release();
		return lastResult == Gdiplus::Ok;
	}
	//@备注 将帧添加到先前调用 保存到文件 或 保存到字节集 方法时指定的文件或字节集中,使用此方法将多帧图像中的选定帧保存到另一个多帧图像
	//@别名 保存添加(编码器参数)
	bool SaveAdd(EncoderParameters *encoderParams = nullptr){
		return SetStatus(Gdiplus::DllExports::GdipSaveAdd(hImage,encoderParams)) == Gdiplus::Ok;
	}
	//@备注 将帧添加到先前调用 保存到文件 或 保存到字节集 方法时指定的文件或字节集中。 
	//@别名 保存添加图像(GP图像,编码器参数)
	bool SaveAddImage(GPImage& Image,EncoderParameters *encoderParams = nullptr){
		return SetStatus(Gdiplus::DllExports::GdipSaveAddImage(hImage, Image.hImage, encoderParams)) == Gdiplus::Ok;
	}
	//@备注 获取此 GP图像类 对象的类型（位图或元文件）
	//@别名 取类型()
	ImageType GetType(){
		Gdiplus::ImageType type = Gdiplus::ImageTypeUnknown;
		SetStatus(Gdiplus::DllExports::GdipGetImageType(hImage, &type));
		return type;
	}
	//@别名 取物理尺寸(返回宽度,返回高度)
	bool GetPhysicalDimension(__out REAL& width,__out REAL& height){
		SetStatus(Gdiplus::DllExports::GdipGetImageDimension(hImage,&width, &height));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取边界(返回矩形,返回单位)
	bool GetBounds(__out RectF& srcRect,__out Unit& srcUnit){
		SetStatus(Gdiplus::DllExports::GdipGetImageBounds(hImage, &srcRect, &srcUnit));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取宽度()
	int GetWidth(){
		UINT width = 0;
		SetStatus(Gdiplus::DllExports::GdipGetImageWidth(hImage, &width));
		return width;
	}
	//@别名 取高度()
	int GetHeight(){
		UINT Height = 0;
		SetStatus(Gdiplus::DllExports::GdipGetImageHeight(hImage, &Height));
		return Height;
	}
	//@别名 取水平分辨率()
	float GetHorizontalResolution(){
		Gdiplus::REAL resolution = 0.0f;
		SetStatus(Gdiplus::DllExports::GdipGetImageHorizontalResolution(hImage, &resolution));
		return resolution;
	}
	//@别名 取垂直分辨率()
	float GetVerticalResolution(){
		Gdiplus::REAL resolution = 0.0f;
		SetStatus(Gdiplus::DllExports::GdipGetImageVerticalResolution(hImage, &resolution));
		return resolution;
	}
	//@别名 取图像标志()
	UINT GetFlags(){
		UINT flags = 0;
		SetStatus(Gdiplus::DllExports::GdipGetImageFlags(hImage, &flags));
		return flags;
	}
	//@别名 取原始格式(返回GP图像格式)
	bool GetRawFormat(__out GUID *format){
		SetStatus(DllExports::GdipGetImageRawFormat(hImage, format));
		return lastResult == Gdiplus::Ok; 
	}
	//@别名 取像素格式()
	int GetPixelFormat(){
		Gdiplus::PixelFormat format;
		SetStatus(DllExports::GdipGetImagePixelFormat(hImage, &format));
		return format; 
	}
	//@别名 取颜色板大小()
	int GetPaletteSize(){
		INT size = 0;
		SetStatus(DllExports::GdipGetImagePaletteSize(hImage, &size));
		return size;
	}
	//@别名 取颜色调试板(返回颜色调试板,颜色板大小)
	bool GetPalette(__out ColorPalette *palette,__in INT size){
		SetStatus(DllExports::GdipGetImagePalette(hImage, palette, size));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 置颜色调试板(颜色调试板)
	bool SetPalette(__in const ColorPalette *palette){
		SetStatus(DllExports::GdipSetImagePalette(hImage, palette));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取图像缩略图(缩略图宽度,缩略图高度,返回缩略图,终止回调函数,回调函数参数)
	bool GetThumbnailImage(UINT thumbWidth,UINT thumbHeight,__out GPImage &newImage, GetThumbnailImageAbort callback,VOID* callbackData = nullptr){
		//GpImage *thumbimage = NULL;
		SetStatus(DllExports::GdipGetImageThumbnail(hImage,thumbWidth, thumbHeight,&newImage.hImage,callback, callbackData));
		//GPImage newImage.hImage = thumbimage;
		//if (newImage == NULL) {
		//	DllExports::GdipDisposeImage(thumbimage);
		//}
		return  lastResult == Gdiplus::Ok;
	}
	//@别名 取帧维面列表大小()
	int GetFrameDimensionsCount(){
		UINT count = 0;
		SetStatus(DllExports::GdipImageGetFrameDimensionsCount(hImage, &count));
		return count;
	}
	//@别名 取帧维面列表(标识符数组,大小)
	bool GetFrameDimensionsList(__out GUID* dimensionIDs, UINT count){
		SetStatus(DllExports::GdipImageGetFrameDimensionsList(hImage,dimensionIDs,count));
		return  lastResult == Gdiplus::Ok;
	}
	//@别名 取帧数(帧属性)
	//@备注 获取此图像中指定维面的帧数
	//@备注 帧属性标识符为 GUID_FrameDimensionPage
	//@参数 帧属性 （常量 帧属性_）
	UINT GetFrameCount(const int dimension)
	{
		const GUID *dimensionID ;

		// 使用有意义的常量来代替魔法数字
		if (dimension == XCGDIP::Frame_DimensionTime)
		{
			dimensionID = &Gdiplus::FrameDimensionTime;
		}
		else if (dimension == XCGDIP::Frame_DimensionPage)
		{
			dimensionID = &Gdiplus::FrameDimensionPage;
		}
		else if (dimension == XCGDIP::Frame_DimensionResolution)
		{
			dimensionID = &Gdiplus::FrameDimensionResolution;
		}
		else
		{
			// 处理未定义的dimension值
			// 可以设置一个默认值，或者返回一个错误码，这里选择返回0
			return 0;
		}

		UINT count = 0;
		SetStatus(DllExports::GdipImageGetFrameCount(hImage, dimensionID, &count));
		return count;
	}

	//@别名 取帧延时(帧延时)
	void GetFrameDelays(CXVector<int>& frameDelays){
		Gdiplus::PropertyItem *m_pItem = 0;
		UINT TotalBuffer ;
		DllExports::GdipGetPropertyItemSize(hImage,PropertyTagFrameDelay,&TotalBuffer);
		m_pItem = (Gdiplus::PropertyItem *)malloc(TotalBuffer);
		memset(m_pItem, 0, TotalBuffer);
		DllExports::GdipGetPropertyItem(hImage,PropertyTagFrameDelay, TotalBuffer, m_pItem);
		int * delays = (int*)(m_pItem->value);
		frameDelays.clear();
		 for (UINT i = 0; i < m_pItem->length / sizeof(LONG); ++i) {
            frameDelays.add(static_cast<int>(delays[i]));
        }
		free((void *)m_pItem);
	}


	//@别名 选择活动帧()
	Status SelectActiveFrame(__in const GUID *dimensionID, __in UINT frameIndex)
	{
		return SetStatus(DllExports::GdipImageSelectActiveFrame(hImage,
																dimensionID,
																frameIndex));
	}
	//@别名 旋转翻转()
	Status RotateFlip(__in RotateFlipType rotateFlipType)
	{
		return SetStatus(DllExports::GdipImageRotateFlip(hImage,
														 rotateFlipType));
	}
	//@别名 取属性数()
	UINT GetPropertyCount()
	{
		UINT numProperty = 0;
		SetStatus(DllExports::GdipGetPropertyCount(hImage,&numProperty));
		return numProperty;
	}
	//@别名 取属性ID列表()
	Status GetPropertyIdList(
		__in UINT numOfProperty, 
		__out PROPID* list
		)
	{
		return SetStatus(DllExports::GdipGetPropertyIdList(hImage,
														   numOfProperty, list));
	}
	//@别名 取属性项目大小()
	UINT GetPropertyItemSize(__in PROPID propId)
	{
		UINT size = 0;
		SetStatus(DllExports::GdipGetPropertyItemSize(hImage,
													  propId,
													  &size));
		return size;
	}
	//@别名 取属性项目()
	Status GetPropertyItem(__in PROPID propId, __in UINT propSize,__out PropertyItem* buffer)
	{
		return SetStatus(DllExports::GdipGetPropertyItem(hImage,
														 propId, propSize, buffer));
	}
	//@别名 取所有属性项目大小()
	Status GetPropertySize(
		__out UINT* totalBufferSize, 
		__out UINT* numProperties
		)
	{
		return SetStatus(DllExports::GdipGetPropertySize(hImage,
														 totalBufferSize,
														 numProperties));
	}
	//@别名 取所有属性项目()
	Status GetAllPropertyItems(
		__in UINT totalBufferSize,
		__in UINT numProperties,
		__out PropertyItem* allItems
		)
	{
		if (allItems == NULL) 
		{
			return SetStatus(InvalidParameter);
		}
		return SetStatus(DllExports::GdipGetAllPropertyItems(hImage,
															 totalBufferSize,
															 numProperties,
															 allItems));
	}
	//@别名 移除属性项目()
	Status RemovePropertyItem(__in PROPID propId)
	{
		return SetStatus(DllExports::GdipRemovePropertyItem(hImage, propId));
	}
	//@别名 置属性项目()
	Status SetPropertyItem(__in const PropertyItem* item)
	{
		return SetStatus(DllExports::GdipSetPropertyItem(hImage, item));
	}
};
//@别名 GP颜色矩阵类
class GPColorMatrix {
	public:
	Gdiplus::ColorMatrix m_data;
	GPColorMatrix(){m_data={};}
	~GPColorMatrix(){reset();}
	//@别名 重置()
	void reset(){
		m_data.m[0][0] = 1.0f;
		m_data.m[0][1] = 0.0f;
		m_data.m[0][2] = 0.0f;
		m_data.m[0][3] = 0.0f;
		m_data.m[0][4] = 0.0f;

		m_data.m[1][0] = 0.0f;
		m_data.m[1][1] = 1.0f;
		m_data.m[1][2] = 0.0f;
		m_data.m[1][3] = 0.0f;
		m_data.m[1][4] = 0.0f;
		 
		m_data.m[2][0] = 0.0f;
		m_data.m[2][1] = 0.0f;
		m_data.m[2][2] = 1.0f;
		m_data.m[2][3] = 0.0f;
		m_data.m[2][4] = 0.0f;
		
		m_data.m[3][0] = 0.0f;
		m_data.m[3][1] = 0.0f;
		m_data.m[3][2] = 0.0f;
		m_data.m[3][3] = 1.0f;
		m_data.m[3][4] = 0.0f;
		 
		m_data.m[4][0] = 0.0f;
		m_data.m[4][1] = 0.0f;
		m_data.m[4][2] = 0.0f;
		m_data.m[4][3] = 0.0f;
		m_data.m[4][4] = 1.0f;    
	}
	//@别名 取指针()
	Gdiplus::ColorMatrix* ptr()
	{
		return &m_data;
	}
	//@别名 取数据()
	Gdiplus::ColorMatrix& data()
	{
		return m_data;
	}
	//@备注 -1 到 1 之间
	//@别名 置红色()
	void Setred(float Scale){
		m_data.m[3][0] = (Gdiplus::REAL)Scale;
	}
	//@备注 -1 到 1 之间
	//@别名 置绿色()
	void Setgreen(float Scale){
		m_data.m[3][1] = (Gdiplus::REAL)Scale;
	}
	//@备注 -1 到 1 之间
	//@别名 置蓝色()
	void Setblue(float Scale){
		m_data.m[3][2] = (Gdiplus::REAL)Scale;
	}
	//@备注 -1 到 1 之间
	//@别名 置透明度()
	void Setalpha(float Scale){
		m_data.m[3][3] = (Gdiplus::REAL)Scale;
	}
	//@备注 -1 到 1 之间
	//@别名 置亮度()
	void Setbrightness(float Scale){
		m_data.m[4][0] = m_data.m[4][1] = m_data.m[4][2] =(Gdiplus::REAL)Scale;
	}
	//@别名 去色()
	void Decolorization(){
		m_data.m[0][0] = m_data.m[0][1] = m_data.m[0][2] = 0.229f;
		m_data.m[1][0] = m_data.m[1][1] = m_data.m[1][2] = 0.587f;
		m_data.m[2][0] = m_data.m[2][1] = m_data.m[2][2] = 0.114f;
	}
	//@别名 反相()
	void opposition(){
		m_data.m[0][0] = m_data.m[1][1] = m_data.m[2][2] = -1.0f;
		m_data.m[3][0] = m_data.m[3][1] = m_data.m[3][2] = 0.999f;
	}
	//@备注 0-2 之间
	//@别名 对比度()
	void contrastratio(float Scale){
		m_data.m[0][0] = m_data.m[1][1] = m_data.m[2][2] = (Gdiplus::REAL)Scale;
		m_data.m[3][0] = m_data.m[3][1] = m_data.m[3][2] = 0.001f;
	}
	//@备注 0-2 之间
	//@别名 饱和度()
	void saturation(float Scale){
		m_data.m[0][0] = m_data.m[0][1] = m_data.m[0][2] = (1.0f - (Gdiplus::REAL)Scale) * 0.229f;
		m_data.m[1][0] = m_data.m[1][1] = m_data.m[1][2] = (1.0f - (Gdiplus::REAL)Scale) * 0.587f;
		m_data.m[2][0] = m_data.m[2][1] = m_data.m[2][2] = (1.0f - (Gdiplus::REAL)Scale) * 0.114f;
		m_data.m[0][0]+=(Gdiplus::REAL)Scale;
		m_data.m[1][1]+=(Gdiplus::REAL)Scale;
		m_data.m[2][2]+=(Gdiplus::REAL)Scale;
	}
	//@备注 -180 到 180 之间
	//@别名 色相()
	void hue(int Scale){
		float f = (Scale / 180) * 3.1415926535f;
		float cosval = std::cosf(f);
		m_data.m[0][0] = m_data.m[1][1] = m_data.m[2][2] =  cosval < 0.0f ? 0.0f : cosval;
		m_data.m[0][1] = m_data.m[1][2] = m_data.m[2][0] =  f < 0.0f ? (cosval < 0.0f ? -cosval : 0.0f) : (cosval < 0 ?  1.0f + cosval : 1.0f - cosval);
		m_data.m[0][2] = m_data.m[1][0] = m_data.m[2][1] =  f < 0.0f ? (cosval < 0.0f ?  1.0f + cosval : 1.0f - cosval) : (cosval < 0.0f ?  -cosval : 0.0f);
	}
};
//@别名 GP图像属性类
class GPImageAttributes : public GPbase {
	//@隐藏{
	public:
	Gdiplus::GpImageAttributes *nativeImageAttr;
	public:
	GPImageAttributes(){
		nativeImageAttr = nullptr;
		lastResult = DllExports::GdipCreateImageAttributes(&nativeImageAttr);
	}
	~GPImageAttributes(){
		Destory();
	}
	//@隐藏}
	//@别名 取指针()
	Gdiplus::GpImageAttributes* GetPtr(){
		return nativeImageAttr;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(nativeImageAttr) Gdiplus::DllExports::GdipDisposeImageAttributes(nativeImageAttr);
		nativeImageAttr = nullptr;
	}
	//@别名 克隆()
	BOOL Clone(GPImageAttributes &ImageAttr) 
    {
        GpImageAttributes* clone;
        SetStatus(DllExports::GdipCloneImageAttributes(
                                            nativeImageAttr,
                                            &clone));
		ImageAttr.nativeImageAttr = clone;
		ImageAttr.lastResult = lastResult;
        return lastResult == Gdiplus::Ok;
    }
	//@别名 置到标准()
    Status
    SetToIdentity(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesToIdentity(
                                            nativeImageAttr,
                                            type));
    }
	//@别名 重置()
    Status
    Reset(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipResetImageAttributes(
                                            nativeImageAttr,
                                            type));
    }
	//@别名 置颜色矩阵()
    Status
    SetColorMatrix(
        __in GPColorMatrix *colorMatrix,
        __in ColorMatrixFlags mode = ColorMatrixFlagsDefault,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorMatrix(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            colorMatrix->ptr(),
                                            NULL,
                                            mode));
    }
	//@别名 清除颜色矩阵()
    Status ClearColorMatrix(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorMatrix(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            NULL,
                                            NULL,
                                            ColorMatrixFlagsDefault));
    }
	//@别名 置颜色矩阵2()
    Status
    SetColorMatrices(
        __in GPColorMatrix *colorMatrix,
        __in GPColorMatrix *grayMatrix,
        __in ColorMatrixFlags mode = ColorMatrixFlagsDefault,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorMatrix(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            colorMatrix->ptr(),
                                            grayMatrix->ptr(),
                                            mode));
    }
	//@别名 清除颜色矩阵2()
    Status ClearColorMatrices(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorMatrix(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            NULL,
                                            NULL,
                                            ColorMatrixFlagsDefault));
    }
	//@别名 置临界值()
    Status SetThreshold(
        __in REAL threshold,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesThreshold(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            threshold));
    }
	//@别名 清除临界值()
    Status ClearThreshold(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesThreshold(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            0.0));
    }
	//@别名 置伽玛值()
    Status SetGamma(
        __in REAL gamma,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesGamma(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            gamma));
    }
	//@别名 清除伽玛值()
    Status ClearGamma(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesGamma(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            0.0));
    }
	//@别名 置无操作()
    Status SetNoOp(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesNoOp(
                                            nativeImageAttr,
                                            type,
                                            TRUE));
    }
	//@别名 清除无操作()
    Status ClearNoOp(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesNoOp(
                                            nativeImageAttr,
                                            type,
                                            FALSE));
    }
	//@别名 置颜色键()
    Status SetColorKey(
        __in const Color& colorLow, 
        __in const Color& colorHigh,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorKeys(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            colorLow.GetValue(),
                                            colorHigh.GetValue()));
    }
	//@别名 清除颜色键()
    Status ClearColorKey(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesColorKeys(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            NULL,
                                            NULL));
    }
	//@别名 置输出通道()
    Status SetOutputChannel(
        __in ColorChannelFlags channelFlags,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesOutputChannel(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            channelFlags));
    }
	//@别名 清除输出通道()
    Status ClearOutputChannel(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesOutputChannel(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            ColorChannelFlagsLast));
    }
	//@别名 置输出通道配置文件()
    Status SetOutputChannelColorProfile(
        __in const WCHAR *colorProfileFilename,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesOutputChannelColorProfile(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            colorProfileFilename));
    }
	//@别名 清除输出通道配置文件()
    Status ClearOutputChannelColorProfile(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesOutputChannelColorProfile(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            NULL));
    }
    //@别名 置重映射表()
    Status SetRemapTable(
        __in UINT mapSize, 
        __in const ColorMap *map,
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesRemapTable(
                                            nativeImageAttr,
                                            type,
                                            TRUE,
                                            mapSize,
                                            map));
    }
	//@别名 清除重映射表()
    Status ClearRemapTable(
        __in ColorAdjustType type = ColorAdjustTypeDefault
        )
    {
        return SetStatus(DllExports::GdipSetImageAttributesRemapTable(
                                            nativeImageAttr,
                                            type,
                                            FALSE,
                                            0,
                                            NULL));
    }
	//@别名 置画刷重映射表()
    Status SetBrushRemapTable(__in UINT mapSize, 
                              __in const ColorMap *map)
    {
        return this->SetRemapTable(mapSize, map, ColorAdjustTypeBrush);
    }
	//@别名 清除画刷重映射表()
    Status ClearBrushRemapTable()
    {
        return this->ClearRemapTable(ColorAdjustTypeBrush);
    }
	//@别名 置环绕模式()
    Status SetWrapMode(__in WrapMode wrap, 
                       __in const Color& color = Color(), 
                       __in BOOL clamp = FALSE) 
    {
        ARGB argb = color.GetValue();

        return SetStatus(DllExports::GdipSetImageAttributesWrapMode(
                           nativeImageAttr, wrap, argb, clamp));
    }
    // The flags of the palette are ignored.
	//@别名 取调整调色板()
    Status GetAdjustedPalette(__in_out ColorPalette* colorPalette,
                              __in ColorAdjustType colorAdjustType)  
    {
        return SetStatus(DllExports::GdipGetImageAttributesAdjustedPalette(
                           nativeImageAttr, colorPalette, colorAdjustType));
    }

private:
    GPImageAttributes(const GPImageAttributes &);
    GPImageAttributes& operator=(const GPImageAttributes &);
};
//@别名 GP图元文件类
class GPMetafile : public GPImage {
	//@别名 创建自WMF()
	inline
	BOOL FromWmf(
		__in HMETAFILE                      hWmf,
		__in const WmfPlaceableFileHeader * wmfPlaceableFileHeader,
		__in BOOL                           deleteWmf
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipCreateMetafileFromWmf(hWmf, deleteWmf, 
														   wmfPlaceableFileHeader, 
														   &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自EMF()
	inline    
	BOOL FromEmf(
		__in HENHMETAFILE hEmf,
		__in BOOL deleteEmf
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipCreateMetafileFromEmf(hEmf, deleteEmf, 
														   &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自文件()
	inline
	BOOL FromFile(__in const WCHAR* filename)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipCreateMetafileFromFile(filename, 
															&metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自WMF文件()
	inline
	BOOL FromWmfFile(
		__in const WCHAR*                   filename,
		__in const WmfPlaceableFileHeader * wmfPlaceableFileHeader
		)
	{
		GpMetafile *    metafile = NULL;
		
		lastResult = DllExports::GdipCreateMetafileFromWmfFile(filename, 
															   wmfPlaceableFileHeader, 
															   &metafile);
		
		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自字节集()
	inline
	BOOL FromStream(__in const CXBytes& bytes)
	{
		GpMetafile *    metafile = NULL;
		IStream* stream = CreateStream(bytes);
		lastResult = DllExports::GdipCreateMetafileFromStream(stream, 
															  &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录()
	inline
	BOOL RecordMetafile(
		__in HDC                 referenceHdc,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafile(
						referenceHdc, type, NULL, MetafileFrameUnitGdi,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录()
	inline
	BOOL RecordMetafile(
		__in HDC                 referenceHdc,
		__in const RectF &       frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,       
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafile(
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录I()
	inline
	BOOL RecordMetafileI(
		__in HDC                 referenceHdc,
		__in const Rect &        frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafileI(
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录文件名()
	inline
	BOOL RecordMetafileFileName(
		__in const WCHAR*        fileName,
		__in HDC                 referenceHdc,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafileFileName(fileName,
						referenceHdc, type, NULL, MetafileFrameUnitGdi,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录文件名()
	inline
	BOOL RecordMetafileFileName(
		__in const WCHAR*        fileName,
		__in HDC                 referenceHdc,
		__in const RectF &       frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafileFileName(fileName,
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录文件名I()
	inline
	BOOL RecordMetafileFileNameI(
		__in const WCHAR*        fileName,
		__in HDC                 referenceHdc,
		__in const Rect &        frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;

		lastResult = DllExports::GdipRecordMetafileFileNameI(fileName,
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录字节集()
	inline
	BOOL RecordMetafileStream(
		__in const CXBytes& bytes,
		__in HDC                 referenceHdc,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;
		IStream* stream = CreateStream(bytes);
		lastResult = DllExports::GdipRecordMetafileStream(stream,
						referenceHdc, type, NULL, MetafileFrameUnitGdi,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录字节集()
	inline
	BOOL RecordMetafileStream(
		__in const CXBytes& bytes,
		__in HDC                 referenceHdc,
		__in const RectF &       frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;
		IStream* stream = CreateStream(bytes);
		lastResult = DllExports::GdipRecordMetafileStream(stream,
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自记录字节集I()
	inline
	BOOL RecordMetafileStreamI(
		__in const CXBytes& bytes,
		__in HDC                 referenceHdc,
		__in const Rect &        frameRect,
		__in MetafileFrameUnit   frameUnit,
		__in EmfType             type,
		__in const WCHAR *       description
		)
	{
		GpMetafile *    metafile = NULL;
		IStream* stream = CreateStream(bytes);
		lastResult = DllExports::GdipRecordMetafileStreamI(stream,
						referenceHdc, type, &frameRect, frameUnit,
						description, &metafile);

		SetNativeImage(metafile);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取图元文件头自WMF()
	inline Status
	GetMetafileHeader(
		__in HMETAFILE                       hWmf,
		__in const WmfPlaceableFileHeader *  wmfPlaceableFileHeader,
		__out MetafileHeader *               header
		)
	{
		return DllExports::GdipGetMetafileHeaderFromWmf(hWmf,
														wmfPlaceableFileHeader, 
														header);
	}
	//@别名 取图元文件头自EMF()
	inline Status
	GetMetafileHeader(
		__in HENHMETAFILE        hEmf,
		__out MetafileHeader *   header
		)
	{
		return DllExports::GdipGetMetafileHeaderFromEmf(hEmf, header);
	}
	//@别名 取图元文件头自文件名()
	inline Status
	GetMetafileHeader(
		__in const WCHAR*        filename,
		__out MetafileHeader *   header
		)
	{
		return DllExports::GdipGetMetafileHeaderFromFile(filename, header);
	}
	//@别名 取图元文件头自字节集()
	inline Status
	GetMetafileHeader(
		__in const CXBytes& bytes,
		__out MetafileHeader *   header
		)
	{
		IStream* stream = CreateStream(bytes);
		return DllExports::GdipGetMetafileHeaderFromStream(stream, header);
	}
	//@别名 取图元文件头()
	inline Status
	GetMetafileHeader(
		__out MetafileHeader *    header
		) 
	{
		return SetStatus(DllExports::GdipGetMetafileHeaderFromMetafile(
											  (GpMetafile *)hImage,
											  header));
	}

	// Once this method is called, the Metafile object is in an invalid state
	// and can no longer be used.  It is the responsiblity of the caller to
	// invoke DeleteEnhMetaFile to delete this hEmf.
	//@别名 取EMF句柄()
	inline HENHMETAFILE
	GetHENHMETAFILE()
	{
		HENHMETAFILE hEmf;

		SetStatus(DllExports::GdipGetHemfFromMetafile(
								  (GpMetafile *)hImage, 
								  &hEmf));

		return hEmf;
	}

	// Used in conjuction with Graphics::EnumerateMetafile to play an EMF+
	// The data must be DWORD aligned if it's an EMF or EMF+.  It must be
	// WORD aligned if it's a WMF.
	//@别名 播放记录()
	inline Status
	PlayRecord(
		__in EmfPlusRecordType   recordType,
		__in UINT                flags,
		__in UINT                dataSize,
		__in const BYTE *        data
		) 
	{
		return SetStatus(DllExports::GdipPlayMetafileRecord(
								(GpMetafile *)hImage,
								recordType,
								flags,
								dataSize,
								data));
	}

	// If you're using a printer HDC for the metafile, but you want the
	// metafile rasterized at screen resolution, then use this API to set
	// the rasterization dpi of the metafile to the screen resolution,
	// e.g. 96 dpi or 120 dpi.
	//@别名 置下层光栅化限制()
	inline Status
	SetDownLevelRasterizationLimit(
		__in UINT     metafileRasterizationLimitDpi
		)
	{
		return SetStatus(DllExports::
						 GdipSetMetafileDownLevelRasterizationLimit(
								(GpMetafile *)hImage,
								metafileRasterizationLimitDpi));
	}
	//@别名 取下层光栅化限制()
	inline UINT
	GetDownLevelRasterizationLimit() 
	{
		UINT    metafileRasterizationLimitDpi = 0;

		SetStatus(DllExports::GdipGetMetafileDownLevelRasterizationLimit(
								(GpMetafile *)hImage,
								&metafileRasterizationLimitDpi));

		return metafileRasterizationLimitDpi;
	}
	//@别名 EMF到WMF数据()
	inline UINT
	EmfToWmfBits(
		__in HENHMETAFILE       hemf,
		__in UINT               cbData16,
		__out LPBYTE            pData16,
		__in INT                iMapMode,
		__in INT                eFlags
		)
	{
		return DllExports::GdipEmfToWmfBits(
			hemf,
			cbData16,
			pData16,
			iMapMode,
			eFlags);
	}
};

//@分组}
//@分组{  Gdiplus
//@别名 GP路径类
class GPPath : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpPath *nativePath;
	public:
	GPPath(){
		nativePath = nullptr;
	}
	~GPPath(){
		Destory();
	}
	//@隐藏}
	//@别名 取指针()
	Gdiplus::GpPath* GetPtr(){
		return nativePath;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(nativePath) Gdiplus::DllExports::GdipDeletePath(nativePath);
		nativePath = nullptr;
	}
	//@别名 克隆()
	BOOL Clone(GPPath &hPath) 
    {
        GpPath *clonepath = NULL;
        SetStatus(DllExports::GdipClonePath(nativePath, &clonepath));
		hPath.nativePath = clonepath;
		hPath.lastResult = lastResult;
        return lastResult == Gdiplus::Ok;
    }
	//@别名 创建()
    BOOL Create(__in FillMode fillmode = FillModeAlternate)
    {   
		this->Destory();
		lastResult = Gdiplus::DllExports::GdipCreatePath(fillmode, &nativePath);
		return lastResult == Gdiplus::Ok;
    }
	//@别名 创建自坐标组()
    BOOL CreatePoints(__in const PointF* points,
                 __in const BYTE* types,
                 __in INT count,
                 __in FillMode fillMode = FillModeAlternate)
    {
        nativePath = NULL;
        lastResult = DllExports::GdipCreatePath2(points, types,count,fillMode,&nativePath);
		return lastResult == Gdiplus::Ok;
    }
	//@别名 创建自坐标组I()
    BOOL CreatePoints(__in const Point* points,
                 __in const BYTE* types,
                 __in INT count,
                 __in FillMode fillMode = FillModeAlternate)
    {
        nativePath = NULL;
        lastResult = DllExports::GdipCreatePath2I(points, types,count,fillMode,&nativePath);
		return lastResult == Gdiplus::Ok;
    }
    // Reset the path object to empty (and fill mode to FillModeAlternate)
	//@别名 重置()
    Status Reset()
    {
        return SetStatus(DllExports::GdipResetPath(nativePath));
    }
	//@别名 取填充模式()
    FillMode GetFillMode() 
    {
        FillMode fillmode = FillModeAlternate;

        SetStatus(DllExports::GdipGetPathFillMode(nativePath, &fillmode));

        return fillmode;
    }
	//@别名 置填充模式()
    Status SetFillMode(__in FillMode fillmode)
    {
        return SetStatus(DllExports::GdipSetPathFillMode(nativePath, 
                                                         fillmode));
    }
	//@别名 取路径数据()
    Status GetPathData(__out PathData* pathData) 
    {
        if (pathData == NULL) 
        {
            return SetStatus(InvalidParameter);
        }
        
        INT count = GetPointCount();
        
        if ((count <= 0) || (pathData->Count>0 && pathData->Count<count))
        {
            pathData->Count = 0;
            if (pathData->Points)
            {
                delete [] pathData->Points;
                pathData->Points = NULL;
            }

            if (pathData->Types) 
            {
                delete [] pathData->Types;
                pathData->Types = NULL;
            }

            if (count <= 0)
            {
                return Ok;
            }
        }

        if (pathData->Count == 0) 
        {
            pathData->Points = new PointF[count];
            if (pathData->Points == NULL) 
            {
                return SetStatus(OutOfMemory);
            
            }
            pathData->Types = new byte[count];
            if (pathData->Types == NULL) 
            {
                delete [] pathData->Points;
                pathData->Points = NULL;

                return SetStatus(OutOfMemory);
            }
            pathData->Count = count;
        }

        return SetStatus(DllExports::GdipGetPathData(nativePath, pathData));
    }
	//@别名 开始图形()
    Status StartFigure()
    {
        return SetStatus(DllExports::GdipStartPathFigure(nativePath));
    }
	//@别名 关闭图形()
    Status CloseFigure()
    {
        return SetStatus(DllExports::GdipClosePathFigure(nativePath));
    }
	//@别名 关闭所有图形()
    Status CloseAllFigures()
    {
        return SetStatus(DllExports::GdipClosePathFigures(nativePath));
    }
	//@别名 置标记()
    Status SetMarker()
    {
        return SetStatus(DllExports::GdipSetPathMarker(nativePath));
    }
	//@别名 清除标记()
    Status ClearMarkers()
    {
        return SetStatus(DllExports::GdipClearPathMarkers(nativePath));
    }
	//@别名 反向()
    Status Reverse()
    {
        return SetStatus(DllExports::GdipReversePath(nativePath));
    }
	//@别名 取最后坐标()
    Status GetLastPoint(__out PointF* lastPoint) 
    {
        return SetStatus(DllExports::GdipGetPathLastPoint(nativePath, 
                                                          lastPoint));
    }
	//@别名 添加直线()
    Status AddLine(__in const PointF& pt1, 
                   __in const PointF& pt2)
    {
        return AddLine(pt1.X, pt1.Y, pt2.X, pt2.Y);
    }
	//@别名 添加直线()
    Status AddLine(__in REAL x1,
                   __in REAL y1, 
                   __in REAL x2, 
                   __in REAL y2)
    {
        return SetStatus(DllExports::GdipAddPathLine(nativePath, x1, y1, 
                                                     x2, y2));
    }
	//@别名 添加直线组()
    Status AddLines(__in const PointF* points, 
                    __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathLine2(nativePath, points, 
                                                      count));
    }
	//@别名 添加直线()
    Status AddLine(__in const Point& pt1, 
                   __in const Point& pt2)
    {
        return AddLine(pt1.X,
                       pt1.Y,
                       pt2.X,
                       pt2.Y);
    }
	//@别名 添加直线()
    Status AddLine(__in INT x1, 
                   __in INT y1, 
                   __in INT x2, 
                   __in INT y2)
    {
        return SetStatus(DllExports::GdipAddPathLineI(nativePath,
                                                     x1,
                                                     y1,
                                                     x2,
                                                     y2));
    }
	//@别名 添加直线组()
    Status AddLines(__in const Point* points, 
                    __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathLine2I(nativePath,
                                                       points,
                                                       count));
    }
	//@别名 添加圆弧()
    Status AddArc(__in const RectF& rect, 
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return AddArc(rect.X, rect.Y, rect.Width, rect.Height,
                      startAngle, sweepAngle);
    }
	//@别名 添加圆弧()
    Status AddArc(__in REAL x, 
                  __in REAL y, 
                  __in REAL width, 
                  __in REAL height,
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return SetStatus(DllExports::GdipAddPathArc(nativePath, x, y, width, 
                                                    height, startAngle, 
                                                    sweepAngle));
    }
	//@别名 添加圆弧()
    Status AddArc(__in const Rect& rect, 
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return AddArc(rect.X, rect.Y, rect.Width, rect.Height,
                      startAngle, sweepAngle);
    }
	//@别名 添加圆弧()
    Status AddArc(__in INT x, 
                  __in INT y, 
                  __in INT width, 
                  __in INT height,
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return SetStatus(DllExports::GdipAddPathArcI(nativePath,
                                                    x,
                                                    y,
                                                    width,
                                                    height,
                                                    startAngle,
                                                    sweepAngle));
    }
	//@别名 添加贝塞尔曲线()
    Status AddBezier(__in const PointF& pt1, 
                     __in const PointF& pt2,
                     __in const PointF& pt3, 
                     __in const PointF& pt4)
    {
        return AddBezier(pt1.X, pt1.Y, pt2.X, pt2.Y, pt3.X, pt3.Y, pt4.X,
                         pt4.Y);
    }
	//@别名 添加贝塞尔曲线()
    Status AddBezier(__in REAL x1, 
                     __in REAL y1, 
                     __in REAL x2, 
                     __in REAL y2,
                     __in REAL x3, 
                     __in REAL y3, 
                     __in REAL x4, 
                     __in REAL y4)
    {
        return SetStatus(DllExports::GdipAddPathBezier(nativePath, x1, y1, x2, 
                                                       y2, x3, y3, x4, y4));
    }
	//@别名 添加贝塞尔曲线组()
    Status AddBeziers(__in const PointF* points, 
                      __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathBeziers(nativePath, points, 
                                                        count));
    }
	//@别名 添加贝塞尔曲线()
    Status AddBezier(__in const Point& pt1, 
                     __in const Point& pt2,
                     __in const Point& pt3, 
                     __in const Point& pt4)
    {
       return AddBezier(pt1.X, pt1.Y, pt2.X, pt2.Y, pt3.X, pt3.Y, pt4.X,
                        pt4.Y);
    }
	//@别名 添加贝塞尔曲线()
    Status AddBezier(__in INT x1, 
                     __in INT y1, 
                     __in INT x2, 
                     __in INT y2,
                     __in INT x3,
                     __in INT y3, 
                     __in INT x4, 
                     __in INT y4)
    {
       return SetStatus(DllExports::GdipAddPathBezierI(nativePath,
                                                      x1,
                                                      y1,
                                                      x2,
                                                      y2,
                                                      x3,
                                                      y3,
                                                      x4,
                                                      y4));
    }
	//@别名 添加贝塞尔曲线组()
    Status AddBeziers(__in const Point* points,
                      __in INT count)
    {
       return SetStatus(DllExports::GdipAddPathBeziersI(nativePath,
                                                        points,
                                                        count));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const PointF* points, 
                    __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathCurve(nativePath,
                                                      points,
                                                      count));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const PointF* points, 
                    __in INT count,
                    __in REAL tension)
    {
        return SetStatus(DllExports::GdipAddPathCurve2(nativePath,
                                                       points,
                                                       count,
                                                       tension));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const PointF* points, 
                    __in INT count, 
                    __in INT offset,
                    __in INT numberOfSegments, 
                    __in REAL tension)
    {
        return SetStatus(DllExports::GdipAddPathCurve3(nativePath,
                                                       points,
                                                       count,
                                                       offset,
                                                       numberOfSegments,
                                                       tension));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const Point* points, 
                    __in INT count)
    {
       return SetStatus(DllExports::GdipAddPathCurveI(nativePath,
                                                     points,
                                                     count));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const Point* points, 
                    __in INT count, 
                    __in REAL tension)
    {
       return SetStatus(DllExports::GdipAddPathCurve2I(nativePath,
                                                      points,
                                                      count,
                                                      tension));
    }
	//@别名 添加曲线()
    Status AddCurve(__in const Point* points, 
                    __in INT count, 
                    __in INT offset,
                    __in INT numberOfSegments, 
                    __in REAL tension)
    {
       return SetStatus(DllExports::GdipAddPathCurve3I(nativePath,
                                                      points,
                                                      count,
                                                      offset,
                                                      numberOfSegments,
                                                      tension));
    }
	//@别名 添加闭合曲线()
    Status AddClosedCurve(__in const PointF* points, 
                          __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathClosedCurve(nativePath,
                                                            points,
                                                            count));
    }
	//@别名 添加闭合曲线()
    Status AddClosedCurve(__in const PointF* points, 
                          __in INT count, 
                          __in REAL tension)
    {
        return SetStatus(DllExports::GdipAddPathClosedCurve2(nativePath,
                                                             points,
                                                             count,
                                                             tension));
    }
	//@别名 添加闭合曲线()
    Status AddClosedCurve(__in const Point* points, 
                          __in INT count)
    {
       return SetStatus(DllExports::GdipAddPathClosedCurveI(nativePath,
                                                            points,
                                                            count));
    }
	//@别名 添加闭合曲线()
    Status AddClosedCurve(__in const Point* points, 
                          __in INT count,
                          __in REAL tension)
    {
       return SetStatus(DllExports::GdipAddPathClosedCurve2I(nativePath,
                                                             points,
                                                             count,
                                                             tension));
    }
	//@别名 添加矩形()
    Status AddRectangle(__in const RectF& rect)
    {
        return SetStatus(DllExports::GdipAddPathRectangle(nativePath,
                                                          rect.X,
                                                          rect.Y,
                                                          rect.Width,
                                                          rect.Height));
    }
	//@别名 添加矩形组()
    Status AddRectangles(__in const RectF* rects, 
                         __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathRectangles(nativePath,
                                                           rects,
                                                           count));
    }
	//@别名 添加矩形()
    Status AddRectangle(__in const Rect& rect)
    {
        return SetStatus(DllExports::GdipAddPathRectangleI(nativePath,
                                                          rect.X,
                                                          rect.Y,
                                                          rect.Width,
                                                          rect.Height));
    }
	//@别名 添加矩形组()
    Status AddRectangles(__in const Rect* rects, INT count)
    {
        return SetStatus(DllExports::GdipAddPathRectanglesI(nativePath,
                                                           rects,
                                                           count));
    }
	//@别名 添加圆角矩形()
	Status AddRoundRect(float x, float y, float width, float height, float roundWidth, float roundHeight)
	{
		float hew = roundWidth / 2;
		float heh = roundHeight / 2;
		SetStatus(Gdiplus::DllExports::GdipAddPathLine( nativePath, x + hew, y, x + width - hew, x)); // 顶部横线
		SetStatus(Gdiplus::DllExports::GdipAddPathArc( nativePath, x + width - 2 * hew, y, 2 * hew, 2 * heh, 270, 90));  // 右上圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLine (nativePath, x + width, y + heh, x + width, y + height - heh));  // 右侧竖线
		SetStatus(Gdiplus::DllExports::GdipAddPathArc (nativePath, x + width - 2 * hew, y + height - 2 * heh, 2 * hew, 2 * heh, 0, 90));  // 右下圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLine (nativePath, x + width - hew, y + height, x + hew, y + height));  // 底部横线
		SetStatus(Gdiplus::DllExports::GdipAddPathArc (nativePath, x, y + height - 2 * heh, 2 * hew, 2 * heh, 90, 90));  //左下圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLine (nativePath, x, y + height - heh, x, y + heh));  //左侧竖线
		return  SetStatus(Gdiplus::DllExports::GdipAddPathArc (nativePath, x, y, 2 * hew, 2 * heh, 180, 90));  //左上圆角    
	}
	//@别名 添加圆角矩形I()
	Status AddRoundRectI(INT x, INT y, INT width, INT height, INT roundWidth, INT roundHeight)
	{
		INT hew = roundWidth / 2;
		INT heh = roundHeight / 2;
		SetStatus(Gdiplus::DllExports::GdipAddPathLineI( nativePath, x + hew, y, x + width - hew, x)); // 顶部横线
		SetStatus(Gdiplus::DllExports::GdipAddPathArcI( nativePath, x + width - 2 * hew, y, 2 * hew, 2 * heh, 270, 90));  // 右上圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLineI (nativePath, x + width, y + heh, x + width, y + height - heh));  // 右侧竖线
		SetStatus(Gdiplus::DllExports::GdipAddPathArcI (nativePath, x + width - 2 * hew, y + height - 2 * heh, 2 * hew, 2 * heh, 0, 90));  // 右下圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLineI (nativePath, x + width - hew, y + height, x + hew, y + height));  // 底部横线
		SetStatus(Gdiplus::DllExports::GdipAddPathArcI (nativePath, x, y + height - 2 * heh, 2 * hew, 2 * heh, 90, 90));  //左下圆角

		SetStatus(Gdiplus::DllExports::GdipAddPathLineI (nativePath, x, y + height - heh, x, y + heh));  //左侧竖线
		return  SetStatus(Gdiplus::DllExports::GdipAddPathArcI (nativePath, x, y, 2 * hew, 2 * heh, 180, 90));  //左上圆角    
	}
	//@别名 添加椭圆()
    Status AddEllipse(__in const RectF& rect)
    {
        return AddEllipse(rect.X, rect.Y, rect.Width, rect.Height);
    }
	//@别名 添加椭圆()
    Status AddEllipse(__in REAL x, 
                      __in REAL y, 
                      __in REAL width, 
                      __in REAL height)
    {
        return SetStatus(DllExports::GdipAddPathEllipse(nativePath,
                                                        x,
                                                        y,
                                                        width,
                                                        height));
    }
	//@别名 添加椭圆()
    Status AddEllipse(__in const Rect& rect)
    {
        return AddEllipse(rect.X, rect.Y, rect.Width, rect.Height);
    }
	//@别名 添加椭圆()
    Status AddEllipse(__in INT x, 
                      __in INT y, 
                      __in INT width, 
                      __in INT height)
    {
        return SetStatus(DllExports::GdipAddPathEllipseI(nativePath,
                                                        x,
                                                        y,
                                                        width,
                                                        height));
    }
	//@别名 添加饼()
    Status AddPie(__in const RectF& rect, 
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return AddPie(rect.X, rect.Y, rect.Width, rect.Height, startAngle,
                      sweepAngle);
    }
	//@别名 添加饼()
    Status AddPie(__in REAL x, 
                  __in REAL y, 
                  __in REAL width, 
                  __in REAL height, 
                  __in REAL startAngle,
                  __in REAL sweepAngle)
    {
        return SetStatus(DllExports::GdipAddPathPie(nativePath, x, y, width,
                                                    height, startAngle, 
                                                    sweepAngle));
    }
	//@别名 添加饼()
    Status AddPie(__in const Rect& rect, 
                  __in REAL startAngle, 
                  __in REAL sweepAngle)
    {
        return AddPie(rect.X,
                      rect.Y,
                      rect.Width,
                      rect.Height,
                      startAngle,
                      sweepAngle);
    }
	//@别名 添加饼()
    Status AddPie(__in INT x, 
                  __in INT y, 
                  __in INT width, 
                  __in INT height, 
                  __in REAL startAngle,
                  __in REAL sweepAngle)
    {
        return SetStatus(DllExports::GdipAddPathPieI(nativePath,
                                                    x,
                                                    y,
                                                    width,
                                                    height,
                                                    startAngle,
                                                    sweepAngle));
    }
	//@别名 添加多边形()
    Status AddPolygon(__in const PointF* points, 
                      __in INT count)
    {
        return SetStatus(DllExports::GdipAddPathPolygon(nativePath, points, 
                                                        count));
    }
	//@别名 添加多边形()
    Status AddPolygon(__in const Point* points, 
                      __in INT count)
    {
       return SetStatus(DllExports::GdipAddPathPolygonI(nativePath, points, 
                                                        count));
    }
	//@别名 添加路径()
    Status AddPath(__in const GPPath* addingPath, 
                   __in BOOL connect)
    {
        GpPath* nativePath2 = NULL;
        if(addingPath)
            nativePath2 = addingPath->nativePath;

        return SetStatus(DllExports::GdipAddPathPath(nativePath, nativePath2, 
                                                     connect));
    }
	//@别名 添加文本()
    Status AddString(
        __in CXText text,
        __in const GPFontFamily    *family,
        __in INT                  style,
        __in REAL                 emSize,  // World units
        __in const PointF        &origin,
        __in const GPStringFormat  *format
    );
	//@别名 添加文本()
    Status AddString(
        __in CXText text,
        __in const GPFontFamily    *family,
        __in INT                  style,
        __in REAL                 emSize,  // World units
        __in const RectF         &layoutRect,
        __in const GPStringFormat  *format
    );  
	//@别名 添加文本()
    Status AddString(
        __in CXText text,
        __in const GPFontFamily    *family,
        __in INT                  style,
        __in REAL                 emSize,  // World units
        __in const Point         &origin,
        __in const GPStringFormat  *format
    );
	//@别名 添加文本()
    Status AddString(
        __in CXText text,
        __in const GPFontFamily    *family,
        __in INT                  style,
        __in REAL                 emSize,  // World units
        __in const Rect          &layoutRect,
        __in const GPStringFormat  *format
    );
    //@别名 变换()
    Status Transform(__in const GPMatrix* matrix)
    {
        if(matrix)
            return SetStatus(DllExports::GdipTransformPath(nativePath, 
                                                      matrix->hMatrix));
        else
            return Ok;
    }
	//@别名 取边界矩形()
    Status GetBounds(__out RectF* bounds,__in const GPMatrix* matrix = NULL,__in const GPPen* pen = NULL) ;
	//@别名 取边界矩形()
    Status GetBounds(__out Rect* bounds,__in const GPMatrix* matrix = NULL,__in const GPPen* pen = NULL) ;
	//@别名 变平()
    Status Flatten(__in const GPMatrix* matrix = NULL, 
                   __in REAL flatness = FlatnessDefault)
    {
        GpMatrix* nativeMatrix = NULL;
        if(matrix)
        {
            nativeMatrix = matrix->hMatrix;
        }
        return SetStatus(DllExports::GdipFlattenPath(
            nativePath, 
            nativeMatrix, 
            flatness
        ));
    }
	//@别名 扩大()
    Status Widen(
        __in const GPPen* pen, 
        __in const GPMatrix* matrix = NULL,
        __in REAL flatness = FlatnessDefault
    );
	//@别名 轮廓线()
    Status Outline(
        __in const GPMatrix *matrix = NULL,
        __in REAL flatness = FlatnessDefault
    )
    {
        GpMatrix* nativeMatrix = NULL;
        if(matrix)
        {
            nativeMatrix = matrix->hMatrix;
        }
        return SetStatus(DllExports::GdipWindingModeOutline(
            nativePath, nativeMatrix, flatness
        ));
    }
    
    // Once this is called, the resultant path is made of line segments and
    // the original path information is lost.  When matrix is NULL, the 
    // identity matrix is assumed.
    //@别名 扭曲()
    Status Warp(__in const PointF* destPoints, 
                __in INT count,
                __in const RectF& srcRect, 
                __in const GPMatrix* matrix = NULL,
                __in WarpMode warpMode = WarpModePerspective,
                __in REAL flatness = FlatnessDefault)
    {
        GpMatrix* nativeMatrix = NULL;
        if(matrix)
            nativeMatrix = matrix->hMatrix;

        return SetStatus(DllExports::GdipWarpPath(
                                        nativePath,
                                        nativeMatrix,
                                        destPoints,
                                        count,
                                        srcRect.X,
                                        srcRect.Y,
                                        srcRect.Width,
                                        srcRect.Height,
                                        warpMode,
                                        flatness));
    }
	//@别名 取坐标数()
    INT GetPointCount() 
    {
        INT count = 0;
        SetStatus(DllExports::GdipGetPointCount(nativePath, &count));
        return count;
    }
	//@别名 取路径类型组()
    Status GetPathTypes(__out BYTE* types, 
                        __in INT count) 
    {
        return SetStatus(DllExports::GdipGetPathTypes(nativePath, types,
                                                      count));
    }
	//@别名 取路径坐标组()
    Status GetPathPoints(__out PointF* points, 
                         __in INT count) 
    {
        return SetStatus(DllExports::GdipGetPathPoints(nativePath, points, 
                                                       count));
    }
	//@别名 取路径坐标组()
    Status GetPathPoints(__out Point* points, 
                         __in INT count) 
    {
        return SetStatus(DllExports::GdipGetPathPointsI(nativePath, points, 
                                                        count));
    }
	//@别名 是否可见()
	BOOL IsVisible(__in const PointF& point, 
                   __in const GPGraphics* g = NULL) ;
	//@别名 是否可见()
	BOOL IsVisible(__in const Point& point,
                   __in const GPGraphics* g = NULL) ;
	//@别名 是否可见轮廓()
	BOOL IsOutlineVisible(__in const PointF& point,
                          __in const GPPen* pen, 
                          __in const GPGraphics* g = NULL) ;
	//@别名 是否可见轮廓I()
	BOOL IsOutlineVisible(__in const Point& point,
                          __in const GPPen* pen, 
                          __in const GPGraphics* g = NULL) ;
};
//@别名 GP区域类
class GPRegion : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpRegion *nativeRegion;
	public:
    
	GPRegion(){
		nativeRegion = nullptr;
	}
	~GPRegion(){
		Destory();
	}
	//@隐藏}
	//@别名 置指针()
	VOID SetNativeRegion(GpRegion* nativeRegion)
	{
		this->nativeRegion = nativeRegion;
	}
	//@别名 取指针()
	Gdiplus::GpRegion* GetPtr(){
		return nativeRegion;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(nativeRegion) Gdiplus::DllExports::GdipDeleteRegion(nativeRegion);
		nativeRegion = nullptr;
	}
	//@别名 创建()
	BOOL Create(){
		GpRegion *region = NULL;
		lastResult = DllExports::GdipCreateRegion(&region);
		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自矩形()
	BOOL CreateFromRect(__in const RectF& rect)
	{
		GpRegion *region = NULL;
		lastResult = DllExports::GdipCreateRegionRect(&rect, &region);
		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自矩形()
	BOOL CreateFromRect(__in const Rect& rect)
	{
		GpRegion *region = NULL;

		lastResult = DllExports::GdipCreateRegionRectI(&rect, &region);

		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自路径()
	BOOL CreateFromPath(__in const GPPath* path)
	{
		GpRegion *region = NULL;
		lastResult = DllExports::GdipCreateRegionPath(path->nativePath, &region);

		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自区域数据()
	BOOL CreateFromRegion(__in CXBytes& regionData)
	{
		GpRegion *region = NULL;
		lastResult = DllExports::GdipCreateRegionRgnData((BYTE*)regionData.getPtr(), regionData.getSize(), &region);
		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自句柄()
	BOOL CreateFromHRGN(__in HRGN hRgn)
	{
		GpRegion *region = NULL;
		lastResult = DllExports::GdipCreateRegionHrgn(hRgn, &region);
		SetNativeRegion(region);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 克隆()
	BOOL Clone(GPRegion& hregion) 
	{
		GpRegion *region = NULL;
		SetStatus(DllExports::GdipCloneRegion(nativeRegion, &region));
		hregion.nativeRegion = region;
		hregion.lastResult = lastResult;
		return lastResult == Gdiplus::Ok;
	}
	//@别名 置为无限()
	Status MakeInfinite()
	{
		return SetStatus(DllExports::GdipSetInfinite(nativeRegion));
	}
	//@别名 置为空()
	Status MakeEmpty()
	{
		return SetStatus(DllExports::GdipSetEmpty(nativeRegion));
	}
	//@别名 交集()
	Status Intersect(__in const RectF& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRect(nativeRegion, &rect, 
														   CombineModeIntersect));
	}
	//@别名 交集()
	Status Intersect(__in const Rect& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRectI(nativeRegion, &rect, 
															CombineModeIntersect));
	}
	//@别名 交集()
	Status Intersect(__in const GPPath* path);
	//@别名 交集()
	Status Intersect(__in const GPRegion* region);
	//@别名 并集()
	Status Union(__in const RectF& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRect(nativeRegion, &rect, 
														   CombineModeUnion));
	}
	//@别名 并集()
	Status Union(__in const Rect& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRectI(nativeRegion, &rect, 
															CombineModeUnion));
	}
	//@别名 并集()
	Status Union(__in const GPPath* path);
	//@别名 并集()
	Status Union(__in const GPRegion* region);
	//@别名 异或()
	Status Xor(__in const RectF& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRect(nativeRegion, &rect, 
														   CombineModeXor));
	}
	//@别名 异或()
	Status Xor(__in const Rect& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRectI(nativeRegion, &rect, 
															CombineModeXor));
	}
	//@别名 异或()
	Status Xor(__in const GPPath* path);
	//@别名 异或()
	Status Xor(__in const GPRegion* region);
	//@别名 排除()
	Status Exclude(__in const RectF& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRect(nativeRegion, &rect, 
														   CombineModeExclude));
	}
	//@别名 排除()
	Status Exclude(__in const Rect& rect)
	{
		 return SetStatus(DllExports::GdipCombineRegionRectI(nativeRegion, &rect, 
															 CombineModeExclude));
	}
	//@别名 排除()
	Status Exclude(__in const GPPath* path);
	//@别名 排除()
	Status Exclude(__in const GPRegion* region);
	//@别名 补集()
	Status Complement(__in const RectF& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRect(nativeRegion, &rect, 
														   CombineModeComplement));
	}
	//@别名 补集()
	Status Complement(__in const Rect& rect)
	{
		return SetStatus(DllExports::GdipCombineRegionRectI(nativeRegion, &rect, 
															CombineModeComplement));
	}
	//@别名 补集()
	Status Complement(__in const GPPath* path);
	//@别名 补集()
	Status Complement(__in const GPRegion* region);
	//@别名 平移()
	Status Translate(__in REAL dx, 
                  __in REAL dy)
	{
		return SetStatus(DllExports::GdipTranslateRegion(nativeRegion, dx, dy));
	}
	//@别名 平移()
	Status Translate(__in INT dx, 
					  __in INT dy)
	{
		return SetStatus(DllExports::GdipTranslateRegionI(nativeRegion, dx, dy));
	}
	//@别名 置矩阵()
	Status Transform(__in const GPMatrix* matrix);
	//@别名 取边界矩形()
	Status GetBounds(__out RectF* rect, __in const GPGraphics* g) ;
	//@别名 取边界矩形()
	Status GetBounds(__out Rect* rect, __in const GPGraphics* g) ;
	//@别名 取区域句柄()
	HRGN GetHRGN(__in const GPGraphics* g) ;
	//@别名 是否空()
	BOOL IsEmpty(__in const GPGraphics *g) ;
	//@别名 是否无限()
	BOOL IsInfinite(__in const GPGraphics *g) ;
	//@别名 是否相等()
	BOOL Equals(__in const GPRegion* region,  __in const GPGraphics* g) ;
	// Get the size of the buffer needed for the GetData method
	//@别名 取数据大小()
	UINT GetDataSize() 
	{
		UINT     bufferSize = 0;
		SetStatus(DllExports::GdipGetRegionDataSize(nativeRegion, &bufferSize));
		return bufferSize;
	}
	//@别名 取数据()
	Status GetData(__out BYTE* buffer, 
                __in UINT bufferSize, 
                __out UINT* sizeFilled) 
	{
		return SetStatus(DllExports::GdipGetRegionData(nativeRegion, buffer, 
													   bufferSize, sizeFilled));
	}
	//@别名 是否可见()
	BOOL IsVisible(__in const RectF& rect, 
                  __in const GPGraphics* g) ;
	//@别名 是否可见()
	BOOL IsVisible(__in const Point& point, 
					  __in const GPGraphics* g) ;
	//@别名 是否可见()
	BOOL IsVisible(__in const Rect& rect, 
					  __in const GPGraphics* g) ;
	//@别名 取扫描数()
	UINT GetRegionScansCount(__in const GPMatrix* matrix) ;
	//@别名 取扫描矩形()
	Status GetRegionScans(
    __in const GPMatrix* matrix,
    __out RectF* rects,
    __in_out INT* count) ;
	//@别名 取扫描矩形()
	Status GetRegionScans(
		__in const GPMatrix* matrix,
		__out Rect* rects,
		__in_out INT* count) ;

};
//@分组}
//@分组{  字体操作
//@别名 GP字体集类
class GPFontCollection : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpFontCollection *nativeFontCollection;
	public:
	GPFontCollection(){
		nativeFontCollection = nullptr;
	}
	~GPFontCollection(){
		nativeFontCollection = nullptr;
	}
	//@隐藏}
	//@别名 取指针()
	Gdiplus::GpFontCollection* GetPtr(){
		return nativeFontCollection;
	}
	//@别名 取字体族数()
	inline INT GetFamilyCount() 
	{
		INT numFound = 0;
		lastResult = DllExports::GdipGetFontCollectionFamilyCount(
								 nativeFontCollection, &numFound);
		return numFound;
	}
	//@别名 取字体族列表(字体族数,返回字体族列表,返回字体族列表数)
	Status GetFamilies(__in INT numSought,__out GPFontFamily * gpfamilies,__out INT * numFound); 
};
//@别名 GP系统字体集类
class GPInstalledFontCollection : public GPFontCollection{
	
	inline
	GPInstalledFontCollection()
	{
		nativeFontCollection = NULL;
		lastResult = DllExports::GdipNewInstalledFontCollection(&nativeFontCollection);
	}
	inline
	~GPInstalledFontCollection()
	{
	}
};
//@别名 GP私有字体集类
class GPPrivateFontCollection : public GPFontCollection{
	//@隐藏{
	inline
	GPPrivateFontCollection()
	{
		nativeFontCollection = NULL;
		lastResult = DllExports::GdipNewPrivateFontCollection(&nativeFontCollection);
	}
	inline
	~GPPrivateFontCollection()
	{
		Destory();
	}
	//@隐藏}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory() {
		if(nativeFontCollection)  
			Gdiplus::DllExports::GdipDeletePrivateFontCollection(&nativeFontCollection);
		nativeFontCollection = nullptr;
	}
	//@别名 添加字体文件()
	inline Status
	AddFontFile(__in const WCHAR* filename)
	{
		return SetStatus(DllExports::GdipPrivateAddFontFile(nativeFontCollection, filename));
	}
	//@别名 添加字体字节集()
	inline Status
	AddMemoryFont(__in const CXBytes& memory)
	{
		return SetStatus(DllExports::GdipPrivateAddMemoryFont(
			nativeFontCollection,
			(BYTE*)memory.getPtr(),
			memory.getSize()));
	}
};
//@别名 GP字体族类
class GPFontFamily {
	protected:
		Gdiplus::Status lastResult;
	public:
		Gdiplus::GpFontFamily *nativeFamily;
	//@隐藏{
	GPFontFamily(){
		nativeFamily = nullptr;
	}
	inline ~GPFontFamily()
	{
		Destory();
	}
	//@隐藏}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory() {
		if(nativeFamily)  
			Gdiplus::DllExports::GdipDeleteFontFamily(nativeFamily);
		nativeFamily = nullptr;
	}
	//@别名 创建自名称() 
	bool CreateFromName(
		__in const WCHAR*          name,
		__in const GPFontCollection* fontCollection = nullptr
	)
	{
		nativeFamily = NULL;
		lastResult = DllExports::GdipCreateFontFamilyFromName(
			name,
			fontCollection ? fontCollection->nativeFontCollection : NULL,
			&nativeFamily
		);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自通用无衬线()
	bool GenericSansSerif() 
	{
		SetStatus(DllExports::GdipGetGenericFontFamilySansSerif(&nativeFamily));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自通用衬线()
	bool GenericSerif() 
	{
		SetStatus(DllExports::GdipGetGenericFontFamilySerif(&nativeFamily));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自通用等宽()
	bool GenericMonospace()
	{
		SetStatus(DllExports::GdipGetGenericFontFamilyMonospace(&nativeFamily));
		return lastResult == Gdiplus::Ok;
	} 
	//@别名 克隆()
	BOOL Clone(GPFontFamily &hclonedFamily) 
	{
		GpFontFamily * clonedFamily = NULL;
		hclonedFamily.Destory();
		SetStatus(DllExports::GdipCloneFontFamily (nativeFamily, &clonedFamily));
		hclonedFamily.nativeFamily = clonedFamily;
		hclonedFamily.lastResult = lastResult;
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取名称()
	inline Status 
	GetFamilyName(
		__out LPWSTR    name,
		__in LANGID                           language
	) 
	{
		return SetStatus(DllExports::GdipGetFamilyName(nativeFamily, 
													   name, 
													   language));
	}
	//@别名 是否风格可用()
	inline BOOL 
	IsStyleAvailable(__in INT style) 
	{
		BOOL    StyleAvailable;
		Status  status;

		status = SetStatus(DllExports::GdipIsStyleAvailable(nativeFamily, style, &StyleAvailable));

		if (status != Ok)
			StyleAvailable = FALSE;

		return StyleAvailable;
	}
	//@别名 取EM高度()
	inline UINT16 
	GetEmHeight(__in INT style) 
	{
		UINT16  EmHeight;

		SetStatus(DllExports::GdipGetEmHeight(nativeFamily, style, &EmHeight));

		return EmHeight;
	}
	//@别名 取上区高度()
	inline UINT16 
	GetCellAscent(__in INT style) 
	{
		UINT16  CellAscent;

		SetStatus(DllExports::GdipGetCellAscent(nativeFamily, style, &CellAscent));

		return CellAscent;
	}
	//@别名 取下区高度()
	inline UINT16 
	GetCellDescent(__in INT style) 
	{
		UINT16  CellDescent;

		SetStatus(DllExports::GdipGetCellDescent(nativeFamily, style, &CellDescent));

		return CellDescent;
	}
	//@别名 取行间距()
	inline UINT16 
	GetLineSpacing(__in INT style) 
	{
		UINT16  LineSpacing;

		SetStatus(DllExports::GdipGetLineSpacing(nativeFamily, style, &LineSpacing));

		return LineSpacing;

	}
	//@隐藏{
	inline Status 
	GetLastStatus() 
	{
		Status lastStatus = lastResult;
		lastResult = Ok;

		return lastStatus;
	}

	inline Status
	SetStatus(Status status)  
	{
		if (status != Ok)
			return (lastResult = status);
		else
			return status;
	}
	//@隐藏}
};
//@别名 GP字体类
class GPFont : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpFont *hFont;
	public:
	GPFont(){
		hFont = nullptr;
	}
	~GPFont(){
		Destory();
	}
	//@隐藏}
	//@别名 取指针()
	Gdiplus::GpFont* GetPtr(){
		return hFont;
	}
	//@别名 置指针()
	VOID SetNativeFont(GpFont *Font)
	{
		hFont = Font;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(hFont) Gdiplus::DllExports::GdipDeleteFont(hFont);
		hFont = nullptr;
	}
	//@别名 创建自场景句柄(场景句柄)
	bool CreateFontFromDC(HDC hdc){
		lastResult = Gdiplus::DllExports::GdipCreateFontFromDC(hdc, &hFont);
		return lastResult ==  Gdiplus::Ok;
	}
	//@别名 创建自名称(字体名称,字体大小,字体风格,单位,GP字体集)
	bool CreateFontFromName(const WCHAR *familyName,float emSize,FontStyle style = FontStyleRegular,Unit unit = UnitPixel,const GPFontCollection& fontCollection = GPFontCollection()){
		Gdiplus::GpFontFamily *nativeFamily = NULL;
		lastResult = Gdiplus::DllExports::GdipCreateFontFamilyFromName(familyName, fontCollection.nativeFontCollection, &nativeFamily);
		if (lastResult != Gdiplus::Ok){
			lastResult = Gdiplus::DllExports::GdipGetGenericFontFamilySerif(&nativeFamily);
			if (lastResult != Gdiplus::Ok) return FALSE;
		}
		lastResult = Gdiplus::DllExports::GdipCreateFont(nativeFamily,emSize,style,(Gdiplus::Unit)unit,&hFont);
		if (lastResult != Gdiplus::Ok){
			lastResult = Gdiplus::DllExports::GdipGetGenericFontFamilySerif(&nativeFamily);
			if (lastResult != Gdiplus::Ok) return FALSE;
			lastResult = Gdiplus::DllExports::GdipCreateFont(nativeFamily,(Gdiplus::REAL)emSize,style,(Gdiplus::Unit)unit,&hFont);
		}
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自默认字体()
	bool CreateFontDefault(){
		HFONT Font = (HFONT)::GetStockObject (DEFAULT_GUI_FONT);
		LOGFONTW logFont;
		if(!::GetObjectW(Font, sizeof(LOGFONTW), &logFont)){return FALSE;}
		HDC hdc = ::GetDC(NULL);
		lastResult =  Gdiplus::DllExports::GdipCreateFontFromLogfontW(hdc, &logFont, &hFont);
		::ReleaseDC(NULL,hdc);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自字体句柄()
	bool CreateFont(__in HDC hdc,
           __in const HFONT hfont)
	{
		if (hfont)
		{
			LOGFONTA lf;

			if(GetObjectA(hfont, sizeof(LOGFONTA), &lf))
				lastResult = DllExports::GdipCreateFontFromLogfontA(hdc, &lf, &hFont);
			else
				lastResult = DllExports::GdipCreateFontFromDC(hdc, &hFont);
		}
		else
		{
			lastResult = DllExports::GdipCreateFontFromDC(hdc, &hFont);
		}
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自逻辑字体W()
	BOOL CreateLogfontW(__in HDC hdc,
           __in const LOGFONTW* logfont)
	{
		if (logfont)
		{
			lastResult = DllExports::GdipCreateFontFromLogfontW(hdc, logfont, &hFont);
		}
		else
		{
			lastResult = DllExports::GdipCreateFontFromDC(hdc, &hFont);
		}
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自字体族()
	BOOL CreateFontFamily(
     __in const GPFontFamily * family,
     __in REAL         emSize,
     __in INT          style,
     __in Unit         unit
	)
	{
		lastResult = DllExports::GdipCreateFont(family ? family->nativeFamily : NULL,
						emSize,
						style,
						unit,
						&hFont);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取字体句柄()
	HFONT GetHFONT(GPGraphics *g);
	//@别名 取逻辑字体()
	Status GetLogFontW(__in const GPGraphics *g,
                  __out LOGFONTW *logfontW) ;
	//@别名 是否可用()
	inline BOOL
	IsAvailable() 
	{
		return (hFont ? TRUE : FALSE);
	}
	//@别名 取字体族()
	inline Status
	GetFamily(__out GPFontFamily *family) 
	{
		if (family == NULL)
		{
			return SetStatus(InvalidParameter);
		}

		Status status = DllExports::GdipGetFamily(hFont, &(family->nativeFamily));
		family->SetStatus(status);

		return SetStatus(status);
	}
	//@别名 取字体风格()
	inline INT
	GetStyle() 
	{
		INT style;

		SetStatus(DllExports::GdipGetFontStyle(hFont, &style));

		return style;
	}
	//@别名 取尺寸()
	inline REAL
	GetSize() 
	{
		REAL size;
		SetStatus(DllExports::GdipGetFontSize(hFont, &size));
		return size;
	}
	//@别名 取单位()
	inline Unit
	GetUnit() 
	{
		Unit unit;
		SetStatus(DllExports::GdipGetFontUnit(hFont, &unit));
		return unit;
	}
	//@别名 取高度()
	REAL GetHeight(__in GPGraphics *pgraphics) ;
	//@别名 取高度自DPI()
	REAL GetHeightDpi(__in REAL dpi) 
	{
		REAL height;
		SetStatus(DllExports::GdipGetFontHeightGivenDPI(hFont, dpi, &height));
		return height;
	}
};
//@别名 GP文本格式类
class GPStringFormat : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpStringFormat *hStringFormat;
	mutable Status  lastError;
	public:
	GPStringFormat(){
		hStringFormat = nullptr;
	}
	~GPStringFormat(){
		Destory();
	}
	
	GPStringFormat(GpStringFormat * clonedStringFormat, Status status)
    {
        lastResult = status;
        hStringFormat = clonedStringFormat;

    }
	//@隐藏}
	//@别名 创建()
	bool Create(
        __in INT     formatFlags = 0,
        __in LANGID  language = LANG_NEUTRAL
    )
    {
        hStringFormat = NULL;
        SetStatus( DllExports::GdipCreateStringFormat(formatFlags,language, &hStringFormat));
		return lastResult == Ok;
    }
	//@别名 创建自通用默认()
	bool GenericDefault()
	{
		SetStatus(DllExports::GdipStringFormatGetGenericDefault(&hStringFormat));
		return lastResult == Ok;
	}
	//@别名 创建自通用印刷()
	bool GenericTypographic()
	{
		SetStatus(DllExports::GdipStringFormatGetGenericTypographic(&hStringFormat));
		return lastResult == Ok;
	}
	//@别名 克隆()
    GPStringFormat *Clone() 
    {
        GpStringFormat *clonedStringFormat = NULL;
        lastResult = DllExports::GdipCloneStringFormat(
            hStringFormat,
            &clonedStringFormat
        );
        if (lastResult == Ok)
            return new GPStringFormat(clonedStringFormat, lastResult);
        else
            return NULL;
    }
	//@别名 取句柄()
	Gdiplus::GpStringFormat* GetPtr(){
		return hStringFormat;
	}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(hStringFormat) Gdiplus::DllExports::GdipDeleteStringFormat(hStringFormat);
		hStringFormat = nullptr;
	}
	//@别名 置格式标志()
	Status SetFormatFlags(__in INT flags)
    {
        return SetStatus(DllExports::GdipSetStringFormatFlags(
            hStringFormat,
            flags
        ));
    }
	//@别名 取格式标志()
    INT GetFormatFlags() 
    {
        INT flags;
        SetStatus(DllExports::GdipGetStringFormatFlags(hStringFormat, &flags));
        return flags;
    }
	//@别名 置对齐()
    Status SetAlignment(__in StringAlignment align)
    {
        return SetStatus(DllExports::GdipSetStringFormatAlign(
            hStringFormat,
            align
        ));
    }
	//@别名 取对齐()
    StringAlignment GetAlignment() 
    {
        StringAlignment alignment;
        SetStatus(DllExports::GdipGetStringFormatAlign(
            hStringFormat,
            &alignment
        ));
        return alignment;
    }
	//@别名 置行对齐()
    Status SetLineAlignment(__in StringAlignment align)
    {
        return SetStatus(DllExports::GdipSetStringFormatLineAlign(
            hStringFormat,
            align
        ));
    }
	//@别名 取行对齐()
    StringAlignment GetLineAlignment() 
    {
        StringAlignment alignment;
        SetStatus(DllExports::GdipGetStringFormatLineAlign(
            hStringFormat,
            &alignment
        ));
        return alignment;
    }
	//@别名 置热键前缀()
    Status SetHotkeyPrefix(__in HotkeyPrefix hotkeyPrefix)
    {
        return SetStatus(DllExports::GdipSetStringFormatHotkeyPrefix(
            hStringFormat,
            (INT)hotkeyPrefix
        ));
    }
	//@别名 取热键前缀()
    HotkeyPrefix GetHotkeyPrefix() 
    {
        HotkeyPrefix hotkeyPrefix;
        SetStatus(DllExports::GdipGetStringFormatHotkeyPrefix(
            hStringFormat,
            (INT*)&hotkeyPrefix
        ));
        return hotkeyPrefix;
    }
	//@别名 置制表位()
    Status SetTabStops(
        __in REAL    firstTabOffset,
        __in INT     count,
        __in const REAL    *tabStops
    )
    {
        return SetStatus(DllExports::GdipSetStringFormatTabStops(
            hStringFormat,
            firstTabOffset,
            count,
            tabStops
        ));
    }
	//@别名 取制表位数()
    INT GetTabStopCount() 
    {
        INT count;
        SetStatus(DllExports::GdipGetStringFormatTabStopCount(hStringFormat, &count));
        return count;
    }
	//@别名 取制表位()
    Status GetTabStops(
        __in INT     count,
        __out REAL   *firstTabOffset,
        __out REAL   *tabStops
    ) 
    {
        return SetStatus(DllExports::GdipGetStringFormatTabStops(
            hStringFormat,
            count,
            firstTabOffset,
            tabStops
        ));
    }
	//@别名 置数字替换()
    Status SetDigitSubstitution(
        __in LANGID                language,
        __in StringDigitSubstitute substitute
    )
    {
        return SetStatus(DllExports::GdipSetStringFormatDigitSubstitution(
            hStringFormat,
            language,
            substitute
        ));
    }
	//@别名 取数字替换语言()
    LANGID GetDigitSubstitutionLanguage() 
    {
        LANGID language;
        SetStatus(DllExports::GdipGetStringFormatDigitSubstitution(
            hStringFormat,
            &language,
            NULL
        ));
        return language;
    }
	//@别名 取数字替换方法()
    StringDigitSubstitute GetDigitSubstitutionMethod() 
    {
        StringDigitSubstitute substitute;
        SetStatus(DllExports::GdipGetStringFormatDigitSubstitution(
            hStringFormat,
            NULL,
            &substitute
        ));
        return substitute;
    }
	//@别名 置修整()
    Status SetTrimming(__in StringTrimming trimming)
    {
        return SetStatus(DllExports::GdipSetStringFormatTrimming(
            hStringFormat,
            trimming
        ));
    }
	//@别名 取修整()
    StringTrimming GetTrimming() 
    {
        StringTrimming trimming;
        SetStatus(DllExports::GdipGetStringFormatTrimming(
            hStringFormat,
            &trimming
        ));
        return trimming;
    }
	//@别名 置测量字符范围()
    Status SetMeasurableCharacterRanges(
        __in INT                  rangeCount,
        __in const CharacterRange *ranges
    )
    {
        return SetStatus(DllExports::GdipSetStringFormatMeasurableCharacterRanges(
            hStringFormat,
            rangeCount,
            ranges
        ));
    }
	//@别名 取测量字符范围数()
    INT GetMeasurableCharacterRangeCount()
    {
        INT count;
        SetStatus(DllExports::GdipGetStringFormatMeasurableCharacterRangeCount(
            hStringFormat,
            &count
        ));
        return count;
    }

};
//@分组}

//@分组{  画刷操作
//@别名 GP画刷类
class GPBrush : public GPbase {
	public:
		//@隐藏{
		Gdiplus::GpBrush* hBrush ;
	public:
		GPBrush(){ hBrush = nullptr;}
		~GPBrush(){ Destory();}
		//@别名 置指针()
		VOID SetNativeBrush(Gdiplus::GpBrush * nativeBrush){
			this->hBrush = nativeBrush;
		}		
		//@隐藏}

		//@别名 取指针()
		Gdiplus::GpBrush* GetPtr(){
			return hBrush;
		}
		//@备注 可以手动销毁, 但超出作用域也会自动销毁
		//@别名 销毁()
		void Destory() {
			if(hBrush)  
				Gdiplus::DllExports::GdipDeleteBrush(hBrush);
			hBrush = nullptr;
		}
		//@备注 获取此画刷的类型
		//@别名 取类型()
		Gdiplus::BrushType GetType(){
			Gdiplus::BrushType type = static_cast<Gdiplus::BrushType>(-1);
			SetStatus(Gdiplus::DllExports::GdipGetBrushType(hBrush, &type));
			return type;
		}
		//@备注 创建一个新的 GP画刷类 对象，该对象是本对象的副本
		//@别名 克隆(新画刷)
		bool Clone(GPBrush& Brush){
			Brush.Destory();
			Gdiplus::GpBrush* clone;
			SetStatus(Gdiplus::DllExports::GdipCloneBrush(hBrush, &clone));
			Brush.hBrush = clone;
			Brush.lastResult = lastResult;
			return lastResult == Gdiplus::Ok;
		}
};
//@别名 GP纯色画刷类
class GPSolidBrush : public GPBrush {
	public:
	//@别名 创建(颜色)
	bool CreateSolidFill(int color){
		this->Destory();
		Gdiplus::GpSolidFill *brush = nullptr;
		lastResult = Gdiplus::DllExports::GdipCreateSolidFill(color, &brush);
		SetNativeBrush(brush);
		return lastResult == Gdiplus::Ok;
	}
		//@别名 创建(颜色)
	bool CreateSolidFill(Color& color){
		this->Destory();
		Gdiplus::GpSolidFill *brush = nullptr;
		lastResult = Gdiplus::DllExports::GdipCreateSolidFill(color.GetValue(), &brush);
		SetNativeBrush(brush);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 取颜色()
	Gdiplus::ARGB GetColor(){
		Gdiplus::ARGB argb;
		SetStatus(Gdiplus::DllExports::GdipGetSolidFillColor((Gdiplus::GpSolidFill*)hBrush, &argb));
		return argb;
	}
	//@别名 置颜色(ARGB颜色)
	bool SetColor(DWORD argb){
		SetStatus(Gdiplus::DllExports::GdipSetSolidFillColor((Gdiplus::GpSolidFill*)hBrush, argb));
		return lastResult == Gdiplus::Ok;
	}
	//@别名 置颜色(颜色)
	bool SetColor(Color& color){
		SetStatus(Gdiplus::DllExports::GdipSetSolidFillColor((Gdiplus::GpSolidFill*)hBrush, color.GetValue()));
		return lastResult == Gdiplus::Ok;
	}
};
//@别名 GP纹理画刷类
class GPTextureBrush : public GPBrush {
	public:
	//@别名 创建(图像,环绕模式)
	//@备注 基于图像和环绕模式创建 纹理画刷 对象。 画笔的大小默认为图像的大小，因此画笔使用整个图像。
	bool CreateTexture(GPImage& Image,WrapMode Mode);
	//@别名 创建自矩形(图像,矩形,环绕模式)
	//@备注 基于图像和矩形创建 纹理画刷 对象。 画笔的大小默认为矩形的宽度和高度，因此画笔使用整个矩形。
	bool CreateTextureRectF(GPImage& Image,RectF& rcf, WrapMode Mode);
	//@别名 创建自图像属性(图像,矩形,图像属性)
	//@备注 基于图像、矩形和图像属性创建 纹理画刷 对象。
	//@参数 GP图像类（包括GP位图类）
	//@参数 矩形指定了画笔的大小，如果矩形大小超出图像范围将会创建失败。
	//@参数 图像属性指定了一些应用效果。
	bool CreateTextureImageAttributes(GPImage& Image,RectF& rcf, GPImageAttributes& ImageAttributes);
	//@别名 置矩阵(矩阵)
	bool SetTransform(GPMatrix& Matrix){
		return SetStatus(Gdiplus::DllExports::GdipSetTextureTransform((Gdiplus::GpTexture*)hBrush, Matrix.hMatrix)) == Gdiplus::Ok;
	}
	//@别名 取矩阵(矩阵)
	bool GetTransform(__out GPMatrix& Matrix){
		return SetStatus(Gdiplus::DllExports::GdipGetTextureTransform((Gdiplus::GpTexture*)hBrush, Matrix.hMatrix)) == Gdiplus::Ok;
	}
	//@别名 矩阵重置()
	bool ResetTransform(){
		return SetStatus(Gdiplus::DllExports::GdipResetTextureTransform((Gdiplus::GpTexture*)hBrush)) == Gdiplus::Ok;
	}
	//@别名 矩阵相乘(矩阵,矩阵顺序)
	bool MultiplyTransform(GPMatrix& Matrix,MatrixOrder Order){
		return SetStatus(Gdiplus::DllExports::GdipMultiplyTextureTransform((Gdiplus::GpTexture*)hBrush, Matrix.hMatrix, (Gdiplus::MatrixOrder)Order)) == Gdiplus::Ok;
	}
	//@别名 矩阵平移(水平偏移量,垂直偏移量,矩阵顺序)
	bool TranslateTransform(float x,float y, MatrixOrder Order){
		return SetStatus(Gdiplus::DllExports::GdipTranslateTextureTransform((Gdiplus::GpTexture*)hBrush, x, y, (Gdiplus::MatrixOrder)Order)) == Gdiplus::Ok;
	}
	//@别名 矩阵缩放(水平偏移量,垂直偏移量,矩阵顺序)
	bool ScaleTransform(float x,float y, MatrixOrder Order){
		return SetStatus(Gdiplus::DllExports::GdipScaleTextureTransform((Gdiplus::GpTexture*)hBrush, x, y, (Gdiplus::MatrixOrder)Order)) == Gdiplus::Ok;
	}
	//@别名 矩阵旋转(角度,矩阵顺序)
	bool RotateTransform(float Rotate,MatrixOrder Order){
		return SetStatus(Gdiplus::DllExports::GdipRotateTextureTransform((Gdiplus::GpTexture*)hBrush, Rotate, (Gdiplus::MatrixOrder)Order)) == Gdiplus::Ok;
	}
	//@别名 置环绕模式(环绕模式)
	bool SetWrapMode(WrapMode Mode){
		return SetStatus(Gdiplus::DllExports::GdipSetTextureWrapMode((Gdiplus::GpTexture*)hBrush, (Gdiplus::WrapMode)Mode)) == Gdiplus::Ok;
	}
	//@别名 取环绕模式()
	WrapMode GetWrapMode(){
		Gdiplus::WrapMode wrapMode;
		SetStatus(Gdiplus::DllExports::GdipGetTextureWrapMode((Gdiplus::GpTexture*)hBrush, &wrapMode));
		return wrapMode;
	}
	//@别名 取图像(图像)
	bool GetImage(__out GPImage& Image){
		Gdiplus::GpImage* image;
		SetStatus(Gdiplus::DllExports::GdipGetTextureImage((Gdiplus::GpTexture*)hBrush, &image));
		Image.hImage = image;
		return lastResult == Gdiplus::Ok;
	}
};
//@别名 GP阴影画刷类
class GPHatchBrush : public GPBrush {
	public:
	//@别名 创建()
	VOID CreateHatchBrush(__in HatchStyle hatchStyle, 
               __in const Color& foreColor,
               __in const Color& backColor = Color())
    {
        GpHatch *brush = NULL;

        lastResult = DllExports::GdipCreateHatchBrush(hatchStyle, 
                                                      foreColor.GetValue(), 
                                                      backColor.GetValue(),
                                                      &brush);
        SetNativeBrush(brush);
    }
	//@别名 取阴影风格()
    HatchStyle GetHatchStyle() 
    {
        HatchStyle hatchStyle;

        SetStatus(DllExports::GdipGetHatchStyle((GpHatch*)hBrush, 
                                                &hatchStyle));

        return hatchStyle;
    }
	//@别名 取前景色()
    Status GetForegroundColor(__out Color* color) 
    {
        ARGB argb;

        if (color == NULL) 
        {
            return SetStatus(InvalidParameter);
        }
        
        Status status = SetStatus(DllExports::GdipGetHatchForegroundColor(
                                                        (GpHatch*)hBrush, 
                                                        &argb));

        color->SetValue(argb);

        return status;
    }
	//@别名 取背景色()
    Status GetBackgroundColor(__out Color *color) 
    {
        ARGB argb;
        
        if (color == NULL) 
        {
            return SetStatus(InvalidParameter);
        }

        Status status = SetStatus(DllExports::GdipGetHatchBackgroundColor(
                                                        (GpHatch*)hBrush,
                                                        &argb));

        color->SetValue(argb);
        
        return status;
    }
};
//@别名 GP线性渐变画刷类
class GPLinearGradientBrush : public GPBrush {
	public:
	//@别名 创建()
	VOID CreateLineBrush(__in const PointF& point1,
                        __in const PointF& point2,
                        __in const Color& color1,
                        __in const Color& color2)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrush(&point1,
                                                     &point2,
                                                     color1.GetValue(),
                                                     color2.GetValue(),
                                                     WrapModeTile,
                                                     &brush);

        SetNativeBrush(brush);
    }
	//@别名 创建I()
    VOID CreateLineBrushI(__in const Point& point1,
                        __in const Point& point2,
                        __in const Color& color1,
                        __in const Color& color2)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrushI(&point1,
                                                      &point2,
                                                      color1.GetValue(),
                                                      color2.GetValue(),
                                                      WrapModeTile,
                                                      &brush);

        SetNativeBrush(brush);
    }
	//@别名 创建自矩形()
    VOID CreateLineBrushFromRect(__in const RectF& rect,
                        __in const Color& color1,
                        __in const Color& color2,
                        __in LinearGradientMode mode)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrushFromRect(&rect,
                                                             color1.GetValue(),
                                                             color2.GetValue(),
                                                             mode,
                                                             WrapModeTile,
                                                             &brush);

        SetNativeBrush(brush);
    }
	//@别名 创建自矩形I()
    VOID CreateLineBrushFromRectI(__in const Rect& rect,
                        __in const Color& color1,
                        __in const Color& color2,
                        __in LinearGradientMode mode)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrushFromRectI(&rect,
                                                              color1.GetValue(),
                                                              color2.GetValue(),
                                                              mode,
                                                              WrapModeTile,
                                                              &brush);

        SetNativeBrush(brush);
    }
	//@别名 创建自矩形角度()
    VOID CreateLineBrushFromRectWithAngle(__in const RectF& rect,
                        __in const Color& color1,
                        __in const Color& color2,
                        __in REAL angle,
                        __in BOOL isAngleScalable = FALSE)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrushFromRectWithAngle(&rect,
                                                                      color1.GetValue(),
                                                                      color2.GetValue(),
                                                                      angle,
                                                                      isAngleScalable,
                                                                      WrapModeTile,
                                                                      &brush);

        SetNativeBrush(brush);
    }
	//@别名 创建自矩形角度I()
    VOID CreateLineBrushFromRectWithAngleI(__in const Rect& rect,
                        __in const Color& color1,
                        __in const Color& color2,
                        __in REAL angle,
                        __in BOOL isAngleScalable = FALSE)
    {
        GpLineGradient *brush = NULL;

        lastResult = DllExports::GdipCreateLineBrushFromRectWithAngleI(&rect,
                                                                       color1.GetValue(),
                                                                       color2.GetValue(),
                                                                       angle,
                                                                       isAngleScalable,
                                                                       WrapModeTile,
                                                                       &brush);

        SetNativeBrush(brush);
    }
	//@别名 置线性颜色()
    Status SetLinearColors(__in const Color& color1, 
                           __in const Color& color2)
    {
        return SetStatus(DllExports::GdipSetLineColors((GpLineGradient*)hBrush,
                                                       color1.GetValue(),
                                                       color2.GetValue()));
    }
	//@别名 取线性颜色()
    Status GetLinearColors(__out Color* colors) 
    {
        ARGB argb[2];

        if (colors == NULL) 
        {
            return SetStatus(InvalidParameter);
        }
        
        Status status = SetStatus(DllExports::GdipGetLineColors((GpLineGradient*) hBrush, argb));

        if (status == Ok)
        {
            // use bitwise copy operator for Color copy
            colors[0] = Color(argb[0]);
            colors[1] = Color(argb[1]);
        }

        return status;
    }
	//@别名 取矩形()
    Status GetRectangle(__out RectF* rect) 
    {
        return SetStatus(DllExports::GdipGetLineRect((GpLineGradient*)hBrush, rect));
    }
	//@别名 取矩形I()
    Status GetRectangleI(__out Rect* rect) 
    {
        return SetStatus(DllExports::GdipGetLineRectI((GpLineGradient*)hBrush, rect));
    }
	//@别名 置伽玛校正()
    Status SetGammaCorrection(__in BOOL useGammaCorrection)
    {
        return SetStatus(DllExports::GdipSetLineGammaCorrection((GpLineGradient*)hBrush,
                    useGammaCorrection));
    }
    //@别名 取伽玛校正()
    BOOL GetGammaCorrection() 
    {
        BOOL useGammaCorrection;

        SetStatus(DllExports::GdipGetLineGammaCorrection((GpLineGradient*)hBrush,
                    &useGammaCorrection));

        return useGammaCorrection;
    }
	//@别名 取混合数()
    INT GetBlendCount() 
    {
        INT count = 0;

        SetStatus(DllExports::GdipGetLineBlendCount((GpLineGradient*)
                                                    hBrush,
                                                    &count));

        return count;
    }
	//@别名 置混合()
    Status SetBlend(__in const REAL* blendFactors, 
                    __in const REAL* blendPositions,
                    __in INT count)
    {
        return SetStatus(DllExports::GdipSetLineBlend((GpLineGradient*)
                                                      hBrush,
                                                      blendFactors,
                                                      blendPositions,
                                                      count));
    }
	//@别名 取混合()
    Status GetBlend(__out REAL* blendFactors, 
                    __out REAL* blendPositions, 
                    __in INT count)  
    {
        return SetStatus(DllExports::GdipGetLineBlend((GpLineGradient*)hBrush,
                                                      blendFactors,
                                                      blendPositions,
                                                      count));
    }
	//@别名 取插值颜色数()
    INT GetInterpolationColorCount() 
    {
        INT count = 0;

        SetStatus(DllExports::GdipGetLinePresetBlendCount((GpLineGradient*)
                                                          hBrush,
                                                          &count));

        return count;
    }
	//@别名 置插值颜色()
    Status SetInterpolationColors(__in const Color* presetColors,
                                  __in const REAL* blendPositions, 
                                  __in INT count)
    {
        if ((count <= 0) || !presetColors)
            return SetStatus(InvalidParameter);
         
        ARGB *argbs = (ARGB*) new BYTE[count*sizeof(ARGB)];
        
        if (argbs)
        {
            for (INT i = 0; i < count; i++)
            {
                argbs[i] = presetColors[i].GetValue();
            }

            Status status = SetStatus(DllExports::GdipSetLinePresetBlend(
                                                                        (GpLineGradient*) hBrush,
                                                                        argbs,
                                                                        blendPositions,
                                                                        count));
            delete [] argbs;
            return status;
        }
        else
        {
            return SetStatus(OutOfMemory);
        }
    }
	//@别名 取插值颜色()
    Status GetInterpolationColors(__out Color* presetColors, 
                                  __out REAL* blendPositions, 
                                  __in INT count)  
    {
        if ((count <= 0) || !presetColors)
            return SetStatus(InvalidParameter);

        ARGB* argbs = (ARGB*) new BYTE[count*sizeof(ARGB)];
        
        if (!argbs)
        {
            return SetStatus(OutOfMemory);
        }

        Status status = SetStatus(DllExports::GdipGetLinePresetBlend((GpLineGradient*)hBrush,
                                                                     argbs,
                                                                     blendPositions,
                                                                     count));
        if (status == Ok) 
        {
            for (INT i = 0; i < count; i++)
            { 
                presetColors[i] = Color(argbs[i]);
            }
        }
        
        delete [] argbs;
        
        return status;
    }
	//@别名 置混合钟形()
    Status SetBlendBellShape(__in REAL focus, 
                             __in REAL scale = 1.0f)
    {
        return SetStatus(DllExports::GdipSetLineSigmaBlend((GpLineGradient*)hBrush, focus, scale));
    }
	//@别名 置混合三角形()
    Status SetBlendTriangularShape(
        __in REAL focus,
        __in REAL scale = 1.0f
    )
    {
        return SetStatus(DllExports::GdipSetLineLinearBlend((GpLineGradient*)hBrush, focus, scale));
    }
	//@别名 置矩阵()
    Status SetTransform(__in const GPMatrix* matrix)
    {
        return SetStatus(DllExports::GdipSetLineTransform((GpLineGradient*)hBrush, 
                                                          matrix->hMatrix));
    }
	//@别名 取矩阵()
    Status GetTransform(__out GPMatrix *matrix) 
    {
        return SetStatus(DllExports::GdipGetLineTransform((GpLineGradient*)hBrush, 
                                                          matrix->hMatrix));
    }
	//@别名 矩阵重置()
    Status ResetTransform()
    {
        return SetStatus(DllExports::GdipResetLineTransform((GpLineGradient*)hBrush));
    }
	//@别名 矩阵相乘()
    Status MultiplyTransform(__in const GPMatrix* matrix,
                             __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipMultiplyLineTransform((GpLineGradient*)hBrush,
                                                                matrix->hMatrix,
                                                                order));
    }
	//@别名 矩阵平移()
    Status TranslateTransform(__in REAL dx, 
                              __in REAL dy,
                              __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipTranslateLineTransform((GpLineGradient*)hBrush,
                                                               dx, dy, order));
    }
	//@别名 矩阵缩放()
    Status ScaleTransform(__in REAL sx, 
                          __in REAL sy,
                          __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipScaleLineTransform((GpLineGradient*)hBrush,
                                                             sx, sy, order));
    }
	//@别名 矩阵旋转()
    Status RotateTransform(__in REAL angle, 
                           __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipRotateLineTransform((GpLineGradient*)hBrush,
                                                              angle, order));
    }
	//@别名 置环绕模式()
    Status SetWrapMode(__in WrapMode wrapMode)
    {
        return SetStatus(DllExports::GdipSetLineWrapMode((GpLineGradient*)hBrush, 
                                                         wrapMode));
    }
	//@别名 取环绕模式()
    WrapMode GetWrapMode() 
    {
        WrapMode wrapMode;

        SetStatus(DllExports::GdipGetLineWrapMode((GpLineGradient*)
                                                  hBrush, 
                                                  &wrapMode));

        return wrapMode;
    }
};
//@分组}

//@分组{  画笔操作
//@别名 GP自定义线帽类
class GPCustomLineCap : public GPbase {
	public:
	Gdiplus::GpCustomLineCap* nativeCap;
	public:
	GPCustomLineCap(){ nativeCap = nullptr;}
	~GPCustomLineCap(){ Destory();}
	//@别名 置指针()
	VOID SetNativeCap(GpCustomLineCap* hnativeCap)
    {
        this->nativeCap = hnativeCap;
    }
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory() {
		if(nativeCap)  
			Gdiplus::DllExports::GdipDeleteCustomLineCap(nativeCap);
		nativeCap = nullptr;
	}
	//@别名 创建()
	bool Create(__in const GPPath* fillPath,__in const GPPath* strokePath,__in LineCap baseCap,__in REAL baseInset) {
		this->Destory();
		lastResult = Gdiplus::DllExports::GdipCreateCustomLineCap(fillPath->nativePath, strokePath->nativePath, baseCap, baseInset, &nativeCap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 置画笔线帽()
	inline Status 
	SetStrokeCaps(
		__in LineCap startCap, 
		__in LineCap endCap)
	{
		return SetStatus(DllExports::GdipSetCustomLineCapStrokeCaps(nativeCap,
					startCap, endCap));
	}
	//@别名 取画笔线帽()
	inline Status 
	GetStrokeCaps(
		__out LineCap* startCap, 
		__out LineCap* endCap) 
	{
		return SetStatus(DllExports::GdipGetCustomLineCapStrokeCaps(nativeCap,
					 startCap, endCap));
	}
	//@别名 置画笔连线方式()
	inline Status 
	SetStrokeJoin(
		__in LineJoin lineJoin)
	{
		return SetStatus(DllExports::GdipSetCustomLineCapStrokeJoin(nativeCap, 
																	lineJoin));
	}
	//@别名 取画笔连线方式()
	inline LineJoin 
	GetStrokeJoin() 
	{
		LineJoin lineJoin;

		SetStatus(DllExports::GdipGetCustomLineCapStrokeJoin(nativeCap, 
															 &lineJoin));

		return lineJoin;
	}
	//@别名 置基线帽()
	inline Status 
	SetBaseCap(__in LineCap baseCap)
	{
		return SetStatus(DllExports::GdipSetCustomLineCapBaseCap(nativeCap, 
																 baseCap));
	}
	//@别名 取基线帽()
	inline LineCap 
	GetBaseCap() 
	{
		LineCap baseCap;
		SetStatus(DllExports::GdipGetCustomLineCapBaseCap(nativeCap, &baseCap));

		return baseCap;
	}
	//@别名 置基距离()
	inline Status 
	SetBaseInset(__in REAL inset)
	{
		return SetStatus(DllExports::GdipSetCustomLineCapBaseInset(nativeCap, 
																   inset));
	}
	//@别名 取基距离()
	inline REAL 
	GetBaseInset() 
	{
		REAL inset;
		SetStatus(DllExports::GdipGetCustomLineCapBaseInset(nativeCap, &inset));

		return inset;
	}
	//@别名 置宽比例()
	inline Status 
	SetWidthScale(__in REAL widthScale)
	{
		return SetStatus(DllExports::GdipSetCustomLineCapWidthScale(nativeCap, 
																	widthScale));
	}
	//@别名 取宽比例()
	inline REAL 
	GetWidthScale() 
	{
		REAL widthScale;
		SetStatus(DllExports::GdipGetCustomLineCapWidthScale(nativeCap, 
															 &widthScale));

		return widthScale;
	}
	//@别名 克隆()
	BOOL Clone(GPCustomLineCap &newLineCap) 
	{
		GpCustomLineCap *newNativeLineCap = NULL;
		
		SetStatus(DllExports::GdipCloneCustomLineCap(nativeCap, 
													 &newNativeLineCap));

		if (lastResult == Ok) 
		{
			newLineCap.Destory();
			newLineCap.nativeCap = newNativeLineCap;
			newLineCap.lastResult = lastResult;
			return 1;
		}

		return 0;
	}
};
//@别名 GP可调节箭头线帽类
class GPAdjustableArrowCap : public GPCustomLineCap {
	public:
	//@别名 创建可调节箭头线帽()
	VOID CreateAdjustableArrowCap(
        __in REAL height,
        __in REAL width,
        __in BOOL isFilled = TRUE
        )
    {
        GpAdjustableArrowCap* cap = NULL;

        lastResult = DllExports::GdipCreateAdjustableArrowCap(
                        height, width, isFilled, &cap);
        SetNativeCap(cap);
    }
	//@别名 置高度()
    Status SetHeight(__in REAL height)
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        return SetStatus(DllExports::GdipSetAdjustableArrowCapHeight(
                            cap, height));
    }
	//@别名 取高度()
    REAL GetHeight() 
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        REAL height;
        SetStatus(DllExports::GdipGetAdjustableArrowCapHeight(
                            cap, &height));

        return height;
    }
	//@别名 置宽度()
    Status SetWidth(__in REAL width)
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        return SetStatus(DllExports::GdipSetAdjustableArrowCapWidth(
                            cap, width));
    }
	//@别名 取宽度()
    REAL GetWidth() 
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        REAL width;
        SetStatus(DllExports::GdipGetAdjustableArrowCapWidth(
                            cap, &width));

        return width;
    }
	//@别名 置中间距离()
    Status SetMiddleInset(__in REAL middleInset)
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        return SetStatus(DllExports::GdipSetAdjustableArrowCapMiddleInset(
                            cap, middleInset));
    }
	//@别名 取中间距离()
    REAL GetMiddleInset() 
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        REAL middleInset;
        SetStatus(DllExports::GdipGetAdjustableArrowCapMiddleInset(
                            cap, &middleInset));

        return middleInset;
    }
	//@别名 置填充状态()
    Status SetFillState(__in BOOL isFilled)
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        return SetStatus(DllExports::GdipSetAdjustableArrowCapFillState(
                            cap, isFilled));
    }
	//@别名 是否填充()
    BOOL IsFilled() 
    {
        GpAdjustableArrowCap* cap = (GpAdjustableArrowCap*) nativeCap;
        BOOL isFilled;
        SetStatus(DllExports::GdipGetAdjustableArrowCapFillState(
                            cap, &isFilled));

        return isFilled;
    }
};
//@别名 GP画笔类
class GPPen : public GPbase {
	public:
		//@隐藏{
		//@别名 画笔指针
		Gdiplus::GpPen* hPen ;
	public:
		GPPen(){ hPen = nullptr;}
		~GPPen(){ Destory();}
		//@隐藏}
		//@别名 取指针()
		Gdiplus::GpPen* GetPtr(){
			return hPen;
		}
		//@备注 可以手动销毁, 但超出作用域也会自动销毁
		//@别名 销毁()
		void Destory() {
			if(hPen)  
				Gdiplus::DllExports::GdipDeletePen(hPen);
			hPen = nullptr;
		}
		//@备注 创建一个新的 GP画笔类 对象，该对象是本对象的副本
		//@别名 克隆(新画笔)
		bool Clone(GPPen& pen){
			pen.Destory();
			Gdiplus::GpPen* clone;
			SetStatus(Gdiplus::DllExports::GdipClonePen(hPen, &clone));
			pen.hPen = clone;
			pen.lastResult = lastResult;
			return lastResult == Gdiplus::Ok;
		}
		//@参数 ARGB颜色 
		//@参数 线宽度	指定此画笔宽度的实数。默认值为1.0
		//@别名 创建自颜色(ARGB颜色,宽度)
		bool CreateFromColor(int color,float width = 1.0){
			Destory();
			Gdiplus::Unit unit = Gdiplus::UnitWorld;
			lastResult = Gdiplus::DllExports::GdipCreatePen1(color,width, unit, &hPen);
			return lastResult == Gdiplus::Ok;
		}
		//@别名 创建自颜色(ARGB颜色,宽度)
		bool CreateFromColor(Color& color,float width = 1.0){
			Destory();
			Gdiplus::Unit unit = Gdiplus::UnitWorld;
			lastResult = Gdiplus::DllExports::GdipCreatePen1(color.GetValue(),width, unit, &hPen);
			return lastResult == Gdiplus::Ok;
		}
		//@备注 创建一个 GP画笔类 对象，该对象使用画刷的属性和一个实数来设置此 GP画笔类 对象的宽度
		//@参数 画刷 
		//@参数 线宽度	指定此画笔宽度的实数。默认值为1.0
		//@别名 创建自画刷(画刷,宽度)
		bool CreateFromBrush(GPBrush& brush,float width = 1.0){
			Destory();
			Gdiplus::Unit unit = Gdiplus::UnitWorld;
			hPen = nullptr;
			lastResult = Gdiplus::DllExports::GdipCreatePen2(brush.hBrush,width, unit, &hPen);
			return lastResult == Gdiplus::Ok;
		}
		//@备注 设置此 GP画笔类 对象的宽度
		//@参数 线宽度	指定此画笔宽度的实数。
		//@别名 置宽度(线宽度)
		bool SetWidth(float width ){
			return SetStatus(Gdiplus::DllExports::GdipSetPenWidth(hPen, (Gdiplus::REAL)width)) == Gdiplus::Ok;
		}
		//@别名 取宽度()
		float GetWidth(){
			Gdiplus::REAL width;
			SetStatus(Gdiplus::DllExports::GdipGetPenWidth(hPen, &width));
			return width;
		}
		//@别名 置线帽(起点帽,终点帽,虚线帽)
		bool SetLineCap(LineCap startCap, LineCap endCap, DashCap dashCap){
			return SetStatus(Gdiplus::DllExports::GdipSetPenLineCap197819(hPen, startCap, (Gdiplus::LineCap)endCap, (Gdiplus::DashCap)dashCap)) == Gdiplus::Ok;
		}
		//@别名 置起点线帽(起点帽)
		bool SetStartCap(LineCap startCap){
			return SetStatus(Gdiplus::DllExports::GdipSetPenStartCap(hPen, startCap)) == Gdiplus::Ok ;
		}
		//@别名 置终点线帽(起点帽)
		bool SetEndCap(LineCap endCap){
			return SetStatus(Gdiplus::DllExports::GdipSetPenEndCap(hPen, endCap)) == Gdiplus::Ok ;
		}
		//@别名 置虚线帽(虚线帽)
		bool SetDashCap(DashCap dashCap){
			return SetStatus(Gdiplus::DllExports::GdipSetPenDashCap197819(hPen, dashCap)) == Gdiplus::Ok ;
		}
		
		//@别名 置颜色(ARGB颜色)
		bool SetColor(int color){
			return SetStatus(Gdiplus::DllExports::GdipSetPenColor(hPen, color)) == Gdiplus::Ok ;
		}
		//@别名 置颜色(颜色)
		bool SetColor(__in const Color& color)
		{
			return SetStatus(DllExports::GdipSetPenColor(hPen,color.GetValue())) == Gdiplus::Ok;
		}
		//@别名 置连线方式()
		Status SetLineJoin(__in LineJoin lineJoin)
		{
			return SetStatus(DllExports::GdipSetPenLineJoin(hPen, lineJoin));
		}
		//@别名 取连线方式()
		LineJoin GetLineJoin() 
		{
			LineJoin lineJoin;
			
			SetStatus(DllExports::GdipGetPenLineJoin(hPen, &lineJoin));
			
			return lineJoin;
		}
		//@别名 置自定义起点线帽()
		Status SetCustomStartCap(__in const GPCustomLineCap* customCap)
		{
			GpCustomLineCap* nativeCap = NULL;
			if(customCap)
				nativeCap = customCap->nativeCap;

			return SetStatus(DllExports::GdipSetPenCustomStartCap(hPen, 
																  nativeCap));
		}
		//@别名 取自定义起点线帽()
		Status GetCustomStartCap(__out GPCustomLineCap* customCap) 
		{
			if(!customCap)
				return SetStatus(InvalidParameter);

			return SetStatus(DllExports::GdipGetPenCustomStartCap(hPen, 
														&(customCap->nativeCap)));
		}
		//@别名 置自定义终点线帽()
		Status SetCustomEndCap(__in const GPCustomLineCap* customCap)
		{
			GpCustomLineCap* nativeCap = NULL;
			if(customCap)
				nativeCap = customCap->nativeCap;

			return SetStatus(DllExports::GdipSetPenCustomEndCap(hPen, 
																nativeCap));
		}
		//@别名 取自定义终点线帽()
		Status GetCustomEndCap(__out GPCustomLineCap* customCap) 
		{
			if(!customCap)
				return SetStatus(InvalidParameter);

			return SetStatus(DllExports::GdipGetPenCustomEndCap(hPen, 
														&(customCap->nativeCap)));
		}
		//@别名 置斜接限制()
		Status SetMiterLimit(__in REAL miterLimit)
		{
			return SetStatus(DllExports::GdipSetPenMiterLimit(hPen, 
														miterLimit));
		}
		//@别名 取斜接限制()
		REAL GetMiterLimit() 
		{
			REAL miterLimit;

			SetStatus(DllExports::GdipGetPenMiterLimit(hPen, &miterLimit));

			return miterLimit;
		}
		//@别名 置对齐方式()
		Status SetAlignment(__in PenAlignment penAlignment)
		{
			return SetStatus(DllExports::GdipSetPenMode(hPen, penAlignment));
		}
		//@别名 取对齐方式()
		PenAlignment GetAlignment() 
		{
			PenAlignment penAlignment;
			
			SetStatus(DllExports::GdipGetPenMode(hPen, &penAlignment));
			
			return penAlignment;
		}
		//@别名 置矩阵()
		Status SetTransform(__in const GPMatrix* matrix)
		{
			return SetStatus(DllExports::GdipSetPenTransform(hPen, 
														   matrix->hMatrix));
		}
		//@别名 取矩阵()
		Status GetTransform(__out GPMatrix* matrix) 
		{
			return SetStatus(DllExports::GdipGetPenTransform(hPen, 
															 matrix->hMatrix));
		}
		//@别名 矩阵重置()
		Status ResetTransform()
		{
			return SetStatus(DllExports::GdipResetPenTransform(hPen));
		}
		//@别名 矩阵相乘()
		Status MultiplyTransform(__in const GPMatrix* matrix,
								 __in MatrixOrder order = MatrixOrderPrepend)
		{
			return SetStatus(DllExports::GdipMultiplyPenTransform(hPen,
															 matrix->hMatrix,
															 order));
		}
		//@别名 矩阵平移()
		Status TranslateTransform(__in REAL dx, 
								  __in REAL dy,
								  __in MatrixOrder order = MatrixOrderPrepend)
		{
			return SetStatus(DllExports::GdipTranslatePenTransform(hPen,
																   dx, 
																   dy, 
																   order));
		}
		//@别名 矩阵缩放()
		Status ScaleTransform(__in REAL sx, 
							  __in REAL sy,
							  __in MatrixOrder order = MatrixOrderPrepend)
		{
			return SetStatus(DllExports::GdipScalePenTransform(hPen,
															   sx, 
															   sy, 
															   order));
		}
		//@别名 矩阵旋转()
		Status RotateTransform(__in REAL angle, 
							   __in MatrixOrder order = MatrixOrderPrepend)
		{
			return SetStatus(DllExports::GdipRotatePenTransform(hPen,
																angle, 
																order));
		}
		//@别名 取画笔类型()
		PenType GetPenType() 
		{
		   PenType type;
		   SetStatus(DllExports::GdipGetPenFillType(hPen, &type));

		   return type;
		}
		//@别名 置画刷()
		Status SetBrush(__in const GPBrush* brush)
		{
			return SetStatus(DllExports::GdipSetPenBrushFill(hPen, 
										   brush->hBrush));
		}
		//@别名 取颜色()
		Status GetColor(__out Color* color) 
		{
			if (color == NULL) 
			{
				return SetStatus(InvalidParameter);
			}
			
			PenType type = GetPenType();

			if (type != PenTypeSolidColor) 
			{
				return WrongState;
			}
			
			ARGB argb;
			
			SetStatus(DllExports::GdipGetPenColor(hPen,
												  &argb));
			if (lastResult == Ok)
			{
				color->SetValue(argb);
			}
			
			return lastResult;
		}
		//@别名 取画刷()
		GPBrush* GetBrush() 
		{
		   PenType type = GetPenType();

		   GPBrush* brush = NULL;

		   switch(type)
		   {
		   case PenTypeSolidColor:
			   brush = new GPSolidBrush();
			   break;

		   case PenTypeHatchFill:
			   brush = new GPHatchBrush();
			   break;

		   case PenTypeTextureFill:
			   brush = new GPTextureBrush();
			   break;

		   case PenTypePathGradient:
			   brush = new GPBrush();
			   break;

		   case PenTypeLinearGradient:
			   brush = new GPLinearGradientBrush();
			   break;

		   default:
			   break;
		   }

		   if(brush)
		   {
			   GpBrush* nativeBrush;

			   SetStatus(DllExports::GdipGetPenBrushFill(hPen, 
														 &nativeBrush));
			   brush->SetNativeBrush(nativeBrush);
		   }

		   return brush;
		}
		//@别名 取虚线样式()
		DashStyle GetDashStyle() 
		{
			DashStyle dashStyle;

			SetStatus(DllExports::GdipGetPenDashStyle(hPen, &dashStyle));

			return dashStyle;
		}
		//@别名 置虚线样式()
		Status SetDashStyle(__in DashStyle dashStyle)
		{
			return SetStatus(DllExports::GdipSetPenDashStyle(hPen, 
															 dashStyle));
		}
		//@别名 取虚线偏移()
		REAL GetDashOffset() 
		{
			REAL dashOffset;

			SetStatus(DllExports::GdipGetPenDashOffset(hPen, &dashOffset));

			return dashOffset;
		}
		//@别名 置虚线偏移()
		Status SetDashOffset(__in REAL dashOffset)
		{
			return SetStatus(DllExports::GdipSetPenDashOffset(hPen, 
															  dashOffset));
		}
		//@别名 置虚线格式()
		Status SetDashPattern(__in const REAL* dashArray, __in INT count)
		{
			return SetStatus(DllExports::GdipSetPenDashArray(hPen,
															 dashArray, 
															 count));
		}
		//@别名 取虚线格式数()
		INT GetDashPatternCount() 
		{
			INT count = 0;
			
			SetStatus(DllExports::GdipGetPenDashCount(hPen, &count));
			
			return count;
		}
		//@别名 取虚线格式()
		Status GetDashPattern(__out REAL* dashArray, 
							  __in INT count) 
		{
			if (dashArray == NULL || count <= 0)
				return SetStatus(InvalidParameter); 
			
			return SetStatus(DllExports::GdipGetPenDashArray(hPen, 
															 dashArray, 
															 count));
		}
		//@别名 置分割数组()
		Status SetCompoundArray(__in const REAL* compoundArray,
								__in INT count)
		{
			return SetStatus(DllExports::GdipSetPenCompoundArray(hPen, 
																 compoundArray,
																 count));
		}
		//@别名 取分割数()
		INT GetCompoundArrayCount() 
		{
			INT count = 0;
			
			SetStatus(DllExports::GdipGetPenCompoundCount(hPen, &count));
			
			return count;
		}
		//@别名 取分割数组()
		Status GetCompoundArray(__out REAL* compoundArray, 
								__in INT count) 
		{
			if (compoundArray == NULL || count <= 0)
				return SetStatus(InvalidParameter); 
			
			return SetStatus(DllExports::GdipGetPenCompoundArray(hPen, 
																 compoundArray, 
																 count));
		}
};
//@分组}

//@分组{  Gdiplus
//@别名 GP图形类
class GPGraphics : public GPbase {
	public:
	//@隐藏{
	Gdiplus::GpGraphics* hGraphics;
	// Gdiplus::GpBitmap* hBitmap;
	public:
	GPGraphics();
	~GPGraphics();
	//@隐藏}
	//@别名 取指针()
	Gdiplus::GpGraphics* GetPtr();
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory();
	//@备注 创建一个与指定设备上下文相关联的 GP图形类 对象
	//@参数 场景句柄 关联的设备上下文句柄
	//@参数 设备句柄 关联的设备的句柄
	//@别名 创建自场景句柄(场景句柄,设备句柄)
	bool CreateFromDC(HDC hdc,HANDLE handle = 0) ;
	// @备注  创建一个与指定窗口关联的 GP图形类 对象
	// @参数  hwnd  窗口句柄
	// @参数  IsICM 可选的。布尔值，指定新的 GP图形类 对象是否根据与显示设备关联的 ICC 配置文件应用颜色调整。真 指定应用颜色调整，假 指定不应用颜色调整。默认值为 假。 
	// @返回  如果成功返回TRUE,否则返回FALSE
	// @别名  创建自窗口句柄(窗口句柄, 使用ICM)
	bool CreateFromHWND(HWND hwnd,bool IsICM = false) ;
	// @备注  创建一个与指定 GP图像类 对象关联的 GP图形类 对象
	// @参数  Image 图像
	// @返回  如果成功返回TRUE,否则返回FALSE
	// @别名  创建自图像(图像)
	bool CreateFromImage(GPImage& Image) ;
	// @备注  返回当前图形对象的DC句柄。不用后用“对象.释放场景句柄”释放设备场景句柄
	// @返回  如果成功返回非0,否则返回0
	// @别名  取场景句柄()
	HDC GetHDC() ;
	// @备注  释放由方法“对象.取场景句柄”返回的设备场景句柄
	// @参数  hdc
	// @返回  如果成功返回TRUE,否则返回FALSE
	// @别名  释放场景句柄(hdc)
	bool ReleaseHDC(HDC hdc) ;
	// @备注  
	// @参数  x
	// @参数  y
	// @返回  如果成功返回TRUE,否则返回FALSE
	// @别名  置渲染原点(x, y)
	bool SetRenderingOrigin(int x,int y) ;
	// @备注  
	// @参数  x 输出参数
	// @参数  y 输出参数
	// @返回  如果成功返回TRUE,否则返回FALSE
	// @别名  取渲染原点(x, y)
	bool GetRenderingOrigin(__out int* x,__out int* y);
	// @别名  置混合模式(混合模式)
	bool SetCompositingMode(CompositingMode Mode) ;
	// @别名  取混合模式()
	CompositingMode GetCompositingMode() ;

	// @别名  置混合品质(混合品质)
	bool SetCompositingQuality(CompositingQuality Quality) ;
	// @别名  取混合品质()
	CompositingQuality GetCompositingQuality() ;
	// @别名  置文本渲染模式(渲染模式)
	bool SetTextRenderingHint(TextRenderingHint TextRendering) ;
	// @别名  取文本渲染模式()
	TextRenderingHint GetTextRenderingHint();
	//@参数  文本对比度 必须介于 0 和 12 之间
	//@别名  置文本对比度(文本对比度)
	bool SetTextContrast(UINT contrast) ;
	// @别名  取文本对比度()
	UINT GetTextContrast() ;
	//@别名  置算法模式(算法模式)
	bool SetInterpolationMode(InterpolationMode mode) ;
	// @别名  取算法模式()
	InterpolationMode GetInterpolationMode();
	//@别名 置平滑模式(平滑模式)
	bool SetSmoothingMode(SmoothingMode Mode);
	// @别名  取平滑模式()
	SmoothingMode GetSmoothingMode() ;
	//@别名 置像素偏移模式(平滑模式)
	bool SetPixelOffsetMode(PixelOffsetMode Mode);
	// @别名  取像素偏移模式()
	PixelOffsetMode GetPixelOffsetMode() ;
	//@别名 取矩阵(GP矩阵)
	bool GetTransform(GPMatrix& Matrix);
	//@别名 置矩阵(GP矩阵)
	bool SetTransform(GPMatrix& Matrix);
	//@备注 将此图形的变换矩阵重置为单位矩阵。这意味着不会发生任何转换。
	//@别名 矩阵重置()
	bool ResetTransform();
	//@备注 用它自己和另一个矩阵的乘积更新这个图形的变换矩阵。
	//@参数 GP矩阵 要与此图形的当前变换矩阵相乘的矩阵
	//@参数 矩阵顺序 用于指定乘法的顺序。GP矩阵顺序.前置 指定传递的矩阵在左侧，GP矩阵顺序.后置 指定传递的矩阵在右侧。
	//@别名 矩阵相乘(GP矩阵,矩阵顺序)
	bool MultiplyTransform(GPMatrix& Matrix,MatrixOrder Order = MatrixOrderPrepend);
	//@备注 使用自身和平移矩阵的乘积更新此图形的当前变换矩阵。
	//@参数 水平偏移量 指定平移的水平分量
	//@参数 垂直偏移量 指定平移的垂直分量
	//@参数 矩阵顺序 用于指定乘法的顺序。GP矩阵顺序.前置 指定传递的矩阵在左侧，GP矩阵顺序.后置 指定传递的矩阵在右侧。
	//@别名 矩阵平移(水平偏移量,垂直偏移量,矩阵顺序)
	bool TranslateTransform(float x,float y,MatrixOrder Order = MatrixOrderPrepend);
	//@备注 使用自身和缩放矩阵的乘积更新此图形的当前变换矩阵。
	//@参数 水平缩放量 指定要在 x 方向上缩放的量
	//@参数 垂直缩放量 指定要在 y 方向上缩放的量
	//@参数 矩阵顺序 用于指定乘法的顺序。GP矩阵顺序.前置 指定传递的矩阵在左侧，GP矩阵顺序.后置 指定传递的矩阵在右侧。
	//@别名 矩阵缩放(水平缩放量,垂直缩放量,矩阵顺序)
	bool ScaleTransform(float x,float y,MatrixOrder Order = MatrixOrderPrepend);
	//@备注 使用自身和矩阵旋转的乘积更新此图形的当前变换矩阵。
	//@参数 角度 指定旋转角度（以度为单位）
	//@参数 矩阵顺序 用于指定乘法的顺序。GP矩阵顺序.前置 指定传递的矩阵在左侧，GP矩阵顺序.后置 指定传递的矩阵在右侧。
	//@别名 矩阵旋转(角度,矩阵顺序)
	bool RotateTransform(float Rotate,MatrixOrder Order = MatrixOrderPrepend);
	//@别名 置页单位(单位)
	bool SetPageUnit(Unit unit);
	//@别名 取页单位()
	Unit GetPageUnit() ;
	//@别名 置页比例(比例)
	bool SetPageScale(float scale);
	//@别名 取页比例()
	float GetPageScale() ;
	//@别名 取水平分辨率()
	float GetDpiX() ;
	//@别名 取垂直分辨率()
	float GetDpiY() ;
	//@别名 转换坐标空间(目标坐标空间,源坐标空间,坐标数组,个数)
	bool TransformPoints(CoordinateSpace destSpace,CoordinateSpace srcSpace,PointF *pts,int count);
	//@别名 转换坐标空间I(目标坐标空间,源坐标空间,坐标数组,个数)
	bool TransformPointsI(CoordinateSpace destSpace,CoordinateSpace srcSpace,Point *pts,int count);
	//@别名 取最近颜色()
	int GetNearestColor(int Color) ;
	//@别名 画直线(GP画笔,x1,y1,x2,y2)
	bool DrawLine(GPPen& pen,float x1,float y1,float x2,float y2);
	//@别名 画直线I(GP画笔,x1,y1,x2,y2)
	bool DrawLineI(GPPen& pen,int x1,int y1,int x2,int y2);
	//@别名 画直线组(GP画笔,坐标数组,个数)
	bool DrawLines(GPPen& pen,PointF *pts,int count);
	//@别名 画直线组I(GP画笔,坐标数组)
	bool DrawLinesI(GPPen& pen,Point *pts,int count);
	//@别名 画圆弧(GP画笔,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool DrawArc(GPPen& pen,float x,float y,float w,float h,float startAngle,float sweepAngle);
	//@别名 画圆弧I(GP画笔,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool DrawArc(GPPen& pen,int x,int y,int w,int h,float startAngle,float sweepAngle);
	//@别名 画贝塞尔曲线(GP画笔,x1,y1,x2,y2,x3,y3,x4,y4)
	bool DrawBezier(GPPen& pen,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4);
	//@别名 画贝塞尔曲线I(GP画笔,x1,y1,x2,y2,x3,y3,x4,y4)
	bool DrawBezierI(GPPen& pen,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
	//@参数 坐标数组 数组成员数必须4个以上
	//@参数 个数 数组个数
	//@别名 画贝塞尔曲线组(GP画笔,坐标数组,个数)
	bool DrawBeziers(GPPen& pen,PointF *pts,int count);
	//@参数 坐标数组 数组成员数必须4个以上
	//@参数 个数 数组个数
	//@别名 画贝塞尔曲线组I(GP画笔,坐标数组,个数)
	bool DrawBeziersI(GPPen& pen,Point *pts,int count);
	//@别名 画矩形(GP画笔,左边,顶边,宽度,高度)
	bool DrawRectangle(GPPen& pen,float x,float y,float w,float h);
	//@别名 画矩形I(GP画笔,左边,顶边,宽度,高度)
	bool DrawRectangle(GPPen& pen,int x,int y,int w,int h);
	//@别名 画矩形组(GP画笔,矩形数组,个数)
	bool DrawRectangles(GPPen& pen,RectF *pts,int count);
	//@别名 画矩形组I(GP画笔,矩形数组,个数)
	bool DrawRectangles(GPPen& pen,Rect *pts,int count);
	//@别名 画椭圆(GP画笔,左边,顶边,宽度,高度)
	bool DrawEllipse(GPPen& pen,float x,float y,float w,float h);
	//@别名 画椭圆I(GP画笔,左边,顶边,宽度,高度)
	bool DrawEllipse(GPPen& pen,int x,int y,int w,int h);
	//@别名 画饼(GP画笔,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool DrawPie(GPPen& pen,float x,float y,float w,float h,float startAngle,float sweepAngle);
	//@别名 画饼I(GP画笔,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool DrawPie(GPPen& pen,int x,int y,int w,int h,float startAngle,float sweepAngle);
	//@别名 画多边形(GP画笔,坐标数组,个数)
	bool DrawPolygon(GPPen& pen,PointF *pts,int count);
	//@别名 画多边形I(GP画笔,坐标数组,个数)
	bool DrawPolygonI(GPPen& pen,Point *pts,int count);
	//@别名 画路径(GP画笔,GP路径)
	bool DrawPath(GPPen& pen,GPPath& path);
	//@别名 画曲线(GP画笔,坐标数组,个数)
	bool DrawCurve(GPPen& pen,PointF *pts,int count);
	//@别名 画曲线I(GP画笔,坐标数组,个数)
	bool DrawCurveI(GPPen& pen,Point *pts,int count);
	//@别名 画曲线2(GP画笔,坐标数组,个数,张力)
	bool DrawCurve2(GPPen& pen,PointF *pts,int count,float tension);
	//@别名 画曲线2I(GP画笔,坐标数组,个数,张力)
	bool DrawCurve2I(GPPen& pen,Point *pts,int count,float tension);
	//@别名 画曲线3(GP画笔,坐标数组,个数,偏移量,段数,张力)
	bool DrawCurve3(GPPen& pen,PointF *pts,int count,int Offset,int segment, float tension);
	//@别名 画曲线3I(GP画笔,坐标数组,个数,偏移量,段数,张力)
	bool DrawCurve3I(GPPen& pen,Point *pts,int count,int Offset,int segment, float tension);
	//@别名 画闭合曲线(GP画笔,坐标数组,个数)
	bool DrawClosedCurve(GPPen& pen,PointF *pts,int count);
	//@别名 画闭合曲线I(GP画笔,坐标数组,个数)
	bool DrawClosedCurveI(GPPen& pen,Point *pts,int count);
	//@别名 画闭合曲线2(GP画笔,坐标数组,个数,张力)
	bool DrawClosedCurve2(GPPen& pen,PointF *pts,int count,float tension);
	//@别名 画闭合曲线2I(GP画笔,坐标数组,个数,张力)
	bool DrawClosedCurve2I(GPPen& pen,Point *pts,int count,float tension);
	//@备注 清除整个绘图面,并以指定色填充。
	//@别名 清除(ARGB颜色)
	bool Clear(ARGB Color);
	//@别名 填充矩形(GP画刷,左边,顶边,宽度,高度)
	bool FillRectangle(GPBrush& brush,float x,float y,float w,float h);
	//@别名 填充矩形I(GP画刷,左边,顶边,宽度,高度)
	bool FillRectangleI(GPBrush& brush,int x,int y,int w,int h);
	//@别名 填充矩形组(GP画刷,矩形数组,个数)
	bool FillRectangles(GPBrush& brush,RectF *rcs,int count);
	//@别名 填充矩形组I(GP画刷,矩形数组,个数)
	bool FillRectanglesI(GPBrush& brush,Rect *rcs,int count);
	//@别名 填充多边形(GP画刷,坐标数组,个数,填充模式)
	bool FillPolygon(GPBrush& brush,PointF *pt,int count,FillMode Mode);
	//@别名 填充多边形I(GP画刷,坐标数组,个数,填充模式)
	bool FillPolygonI(GPBrush& brush,Point *pt,int count,FillMode Mode);
	//@别名 填充椭圆(GP画刷,左边,顶边,宽度,高度)
	bool FillEllipse(GPBrush& brush,float x,float y,float w,float h);
	//@别名 填充椭圆I(GP画刷,左边,顶边,宽度,高度)
	bool FillEllipseI(GPBrush& brush,int x,int y,int w,int h);
	//@别名 填充饼(GP画刷,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool FillPie(GPBrush& brush,float x,float y,float w,float h,float startAngle,float sweepAngle);
	//@别名 填充饼I(GP画刷,左边,顶边,宽度,高度,开始角度,扫描角度)
	bool FillPieI(GPBrush& brush,int x,int y,int w,int h,float startAngle,float sweepAngle);
	//@别名 填充路径(GP画刷,GP路径)
	bool FillPath(GPBrush& brush,GPPath& path);
	//@别名 填充闭合曲线(GP画刷,坐标数组,个数)
	bool FillClosedCurve(GPBrush& brush,PointF *pt,int count);
	//@别名 填充闭合曲线I(GP画刷,坐标数组,个数)
	bool FillClosedCurveI(GPBrush& brush,Point *pt,int count);
	//@别名 填充闭合曲线2(GP画刷,坐标数组,个数,张力,填充模式)
	bool FillClosedCurve2(GPBrush& brush,PointF *pt,int count,float tension,FillMode Mode);
	//@别名 填充闭合曲线2I(GP画刷,坐标数组,个数,张力,填充模式)
	bool FillClosedCurve2I(GPBrush& brush,Point *pt,int count,float tension,FillMode Mode);
	//@别名 填充区域(GP画刷,GP区域)
	bool FillRegion(GPBrush& brush,GPRegion& region);
	//@别名 画文本(文本,GP字体,GP画刷,矩形,GP文本格式)
	bool DrawString(CXText text,GPFont* font,GPBrush* brush,RectF *rc,GPStringFormat& stringFormat = GPStringFormat());
	
	//@别名 画文本(文本,GP字体,GP画刷,左边,顶边)
    Status DrawString(CXText text,const GPFont *font,const GPBrush *brush,const REAL x,const REAL y)
    {
        RectF rect(x, y, 0.0f, 0.0f);
        return SetStatus(DllExports::GdipDrawString(
            hGraphics,
            text.getPtr(),
            text.getSize(),
            font ? font->hFont : NULL,
            &rect,
            NULL,
            brush ? brush->hBrush : NULL
        ));
    }
	//@别名 画文本(文本,GP字体,GP画刷,坐标位置)
	Status DrawString(CXText text,const GPFont *font,const GPBrush *brush,const PointF &origin)
    {
        RectF rect(origin.X, origin.Y, 0.0f, 0.0f);
        return SetStatus(DllExports::GdipDrawString(
            hGraphics,
            text.getPtr(),
            text.getSize(),
            font ? font->hFont : NULL,
            &rect,
            NULL,
            brush ? brush->hBrush : NULL
        ));
    }
	//@备注 测量字符串在指定字体、文本格式和 布局矩形 中的范围.
	//@参数 文本 要测量的文本
	//@参数 GP字体
	//@参数 布局矩形 此矩形作为测量的参考,可仅设置左边顶边,也可仅设置宽度高度
	//@参数 GP文本格式
	//@参数 测量矩形 输出参数
	//@别名 测量文本矩形(文本,GP字体,布局矩形,GP文本格式,测量矩形)
	BOOL MeasureString(__in const CXText text,__in const GPFont& font,__in const RectF& layoutRect,__in const GPStringFormat& stringFormat,__out RectF* boundingBox);
	//@备注 测量字符串在指定字体、文本格式和 布局矩形 中的范围.
	//@参数 文本 要测量的文本
	//@参数 GP字体
	//@参数 布局矩形 此矩形作为测量的参考,可仅设置左边顶边,也可仅设置宽度高度
	//@参数 GP文本格式
	//@参数 测量矩形 输出参数
	//@参数 适合字符数 输出参数,实际适合布局矩形的字符数
	//@参数 适合行数 输出参数,适合布局矩形的行数
	//@别名 测量文本矩形2(文本,GP字体,布局矩形,GP文本格式,测量矩形,适合字符数,适合行数)
	BOOL MeasureString2(__in const CXText text,__in const GPFont& font,__in const RectF& layoutRect,__in const GPStringFormat& stringFormat,__out RectF* boundingBox,__out INT* codepointsFitted,__out INT* linesFilled);
	
	//@别名 测量文本矩形1(文本,GP字体,布局矩形,测量矩形)
	BOOL MeasureString1(__in const CXText text,__in const GPFont *font, __in const RectF  &layoutRect, __out RectF *boundingBox) ;

	//@备注 获取一组区域，每个区域限定字符串中的字符位置范围.
	//@参数 文本 要测量的文本
	//@参数 GP字体
	//@参数 布局矩形 此矩形作为测量的参考,
	//@参数 GP文本格式 设置 文本格式.置测量字符范围()
	//@参数 区域数 指定预期接收到区域数组中的区域数。此数字应等于 <文本格式>  对象中当前的字符范围数。
	//@参数 区域集 输出参数,直接传递空数组对象, 函数执行完毕后, 数组每个区域都限定了一个文本范围。
	//@别名 测量字符范围(文本,GP字体,布局矩形,GP文本格式,区域数,区域集)
	BOOL MeasureCharacterRanges(const CXText string,const GPFont &font,const RectF &layoutRect,const GPStringFormat &stringFormat,INT regionCount,
    __out GPRegion  *regions);
	//@参数 文本 要测量的文本
	//@参数 GP字体
	//@参数 GP画刷 
	//@参数 坐标数组 每一个坐标指定每个字符所在的位置。
	//@参数 GP控制文本选项 GP控制文本选项 常量组合
	//@参数 GP矩阵 
	//@别名 画控制文本(文本,GP字体,GP画刷,坐标数组,GP控制文本选项,GP矩阵)
	BOOL DrawDriverString(CXText string,const GPFont &font,GPBrush& brush,PointF *pt,DriverStringOptions Options,GPMatrix& Matrix);
	//@参数 文本 要测量的文本
	//@参数 GP字体
	//@参数 坐标数组 每一个坐标指定每个字符所在的位置。
	//@参数 GP控制文本选项 GP控制文本选项 常量组合
	//@参数 GP矩阵 
	//@参数 边界矩形 输出参数
	//@别名 测量控制文本(文本,GP字体,坐标数组,GP控制文本选项,GP矩阵,边界矩形)
	BOOL MeasureDriverString(CXText string,const GPFont &font,PointF *pt,DriverStringOptions Options,GPMatrix& Matrix,RectF *layoutRect);
	//@备注 在此图形目标偏移 x、y 上绘制缓存位图。 请注意，如果 缓存位图 本机格式与此 Graphics 不同，这将失败并显示 WrongState
	//@别名 画缓存位图(缓存位图,x,y)
	BOOL DrawCachedBitmap(GPCachedBitmap& pBitmap,int x,int y);
	//@别名 画图像(图像,x,y)
	BOOL DrawImage(GPImage& pImage,float x,float y);
	//@别名 画图像I(图像,x,y)
	BOOL DrawImageI(GPImage& pImage,int x,int y);
	//@别名 画图像矩形(图像,左边,顶边,宽度,高度)
	BOOL DrawImageRect(GPImage& pImage,float x,float y,float w,float h);
	//@别名 画图像矩形I(图像,左边,顶边,宽度,高度)
	BOOL DrawImageRectI(GPImage& pImage,int x,int y,int w,int h);
	//@别名 画图像坐标组(图像,坐标数组,数组个数)
	BOOL DrawImagePoints(GPImage& pImage,PointF *pt,int count);
	//@别名 画图像部分(图像,左边,顶边,原图左边,原图顶边,原图宽度,原图高度,单位)
	BOOL DrawImagePointRect(GPImage& pImage,float x,float y,float L,float T,float w,float h,Unit unit = UnitPixel);
	//@别名 画图像缩放部分(图像,左边,顶边,宽度,高度,原图左边,原图顶边,原图宽度,原图高度,原图单位,图像属性)
	BOOL DrawImageRectRect(GPImage& pImage,float x,float y,float w,float h,float L,float T,float w1,float h1,Unit unit,GPImageAttributes& ImageAttr);
	//@别名 画图像效果()
	Status DrawImageeffect(
        __in GPImage *image,
        __in RectF *sourceRect,
        __in GPMatrix *xForm,
        __in GPEffect *effect,
        __in GPImageAttributes *imageAttributes,
        __in Unit srcUnit
    )
    {
        return SetStatus(DllExports::GdipDrawImageFX(
            hGraphics,
            image->hImage,
            sourceRect,
            xForm ? xForm->hMatrix : NULL,
            effect ? effect->nativeEffect : NULL,
            imageAttributes ? imageAttributes->nativeImageAttr : NULL,
            srcUnit
        ));
    }
	
	//@别名 置剪辑区(图形,合并模式)
	Status SetClip(__in const GPGraphics* g,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipGraphics(hGraphics,
                                                         g->hGraphics,
                                                         combineMode));
    }
	//@别名 置剪辑区(矩形F,合并模式)
    Status SetClip(__in const RectF& rect,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipRect(hGraphics,
                                                     rect.X, rect.Y,
                                                     rect.Width, rect.Height,
                                                     combineMode));
    }
	//@别名 置剪辑区(矩形,合并模式)
    Status SetClip(__in const Rect& rect,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipRectI(hGraphics,
                                                      rect.X, rect.Y,
                                                      rect.Width, rect.Height,
                                                      combineMode));
    }
	//@别名 置剪辑区(路径,合并模式)
    Status SetClip(__in const GPPath* path,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipPath(hGraphics,
                                                     path->nativePath,
                                                     combineMode));
    }
	//@别名 置剪辑区(区域,合并模式)
    Status SetClip(__in const GPRegion* region,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipRegion(hGraphics,
                                                       region->nativeRegion,
                                                       combineMode));
    }

    // This is different than the other SetClip methods because it assumes
    // that the HRGN is already in device units, so it doesn't transform
    // the coordinates in the HRGN.
	//@别名 置剪辑区(HRGN,合并模式)
    Status SetClip(__in HRGN hRgn,
                   __in CombineMode combineMode = CombineModeReplace)
    {
        return SetStatus(DllExports::GdipSetClipHrgn(hGraphics, hRgn,
                                                     combineMode));
    }


	//@别名 交集剪辑区()
	Status IntersectClip(__in const RectF& rect)
    {
        return SetStatus(DllExports::GdipSetClipRect(hGraphics,
                                                     rect.X, rect.Y,
                                                     rect.Width, rect.Height,
                                                     CombineModeIntersect));
    }
	//@别名 交集剪辑区()
    Status IntersectClip(__in const Rect& rect)
    {
        return SetStatus(DllExports::GdipSetClipRectI(hGraphics,
                                                      rect.X, rect.Y,
                                                      rect.Width, rect.Height,
                                                      CombineModeIntersect));
    }
	//@别名 交集剪辑区()
    Status IntersectClip(__in const GPRegion* region)
    {
        return SetStatus(DllExports::GdipSetClipRegion(hGraphics,
                                                       region->nativeRegion,
                                                       CombineModeIntersect));
    }
	//@别名 排除剪辑区()
    Status ExcludeClip(__in const RectF& rect)
    {
        return SetStatus(DllExports::GdipSetClipRect(hGraphics,
                                                     rect.X, rect.Y,
                                                     rect.Width, rect.Height,
                                                     CombineModeExclude));
    }
	//@别名 排除剪辑区()
    Status ExcludeClip(__in const Rect& rect)
    {
        return SetStatus(DllExports::GdipSetClipRectI(hGraphics,
                                                      rect.X, rect.Y,
                                                      rect.Width, rect.Height,
                                                      CombineModeExclude));
    }
	//@别名 排除剪辑区()
    Status ExcludeClip(__in const GPRegion* region)
    {
        return SetStatus(DllExports::GdipSetClipRegion(hGraphics,
                                                       region->nativeRegion,
                                                       CombineModeExclude));
    }
	//@别名 重置剪辑区()
    Status ResetClip()
    {
        return SetStatus(DllExports::GdipResetClip(hGraphics));
    }
	//@别名 平移剪辑区()
    Status TranslateClip(__in REAL dx,
                         __in REAL dy)
    {
        return SetStatus(DllExports::GdipTranslateClip(hGraphics, dx, dy));
    }
	//@别名 平移剪辑区()
    Status TranslateClip(__in INT dx,
                         __in INT dy)
    {
        return SetStatus(DllExports::GdipTranslateClipI(hGraphics,
                                                        dx, dy));
    }
	//@别名 取剪辑区()
    Status GetClip(__out GPRegion* region) 
    {
        return SetStatus(DllExports::GdipGetClip(hGraphics,
                                                 region->nativeRegion));
    }
	//@别名 取剪辑区边界()
    Status GetClipBounds(__out RectF* rect) 
    {
        return SetStatus(DllExports::GdipGetClipBounds(hGraphics, rect));
    }
	//@别名 取剪辑区边界()
    Status GetClipBounds(__out Rect* rect) 
    {
        return SetStatus(DllExports::GdipGetClipBoundsI(hGraphics, rect));
    }
	//@别名 是否为空剪辑区()
    BOOL IsClipEmpty() 
    {
        BOOL booln = FALSE;

        SetStatus(DllExports::GdipIsClipEmpty(hGraphics, &booln));

        return booln;
    }
	//@别名 取可见剪辑区边界()
    Status GetVisibleClipBounds(__out RectF *rect) 
    {

        return SetStatus(DllExports::GdipGetVisibleClipBounds(hGraphics,
                                                              rect));
    }
	//@别名 取可见剪辑区边界()
    Status GetVisibleClipBounds(__out Rect *rect) 
    {
       return SetStatus(DllExports::GdipGetVisibleClipBoundsI(hGraphics,
                                                              rect));
    }
	//@别名 是否为空可见剪辑区()
    BOOL IsVisibleClipEmpty() 
    {
        BOOL booln = FALSE;

        SetStatus(DllExports::GdipIsVisibleClipEmpty(hGraphics, &booln));

        return booln;
    }
	//@别名 是否可见坐标()
	BOOL IsVisible(__in const Point& point)
    {
        BOOL booln = FALSE;
        SetStatus(DllExports::GdipIsVisiblePointI(hGraphics,
                                                  point.X,
                                                  point.Y,
                                                  &booln));

        return booln;
    }
	//@别名 是否可见坐标()
	BOOL IsVisible(__in const Rect& rect) 
    {

        BOOL booln = TRUE;
        SetStatus(DllExports::GdipIsVisibleRectI(hGraphics,
                                                 rect.X,
                                                 rect.Y,
                                                 rect.Width,
                                                 rect.Height,
                                                 &booln));
        return booln;
    }
	//@别名 是否可见坐标()
	BOOL IsVisible(__in const PointF& point) 
    {
        BOOL booln = FALSE;
        SetStatus(DllExports::GdipIsVisiblePoint(hGraphics,
                                                 point.X,
                                                 point.Y,
                                                 &booln));

        return booln;
    }
	//@别名 是否可见坐标()
    BOOL IsVisible(__in REAL x,
                   __in REAL y,
                   __in REAL width,
                   __in REAL height) 
    {
        return IsVisible(RectF(x, y, width, height));
    }
	//@别名 是否可见坐标()
    BOOL IsVisible(__in const RectF& rect) 
    {
        BOOL booln = TRUE;
        SetStatus(DllExports::GdipIsVisibleRect(hGraphics,
                                                rect.X,
                                                rect.Y,
                                                rect.Width,
                                                rect.Height,
                                                &booln));
        return booln;
    }
	//@别名 保存()
	GraphicsState Save() 
    {
        GraphicsState gstate;
        SetStatus(DllExports::GdipSaveGraphics(hGraphics, &gstate));

        return gstate;
    }
	//@别名 恢复()
    Status Restore(__in GraphicsState gstate)
    {
        return SetStatus(DllExports::GdipRestoreGraphics(hGraphics,
                                                         gstate));
    }
	//@别名 开始容器()
    GraphicsContainer BeginContainer(__in const RectF &dstrect,
                                     __in const RectF &srcrect,
                                     __in Unit         unit)
    {
        GraphicsContainer state;

        SetStatus(DllExports::GdipBeginContainer(hGraphics, &dstrect,
                                                 &srcrect, unit, &state));

        return state;
    }
	//@别名 开始容器()
    GraphicsContainer BeginContainer(__in const Rect    &dstrect,
                                     __in const Rect    &srcrect,
                                     __in Unit           unit)
    {
        GraphicsContainer state;

        SetStatus(DllExports::GdipBeginContainerI(hGraphics, &dstrect,
                                                  &srcrect, unit, &state));

        return state;
    }
	//@别名 开始容器()
    GraphicsContainer BeginContainer()
    {
        GraphicsContainer state;

        SetStatus(DllExports::GdipBeginContainer2(hGraphics, &state));

        return state;
    }
	//@别名 结束容器()
    Status EndContainer(__in GraphicsContainer state)
    {
        return SetStatus(DllExports::GdipEndContainer(hGraphics, state));
    }
	//@别名 创建半调调色板()
	static HPALETTE GetHalftonePalette()
    {
        return DllExports::GdipCreateHalftonePalette();
    }
	//@别名 添加图元文件注译()
	Status AddMetafileComment(__in const BYTE * data,
                              __in UINT sizeData)
    {
        return SetStatus(DllExports::GdipComment(hGraphics, sizeData, data));
    }
	//@别名 列举图元文件()
	Status EnumerateMetafile(
        __in const GPMetafile *        metafile,
        __in const PointF &          destPoint,
        __in EnumerateMetafileProc   callback,
        __in VOID *                  callbackData    = NULL,
        __in const GPImageAttributes *       imageAttributes = NULL
        )
    {
        return SetStatus(DllExports::GdipEnumerateMetafileDestPoint(
                    hGraphics,
                    (const GpMetafile *)(metafile ? metafile->hImage:NULL),
                    destPoint,
                    callback,
                    callbackData,
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL));
    }
	//@别名 列举图元文件()
	Status EnumerateMetafile(
        __in const GPMetafile *        metafile,
        __in const RectF &           destRect,
        __in EnumerateMetafileProc   callback,
        __in VOID *                  callbackData    = NULL,
        __in const GPImageAttributes *       imageAttributes = NULL
        )
    {
        return SetStatus(DllExports::GdipEnumerateMetafileDestRect(
                    hGraphics,
                    (const GpMetafile *)(metafile ? metafile->hImage:NULL),
                    destRect,
                    callback,
                    callbackData,
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL));
    }
	//@别名 图元文件事件_回调(记录类型,标志,数据大小,数据指针,附加参数)
	事件定义 virtual BOOL OnEnumerateMetafileProc(EmfPlusRecordType unnamedParam1,UINT unnamedParam2,UINT unnamedParam3,const BYTE *unnamedParam4,VOID *unnamedParam5)
	{
		return TRUE;
		}
};
//@别名 GP位图类
class GPBitmap : public GPImage {
	
	public:
	//@别名 创建自文件()
	inline 
	BOOL FromFile(
		__in const WCHAR *filename, 
		__in BOOL useEmbeddedColorManagement = TRUE
		)
	{
		GpBitmap *bitmap = NULL;
		if(useEmbeddedColorManagement) 
		{
			lastResult = DllExports::GdipCreateBitmapFromFileICM(filename, &bitmap);
		}
		else
		{
			lastResult = DllExports::GdipCreateBitmapFromFile(filename, &bitmap);
		}
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自字节集()
	inline 
	BOOL FromStream(
		__in const CXBytes& bytes,
		__in BOOL useEmbeddedColorManagement
		)
	{
		GpBitmap *bitmap = NULL;
		m_stream = CreateStream(bytes);
		if(useEmbeddedColorManagement)
		{
			lastResult = DllExports::GdipCreateBitmapFromStreamICM(m_stream, &bitmap);
		}
		else
		{
			lastResult = DllExports::GdipCreateBitmapFromStream(m_stream, &bitmap);
		}
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自扫描行()
	inline
	BOOL CreateFromScan0(
		__in INT width,
		__in INT height,
		__in INT stride,
		__in PixelFormat format,
		__in BYTE *scan0
		)
	{
		GpBitmap *bitmap = NULL;
		lastResult = DllExports::GdipCreateBitmapFromScan0(width,
														   height,
														   stride,
														   format,
														   scan0,
														   &bitmap);

		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@备注 创建一个指定大小和像素格式的 GP位图类 对象。PixelFormat
	//@别名 创建自像素格式(宽度,高度,像素格式)
	BOOL CreateBitmapFromScan0(int w,int h,int format){
		Gdiplus::GpBitmap *bitmap = NULL;
		lastResult = Gdiplus::DllExports::GdipCreateBitmapFromScan0(w, h,0, format, NULL,&bitmap);
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@备注 基于 GP图形类 对象、宽度和高度创建 GP位图类 对象。
	//@别名 创建自图形(宽度,高度,图形)
	BOOL CreateBitmapFromGraphics(int w,int h,GPGraphics& format){
		Gdiplus::GpBitmap *bitmap = NULL;
		lastResult = Gdiplus::DllExports::GdipCreateBitmapFromGraphics(w, h,format.hGraphics, &bitmap);
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自表面()
	inline 
	BOOL FromDirectDrawSurface7(
		__in IDirectDrawSurface7 * surface
		)
	{
		GpBitmap *bitmap = NULL;
		lastResult = DllExports::GdipCreateBitmapFromDirectDrawSurface(surface,
														   &bitmap);

		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自GDI设备无关位图()
	inline 
	BOOL FromBITMAPINFO(
		__in const BITMAPINFO* gdiBitmapInfo, 
		__in VOID* gdiBitmapData
		)
	{
		GpBitmap *bitmap = NULL;

		lastResult = DllExports::GdipCreateBitmapFromGdiDib(gdiBitmapInfo,
															gdiBitmapData,
															&bitmap);

		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自位图句柄()
	inline 
	BOOL FromHBITMAP(
		__in HBITMAP hbm, 
		__in HPALETTE hpal
		)
	{
		GpBitmap *bitmap = NULL;
		lastResult = DllExports::GdipCreateBitmapFromHBITMAP(hbm, hpal, &bitmap);
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自图标句柄()
	inline 
	BOOL FromHICON(
		__in HICON hicon
		)
	{
		GpBitmap *bitmap = NULL;
		lastResult = DllExports::GdipCreateBitmapFromHICON(hicon, &bitmap);
		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 创建自资源()
	inline 
	BOOL FromResource(
		__in HINSTANCE hInstance, 
		__in const WCHAR *bitmapName
		)
	{
		GpBitmap *bitmap = NULL;
		lastResult = DllExports::GdipCreateBitmapFromResource(hInstance,
															  bitmapName,
															  &bitmap);

		SetNativeImage(bitmap);
		return lastResult == Gdiplus::Ok;
	}
	//@别名 克隆位图() 
	BOOL Clone(
		__in const Rect& rect,
		__in PixelFormat format,
		__out GPBitmap& pBitmap
		)
	{
		return Clone(rect.X, rect.Y, rect.Width, rect.Height, format,pBitmap);
	}
	//@别名 克隆位图() 
	BOOL Clone(
		__in INT x,
		__in INT y,
		__in INT width,
		__in INT height,
		__in PixelFormat format,
		__out GPBitmap& pBitmap
		)
	{
	   GpBitmap* gpdstBitmap = NULL;
	   SetStatus(DllExports::GdipCloneBitmapAreaI(
								   x,
								   y,
								   width,
								   height,
								   format,
								   (GpBitmap *)hImage,
								   &gpdstBitmap));
		pBitmap.hImage = gpdstBitmap;
		pBitmap.lastResult = lastResult;
		return lastResult == Gdiplus::Ok;						   
	}
	//@别名 克隆位图() 
	BOOL Clone(
		__in const RectF& rect,
		__in PixelFormat format,
		__out GPBitmap& pBitmap
		)
	{
		return Clone(rect.X, rect.Y, rect.Width, rect.Height, format,pBitmap);
	}
	//@别名 克隆位图()
	BOOL Clone(
		__in REAL x,
		__in REAL y,
		__in REAL width,
		__in REAL height,
		__in PixelFormat format,
		__out GPBitmap& pBitmap
		)
	{
	   GpBitmap* gpdstBitmap = NULL;
	   SetStatus(DllExports::GdipCloneBitmapArea(
								   x,
								   y,
								   width,
								   height,
								   format,
								   (GpBitmap *)hImage,
								   &gpdstBitmap));
	   
		pBitmap.hImage = gpdstBitmap;
		pBitmap.lastResult = lastResult;
		return lastResult == Gdiplus::Ok;
	}


	//@别名 写像素数据(像素数据)

	void WritePixelData(const BYTE* pixelData,UINT datalen){
		Rect rect;
		BitmapData bitmapData;
		rect.X =0;rect.Y=0;rect.Width = GetWidth();rect.Height = GetHeight();
		LockBits(&rect,ImageLockModeWrite,PixelFormat32bppARGB,&bitmapData);
		//pixelData.getPtr();
		int len =rect.Width*rect.Height*4;
		memcpy_s(bitmapData.Scan0,len, pixelData,datalen);

		UnlockBits(&bitmapData);

	}

	//@别名 读像素数据()
	void ReadPixelData(CXBytes& pixelData){
		Rect rect;
		BitmapData bitmapData;
		rect.X =0;rect.Y=0;rect.Width = GetWidth();rect.Height = GetHeight();
		LockBits(&rect,ImageLockModeRead,PixelFormat32bppARGB,&bitmapData);
		//pixelData.getPtr();
		
		int len =rect.Width*rect.Height*4;
		pixelData.resize(len);
		memcpy_s((void*)pixelData.getPtr(),len,bitmapData.Scan0,len);

		UnlockBits(&bitmapData);

	}


	//@别名 锁定()
	inline Status
	LockBits(
		__in const Rect* rect,
		__in UINT flags,
		__in PixelFormat format,
		__out BitmapData* lockedBitmapData
	)
	{
		return SetStatus(DllExports::GdipBitmapLockBits(
										static_cast<GpBitmap*>(hImage),
										rect,
										flags,
										format,
										lockedBitmapData));
	}
	//@别名 解除锁定()
	inline Status 
	UnlockBits(
		__in BitmapData* lockedBitmapData
		)
	{
		return SetStatus(DllExports::GdipBitmapUnlockBits(
										static_cast<GpBitmap*>(hImage),
										lockedBitmapData));
	}
	//@别名 取像素()
	inline Status 
	GetPixel(
		__in INT x, 
		__in INT y, 
		__out Color *color) 
	{
		ARGB argb;

		Status status = SetStatus(DllExports::GdipBitmapGetPixel(
			static_cast<GpBitmap *>(hImage),
			x, y,        
			&argb));

		if (status == Ok) 
		{
			color->SetValue(argb);
		}

		return  status;
	}
	//@别名 置像素()
	inline Status 
	SetPixel(
		__in INT x, 
		__in INT y, 
		__in const Color& color) 
	{
		return SetStatus(DllExports::GdipBitmapSetPixel(
			static_cast<GpBitmap *>(hImage),
			x, y,
			color.GetValue()));
	}
	//@别名 置分辨率()
	inline Status 
	SetResolution(
		__in REAL xdpi, 
		__in REAL ydpi)
	{
		return SetStatus(DllExports::GdipBitmapSetResolution(
			static_cast<GpBitmap *>(hImage),
			xdpi, ydpi));
	}
	//@别名 取位图句柄()
	inline Status 
	GetHBITMAP(
		__in const Color& colorBackground,
		__out HBITMAP* hbmReturn
		)
	{
		return SetStatus(DllExports::GdipCreateHBITMAPFromBitmap(
											static_cast<GpBitmap*>(hImage),
											hbmReturn,
											colorBackground.GetValue()));
	}
	//@别名 取图标句柄()
	inline Status 
	GetHICON(
		__out HICON* hiconReturn
		)
	{
		return SetStatus(DllExports::GdipCreateHICONFromBitmap(
											static_cast<GpBitmap*>(hImage),
											hiconReturn));
	}
	//@别名 应用效果(效果类,应用矩形)
	//@备注 效果类请看 GPEffect.h
	//@参数 继承效果类的各种效果（如模糊类）
	//@参数 矩形区域，如果为空则应用整个位图
	Status ApplyEffect(GPEffect *effect,RECT *ROI = nullptr)
	{
		if(effect->auxData)
		{
			DllExports::GdipFree(effect->auxData);
			effect->auxData = NULL;
			effect->auxDataSize = 0;
		}
		RECT m_ROI = {0, 0, this->GetWidth(), this->GetHeight()};
		if(ROI){
			 m_ROI = *ROI;
		}
		return DllExports::GdipBitmapApplyEffect(
			static_cast<GpBitmap *>(hImage),
			effect->nativeEffect,
			&m_ROI,
			effect->useAuxData,
			&effect->auxData,
			&effect->auxDataSize
			);
	}


	
};
//@别名 GP缓存位图类
class GPCachedBitmap : public GPbase{
	public:
		Gdiplus::GpCachedBitmap* nativeCachedBitmap;
	public:
	//@隐藏{
	GPCachedBitmap(){
		nativeCachedBitmap = nullptr;
	}
	~GPCachedBitmap(){
		Destory();
	}
	//@隐藏}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if(nativeCachedBitmap) Gdiplus::DllExports::GdipDeleteCachedBitmap(nativeCachedBitmap);
		nativeCachedBitmap = nullptr;
		lastResult = Gdiplus::Ok;
	}
	//@别名 创建()
	bool Create(GPBitmap& pBitmap,GPGraphics &pGraphics){
		this->Destory();
		lastResult = Gdiplus::DllExports::GdipCreateCachedBitmap((Gdiplus::GpBitmap *)pBitmap.hImage, pGraphics.hGraphics, &nativeCachedBitmap);
		return lastResult == Gdiplus::Ok;
	}

};
//@备注 用做内存中的图形, 双缓冲机制可以用. 也可以看做是和GDI交互的类
//@别名 GP缓存图形类
class GPCachedGraphics : public GPGraphics {
	public:
	//@隐藏{
		HBITMAP m_hBitmap;
		HDC m_hdc;
		INT m_Width;
		INT m_Height;
	public:
	GPCachedGraphics(){m_hBitmap = NULL;}
	~GPCachedGraphics(){Destory();}
	//@隐藏}
	//@别名 取位图句柄()
	HBITMAP GetBitmap(){return m_hBitmap;}
	//@备注 可以手动销毁, 但超出作用域也会自动销毁
	//@别名 销毁()
	void Destory(){
		if (hGraphics){
			Gdiplus::DllExports::GdipDeleteGraphics(hGraphics);
		}
		if(m_hBitmap)
			::DeleteObject (m_hBitmap);
		if(m_hdc)
			::DeleteDC (m_hdc);
		m_hdc = NULL;
		m_hBitmap = NULL;
		m_Width = 0;
		m_Height = 0;
		hGraphics = NULL;
		lastResult = Gdiplus::Ok;
	};
	//@别名 创建()
	BOOL Create(int Width,int Height,HDC hdc = NULL){
		this->Destory();
		BITMAPINFO bi;
		ZeroMemory(&bi, sizeof(BITMAPINFO));
		m_hdc = ::CreateCompatibleDC (hdc);
		if(!m_hdc) return FALSE;
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = Width;
		bi.bmiHeader.biHeight = Height;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;
		m_hBitmap = ::CreateDIBSection (m_hdc, &bi, DIB_RGB_COLORS, NULL, NULL,0);
		if(!m_hBitmap) {
			::DeleteDC(m_hdc);
			m_hdc = NULL;
			return FALSE;
		}
		::SelectObject(m_hdc, m_hBitmap);
		if( SetStatus(Gdiplus::DllExports::GdipCreateFromHDC(m_hdc, &hGraphics)) != Gdiplus::Ok)
		{
			::DeleteObject (m_hBitmap);
			::DeleteDC (m_hdc);
			return FALSE;
		}
		m_Width = Width;
		m_Height = Height;
		return TRUE;
	}
	//@别名 创建自场景句柄()
	BOOL CreateFromHDC(HDC hdc){
		this->Destory();
		m_Width = ::GetDeviceCaps (hdc, HORZRES);
		m_Height = ::GetDeviceCaps (hdc, VERTRES);
		return Create(m_Width, m_Height, hdc);
	}
	//@别名 创建自窗口句柄()
	BOOL CreateFromHWND(HWND hWnd){
		this->Destory();
		RECT rc;
		::GetClientRect(hWnd, &rc);
		return Create(rc.right - rc.left, rc.bottom - rc.top, 0);
	}
	//@别名 创建自图像()
	BOOL CreateFromImage(GPImage& hImage){
		this->Destory();
		int width = hImage.GetWidth ();
		int height = hImage.GetHeight ();
		if (Create (width, height, 0) == FALSE){
			return (FALSE);
		}
		return (DrawImageRectI (hImage, 0, 0, width, height));
	}
	//@备注 此方法不支持透明，但速度最快
	//@别名 复制()
	BOOL Copy(HDC hdc,int x,int y,int w,int h,int x1,int y1,UINT rop = SRCCOPY){
		BOOL ret = ::BitBlt(hdc, x, y, w, h, m_hdc, x1, y1, rop);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@备注 此方法不支持透明，但速度最快
	//@别名 复制到图形()
	BOOL Copy2Graphics(GPGraphics &hGraphics,int x,int y,int w,int h,int x1,int y1,UINT rop = SRCCOPY){
		HDC hdc = hGraphics.GetHDC();
		BOOL ret = ::BitBlt(m_hdc, x, y, w, h, hdc, x1, y1, rop);
		hGraphics.ReleaseHDC(hdc);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@备注 此方法不支持透明，但速度最快
	//@别名 复制自图形()
	BOOL CopyFromGraphics(GPGraphics &hGraphics,int x,int y,int w,int h,int x1,int y1){
		HDC hdc = hGraphics.GetHDC();
		BOOL ret = ::BitBlt(m_hdc, x, y, w, h, hdc, x1, y1, SRCCOPY);
		hGraphics.ReleaseHDC(hdc);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}


	//@备注 此方法支持复制过程中, 指定颜色透明
	//@别名 复制透明色()
	BOOL CopyTransparent(HDC hdc,int x,int y,int w,int h,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,UINT crTransparent){
		BOOL ret = ::GdiTransparentBlt(hdc, x, y, w, h, m_hdc, xoriginSrc, yoriginSrc, wSrc, hSrc,crTransparent);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@备注 此方法支持复制过程中, 指定颜色透明
	//@别名 复制透明色到图形()
	BOOL CopyTransparent2Graphics(GPGraphics &hGraphics,int x,int y,int w,int h,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,UINT crTransparent){
		HDC hdc = hGraphics.GetHDC();
		BOOL ret = ::GdiTransparentBlt(hdc, x, y, w, h, m_hdc, xoriginSrc, yoriginSrc, wSrc, hSrc,crTransparent);
		hGraphics.ReleaseHDC(hdc);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@备注 此方法支持透明混合
	//@别名 复制混合()
	BOOL CopyBlend(HDC hdc,int x,int y,int w,int h,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,BYTE crAlpha){
		BLENDFUNCTION bf = {0};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = crAlpha;
		BOOL ret = ::AlphaBlend(hdc, x, y, w, h, m_hdc, xoriginSrc, yoriginSrc, wSrc, hSrc, bf);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@备注 此方法支持透明混合
	//@别名 复制混合到图形()
	BOOL CopyBlend2Graphics(GPGraphics &hGraphics,int x,int y,int w,int h,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,BYTE crAlpha){
		BLENDFUNCTION bf = {0};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = crAlpha;
		HDC hdc = hGraphics.GetHDC();
		BOOL ret = ::AlphaBlend(hdc, x, y, w, h, m_hdc, xoriginSrc, yoriginSrc, wSrc, hSrc, bf);
		hGraphics.ReleaseHDC(hdc);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
	//@别名 更新到分层窗口()
	BOOL UpdateLayeredWin(HWND hWnd,HDC hdc,SIZE* psize,POINT* pt,BYTE crAlpha){
		BLENDFUNCTION bf = {0};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = crAlpha;
		BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, NULL, psize, m_hdc, pt, 0, &bf, ULW_ALPHA);
		return SetStatus(ret? Gdiplus::Ok: Gdiplus::GenericError) == Gdiplus::Ok;
	}
};

//@别名 GP路径渐变画刷类
class GPPathGradientBrush : public GPBrush
{
public:
	//@别名 创建()
    BOOL Create(
        __in const PointF* points,
        __in INT count,
        __in WrapMode wrapMode = WrapModeClamp)
    {
        GpPathGradient *brush = NULL;

        lastResult = DllExports::GdipCreatePathGradient(
                                        points, count,
                                        wrapMode, &brush);
        SetNativeBrush(brush);
		return lastResult == Gdiplus::Ok;
    }
	//@别名 创建I()
    BOOL CreateI(
        __in const Point* points,
        __in INT count,
        __in WrapMode wrapMode = WrapModeClamp)
    {
        GpPathGradient *brush = NULL;
        lastResult = DllExports::GdipCreatePathGradientI(
                                        points, count,
                                        wrapMode, &brush);

        SetNativeBrush(brush);
		return lastResult == Gdiplus::Ok;
    }
	//@别名 创建自路径()
    BOOL CreateFrompath( __in const GPPath* path)
    {
        GpPathGradient *brush = NULL;
        lastResult = DllExports::GdipCreatePathGradientFromPath(
                                        path->nativePath, &brush);
        SetNativeBrush(brush);
		return lastResult == Gdiplus::Ok;
    }
	//@别名 取中心颜色()
    Status GetCenterColor(__out Color* color) 
    {
        ARGB argb;
        if (color == NULL) 
        {
            return SetStatus(InvalidParameter);
        }
        SetStatus(DllExports::GdipGetPathGradientCenterColor(
                       (GpPathGradient*) hBrush, &argb));

        color->SetValue(argb);
        return lastResult;
    }
	//@别名 置中心颜色()
    Status SetCenterColor(__in const Color& color)
    {
        SetStatus(DllExports::GdipSetPathGradientCenterColor(
                       (GpPathGradient*) hBrush,
                       color.GetValue()));

        return lastResult;
    }
	//@别名 取坐标数()
    INT GetPointCount() 
    {
        INT count;

        SetStatus(DllExports::GdipGetPathGradientPointCount(
                       (GpPathGradient*) hBrush, &count));

        return count;
    }
	//@别名 取周围颜色数()
    INT GetSurroundColorCount() 
    {
        INT count;

        SetStatus(DllExports::GdipGetPathGradientSurroundColorCount(
                       (GpPathGradient*) hBrush, &count));

        return count;
    }
	//@别名 取周围颜色()
    Status GetSurroundColors(__out Color* colors, 
                             __in_out INT* count) 
    {
        if(colors == NULL || count == NULL)
        {
            return SetStatus(InvalidParameter);
        }

        INT count1;
        
        SetStatus(DllExports::GdipGetPathGradientSurroundColorCount(
                        (GpPathGradient*) hBrush, &count1));

        if(lastResult != Ok)
            return lastResult;

        if((*count < count1) || (count1 <= 0))
            return SetStatus(InsufficientBuffer);

        ARGB* argbs = (ARGB*) new ARGB[count1];
        if(argbs == NULL)
            return SetStatus(OutOfMemory);

        SetStatus(DllExports::GdipGetPathGradientSurroundColorsWithCount(
                    (GpPathGradient*)hBrush, argbs, &count1));

        if(lastResult == Ok)
        {
            for(INT i = 0; i < count1; i++)
            {
                colors[i].SetValue(argbs[i]);
            }        
            *count = count1;
        }

        delete [] argbs;
        return lastResult;
    }
	//@别名 置周围颜色()
    Status SetSurroundColors(__in const Color* colors, 
                             __in_out INT* count)
    {
        if(colors == NULL || count == NULL)
        {
            return SetStatus(InvalidParameter);
        }

        INT count1 = GetPointCount();

        if((*count > count1) || (count1 <= 0))
            return SetStatus(InvalidParameter);

        count1 = *count;

        ARGB* argbs = (ARGB*) new ARGB[count1];
        if(argbs == NULL)
            return SetStatus(OutOfMemory);

        for(INT i = 0; i < count1; i++)
        {
            argbs[i] = colors[i].GetValue();
        }

        SetStatus(DllExports::GdipSetPathGradientSurroundColorsWithCount(
                    (GpPathGradient*)hBrush, argbs, &count1));

        if(lastResult == Ok)
            *count = count1;

        delete [] argbs;

        return lastResult;
    }
	//@别名 取路径()
    Status GetGraphicsPath(__out GPPath* path) 
    {
        if(path == NULL)
            return SetStatus(InvalidParameter);

        return SetStatus(DllExports::GdipGetPathGradientPath(
                    (GpPathGradient*)hBrush, path->nativePath));
    }
	//@别名 置路径()
    Status SetGraphicsPath(__in const GPPath* path)
    {
        if(path == NULL)
            return SetStatus(InvalidParameter);

        return SetStatus(DllExports::GdipSetPathGradientPath(
                    (GpPathGradient*)hBrush, path->nativePath));
    }
	//@别名 取中心点()
    Status GetCenterPoint(__out PointF* point) 
    {
        return SetStatus(DllExports::GdipGetPathGradientCenterPoint(
                                (GpPathGradient*)hBrush,
                                point));
    }
	//@别名 取中心点()
    Status GetCenterPoint(__out Point* point) 
    {
        return SetStatus(DllExports::GdipGetPathGradientCenterPointI(
                                (GpPathGradient*)hBrush,
                                point));
    }
	//@别名 置中心点()
    Status SetCenterPoint(__in const PointF& point)
    {
        return SetStatus(DllExports::GdipSetPathGradientCenterPoint(
                                (GpPathGradient*)hBrush,
                                &point));
    }
	//@别名 置中心点()
    Status SetCenterPoint(__in const Point& point)
    {
        return SetStatus(DllExports::GdipSetPathGradientCenterPointI(
                                (GpPathGradient*)hBrush,
                                &point));
    }
	//@别名 取矩形()
    Status GetRectangle(__out RectF* rect) 
    {
        return SetStatus(DllExports::GdipGetPathGradientRect(
                            (GpPathGradient*)hBrush, rect));
    }
	//@别名 取矩形()
    Status GetRectangle(__out Rect* rect) 
    {
        return SetStatus(DllExports::GdipGetPathGradientRectI(
                            (GpPathGradient*)hBrush, rect));
    }
	//@别名 置伽玛校正()
    Status SetGammaCorrection(__in BOOL useGammaCorrection)
    {
        return SetStatus(DllExports::GdipSetPathGradientGammaCorrection(
            (GpPathGradient*)hBrush, useGammaCorrection));
    }
	//@别名 取伽玛校正()
    BOOL GetGammaCorrection() 
    {
        BOOL useGammaCorrection;

        SetStatus(DllExports::GdipGetPathGradientGammaCorrection(
            (GpPathGradient*)hBrush, &useGammaCorrection));

        return useGammaCorrection;
    }
	//@别名 取混合数()
    INT GetBlendCount() 
    {
       INT count = 0;

       SetStatus(DllExports::GdipGetPathGradientBlendCount(
                           (GpPathGradient*) hBrush, &count));

       return count;
    }
	//@别名 取混合()
    Status GetBlend(__out REAL* blendFactors,
                    __out REAL* blendPositions,
                    __in INT count) 
    {
        return SetStatus(DllExports::GdipGetPathGradientBlend(
                            (GpPathGradient*)hBrush,
                            blendFactors, blendPositions, count));
    }
	//@别名 置混合()
    Status SetBlend(__in const REAL* blendFactors, 
                    __in const REAL* blendPositions, 
                    __in INT count)
    {
        return SetStatus(DllExports::GdipSetPathGradientBlend(
                            (GpPathGradient*)hBrush,
                            blendFactors, blendPositions, count));
    }
	//@别名 取预设颜色数()
    INT GetInterpolationColorCount() 
    {
       INT count = 0;

       SetStatus(DllExports::GdipGetPathGradientPresetBlendCount(
                        (GpPathGradient*) hBrush, &count));

       return count;
    }
	//@别名 置预设颜色()
    Status SetInterpolationColors(__in const Color* presetColors,
                                  __in const REAL* blendPositions, 
                                  __in INT count)
    {
        if ((count <= 0) || !presetColors) 
        {
            return SetStatus(InvalidParameter);
        }

        ARGB* argbs = (ARGB*) new ARGB[count];
        if(argbs)
        {
            for(INT i = 0; i < count; i++)
            {
                argbs[i] = presetColors[i].GetValue();
            }

            Status status = SetStatus(DllExports::
                               GdipSetPathGradientPresetBlend(
                                    (GpPathGradient*) hBrush,
                                    argbs,
                                    blendPositions,
                                    count));
            delete[] argbs;
            return status;
        }
        else
        {
            return SetStatus(OutOfMemory);
        }
    }
	//@别名 取预设颜色()
    Status GetInterpolationColors(__out Color* presetColors,
                                  __out REAL* blendPositions, 
                                  __in INT count) 
    {
        if ((count <= 0) || !presetColors) 
        {
            return SetStatus(InvalidParameter);
        }

        ARGB* argbs = (ARGB*) new ARGB[count];
        
        if (!argbs)
        {
            return SetStatus(OutOfMemory);
        }

        GpStatus status = SetStatus(DllExports::GdipGetPathGradientPresetBlend(
                                (GpPathGradient*)hBrush,
                                argbs,
                                blendPositions,
                                count));
        
        for(INT i = 0; i < count; i++)
        {
            presetColors[i] = Color(argbs[i]);
        }
        delete [] argbs;
        
        return status;
    }
	//@别名 置钟形混合()
    Status SetBlendBellShape(__in REAL focus, 
                             __in REAL scale = 1.0)
    {
        return SetStatus(DllExports::GdipSetPathGradientSigmaBlend(
                            (GpPathGradient*)hBrush, focus, scale));
    }
	//@别名 置线性混合()
    Status SetBlendTriangularShape(
        __in REAL focus,
        __in REAL scale = 1.0
    )
    {
        return SetStatus(DllExports::GdipSetPathGradientLinearBlend(
                            (GpPathGradient*)hBrush, focus, scale));
    }
	//@别名 取矩阵()
    Status GetTransform(__out GPMatrix *matrix) 
    {
        return SetStatus(DllExports::GdipGetPathGradientTransform(
                            (GpPathGradient*) hBrush, 
                            matrix->hMatrix));
    }
	//@别名 置矩阵()
    Status SetTransform(__in const GPMatrix* matrix)
    {
        return SetStatus(DllExports::GdipSetPathGradientTransform(
                            (GpPathGradient*) hBrush, 
                            matrix->hMatrix));
    }
	//@别名 矩阵重置()
    Status ResetTransform()
    {
        return SetStatus(DllExports::GdipResetPathGradientTransform(
                            (GpPathGradient*)hBrush));
    }
	//@别名 矩阵相乘()
    Status MultiplyTransform(__in const GPMatrix* matrix,
                             __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipMultiplyPathGradientTransform(
                            (GpPathGradient*)hBrush,
                            matrix->hMatrix,
                            order));
    }
	//@别名 矩阵平移()
    Status TranslateTransform(__in REAL dx, 
                              __in REAL dy,
                              __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipTranslatePathGradientTransform(
                            (GpPathGradient*)hBrush,
                            dx, dy, order));
    }
	//@别名 矩阵缩放()
    Status ScaleTransform(__in REAL sx, 
                          __in REAL sy,
                          __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipScalePathGradientTransform(
                            (GpPathGradient*)hBrush,
                            sx, sy, order));
    }
	//@别名 矩阵旋转()
    Status RotateTransform(__in REAL angle, 
                           __in MatrixOrder order = MatrixOrderPrepend)
    {
        return SetStatus(DllExports::GdipRotatePathGradientTransform(
                            (GpPathGradient*)hBrush,
                            angle, order));
    }
	//@别名 取中心点比例()
    Status GetFocusScales(__out REAL* xScale, 
                          __out REAL* yScale) 
    {
        return SetStatus(DllExports::GdipGetPathGradientFocusScales(
                            (GpPathGradient*) hBrush, xScale, yScale));
    }
	//@别名 置中心点比例()
    Status SetFocusScales(__in REAL xScale,
                          __in REAL yScale)
    {
        return SetStatus(DllExports::GdipSetPathGradientFocusScales(
                            (GpPathGradient*) hBrush, xScale, yScale));
    }
	//@别名 取环绕模式()
    WrapMode GetWrapMode() 
    {
        WrapMode wrapMode;

        SetStatus(DllExports::GdipGetPathGradientWrapMode(
                     (GpPathGradient*) hBrush, &wrapMode));

        return wrapMode;
    }
	//@别名 置环绕模式()
    Status SetWrapMode(__in WrapMode wrapMode)
    {
        return SetStatus(DllExports::GdipSetPathGradientWrapMode(
                            (GpPathGradient*) hBrush, wrapMode));
    }

private:
    GPPathGradientBrush(const GPPathGradientBrush &);
    GPPathGradientBrush& operator=(const GPPathGradientBrush &);

protected:

    GPPathGradientBrush()
    {
    }
};
//@分组}
