#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Ent {
    Vec pos;
    u32 flags;
    u32 pad14;
    f32 d;
    u32 pad1C;
} Ent;

typedef struct Obj {
    u8 pad0[0x1C0];
    Ent e[4];
    u8 pad240[0x10];
    s8 n250;
    s8 cur251;
} Obj;

typedef struct Chr {
    u8 pad0[0xA44];
    u32 xA44;
} Chr;

extern f32 Acosf_129178(f32);
extern f32 VecDistSq_1cb3c0(Vec *, Ent *);
extern void VecNormalizeXZ_1cbb50(Vec *, Vec *);
extern void VecSub_1cbd00(Vec *, Ent *, Ent *);
extern s32 CharaGetId_214a80(Chr *);
extern void CharaGetPos_2388a0(Chr *, Vec *);
extern void CharaGetRot_2388b0(Chr *, Vec *);
extern u8 IsInBattle_288420(void);
extern s32 AiRouteCheckCameraViewMaybe_2bcaa0(Obj *, Vec *, Ent *, s32, s32);
extern void CharaPlaceAt_2f3a40(s32, Ent *, s32, f32);
extern f32 D_0047D1FC;

s32 AiWarpToWaypointOffscreenMaybe_2bc6c0(Obj *obj, Chr *chr, s32 arg2, s32 idx) {
    Vec v90;
    Vec v80;
    Vec v70;
    Ent *e;
    f32 ang;
    f32 z;

    if (chr == 0) {
        return 0;
    }
    if (IsInBattle_288420() == 0) {
    if ((!(obj->e[idx].d <= 1000.0f) || (chr->xA44 & 0x20000)) && idx < obj->n250) {
        CharaGetPos_2388a0(chr, &v90);
        if ((idx == obj->n250 - 1 || !(obj->e[idx + 1].flags & 8))) {
            e = &obj->e[idx];
            if (AiRouteCheckCameraViewMaybe_2bcaa0(obj, &v90, e, arg2, (chr->xA44 & 0x20000) != 0) != 0) {
                if (VecDistSq_1cb3c0(&v90, e) < 5.0f) {
                    idx++;
                    if (idx >= obj->n250) {
                        return 0;
                    }
                }
                obj->cur251 = idx;
                CharaGetRot_2388b0(chr, &v80);
                ang = v80.y;
                if ((obj->e[idx].flags & 4) && idx < obj->n250 - 1) {
                    VecSub_1cbd00(&v70, &obj->e[idx + 1], &obj->e[idx]);
                    VecNormalizeXZ_1cbb50(&v70, &v70);
                    z = v70.z;
                    if (z < 1.0f) {
                        if (z > -1.0f) {
                            ang = Acosf_129178(z);
                            if (v70.x < 0.0f) {
                                ang = ang * -1.0f;
                            }
                        } else {
                            ang = D_0047D1FC;
                        }
                    }
                }
                CharaPlaceAt_2f3a40(CharaGetId_214a80(chr), &obj->e[idx], 0xF, ang);
                return 1;
            }
        }
    }
    }
    return 0;
}
