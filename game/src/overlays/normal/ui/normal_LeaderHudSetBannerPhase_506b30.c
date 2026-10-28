/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetBannerPhase_506b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x71]; s8 f71; } Obj;
extern s32 normal_LeaderHudSetBannerPhase_506b30(Obj *p, s8 v);
s32 normal_LeaderHudSetBannerPhase_506b30(Obj *p, s8 v) { p->f71 = v; return 1; }
