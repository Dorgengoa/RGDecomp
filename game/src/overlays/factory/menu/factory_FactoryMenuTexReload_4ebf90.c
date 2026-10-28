/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuTexReload_4ebf90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EBF90 -- open the factory's own window set: for
 * each entry, take a slot id and either create the window or re-show the one
 * the id already names, stopping at the first failure.
 * 252 bytes, 64 instructions, 4 conditional branches, 7 calls.
 *
 * * TWIN of `factory_FactoryMenuResRequest_4ec2f0` at ratio 0.871 -- the other window set, two
 * entries instead of one, keyed on `i == 1` instead of `i == 0`, without the
 * stale-handle release and without the trailing flag clear.
 *
 * * `addiu $2, $28, -0x4950` is `&D_00480820[i]` over an 8-byte record and
 * `addiu $2, $28, -0x6F0` is `&D_00484A80[i]` over `s32`.  BOTH stay
 * gp-relative only because their DECLARED SIZE is at most 8 bytes
 * ([[normal-small-data-threshold]]); an incomplete array would move them to
 * `%hi`/`%lo` and cost a word at every reference.
 *
 * * `blezl $17` IS `i < 1` -- mwcc turns the one-iteration bound into the
 * `<= 0` branch with no `slti`, where the twin's `i < 2` needs one.
 */

typedef struct Ent {
    s32 f00;
    s32 f04;
} Ent;                                          /* 8 */

extern Ent  D_00480820[1];                      /* _gp - 0x4950 */
extern u8   D_004807FC;                         /* _gp - 0x4974 */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern s32  D_00484A80[1];                      /* _gp - 0x6F0  */
extern s32  D_00484A88;                         /* _gp - 0x6E8  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuTexReload_4ebf90(void)
{
    void *h;
    Ent  *e;
    s32   t;
    s32   i;

    GetDrawCtxNameTable_15de40();
    h = GetLoaderMgr_1f59d0();
    for (i = 0; i < 1; i++) {
        e = &D_00480820[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 0) {
            if (D_00484A88 != 0) {
                MemStackHeapFree_14dcb0(D_00484A30, D_00484A30);
                D_00484A88 = 0;
            }
            t = MemStackAllocAligned64_14da10(D_00484A30, 0xF081);
            D_00484A88 = t;
            e->f00 = ((short)LoaderRequestFileEx_1cd6c0(h, D_00484A80[i], t, 0xF080));
        } else {
            e->f00 = LoaderRequestFile_1cd870(h, D_00484A80[i], 0);
        }
        if (e->f00 == -1) {
            return;
        }
    }
    LoaderQueueAppendSeparator_1cd670(h);
    D_004807FC = 0;
}
