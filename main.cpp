#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <Imagehlp.h>

#pragma comment(lib, "Imagehlp.lib")

void DisableDynamicBase(char* path)
{
	LOADED_IMAGE image = { 0 };

	if (!MapAndLoad(path, NULL, &image, FALSE, FALSE)) {
		printf("MapAndLoad() %s failed!\n", path);
	}
	else {
		image.FileHeader->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
		printf("Dynamic Base Disabled!\n");
		UnMapAndLoad(&image);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage %s <file name>\n", argv[0]);
		return 1;
	}

	DisableDynamicBase(argv[1]);

	return 0;
}
