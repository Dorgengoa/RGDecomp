/* rgp:protos */
#define RGP_SELF_insect_InsectHelpGetEntryRaw_510bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510BD0 -- 48 bytes.  `bnel` PAST the body is an if/else chain
 * (insect-dispatch-branch-polarity); the base pointer at +8 is RE-LOADED in
 * both arms, so each arm indexes it on its own rather than sharing a CSE. */
typedef struct Ent { u8 raw[0x10]; } Ent;

typedef struct Owner {
    u8   pad00[8];
    Ent *f8;                        /* +0x08 */
    s32  fC;                        /* +0x0C */
} Owner;

Ent *insect_InsectHelpGetEntryRaw_510bd0(Owner *o, s32 i)
{
    if (i == -1) {
        return &o->f8[o->fC];
    }
    return &o->f8[i];
}
