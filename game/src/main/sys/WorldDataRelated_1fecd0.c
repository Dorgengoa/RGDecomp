/* rgp:protos */
#define RGP_SELF_WorldDataRelated_1fecd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s88m de-asm: retail keeps the compare operands (lh/andi + li 1) of an
 * empty-bodied test after the branch itself is removed. */
typedef struct {
    u8 pad[0x32];
    s16 f;
} S;

/*rgp*/
/*rgp*/

void WorldDataRelated_1fecd0(void)
{
    GetWorldDataMgr_1fedf0();
    if ((((S *)GetGameData_1fede0())->f & 1) == 1) { return; }
}
