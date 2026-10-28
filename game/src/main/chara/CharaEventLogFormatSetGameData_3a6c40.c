/* rgp:protos */
#define RGP_SELF_CharaEventLogFormatSetGameData_3a6c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_004837B8.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004837B8;

void CharaEventLogFormatSetGameData_3a6c40(s32 value)
{
    D_004837B8 = value;
}
