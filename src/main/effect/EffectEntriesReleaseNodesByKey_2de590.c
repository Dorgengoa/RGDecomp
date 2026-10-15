#include "types.h"

typedef struct Ent_FUN_002de590 {
    u8 pad000[0xB4];
    s16 fB4;
    u8 pad0B6[0x2A];
} Ent_FUN_002de590;

typedef struct Obj_FUN_002de590 {
    Ent_FUN_002de590 arr[0x30];
} Obj_FUN_002de590;

typedef struct A_FUN_002de590 A_FUN_002de590;
typedef struct B_FUN_002de590 B_FUN_002de590;

extern void EffectEntryReleaseNodesByKey_2da1d0(Ent_FUN_002de590 *e, A_FUN_002de590 *a, B_FUN_002de590 *b);

void EffectEntriesReleaseNodesByKey_2de590(Obj_FUN_002de590 *o, A_FUN_002de590 *a, B_FUN_002de590 *b)
{
    s32 i;

    for (i = 0; i < 0x30; i++) {
        if (o->arr[i].fB4 != 0) {
            EffectEntryReleaseNodesByKey_2da1d0(&o->arr[i], a, b);
        }
    }
}
