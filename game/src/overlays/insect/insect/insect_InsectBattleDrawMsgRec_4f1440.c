/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawMsgRec_4f1440 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1440 -- two-call forwarder; the first call's result is the
 * third argument of the second.
 * ARITY: both arguments of insect_InsectMsgGet_512b70 and all three of
 * insect_InsectBattleDrawTextRec_4f1410 are marshalled here with real instructions. */
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawMsgRec_4f1440(u8 *a, s32 b, s32 c)
{
    insect_InsectBattleDrawTextRec_4f1410(a, b, ((s32)insect_InsectMsgGet_512b70(a + 0x506C, c)));
}
