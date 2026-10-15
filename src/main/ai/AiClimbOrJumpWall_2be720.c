#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Tri {
    Vec p[3];
    Vec n;
    u8 pad40[6];
    s16 x46;
} Tri;

typedef struct Face {
    u8 pad0[0x46];
    s16 x46;
} Face;

typedef struct Tgt {
    u8 pad0[0x3D8];
    s32 x3D8;
} Tgt;

typedef struct Ai {
    u8 pad0[0xA8];
    s16 xA8;
    u8 padAA[0x190 - 0xAA];
    Vec x190;
    u8 pad1A0[0x262 - 0x1A0];
    s8 x262;
    u8 pad263;
    f32 x264;
    f32 x268;
} Ai;

extern void ClosestPointOnSegmentXZ_1c9e60(Vec *, Vec *, Vec *, Vec *);
extern f32 VecDistSqXZ_1cb390(Vec *, Vec *);
extern f32 VecDot3_1cba90(Vec *, Vec *);
extern void VecNormalizeXZ_1cbb50(Vec *, Vec *);
extern void VecSub_1cbd00(Vec *, Vec *, Vec *);
extern void VecCopy_1cbe30(Vec *, Vec *);
extern void CharaAddFlags_212460(Tgt *, s32);
extern s32 CharaGetActionMode_213850(Tgt *);
extern f32 CharaGetHeightAboveGround_238380(Tgt *);
extern Tri *CharaGetWallTriMaybe_238390(Tgt *, s32);
extern f32 CharaGetCollRadius_2386a0(Tgt *);
extern void CharaSetPosVec_2387a0(Tgt *, Vec *);
extern void CharaGetForwardVec_238830(Tgt *, Vec *);
extern void CharaGetPos_2388a0(Tgt *, Vec *);
extern s32 IsInBattle_288420(void);
extern void AiCollIgnoreTimerStart_2c1140(Ai *, Tgt *, s32);
extern void SrtGetPosThunk_1c7430(Tgt *, Vec *);
extern f32 D_0047DB74;

