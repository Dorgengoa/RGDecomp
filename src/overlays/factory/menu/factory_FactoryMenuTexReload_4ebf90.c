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

extern s32   func_14DA10(void *w, s32 id);
extern void  func_14DCB0(void *a, void *b);
extern s32   func_15DE40(void);
extern s32   func_1CD670(void *h);
extern s32   func_1CD6C0(void *h, s32 id, s32 w, s32 a, s32 b);
extern s32   func_1CD870(void *h, s32 id, s32 a);
extern void *func_1F59D0(void);

void factory_FactoryMenuTexReload_4ebf90(void)
{
    void *h;
    Ent  *e;
    s32   t;
    s32   i;

    func_15DE40();
    h = func_1F59D0();
    for (i = 0; i < 1; i++) {
        e = &D_00480820[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 0) {
            if (D_00484A88 != 0) {
                func_14DCB0(D_00484A30, D_00484A30);
                D_00484A88 = 0;
            }
            t = func_14DA10(D_00484A30, 0xF081);
            D_00484A88 = t;
            e->f00 = func_1CD6C0(h, D_00484A80[i], t, 0xF080, 0);
        } else {
            e->f00 = func_1CD870(h, D_00484A80[i], 0);
        }
        if (e->f00 == -1) {
            return;
        }
    }
    func_1CD670(h);
    D_004807FC = 0;
}
