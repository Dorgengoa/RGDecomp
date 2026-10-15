#include "types.h"
typedef struct Obj { u8 pad00[0x68]; s32 f68; } Obj;
extern s32 normal_LeaderHudGetBannerWidth_506ac0(Obj *p);
s32 normal_LeaderHudGetBannerWidth_506ac0(Obj *p) { return p->f68; }
