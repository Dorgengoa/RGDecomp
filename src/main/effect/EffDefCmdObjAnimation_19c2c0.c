#include "types.h"

typedef struct Ctx19c {
    u8 pad0[0x20];
    s32 m20;
    u8 pad24[0x40 - 0x24];
    s32 m40;
    u8 pad44[0x4C - 0x44];
    void *m4C;
} Ctx19c;

extern void *MemStackNew_14e230(s32, s32);
extern s32 SlotGetInt_15f720(s64 *);
extern s32 VariantGetInt_15f780(s64 *);
extern void EffCurveAllocKeys_197670(void *, s32, s32, s32, s32);
extern void *EffCurveCtorAlpha_19c960(void *);
extern void *EffCurveCtorColorRgb_19c9c0(void *);
extern void *EffCurveCtorColorB_19ca20(void *);
extern void *EffCurveCtorColorG_19ca80(void *);
extern void *EffCurveCtorColorR_19cae0(void *);
extern void *EffCurveCtorV_19cb40(void *);
extern void *EffCurveCtorU_19cba0(void *);
extern void *EffCurveCtorScaleXyz_19cc00(void *);
extern void *EffCurveCtorScaleZ_19cc60(void *);
extern void *EffCurveCtorScaleY_19ccc0(void *);
extern void *EffCurveCtorScaleX_19cd20(void *);
extern void *EffCurveCtorRotXyz_19cd80(void *);
extern void *EffCurveCtorRotZ_19cde0(void *);
extern void *EffCurveCtorRotY_19ce40(void *);
extern void *EffCurveCtorRotX_19cea0(void *);
extern void *EffCurveCtorPosXyz_19cf00(void *);
extern void *EffCurveCtorPosZ_19cf60(void *);
extern void *EffCurveCtorPosY_19cfc0(void *);
extern void *EffCurveCtorPosX_19d020(void *);
extern u32 strlen(const char *);
extern s32 strcmp(const char *, const char *);
extern char D_0045A7F0[];
extern char D_0045A7F8[];
extern char D_0045A800[];
extern char D_0045A808[];
extern char D_0045A810[];

#define NEW(ctor) { void *m_ = MemStackNew_14e230(0x24, c->m20); if (m_ != 0) { m_ = ctor(m_); } c->m4C = m_; }

s32 EffDefCmdObjAnimation_19c2c0(s64 *arg0, s32 arg1, Ctx19c **arg2)
{
    Ctx19c *c;
    s32 id;
    char *name;
    char *opt;
    s32 k;
    s32 mode;
    void *r;

    c = *arg2;
    id = VariantGetInt_15f780(arg0++);
    name = (char *)SlotGetInt_15f720(arg0++);
    opt = 0;
    if (arg1 >= 3) {
        opt = (char *)SlotGetInt_15f720(arg0);
    }
    if (name == 0) {
        r = 0;
        goto done;
    }
    {
        c->m4C = 0;
        k = -1;
        if (*name == 'x') {
            k = 0;
        } else if (*name == 'y') {
            k = 1;
        } else if (*name == 'z') {
            k = 2;
        } else if (*name == 'r') {
            k = 0;
        } else if (*name == 'g') {
            k = 1;
        } else if (*name == 'b') {
            k = 2;
        } else if (*name == 'a') {
            k = 3;
        } else if (*name == 'u') {
            k = 0;
        } else if (*name == 'v') {
            k = 1;
        }
        if (strlen(name) > 1) {
            if (strcmp(name, D_0045A810) == 0) {
                k = 100;
            } else if (strcmp(name, D_0045A808) == 0) {
                k = 100;
            }
        }
        mode = 1;
        if (opt != 0) {
            if (strcmp(opt, D_0045A800) == 0) {
                mode = 0;
            } else if (strcmp(opt, D_0045A7F8) == 0) {
                mode = 1;
            } else if (strcmp(opt, D_0045A7F0) == 0) {
                mode = 2;
            }
        }
        switch (c->m40) {
        case 0:
            break;
        case 1:
            switch (k) {
            case 0:
                NEW(EffCurveCtorPosX_19d020)
                break;
            case 1:
                NEW(EffCurveCtorPosY_19cfc0)
                break;
            case 2:
                NEW(EffCurveCtorPosZ_19cf60)
                break;
            case 100:
                NEW(EffCurveCtorPosXyz_19cf00)
                break;
            }
            break;
        case 2:
            switch (k) {
            case 0:
                NEW(EffCurveCtorRotX_19cea0)
                break;
            case 1:
                NEW(EffCurveCtorRotY_19ce40)
                break;
            case 2:
                NEW(EffCurveCtorRotZ_19cde0)
                break;
            case 100:
                NEW(EffCurveCtorRotXyz_19cd80)
                break;
            }
            break;
        case 3:
            switch (k) {
            case 0:
                NEW(EffCurveCtorScaleX_19cd20)
                break;
            case 1:
                NEW(EffCurveCtorScaleY_19ccc0)
                break;
            case 2:
                NEW(EffCurveCtorScaleZ_19cc60)
                break;
            case 100:
                NEW(EffCurveCtorScaleXyz_19cc00)
                break;
            }
            break;
        case 6:
            switch (k) {
            case 0:
                NEW(EffCurveCtorU_19cba0)
                break;
            case 1:
                NEW(EffCurveCtorV_19cb40)
                break;
            }
            break;
        case 4:
            switch (k) {
            case 0:
                NEW(EffCurveCtorColorR_19cae0)
                break;
            case 1:
                NEW(EffCurveCtorColorG_19ca80)
                break;
            case 2:
                NEW(EffCurveCtorColorB_19ca20)
                break;
            case 100:
                NEW(EffCurveCtorColorRgb_19c9c0)
                break;
            }
            break;
        case 7:
            switch (k) {
            case 0:
                NEW(EffCurveCtorColorR_19cae0)
                break;
            case 1:
                NEW(EffCurveCtorColorG_19ca80)
                break;
            case 2:
                NEW(EffCurveCtorColorB_19ca20)
                break;
            case 3:
                NEW(EffCurveCtorAlpha_19c960)
                break;
            }
            break;
        case 5:
            switch (k) {
            case 3:
                NEW(EffCurveCtorAlpha_19c960)
                break;
            }
            break;
        }
        if (c->m4C != 0) {
            EffCurveAllocKeys_197670(c->m4C, c->m20, id, mode, 0);
        }
        r = c->m4C;
    }
done:
    if (r == 0) {
        return 0;
    }
    return 1;
}
