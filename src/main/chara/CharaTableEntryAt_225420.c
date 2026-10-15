#include "types.h"

typedef struct E_00225420 {
    u8 pad000[0x44];
} E_00225420;

typedef struct Obj_00225420 {
    u8 pad000[0x2C];
    E_00225420 *base;
    s16 count;
} Obj_00225420;

E_00225420 *CharaTableEntryAt_225420(Obj_00225420 *o, s32 n)
{
    if (o->base == 0) {
        goto bad;
    }
    if (n < 0) {
        goto bad;
    }
    if (o->count > n) {
        goto ok;
    }
bad:
    return 0;
ok:
    return &o->base[n];
}
