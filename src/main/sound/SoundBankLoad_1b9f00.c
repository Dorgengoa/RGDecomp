#include "types.h"
#pragma optimization_level 3

typedef struct Ent12 {
    s32 w0;
    s32 w4;
    s32 w8;
} Ent12;

typedef struct Slot {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 n20;
    s32 *a24;
    s32 *a28;
    s32 *a2C;
    s32 n30;
    Ent12 *a34;
} Slot;

typedef struct Chan {
    u8 pad0[4];
    s32 w4;
    s32 w8;
    u8 padC[0xC];
    Slot slots[5];
    u8 pad130[0x14C - 0x130];
    s32 w14C;
    u8 pad150[0x1E0 - 0x150];
} Chan;

typedef struct Heap {
    u8 pad0[0x28];
    s32 w28;
    s32 w2C;
    u8 pad30[4];
    s32 w34;
} Heap;

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern void OperatorDeleteArray_100820(s32 *);
extern s32 *OperatorNewArray_100900(s32);
extern s32 MemStackStrDup_14cff0(s32, Heap *);
extern void MemStackAllocQw_14d950(Heap *, s32);
extern s32 MemStackNew_14e1b0(s32, Heap *);
extern s32 ArchiveCountEntries_181bb0(void *);
extern s32 ArchiveFindByExt_181be0(void *, void *, s32 *, s32, s32 *, s32 *);
extern s32 MidiFileParse_1b5b50(Ent12 *, s32, s32, u32 *, s32);
extern s32 SoundSendCmd_1b6cc0();
extern void SoundBankVolParse_1b7200(Chan *, s32, s32, s32);
extern void SoundBankCfgParse_1b74a0(Chan *, s32, s32, s32, Heap *);
extern void MidiSeqDataCtor_1ba5f0(void);
extern void SoundBankPartRelease_1ba620(s32, Slot *, s32);
extern void SoundBankUploadPart_1ba770(s32, s32, s32, s32, s32, s32);
extern s32 SoundCategoryGetChanMapMaybe_1bab00(s32, Chan *);
extern void SifDmaSendSync_1c21e0(s32, s32, s32);
extern s32 IopHeapAllocLocked_1c22d0(s32);
extern u8 D_0045ABD8[];
extern u8 D_0045ABE0[];
extern u8 D_0045ABE8[];
extern u8 D_0045ABF0[];
extern u8 D_0045ABF8[];
extern u8 D_0045AC00[];
extern s32 D_0047E1F8;
extern u8 D_0049EB10[][0x1E0];

static inline Chan *GetChan(s32 ch)
{
    if (ch < 0 || ch > 16) return 0;
    return (Chan *)D_0049EB10[ch];
}

static inline Slot *GetSlot(Chan *c, s32 i)
{
    if (i < 0 || i >= 5) return 0;
    return &c->slots[i];
}

