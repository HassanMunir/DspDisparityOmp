################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
system/platform_osal.obj: ../system/platform_osal.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -O3 --symdebug:none --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/imglib_c66x_3_1_1_0/inc" --gcc --display_error_number --diag_warning=225 --openmp --opt_for_speed=5 --preproc_with_compile --preproc_dependency="system/platform_osal.pp" --obj_directory="system" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/resourcemgr.obj: ../system/resourcemgr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -O3 --symdebug:none --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/imglib_c66x_3_1_1_0/inc" --gcc --display_error_number --diag_warning=225 --openmp --opt_for_speed=5 --preproc_with_compile --preproc_dependency="system/resourcemgr.pp" --obj_directory="system" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


