/* rgp:protos */
#define RGP_SELF_normal_LeaderHudGetBannerPhase_506b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x71]; s8 f71; } Obj;
extern s8 normal_LeaderHudGetBannerPhase_506b20(Obj *p);
s8 normal_LeaderHudGetBannerPhase_506b20(Obj *p) { return p->f71; }
