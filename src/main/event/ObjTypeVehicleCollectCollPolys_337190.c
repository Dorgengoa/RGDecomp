#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { f32 m[4][4]; } Mtx4;

typedef struct {
    u8 pad00[0xD0];
    u32 fD0;
    u8 padD4[0x44];
    void *f118;
} Obj;

extern s32 ObjTypeVehicleGetPlayState_3380a0(Obj *);
extern void XformGetMatrix_2e7750(void *, Mtx4 *);
extern void *EventVolumeRecGetVolumes_2e4d80(void *);
extern s32 EventVolumeRecGetCount_2e4d90(void *);
extern void EventVolumeGetMatrix_2e5630(void *, Vec4 *);
extern void MatMul_1cb700(Vec4 *, Mtx4 *, Vec4 *);
extern void MatMulVec4_1cb940(Vec4 *, Vec4 *, Vec4 *);
extern void VecCopy_1cbe30(void *, Vec4 *);
extern Vec4 D_00452E20[];

/* stack locals are allocated in REVERSE declaration order:
   c -> sp+0x80, b -> sp+0x100, m -> sp+0x140 */
s32 ObjTypeVehicleCollectCollPolys_337190(Obj *self, void *out, s32 limit) {
    Mtx4 m;
    Vec4 b[4];
    Vec4 c[8];
    void *src;
    s32 cnt;
    s32 i;
    s32 n;
    s32 k;
    s32 t;
    u8 *q;

    if (out == 0) {
        return 0;
    }
    /* boolean built, inverted, then tested: sltu/xori */
    t = !((self->fD0 & 0x80000000) != 0);
    if (t == 0) {
        return 0;
    }
    if (ObjTypeVehicleGetPlayState_3380a0(self) != 1 && ObjTypeVehicleGetPlayState_3380a0(self) != 3) {
        return 0;
    }
    if (self->f118 == 0) {
        return 0;
    }
    XformGetMatrix_2e7750((u8 *)self + 0x10, &m);
    src = EventVolumeRecGetVolumes_2e4d80(self->f118);
    cnt = EventVolumeRecGetCount_2e4d90(self->f118);
    i = 0;
    for (n = 0; n < cnt; i += 8, n++, src = (u8 *)src + 0x40) {
        /* a break, not a return: mwcc duplicates the shared tail's
           daddu $2,$17,$0 into the branch-likely delay slot */
        if (i + 8 > limit) {
            break;
        }
        EventVolumeGetMatrix_2e5630(src, &b[0]);
        MatMul_1cb700(&b[0], &m, &b[0]);
        k = 0;
        do {
            MatMulVec4_1cb940(&c[k], &b[0], &D_00452E20[k]);
            k++;
        } while (k < 8);

        q = (u8 *)out + i * 0x60;
        VecCopy_1cbe30(q, &c[1]);
        VecCopy_1cbe30(q + 0x10, &c[0]);
        VecCopy_1cbe30(q + 0x20, &c[5]);
        VecCopy_1cbe30(q + 0x30, &b[0]);

        q = (u8 *)out + (i + 1) * 0x60;
        VecCopy_1cbe30(q, &c[4]);
        VecCopy_1cbe30(q + 0x10, &c[5]);
        VecCopy_1cbe30(q + 0x20, &c[0]);
        VecCopy_1cbe30(q + 0x30, &b[0]);

        q = (u8 *)out + (i + 2) * 0x60;
        VecCopy_1cbe30(q, &c[3]);
        VecCopy_1cbe30(q + 0x10, &c[2]);
        VecCopy_1cbe30(q + 0x20, &c[7]);
        VecCopy_1cbe30(q + 0x30, &b[0]);

        q = (u8 *)out + (i + 3) * 0x60;
        VecCopy_1cbe30(q, &c[6]);
        VecCopy_1cbe30(q + 0x10, &c[7]);
        VecCopy_1cbe30(q + 0x20, &c[2]);
        VecCopy_1cbe30(q + 0x30, &b[0]);

        q = (u8 *)out + (i + 4) * 0x60;
        VecCopy_1cbe30(q, &c[2]);
        VecCopy_1cbe30(q + 0x10, &c[1]);
        VecCopy_1cbe30(q + 0x20, &c[6]);
        VecCopy_1cbe30(q + 0x30, &b[2]);

        q = (u8 *)out + (i + 5) * 0x60;
        VecCopy_1cbe30(q, &c[5]);
        VecCopy_1cbe30(q + 0x10, &c[6]);
        VecCopy_1cbe30(q + 0x20, &c[1]);
        VecCopy_1cbe30(q + 0x30, &b[2]);

        q = (u8 *)out + (i + 6) * 0x60;
        VecCopy_1cbe30(q, &c[0]);
        VecCopy_1cbe30(q + 0x10, &c[3]);
        VecCopy_1cbe30(q + 0x20, &c[4]);
        VecCopy_1cbe30(q + 0x30, &b[2]);

        q = (u8 *)out + (i + 7) * 0x60;
        VecCopy_1cbe30(q, &c[7]);
        VecCopy_1cbe30(q + 0x10, &c[4]);
        VecCopy_1cbe30(q + 0x20, &c[3]);
        VecCopy_1cbe30(q + 0x30, &b[2]);
    }
    return i;
}
