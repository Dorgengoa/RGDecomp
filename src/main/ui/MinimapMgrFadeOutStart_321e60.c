#include "types.h"
typedef struct P321E60 { u8 pad000[0x51C]; f32 m51C; } P321E60;
void MinimapMgrFadeOutStart_321e60(P321E60 *p, f32 x) { p->m51C = -(1.0f / x); }
