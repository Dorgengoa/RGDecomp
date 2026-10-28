/* rgp:protos */
#define RGP_SELF_InsectRecSlotFindItemById_3cfad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004838E8;

void *InsectRecSlotFindItemById_3cfad0(void *arg0, s32 arg1) {
    s32 i;
    void *temp_2;

    if (D_004838E8 == 0) {
        return NULL;
    }
    i = 0;
    while (i < 5) {
        temp_2 = *(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x18)) + (i * 4) + 0xC);
        if ((temp_2 != NULL) && (arg1 == *(s16 *)((u8 *)temp_2 + 4))) {
            return temp_2;
        }
        i += 1;
    }
    return NULL;
}
