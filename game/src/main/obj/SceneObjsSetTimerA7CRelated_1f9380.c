/* rgp:protos */
#define RGP_SELF_SceneObjsSetTimerA7CRelated_1f9380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_00481A7C.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00481A7C;

void SceneObjsSetTimerA7CRelated_1f9380(s32 value)
{
    D_00481A7C = value;
}
