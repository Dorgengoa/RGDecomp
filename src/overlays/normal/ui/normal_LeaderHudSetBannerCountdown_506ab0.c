#include "types.h"
typedef struct Obj { u8 pad00[0x8C]; s32 f8C; } Obj;
extern s32 normal_LeaderHudSetBannerCountdown_506ab0(Obj *p, s32 v);
s32 normal_LeaderHudSetBannerCountdown_506ab0(Obj *p, s32 v) { p->f8C = v; return 1; }
