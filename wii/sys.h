#ifndef _SYS_H_
#define _SYS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes */
void Sys_Init(void);
void Sys_Reboot(void);
void Sys_Shutdown(void);
void Sys_LoadMenu(void);

#ifdef __cplusplus
}
#endif

#endif
