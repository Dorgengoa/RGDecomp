/* rgp:protos */
#define RGP_SELF_ActionResultListAddUniqueRelated_3a6c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x54]; s16 count; s16 pad56; s32 arr[4]; } T3a6;
s32 ActionResultListAddUniqueRelated_3a6c50(T3a6 *arg0, s32 arg1) {
    s32 i;

    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < arg0->count; i++) {
        if (arg0->arr[i] == arg1) {
            return 0;
        }
    }
    if (arg0->count < 4) {
        arg0->arr[arg0->count++] = arg1;
    }
    return 1;
}
