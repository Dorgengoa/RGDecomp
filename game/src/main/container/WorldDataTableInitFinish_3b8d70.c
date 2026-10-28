/* rgp:protos */
#define RGP_SELF_WorldDataTableInitFinish_3b8d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S003B8D70 {
    u8 pad00[0x7A];
    u8 bit0 : 1;
    u8 rest : 7;
    u8 pad7B[0x94 - 0x7B];
    s32 w94;
    s16 h98;
} S003B8D70;

s32 WorldDataTableInitFinish_3b8d70(S003B8D70 *s)
{
    s->w94 = 0;
    s->h98 = 0;
    s->bit0 = 0;
    return 1;
}
