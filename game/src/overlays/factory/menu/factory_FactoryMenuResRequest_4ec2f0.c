/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuResRequest_4ec2f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EC2F0 -- open the parts window set: two entries,
 * the second of which owns the shared text window.
 * 228 bytes, 60 instructions, 3 conditional branches, 6 calls.
 *
 * * TWIN of `factory_FactoryMenuTexReload_4ebf90` at ratio 0.871.  The differences are the two
 * gp bases, the trip count, the special index (1 rather than 0), and the fact
 * that this one neither releases a stale handle nor clears a flag at the end.
 *
 * * `D_00480810` is declared `[1]` even though the loop reaches index 1: the
 * DECLARED SIZE is a relocation control, and 16 bytes would take it out of
 * small data ([[normal-small-data-threshold]]).  `D_00484A78[2]` is 8 bytes and
 * still lands in it.
 */

typedef struct Ent {
    s32 f00;
    s32 f04;
} Ent;                                          /* 8 */

extern Ent  D_00480810[1];                      /* _gp - 0x4960 */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern s32  D_00484A78[2];                      /* _gp - 0x6F8  */
extern s32  D_00484A88;                         /* _gp - 0x6E8  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuResRequest_4ec2f0(void)
{
    void *h;
    Ent  *e;
    s32   t;
    s32   i;

    GetDrawCtxNameTable_15de40();
    h = GetLoaderMgr_1f59d0();
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 1) {
            t = MemStackAllocAligned64_14da10(D_00484A30, 0xF081);
            D_00484A88 = t;
            e->f00 = ((short)LoaderRequestFileEx_1cd6c0(h, D_00484A78[i], t, 0xF080));
        } else {
            e->f00 = LoaderRequestFile_1cd870(h, D_00484A78[i], 0);
        }
        if (e->f00 == -1) {
            return;
        }
    }
    LoaderQueueAppendSeparator_1cd670(h);
}
