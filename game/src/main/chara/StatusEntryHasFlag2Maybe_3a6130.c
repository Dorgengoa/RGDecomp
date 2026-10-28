/* rgp:protos */
#define RGP_SELF_StatusEntryHasFlag2Maybe_3a6130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Flg_FUN_003a6130 {
    u8 b0;
    u8 b1;
    u8 low : 2;
    u8 flag : 1;
} Flg_FUN_003a6130;

s32 StatusEntryHasFlag2Maybe_3a6130(Flg_FUN_003a6130 *p)
{
    return p->b0 && p->flag;
}
