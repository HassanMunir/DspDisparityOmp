#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_37_02_27/packages;C:/ti/omp_1_01_03_02/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/ndk_2_23_00_00/packages;C:/ti/mcsdk_2_01_02_06;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv5/ccs_base;C:/ti/mathlib_c66x_3_0_1_1/packages;C:/Users/Hassan/workspace_v5_5/DisparityOmp/.config
override XDCROOT = C:/ti/xdctools_3_25_04_88
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_37_02_27/packages;C:/ti/omp_1_01_03_02/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/ndk_2_23_00_00/packages;C:/ti/mcsdk_2_01_02_06;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv5/ccs_base;C:/ti/mathlib_c66x_3_0_1_1/packages;C:/Users/Hassan/workspace_v5_5/DisparityOmp/.config;C:/ti/xdctools_3_25_04_88/packages;..
HOSTOS = Windows
endif
