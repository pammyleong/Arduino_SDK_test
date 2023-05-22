#ifndef _MMF_SOURCE_PCMU_FILE_H_
#define _MMF_SOURCE_PCMU_FILE_H_

#include "sample_pcmu.h"

void *pcmuf_mod_open(void);
void pcmuf_mod_close(void *ctx);
int pcmuf_mod_set_param(void *ctx, int cmd, int arg);
int pcmuf_mod_handle(void *ctx, void *b);

/*customized CMDs used for this module - all customized CMDs should start from 0x10 at least*/

#endif