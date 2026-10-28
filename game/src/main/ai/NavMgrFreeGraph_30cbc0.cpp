/* rgp:protos */
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct {
    void **data;
    u32 count;
    u32 unk8;
    u32 cap;
} PtrArr;

typedef struct {
    u8 *elems;
    u32 nElems;
    PtrArr arr;
    s32 sub[1];
} Mgr;

extern "C" void BitArraySet_42cdc0(void *, u32, s32);
extern "C" s32 BitArrayTest_42ce40(void *, u32);

inline bool Mgr_IsValid(Mgr *m)
{
    if (m->elems == 0) return 0;
    if (m->arr.data == 0) return 0;
    if (m->sub[0] == 0) return 0;
    return 1;
}

inline u8 *Mgr_Get(Mgr *m, u32 i)
{
    if (i >= m->nElems) return 0;
    return m->elems + i * 0x120;
}

inline s32 PtrArr_Find(PtrArr *a, void *p)
{
    u32 i;
    void **d;
    if (a->data == 0) return -1;
    if (p == 0) return -1;
    d = a->data;
    for (i = 0; i < a->count; i++, d++) {
        if (*d == p) return i;
    }
    return -1;
}

inline void PtrArr_RemoveAt(PtrArr *a, u32 idx)
{
    u32 i;
    if (a->data != 0 && idx < a->count) {
        for (i = idx + 1; i < a->count; i++) {
            a->data[i - 1] = a->data[i];
        }
        a->count--;
        for (a->cap = 1; a->cap < a->count; a->cap <<= 1) {
        }
    }
}

extern "C" s32 NavMgrFreeGraph_30cbc0(Mgr *m, u32 idx)
{
    u8 *e;
    if (!Mgr_IsValid(m)) return 0;
    if (!BitArrayTest_42ce40(m->sub, idx)) return 0;
    e = Mgr_Get(m, idx);
    if (e == 0) return 0;
    { s32 k = PtrArr_Find(&m->arr, e); PtrArr_RemoveAt(&m->arr, k);
    BitArraySet_42cdc0(m->sub, idx, 0); }
    return 1;
}
