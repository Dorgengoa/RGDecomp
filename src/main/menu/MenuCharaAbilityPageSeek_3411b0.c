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
extern s32 GetGameData_1fede0(void);
extern s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern void CharaAbilityViewCtor_3a8180(A *, s32, s32, s32);
extern void IterInit_370170(B *, A *);
extern s32 IterSeek_36fff0(B *, s32);

s32 MenuCharaAbilityPageSeek_3411b0(s32 p0)
{
    B b;
    A a;
    s32 r0;
    s32 r1;

    r0 = GetGameData_1fede0();
    r1 = PartyGetSlotChara_3c2fb0(*(s32 *)(r0 + 0x18), D_00482378[0x6C]);
    if (r1 == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(&a, r1, -1, -1);
    IterInit_370170(&b, &a);
    return IterSeek_36fff0(&b, p0);
}
