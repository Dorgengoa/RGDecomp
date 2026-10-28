/* rgp:protos */
#define RGP_SELF_title_TitleMenuObjResetMaybe_4ed320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ED320 -- three instructions:
 *
 *     sh     $0, 0xA($4)
 *     jr     $31
 *      daddu $2, $0, $0
 *
 * Clear a halfword field at +0xA and return 0.  The fourth word inside the
 * recorded size is padding, not code -- title's symbol sizes are clamped to
 * the next symbol, so the slot is 0xC.  See otextsplit.real_size.
 */

typedef struct Obj_title_FUN_004ed320 {
    u8 pad000[0xA];
    s16 flag;          /* +0xA */
} Obj_title_FUN_004ed320;

s32 title_TitleMenuObjResetMaybe_4ed320(Obj_title_FUN_004ed320 *o)
{
    o->flag = 0;
    return 0;
}
