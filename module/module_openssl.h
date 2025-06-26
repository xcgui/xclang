#ifndef  XC_OPENSSL_H
//@隐藏{
#define  XC_OPENSSL_H

#include "openssl/md5.h"
#include <openssl/rsa.h>
#include "openssl/sha.h"
#include "openssl/core_names.h"
#include <openssl/encoder.h>
#include <openssl/decoder.h>
#include <openssl/pem.h>
#include "openssl/evp.h"

//#pragma comment(lib, "libcrypto-3.lib")
//#pragma warning(disable:4996)
#include "module_base.h"

//@隐藏}

//@模块名称  OpenSSL  
//@版本  3.0.1
//@日期  2022-02-10
//@作者  XCGUI  
//@QQ  154460336
//@模块备注 OpenSSL 3.0.1
//命令手册 https://www.openssl.org/docs/manmaster/man3/
//遇到未添加接口, 自己手动声明下
//@依赖  module_base.h

#if XC_MOUDLE
#pragma comment(lib, "libcrypto-3.lib")
#endif

#ifdef  _WIN64
//@lib  "x64\libcrypto-3.lib"
//@复制文件 @当前模块路径 "x64\libcrypto-3-x64.dll"
#else
//@lib  "x86\libcrypto-3.lib"
//@复制文件 @当前模块路径 "x86\libcrypto-3.dll"
#endif


/*@声明
@src  "module_openssl.cpp"

#define EVP_MAX_MD_SIZE                 64
#define EVP_MAX_KEY_LENGTH              64
#define EVP_MAX_IV_LENGTH               16
#define EVP_MAX_BLOCK_LENGTH            32

#define OSSL_KEYMGMT_SELECT_PRIVATE_KEY            0x01
#define OSSL_KEYMGMT_SELECT_PUBLIC_KEY             0x02
#define OSSL_KEYMGMT_SELECT_DOMAIN_PARAMETERS      0x04
#define OSSL_KEYMGMT_SELECT_OTHER_PARAMETERS       0x80

# define RSA_PKCS1_PADDING          1
# define RSA_NO_PADDING             3
# define RSA_PKCS1_OAEP_PADDING     4
# define RSA_X931_PADDING           5

# define RSA_PKCS1_PSS_PADDING      6
# define RSA_PKCS1_WITH_TLS_PADDING 7

# define RSA_PKCS1_PADDING_SIZE    11

struct EVP_MD_CTX{};
struct EVP_MD{};
struct EVP_CIPHER{};
struct EVP_PKEY_CTX{};
struct EVP_PKEY{};
struct OSSL_PARAM{};
struct ENGINE{};
struct ASN1_PCTX{};
struct BIO{};
struct BIO_METHOD{};
struct EVP_ENCODE_CTX{};
struct OSSL_ENCODER_CTX{};
struct OSSL_LIB_CTX{};

*/

