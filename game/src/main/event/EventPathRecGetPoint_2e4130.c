/* rgp:protos */
#define RGP_SELF_EventPathRecGetPoint_2e4130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_002e4130 {
    u8 pad000[0x30];
} E_002e4130;

typedef struct Obj_002e4130 {
    u8 pad000[0x10];
    E_002e4130 *base;
    u8 pad014[0x4];
    s16 count;
} Obj_002e4130;

E_002e4130 *EventPathRecGetPoint_2e4130(Obj_002e4130 *o, s32 n)
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
