/* rgp:protos */
#define RGP_SELF_AbilityReqIsSet_27a5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `lui %hi` + `lw %lo` instead of a gp-relative load: the object is bigger
   than the 8-byte small-data threshold, so pad the extern past it. */
typedef struct BigD27A5F0 { s32 m00; s32 pad[3]; } BigD27A5F0;
extern BigD27A5F0 D_004D7C74;
u8 AbilityReqIsSet_27a5f0(void) { return !(D_004D7C74.m00 < 0); }
