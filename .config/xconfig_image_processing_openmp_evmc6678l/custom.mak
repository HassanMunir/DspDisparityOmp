## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/image_processing_openmp_evmc6678l_pe66.oe66

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/image_processing_openmp_evmc6678l_pe66.xdl
	$(SED) 's"^\"\(package/cfg/image_processing_openmp_evmc6678l_pe66cfg.cmd\)\"$""\"C:/Users/CK-PC/DSP/Pothole_omp_ndk/.config/xconfig_image_processing_openmp_evmc6678l/\1\""' package/cfg/image_processing_openmp_evmc6678l_pe66.xdl > $@
	-$(SETDATE) -r:max package/cfg/image_processing_openmp_evmc6678l_pe66.h compiler.opt compiler.opt.defs
