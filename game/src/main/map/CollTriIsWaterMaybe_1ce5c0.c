/* rgp:protos */
#define RGP_SELF_CollTriIsWaterMaybe_1ce5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1CE5C0 { u8 pad000[0x44]; s16 m44; s16 m46; } P1CE5C0;
s32 CollTriIsWaterMaybe_1ce5c0(P1CE5C0 *p) { return (p->m46 & 8) != 0 && p->m44 == 2; }
