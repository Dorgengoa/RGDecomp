/* rgp:protos */
#define RGP_SELF_CagePlaceCursorSet_39af40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Q_FUN_0039af40 {
    u8 d[0x10];
} Q_FUN_0039af40;

typedef struct Obj_FUN_0039af40 {
    u8 pad000[0xB0];
    Q_FUN_0039af40 fB0;
    Q_FUN_0039af40 fC0;
    Q_FUN_0039af40 fD0;
    Q_FUN_0039af40 fE0;
    s32 fF0;
    s32 fF4;
} Obj_FUN_0039af40;

/*rgp*/

void CagePlaceCursorSet_39af40(Obj_FUN_0039af40 *o, s32 a, Q_FUN_0039af40 *b, Q_FUN_0039af40 *c)
{
    VecCopy_1cbe30(&o->fB0, b);
    VecCopy_1cbe30(&o->fC0, c);
    VecCopy_1cbe30(&o->fD0, &o->fB0);
    VecCopy_1cbe30(&o->fE0, &o->fC0);
    o->fF0 = a;
    o->fF4 = 0;
}
