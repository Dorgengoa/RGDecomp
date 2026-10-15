#include "types.h"

typedef struct E001e81b0 {
    s16 unk0;
    s16 unk2;
    void *unk4;
    s32 unk8;
} E001e81b0;

typedef struct S001e81b0 {
    E001e81b0 e[4];
    u8 pad30[0x16D4 - 0x30];
    s32 unk16D4;
} S001e81b0;

extern void *MemStackAllocQw_14d950(s32, u32);
extern void *memcpy(void *, const void *, u32);

static inline s32 plus(s32 a,s32 b){return a+b;}
s32 MapAreaDataCopyFileBuf_1e81b0(S001e81b0 *arg0, s32 arg1, void **arg2)
{
    E001e81b0 *e;
    u32 n;
    void *r;
    void **pd;
    s32 *ps;

    if (arg2 == NULL) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 4) {
        return 1;
    }
    e = (E001e81b0 *)(s32)plus(arg1*12,(s32)arg0);
    if (e->unk2 == 0) {
        return 0;
    }
    pd = &e->unk4;
    if (*pd == NULL || *(ps=&e->unk8) <= 0) {
        return 1;
    }
    if (e->unk8 & 0xF) {
        n = ((u32)e->unk8 >> 4) + 1;
    } else {
        n = (u32)e->unk8 >> 4;
    }
    r = MemStackAllocQw_14d950(arg0->unk16D4, n);
    *arg2 = r;
    if (r == NULL) {
        return -1;
    }
    memcpy(r, *pd, *ps);
    return 2;
}