void AiClimbOrJumpWall_2be720(Ai *self, Tgt **tp, Vec *pos, s8 flag)
{
    Vec vE0;
    Vec vD0;
    Vec vC0;
    Vec vB0;
    Vec vA0;
    Vec v90;
    Vec v80;
    Vec v70;
    Vec v60;
    Tri *tri;
    Tgt *t;
    f32 dot;
    f32 range;
    f32 top;
    f32 d;
    f32 k;
    s32 c;

    if (tp == 0 || (t = *tp) == 0) {
        return;
    }
    if (self->xA8 >= 0x80 && self->xA8 < 0xA0) {
        return;
    }
    VecCopy_1cbe30(&vB0, pos);
    CharaGetPos_2388a0(t, &vE0);
    SrtGetPosThunk_1c7430(t, &vC0);
    VecSub_1cbd00(&vA0, &vE0, &vC0);
    CharaGetForwardVec_238830(t, &vD0);
    dot = VecDot3_1cba90(&vD0, &vA0);
    range = 2500;
    if (flag == 0) {
        range = 175.0f;
    }
    c = self->x262;
    if (c < 0) {
        self->x262 = c + 1;
        return;
    }
    if (c <= 0 && VecDistSqXZ_1cb390(&vE0, &vB0) <= range) {
        return;
    }
    if (CharaGetActionMode_213850(t) == 5) {
        return;
    }
    if (CharaGetActionMode_213850(t) == 6) {
        return;
    }
    if ((t->x3D8 & 0x40) && (CharaGetWallTriMaybe_238390(t, 0)->x46 & 0x20)) {
        tri = CharaGetWallTriMaybe_238390(t, 0);
        VecCopy_1cbe30(&v90, &tri->n);
        VecNormalizeXZ_1cbb50(&v90, &v90);
        d = VecDot3_1cba90(&v90, &vD0);
        d = (d < 0.0f) ? -d : d;
        if (d <= 0.75f) {
            return;
        }
        top = tri->p[0].y;
        if (top < tri->p[1].y) {
            top = tri->p[1].y;
        }
        if (top < tri->p[2].y) {
            top = tri->p[2].y;
        }
        if (self->x262 == 0) {
            if (!(dot < D_0047DB74)) {
                return;
            }
            d = top - vE0.y;
            if (!(d < 100.0f)) {
                return;
            }
            if (d < 40.0f) {
                VecCopy_1cbe30(&self->x190, &vE0);
                self->x264 = top + CharaGetCollRadius_2386a0(t);
                k = (f32)self->x262 / 5.0f;
                vE0.y += 7.0f + k * k;
                CharaSetPosVec_2387a0(t, &vE0);
                v60.x = vE0.x + 100.0f * vD0.z;
                v60.y = 0.0f;
                v60.z = vE0.z - 100.0f * vD0.x;
                v60.w = 1.0f;
                v70.x = vE0.x - 100.0f * vD0.z;
                v70.y = 0.0f;
                v70.z = vE0.z + 100.0f * vD0.x;
                v70.w = 1.0f;
                ClosestPointOnSegmentXZ_1c9e60(&v80, &v60, &v70, &tri->p[0]);
                self->x268 = VecDistSqXZ_1cb390(&v80, &tri->p[0]);
                ClosestPointOnSegmentXZ_1c9e60(&v80, &v60, &v70, &tri->p[1]);
                d = VecDistSqXZ_1cb390(&v80, &tri->p[1]);
                if (self->x268 < d) {
                    self->x268 = d;
                }
                ClosestPointOnSegmentXZ_1c9e60(&v80, &v60, &v70, &tri->p[2]);
                d = VecDistSqXZ_1cb390(&v80, &tri->p[2]);
                if (self->x268 < d) {
                    self->x268 = d;
                }
                if (self->x268 < CharaGetCollRadius_2386a0(t) * CharaGetCollRadius_2386a0(t)) {
                    self->x268 = CharaGetCollRadius_2386a0(t) * CharaGetCollRadius_2386a0(t);
                }
                self->x262++;
            } else {
                CharaAddFlags_212460(*tp, 0x10002);
                self->x262 = -60;
            }
            if ((u8)IsInBattle_288420() == 0) {
                AiCollIgnoreTimerStart_2c1140(self, t, 5);
            }
            return;
        }
        if (self->x264 < top + CharaGetCollRadius_2386a0(t)) {
            self->x264 = top + CharaGetCollRadius_2386a0(t);
        }
        if (vE0.y < vC0.y - 5.0f || !(vE0.y <= self->x264) || CharaGetHeightAboveGround_238380(t) < 0.5f) {
            self->x262 = -10;
            self->x264 = 0.0f;
            d = vE0.y - self->x190.y;
            d = (d < 0.0f) ? -d : d;
            if (d < 1.0f && VecDistSqXZ_1cb390(&vE0, &self->x190) < 1.0f) {
                self->x262 = -60;
            }
        } else {
            k = (f32)self->x262 / 5.0f;
            vE0.y += 7.0f + k * k;
            CharaSetPosVec_2387a0(t, &vE0);
            self->x262++;
        }
        if ((u8)IsInBattle_288420() == 0) {
            AiCollIgnoreTimerStart_2c1140(self, t, 5);
        }
        return;
    }
    if (self->x262 <= 0) {
        return;
    }
    if (!(vE0.y <= self->x264) || CharaGetHeightAboveGround_238380(t) < 0.5f || !(VecDistSqXZ_1cb390(&vE0, &self->x190) <= self->x268)) {
        self->x262 = -5;
        self->x264 = 0.0f;
        d = vE0.y - self->x190.y;
        d = (d < 0.0f) ? -d : d;
        if (d < 1.0f && VecDistSqXZ_1cb390(&vE0, &self->x190) < 1.0f) {
            self->x262 = -30;
        }
    } else {
        self->x262++;
        k = (f32)self->x262 / 5.0f;
        vE0.y += 7.0f + k * k;
        CharaSetPosVec_2387a0(t, &vE0);
    }
    if ((u8)IsInBattle_288420() == 0) {
        AiCollIgnoreTimerStart_2c1140(self, t, 5);
    }
}
