#include "types.h"

/* factory.bin overlay, 0x004EBE90 -- poll the modal confirm window: while it is
 * still open, ask it for its result; on "1" tear it down, push the chosen line
 * into the message box and release the handle.
 * 248 bytes, 62 instructions, 4 conditional branches, 8 calls.
 *
 * * SAME `Ent D_00480820[1]` record as `factory_FactoryMenuTexReload_4ebf90` (_gp - 0x4950,
 * 8 bytes, small data): `f00` is the window handle, `f04` the latched result.
 *
 * * `daddu $17, $0, $0` + `addu $4, $17, $4` is the accumulator that mwcc will
 * NOT constant-fold: the COMPOUND assignment `n += ...` keeps the zero in its
 * own register where every single-expression spelling folds it away
 * ([[insect-compound-assign-blocks-fold]]).
 *
 * * `addiu $16, $28, -0x4950` BEFORE `lw $3, 0x4($16)` is the CAST: without it
 * mwcc constant-folds the FIRST deref of `e` back to a gp-direct
 * `lw $3, -0x494C($28)` and materialises the base pointer afterwards, because
 * inside the block that DEFINES `e` the address is a known constant.  A cast
 * on the address expression -- `(Ent *)`, `(Ent *)(void *)`, `(Ent *)(u8 *)`
 * and `&D_00480820[n]` with a variable subscript all produce the SAME object
 * -- binds every deref to the register form.  The later five accesses go
 * through $16 either way, so this is a one-token entry-block decision; 32
 * earlier arms over statement order, declaration order, extern width,
 * condition form and volatile all left it at 2 wrong words.
 *
 * * `sw $2, 0x4($16)` in the branch delay slot with the compare on `$2` means
 * the call result is a NAMED LOCAL: re-reading `f04` after storing to it would
 * have to reload, because a load will not cross a store to a global.
 */

typedef struct Ent {
    s32 f00;
    s32 f04;
} Ent;                                          /* 8 */

extern Ent   D_00480820[1];                     /* _gp - 0x4950 */
extern u8    D_004807FC;                        /* _gp - 0x4974 */
extern u8    D_00480800;                        /* _gp - 0x4970 */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern s32   D_00484A88;                        /* _gp - 0x6E8  */

extern void *func_1F59D0(void);
extern s32   func_1CD4F0(void *h, s32 id);
extern s32   func_15DE40(void);
extern s32   func_1CD490(void *h, s32 id, s32 *out);
extern void  func_289C60(s32 a, s32 b, s32 c, s32 d);
extern void  func_1594D0(s32 h, s32 a, s32 id, void *p, s32 n);
extern void  func_1CD340(void *h, s32 id);

void factory_FactoryMenuTexReloadPoll_4ebe90(void)
{
    s32   sel;
    void *h;
    Ent  *e;
    s32   r;
    s32   a;
    s32   b;
    s32   n;

    h = func_1F59D0();
    e = (Ent *)&D_00480820[0];
    n = 0;
    if (e->f04 == 0 && e->f00 != -1) {
        r = func_1CD4F0(h, e->f00);
        e->f04 = r;
        if (r == 1) {
            func_15DE40();
            a = func_1CD490(h, e->f00, &sel);
            b = func_15DE40();
            func_289C60(a, sel, D_00484A88, 0xF081);
            func_1594D0(b, D_00484A88, 0x32E, D_00484A30, 0);
            func_1CD340(h, e->f00);
            e->f00 = -1;
        }
    }
    n += D_00480820[0].f04;
    if (n == 1) {
        D_004807FC = 1;
        D_00480800 = 1;
    }
}
