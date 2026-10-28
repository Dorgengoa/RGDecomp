/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialCellItemCount_4f3370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3370 -- 112 bytes / 28 words.  Look up one
 * inventory record and hand its id to the item-name query.
 *
 * * Both guards are the INVERTED early return: retail branches INTO the
 *   continuation (`bnel $16,$0` / `bnel $2,$0`) and lets the failure fall
 *   through to `b <epilogue>` with the constant in the delay slot.
 * * `dsll32 $2,16 / dsra32 $2,16` on the CALL RESULT is an explicit `(s16)`
 *   cast on an s32 value ([[normal-s16-cast-sign-extension]]), not an s16
 *   return type.
 * * `Ctx { pad[0x18]; void *f18; }` + `func_3C78D0(ctx->f18, id, 0, 0)` is the
 *   byte-identical shape from normal_FUN_0050EF80.
 */

typedef struct Ctx { u8 pad00[0x18]; void *f18; } Ctx;
typedef struct Rec { s16 f00; } Rec;

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialCellItemCount_4f3370(void *o)
{
    Ctx *ctx;
    Rec *r;

    ctx = ((Ctx *)GetGameData_1fede0());
    if (ctx == 0) {
        return -1;
    }
    r = ((Rec *)factory_FactoryMaterialGetCellItem_4f3290(o));
    if (r == 0) {
        return 0;
    }
    return (s16)InvCountById_3c78d0(ctx->f18, r->f00, 0, 0);
}
