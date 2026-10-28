/* rgp:protos */
#define RGP_SELF_EvCmdRecordSetModeOne_25f990 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct T0025f990 {
    u8 pad[0x24];
    s32 f24;
} T0025f990;

/*rgp*/
/*rgp*/

s32 EvCmdRecordSetModeOne_25f990(void)
{
    RecordSetMode_431310(((T0025f990 *)GetGameData_1fede0())->f24, 1);
    return 1;
}