#ifdef  __cplusplus
extern "C" {
#endif

	//@分组{ base64编码/解码
	
	//@别名  EVP编码上下文_创建()
	EVP_ENCODE_CTX* EVP_ENCODE_CTX_new(void);
	//@别名  EVP编码上下文_释放()
	void EVP_ENCODE_CTX_free(EVP_ENCODE_CTX* ctx);
	//@别名  EVP编码上下文_初始化()
	void EVP_EncodeInit(EVP_ENCODE_CTX* ctx);
	//@别名  EVP编码上下文_编码()
	int  EVP_EncodeUpdate(EVP_ENCODE_CTX* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
	//@别名  EVP编码上下文_完成()
	void EVP_EncodeFinal(EVP_ENCODE_CTX* ctx, unsigned char* out, int* outl);
	//@分组}


//------摘要算法-----------------------------

	//@分组{ 摘要算法
	//@别名  EVP摘要上下文_创建()
	EVP_MD_CTX* EVP_MD_CTX_new(void);
	//@别名  EVP摘要上下文_重置()
	int EVP_MD_CTX_reset(EVP_MD_CTX* ctx);
	//@别名  EVP摘要上下文_释放()
	void EVP_MD_CTX_free(EVP_MD_CTX* ctx);
	//@别名  EVP摘要上下文_控制()
	int EVP_MD_CTX_ctrl(EVP_MD_CTX* ctx, int cmd, int p1, void* p2);
	//@别名  EVP摘要上下文_取参数()
	int EVP_MD_CTX_get_params(EVP_MD_CTX* ctx, OSSL_PARAM params[]);
	//@别名  EVP摘要上下文_置参数()
	int EVP_MD_CTX_set_params(EVP_MD_CTX* ctx, const OSSL_PARAM params[]);

	const OSSL_PARAM* EVP_MD_CTX_settable_params(EVP_MD_CTX* ctx);

	const OSSL_PARAM* EVP_MD_CTX_gettable_params(EVP_MD_CTX* ctx);

	EVP_PKEY_CTX* EVP_MD_CTX_get_pkey_ctx(const EVP_MD_CTX* ctx);
	void EVP_MD_CTX_set_pkey_ctx(EVP_MD_CTX* ctx, EVP_PKEY_CTX* pctx);

	//@别名  EVP摘要_取算法()
	EVP_MD* EVP_MD_fetch(OSSL_LIB_CTX* ctx, const char* algorithm, const char* properties);
	//@别名  EVP摘要_增加引用计数()
	int EVP_MD_up_ref(EVP_MD* md);
	//@别名  EVP摘要_释放()
	void EVP_MDfree(EVP_MD* md);
	//@别名  EVP摘要_取参数()
	int EVP_MD_get_params(const EVP_MD* digest, OSSL_PARAM params[]);

	const OSSL_PARAM* EVP_MD_gettable_params(const EVP_MD* digest);

	const OSSL_PARAM* EVP_MD_settable_ctx_params(const EVP_MD* md);

	const OSSL_PARAM* EVP_MD_gettable_ctx_params(const EVP_MD* md);


	//@别名  EVP摘要_置标志()
	void EVP_MD_CTX_set_flags(EVP_MD_CTX* ctx, int flags);
	//@别名  EVP摘要_清除标志()
	void EVP_MD_CTX_clear_flags(EVP_MD_CTX* ctx, int flags);
	//@别名  EVP摘要_测试标志()
	int EVP_MD_CTX_test_flags(const EVP_MD_CTX* ctx, int flags);
	//@备注  它使用摘要算法名称对数据的数据进行哈希处理，该名称使用可选的 libctx 和 propq 参数获取。摘要值以 md 为单位，如果指针不是 NULL，则其长度写在 mdlen。最多写入EVP_MAX_MD_SIZE字节
	//@别名  EVP摘要_快速()
	int EVP_Q_digest(OSSL_LIB_CTX* libctx, const char* name, const char* propq, const void* data, size_t datalen, unsigned char* md, size_t* mdlen);
	
	int EVP_Digest(const void* data, size_t count, unsigned char* md,
		unsigned int* size, const EVP_MD* type, ENGINE* impl);

	//@别名 EVP摘要算法_初始化2(摘要上下文, 算法实现, 参数)
	int EVP_DigestInit_ex2(EVP_MD_CTX* ctx, const EVP_MD* type, const OSSL_PARAM params[]);
	//@别名 EVP摘要算法_初始化(摘要上下文, 算法实现, 第三方实现)
	int EVP_DigestInit_ex(EVP_MD_CTX* ctx, const EVP_MD* type, ENGINE* impl);
	//@别名 EVP摘要算法_计算(摘要上下文, 数据, 长度)
	int EVP_DigestUpdate(EVP_MD_CTX* ctx, const void* d, size_t cnt);
	//@别名 EVP摘要算法_完成(摘要上下文, 返回数据, 返回长度)
	int EVP_DigestFinal_ex(EVP_MD_CTX* ctx, unsigned char* md, unsigned int* s);

	int EVP_DigestFinalXOF(EVP_MD_CTX* ctx, unsigned char* md, size_t len);

	int EVP_DigestInit(EVP_MD_CTX* ctx, const EVP_MD* type);
	int EVP_DigestFinal(EVP_MD_CTX* ctx, unsigned char* md, unsigned int* s);

	EVP_MD_CTX* EVP_MD_CTX_dup(const EVP_MD_CTX* in);
	int EVP_MD_CTX_copy_ex(EVP_MD_CTX* out, const EVP_MD_CTX* in);
	int EVP_MD_CTX_copy(EVP_MD_CTX* out, const EVP_MD_CTX* in);
	//@备注  返回给定消息摘要的名称。对于具有多个名称的已提取消息摘要，仅返回其中一个;
	//@别名  EVP摘要_取算法名()
	const char* EVP_MD_get0_name(const EVP_MD* md);
	//@备注  返回摘要的说明，用于显示和人类使用。描述由摘要实现自行决定
	//@别名  EVP摘要_取算法描述()
	const char* EVP_MD_get0_description(const EVP_MD* md);
	//@备注  如果 md 是可用 name 标识的算法的实现，则返回 1，否则为 0
	//如果 md 是旧版摘要（它是来自 EVP_sha256（） 等的返回值，而不是 EVP_MD_fetch（）的结果），则只会考虑在默认库上下文中注册的密码名称
	//@别名  EVP摘要_是否可用算法(算法实现, 算法名称)
	int EVP_MD_is_a(const EVP_MD* md, const char* name);
	int EVP_MD_names_do_all(const EVP_MD* md, void (*fn)(const char* name, void* data), void* data);
	const OSSL_PROVIDER* EVP_MD_get0_provider(const EVP_MD* md);
	int EVP_MD_get_type(const EVP_MD* md);
	int EVP_MD_get_pkey_type(const EVP_MD* md);
	//@备注 返回传递EVP_MD或EVP_MD_CTX结构时消息摘要的大小，即哈希的大小
	//@别名 EVP摘要_取大小()
	int EVP_MD_get_size(const EVP_MD* md);
	//@备注 返回传递EVP_MD或EVP_MD_CTX结构时消息摘要的块大小
	//@别名 EVP摘要_取块大小()
	int EVP_MD_get_block_size(const EVP_MD* md);
	unsigned long EVP_MD_get_flags(const EVP_MD* md);

	const EVP_MD* EVP_MD_CTX_get0_md(const EVP_MD_CTX* ctx);
	EVP_MD* EVP_MD_CTX_get1_md(EVP_MD_CTX* ctx);
	//# define const char* EVP_MD_CTX_get0_name(const EVP_MD_CTX* ctx);
	//# define int EVP_MD_CTX_get_size(const EVP_MD_CTX* ctx);
	//# define int EVP_MD_CTX_get_block_size(const EVP_MD_CTX* ctx);
	//# define int EVP_MD_CTX_get_type(const EVP_MD_CTX* ctx);
	//@备注 返回传递的EVP_MD_CTX的摘要方法私有数据。该空间由 OpenSSL 分配，其大小最初设置为 EVP_MD_meth_set_app_datasize()
	void* EVP_MD_CTX_get0_md_data(const EVP_MD_CTX* ctx);

	const EVP_MD* EVP_md_null(void);
	//@备注 函数的存在是为了在版本 3 之前与 OpenSSL 向后兼容，并且与 EVP_MD_fetch（） 函数不同，因为它不尝试"获取"密码的实现。此外，它只知道 OpenSSL 内置并具有关联 NID 的摘要。同样，EVP_get_digestbynid（） 和 EVP_get_digestbyobj（） 也会返回没有关联实现的对象
	//@别名 EVP摘要_从名称(算法名称)
	const EVP_MD* EVP_get_digestbyname(const char* name);
	//# define	const EVP_MD* EVP_get_digestbynid(int type);
	//# define	const EVP_MD* EVP_get_digestbyobj(const ASN1_OBJECT* o);
	//@备注 遍历由给定库上下文 libctx 中所有激活的提供程序实现的所有消息摘要，并针对每个实现，使用实现方法和给定的 arg 作为参数调用给定函数 fn
	//@别名 EVP摘要_遍历()
	void EVP_MD_do_all_provided(OSSL_LIB_CTX* libctx, void (*fn)(EVP_MD* mac, void* arg), void* arg);

#define EVP_MD_type EVP_MD_get_type
#define EVP_MD_nid EVP_MD_get_type
#define EVP_MD_name EVP_MD_get0_name
#define EVP_MD_pkey_type EVP_MD_get_pkey_type
#define EVP_MD_size EVP_MD_get_size
#define EVP_MD_block_size EVP_MD_get_block_size
#define EVP_MD_flags EVP_MD_get_flags
#define EVP_MD_CTX_size EVP_MD_CTX_get_size
#define EVP_MD_CTX_block_size EVP_MD_CTX_get_block_size
#define EVP_MD_CTX_type EVP_MD_CTX_get_type
#define EVP_MD_CTX_pkey_ctx EVP_MD_CTX_get_pkey_ctx
#define EVP_MD_CTX_md_data EVP_MD_CTX_get0_md_data
	//@分组}


		//-----------------------------------加解密,对称算法
	//@分组{  加解密

	//@别名  EVP加解密上下文_创建()
	EVP_CIPHER_CTX* EVP_CIPHER_CTX_new(void);
	//@别名  EVP加解密上下文_重置()
	int EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX* ctx);
	//@别名  EVP加解密上下文_释放()
	void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX* ctx);
	EVP_CIPHER_CTX* EVP_CIPHER_CTX_dup(const EVP_CIPHER_CTX* in);

	int EVP_CIPHER_CTX_copy(EVP_CIPHER_CTX* out, const EVP_CIPHER_CTX* in);
	//@别名  EVP加解密上下文_置填充方式()
	int EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX* x, int padding);
	int EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX* x, int keylen);
	int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX* ctx, int cmd, int p1, void* p2);
	int EVP_CIPHER_CTX_rand_key(EVP_CIPHER_CTX* ctx, unsigned char* key);
	void EVP_CIPHER_CTX_set_flags(EVP_CIPHER_CTX* ctx, int flags);
	void EVP_CIPHER_CTX_clear_flags(EVP_CIPHER_CTX* ctx, int flags);
	int EVP_CIPHER_CTX_test_flags(const EVP_CIPHER_CTX* ctx, int flags);

	//@别名  EVP加解密_取算法()
	EVP_CIPHER* EVP_CIPHER_fetch(OSSL_LIB_CTX* ctx, const char* algorithm, const char* properties);

	int EVP_CIPHER_up_ref(EVP_CIPHER* cipher);
	//@别名  EVP加解密_释放()
	void EVP_CIPHER_free(EVP_CIPHER* cipher);

	//@别名  EVP加密_初始化(加解密上下文,算法实现, 第三方引擎, 密钥, 向量)
	int EVP_EncryptInit_ex(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,	ENGINE* impl, const unsigned char* key, const unsigned char* iv);
	//@别名  EVP加密_初始化2(加解密上下文, 算法实现, 密钥, 向量, 参数)
	int EVP_EncryptInit_ex2(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,const unsigned char* key, const unsigned char* iv, const OSSL_PARAM params[]);
	//@别名  EVP加密_计算(加解密上下文, 接收数据, 接收长度, 输入数据, 输入长度)
	int EVP_EncryptUpdate(EVP_CIPHER_CTX* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
	//@别名  EVP加密_完成(加解密上下文, 接收数据, 接收长度)
	int EVP_EncryptFinal_ex(EVP_CIPHER_CTX* ctx, unsigned char* out, int* outl);
	
	//@别名  EVP解密_初始化(加解密上下文,算法实现, 第三方引擎, 密钥, 向量)
	int EVP_DecryptInit_ex(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,	ENGINE* impl, const unsigned char* key, const unsigned char* iv);
	//@别名  EVP解密_初始化2(加解密上下文, 算法实现, 密钥, 向量, 参数)
	int EVP_DecryptInit_ex2(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type, const unsigned char* key, const unsigned char* iv, const OSSL_PARAM params[]);
	//@别名  EVP解密_计算(加解密上下文, 接收数据, 接收长度, 输入数据, 输入长度)
	int EVP_DecryptUpdate(EVP_CIPHER_CTX* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
	//@别名  EVP解密_完成(加解密上下文, 接收数据, 接收长度)
	int EVP_DecryptFinal_ex(EVP_CIPHER_CTX* ctx, unsigned char* outm, int* outl);

	//@别名  EVP加解密_初始化(加解密上下文,算法实现, 第三方引擎, 密钥, 向量)
	int EVP_CipherInit_ex(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,ENGINE* impl, const unsigned char* key, const unsigned char* iv, int enc);
	//@别名  EVP加解密_初始化2(加解密上下文, 算法实现, 密钥, 向量, 参数)
	int EVP_CipherInit_ex2(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,	const unsigned char* key, const unsigned char* iv,int enc, const OSSL_PARAM params[]);
	//@别名  EVP加解密_计算(加解密上下文, 接收数据, 接收长度, 输入数据, 输入长度)
	int EVP_CipherUpdate(EVP_CIPHER_CTX* ctx, unsigned char* out,int* outl, const unsigned char* in, int inl);
	//@别名  EVP加解密_完成(加解密上下文, 接收数据, 接收长度)
	int EVP_CipherFinal_ex(EVP_CIPHER_CTX* ctx, unsigned char* outm, int* outl);

	int EVP_EncryptInit(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type, const unsigned char* key, const unsigned char* iv);
	int EVP_EncryptFinal(EVP_CIPHER_CTX* ctx, unsigned char* out, int* outl);

	int EVP_DecryptInit(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type, const unsigned char* key, const unsigned char* iv);
	int EVP_DecryptFinal(EVP_CIPHER_CTX* ctx, unsigned char* outm, int* outl);

	int EVP_CipherInit(EVP_CIPHER_CTX* ctx, const EVP_CIPHER* type,	const unsigned char* key, const unsigned char* iv, int enc);
	int EVP_CipherFinal(EVP_CIPHER_CTX* ctx, unsigned char* outm, int* outl);

	int EVP_Cipher(EVP_CIPHER_CTX* ctx, unsigned char* out,	const unsigned char* in, unsigned int inl);
	
	//@别名  EVP_取算法(算法名称)
	const EVP_CIPHER* EVP_get_cipherbyname(const char* name);
	//# define	const EVP_CIPHER* EVP_get_cipherbynid(int nid);
	//# define	const EVP_CIPHER* EVP_get_cipherbyobj(const ASN1_OBJECT* a);

	int EVP_CIPHER_get_nid(const EVP_CIPHER* e);
	//@别名  EVP加解密_是否可用(算法结构, 算法名称)
	int EVP_CIPHER_is_a(const EVP_CIPHER* cipher, const char* name);
	int EVP_CIPHER_names_do_all(const EVP_CIPHER* cipher,void (*fn)(const char* name, void* data),void* data);
	
	//@别名  EVP加解密_取名称()
	const char* EVP_CIPHER_get0_name(const EVP_CIPHER* cipher);
	//@别名  EVP加解密_取描述()
	const char* EVP_CIPHER_get0_description(const EVP_CIPHER* cipher);
	const OSSL_PROVIDER* EVP_CIPHER_get0_provider(const EVP_CIPHER* cipher);
	//@别名  EVP加解密_取块大小()
	int EVP_CIPHER_get_block_size(const EVP_CIPHER* e);
	//@别名  EVP加解密_取密钥长度()
	int EVP_CIPHER_get_key_length(const EVP_CIPHER* e);
	//@别名  EVP加解密_取向量长度()
	int EVP_CIPHER_get_iv_length(const EVP_CIPHER* e);
	unsigned long EVP_CIPHER_get_flags(const EVP_CIPHER* e);
	int EVP_CIPHER_get_mode(const EVP_CIPHER* e);
	int EVP_CIPHER_get_type(const EVP_CIPHER* cipher);

	const EVP_CIPHER* EVP_CIPHER_CTX_get0_cipher(const EVP_CIPHER_CTX* ctx);
	EVP_CIPHER* EVP_CIPHER_CTX_get1_cipher(EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_nid(const EVP_CIPHER_CTX* ctx);

	//	#define EVP_CIPHER_CTX_get0_name //const char* EVP_CIPHER_CTX_get0_name(const EVP_CIPHER_CTX* ctx);

	int EVP_CIPHER_get_params(EVP_CIPHER* cipher, OSSL_PARAM params[]);
	int EVP_CIPHER_CTX_set_params(EVP_CIPHER_CTX* ctx, const OSSL_PARAM params[]);
	int EVP_CIPHER_CTX_get_params(EVP_CIPHER_CTX* ctx, OSSL_PARAM params[]);
	const OSSL_PARAM* EVP_CIPHER_gettable_params(const EVP_CIPHER* cipher);
	const OSSL_PARAM* EVP_CIPHER_settable_ctx_params(const EVP_CIPHER* cipher);
	const OSSL_PARAM* EVP_CIPHER_gettable_ctx_params(const EVP_CIPHER* cipher);
	const OSSL_PARAM* EVP_CIPHER_CTX_settable_params(EVP_CIPHER_CTX* ctx);
	const OSSL_PARAM* EVP_CIPHER_CTX_gettable_params(EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_block_size(const EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_key_length(const EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_iv_length(const EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_tag_length(const EVP_CIPHER_CTX* ctx);
	void* EVP_CIPHER_CTX_get_app_data(const EVP_CIPHER_CTX* ctx);
	void EVP_CIPHER_CTX_set_app_data(EVP_CIPHER_CTX* ctx, void* data);
	//	#define int EVP_CIPHER_CTX_get_type(const EVP_CIPHER_CTX* ctx);
	//	#define	int EVP_CIPHER_CTX_get_mode(const EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_get_num(const EVP_CIPHER_CTX* ctx);
	int EVP_CIPHER_CTX_set_num(EVP_CIPHER_CTX* ctx, int num);
	int EVP_CIPHER_CTX_is_encrypting(const EVP_CIPHER_CTX* ctx);

	int EVP_CIPHER_param_to_asn1(EVP_CIPHER_CTX* c, ASN1_TYPE* type);
	int EVP_CIPHER_asn1_to_param(EVP_CIPHER_CTX* c, ASN1_TYPE* type);

	void EVP_CIPHER_do_all_provided(OSSL_LIB_CTX* libctx,
		void (*fn)(EVP_CIPHER* cipher, void* arg),
		void* arg);

#define EVP_CIPHER_nid EVP_CIPHER_get_nid
#define EVP_CIPHER_name EVP_CIPHER_get0_name
#define EVP_CIPHER_block_size EVP_CIPHER_get_block_size
#define EVP_CIPHER_key_length EVP_CIPHER_get_key_length
#define EVP_CIPHER_iv_length EVP_CIPHER_get_iv_length
#define EVP_CIPHER_flags EVP_CIPHER_get_flags
#define EVP_CIPHER_mode EVP_CIPHER_get_mode
#define EVP_CIPHER_type EVP_CIPHER_get_type
#define EVP_CIPHER_CTX_encrypting EVP_CIPHER_CTX_is_encrypting
#define EVP_CIPHER_CTX_nid EVP_CIPHER_CTX_get_nid
#define EVP_CIPHER_CTX_block_size EVP_CIPHER_CTX_get_block_size
#define EVP_CIPHER_CTX_key_length EVP_CIPHER_CTX_get_key_length
#define EVP_CIPHER_CTX_iv_length EVP_CIPHER_CTX_get_iv_length
#define EVP_CIPHER_CTX_tag_length EVP_CIPHER_CTX_get_tag_length
#define EVP_CIPHER_CTX_num EVP_CIPHER_CTX_get_num
#define EVP_CIPHER_CTX_type EVP_CIPHER_CTX_get_type
#define EVP_CIPHER_CTX_mode EVP_CIPHER_CTX_get_mode

	//@分组}

		//---------------------------------------------------非对称算法
	//@分组{ 非对称算法

	//@别名  EVP非对称上下文_创建()
	EVP_PKEY_CTX* EVP_PKEY_CTX_new(EVP_PKEY* pkey, ENGINE* e);
	//@别名  EVP非对称上下文_创建ID()
	EVP_PKEY_CTX* EVP_PKEY_CTX_new_id(int id, ENGINE* e);
	//@别名  EVP非对称上下文_创建从名称()
	EVP_PKEY_CTX* EVP_PKEY_CTX_new_from_name(OSSL_LIB_CTX* libctx,const char* name,	const char* propquery);
	//@别名  EVP非对称上下文_创建从密钥()
	EVP_PKEY_CTX* EVP_PKEY_CTX_new_from_pkey(OSSL_LIB_CTX* libctx,EVP_PKEY* pkey,const char* propquery);
	EVP_PKEY_CTX* EVP_PKEY_CTX_dup(const EVP_PKEY_CTX* ctx);
	//@别名  EVP非对称上下文_释放()
	void EVP_PKEY_CTX_free(EVP_PKEY_CTX* ctx);
	//@别名  EVP非对称上下文_是否可用()
	int EVP_PKEY_CTX_is_a(EVP_PKEY_CTX* ctx, const char* keytype);
	//@别名  EVP非对称上下文_置RSA填充方式()
	int EVP_PKEY_CTX_set_rsa_padding(EVP_PKEY_CTX* ctx, int pad_mode);
	//@别名  EVP非对称上下文_取RSA填充方式()
	int EVP_PKEY_CTX_get_rsa_padding(EVP_PKEY_CTX* ctx, int* pad_mode);
	//@别名  EVP非对称上下文_置RSA位数()
	int EVP_PKEY_CTX_set_rsa_keygen_bits(EVP_PKEY_CTX* ctx, int bits);

	//密钥
	//@别名  EVP密钥_创建()
	EVP_PKEY* EVP_PKEY_new(void);
	//@别名  EVP密钥_
	void EVP_PKEY_free(EVP_PKEY* pkey);

	int EVP_PKEY_encrypt_init(EVP_PKEY_CTX* ctx);
	int EVP_PKEY_encrypt_init_ex(EVP_PKEY_CTX* ctx, const OSSL_PARAM params[]);
	int EVP_PKEY_encrypt(EVP_PKEY_CTX* ctx,	unsigned char* out, size_t* outlen,	const unsigned char* in, size_t inlen);

	//@别名  EVP密钥_初始化(EVP密钥上下文)
	int EVP_PKEY_decrypt_init(EVP_PKEY_CTX* ctx);
	//@别名  EVP密钥_初始化扩展(EVP密钥上下文, 参数)
	int EVP_PKEY_decrypt_init_ex(EVP_PKEY_CTX* ctx, const OSSL_PARAM params[]);
	//@别名  EVP密钥_解密(EVP密钥上下文, 接收返回数据, 返回长度, 输入数据, 输入长度)
	int EVP_PKEY_decrypt(EVP_PKEY_CTX* ctx,	unsigned char* out, size_t* outlen,	const unsigned char* in, size_t inlen);

	//EVP密钥_从用户数据_初始化()
	int EVP_PKEY_fromdata_init(EVP_PKEY_CTX* ctx);
	//EVP密钥_从用户数据()
	int EVP_PKEY_fromdata(EVP_PKEY_CTX* ctx, EVP_PKEY** ppkey, int selection,OSSL_PARAM params[]);

	const OSSL_PARAM* EVP_PKEY_fromdata_settable(EVP_PKEY_CTX* ctx, int selection);
	//@别名  EVP密钥_打印公钥()
	int EVP_PKEY_print_public(BIO* out, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);
	//@别名  EVP密钥_打印公钥到文件()
	int EVP_PKEY_print_public_fp(FILE* fp, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);
	//@别名  EVP密钥_打印私钥()
	int EVP_PKEY_print_private(BIO* out, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);
	//@别名  EVP密钥_打印私钥到文件()
	int EVP_PKEY_print_private_fp(FILE* fp, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);
	int EVP_PKEY_print_params(BIO* out, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);
	int EVP_PKEY_print_params_fp(FILE* fp, const EVP_PKEY* pkey,int indent, ASN1_PCTX* pctx);

	EVP_PKEY* EVP_PKEY_Q_keygen(OSSL_LIB_CTX* libctx, const char* propq, const char* type, ...);

	//@备注  初始化密钥生成操作的公钥算法上下文 ctx
	//@别名  EVP密钥_生成_初始化()
	int EVP_PKEY_keygen_init(EVP_PKEY_CTX* ctx);
	int EVP_PKEY_paramgen_init(EVP_PKEY_CTX* ctx);
	int EVP_PKEY_generate(EVP_PKEY_CTX* ctx, EVP_PKEY** ppkey);
	int EVP_PKEY_paramgen(EVP_PKEY_CTX* ctx, EVP_PKEY** ppkey);
	//@别名  EVP密钥_生成()
	int EVP_PKEY_keygen(EVP_PKEY_CTX* ctx, EVP_PKEY** ppkey);

	typedef int EVP_PKEY_gen_cb(EVP_PKEY_CTX* ctx);

	void EVP_PKEY_CTX_set_cb(EVP_PKEY_CTX* ctx, EVP_PKEY_gen_cb* cb);
	EVP_PKEY_gen_cb* EVP_PKEY_CTX_get_cb(EVP_PKEY_CTX* ctx);

	int EVP_PKEY_CTX_get_keygen_info(EVP_PKEY_CTX* ctx, int idx);

	void EVP_PKEY_CTX_set_app_data(EVP_PKEY_CTX* ctx, void* data);
	void* EVP_PKEY_CTX_get_app_data(EVP_PKEY_CTX* ctx);

//@分组}

	//@分组{ BIO内存操作

	//@别名 BIO_创建扩展()
	BIO* BIO_new_ex(OSSL_LIB_CTX* libctx, const BIO_METHOD* type);

	//@别名 BIO_创建()
	BIO* BIO_new(const BIO_METHOD* type);
	int  BIO_up_ref(BIO* a);
	//@别名 BIO_释放()
	int  BIO_free(BIO* a);
	void BIO_vfree(BIO* a);
	void BIO_free_all(BIO* a);

	BIO* BIO_new_mem_buf(const void* buf, int len);

	typedef int BIO_info_cb(BIO* b, int state, int res);

	long BIO_ctrl(BIO* bp, int cmd, long larg, void* parg);
	long BIO_callback_ctrl(BIO* b, int cmd, BIO_info_cb* cb);
	void* BIO_ptr_ctrl(BIO* bp, int cmd, long larg);
	long BIO_int_ctrl(BIO* bp, int cmd, long larg, int iarg);
	/*
	# define	int BIO_reset(BIO* b);
	# define	int BIO_seek(BIO* b, int ofs);
	# define	int BIO_tell(BIO* b);
	# define	int BIO_flush(BIO* b);
	# define	int BIO_eof(BIO* b);
	# define	int BIO_set_close(BIO* b, long flag);
	# define	int BIO_get_close(BIO* b);
	# define	int BIO_pending(BIO* b);
	# define	int BIO_wpending(BIO* b);
		*/
	//@别名 BIO_取大小()
	size_t BIO_ctrl_pending(BIO* b);
	size_t BIO_ctrl_wpending(BIO* b);

	//# define	int BIO_get_info_callback(BIO* b, BIO_info_cb** cbp);
	//# define	int BIO_set_info_callback(BIO* b, BIO_info_cb* cb);

	//@别名 BIO_内存方法()
	const BIO_METHOD* BIO_s_mem(void);
	const BIO_METHOD* BIO_s_secmem(void);
	
	/*@声明
	#define BIO_get_mem_data(b,pp)  //long BIO_get_mem_data(BIO* b, char** pp);
	#define BIO_set_mem_buf(b,bm,c) //BIO_set_mem_buf(BIO* b, BUF_MEM* bm, int c);
	#define BIO_get_mem_ptr(b,pp)   //BIO_get_mem_ptr(BIO* b, BUF_MEM** pp);
	#define BIO_set_mem_eof_return(b, v);
		*/

//@分组}


//@分组{  PEM编码转换
	
	//@别名 OSSL编码上下文_创建从密钥()
	OSSL_ENCODER_CTX* OSSL_ENCODER_CTX_new_for_pkey(const EVP_PKEY* pkey, int selection,const char* output_type,
			const char* output_structure,const char* propquery);
	//@别名 OSSL编码上下文_置加密算法
	int OSSL_ENCODER_CTX_set_cipher(OSSL_ENCODER_CTX* ctx,const char* cipher_name,const char* propquery);
	//@别名 OSSL编码上下文_置密码短语()
	int OSSL_ENCODER_CTX_set_passphrase(OSSL_ENCODER_CTX* ctx,const unsigned char* kstr,size_t klen);
	int OSSL_ENCODER_CTX_set_pem_password_cb(OSSL_ENCODER_CTX* ctx,pem_password_cb* cb, void* cbarg);
	int OSSL_ENCODER_CTX_set_passphrase_ui(OSSL_ENCODER_CTX* ctx,const UI_METHOD* ui_method,void* ui_data);
	int OSSL_ENCODER_CTX_set_passphrase_cb(OSSL_ENCODER_CTX* ctx,OSSL_PASSPHRASE_CALLBACK* cb,void* cbarg);

	//@别名 OSSL编码上下文_取数据(OSSL编码上下文, 接收数据地址, 接收长度)
	int OSSL_ENCODER_to_data(OSSL_ENCODER_CTX* ctx, unsigned char** pdata, size_t* pdata_len);
	//@别名 OSSL编码上下文_取数据到BIO(OSSL编码上下文, 接收BIO)
	int OSSL_ENCODER_to_bio(OSSL_ENCODER_CTX* ctx, BIO* out);
	//@别名 OSSL编码上下文_取数据到文件(OSSL编码上下文, 接收文件)
	int OSSL_ENCODER_to_fp(OSSL_ENCODER_CTX* ctx, FILE* fp);

	//@分组}

	//@分组{ 算法实现
	
	const EVP_MD* EVP_md4(void);
	const EVP_MD* EVP_md5(void);
	const EVP_MD* EVP_md5_sha1(void);

	const EVP_MD* EVP_sha1(void);
	const EVP_MD* EVP_sha224(void);
	const EVP_MD* EVP_sha256(void);
	const EVP_MD* EVP_sha384(void);
	const EVP_MD* EVP_sha512(void);
	const EVP_MD* EVP_sha512_224(void);
	const EVP_MD* EVP_sha512_256(void);
	const EVP_MD* EVP_sha3_224(void);
	const EVP_MD* EVP_sha3_256(void);
	const EVP_MD* EVP_sha3_384(void);
	const EVP_MD* EVP_sha3_512(void);
	const EVP_MD* EVP_shake128(void);
	const EVP_MD* EVP_shake256(void);

	const EVP_CIPHER* EVP_aes_128_ecb(void);
	const EVP_CIPHER* EVP_aes_128_cbc(void);
	const EVP_CIPHER* EVP_aes_128_cfb1(void);
	const EVP_CIPHER* EVP_aes_128_cfb8(void);
	const EVP_CIPHER* EVP_aes_128_cfb128(void);
# define EVP_aes_128_cfb EVP_aes_128_cfb128
	const EVP_CIPHER* EVP_aes_128_ofb(void);
	const EVP_CIPHER* EVP_aes_128_ctr(void);
	const EVP_CIPHER* EVP_aes_128_ccm(void);
	const EVP_CIPHER* EVP_aes_128_gcm(void);
	const EVP_CIPHER* EVP_aes_128_xts(void);
	const EVP_CIPHER* EVP_aes_128_wrap(void);
	const EVP_CIPHER* EVP_aes_128_wrap_pad(void);
# ifndef OPENSSL_NO_OCB
	const EVP_CIPHER* EVP_aes_128_ocb(void);
# endif
	const EVP_CIPHER* EVP_aes_192_ecb(void);
	const EVP_CIPHER* EVP_aes_192_cbc(void);
	const EVP_CIPHER* EVP_aes_192_cfb1(void);
	const EVP_CIPHER* EVP_aes_192_cfb8(void);
	const EVP_CIPHER* EVP_aes_192_cfb128(void);
# define EVP_aes_192_cfb EVP_aes_192_cfb128
	const EVP_CIPHER* EVP_aes_192_ofb(void);
	const EVP_CIPHER* EVP_aes_192_ctr(void);
	const EVP_CIPHER* EVP_aes_192_ccm(void);
	const EVP_CIPHER* EVP_aes_192_gcm(void);
	const EVP_CIPHER* EVP_aes_192_wrap(void);
	const EVP_CIPHER* EVP_aes_192_wrap_pad(void);
# ifndef OPENSSL_NO_OCB
	const EVP_CIPHER* EVP_aes_192_ocb(void);
# endif
	const EVP_CIPHER* EVP_aes_256_ecb(void);
	const EVP_CIPHER* EVP_aes_256_cbc(void);
	const EVP_CIPHER* EVP_aes_256_cfb1(void);
	const EVP_CIPHER* EVP_aes_256_cfb8(void);
	const EVP_CIPHER* EVP_aes_256_cfb128(void);
# define EVP_aes_256_cfb EVP_aes_256_cfb128
	const EVP_CIPHER* EVP_aes_256_ofb(void);
	const EVP_CIPHER* EVP_aes_256_ctr(void);
	const EVP_CIPHER* EVP_aes_256_ccm(void);
	const EVP_CIPHER* EVP_aes_256_gcm(void);
	const EVP_CIPHER* EVP_aes_256_xts(void);
	const EVP_CIPHER* EVP_aes_256_wrap(void);
	const EVP_CIPHER* EVP_aes_256_wrap_pad(void);
# ifndef OPENSSL_NO_OCB
	const EVP_CIPHER* EVP_aes_256_ocb(void);
# endif
	const EVP_CIPHER* EVP_aes_128_cbc_hmac_sha1(void);
	const EVP_CIPHER* EVP_aes_256_cbc_hmac_sha1(void);
	const EVP_CIPHER* EVP_aes_128_cbc_hmac_sha256(void);
	const EVP_CIPHER* EVP_aes_256_cbc_hmac_sha256(void);

	const EVP_CIPHER* EVP_des_ecb(void);
	const EVP_CIPHER* EVP_des_ede(void);
	const EVP_CIPHER* EVP_des_ede3(void);
	const EVP_CIPHER* EVP_des_ede_ecb(void);
	const EVP_CIPHER* EVP_des_ede3_ecb(void);
	const EVP_CIPHER* EVP_des_cfb64(void);
#  define EVP_des_cfb EVP_des_cfb64
	const EVP_CIPHER* EVP_des_cfb1(void);
	const EVP_CIPHER* EVP_des_cfb8(void);
	const EVP_CIPHER* EVP_des_ede_cfb64(void);
#  define EVP_des_ede_cfb EVP_des_ede_cfb64
	const EVP_CIPHER* EVP_des_ede3_cfb64(void);
#  define EVP_des_ede3_cfb EVP_des_ede3_cfb64
	const EVP_CIPHER* EVP_des_ede3_cfb1(void);
	const EVP_CIPHER* EVP_des_ede3_cfb8(void);
	const EVP_CIPHER* EVP_des_ofb(void);
	const EVP_CIPHER* EVP_des_ede_ofb(void);
	const EVP_CIPHER* EVP_des_ede3_ofb(void);
	const EVP_CIPHER* EVP_des_cbc(void);
	const EVP_CIPHER* EVP_des_ede_cbc(void);
	const EVP_CIPHER* EVP_des_ede3_cbc(void);
	const EVP_CIPHER* EVP_desx_cbc(void);
	const EVP_CIPHER* EVP_des_ede3_wrap(void);

	//@分组}

#ifdef  __cplusplus
}
#endif


//@分组{  封装算法   封装好的固定加密模式


//@备注  摘要算法
//@返回  返回计算结果
//@别名  openssl_摘要(数据, 数据长度, 算法类型)
CXBytes openssl_md(const char* data, UINT dataLength, const EVP_MD* type);

//@备注  称加密算法的加密或解密操作, 对数据进行加密或解密, 指定加解密算法
//@参数  加密或解密数据
//@参数  数据长度,字节为单位
//@参数  加密密码, 长度可通过 EVP_CIPHER_get_key_length() 获取
//@参数  加密向量, 长度可通过 EVP_CIPHER_get_iv_length() 获取
//@参数  1为加密,0为解密
//@参数  加解密算法方法, 例如: EVP_des_ede_cbc()
//@返回  返回计算结果
//@别名  openssl_加解密(加密数据, 数据长度, key, 向量, 加密或解密, 算法类型)
CXBytes openssl_cipher(const char* data, UINT dataLen, const char* key, const char* iv, int bEncrypt, const EVP_CIPHER* type);

//@备注  RSA生成密钥对, 指定密钥位数
//@返回  返回密钥对
//@别名  openssl_rsa_生成密钥对(密钥位数)
EVP_PKEY* openssl_rsa_keygen(int bits);

//@备注  RSA打印密钥
//@返回  返回打印文本
//@别名  openssl_rsa_key_打印(密钥, 公钥或私钥)
CXTextA  openssl_rsa_key_print(EVP_PKEY* pKey, BOOL bPublic);

//@备注  RSA密钥转换为PEM格式
//@返回  返回PEM密钥文本
//@别名  openssl_rsa_key_pem(密钥, 公钥或私钥, 加密算法名称, 密码短语)
CXTextA openssl_rsa_key_pem(EVP_PKEY* pKey, BOOL bPublic, const char* cipher_name, const char* passphrase);

//@备注  PEM格式转换为密钥
//@返回  返回密钥
//@别名  openssl_rsa_pem_取密钥(数据, 数据长度, 公钥或私钥, 密码短语)
EVP_PKEY* openssl_rsa_pem_getkey(const char* data, UINT dataLen, BOOL bPublic, const char* passphrase);

//@备注  RSA加密数据
//@返回  返回解密结果
//@别名  openssl_rsa_加密(公钥, 数据, 数据长度)
CXBytes openssl_rsa_encrypt(EVP_PKEY* pKey, const char* data, UINT dataLen);

//@备注  RSA解密数据
//@返回  返回解密结果
//@别名  openssl_rsa_解密(私钥, 数据, 数据长度)
CXBytes openssl_rsa_decrypt(EVP_PKEY* pKey, const char* data, UINT dataLen);


//@分组}


//@隐藏{
void test_RSA_KEY(); //官方例子
//@隐藏}

#endif //XC_OPENSSL_H