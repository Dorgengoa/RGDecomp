#include "types.h"

typedef struct Obj_FUN_001e1250 {
    u8 pad000[0x790];
    void *f790;
} Obj_FUN_001e1250;

extern s32 MapEntryCloneWithCardNode_1e12c0(Obj_FUN_001e1250 *o, s32 c, s32 d);
extern void MapEntryPlaySpinMotion_1e0be0(Obj_FUN_001e1250 *o);

s32 MapEntryInitWithRec_1e1250(Obj_FUN_001e1250 *o, void *p, s32 c, s32 d)
{
    if (MapEntryCloneWithCardNode_1e12c0(o, c, d) == 0) {
        return 0;
    }
    if (p == 0) {
        return 0;
    }
    o->f790 = p;
    MapEntryPlaySpinMotion_1e0be0(o);
    return 1;
}
