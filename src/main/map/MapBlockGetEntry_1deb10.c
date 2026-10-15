#include "types.h"
extern s32 MapDataIsLoadedOrUnloading_1e7980(void*);extern s32 MapEntryGetRec_1e1240(void*);
static inline s32 valid(u32 x,u32 n){return n>x;}
void*MapBlockGetEntry_1deb10(u8*p,u32 idx){u8*q;if(!MapDataIsLoadedOrUnloading_1e7980(p))return 0;q=*(u8**)(p+0xc0);if(!q)return 0;if(!valid(idx,(u32)*(s16*)(p+0xc8)))return 0;q+=idx*1952;return MapEntryGetRec_1e1240(q)?q:0;}
