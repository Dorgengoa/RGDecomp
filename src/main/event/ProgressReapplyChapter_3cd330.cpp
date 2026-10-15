#pragma opt_propagation off
#include "types.h"

class V {
public:
    virtual s32 v08();
    virtual s32 v0c();
    virtual s32 v10();
    virtual s32 v14();
    virtual s32 v18();
    virtual s32 v1c();
    virtual s32 v20();
    virtual s32 v24();
    virtual s32 v28();
    virtual s32 v2c();
    virtual s32 v30();
    virtual s32 v34();
    virtual s32 v38();
    virtual s32 v3c();
    virtual s32 v40();
    virtual s32 v44();
    virtual s32 v48();
    virtual s32 v4c();
    virtual s32 v50();
    virtual s32 v54();
    virtual s32 v58();
    virtual s32 v5c();
    virtual s32 v60();
    virtual s32 v64();
    virtual s32 v68();
    virtual s32 v6c();
    virtual u8 *v70(s16);
};
struct A4 { u8 pad[8]; V *m8; };
struct AR { u8 pad[4]; A4 *m4; s16 m8; };
struct AR2 { u8 pad[4]; A4 *m4; s32 m8; };
typedef struct {
    s16 m0;
    u8 pad2[0x12];
    s32 m14;
    u8 *m18;
    u8 pad1C[4];
} Elem;
typedef struct {
    s16 m0;
    u8 pad2[0x12];
    s32 m14;
    Elem *m18;
} Obj;

extern "C" {
void ProgressValueSet_3cd020(void *, s32, s32, s32, s32, s32);
Obj *ProgressTableFindRowMaybe_422830(V *, s32);
}

inline u8 *pick(Elem *e, s32 i, s32 lim, s32 f) {
    u8 *p = e->m18;
    if (p == 0) return 0;
    if (i < lim) return p + (e->m14 - 1) * 16;
    if (lim < i) return p;
    if (f) return p;
    return 0;
}
static inline Obj *GetO(V *v, s32 i) { return ProgressTableFindRowMaybe_422830(v, i); }
extern "C" s32 ProgressReapplyChapter_3cd330(u8 *arg0, s32 arg1)
{
    u8 *r;
    Obj *o;
    s32 lim;
    s32 i;
    Elem *e;
    s32 j;
    u8 *p;
    u8 *q;
    s16 k;
    V *vv;
    A4 *a4;

    k = *(s16 *)(arg0 + 8);
    vv = (*(A4 **)(arg0 + 4))->m8;
    r = vv->v70(k);
    if (r == 0) return 0;
    lim = *(s16 *)(r + 8);
    i = 0;
    do {
        o = GetO((*(A4 **)(arg0 + 4))->m8, i);
        if (o != 0) {
            e = o->m18;
            if (e != 0) {
                for (j = 0; j < o->m14; j++, e++) {
                    p = e->m18;
                    if (p == 0) {
                        continue;
                    }
                    if (i < lim) {
                        q = p + (e->m14 - 1) * 16;
                    } else if (lim < i) {
                        q = p;
                    } else if (arg1 != 0) {
                        q = p;
                    } else {
                        continue;
                    }
                    if (q != 0) {
                        ProgressValueSet_3cd020(arg0, o->m0, e->m0, *(s16 *)q, 0, 0);
                    }
                }
            }
        }
        i++;
    } while (i < 13);
    return 1;
}
