#include "types.h"

extern void OperatorDelete_100840(void *);
extern void EffHdlAssignIndex_1a6030(void *a, s32 idx);
extern void StringVectorInsert_1a6240(void *v, void *pos, s32 n, void *val);
extern void VectorU32InsertN_1a4e80(void *v, void *pos, s32 n, void *val);

struct Stra5e50 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

struct Elta5e50 {
    s32 first;
    struct Stra5e50 second;
};

struct Arga5e50 {
    u8 pad000[0x2];
    u16 m02;
};

struct Poola5e50 {
    u8 pad000[0x4];
    s32 v1size;             /* +0x04 */
    struct Elta5e50 *v1data; /* +0x08 */
    u8 pad00c[0x4];         /* +0x0C is the second vector */
    s32 v2size;             /* +0x10 */
    s32 *v2data;            /* +0x14 */
    u8 pad018[0x4];
    s32 fcount;             /* +0x1C */
    s32 *fdata;             /* +0x20 */
};

void *EffHdlSlotAlloc_1a5e50(struct Poola5e50 *self, struct Arga5e50 *a)
{
    s32 idx;
    u32 i;
    struct Elta5e50 tmp;
    s32 key;
    s32 *w;
    s32 c;

    if (self->fcount == 0) {
        idx = self->v2size;
        EffHdlAssignIndex_1a6030(a, idx);
        w = (s32 *)&tmp.second;
        for (i = 0; i < 3; i++) {
            w[i] = 0;
        }
        StringVectorInsert_1a6240(self, self->v1data + self->v1size, 1, &tmp);
        if ((tmp.second.m00 & 1) != 0) {
            OperatorDelete_100840(tmp.second.m08);
        }
        key = a->m02;
        VectorU32InsertN_1a4e80((u8 *)self + 0xC, self->v2data + self->v2size, 1, &key);
    } else {
        idx = ((s32 *)self->fdata)[*(volatile s32 *)&self->fcount - 1];
        EffHdlAssignIndex_1a6030(a, idx);
        self->fcount = self->fcount - 1;
        self->v2data[idx] = a->m02;
    }
    return self->v1data + idx;
}
