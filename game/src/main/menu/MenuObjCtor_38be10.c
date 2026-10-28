/* rgp:protos */
#define RGP_SELF_MenuObjCtor_38be10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0038be10 {
    u8 pad000[0x1B0];
    const u8 *f1B0;
    u8 pad1B4[0x5DC];
    u8 f790[0x1B8];
    u8 f948[0x4];
    u8 f94C[0x4];
} Obj_FUN_0038be10;

extern u8 D_00470F50[];
/*rgp*/
extern void *memset(void *d, s32 c, u32 n);
/*rgp*/
/*rgp*/

Obj_FUN_0038be10 *MenuObjCtor_38be10(Obj_FUN_0038be10 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    ModelObjExCtor_1c4920(o, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    o->f1B0 = D_00470F50;
    *(s32 *)o->f94C = 0;
    *(s32 *)o->f948 = 0;
    memset(o->f790, 0, 0x1D0);
    BitArray16Ctor_3842e0((u8 *)o + 0x986);
    MenuObjParamsCtor_388010((u8 *)o + 0x990);
    return o;
}
