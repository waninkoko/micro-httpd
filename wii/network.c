#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ogcsys.h>
#include <network.h>

/* Constants */
#define BLOCK_SIZE		100

/* Variables */
static char hostip[16];
static u32  inited = 0;


char *Network_GetIP(void)
{
	/* Return IP string */
	return hostip;
}

s32 Network_Init(void)
{
	s32 ret;

	/* Already initialized */
	if (inited)
		return 0;

	/* Initialize network */
	while ((ret = net_init()) == -EAGAIN)
		usleep(100 * 1000);

	/* Network error */
	if (ret < 0)
		return ret;

	/* Get IP */
	ret = if_config(hostip, NULL, NULL, true);
	if (ret < 0)
		return ret;

	/* Set initialized */
	inited = 1;

	return 0;
}