s32 SoundBankLoad_1b9f00(s32 ch, void *def, Heap *heap)
{
    s32 aId;
    s32 aN;
    s32 bId;
    s32 bN;
    s32 cId;
    s32 dId;
    s32 cN;
    s32 dN;
    Chan *c;
    s32 hi;
    s32 i;
    Slot *slot;
    Slot *e;
    s32 *pa;
    s32 flag;
    u32 *base;
    s32 *B;
    s32 j;
    s32 *A;
    s32 ret;
    s32 *pb;
    s32 m;
    s32 off;
    s32 k;
    s32 n;
    s32 lim;
    s32 r;
    s32 sz;
    s32 *C;

    if (D_0047E1F8 == 0) {
        return -1;
    }
    c = GetChan(ch);
    if (c == 0) {
        return -1;
    }
    if (SoundCategoryGetChanMapMaybe_1bab00(ch, c) == 0) {
        return -1;
    }
    hi = (u8)ch << 24;
    if (ArchiveFindByExt_181be0(def, D_0045ABE8, &aId, 1, &aN, 0) <= 0) {
        return -1;
    }
    if (ArchiveFindByExt_181be0(def, D_0045ABF0, &bId, 1, &bN, 0) <= 0) {
        return -1;
    }
    i = 0;
    slot = 0;
    for (; i < 5; i++) {
        e = GetSlot(c, i);
        if (e == 0) {
            break;
        }
        if (e->w0 == 0) {
            slot = e;
            break;
        }
    }
    if (slot == 0) {
        return -1;
    }
    slot->w0 = 1;
    ret = hi | ((u8)i << 16);
    if (c->w8 >= 0) {
        SoundSendCmd_1b6cc0(0xF, 1, c->w8);
        SoundSendCmd_1b6cc0(1, 1, c->w8);
        SoundSendCmd_1b6cc0(2, 1, c->w8);
    }
    if (c->w4 != c->w8) {
        if (i == 0) {
            SoundSendCmd_1b6cc0(1, 1, c->w4);
            SoundSendCmd_1b6cc0(2, 1, c->w4);
        }
        if (i == 0) {
            if (c->w14C < 0) {
                c->w14C = SoundSendCmd_1b6cc0(4, 1, -1);
            }
        }
        if (c->w14C >= 0) {
            SoundSendCmd_1b6cc0(7, 2, c->w4, c->w14C);
        }
    }
    if (ArchiveFindByExt_181be0(def, D_0045ABD8, &cId, 1, &cN, 0) <= 0) {
        cN = 0;
    }
    if (ArchiveFindByExt_181be0(def, D_0045ABE0, &dId, 1, &dN, 0) <= 0) {
        dN = 0;
    }
    flag = 0;
    if (dN > 0 && dId != 0 && cId != 0 && cN > 0) {
        flag = 1;
    }
    SoundBankPartRelease_1ba620(ch, slot, 0);
    slot->w4 = 0;
    slot->w8 = 0;
    slot->wC = 0;
    slot->w10 = -1;
    slot->n30 = 0;
    slot->n20 = 0;
    slot->w18 = 0;
    slot->w1C = 0;
    slot->a24 = 0;
    slot->a34 = 0;
    slot->w14 = 0;
    slot->a28 = 0;
    slot->a2C = 0;
    if (flag) {
        SoundBankUploadPart_1ba770(ch, i, dId, (s32)(u32)dN, cId, (s32)(u32)cN);
    }
    n = ArchiveCountEntries_181bb0(def);
    A = OperatorNewArray_100900(n * 4);
    B = OperatorNewArray_100900(n * 4);
    C = OperatorNewArray_100900(n * 4);
    if (c->w8 >= 0) {
        slot->n20 = ArchiveFindByExt_181be0(def, D_0045ABF8, A, n, B, C);
        slot->a24 = (s32 *)MemStackNew_14e1b0(slot->n20 * 4, heap);
        slot->a28 = (s32 *)MemStackNew_14e1b0(slot->n20 * 4, heap);
        slot->a2C = (s32 *)MemStackNew_14e1b0(slot->n20 * 4, heap);
        for (j = 0; j < slot->n20; j++) {
            pa = &A[j];
            slot->a24[j] = 0;
            slot->a28[j] = 0;
            slot->a2C[j] = -1;
            if (*pa != 0 && B[(u32)j] > 0) {
                slot->a28[j] = IopHeapAllocLocked_1c22d0(B[(u32)j] + 4);
                if (slot->a28[j] != 0) {
                    SifDmaSendSync_1c21e0(*pa, (slot->a28[j] + 3) & ~3, *(pb = &B[j]));
                    slot->a2C[j] = SoundSendCmd_1b6cc0(3, 3, -1, (slot->a28[j] + 3) & ~3, *pb);
                }
            }
            slot->a24[(u32)j] = MemStackStrDup_14cff0(C[(u32)j], heap);
        }
    }
    slot->n30 = ArchiveFindByExt_181be0(def, D_0045AC00, A, n, B, C);
    if (slot->n30 > 0) {
        m = (s32)(u32)slot->n30;
        slot->a34 = (Ent12 *)ConstructNewArray_100710(MemStackNew_14e1b0(m * 12 + 0x10, heap), MidiSeqDataCtor_1ba5f0, 0, 0xC, m);
    }
    off = 0;
    base = (u32 *)(heap->w28 + heap->w2C * 16);
    lim = (heap->w34 - heap->w2C) * 16;
    for (k = 0; k < slot->n30; k++) {
        slot->a34[k].w0 = C[k];
        r = MidiFileParse_1b5b50(&slot->a34[k], A[k], B[k], base, lim - off);
        sz = (r + 3) / 4 * 4;
        base += sz / 4;
        off += sz;
        if (!(off < lim)) {
            break;
        }
    }
    MemStackAllocQw_14d950(heap, (off + 15) / 16 * 16 / 16);
    SoundBankCfgParse_1b74a0(c, i, aId, aN, heap);
    SoundBankVolParse_1b7200(c, i, bId, bN);
    for (k = 0; k < slot->n30; k++) {
        slot->a34[k].w0 = 0;
    }
    OperatorDeleteArray_100820(A);
    OperatorDeleteArray_100820(B);
    OperatorDeleteArray_100820(C);
    return ret;
}
