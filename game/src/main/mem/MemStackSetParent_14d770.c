/* rgp:protos */
#define RGP_SELF_MemStackSetParent_14d770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0014d770 {
    u8 pad000[0x40];
    struct Obj_FUN_0014d770 *f40;
} Obj_FUN_0014d770;

/*rgp*/
/*rgp*/

void MemStackSetParent_14d770(Obj_FUN_0014d770 *o, Obj_FUN_0014d770 *p)
{
    if (p == o) {
        return;
    }
    if (p == 0) {
        MemStackDetach_14d5e0(o);
        return;
    }
    if (o->f40 != 0) {
        return;
    }
    o->f40 = p;
    MemStackAddChild_14d650(p, o);
}
