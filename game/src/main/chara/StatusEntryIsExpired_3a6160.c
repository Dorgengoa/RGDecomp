/* rgp:protos */
#define RGP_SELF_StatusEntryIsExpired_3a6160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Flg_FUN_003a6160 {
    u8 b0;
    u8 b1;
    u8 low : 1;
    u8 flag : 1;
} Flg_FUN_003a6160;

s32 StatusEntryIsExpired_3a6160(Flg_FUN_003a6160 *p)
{
    return p->b0 && p->flag;
}
