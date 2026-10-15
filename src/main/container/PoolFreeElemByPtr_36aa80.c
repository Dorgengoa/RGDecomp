#include "types.h"
#pragma divbyzerocheck on
extern s32 PoolFreeElem_36a8e0(void *, s32);
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
void PoolFreeElemByPtr_36aa80(void *p, u32 a) { PoolFreeElem_36a8e0(p,index_of(p,a)); }
