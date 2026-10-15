#include "types.h"

typedef struct Obj_FUN_0038be10 {
    u8 pad000[0x1B0];
    const u8 *f1B0;
    u8 pad1B4[0x5DC];
    u8 f790[0x1B8];
    u8 f948[0x4];
    u8 f94C[0x4];
} Obj_FUN_0038be10;

extern const u8 D_00470F50[];
extern void ModelObjExCtor_1c4920(Obj_FUN_0038be10 *o);
extern void *memset(void *d, s32 c, u32 n);
extern void BitArray16Ctor_3842e0(void *p);
extern void MenuObjParamsCtor_388010(void *p);

Obj_FUN_0038be10 *MenuObjCtor_38be10(Obj_FUN_0038be10 *o)
{
    ModelObjExCtor_1c4920(o);
    o->f1B0 = D_00470F50;
    *(s32 *)o->f94C = 0;
    *(s32 *)o->f948 = 0;
    memset(o->f790, 0, 0x1D0);
    BitArray16Ctor_3842e0((u8 *)o + 0x986);
    MenuObjParamsCtor_388010((u8 *)o + 0x990);
    return o;
}
