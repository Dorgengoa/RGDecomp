#include "types.h"
typedef struct E0033bb00 {
    s16 h28;
    u8 pad[0x12];
} E0033bb00;

typedef struct S0033bb00 {
    u8 pad00[0x28];
    E0033bb00 e[10];
} S0033bb00;

void SunaKemuClear_33bb00(S0033bb00 *s)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        s->e[i].h28 = 0;
    }
    *(s32 *)((u8 *)s + 0xE0) = 0;
}
