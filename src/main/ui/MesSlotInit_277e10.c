#include "types.h"

typedef struct Obj_FUN_00277e10 {
    s16 f00;
    s16 f02;
    s32 f04;
    u8 f08;
    u8 pad009[0x3F];
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
} Obj_FUN_00277e10;

typedef struct T_FUN_00277e10 T_FUN_00277e10;

extern T_FUN_00277e10 *GetDrawCtx_15de80(void);
extern s16 DrawEnvGetWidth_1451e0(T_FUN_00277e10 *t);
extern s16 DrawEnvGetHeight_1451d0(T_FUN_00277e10 *t);
extern void TextStyleInit_26c610(void *p);
extern void TextStyleSetFontType_26edf0(void *p, s32 n);

void MesSlotInit_277e10(Obj_FUN_00277e10 *o)
{
    T_FUN_00277e10 *t;

    t = GetDrawCtx_15de80();
    o->f00 = DrawEnvGetWidth_1451e0(t);
    o->f02 = DrawEnvGetHeight_1451d0(t);
    o->f04 = 0;
    TextStyleInit_26c610(&o->f08);
    TextStyleSetFontType_26edf0(&o->f08, 1);
    o->f48 = 0x338;
    o->f50 = 0;
    o->f4C = 0;
    o->f54 = -1;
}
