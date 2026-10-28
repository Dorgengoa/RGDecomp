/* rgp:protos */
#define RGP_SELF_CharaAddCollIgnoreMask_238920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `dsll32 $5,$5,16` / `dsra32 $5,$5,16` is an (s16) cast of a WIDER value. */
typedef struct P238920 { u8 pad000[0x40E]; s16 m40E; } P238920;
void CharaAddCollIgnoreMask_238920(P238920 *p, s32 v) { p->m40E |= (s16)v; }
