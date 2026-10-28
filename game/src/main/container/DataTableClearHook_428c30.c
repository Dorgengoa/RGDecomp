/* rgp:protos */
#define RGP_SELF_DataTableClearHook_428c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct E00428C30 {
    s16 a;
    s16 b;
} E00428C30;

typedef struct S00428C30 {
    u8 pad[0x94];
    E00428C30 e[0x15];
} S00428C30;

void DataTableClearHook_428c30(S00428C30 *s)
{
    s32 i;

    for (i = 0; i < 0x15; i++) {
        s->e[i].a = -1;
        s->e[i].b = -1;
    }
}
