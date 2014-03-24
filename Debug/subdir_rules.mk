################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
RecieveImage.obj: ../RecieveImage.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/mathlib_c66x_3_0_1_1/inc" --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --gcc --display_error_number --diag_warning=225 --openmp --preproc_with_compile --preproc_dependency="RecieveImage.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../image_processing_openmp_evmc6678l.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_25_04_88/xs" --xdcpath="C:/ti/bios_6_35_04_50/packages;C:/ti/omp_1_01_03_02/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/ndk_2_23_00_00/packages;C:/ti/mcsdk_2_01_02_06;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv5/ccs_base;C:/ti/mathlib_c66x_3_0_1_1/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p demos.image_processing.openmp.evmc6678l.platform -r debug -b "C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld" -c "C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0" --compileOptions "--gcc" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld
configPkg/compiler.opt: | configPkg/linker.cmd C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld
configPkg/: | configPkg/linker.cmd C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld

mcip_master_main.obj: ../mcip_master_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/mathlib_c66x_3_0_1_1/inc" --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --gcc --display_error_number --diag_warning=225 --openmp --preproc_with_compile --preproc_dependency="mcip_master_main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


