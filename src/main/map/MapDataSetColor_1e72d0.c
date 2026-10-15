#include "types.h"
static inline s32 clamp(s32 v){if(v<0)v=0;if(v>255)v=255;return v;}
void MapDataSetColor_1e72d0(u8*p,s32 a,s32 b,s32 c,s32 d){a=clamp(a);b=clamp(b);c=clamp(c);d=256-d*2;if(d<0)d=0;if(d>255)d=255;p[0x50]=a;p[0x51]=b;p[0x52]=c;p[0x53]=d;}
