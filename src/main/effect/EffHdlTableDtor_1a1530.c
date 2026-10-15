#include "types.h"

extern void *StrMapEraseSubtree_1a25f0(void *, void *);
extern void *BufHolderDtor_1a1670(void *, s16);
extern void *EffHdlTableBaseDtor_1a16e0(void *, s16);
extern void OperatorDelete_100840(void *);

struct Obj_FUN_001a1530 {
    u8 pad000[0x28];
    void *m28;
};

void *EffHdlTableDtor_1a1530(struct Obj_FUN_001a1530 *o, s16 flag)
{
    void *p;

    if (o != 0) {
        p = (u8 *)o + 0x24;
        if (p != 0) {
            if (p != 0) {
                if (o->m28 != 0) {
                    StrMapEraseSubtree_1a25f0(p, o->m28);
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
