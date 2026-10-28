/* rgp:protos */
#define RGP_SELF_DrawListBeginPrim_141b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same TU family as DrawListClearScreen_1423c0 / DrawListEmitFrameEnvMaybe_142280 (src/s17r08): identical
   `e = a->m08[a->m00]; GsPktInit_13f7f0(&a->m130, e ? e+8 : 0, ctx);
   GsPktBegin_13f7e0(&a->m130);` opening, but this variant stops right after the
   init calls and returns the sub-object pointer instead of continuing on
   to build a packet. */

typedef struct Ctx00141b00 {
    s32 unk0;               /* 0x00 index into unk08 */
    u8 pad04[0x08 - 0x04];
    void *unk08[6];          /* 0x08 */
    u8 pad20[0x130 - 0x20];
    u8 unk130[0x140];        /* 0x130 sub-object passed to init calls */
    void *unk270;             /* 0x270 */
} Ctx00141b00;

/*rgp*/
/*rgp*/

void *DrawListBeginPrim_141b00(Ctx00141b00 *a)
{
    void *e;
    void *ctx;

    ctx = a->unk270;
    e = a->unk08[a->unk0];
    GsPktInit_13f7f0(&a->unk130, e ? (void *)((u8 *)e + 8) : 0, ctx);
    GsPktBegin_13f7e0(&a->unk130);
    return &a->unk130;
}
