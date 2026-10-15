#include "types.h"

/* insmenu 0x004F35E0 (140 bytes) -- register the three lab-menu sound banks.
 *
 * ★ `sll 3 / subu / sll 3` is a multiply by 56, the descriptor stride, so the
 * overlay table is an ARRAY of 56-byte records and the call takes `&tbl[i]`.
 * ★★ D_00480458 is declared `[2]` and indexed to [2]: the declared size is a
 * RELOCATION CONTROL, not a bound.  At `[3]` (12 bytes) mwcc puts the array
 * OUT of small data and emits a %hi/%lo pair where retail has a single
 * `addiu $2, $28, -0x4D18`, which reads as one word LONG.  `[1]` works too and
 * gives the identical text. */

typedef struct Bank Bank;
struct Bank {
    u8 pad00[0x38];
};

extern const Bank D_004FA1D0[];
extern s32 D_00480458[2];       /* gp - 0x4D18 */

extern void func_28B160(const Bank *tbl, s32 n);
extern s32  func_28B550(const Bank *b, s32 id, s32 c, s32 d);
extern void func_28AFD0(void);

s32 insmenu_InsectVsMenuResRequest_4f35e0(void)
{
    s32 i;

    func_28B160(D_004FA1D0, 3);
    for (i = 0; i < 3; i++) {
        if (func_28B550(&D_004FA1D0[i], D_00480458[i], 0, 0) == -1) {
            break;
        }
    }
    func_28AFD0();
    return 0;
}
