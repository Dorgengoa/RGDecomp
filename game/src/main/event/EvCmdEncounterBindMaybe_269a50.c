/* rgp:protos */
#define RGP_SELF_EvCmdEncounterBindMaybe_269a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_269a50;
struct O269a50 { u8 pad000[0x20]; s32 m20; };
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEncounterBindMaybe_269a50(E8_269a50 *p0, s32 p1)
{
    s32 a;
    s32 b;

    if (p1 <= 0) {
        return 0;
    }
    a = ScriptGetInt_26a2a0(p0++);
    b = -1;
    if (p1 >= 2) {
        b = ScriptGetInt_26a2a0(p0);
    }
    CharaSysEncounterBindAndStartMaybe_3a5340(((struct O269a50 *)GetGameData_1fede0())->m20, a, b, 0);
    return 1;
}
