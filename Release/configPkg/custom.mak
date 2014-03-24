## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/image_processing_openmp_evmc6678l_pe66.oe66 \

linker.cmd: package/cfg/image_processing_openmp_evmc6678l_pe66.xdl
	$(SED) 's"^\"\(package/cfg/image_processing_openmp_evmc6678l_pe66cfg.cmd\)\"$""\"/home/gtbldadm/ti/mcsdk_2_01_02_06/demos/image_processing/openmp/evmc6678l/Release/configPkg/\1\""' package/cfg/image_processing_openmp_evmc6678l_pe66.xdl > $@
