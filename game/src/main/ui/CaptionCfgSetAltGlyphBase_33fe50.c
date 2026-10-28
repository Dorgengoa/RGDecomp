/* rgp:protos */
#define RGP_SELF_CaptionCfgSetAltGlyphBase_33fe50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x4D. */

typedef struct Obj_FUN_0033fe50 {
    u8 pad000[0x4D];
    u8 field;         /* +0x4D */
} Obj_FUN_0033fe50;

void CaptionCfgSetAltGlyphBase_33fe50(Obj_FUN_0033fe50 *o, u8 value)
{
    o->field = value;
}
