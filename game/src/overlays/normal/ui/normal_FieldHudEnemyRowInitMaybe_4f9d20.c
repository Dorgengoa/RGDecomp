/* rgp:protos */
#define RGP_SELF_normal_FieldHudEnemyRowInitMaybe_4f9d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9D20 -- seeds a 0x39-byte slot: two header words then a 0x31
 * clear, which leaves as a TAIL CALL (`j func_131B60`, no frame at all). */
extern void memset(void *p, s32 v, s32 n);
extern void normal_FieldHudEnemyRowInitMaybe_4f9d20(u8 *p, s32 a);
void normal_FieldHudEnemyRowInitMaybe_4f9d20(u8 *p, s32 a)
{
    *(s32 *)(p + 0) = a;
    *(s32 *)(p + 4) = 0;
    memset(p + 8, 0, 0x31);
}
