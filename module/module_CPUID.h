//@模块名称 CPUID
//@版本 0.1.0
//@日期 2022-12-15
//@作者 欧阳逸洛
//@模块备注 x86 CPU检测和特征提取
//注意事项：目前部分汉化，仅研究用途。
//包装源：https://github.com/anrieff/libcpuid
//包装源许可证：https://github.com/anrieff/libcpuid/blob/master/COPYING
//包装源版本：0.6.2

#ifdef _WIN64 //x64
//@lib "x64/libcpuid.lib"
//@复制文件 @当前模块路径 "x64/libcpuid.dll"

#else // x86 
//@lib "x86/libcpuid.lib"
//@复制文件 @当前模块路径 "x86/libcpuid.dll"
#endif

//@隐藏{
#pragma once

#ifdef _WIN64 //x64
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x64/libcpuid.lib")
#endif //XC_MODULE_DEV

#else // x86 
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x86/libcpuid.lib")
#endif //XC_MODULE_DEV
#endif

#include "include/libcpuid.h"

//@隐藏}


/*@声明

//@别名 处理器_供应商
enum cpu_vendor_t {

	//@别名 处理器_供应商_英特尔
	VENDOR_INTEL = 0,

	//@别名 处理器_供应商_超微半导体
	VENDOR_AMD,

	//@别名 处理器_供应商_赛瑞克斯
	VENDOR_CYRIX,

	//@别名 处理器_供应商_NexGen
	VENDOR_NEXGEN,

	//@别名 处理器_供应商_全美达
	VENDOR_TRANSMETA,

	//@别名 处理器_供应商_联华电子公司
	VENDOR_UMC,

	//@别名 处理器_供应商_半人马
	VENDOR_CENTAUR,

	//@别名 处理器_供应商_Rise
	VENDOR_RISE,

	//@别名 处理器_供应商_矽统科技股份有限公司
	VENDOR_SIS,

	//@别名 处理器_供应商_美国国家半导体
	VENDOR_NSC,

	//@别名 处理器_供应商_海光
	VENDOR_HYGON,

	//@别名 处理器_供应商_数量
	NUM_CPU_VENDORS,

	//@别名 处理器_供应商_未知
	VENDOR_UNKNOWN = -1,
} ;
//#define NUM_CPU_VENDORS NUM_CPU_VENDORS

//@别名 处理器_架构
enum cpu_architecture_t {

	//@别名 处理器_架构_X86
	ARCHITECTURE_X86 = 0,

	//@别名 处理器_架构_ARM
	ARCHITECTURE_ARM,

	//@别名 处理器_架构_数量
	NUM_CPU_ARCHITECTURES,

	//@别名 处理器_架构_未知
	ARCHITECTURE_UNKNOWN = -1,

} ;
//#define NUM_CPU_ARCHITECTURES NUM_CPU_ARCHITECTURES

//@别名 处理器_用途
enum cpu_purpose_t {

	//@别名 处理器_用途_通用
	PURPOSE_GENERAL = 0,
	
	//@别名 处理器_用途_性能
	PURPOSE_PERFORMANCE,
	
	//@别名 处理器_用途_效率
	PURPOSE_EFFICIENCY,
	
	//@别名 处理器_用途_数量
	NUM_CPU_PURPOSES,
} ;
//#define NUM_CPU_PURPOSES NUM_CPU_PURPOSES

//@别名 虚拟机供应商程序
enum hypervisor_vendor_t{
	
	//@别名 虚拟机供应商程序_无
	HYPERVISOR_NONE = 0,
	
	//@别名 虚拟机供应商程序_Bhyve
	HYPERVISOR_BHYVE,
	
	//@别名 虚拟机供应商程序_HyperV
	HYPERVISOR_HYPERV,
	
	//@别名 虚拟机供应商程序_KVM
	HYPERVISOR_KVM,
	
	//@别名 虚拟机供应商程序_Parallels
	HYPERVISOR_PARALLELS,
	
	//@别名 虚拟机供应商程序_QEMU
	HYPERVISOR_QEMU,
	
	//@别名 虚拟机供应商程序_VirtualBox
	HYPERVISOR_VIRTUALBOX,
	
	//@别名 虚拟机供应商程序_VMware
	HYPERVISOR_VMWARE,
	
	//@别名 虚拟机供应商程序_Xen 
	HYPERVISOR_XEN,
	
	//@别名 虚拟机供应商程序_数量
	NUM_HYPERVISOR_VENDORS,
	
	//@别名 虚拟机供应商程序_未知
	HYPERVISOR_UNKNOWN = -1,
} ;
//#define NUM_HYPERVISOR_VENDORS NUM_HYPERVISOR_VENDORS

//@别名 处理器_原始数据
struct cpu_raw_data_t {

	uint32_t basic_cpuid[MAX_CPUID_LEVEL][NUM_REGS];


	uint32_t ext_cpuid[MAX_EXT_CPUID_LEVEL][NUM_REGS];


	uint32_t intel_fn4[MAX_INTELFN4_LEVEL][NUM_REGS];


	uint32_t intel_fn11[MAX_INTELFN11_LEVEL][NUM_REGS];


	uint32_t intel_fn12h[MAX_INTELFN12H_LEVEL][NUM_REGS];


	uint32_t intel_fn14h[MAX_INTELFN14H_LEVEL][NUM_REGS];


	uint32_t amd_fn8000001dh[MAX_AMDFN8000001DH_LEVEL][NUM_REGS];
};

//@别名 处理器_原始数据数组
struct cpu_raw_data_array_t {

	bool with_affinity;


	logical_cpu_t num_raw;


	struct cpu_raw_data_t* raw;
};

//@别名 处理器_软件保护扩展
struct cpu_sgx_t {

	//@别名 是否支持
	uint32_t present;

	//@别名 最大Enclave大小_32位
	uint8_t max_enclave_32bit;

	//@别名 最大Enclave大小_64位
	uint8_t max_enclave_64bit;

	//@别名 标志
	uint8_t flags[SGX_FLAGS_MAX];

	//@别名 Enclave页面缓存数量
	int num_epc_sections;

	//@别名 杂项
	uint32_t misc_select;

	//@别名 Enclave控制结构_属性
	uint64_t secs_attributes;

	//@别名 Enclave控制结构_XSAVE功能请求掩码
	uint64_t secs_xfrm;
};

//@别名 处理器_信息
struct cpu_id_t {

	//@别名 架构
	cpu_architecture_t architecture;

	//@别名 供应商文本
	char vendor_str[VENDOR_STR_MAX];

	//@别名 规格文本
	char brand_str[BRAND_STR_MAX];

	//@别名 供应商
	cpu_vendor_t vendor;

	//@别名 标志
	uint8_t flags[CPU_FLAGS_MAX];

	//@别名 系列
	int32_t family;

	//@别名 型号
	int32_t model;

	//@别名 步进
	int32_t stepping;
	
	//@别名 扩展系列
	int32_t ext_family;

	//@别名 扩展型号
	int32_t ext_model;

	//@别名 核心数
	int32_t num_cores;

	//@别名 逻辑处理器数量
	int32_t num_logical_cpus;

	//@别名  逻辑处理器总数
	int32_t total_logical_cpus;

	//@别名 一级数据缓存
	int32_t l1_data_cache;

	//@别名 一级指令缓存
	int32_t l1_instruction_cache;

	//@别名 二级缓存
	int32_t l2_cache;

	//@别名 三级缓存
	int32_t l3_cache;

	//@别名 四级缓存
	int32_t l4_cache;

	//@别名 一级缓存关联性
	int32_t l1_assoc;

	//@别名 一级数据缓存关联性
	int32_t l1_data_assoc;

	//@别名 一级指令缓存关联性
	int32_t l1_instruction_assoc;

	//@别名 二级缓存关联性
	int32_t l2_assoc;

	//@别名 三级缓存关联性
	int32_t l3_assoc;

	//@别名 四级缓存关联性
	int32_t l4_assoc;

	//@别名 一级缓存行
	int32_t l1_cacheline;

	//@别名 一级数据缓存行
	int32_t l1_data_cacheline;

	//@别名 一级指令缓存行
	int32_t l1_instruction_cacheline;

	//@别名 二级缓存行
	int32_t l2_cacheline;

	//@别名 三级缓存行
	int32_t l3_cacheline;

	//@别名 四级缓存行
	int32_t l4_cacheline;

	//@别名 一级数据缓存实例数
	int32_t l1_data_instances;

	//@别名 一级指令缓存实例数
	int32_t l1_instruction_instances;

	//@别名 二级缓存实例数
	int32_t l2_instances;

	//@别名 三级缓存实例数
	int32_t l3_instances;

	//@别名 四级缓存实例数
	int32_t l4_instances;

	//@别名 代号
	char cpu_codename[64];

	//@别名 SSE执行单元大小
	int32_t sse_size;

	//@别名 检测提示
	uint8_t detection_hints[CPU_HINTS_MAX];

	//@别名 处理器软件保护扩展
	struct cpu_sgx_t sgx;

	//@别名 亲和性掩码
	cpu_affinity_mask_t affinity_mask;

	//@别名 用途
	cpu_purpose_t purpose;
};

//@别名 系统处理器信息
struct system_id_t {

	//@别名 处理器类型数量
	uint8_t num_cpu_types;

	//@别名 处理器类型
	struct cpu_id_t* cpu_types;

	//@别名 一级数据缓存实例总数
	int32_t l1_data_total_instances;

	//@别名 一级指令缓存实例总数
	int32_t l1_instruction_total_instances;

	//@别名 二级缓存实例总数
	int32_t l2_total_instances;

	//@别名 三级缓存实例总数
	int32_t l3_total_instances;

	//@别名 四级缓存实例总数
	int32_t l4_total_instances;
};

//@别名 处理器_特征
enum cpu_feature_t{

    //@别名 处理器_特征_FPU = 0
    CPU_FEATURE_FPU = 0,

	//@别名 处理器_特征_VME
	CPU_FEATURE_VME,

	//@别名 处理器_特征_DE
	CPU_FEATURE_DE,

	//@别名 处理器_特征_PSE
	CPU_FEATURE_PSE,

	//@别名 处理器_特征_TSC
	CPU_FEATURE_TSC,

	//@别名 处理器_特征_MSR
	CPU_FEATURE_MSR,

	//@别名 处理器_特征_PAE
	CPU_FEATURE_PAE,

	//@别名 处理器_特征_MCE
	CPU_FEATURE_MCE,

	//@别名 处理器_特征_CX8
	CPU_FEATURE_CX8,

	//@别名 处理器_特征_APIC
	CPU_FEATURE_APIC,

	//@别名 处理器_特征_MTRR
	CPU_FEATURE_MTRR,

	//@别名 处理器_特征_SEP
	CPU_FEATURE_SEP,

	//@别名 处理器_特征_PGE
	CPU_FEATURE_PGE,

	//@别名 处理器_特征_MCA
	CPU_FEATURE_MCA,

	//@别名 处理器_特征_CMOV
	CPU_FEATURE_CMOV,

	//@别名 处理器_特征_PAT
	CPU_FEATURE_PAT,

	//@别名 处理器_特征_PSE36
	CPU_FEATURE_PSE36,

	//@别名 处理器_特征_PN
	CPU_FEATURE_PN,

	//@别名 处理器_特征_CLFLUSH
	CPU_FEATURE_CLFLUSH,

	//@别名 处理器_特征_DTS
	CPU_FEATURE_DTS,

	//@别名 处理器_特征_ACPI
	CPU_FEATURE_ACPI,

	//@别名 处理器_特征_MMX
	CPU_FEATURE_MMX,

	//@别名 处理器_特征_FXSR
	CPU_FEATURE_FXSR,

	//@别名 处理器_特征_SSE
	CPU_FEATURE_SSE,

	//@别名 处理器_特征_SSE2
	CPU_FEATURE_SSE2,

	//@别名 处理器_特征_SS
	CPU_FEATURE_SS,

	//@别名 处理器_特征_HT
	CPU_FEATURE_HT,
	
	//@别名 处理器_特征_TM
	CPU_FEATURE_TM,
	
	//@别名 处理器_特征_IA64
	CPU_FEATURE_IA64,
	
	//@别名 处理器_特征_PBE
	CPU_FEATURE_PBE,
	
	//@别名 处理器_特征_PNI
	CPU_FEATURE_PNI,
	
	//@别名 处理器_特征_PCLMUL
	CPU_FEATURE_PCLMUL,

	//@别名 处理器_特征_DTS64
	CPU_FEATURE_DTS64,

	//@别名 处理器_特征_MONITOR
	CPU_FEATURE_MONITOR,

	//@别名 处理器_特征_DS_CPL
	CPU_FEATURE_DS_CPL,

	//@别名 处理器_特征_VMX
	CPU_FEATURE_VMX,

	//@别名 处理器_特征_SMX
	CPU_FEATURE_SMX,

	//@别名 处理器_特征_EST
	CPU_FEATURE_EST,

	//@别名 处理器_特征_TM2
	CPU_FEATURE_TM2,

	//@别名 处理器_特征_SSSE3
	CPU_FEATURE_SSSE3,

	//@别名 处理器_特征_CID
	CPU_FEATURE_CID,

	//@别名 处理器_特征_CX16
	CPU_FEATURE_CX16,

	//@别名 处理器_特征_XTPR
	CPU_FEATURE_XTPR,

	//@别名 处理器_特征_PDCM
	CPU_FEATURE_PDCM,

	//@别名 处理器_特征_DCA
	CPU_FEATURE_DCA,

	//@别名 处理器_特征_SSE4_1
	CPU_FEATURE_SSE4_1,

	//@别名 处理器_特征_SSE4_2
	CPU_FEATURE_SSE4_2,

	//@别名 处理器_特征_SYSCALL
	CPU_FEATURE_SYSCALL,

	//@别名 处理器_特征_XD
	CPU_FEATURE_XD,
	
	//@别名 处理器_特征_MOVBE
	CPU_FEATURE_MOVBE,
	
	//@别名 处理器_特征_POPCNT
	CPU_FEATURE_POPCNT,
	
	//@别名 处理器_特征_AES
	CPU_FEATURE_AES,
	
	//@别名 处理器_特征_XSAVE
	CPU_FEATURE_XSAVE,
	
	//@别名 处理器_特征_OSXSAVE
	CPU_FEATURE_OSXSAVE,
	
	//@别名 处理器_特征_AVX
	CPU_FEATURE_AVX,
	
	//@别名 处理器_特征_MMXEXT
	CPU_FEATURE_MMXEXT,
	
	//@别名 处理器_特征_3DNOW
	CPU_FEATURE_3DNOW,
	
	//@别名 处理器_特征_3DNOWEXT
	CPU_FEATURE_3DNOWEXT,
	
	//@别名 处理器_特征_NX
	CPU_FEATURE_NX,
	
	//@别名 处理器_特征_FXSR_OPT
	CPU_FEATURE_FXSR_OPT,
	
	//@别名 处理器_特征_RDTSCP
	CPU_FEATURE_RDTSCP,
	
	//@别名 处理器_特征_LM
	CPU_FEATURE_LM,
	
	//@别名 处理器_特征_LAHF_LM
	CPU_FEATURE_LAHF_LM,
	
	//@别名 处理器_特征_CMP_LEGACY
	CPU_FEATURE_CMP_LEGACY,
	
	//@别名 处理器_特征_SVM
	CPU_FEATURE_SVM,
	
	//@别名 处理器_特征_ABM
	CPU_FEATURE_ABM,
	
	//@别名 处理器_特征_MISALIGNSSE
	CPU_FEATURE_MISALIGNSSE,
	
	//@别名 处理器_特征_SSE4A
	CPU_FEATURE_SSE4A,
	
	//@别名 处理器_特征_3DNOWPREFETCH
	CPU_FEATURE_3DNOWPREFETCH,
	
	//@别名 处理器_特征_OSVW
	CPU_FEATURE_OSVW,
	
	//@别名 处理器_特征_IBS
	CPU_FEATURE_IBS,
	
	//@别名 处理器_特征_SSE5
	CPU_FEATURE_SSE5,
	
	//@别名 处理器_特征_SKINIT
	CPU_FEATURE_SKINIT,
	
	//@别名 处理器_特征_WDT
	CPU_FEATURE_WDT,
	
	//@别名 处理器_特征_TS
	CPU_FEATURE_TS,
	
	//@别名 处理器_特征_FID
	CPU_FEATURE_FID,
	
	//@别名 处理器_特征_VID
	CPU_FEATURE_VID,
	
	//@别名 处理器_特征_TTP
	CPU_FEATURE_TTP,
	
	//@别名 处理器_特征_TM_AMD
	CPU_FEATURE_TM_AMD,
	
	//@别名 处理器_特征_STC
	CPU_FEATURE_STC,
	
	//@别名 处理器_特征_100MHZSTEPS
	CPU_FEATURE_100MHZSTEPS,
	
	//@别名 处理器_特征_HWPSTATE
	CPU_FEATURE_HWPSTATE,
	
	//@别名 处理器_特征_CONSTANT_TSC
	CPU_FEATURE_CONSTANT_TSC,
	
	//@别名 处理器_特征_XOP
	CPU_FEATURE_XOP,
	
	//@别名 处理器_特征_FMA3
	CPU_FEATURE_FMA3,
	
	//@别名 处理器_特征_FMA4
	CPU_FEATURE_FMA4,
	
	//@别名 处理器_特征_TBM
	CPU_FEATURE_TBM,
	
	//@别名 处理器_特征_F16C
	CPU_FEATURE_F16C,
	
	//@别名 处理器_特征_RDRAND
	CPU_FEATURE_RDRAND,
	
	//@别名 处理器_特征_X2APIC
	CPU_FEATURE_X2APIC,
	
	//@别名 处理器_特征_CPB
	CPU_FEATURE_CPB,
	
	//@别名 处理器_特征_APERFMPERF
	CPU_FEATURE_APERFMPERF,
	
	//@别名 处理器_特征_PFI
	CPU_FEATURE_PFI,
	
	//@别名 处理器_特征_PA
	CPU_FEATURE_PA,
	
	//@别名 处理器_特征_AVX2
	CPU_FEATURE_AVX2,
	
	//@别名 处理器_特征_BMI1
	CPU_FEATURE_BMI1,
	
	//@别名 处理器_特征_BMI2
	CPU_FEATURE_BMI2,
	
	//@别名 处理器_特征_HLE
	CPU_FEATURE_HLE,
	
	//@别名 处理器_特征_RTM
	CPU_FEATURE_RTM,
	
	//@别名 处理器_特征_AVX512F
	CPU_FEATURE_AVX512F,
	
	//@别名 处理器_特征_AVX512DQ
	CPU_FEATURE_AVX512DQ,
	
	//@别名 处理器_特征_AVX512PF
	CPU_FEATURE_AVX512PF,
	
	//@别名 处理器_特征_AVX512ER
	CPU_FEATURE_AVX512ER,
	
	//@别名 处理器_特征_AVX512CD
	CPU_FEATURE_AVX512CD,
	
	//@别名 处理器_特征_SHA_NI
	CPU_FEATURE_SHA_NI,
	
	//@别名 处理器_特征_AVX512BW
	CPU_FEATURE_AVX512BW,
	
	//@别名 处理器_特征_AVX512VL
	CPU_FEATURE_AVX512VL,
	
	//@别名 处理器_特征_SGX
	CPU_FEATURE_SGX,
	
	//@别名 处理器_特征_RDSEED
	CPU_FEATURE_RDSEED,
	
	//@别名 处理器_特征_ADX
	CPU_FEATURE_ADX,
	
	//@别名 处理器_特征_AVX512VNNI
	CPU_FEATURE_AVX512VNNI,
	
	//@别名 处理器_特征_AVX512VBMI
	CPU_FEATURE_AVX512VBMI,
	
	//@别名 处理器_特征_AVX512VBMI2
	CPU_FEATURE_AVX512VBMI2,
	
	//@别名 处理器_特征_HYPERVISOR
	CPU_FEATURE_HYPERVISOR,
	
	//@别名 处理器_特征_数量
	NUM_CPU_FEATURES,
} ;

//@别名 处理器_检测提示标识符
enum cpu_hint_t{

	//@别名 处理器_检测提示_SSE单位大小
	CPU_HINT_SSE_SIZE_AUTH = 0,

	//@别名 处理器_检测提示数量
	NUM_CPU_HINTS,
} ;


//@别名 处理器_软件保护扩展特征
enum cpu_sgx_feature_t{

	//@别名 英特尔_软件保护扩展1
	INTEL_SGX1,

	//@别名 英特尔_软件保护扩展2
	INTEL_SGX2,

	//@别名 处理器_软件保护扩展特征_数量
	NUM_SGX_FEATURES,
} ;

//@别名 处理器_错误
enum cpu_error_t {

	//@别名 处理器_错误_无
	ERR_OK = 0,

	//@别名 处理器_错误_不支持CPUID
	ERR_NO_CPUID = -1,

	//@别名 处理器_错误_不支持RDTSC
	ERR_NO_RDTSC = -2,

	//@别名 处理器_错误_内存分配失败
	ERR_NO_MEM = -3,

	//@别名 处理器_错误_文件打开失败
	ERR_OPEN = -4,

	//@别名 处理器_错误_文件格式错误
	ERR_BADFMT = -5,

	//@别名 处理器_错误_未实现
	ERR_NOT_IMP = -6,

	//@别名 处理器_错误_不支持的CPU
	ERR_CPU_UNKN = -7,

	//@别名 处理器_错误_不支持RDMSR
	ERR_NO_RDMSR = -8,

	//@别名 处理器_错误_RDMSR驱动程序错误
	ERR_NO_DRIVER = -9,

	//@别名 处理器_错误_没有权限安装RDMSR驱动程序
	ERR_NO_PERMS = -10,

	//@别名 处理器_错误_无法提取RDMSR驱动程序
	ERR_EXTRACT = -11,

	//@别名 处理器_错误_错误句柄
	ERR_HANDLE = -12,

	//@别名 处理器_错误_无效的MSR
	ERR_INVMSR = -13,

	//@别名 处理器_错误_无效核心号
	ERR_INVCNB = -14,

	//@别名 处理器_错误_句柄读取错误
	ERR_HANDLE_R = -15,

	//@别名 处理器_错误_给定范围无效
	ERR_INVRANGE = -16,

	//@别名 处理器_错误_未找到请求的类型
	ERR_NOT_FOUND = -17,

} ;

//@别名 处理器_标记
struct cpu_mark_t {

	//@别名 RDTSC时间戳
	uint64_t tsc;

	//@别名 系统时钟
	uint64_t sys_clock;
};

//@别名 处理器信息_取逻辑处理器线程数()
int cpuid_get_total_cpus(void);

//@别名 处理器信息_是否支持()
int cpuid_present(void);

//@别名 处理器_执行CPUID指令()
void cpu_exec_cpuid(uint32_t eax, uint32_t* regs);

//@别名 处理器_执行CPUID指令_扩展()
void cpu_exec_cpuid_ext(uint32_t* regs);

//@别名 处理器信息_取原始数据(数据指针)
cpu_error_t cpuid_get_raw_data(struct cpu_raw_data_t* data);

//@别名 处理器信息_取所有原始数据(原始数据数组指针)
cpu_error_t cpuid_get_all_raw_data(struct cpu_raw_data_array_t* data);

//@别名 处理器信息_序列化原始数据(原始数据指针,文件名)
cpu_error_t cpuid_serialize_raw_data(struct cpu_raw_data_t* data, const char* filename);

//@别名 处理器信息_序列化所有原始数据(原始数据数组指针,文件名)
cpu_error_t cpuid_serialize_all_raw_data(struct cpu_raw_data_array_t* data, const char* filename);

//@别名 处理器信息_反序列化原始数据(原始数据指针,文件名)
cpu_error_t cpuid_deserialize_raw_data(struct cpu_raw_data_t* data, const char* filename);

//@别名 处理器信息_反序列化所有原始数据(原始数据数组指针,文件名)
cpu_error_t cpuid_deserialize_all_raw_data(struct cpu_raw_data_array_t* data, const char* filename);

//@别名 处理器_识别(原始数据指针,处理器信息指针)
cpu_error_t cpu_identify(struct cpu_raw_data_t* raw, struct cpu_id_t* data);

//@别名 处理器_识别所有(原始数据数组指针,系统处理器信息指针)
cpu_error_t cpu_identify_all(struct cpu_raw_data_array_t* raw_array, struct system_id_t* system);

//@别名 处理器_识别核心类型(用途,原始数据数组指针,处理器信息指针)
cpu_error_t cpu_request_core_type(cpu_purpose_t purpose, struct cpu_raw_data_array_t* raw_array, struct cpu_id_t* data);

//@别名 处理器_取架构文本(架构)
const char* cpu_architecture_str(cpu_architecture_t architecture);

//@别名 处理器_取用途文本(架构)
const char* cpu_purpose_str(cpu_purpose_t purpose);

//@别名 取亲和性掩码文本2(亲和性掩码指针,缓冲区,缓冲区长度)
//@备注 线程安全
char* affinity_mask_str_r(cpu_affinity_mask_t* affinity_mask, char* buffer, uint32_t buffer_len);

//@别名 取亲和性掩码文本1(亲和性掩码指针)
//@备注 非线程安全
char* affinity_mask_str(cpu_affinity_mask_t* affinity_mask);

//@别名 处理器_取特征文本(特征)
const char* cpu_feature_str(cpu_feature_t feature);

//@别名 处理器_取错误文本()
const char* cpuid_error(void);

//@别名 处理器_RDTSC(结果)
void cpu_rdtsc(uint64_t* result);

//@别名 处理器_TSC_标记(标记指针)
void cpu_tsc_mark(struct cpu_mark_t* mark);

//@别名 处理器_TSC_取消标记(标记指针)
void cpu_tsc_unmark(struct cpu_mark_t* mark);

//@别名 处理器_从标记取时钟(标记指针)
int cpu_clock_by_mark(struct cpu_mark_t* mark);

//@别名 处理器_从系统取时钟()
int cpu_clock_by_os(void);

//@别名 处理器_测量时钟(毫秒,四次连续测量)
int cpu_clock_measure(int millis, BOOL quad_check);

//@别名 处理器_从IC测量时钟(毫秒,运行次数)
int cpu_clock_by_ic(int millis, int runs);

//@别名 处理器_取时钟()
//@备注 获取CPU时钟频率（多合一方法）
int cpu_clock(void);

//@别名 处理器_Enclave页面缓存
struct cpu_epc_t {
	//@别名 起始地址
	uint64_t start_addr;
	//@别名 长度
	uint64_t length;
};

//@别名 处理器信息_取Enclave页面缓存(索引,原始数据指针)
struct cpu_epc_t cpuid_get_epc(int index, const struct cpu_raw_data_t* raw);

//@别名 处理器信息_库版本()
const char* cpuid_lib_version(void);

//@别名 处理器信息_警告回调函数类型(消息)
typedef void (*libcpuid_warn_fn_t) (const char* msg);

//@别名 处理器信息_置警告回调函数(回调函数)
libcpuid_warn_fn_t cpuid_set_warn_function(libcpuid_warn_fn_t warn_fun);

//@别名 处理器信息_置警告回调级别(级别)
//@备注 级别范围 0..2
void cpuid_set_verbosiness_level(int level);

//@别名 处理器信息_取供应商()
cpu_vendor_t cpuid_get_vendor(void);

//@别名 处理器信息_取虚拟机供应商程序(原始数据指针,信息指针)
hypervisor_vendor_t cpuid_get_hypervisor(struct cpu_raw_data_t* raw, struct cpu_id_t* data);

//@别名 处理器_列表
struct cpu_list_t {
    
	//@别名 条目数
	int num_entries;
	
	//@别名 名称
	char** names;
};

//@别名 处理器信息_取处理器列表(供应商,列表指针)
void cpuid_get_cpu_list(cpu_vendor_t vendor, struct cpu_list_t* list);

//@别名 处理器信息_释放处理器列表(列表指针)
void cpuid_free_cpu_list(struct cpu_list_t* list);

//@别名 处理器信息_释放原始数据数组(原始数据数组指针)
void cpuid_free_raw_data_array(struct cpu_raw_data_array_t* raw_array);

//@别名 处理器信息_释放系统处理器信息(系统处理器信息指针)
void cpuid_free_system_id(struct system_id_t* system);

//@别名 MSR驱动句柄
struct msr_driver_t;

//@别名 处理器_MSR驱动_打开()
struct msr_driver_t* cpu_msr_driver_open(void);

//@别名 处理器_MSR驱动_打开核心(核心数)
struct msr_driver_t* cpu_msr_driver_open_core(unsigned core_num);

//@别名 处理器_读取MSR(句柄,MSR索引,结果指针)
cpu_error_t cpu_rdmsr(struct msr_driver_t* handle, uint32_t msr_index, uint64_t* result);

//@别名 处理器_MSR信息请求
enum cpu_msrinfo_request_t {

	//@别名 处理器_MSR信息请求_MPERF
	INFO_MPERF,
	
	//@别名 处理器_MSR信息请求_APERF
	INFO_APERF,
	
	//@别名 处理器_MSR信息请求_最小乘数
	INFO_MIN_MULTIPLIER,
	
	//@别名 处理器_MSR信息请求_当前乘数
	INFO_CUR_MULTIPLIER,
	
	//@别名 处理器_MSR信息请求_最大乘数
	INFO_MAX_MULTIPLIER,
	
	//@别名 处理器_MSR信息请求_核心摄氏度
	INFO_TEMPERATURE,
	
	//@别名 处理器_MSR信息请求_节流
	INFO_THROTTLING,
	
	//@别名 处理器_MSR信息请求_核心电压
	INFO_VOLTAGE,
	
	//@别名 处理器_MSR信息请求_基本时钟
	INFO_BCLK,
	
	//@别名 处理器_MSR信息请求_总线时钟
	INFO_BUS_CLOCK,
} ;

//@别名 处理器_读取MSR_范围(句柄,MSR索引,范围高位,范围低位,结果指针)
cpu_error_t cpu_rdmsr_range(struct msr_driver_t* handle, uint32_t msr_index, uint8_t highbit,
	uint8_t lowbit, uint64_t* result);

//@别名 处理器_MSR信息(句柄,信息字段开关)
cpu_error_t cpu_msrinfo(struct msr_driver_t* handle, cpu_msrinfo_request_t which);
//@别名 处理器_无效值
#define CPU_INVALID_VALUE 0x3fffffff

//@别名 MSR_序列化原始数据(句柄,文件名)
cpu_error_t msr_serialize_raw_data(struct msr_driver_t* handle, const char* filename);

//@别名 处理器_MSR驱动_关闭(句柄)
cpu_error_t cpu_msr_driver_close(struct msr_driver_t* handle);
*/