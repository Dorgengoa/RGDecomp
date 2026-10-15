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

extern s32   func_14DA10(void *w, s32 id);
extern s32   func_15DE40(void);
extern s32   func_1CD670(void *h);
extern s32   func_1CD6C0(void *h, s32 id, s32 w, s32 a, s32 b);
extern s32   func_1CD870(void *h, s32 id, s32 a);
extern void *func_1F59D0(void);

void factory_FactoryMenuResRequest_4ec2f0(void)
{
    void *h;
    Ent  *e;
    s32   t;
    s32   i;

    func_15DE40();
    h = func_1F59D0();
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 1) {
            t = func_14DA10(D_00484A30, 0xF081);
            D_00484A88 = t;
            e->f00 = func_1CD6C0(h, D_00484A78[i], t, 0xF080, 0);
        } else {
            e->f00 = func_1CD870(h, D_00484A78[i], 0);
        }
        if (e->f00 == -1) {
            return;
        }
    }
    func_1CD670(h);
}
