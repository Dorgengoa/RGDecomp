/* rgp:protos */
#define RGP_SELF_UnitCanActKind18_3bdc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x234];
    struct Obj1 *m234;
};

struct Obj1 {
    u8 pad000[0x82];
    u8 m82;
};

s32 UnitCanActKind18_3bdc10(struct Obj0 *p0)
{
    struct Obj1 * t0;
    u8 t1;

    t0 = p0->m234;
    if (t0 != 0) {
        t1 = p0->m234->m82;
        return (t1 & 1);
    }
    return 0;
}
