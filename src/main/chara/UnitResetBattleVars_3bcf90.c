#include "types.h"

typedef struct {
    u8 pad0[0x86];
    s16 x;
    s16 y;
    s16 z;
} Sub;

typedef struct {
    u8 pad0[0x1C0];
    u8 f1C0 : 1;
    u8 pad1C1[3];
    f32 f1C4;
    u8 f1C8 : 1;
    u8 pad1C9[0x1DC - 0x1C9];
    s32 f1DC;
    f32 f1E0;
    f32 f1E4;
    f32 f1E8;
    s32 f1EC;
    u8 pad1F0[0x234 - 0x1F0];
    Sub *p234;
} Obj;

typedef struct {
    u8 pad0[0x24C];
    u8 flag : 1;
} Mgr2;

typedef struct {
    u8 pad0[0x20];
    Mgr2 *p20;
} Mgr;

extern const s32 D_00465CD0[];
extern Mgr *D_00483818;

s32 UnitResetBattleVars_3bcf90(Obj *arg0) {
    if (D_00483818 == NULL) {
        return 0;
    }
    if (D_00483818->p20->flag) {
        return 0;
    }
    arg0->f1EC = 0;
    arg0->f1DC = 0;
    arg0->f1E0 = arg0->p234->x;
    arg0->f1E4 = arg0->p234->y;
    arg0->f1E8 = arg0->p234->z;
    arg0->f1C0 = 1;
    arg0->f1C4 = D_00465CD0[0];
    arg0->f1C8 = 0;
    return 1;
}
