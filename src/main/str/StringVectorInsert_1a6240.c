#include "types.h"
#pragma optimization_level 3

typedef struct Console6240 {
    u8 pad00[0xC];
    void *out;
} Console6240;

typedef struct Alloc6240 {
    char c;
} Alloc6240;

typedef struct Body6240 {
    f32 v[3];
} Body6240;

typedef struct Str6240 {
    u32 flags;
    s32 len;
    char *ptr;
} Str6240;

typedef struct Elem6240 {
    s32 id;
    Str6240 s;
} Elem6240;

typedef struct Vec6240 {
    u32 cap;
    u32 size;
    Elem6240 *data;
} Vec6240;

extern Console6240 *const volatile D_00449858;
extern const char D_0045A6F0[];
extern const char D_0045A7B0[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
extern void Abort_12de80(void);
extern void *OperatorNew_100990(u32 n);
extern void OperatorDelete_100840(void *p);
extern void StringReserve_107e80(Str6240 *s, s32 n);
extern void StringReplace_106f90(Str6240 *s, s32 a, s32 b, char *first, char *last, Alloc6240 al);
extern void StringAssign_1a77a0(Str6240 *d, Str6240 *s);

#define CONSTRUCT(d, src) { \
    Alloc6240 al; \
    u32 i; \
    (d)->id = (src)->id; \
    if (((src)->s.flags & 1) == 0) { \
        *(Body6240 *)&(d)->s = *(Body6240 *)&(src)->s; \
    } else { \
        Str6240 *z_ = &(d)->s; \
        for (i = 0; i < 3; i++) { \
            ((s32 *)z_)[i] = 0; \
        } \
        StringReserve_107e80(&(d)->s, (src)->s.len); \
        StringReplace_106f90(&(d)->s, 0, 0, (src)->s.ptr, (src)->s.ptr + (src)->s.len, al); \
    } \
}

void StringVectorInsert_1a6240(Vec6240 *v, Elem6240 *pos, u32 n, Elem6240 *x)
{
    u32 nsize;
    u32 cap;
    u32 m;
    u32 tail;
    Elem6240 *last;
    Elem6240 *q;
    Elem6240 *p;
    Elem6240 *end;
    Vec6240 tmp;
    Elem6240 *fEp; Elem6240 *fW; Elem6240 *fP; Elem6240 *fQ; Elem6240 *fE;

    if (n == 0) {
        return;
    }
    if (n > 0xFFFFFFF || v->size > 0xFFFFFFF - n) {
        Fprintf_12f9a0(D_00449858->out, D_0045A6F0);
        Abort_12de80();
    }
    nsize = v->size + n;
    if (nsize <= v->cap) {
        fE = v->data + v->size;
        tail = fE - pos;
        if (tail < n) {
            for (fP = fE; tail < n; fP++, n--) {
                if (fP != 0) CONSTRUCT(fP, x)
                v->size++;
            }
            for (fQ = pos; fQ < fE; fQ++, fP++) {
                if (fP != 0) CONSTRUCT(fP, fQ)
                v->size++;
            }
        } else {
            for (fW = fE, fEp = fE - n; fEp < fE; fEp++, fW++) {
                if (fW != 0) CONSTRUCT(fW, fEp)
                v->size++;
            }
            m = tail - n;
            if (fE - m <= x) {
                if (x < fE) {
                    x += n;
                }
            }
            for (q = pos + m; pos < q;) {
                q--;
                fE--;
                fE->id = q->id;
                StringAssign_1a77a0(&fE->s, &q->s);
            }
        }
        for (q = pos; n != 0; n--) {
            q->id = x->id;
            StringAssign_1a77a0(&q->s, &x->s);
            q++;
        }
        return;
    }
    cap = *(volatile u32 *)&v->cap;
    tmp.cap = 0;
    tmp.size = 0;
    tmp.data = 0;
    cap = cap ? cap : 1;
    while (nsize > cap) {
        if (cap < 0x7FFFFFF) {
            cap = cap * 2;
        } else {
            cap = 0xFFFFFFF;
        }
    }
    p = (Elem6240 *)OperatorNew_100990(cap * sizeof(Elem6240));
    if (p == 0) {
        Fprintf_12f9a0(D_00449858->out, D_0045A7B0);
        Abort_12de80();
    }
    tmp.cap = cap;
    q = v->data;
    end = q + v->size;
    tmp.data = p;
    for (; q < pos; q++, p++) {
        if (p != 0) CONSTRUCT(p, q)
        tmp.size++;
    }
    for (; n != 0; p++, n--) {
        if (p != 0) CONSTRUCT(p, x)
        tmp.size++;
    }
    for (; q < end; q++, p++) {
        if (p != 0) CONSTRUCT(p, q)
        tmp.size++;
    }
    if (&tmp != v) {
        cap = tmp.cap;
        tmp.cap = v->cap;
        v->cap = cap;
        p = tmp.data;
        tmp.data = v->data;
        v->data = p;
        cap = tmp.size;
        tmp.size = v->size;
        v->size = cap;
    }
    p = tmp.data;
    for (last = p + tmp.size; p < last;) {
        last--;
        if (last != 0) {
            if (&last->s != 0 && (last->s.flags & 1)) {
                OperatorDelete_100840(last->s.ptr);
            }
        }
    }
    tmp.size = 0;
    if (tmp.data != 0) {
        OperatorDelete_100840(tmp.data);
    }
}
