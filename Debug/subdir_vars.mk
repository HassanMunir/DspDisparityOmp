################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../image_processing_openmp_evmc6678l.cfg 

C_SRCS += \
../RecieveImage.c \
../mcip_master_main.c 

OBJS += \
./RecieveImage.obj \
./mcip_master_main.obj 

C_DEPS += \
./RecieveImage.pp \
./mcip_master_main.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"RecieveImage.pp" \
"mcip_master_main.pp" 

OBJS__QUOTED += \
"RecieveImage.obj" \
"mcip_master_main.obj" 

C_SRCS__QUOTED += \
"../RecieveImage.c" \
"../mcip_master_main.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


