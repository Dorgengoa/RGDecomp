/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
s32 StrEqualNonNull_1ca6c0(char *, const char *);
s32 ActCfgTableFindActionByName_223d20(s32, s32);
s32 CharaTableGetStepCount_225410(s32);
s32 CharaTableEntryAt_225420(s32, s32);
s32 CharaTableGetActionKind_225d30(s32);
s32 CharaTableEntryGetEndType_226100(s32);
s32 CharaTableEntryCondMatchesMaybe_226110(s32, char *, s64, f32);
s32 CharaTableEntryGetMotionFlags_226240(s32);
s32 CharaIsHeadUnderwaterMaybe_238250(struct Obj *);
f32 CharaGetHeightAboveGround_238380(struct Obj *);
char *CharaGetCurMotionName_238560(struct Obj *);
f32 CharaGetMotionFrame_238570(struct Obj *);
s32 IsInBattle_288420(void);
char *strcpy(char *, const char *);
}
extern "C" volatile f32 D_0045B080[];
extern "C" char D_0045C8E0[];
extern "C" char D_0045C8F0[];
extern "C" char D_0045C900[];
extern "C" char D_0045C910[];
extern "C" f32 D_0047D34C;


struct Obj {
    u8 pad84[0x84];
    f32 x84;
    u8 pad3D0[0x348];
    u64 x3D0;
    s32 x3D8;
    u8 pad424[0x48];
    s16 x424;
    u8 pad428[0x2];
    s32 x428;
    u8 pad570[0x144];
    s64 x570;
    u8 padA0C[0x494];
    s32 xA0C;
    u8 padA20[0x10];
    s32 xA20;
    f32 xA24;
    u8 padA2E[0x6];
    s16 xA2E;
    u8 padA38[0x8];
    s16 xA38;
    u8 padA44[0xA];
    s32 xA44;
    u8 padAD0[0x88];
    f32 xAD0;
};

static inline bool canAct(Obj *a) {
    s32 fl;
    if (a->x3D0 & 0x400000000000ULL) return true;
    fl = a->x3D8;
    if (fl & 1) return true;
    if (!(fl & 4)) return true;
    if (CharaGetHeightAboveGround_238380(a) < D_0047D34C * D_0045B080[0] - a->x84) return true;
    return false;
}

static inline bool isSet(s32 x, s32 m) { return (x & m) != 0; }

static inline bool flagOk(s32 x) {
    bool ok = false;
    if (x & 0x1000000) {
        if (((x & 0x800000) != 0) ^ 1) ok = true;
    }
    return ok;
}

extern "C" s32 CharaActionGetCancelMaskMaybe_210b60(Obj *a) {
    s32 ret;
    bool ok;
    s32 h;
    s32 t;
    char *name;
    s32 r;
    u8 buf[0x20] __attribute__((aligned(16)));

    ret = 7;
    if (a->xA38 == 0) return ret;
    h = ActCfgTableFindActionByName_223d20(a->x428, a->xA0C);
    if (h == 0) return ret;
    t = CharaTableEntryAt_225420(h, a->xA20);
    if (t == 0) return ret;
    if (a->xA20 + 1 < ((short)CharaTableGetStepCount_225410(h))) ret &= ~6;
    { u8 *p_ = buf; u32 n_ = 0x20; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }
    name = CharaGetCurMotionName_238560(a);
    if (a->xA2E == 1) {
        if (((unsigned char)StrEqualNonNull_1ca6c0(name, D_0045C8E0))) {
            name = (char *)buf;
            strcpy(name, D_0045C8F0);
        }
        if (((unsigned char)StrEqualNonNull_1ca6c0(name, D_0045C900))) {
            name = (char *)buf;
            strcpy(name, D_0045C910);
        }
    }
    if (CharaTableEntryCondMatchesMaybe_226110(t, name, a->x570, CharaGetMotionFrame_238570(a)) == 0) {
        if (((short)CharaTableEntryGetEndType_226100(t)) != 4 || !(a->x3D8 & 0x10)) {
        if (((short)CharaTableEntryGetEndType_226100(t)) != 5 || (!canAct(a) && !(a->x3D8 & 0x10))) ret &= ~7;
        }
    } else {
        switch (((short)CharaTableEntryGetEndType_226100(t))) {
        case 1:
            if (a->xAD0 < a->xA24) ret &= ~7;
            break;
        case 0:
            if (CharaTableEntryGetMotionFlags_226240(t) & 2) {
                ret |= 1;
                break;
            }
            ok = false;
            if ((a->xA44 & 0x1000000) && (((a->xA44 & 0x800000) != 0) ^ 1)) ok = true;
            if (!ok) {
                if (((short)CharaTableGetActionKind_225d30(h)) == 1) break;
            }
            {
                s16 v = a->x424;
                ret &= ~3;
                if (v < 0x80 || v >= 0x9C) {
                    if (a->xA2E == 0 || ((unsigned char)IsInBattle_288420()) != 0) ret &= ~4;
                }
            }
            break;
        case 2:
        case 3:
            ok = false;
            if ((a->xA44 & 0x1000000) && (((a->xA44 & 0x800000) != 0) ^ 1)) ok = true;
            if (ok) {
                r = ((short)CharaTableGetActionKind_225d30(h));
                if (r != 0x1F && r != 0x1E && r != 0x13) ret &= ~3;
            }
            break;
        case 4:
            if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(a)) == 0) {
                if (!canAct(a) && !(a->x3D8 & 0x10)) ret &= ~1;
            }
            break;
        }
    }
    if (a->x3D0 & 0x40000) ret |= 6;
    if (a->x3D0 & 0x20000) ret |= 1;
    return ret;
}
