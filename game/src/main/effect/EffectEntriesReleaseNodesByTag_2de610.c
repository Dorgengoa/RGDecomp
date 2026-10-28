/* rgp:protos */
#define RGP_SELF_EffectEntriesReleaseNodesByTag_2de610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent_FUN_002de610 {
    u8 pad000[0xB4];
    s16 fB4;
    u8 pad0B6[0x2A];
} Ent_FUN_002de610;

typedef struct Obj_FUN_002de610 {
    Ent_FUN_002de610 arr[0x30];
} Obj_FUN_002de610;

typedef struct Arg_FUN_002de610 Arg_FUN_002de610;

/*rgp*/

void EffectEntriesReleaseNodesByTag_2de610(Obj_FUN_002de610 *o, Arg_FUN_002de610 *a)
{
    s32 i;

    for (i = 0; i < 0x30; i++) {
        if (o->arr[i].fB4 != 0) {
            EffectEntryReleaseNodesByTag_2da2a0(&o->arr[i], a);
        }
    }
}
