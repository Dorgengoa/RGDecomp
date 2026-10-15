#include "types.h"
#pragma divbyzerocheck on

typedef unsigned __int128 u128;

typedef struct Tex0 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} Tex0;

typedef struct Node {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u16 f28;
    u8 f2A;
    u8 f2B;
    u8 pad2C[6];
    u8 f32;
    u8 f33;
    s16 f34;
    s16 f36;
    Tex0 tex0;
    u8 pad40[0x10];
    s32 f50;
    u8 pad54[0x10];
    struct Node *next;
} Node;

typedef struct Slot {
    u8 pad0[8];
    Node *head;
    u8 padC[4];
} Slot;

typedef struct Mgr {
    s32 f0;
    s32 f4;
    s32 cur;
    s32 count;
    s32 f10;
    s32 f14;
    u8 pad18[4];
    Slot *tbl;
} Mgr;

extern s32 TexBuildUploadPkt_158610(Mgr *, u32 *, Node *, s32);
extern u128 D_00449F80[];
extern s32 D_00491880[];
extern s32 D_00491884[];

static inline s32 put(u32 *p)
{
    s32 n;

    if (p == 0) {
        n = 1;
    } else {
        *(u128 *)p = D_00449F80[0];
        n = 1;
    }
    return n;
}

s32 TexGroupAllocVram_157e70(Mgr *self, s32 idx, u32 *pkt)
{
    u32 *start;
    u128 room;
    s32 addr;
    s32 vram;
    s32 end;
    Node *node;
    s32 clut;
    s32 sz;
    s32 ok;
    s32 t;
    s32 k;
    s32 d;
    s32 m;

    if (pkt != 0) {
        if (idx < 0 || idx >= self->count) {
            self->cur = -1;
            return 0;
        }
    } else {
        self->cur = -1;
    }
    start = pkt;
    if (pkt != 0) {
        pkt += put(pkt) * 4;
    }
    vram = self->f10;
    end = self->f14;
    addr = self->f0;
    clut = self->f4;
    room = end - vram > 0;
    if (self->cur != idx) {
        for (node = self->tbl[idx].head; node != 0; node = node->next) {
            if (node->f2B != 0) {
                continue;
            }
            ok = 0;
            if (room) {
                sz = 0;
                if (node->f36 == 0 && node->f6 == 8 && node->f50 != 0) {
                    t = 1;
                    sz = node->f28 * 4;
                } else {
                    t = 0;
                }
                if (t && vram + sz < end) {
                    ok = 1;
                }
            }
            if (ok) {
                node->tex0.tbp0 = vram;
                vram += sz;
                node->tex0.psm = 0x1B;
            } else {
                node->tex0.tbp0 = addr;
                addr += node->f28;
            }
            k = 0;
            if (node->f6 == 8) {
                k = 4;
            } else if (node->f6 == 4) {
                k = 1;
            }
            if (k > 0) {
                clut -= node->f32 * k;
                node->f34 = clut;
                m = node->f33;
                d = node->f32;
                if (d > 0) {
                    node->f33 = m % d;
                    t = 1;
                    if (node->f6 == 8) {
                        t = 4;
                    }
                    node->tex0.cbp = node->f34 + node->f33 * t;
                }
            }
            if (pkt != 0) {
                pkt += TexBuildUploadPkt_158610(self, pkt, node, 0);
                node->f2A = 1;
            } else {
                node->f2A = 0;
            }
        }
        if (clut < addr) {
            D_00491880[0] = 1;
            D_00491884[0] = idx;
        }
    }
    if (pkt != 0) {
        pkt += put(pkt) * 4;
        self->cur = idx;
    }
    return (pkt - start) / 4;
}
