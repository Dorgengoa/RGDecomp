#include "types.h"

typedef struct Obj_FUN_002de2e0 {
    u8 pad000[0xB4];
    s16 fB4;
} Obj_FUN_002de2e0;

extern Obj_FUN_002de2e0 *EffectFindByNameNoId_2dfed0(void);
extern void EffectEntryReleaseAllNodes_2da430(Obj_FUN_002de2e0 *o);

void EffectEntriesReleaseAllNodesByName_2de2e0(void)
{
    Obj_FUN_002de2e0 *o;

    o = EffectFindByNameNoId_2dfed0();
    if (o != 0) {
        if (o->fB4 != 0) {
            EffectEntryReleaseAllNodes_2da430(o);
        }
    }
}
