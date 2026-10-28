/* rgp:protos */
#define RGP_SELF_normal_ShopMenuResRequest_50b020 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050B020 -- two-slot loader loop over the 8-byte gp table at
 * gp-0x4B30; slot 0 takes the F081/F080 path, every other slot the plain one. */

typedef struct Ent { s32 f00; s32 f04; } Ent;

extern Ent   D_00480640[1];       /* gp - 0x4B30 */
extern s32   D_004845F0[2];       /* gp - 0xB80  */
extern s32   D_004845FC;          /* gp - 0xB74  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuResRequest_50b020(void)
{
    void *w;
    s32   i;
    Ent  *e;

    GetDrawCtxNameTable_15de40();
    w = GetLoaderMgr_1f59d0();
    for (i = 0; i < 2; i++) {
        e = &D_00480640[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 0) {
            D_004845FC = HeapHandleAllocBack_1cdb10(GetLoaderMgr_1f59d0(), 0xF081);
            e->f00 = ((short)LoaderRequestFileEx_1cd6c0(w, D_004845F0[i], D_004845FC, 0xF080));
        } else {
            e->f00 = LoaderRequestFile_1cd870(w, D_004845F0[i], 0);
        }
        if (e->f00 == -1) {
            return 1;
        }
    }
    LoaderQueueAppendSeparator_1cd670(w);
    return 0;
}
