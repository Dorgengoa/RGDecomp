/* rgp:protos */
#define RGP_SELF_TreasureBoxGetEncounterId_33aa40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj3 {
    u8 pad000[0x4];
    s16 m04;
};

struct Obj2 {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    struct Obj3 *m18;
};

struct Obj1 {
    u8 pad000[0x12];
    s16 m12;
};

struct Obj0 {
    u8 pad000[0x68];
    struct Obj1 *m68;
};

/*rgp*/
/*rgp*/

s32 TreasureBoxGetEncounterId_33aa40(struct Obj0 *p0)
{
    s32 r;
    struct Obj2 *o;

    if (p0->m68 == 0) {
        return -1;
    }
    r = p0->m68->m12;
    if (r == 0x3563) {
        o = ((struct Obj2 *)GetGameData_1fede0());
        if (o != 0 && o->m18->m04 == 0xA && ((short)StateVarGet_3ccac0(o->m10, 0xD)) >= 3) {
            r = 0x35C7;
        }
    }
    return r;
}
