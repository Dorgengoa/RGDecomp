#include "types.h"

typedef struct Ent_FUN_002deb30 {
    u8 pad000[0xB4];
    s16 fB4;
    u8 pad0B6[0x2A];
} Ent_FUN_002deb30;

typedef struct Obj_FUN_002deb30 {
    Ent_FUN_002deb30 arr[0x30];
} Obj_FUN_002deb30;

extern void EffectEntriesUpdateRelease_2de490(Obj_FUN_002deb30 *o);
extern void EffectEntryUpdateNodes_2dabf0(Ent_FUN_002deb30 *e);

void EffectEntriesUpdate_2deb30(Obj_FUN_002deb30 *o)
{
    s32 i;

    EffectEntriesUpdateRelease_2de490(o);
    for (i = 0; i < 0x30; i++) {
        if (o->arr[i].fB4 == 3) {
            EffectEntryUpdateNodes_2dabf0(&o->arr[i]);
        }
    }
}
