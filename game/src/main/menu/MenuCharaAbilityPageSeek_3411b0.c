/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityPageSeek_3411b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Build a transform from the current record and hand it to the consumer.
   The -1 in the bnel delay slot is the shared constant for BOTH of
   CharaAbilityViewCtor_3a8180's trailing arguments. */

typedef struct A {
    u8 b[0x18];
} A;

typedef struct B {
    u8 b[0x8];
} B;

extern s8 *D_00482378;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuCharaAbilityPageSeek_3411b0(s32 p0)
{
    B b __attribute__((aligned(16)));
    A a __attribute__((aligned(16)));
    s32 r0;
    s32 r1;

    r0 = ((s32)GetGameData_1fede0());
    r1 = PartyGetSlotChara_3c2fb0(*(s32 *)(r0 + 0x18), D_00482378[0x6C]);
    if (r1 == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(&a, r1, -1, -1);
    IterInit_370170(&b, &a, 0, 0);
    return IterSeek_36fff0(&b, p0, 0, 0);
}
