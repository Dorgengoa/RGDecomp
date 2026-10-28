/* rgp:protos */
#define RGP_SELF_EffHdlTableDtor_1a13f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj_FUN_001a13f0 {
    u8 pad000[0x28];
    void *m28;
};

void *EffHdlTableDtor_1a13f0(struct Obj_FUN_001a13f0 *o, s16 flag)
{
    void *p;

    if (o != 0) {
        p = (u8 *)o + 0x24;
        if (p != 0) {
            if (p != 0) {
                if (o->m28 != 0) {
                    StrMapEraseSubtree_1a2cd0(p, o->m28);
                }
            }
        }
        if (o != 0) {
            BufHolderDtor_1a1670((u8 *)o + 0x18, -1);
            BufHolderDtor_1a1670((u8 *)o + 0xC, -1);
            EffHdlTableBaseDtor_1a16e0(o, -1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
