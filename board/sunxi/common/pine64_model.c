
#include <common.h>
#include <asm/arch-sun50iw1p1/dram.h>
#include <fdt_support.h>

DECLARE_GLOBAL_DATA_PTR;

int pine64_set_model(void)
{
	int nodeoffset;
	int ret;
	char *model = NULL;

	nodeoffset = fdt_path_offset(working_fdt, "/soc@01c00000/product");
	if (nodeoffset < 0) {
		printf("pine64_set_model: /soc@01c00000/product does not exist\n");
		return -1;
	}

	ret = fdt_getprop_string(working_fdt, nodeoffset, "machine", &model);
	if (ret < 0 || !model) {
		printf("pine64_set_model: /soc@01c00000/product/machine does not exist\n");
		return -1;
	}

	printf("Pine64 model: %s\n", model);

	if(setenv("pine64_model", model)) {
		printf("error:set variable [pine64_model] fail\n");
	}

	return 0;
}
