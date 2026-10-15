#include "types.h"
#pragma divbyzerocheck on

typedef unsigned __int128 u128;

typedef struct Sub {
    u8 pad0[4];
    s32 x4;
} Sub;

typedef struct Ref {
    u8 pad0[0xC];
    s32 xC;
    s32 x10;
} Ref;

typedef struct Ent Ent;
struct Ent {
    Ent *next;
    s32 x4;
    s32 x8;
    u32 xC;
    s32 x10;
    Ref *x14;
    Sub *x18;
    Sub *x1C;
    Sub *x20;
    Sub *x24;
};

typedef struct Grp Grp;
struct Grp {
    Grp *next;
    Ent *ents;
    u8 pad8[8];
    u32 *x10;
};

typedef struct Obj {
    u8 pad0[0x64];
    s32 x64;
    s32 x68;
    s32 x6C;
    u8 pad70[0xB4 - 0x70];
    s32 xB4;
    u8 padB8[4];
    s32 xBC;
    u8 padC0[4];
    s32 xC4;
    u8 padC8[4];
    s32 xCC;
    s32 xD0;
    u8 padD4[0xF0 - 0xD4];
    Grp *grp;
} Obj;

s32 ModelResCalcPrimCountMaybe_15c780(Obj *, s32, s32 *);
s32 MeshPktUnpackBoneRefsMaybe_164ec0(u32 *, s32, s32, s32, s32, s32 *);
s32 MeshPktUnpackV2Indexed_165150(u32 *, s32, s32, s32, s32, s32);
s32 MeshPktUnpackV3Indexed_165330(u32 *, s32, s32, s32, s32, s32);
s32 MeshPktUnpackV4Indexed_165550(u32 *, s32, s32, s32, s32, s32);

s32 ModelMeshBuildUnpackPktMaybe_15b2a0(Obj *o, u32 *dst)
{
    u32 *s;
    s32 n0;
    Grp *g;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 a64;
    s32 a68;
    s32 a6C;
    u32 *p;
    Ent *e;
    s32 j;
    s32 cnt;
    s32 tmp;
    s32 hdr;
    s32 r;
    s32 q;
    s32 rem;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 len;
    s32 len1;
    s32 l2;
    s32 k;
    s32 m;
    s32 m2;
    s32 i;
    u32 *start;
    s32 last;
    u32 *hp;
    Ent *t;

    p = dst;
    n0 = o->xB4;
    g = o->grp;
    f1 = o->xBC;
    f2 = o->xC4;
    f3 = o->xCC;
    f4 = o->xD0;
    a64 = o->x64;
    a68 = o->x68;
    a6C = o->x6C;
    for (; g != NULL; g = g->next) {
        for (e = g->ents; e != NULL; e = e->next) {
            if (e->x14 != NULL) {
                e->x10 = e->x14->x10;
                e->xC = e->x14->xC;
                continue;
            }
            cnt = 0;
            hdr = e->x4;
            r = ModelResCalcPrimCountMaybe_15c780(o, hdr, &cnt);
            q = e->x8 / r;
            rem = e->x8 % r;
            if (rem > 0) {
                q++;
            }
            w0 = 0;
            w1 = 0;
            w2 = 0;
            w3 = 0;
            if (e->x18 != NULL) {
                w0 = e->x18->x4;
            }
            w4 = w0;
            if (e->x1C != NULL) {
                w1 = e->x1C->x4;
            }
            if (e->x20 != NULL) {
                w2 = e->x20->x4;
            }
            if (e->x24 != NULL) {
                w3 = e->x24->x4;
            }
            start = p;
            for (j = 0; j < q; j++) {
                len = r;
                last = 0;
                if (j == q - 1) {
                    if (rem > 0) {
                        last = 1;
                        len = rem;
                    }
                }
                if (j > 0) {
                    if (cnt > 0) {
                        len += cnt;
                    }
                }
                len1 = len + 1;
                m = len1 * 2;
                m2 = m + len1;
                p[0] = 0x01000101;
                p[1] = 0x6C028000;
                p[2] = hdr;
                p[3] = len;
                p[4] = len | 0x8000;
                p[5] = len1;
                p[6] = m;
                p[7] = m2;
                m2 += len1;
                p[8] = m2;
                hp = &p[9];
                p = &p[10];
                k = 2;
                p += MeshPktUnpackV3Indexed_165330(p, k, len, n0, a64, w0);
                l2 = len * 2;
                k += len1;
                w0 += l2;
                if (w1 != 0 && f1 != 0) {
                    p += MeshPktUnpackV3Indexed_165330(p, k, len, f1, a68, w1);
                    w1 += l2;
                }
                k += len1;
                if (w2 != 0 && f2 != 0) {
                    p += MeshPktUnpackV2Indexed_165150(p, k, len, f2, a6C, w2);
                    w2 += l2;
                }
                k += len1;
                if (w3 != 0 && f3 != 0) {
                    p += MeshPktUnpackV4Indexed_165550(p, k, len, f3, 8, w3);
                    w3 += l2;
                }
                k += len1;
                if (f4 != 0) {
                    p += MeshPktUnpackBoneRefsMaybe_164ec0(p, k, len, f4, w4, &tmp);
                    w4 += l2;
                    *hp = (tmp - 1) * 2;
                }
                *p++ = 0x17000000;
                m = ((s32)p & 0xF) / 4;
                for (i = 0; i < 4 - m; i++) {
                    *p++ = 0;
                }
                if (!last && cnt > 0) {
                    if (w0 != 0) {
                        w0 -= cnt * 2;
                    }
                    if (w1 != 0) {
                        w1 -= cnt * 2;
                    }
                    if (w2 != 0) {
                        w2 -= cnt * 2;
                    }
                    if (w3 != 0) {
                        w3 -= cnt * 2;
                    }
                    if (w4 != 0) {
                        w4 -= cnt * 2;
                    }
                }
            }
            e->x10 = ((s32)p - (s32)start) / 16;
            e->xC = (u32)start & 0x0FFFFFFF;
        }
        s = p;
        for (t = g->ents; t != NULL; t = t->next) {
            *(u128 *)p = 0;
            p[0] = t->x10 | 0x30000000;
            p[1] = t->xC;
            p += 4;
        }
        *(u128 *)p = 0;
        p[0] = 0x60000000;
        p[2] = 0x11000000;
        g->x10 = s;
        p += 4;
    }
    return ((s32)p - (s32)dst) / 16;
}
