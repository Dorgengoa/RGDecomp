/* rgp:protos */
#define RGP_SELF_McGetInfoPollThrottled_3755f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj003755f0 {
    u8 pad0[0x4E4];
    s32 unk4E4;
} Obj003755f0;

/*rgp*/

s32 McGetInfoPollThrottled_3755f0(Obj003755f0 *arg0)
{
    s32 result;
    s32 count;

    result = 0;
    count = arg0->unk4E4 + 1;
    arg0->unk4E4 = count;
    if (count >= 5) {
        result = McGetInfoStep_375640(arg0);
        arg0->unk4E4 = 0;
    }
    return result;
}
