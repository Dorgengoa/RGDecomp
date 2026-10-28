/* rgp:protos */
#define RGP_SELF_CharaTable2x5x2Get_3abbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct E003ABBE0 {
    s32 w[2];
} E003ABBE0;

typedef struct S003ABBE0 {
    u8 pad[0x290];
    E003ABBE0 arr[1][5];
} S003ABBE0;

s32 CharaTable2x5x2Get_3abbe0(S003ABBE0 *s, s32 i, s32 j, s32 k)
{
    return s->arr[i][j].w[k];
}
