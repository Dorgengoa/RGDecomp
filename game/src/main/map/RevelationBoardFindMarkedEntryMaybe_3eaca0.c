/* rgp:protos */
#define RGP_SELF_RevelationBoardFindMarkedEntryMaybe_3eaca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s16 RevelationBoardFindMarkedEntryMaybe_3eaca0(void *rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3) {
    void *obj;
    u8 *elem;
    s32 i;

    obj = RevelationBoardFindById_3eb580((void *)rgp_a0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    if (obj == NULL) {
        return -1;
    }
    elem = *(u8 **)((u8 *)obj + 8);
    for (i = 0; i < *(s16 *)((u8 *)obj + 4); i++, elem += 0x1C) {
        if (*(u8 *)(elem + 0x18) & 1) {
            return *(s16 *)(elem + 0x16);
        }
    }
    return -1;
}
