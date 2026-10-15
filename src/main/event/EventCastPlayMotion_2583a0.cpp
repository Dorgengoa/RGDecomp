#pragma optimization_level 3
#pragma opt_common_subs off
#include "types.h"

class Obj {
public:
    u8 pad[0x1B0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15(f32);
};

typedef struct Row {
    s32 f0;
    s32 f4;
    s32 f8;
    Obj *obj;
} Row;

typedef struct Res {
    u8 pad[0x24];
    f32 f24;
    f32 f28;
    f32 f2C;
} Res;

extern "C" {
f32 Floorf_128e30(f32);
Res *MotionListFindByName_1721d0(s32 *, char *, s32 *, s32 *);
void ModelObjPlayMotionByName_1867a0(Obj *, char *, s32);
void ModelObjSetMotionPhase_1add80(Obj *, f32);
s32 GetGameMode_1f59c0(void);
s32 GetAttackChain_1fdb40(void);
s32 ModelHasMotion_20a5b0(Obj *, char *);
f32 AttackChainGetTimer_382e70(s32);
s32 strcmp(const char *, const char *);
char *strcpy(char *, const char *);
extern char D_0045EDD0[];
extern char D_0045EDD8[];
extern char D_0045EDE0[];
extern char D_0045EDE8[];
extern char D_0045EDF0[];
extern char D_0045EDF8[];
extern char D_0045EE08[];
}

extern "C" s32 EventCastPlayMotion_2583a0(Row *tbl, s32 idx, char *name, s32 flags)
{
    s32 ac;
    s32 a8;
    s32 pos[3];
    char buf[0x28];
    Obj **pp;
    Row *row;
    Res *res;
    f32 k;
    f32 t;

    if (idx < 0 || idx >= 0x20) {
        return 0;
    }
    row = &tbl[idx];
    if (row->f0 != 0) {
        return 0;
    }
    pp = &row->obj;
    if (*pp == 0) {
        return 0;
    }
    if (GetGameMode_1f59c0() == 9) {
        flags |= 4;
    }
    strcpy(buf, name);
    if (GetGameMode_1f59c0() == 10 || GetGameMode_1f59c0() == 9) {
        if (ModelHasMotion_20a5b0(*pp, D_0045EDD0) != 0 && ModelHasMotion_20a5b0(*pp, D_0045EDD8) != 0) {
            if (strcmp(buf, D_0045EDE0) == 0) {
                strcpy(buf, D_0045EDD0);
            }
            if (strcmp(buf, D_0045EDE8) == 0) {
                strcpy(buf, D_0045EDF0);
            }
            if (strcmp(buf, D_0045EDF8) == 0) {
                strcpy(buf, D_0045EE08);
            }
        }
    }
    ModelObjPlayMotionByName_1867a0(*pp, buf, flags);
    if (GetGameMode_1f59c0() == 9) {
        {
            s32 *src = (s32 *)((u8 *)*pp + 0x1F0);
            pos[0] = src[0];
            pos[1] = src[1];
            pos[2] = src[2];
        }
        res = MotionListFindByName_1721d0(pos, buf, &ac, &a8);
        if (res != 0) {
            t = AttackChainGetTimer_382e70(GetAttackChain_1fdb40());
            pp = &((Row *)((idx << 4) + (s32)tbl))->obj;
            k = res->f2C / (res->f28 - res->f24);
            (*pp)->v15(1.0f);
            ModelObjSetMotionPhase_1add80(*pp, k * (t - Floorf_128e30(t)));
        }
    }
    return 1;
}
