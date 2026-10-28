/* rgp:protos */
#define RGP_SELF_PoolFreeElemByPtr_36aa80 1
#define RGP_SELF_index_of 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
/*rgp*/
static inline s32 index_of(void *p, u32 a) {
 u32 base; u64 ptr; s32 diff; s32 size; s32 index;
 if (a == 0) return -1;
 base=*(u32 *)((u8*)p+8); ptr=(u64)(u32)a;
 if (ptr < base) return -1;
 diff=(s32)(ptr-base); size=*(s32 *)((u8*)p+0x10);
 index=diff/size;
 if (diff%size > 0) return -1;
 if (index >= *(s32 *)((u8*)p+0x14)) return -1;
 return index;
}
int PoolFreeElemByPtr_36aa80(void *p, u32 a) { return PoolFreeElem_36a8e0(p,index_of(p,a)); }
