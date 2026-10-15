#include "types.h"
#pragma optimization_level 3

typedef struct V { f32 x, y, z, w; } V;
typedef struct Vec { u32 cap; u32 size; V *data; } Vec;

extern V *OperatorNew_100990(u32);
extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32, void *);
extern void Vec4VectorDtor_250980(Vec *, s32);
extern u8 *D_00449858[];
extern u8 D_0045ED60[];
extern u8 D_0045ED80[];

#define CONS(d, s) if ((d) != 0) { *(d) = *(s); }
#define ASSIGN(d, s) { *(s32 *)&(d)->x = *(s32 *)&(s)->x; *(s32 *)&(d)->y = *(s32 *)&(s)->y; { f32 z_ = (s)->z; f32 w_ = (s)->w; (d)->z = z_; (d)->w = w_; } }
#pragma opt_dead_assignments off

void Vec4VectorInsertN_250530(Vec *v, V *pos, u32 n, V *val) {
    Vec tmp;
    u32 newsize;
    u32 tail;
    V *p;
    V *q;
    u32 cap;
    V *mem;
    u32 k;
    V *s;
    V *d;
    V *last;

    if (n == 0) return;
    if (n >= 0x10000000 || v->size > 0x0FFFFFFF - n) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_0045ED60);
        Abort_12de80();
    }
    newsize = v->size + n;
    if (newsize <= v->cap) {
        V *end = v->data + v->size;
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
            d = end;
            for (s = end - n; s < end; s++, d++) {
                CONS(d, s);
                v->size++;
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
            if (cap < 0x07FFFFFF) cap *= 2;
            else cap = 0x0FFFFFFF;
        }
        mem = OperatorNew_100990(cap * sizeof(V));
        if (mem == 0) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_0045ED80);
            Abort_12de80();
        }
        tmp.cap = cap;
        tmp.data = mem;
        q = v->data;
        last = q + v->size;
        for (; q < pos; q++, mem++) {
            CONS(mem, q);
            tmp.size++;
        }
        for (; n != 0; mem++, n--) {
            CONS(mem, val);
            tmp.size++;
        }
        for (; q < last; q++, mem++) {
            CONS(mem, q);
            tmp.size++;
        }
        if (&tmp != v) {
            u32 t;
            t = tmp.cap; tmp.cap = v->cap; v->cap = t;
            t = (u32)tmp.data; tmp.data = v->data; v->data = (V *)t;
            t = tmp.size; tmp.size = v->size; v->size = t;
        }
        Vec4VectorDtor_250980(&tmp, -1);
    }
}
