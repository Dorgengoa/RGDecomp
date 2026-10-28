/* rgp:protos */
#define RGP_SELF_StateVarGetByName_3cca60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj2 {
    s16 m00;
};

/*rgp*/
/*rgp*/

s32 StateVarGetByName_3cca60(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *t0;
    s32 t1;
    struct Obj2 *r0;
    s16 t2;

    t0 = p0->m04;
    if (t0 == 0) {
        return -1;
    }
    t1 = t0->m10;
    r0 = ((struct Obj2 *)TableFindByName_421fb0(t1, p1));
    if (r0 != 0) {
        t2 = r0->m00;
        return ((short)StateVarGet_3ccac0(p0, t2));
    }
    return -1;
}
