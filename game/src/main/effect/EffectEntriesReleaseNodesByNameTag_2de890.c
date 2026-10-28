/* rgp:protos */
#define RGP_SELF_EffectEntriesReleaseNodesByNameTag_2de890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same 0xE0-stride, 0x30-entry record array as the already-matched sibling
   src/s33a/EffectEntriesReleaseNodesByTag_2de610.c, plus an added strcmp gate on the name string at
   +0xBC (see src/accessors/EffectEntryGetName_2d9540.c). */

typedef struct Ent {
    u8 pad000[0xB4];
    s16 fB4;
    u8 pad0B6[0x2A];
} Ent;

/*rgp*/
/*rgp*/
extern s32 strcmp(const s8 *, const s8 *);

void EffectEntriesReleaseNodesByNameTag_2de890(Ent *arg0, const s8 *arg1, s32 arg2)
{
    s32 i;
    Ent *rec;

    i = 0;
    do {
        rec = (Ent *)((u8 *)arg0 + i * 0xE0);
        if (rec->fB4 != 0 && strcmp(arg1, (const s8 *)((s32)EffectEntryGetName_2d9540(rec))) == 0) {
            EffectEntryReleaseNodesByTag_2da2a0(rec, arg2);
        }
        i += 1;
    } while (i < 0x30);
}
