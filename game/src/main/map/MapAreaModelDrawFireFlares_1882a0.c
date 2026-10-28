/* rgp:protos */
#define RGP_SELF_MapAreaModelDrawFireFlares_1882a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct { f32 f; s32 x; } P98;
/*rgp*/
/*rgp*/

void MapAreaModelDrawFireFlares_1882a0(u8 *arg0, s32 arg1)
{
    P98 sp98 __attribute__((aligned(16)));
    u8 sp50[0x40] __attribute__((aligned(16)));
    s32 id;
    u8 **list;
    s32 *pc;
    s32 i;
    u8 *e;

    sp98.f = 0.0f;
    sp98.f = TimeOfDayGetHour_18d920((void *)arg0);
    sp98.x = *(s32 *)(arg0 + 0x1678);
    id = GetDrawCtx_15de80();
    GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(id, arg1, 1.0f);
    list = *(u8 ***)(arg0 + 0x58C);
    pc = (s32 *)(arg0 + 0x580);
    MtxIdentity_13d2e0(sp50);
    FuncDataTableDrawFireFlaresMaybe_18eb30(sp50, arg0 + 0x1664, &sp98, 0, 0);
    if (list != NULL) {
        for (i = 0; i < *pc; i++, list++) {
            e = *list;
            if (*(s32 *)(e + 0x114) & 2) {
                NodeCalcWorldMatrixThunk_186130(e, sp50);
                FuncDataTableDrawFireFlaresMaybe_18eb30(sp50, e + 0x114, &sp98, 0, 0);
            }
        }
    }
}
