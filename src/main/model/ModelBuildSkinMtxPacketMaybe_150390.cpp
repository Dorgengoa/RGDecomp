#include "types.h"
#include "vec.h"

struct B150390 {
    u8 pad0[0xA0];
    Mtx4 mA0;
};

struct M150390 {
    u8 pad0[0x50];
    virtual void v08();
    virtual s32 v0C(s32);
    u8 pad54[0x124 - 0x54];
    u32 w124;
    s32 w128;
    s32 *w12C;
};

struct L150390 {
    s32 w0;
    void **p4;
};

struct S150390 {
    s32 w0;
    s32 w4;
    s32 w8;
    L150390 *pC;
};

struct O150390 {
    s32 w0;
    u8 pad4[0x100];
    L150390 *p104;
    u8 *p108;
};

extern "C" {
void MtxInverse_13cf40(Mtx4 *, void *);
void MtxMulChain4_13cff0(u128 *, Mtx4 *, Mtx4 *, Mtx4 *, void *);
void MtxIdentity_13d2e0(Mtx4 *);
B150390 *ArrayGetChecked_152fd0(L150390 *, s32);
}

extern "C" s32 ModelBuildSkinMtxPacketMaybe_150390(O150390 *obj, s32 pad, u128 *out, S150390 *src, s32 idx, s32 idx2)
{
    M150390 *m;
    B150390 *bn;
    u128 *p;
    s32 *list;
    u32 flags;
    s32 cnt;
    Mtx4 a;
    Mtx4 id;
    Mtx4 b;
    s32 *e;
    B150390 *q;
    s32 n; L150390 *lookup;

    if (src == 0 || src->w0 == 0) {
        return 0;
    }
    if ((pad=obj->w0, lookup=src->pC, pad==0)) {
        return 0;
    }
    m = (M150390 *)lookup->p4[idx];
    if (m == 0) {
        return 0;
    }
    bn = (B150390 *)obj->p104->p4[idx2];
    if (bn == 0) {
        return 0;
    }
    *out = 0;
    p = out + 1;
    if (m->v0C(2) != 0) {
        cnt = m->w128;
        list = m->w12C;
        flags = m->w124;
        while (obj->p108 != 0 && flags != 0 && cnt > 0 && list != 0) {
            *p = 0;
            ((u32 *)p)[2] = 0x11000000;
            ((u32 *)p)[3] = flags | (cnt << 18) | 0x6C000000;
            p++;
            MtxInverse_13cf40(&a, &bn->mA0);
            MtxIdentity_13d2e0(&id);
            for (cnt--; cnt >= 0; cnt--) {
                e = &list[cnt];
                q = ArrayGetChecked_152fd0(obj->p104, *e);
                if (q != 0) {
                    MtxInverse_13cf40(&b, obj->p108 + (*e << 6));
                    MtxMulChain4_13cff0(p, &a, &q->mA0, &b, obj->p108 + (idx2 << 6));
                } else {
                    p[0] = *(u128 *)&id.r[0];
                    p[1] = *(u128 *)&id.r[1];
                    p[2] = *(u128 *)&id.r[2];
                    p[3] = *(u128 *)&id.r[3];
                }
                p += 4;
            }
            break;
        }
    }
    n = p - out;
    *(u32 *)out = (n - 1) | 0x60000000;
    return n;
}
