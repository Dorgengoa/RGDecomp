#include "types.h"

extern void NavMgrPoolArrayCtor_2d1c40(void *);
extern void NavMgrPoolPtrArrayCtor_2d1c00(void *);
extern void BitArrayCtor_2d1bc0(void *);
extern void NavMgrPoolClear_2d1ba0(void *);
extern void Zero12Bytes_42cfb0(void *);

void *NavMgrPoolCtor_2d1b40(void *p)
{
    NavMgrPoolArrayCtor_2d1c40(p);
    NavMgrPoolPtrArrayCtor_2d1c00((void *)((s32)p + 0x8));
    BitArrayCtor_2d1bc0((u8 *)p + 0x18);
    NavMgrPoolClear_2d1ba0(p);
    *(s32 *)((u8 *)p + 0x00) = 0;
    *(s32 *)((u8 *)p + 0x04) = 0;
    *(s32 *)((u8 *)p + 0x08) = 0;
    *(s32 *)((u8 *)p + 0x0C) = 0;
    *(s32 *)((u8 *)p + 0x10) = 0;
    *(s32 *)((u8 *)p + 0x14) = 0;
    Zero12Bytes_42cfb0((void *)((s32)p + 0x18));
    return p;
}
