#include "types.h"
typedef struct Obj { u8 pad00[0x88]; s8 f88; } Obj;
extern s8 normal_LeaderHudIsBannerBlinking_506ae0(Obj *p);
s8 normal_LeaderHudIsBannerBlinking_506ae0(Obj *p) { return p->f88; }
