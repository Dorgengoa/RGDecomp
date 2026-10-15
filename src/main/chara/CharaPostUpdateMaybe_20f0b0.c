#include "types.h"

typedef struct {
    f32 start;
    f32 len;
} Seg;

extern f32 ModelObjGetMotionPhase_1add70(s32);
extern s32 ModelObjGetMotionName_1add90(s32);
extern s32 StrEqualNonNull_1ca6c0(s32, s32);
extern void CharaHitInfoInit_219140(s8 *);
extern void ActCfgTableFireTimeClsn_21f840(void *, s8 *, s32, s32, f32, f32);
extern void ActCfgTableFireNormalTimeClsn_21f960(void *, s8 *, s32, s32, f32, f32);
extern void ActCfgTableRunTimeEvnts_221f40(void *, s32, s32, s32, f32, f32);
extern void ActCfgTableRunNormalTimeEvnts_222250(void *, s32, s32, s32, f32, f32);
extern s32 ActCfgTableGetCollIgnoreMask_223cd0(s32);
extern s32 ActCfgTableGetFlags64_223ce0(s32);
extern void CharaSetCollIgnoreMask_238940(s8 *, s32);
extern void CharaSetFlags3D0_238970(s8 *, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetParamIntById_2e04a0(s32, s32, s32, s32);
extern s32 EffectExistsById_2e1130(s32, s32);

void CharaPostUpdateMaybe_20f0b0(s8 *arg0, f32 dt) {
    Seg seg[2];
    s32 n;
    s32 id;
    s32 i;
    f32 t;
    f32 b;
    f32 a;
    s32 h;
    u32 flags;
    u8 on;


    if (*(s32 *)(arg0 + 0x428) != 0) {
        if (*(s32 *)(arg0 + 0x3F4) != 0) {
            n = 0;
            id = 0;
            if (*(s8 *)(arg0 + 0xA8C) != 0) {
                id = ModelObjGetMotionName_1add90(*(s32 *)(arg0 + 0x3F4));
            }
            t = ModelObjGetMotionPhase_1add70(*(s32 *)(arg0 + 0x3F4));
            if (StrEqualNonNull_1ca6c0(*(s32 *)(arg0 + 0x400), id) != 0) {
                f32 s = *(f32 *)(arg0 + 0x3F8);
                if (s <= t) {
                    n += 1;
                    seg[0].start = s;
                    seg[0].len = t - s;
                } else {
                    seg[1].start = 0.0f;
                    seg[1].len = t;
                    seg[0].start = s;
                    seg[0].len = 1.0f - s;
                    n += 2;
                }
            } else {
                seg[0].len = t;
                n += 1;
                seg[0].start = 0.0f;
            }
            for (i = 0; i < n; i++) {
                if (*(s16 *)(arg0 + 0xA38) == 0) {
                    b = seg[i].len;
                    a = seg[i].start;
                    ActCfgTableFireNormalTimeClsn_21f960(*(void **)(arg0 + 0x428), arg0, *(s16 *)(arg0 + 0xA32), id, a, b);
                    ActCfgTableRunNormalTimeEvnts_222250(*(void **)(arg0 + 0x428), *(s16 *)(arg0 + 0x424), *(s16 *)(arg0 + 0xA32), id, a, b);
                } else {
                    b = seg[i].len;
                    a = seg[i].start;
                    ActCfgTableFireTimeClsn_21f840(*(void **)(arg0 + 0x428), arg0, *(s32 *)(arg0 + 0xA0C), id, a, b);
                    ActCfgTableRunTimeEvnts_221f40(*(void **)(arg0 + 0x428), *(s16 *)(arg0 + 0x424), *(s32 *)(arg0 + 0xA0C), id, a, b);
                }
            }
        }
        CharaSetFlags3D0_238970(arg0, ActCfgTableGetFlags64_223ce0(*(s32 *)(arg0 + 0x428)));
        CharaSetCollIgnoreMask_238940(arg0, ActCfgTableGetCollIgnoreMask_223cd0(*(s32 *)(arg0 + 0x428)));
    }
    if (*(s32 *)(arg0 + 0xB0C) >= 0) {
        h = GetEffectMgr_2d9040();
        if (EffectExistsById_2e1130(h, *(s32 *)(arg0 + 0xB0C)) == 0) {
            *(s32 *)(arg0 + 0xB0C) = -1;
        } else if (*(s16 *)(arg0 + 0xA36) != 11) {
            EffectSetParamIntById_2e04a0(h, *(s32 *)(arg0 + 0xB0C), 0, 1);
        }
    }
    *(s32 *)(arg0 + 0xA50) = *(s32 *)(arg0 + 0xA54);
    flags = *(u32 *)(arg0 + 0xA44);
    on = (flags & 0x20000) != 0;
    if (on) {
        flags |= 0x10000;
    } else {
        flags &= ~0x10000;
    }
    *(u32 *)(arg0 + 0xA44) = flags;
    *(u32 *)(arg0 + 0xA44) &= ~0x20000;
    *(u32 *)(arg0 + 0xA44) &= ~0x8000;
    *(u32 *)(arg0 + 0xA44) &= ~0x400000;
    *(f32 *)(arg0 + 0xAE0) -= dt;
    if (*(f32 *)(arg0 + 0xAE0) < 0.0f) {
        *(f32 *)(arg0 + 0xAE0) = 0.0f;
    }
    CharaHitInfoInit_219140(arg0 + 0x870);
    *(u64 *)(arg0 + 0x568) &= ~(1ULL << 54);
}
