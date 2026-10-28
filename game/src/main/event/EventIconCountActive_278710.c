/* rgp:protos */
#define RGP_SELF_EventIconCountActive_278710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem_00278710 {
    u8 pad0[0x28];
    s32 unk28;
    u8 pad1[0x14];
} Elem_00278710;

s32 EventIconCountActive_278710(Elem_00278710 *arg0)
{
    s32 count;
    s32 i;
    s32 ok;

    count = 0;
    for (i = 0; i < 0x10; i++) {
        ok = !(arg0[i].unk28 < 0);
        if (ok) {
            count++;
        }
    }
    return count;
}
