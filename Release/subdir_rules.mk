################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/linker.cmd: ../image_processing_openmp_evmc6678l.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_23_04_60/xs" --xdcpath="C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/ndk_2_23_00_00/packages;C:/ti/omp_1_01_03_02/packages;C:/ti/bios_6_33_06_50/packages;C:/ti/imglib_c66x_3_1_1_0/packages;C:/ti/mcsdk_2_01_02_06;C:/ti/mcsdk_2_01_02_06/demos;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p demos.image_processing.openmp.evmc6678l.platform -r release -b "C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld" -c "C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0" --compileOptions "--gcc" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld
configPkg/compiler.opt: | configPkg/linker.cmd C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld
configPkg/: | configPkg/linker.cmd C:/Users/Hassan/workspace_v5_5/image_processing_openmp_evmc6678l/platform/config.bld

mcip_master_main.obj: ../mcip_master_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -O3 --symdebug:none --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/imglib_c66x_3_1_1_0/inc" --gcc --display_error_number --diag_warning=225 --openmp --opt_for_speed=5 --preproc_with_compile --preproc_dependency="mcip_master_main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

udpHello.obj: ../udpHello.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -O3 --symdebug:none --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/imglib_c66x_3_1_1_0/inc" --gcc --display_error_number --diag_warning=225 --openmp --opt_for_speed=5 --preproc_with_compile --preproc_dependency="udpHello.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


