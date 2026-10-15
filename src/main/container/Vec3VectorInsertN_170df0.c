#include "types.h"
#pragma optimization_level 3
#pragma divbyzerocheck on

typedef struct V { f32 x, y, z; } V;
typedef struct Vec { u32 cap; u32 size; V *data; } Vec;

extern void OperatorDelete_100840(V *);
extern V *OperatorNew_100990(u32);
extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32, void *);
extern void Vec3VectorClear_171420(Vec *);
extern u8 *D_00449858[];
extern u8 D_004591D0[];
extern u8 D_00459210[];

#define CONS(d, s) if ((d) != 0) { *(d) = *(s); }
#define ASSIGN(d, s) { *(s32 *)&(d)->x = *(s32 *)&(s)->x; (d)->y = (s)->y; (d)->z = (s)->z; }
#pragma opt_dead_assignments off

void Vec3VectorInsertN_170df0(Vec *v, V *pos, u32 n, V *val) {
    Vec tmp;
    Vec *tp;
    u32 newsize;
    V *end;
    u32 tail;
    V *p;
    V *q;
    u32 cap;
    V *mem;
    u32 k;

    if (n == 0) return;
    if (n >= 0x15555556 || v->size > 0x15555555 - n) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_004591D0);
        Abort_12de80();
    }
    newsize = v->size + n;
    if (newsize <= v->cap) {
        end = v->data + v->size;
        tail = end - pos;
        if (tail < n) {
            p = end;
            for (; tail < n; n--) {
                CONS(p, val);
                p++;
                v->size++;
            }
            for (q = pos; q < end; q++, p++) {
                CONS(p, q);
                v->size++;
            }
        } else {
            {
            V *s;
            V *d = end;
            for (s = end - n; s < end; s++, d++) {
                CONS(d, s);
                v->size++;
            }
            }
            k = tail - n;
            if (!(end - k > val) && end > val) val += n;
            q = pos + k;
            while (pos < q) {
                q--;
                end--;
                ASSIGN(end, q);
            }
        }
        {
            u32 m = n;
            while (m != 0) {
                m--;
                ASSIGN(pos, val);
                pos++;
            }
        }
    } else {
        tmp.cap = 0;
        tmp.size = 0;
        tmp.data = 0;
        { u32 c_ = *(volatile u32 *)&v->cap; cap = c_ ? c_ : 1; }
        while (newsize > cap) {
            if (cap < 0x0AAAAAAA) cap *= 2;
            else cap = 0x15555555;
        }
        mem = OperatorNew_100990(cap * sizeof(V));
        if (mem == 0) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00459210);
            Abort_12de80();
        }
        tmp.cap = cap;
        tmp.data = mem;
        q = v->data;
        end = q + v->size;
        for (; q < pos; q++, mem++) {
            CONS(mem, q);
            tmp.size++;
        }
        for (; n != 0; mem++, n--) {
            CONS(mem, val);
            tmp.size++;
        }
        for (; q < end; q++, mem++) {
            CONS(mem, q);
            tmp.size++;
        }
        if (&tmp != v) {
            u32 t;
            t = tmp.cap; tmp.cap = v->cap; v->cap = t;
            t = (u32)tmp.data; tmp.data = v->data; v->data = (V *)t;
            t = tmp.size; tmp.size = v->size; v->size = t;
        }
        Vec3VectorClear_171420(&tmp);
        if (tmp.data != 0) OperatorDelete_100840(tmp.data);
    }
}
