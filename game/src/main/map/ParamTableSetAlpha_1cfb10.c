/* rgp:protos */
#define RGP_SELF_ParamTableSetAlpha_1cfb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Stores a float into the record ParamTableGetRec_1cfbc0 hands back, if there is one.
   The value has to survive the call, so it lives in $f20 -- the swc1/lwc1
   pair around the body is that callee-saved FPR, not a spill.

   ⚠ The first two arguments were INVISIBLE here until ParamTableGetRec_1cfbc0 was
   written: nothing in this function touches $4 or $5, so an earlier version
   of this file declared it `ParamTableSetAlpha_1cfb10(f32 v)` and still matched
   byte-for-byte. They are the owner and the index the lookup bounds-checks.
   A pass-through argument leaves no trace in the callER -- read the callEE. */

typedef struct Rec001cfb10 {
    s32 unk0;
    f32 unk4;
} Rec001cfb10;

/*rgp*/

void * ParamTableSetAlpha_1cfb10(void *owner, s32 index, f32 v)
{ void * rgp_v0 = 0;
    Rec001cfb10 *r;

    r = (rgp_v0 = ((Rec001cfb10 *)ParamTableGetRec_1cfbc0(owner, index)));
    if (r != 0) {
        r->unk4 = v;
    }
return rgp_v0; }
