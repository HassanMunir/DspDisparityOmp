################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
platform/package/package_demos.image_processing.openmp.evmc6678l.platform.obj: ../platform/package/package_demos.image_processing.openmp.evmc6678l.platform.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/qmss" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/drv/cppi" --include_path="C:/ti/mathlib_c66x_3_0_1_1/inc" --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.4.0/include" --gcc --display_error_number --diag_warning=225 --openmp --preproc_with_compile --preproc_dependency="platform/package/package_demos.image_processing.openmp.evmc6678l.platform.pp" --obj_directory="platform/package" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


