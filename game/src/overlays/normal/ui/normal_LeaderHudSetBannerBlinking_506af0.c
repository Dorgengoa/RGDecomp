/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetBannerBlinking_506af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x88]; s8 f88; } Obj;
extern s32 normal_LeaderHudSetBannerBlinking_506af0(Obj *p, s8 v);
s32 normal_LeaderHudSetBannerBlinking_506af0(Obj *p, s8 v) { p->f88 = v; return 1; }
