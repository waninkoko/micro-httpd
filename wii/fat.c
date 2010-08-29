#include <stdio.h>
#include <ogcsys.h>
#include <fat.h>
#include <sdcard/wiisd_io.h>


s32 __Fat_Mount(const char *name, const DISC_INTERFACE *interface)
{
	bool ret;

	/* Startup interface */
	ret = interface->startup();
	if (!ret)
		return IPC_EINVAL;

	/* Mount device */
	ret = fatMountSimple(name, interface);
	if (!ret)
		return IPC_EINVAL;

	/* Workaround */
	fopen("sd:/", "rb");

	return 0;
}


s32 Fat_MountSD(void)
{
	/* Mount SD card */
	return __Fat_Mount("sd", &__io_wiisd);
}

s32 Fat_MountUSB(void)
{
	/* Mount USB device */
	return __Fat_Mount("usb", &__io_usbstorage);
}
