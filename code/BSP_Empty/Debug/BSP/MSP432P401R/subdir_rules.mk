################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
BSP/MSP432P401R/%.obj: ../BSP/MSP432P401R/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/Software/Work/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Code/MCU/TI/BSP_Empty" --include_path="D:/Code/MCU/TI/BSP_Empty/Debug" --include_path="D:/Software/Work/CCS/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="D:/Software/Work/CCS/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="D:/Software/Work/CCS/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="D:/Software/Work/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="BSP/MSP432P401R/$(basename $(<F)).d_raw" --include_path="D:/Code/MCU/TI/BSP_Empty/Debug/syscfg" --obj_directory="BSP/MSP432P401R" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


