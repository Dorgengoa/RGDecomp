/* rgp:protos */
#define RGP_SELF_MapAreaGetTreasureBoxSlot_1dcb20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct E001dcb20 {
    s32 w0;
    s32 w4;
    s32 w8;
} E001dcb20;

typedef struct S001dcb20 {
    u8 pad[0xB4];
    E001dcb20 arr[4];         /* +0xB4 */
} S001dcb20;

E001dcb20 *MapAreaGetTreasureBoxSlot_1dcb20(S001dcb20 *s, u32 i)
{
    E001dcb20 *r;

    if (i >= 4) {
        r = 0;
    } else {
        r = &s->arr[i];
    }
    return r;
}
