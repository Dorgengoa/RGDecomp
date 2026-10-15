#include "types.h"

typedef unsigned __int128 u128;

class Elem {
public:
    s32 m0;
    s32 m4;
    u8 p8[0x1C];
    u8 m24;
    u8 p25[7];
    u8 m2C;
    u8 p2D[3];
    u8 m30[0xB0];
    virtual void v0();
    virtual void v1();
    virtual void f10();
    u8 pad2[0xC];
};

typedef struct { u128 a, b, c, d; } Blk;

typedef struct {
    s32 m0;
    u8 p4[0x100];
    s32 m104;
    s32 m108;
    s32 m10C;
    s32 *m110;
    u8 p114[0xC];
    u8 m120[4];
    s32 m124;
    u8 p128[0x58];
    u8 m180[0x10];
    u8 m190[0x10];
    u8 m1A0[0x10];
} Self;

typedef struct {
    s32 m0;
    u8 p4[8];
    s32 mC;
    s32 m10;
    s32 m14;
    u8 p18[7];
    u8 m1F;
    u8 m20[0x40];
    Blk m60;
} Src;

extern "C" {
s32 ConstructNewArray_100710(s32, void (*)(void), s32, s32, s32);
void Mat44To34_13e270(u8 *, u8 *);
void FrameAllocExtMaybe_149390(Elem *, s32);
void FrameSetParent_149e90(Elem *, Elem *);
void ModelFrameSetMatrix_14a190(Elem *, u8 *);
void FrameSetRotMode_14a250(Elem *, s32);
void ModelFrameSetScaleLink_14a4e0(Elem *, u8 *);
void ModelFrameSetRotLink_14a500(Elem *, u8 *);
void ModelFrameSetPosLink_14a530(Elem *, u8 *);
void FrameResetXform_14a550(Elem *);
void ModelFrameSetFlags_14a760(Elem *, s32);
void ModelResGetMeshCount_14c5c0(s32 *);
void ModelResGetMaterialCount_14c640(s32 *);
Src *ArrayGetChecked_14c7f0(s32 *, s32);
s32 ModelResGetFrameCount_14c850(s32 *);
s32 MemStackStrDup_14cf10(s32, s32);
s32 MemStackNew_14e1b0(s32, s32);
s32 MemStackNew_14e230(s32, s32);
void ModelCalcBBox_151e20(Self *, s32 *, s32);
s32 ModelBuildMeshes_152380(u8 *, s32 *, s32, s32);
s32 ParallelArray3Alloc_152ea0(s32, s32, s32);
void ArraySetChecked_152f90(s32, s32, Elem *);
void ParallelArray3Clear_153010(s32);
void ModelFrameCtor_150a90(void);
s32 ModelBuildFrames_1506c0(Self *self, s32 *list, s32 arg2, s32 heap);
}

#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))

static inline s32 nonempty(s32 *l) {
    return *l != 0;
}

s32 ModelBuildFrames_1506c0(Self *self, s32 *list, s32 arg2, s32 heap) {
    s32 buf[8];
    s32 failed;
    s32 ret;
    s32 n;
    s32 p;
    Elem *arr;
    s32 cnt;
    s32 i;
    Elem *e;
    Src *d;
    s32 r;
    u8 *t;

    if (list == 0) {
        return 0;
    }
    if (!nonempty(list)) {
        return 0;
    }
    ret = 0;
    n = ModelResGetFrameCount_14c850(list);
    ModelResGetMaterialCount_14c640(list);
    ModelResGetMeshCount_14c5c0(list);
    if (n == 0) {
        return 0;
    }
    failed = 0;
    p = MemStackNew_14e230(0x10, heap);
    if (p != 0) {
        ParallelArray3Clear_153010(p);
    }
    self->m104 = p;
    if (p != 0 && ParallelArray3Alloc_152ea0(p, n, heap) != 0) {
        arr = (Elem *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xF0 + 0x10, heap), ModelFrameCtor_150a90, 0, 0xF0, n);
        if (arr != 0) {
            cnt = 0;
            for (i = 0; i < n; i++) {
                e = &arr[i];
                e->f10();
                FrameResetXform_14a550(e);
                d = ArrayGetChecked_14c7f0(list, i);
                ArraySetChecked_152f90(self->m104, i, e);
                if (d == 0) {
                    continue;
                }
                if (d->m10 >= 0) {
                    FrameSetParent_149e90(e, &arr[d->m10]);
                } else {
                    ModelFrameSetPosLink_14a530(e, self->m180);
                    ModelFrameSetRotLink_14a500(e, self->m190);
                    FrameSetRotMode_14a250(e, 1);
                    ModelFrameSetScaleLink_14a4e0(e, self->m1A0);
                    cnt++;
                }
                e->m0 = MemStackStrDup_14cf10(d->m0, heap);
                ModelFrameSetMatrix_14a190(e, d->m20);
                Mat44To34_13e270(e->m30, d->m20);
                e->m2C = 1;
                e->m24 = d->m1F;
                ModelFrameSetFlags_14a760(e, d->m14);
                if (d->mC >= 0) {
                    FrameAllocExtMaybe_149390(e, heap);
                }
            }
            if (cnt > 0) {
                self->m110 = (s32 *)MemStackNew_14e1b0(cnt * 4, heap);
            }
            if (self->m110 != 0) {
                for (i = 0; i < n; i++) {
                    if (arr[i].m4 == 0) {
                        s32 k = self->m10C;
                        self->m10C = k + 1;
                        self->m110[k] = i;
                    }
                    if (self->m10C == cnt) {
                        break;
                    }
                }
            }
            t = self->m120;
            ret = 1;
            if (t != 0) {
                r = ModelBuildMeshes_152380(t, list, arg2, heap);
            } else {
                r = 0;
            }
            if (r == 0) {
                failed = 1;
            }
        }
    }
    if (failed != 0 || self->m124 != 0) {
        self->m108 = ConstructNewArray_100710(MemStackNew_14e1b0((n << 6) + 0x10, heap), 0, 0, 0x40, n);
        if (self->m108 != 0) {
            for (i = 0; i < n; i++) {
                d = ArrayGetChecked_14c7f0(list, i);
                if (d != 0) {
                    *(Blk *)(self->m108 + (i << 6)) = d->m60;
                }
            }
        }
    }
    self->m0 = ret;
    ModelCalcBBox_151e20(self, buf, 0);
    return ret;
}
