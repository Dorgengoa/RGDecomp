#include "types.h"
#pragma optimization_level 3
#pragma opt_dead_assignments off

typedef struct { u32 cap; u32 size; u32 *data; } Vec;

extern void OperatorDelete_100840(void *);
extern void *OperatorNew_100990(u32);
extern void Abort_12de80();
extern void Fprintf_12f9a0(s32, void *);
extern u8 D_00449858[0x400];
extern u8 D_0045A6F0[0x400];
extern u8 D_0045A7D0[0x400];

void VectorU32InsertN_1a4e80(Vec *v, u32 *pos, u32 n, u32 *val) {
    u32 newsize;
    u32 *end;
    s32 tail;
    u32 *src;
    u32 *dst;
    u32 k;
    s32 idx;
    u32 cap;
    u32 *nd;
    u32 *oend;
    u32 **pd;
    u32 max;
    u32 m;
    u32 *old;

    if (n != 0) {
        if (n >= 0x40000000U || v->size > 0x3FFFFFFFU - n) {
            Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_0045A6F0);
            Abort_12de80();
        }
        newsize = v->size + n;
        if (newsize <= v->cap) {
            end = v->data + v->size;
            tail = end - pos;
            if (end - (tail - n) <= val && val < end) {
                val += n;
            }
            if (tail != 0) {
                src = end;
                dst = end + n;
                while (pos < src) {
                    *--dst = *--src;
                }
            }
            for (k = n; k != 0; k--) {
                *pos++ = *val;
            }
            v->size += n;
        } else {
            old = v->data;
            idx = pos - old;
            cap = *(u32 *)v;
            switch (cap) { case 0: cap = 1; break; }
            while (newsize > cap) {
                if (cap < 0x1FFFFFFFU) {
                    cap *= 2;
                } else {
                    cap = 0x3FFFFFFF;
                }
            }
            pd = &v->data;
            nd = OperatorNew_100990(cap * 4);
            if (nd == NULL) {
                Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_0045A7D0);
                Abort_12de80();
            }
            *pd = nd;
            dst = v->data + idx;
            for (k = n; k != 0; k--) {
                *dst++ = *val;
            }
            if (old != NULL) {
                src = old;
                oend = old + idx;
                dst = v->data;
                while (src < oend) {
                    *dst++ = *src++;
                }
                src = old + idx;
                oend = old + v->size;
                dst = v->data + (s32)idx + n;
                while (src < oend) {
                    *dst++ = *src++;
                }
                OperatorDelete_100840(old);
            }
            v->size = newsize;
            v->cap = cap;
        }
    }
}
