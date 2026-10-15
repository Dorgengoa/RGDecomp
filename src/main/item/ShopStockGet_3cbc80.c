#include "types.h"

typedef struct P { u8 pad0[0x440]; s8 f440[0x400]; } P;

s32 ShopStockGet_3cbc80(P *p, s32 i)
{
    if (i < 0 || 0x400 <= i) return -1;
    return p->f440[i];
}
