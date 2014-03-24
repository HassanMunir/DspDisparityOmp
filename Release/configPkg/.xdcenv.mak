#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/gtbldadm/ti/pdk_C6678_1_1_2_6/packages;/home/gtbldadm/ti/ipc_1_24_03_32/packages;/home/gtbldadm/ti/ndk_2_21_01_38/packages;/home/gtbldadm/ti/omp_1_01_03_02/packages;/home/gtbldadm/ti/bios_6_33_06_50/packages;/home/gtbldadm/ti/imglib_c66x_3_1_1_0/packages;/home/gtbldadm/ti/mcsdk_2_01_02_06;/home/gtbldadm/ti/mcsdk_2_01_02_06/demos
override XDCROOT = /home/gtbldadm/ti/xdctools_3_23_04_60
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/gtbldadm/ti/pdk_C6678_1_1_2_6/packages;/home/gtbldadm/ti/ipc_1_24_03_32/packages;/home/gtbldadm/ti/ndk_2_21_01_38/packages;/home/gtbldadm/ti/omp_1_01_03_02/packages;/home/gtbldadm/ti/bios_6_33_06_50/packages;/home/gtbldadm/ti/imglib_c66x_3_1_1_0/packages;/home/gtbldadm/ti/mcsdk_2_01_02_06;/home/gtbldadm/ti/mcsdk_2_01_02_06/demos;/home/gtbldadm/ti/xdctools_3_23_04_60/packages;..
HOSTOS = Linux
endif
