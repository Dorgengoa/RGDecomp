#include "types.h"
typedef struct P272210 { u8 pad000[0x58]; s16 m58; } P272210;
void MesWinAddPage_272210(P272210 *p, s32 v) { p->m58 += (s16)v; }
