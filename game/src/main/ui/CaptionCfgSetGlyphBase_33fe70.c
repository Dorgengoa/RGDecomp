/* rgp:protos */
#define RGP_SELF_CaptionCfgSetGlyphBase_33fe70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x4C. */

typedef struct Obj_FUN_0033fe70 {
    u8 pad000[0x4C];
    u8 field;         /* +0x4C */
} Obj_FUN_0033fe70;

void CaptionCfgSetGlyphBase_33fe70(Obj_FUN_0033fe70 *o, u8 value)
{
    o->field = value;
}
