/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_4247f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E004247F0 {
    u8 pad0[0xC];
} E004247F0;

typedef struct S004247F0 {
    u8 pad0[0x94];
    s16 count;                /* +0x94 */
    u8 pad96[0x2];
    E004247F0 *base;          /* +0x98 */
} S004247F0;

E004247F0 *ArrayGetChecked_4247f0(S004247F0 *o, s32 i)
{
    if (i < 0 || i >= o->count) {
        return 0;
    }
    return &o->base[i];
}
