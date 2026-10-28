/* rgp:protos */
#define RGP_SELF_LeaderGetControlStateMaybe_2f5440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN LeaderGetControlStateMaybe_2f5440 -- two guards branching the SAME way is an `&&`. */

typedef struct Ctx5440 {
    u8  pad00[0x18];
    u8 *m18;            /* 0x18 */
} Ctx5440;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 LeaderGetControlStateMaybe_2f5440(void)
{
    Ctx5440 *c;

    if (((unsigned char)IsInBattle_288420()) != 0 && BtlChgMenuIsMemberPageUp_204e20() != 0) {
        return 1;
    }
    c = ((Ctx5440 *)GetGameData_1fede0());
    return CharaGetControlStateMaybe_2f5320(*(s16 *)(c->m18 + 0x18E));
}
