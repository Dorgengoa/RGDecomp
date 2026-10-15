#include "types.h"
typedef struct P42E9D0 { u8 pad000[0x8]; s32 m8; } P42E9D0;
s32 DListContains_42e9d0(s32 key, P42E9D0 *p)
{
    return p != 0 && p->m8 == key;
}
