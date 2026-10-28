/* rgp:protos */
#define RGP_SELF_MesWinGetClipMode_2721d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x1C4A. */

typedef struct Obj_FUN_002721d0 {
    u8 pad000[0x1C4A];
    u8 field;         /* +0x1C4A */
} Obj_FUN_002721d0;

u8 MesWinGetClipMode_2721d0(Obj_FUN_002721d0 *o)
{
    return o->field;
}
