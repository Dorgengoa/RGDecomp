/* rgp:protos */
#define RGP_SELF_CaptionCfgGetAltGlyphBase_33fe40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x4D. */

typedef struct Obj_FUN_0033fe40 {
    u8 pad000[0x4D];
    s8 field;         /* +0x4D */
} Obj_FUN_0033fe40;

s8 CaptionCfgGetAltGlyphBase_33fe40(Obj_FUN_0033fe40 *o)
{
    return o->field;
}
