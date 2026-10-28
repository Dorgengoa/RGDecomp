/* rgp:protos */
#define RGP_SELF_normal_FieldHudSlotRecClearRelated_4f9ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9CE0 -- clears a 0x1C entry and invalidates its two ids.
 * Pass-33 LIST rank: 56 bytes, 14 instructions, ZERO branches, 1 call.
 * `daddu $16,$4,$0` in the call's delay slot is the parameter being saved
 * across it, not an argument. */

typedef struct Ent { u8 pad00[0x0C]; s32 f0C; s32 f10; } Ent;

extern void memset(void *p, s32 v, s32 n);

extern void normal_FieldHudSlotRecClearRelated_4f9ce0(Ent *p);

void normal_FieldHudSlotRecClearRelated_4f9ce0(Ent *p)
{
    memset(p, 0, 0x1C);
    p->f0C = -1;
    p->f10 = -1;
}
