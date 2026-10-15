#include "types.h"
/* insect 0x00508670 -- 592 bytes, 148 instructions.  State dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 0); five arms plus a default. */

typedef struct Obj {
    u8  pad0000[0x4F90];
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5000 - 0x4FBD];
    u8  f5000[4];                   /* +0x5000 */
    u8  pad5004[0x5DB0 - 0x5004];
    s32 f5DB0;                      /* +0x5DB0 */
    u8  pad5DB4[0x5EFE - 0x5DB4];
    s16 f5EFE;                      /* +0x5EFE */
    u8  pad5F00[0x5FC8 - 0x5F00];
    f32 f5FC8;                      /* +0x5FC8 */
} Obj;

extern s32 func_201A90(void);
extern s32 insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void func_1E2F10(s32 h, s32 id, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern s32 insect_InsectLoaderIsIdle_512030(void *p);
extern void func_1E2670(s32 h, f32 v);
extern void func_1E2660(s32 h, s32 v);
extern void func_1E2650(s32 h);
extern s32 func_340420(void);
extern s32 func_1E56C0(s32 h);
extern void func_33F180(s32 h, s32 v);
extern void func_33E8F0(s32 h, s32 v);
extern s32 func_33DD30(s32 h);
extern s32 insect_InsectCursorSetGetEvents_5119f0(void *p, s32 k);

void insect_InsectBattleFlowStageCaption_508670(Obj *o)
{
    s32 h;
    s32 id;
    s32 p;

    h = func_201A90();
    id = o->f5EFE + 0xBEA;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        func_1E2F10(h, id, 0);
        insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
        o->f5DB0 = 0x1E;
        break;
    case 6:
        if (insect_InsectLoaderIsIdle_512030(o->f5000) != 0) {
            if (o->f5DB0 <= 0) {
                func_1E2670(h, 0.0f);
                func_1E2660(h, (s32)(15.0f / o->f5FC8));
                func_1E2650(h);
                p = func_340420();
                func_33F180(func_1E56C0(h), (s32)(10.0f / o->f5FC8));
                func_33E8F0(p, (s32)(10.0f / o->f5FC8));
                insect_InsectBattleSetStep_50d7a0(o, 9, 0, -1);
            }
        }
        break;
    case 9:
        if (func_33DD30(func_340420()) == 0) {
            o->f5DB0 = (s32)(10.0f / o->f5FC8);
            insect_InsectBattleSetStep_50d7a0(o, 10, 0, -1);
            o->f4FBC &= 0xFD;
        }
        break;
    case 10:
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1) != 0) {
            o->f5DB0 = 0;
        }
        if (o->f5DB0 <= 0) {
            insect_InsectBattleSetStep_50d7a0(o, 11, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 6, 2, -1);
        }
        break;
    case 11:
        insect_InsectBattleSetState_50d8c0(o, 6, 0, -1);
        break;
    }
}
