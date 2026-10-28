/* rgp:protos */
#define RGP_SELF_EventIconSpawn_278640 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/

void EventIconSpawn_278640(void *arg0, s32 arg1, u128 *arg2, u128 *arg3, s32 arg4) {
    void *temp_2;

    temp_2 = EventIconFindFree_278750((int)arg0);
    if (temp_2 != NULL) {
        *(s32 *)((u8 *)temp_2 + 0x28) = -1;
        *(f32 *)((u8 *)temp_2 + 0x20) = 1.0f;
        *(f32 *)((u8 *)temp_2 + 0x24) = 1.0f;
        *(u128 *)((u8 *)temp_2 + 0x0) = 0;
        *(u128 *)((u8 *)temp_2 + 0x10) = 0;
        *(s32 *)((u8 *)temp_2 + 0x2C) = 0;
        *(s32 *)((u8 *)temp_2 + 0x30) = 0x2D;
        *(f32 *)((u8 *)temp_2 + 0x34) = 0.0f;
        *(s32 *)((u8 *)temp_2 + 0x38) = 0;

        *(s32 *)((u8 *)temp_2 + 0x28) = arg1;
        *(f32 *)((u8 *)temp_2 + 0x20) = 0.0f;
        *(f32 *)((u8 *)temp_2 + 0x24) = 0.0f;
        *(s32 *)((u8 *)temp_2 + 0x2C) = arg4;
        *(u128 *)((u8 *)temp_2 + 0x0) = *arg2;
        *(u128 *)((u8 *)temp_2 + 0x10) = *arg3;
        *(f32 *)((u8 *)temp_2 + 0x34) = 35.0f + *(f32 *)((u8 *)temp_2 + 4);
        *(s32 *)((u8 *)temp_2 + 0x38) = 0;
        *(s32 *)((u8 *)arg0 + 0x404) = 1;
    }
}
