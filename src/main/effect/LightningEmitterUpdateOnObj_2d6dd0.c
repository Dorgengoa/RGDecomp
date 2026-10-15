#include "types.h"

typedef struct Ent {
    s16 f0;         /* 0x00 (0x30) */
    u8 pad2[6];
    s16 f8;         /* 0x08 (0x38) */
    s16 fA;         /* 0x0A (0x3A) */
    s8 fC;          /* 0x0C (0x3C) */
    u8 padD[0x23];
} Ent;

typedef struct Self {
    u8 pad[0x30];
    Ent ent[1];
} Self;

typedef struct Obj {
    u8 pad[0xC0];
    s8 fC0;
} Obj;

typedef struct Info {
    u8 pad[4];
    f32 f4;
} Info;

Info *ObjGetNthAttachPointPos_1ade20(s32, s32, s32, f32 *);
s32 ObjRecGetLiveObject_1c4a90(s32, s16);
s32 GetStaticScene_1c6c70();
f32 RandRangeFloat_1ca5d0(f32);
Obj *LightningMgrFindFreeBolt_2d64f0(Self *);
s32 LightningBoltGetMidPoint_2d6920(Obj *, f32 *);
void LightningBoltBuild_2d6960(Obj *, f32 *, f32 *, f32);
void sceVu0CopyVector(f32 *, f32 *);

void LightningEmitterUpdateOnObj_2d6dd0(Self *self, s32 idx) {
    f32 a[4];
    f32 b[4];
    s32 o;
    s32 n;
    s32 i;
    Obj *p;
    Info *r;
    f32 s;
    f32 t;

    if (self->ent[idx].f8 % 3 == 0) {
        o = ObjRecGetLiveObject_1c4a90(GetStaticScene_1c6c70(), self->ent[idx].f0);
        if (o == 0) {
            return;
        }
        n = (s32)(1.0f + ObjGetNthAttachPointPos_1ade20(o, 0, 0, a)->f4 / 40.0f);
        for (i = 0; i < n; i++) {
            p = LightningMgrFindFreeBolt_2d64f0(self);
            if (p != 0) {
                r = ObjGetNthAttachPointPos_1ade20(o, 0, 0, a);
                a[0] += r->f4 / 4.0f - RandRangeFloat_1ca5d0(r->f4 / 2.0f);
                a[1] += r->f4 / 4.0f - RandRangeFloat_1ca5d0(r->f4 / 2.0f);
                a[2] += r->f4 / 4.0f - RandRangeFloat_1ca5d0(r->f4 / 2.0f);
                sceVu0CopyVector(b, a);
                s = 5.0f + r->f4 / 20.0f;
                t = 2.0f * s;
                b[0] += s - RandRangeFloat_1ca5d0(t);
                b[1] += s - RandRangeFloat_1ca5d0(t);
                b[2] += s - RandRangeFloat_1ca5d0(t);
                LightningBoltBuild_2d6960(p, a, b, r->f4);
                p->fC0 = self->ent[idx].fC;
            }
            if (p == 0) {
                continue;
            }
            r = ObjGetNthAttachPointPos_1ade20(o, 0, 0, a);
            if (LightningBoltGetMidPoint_2d6920(p, a) != 0 && r != 0) {
                sceVu0CopyVector(b, a);
                s = 5.0f + r->f4 / 20.0f;
                t = 2.0f * s;
                b[0] += s - RandRangeFloat_1ca5d0(t);
                b[1] += s - RandRangeFloat_1ca5d0(t);
                b[2] += s - RandRangeFloat_1ca5d0(t);
                p = LightningMgrFindFreeBolt_2d64f0(self);
                if (p != 0) {
                    LightningBoltBuild_2d6960(p, a, b, r->f4);
                    p->fC0 = self->ent[idx].fC;
                }
            }
        }
    }
    {
        Ent *e2 = (Ent *)((u8 *)self->ent + ((idx * 3) << 4));
        if (--e2->f8 <= 0) {
            self->ent[idx].fA = 0;
        }
    }
}
