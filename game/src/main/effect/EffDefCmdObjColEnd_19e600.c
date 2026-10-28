/* rgp:protos */
#define RGP_SELF_EffDefCmdObjColEnd_19e600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Release the four handles hanging off *p2 through one shared releaser.
   The entry beql's delay slot holds `sw $0,0x50`, which is the FIRST
   instruction of its branch TARGET duplicated -- so that store is OUTSIDE
   the guard, not the last statement inside it.  The last guard is a plain `beqz`+nop because its branch target is
   a STORE and mwcc will not speculate one into a likely slot. */

typedef struct Rel {
    u8   pad000[0x20];
    void *m20;
    u8   pad024[0x4];
    void *m28;
    u8   pad02C[0x18];
    void *m44;
    void *m48;
    u8   pad04C[0x4];
    void *m50;
    void *m54;
} Rel;

s32 EffDefCmdObjColEnd_19e600(s32 a0, s32 a1, Rel **pp)
{
    Rel *o;

    o = *pp;
    if (o->m28 != 0) {
        if (o->m44 != 0) {
            EffObjAddChannel_1a9ce0(o->m28, o->m20, o->m44);
        }
        if (o->m50 != 0) {
            EffObjAddChannel_1a9ce0(o->m28, o->m20, o->m50);
        }
        if (o->m48 != 0) {
            EffObjAddChannel_1a9ce0(o->m28, o->m20, o->m48);
        }
        if (o->m54 != 0) {
            EffObjAddChannel_1a9ce0(o->m28, o->m20, o->m54);
        }
    }
    o->m50 = 0;
    o->m44 = 0;
    o->m48 = 0;
    o->m54 = 0;
    return 1;
}
