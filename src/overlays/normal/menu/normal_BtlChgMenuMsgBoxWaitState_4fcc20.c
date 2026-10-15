/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by the
 * SYMBOL-not-integer lever: an unnamed far address spelled as an integer
 * gives `lui`/`ori`; retail's `lui`/`addiu` pair NEEDS a relocation, so it can
 * only come from a symbol reference.  `extern u8 D_004B2570[0x10];` + pass the
 * array.  3 bad -> MATCH, first build.
 * The park note recorded this as its untried NEXT LEAD and believed it blocked
 * because "the object scorer cannot resolve a cross-image reloc".  That
 * blocker is REFUTED: bytecheck.resolve() resolves a name matching
 * ^(?:D|func|jtbl|jpt|L)_?[0-9A-Fa-f]{6,8}$ at its own address, so an
 * UNDEFINED D_004B2570 scores and links with NO config/ line.
 * The [0x10] size is load-bearing: it keeps the object out of small data, or
 * every reference comes out GPREL16 instead of lui/%lo.
 * Arms B/C/D in the old note (hex literal / decimal / (void *) cast with the
 * callee retyped) stay a measured 3-arm, ONE-object null -- the RADIX and
 * POINTER-CAST axes are inert; only the SYMBOL axis is live. */
#include "types.h"
/* normal 0x004FCC20 -- run the 0x4B2570 request, then post 0x560D when the
 * result is 1 or 2.  `sltiu $1, x-1, 2` is the two-arm switch's range test. */

extern u8 D_004B2570[0x10];
extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_00484498;          /* gp - 0xCD8 */

extern s32  func_28E170(void *p, void *a, s32 b, s32 c);
extern s32  func_28EC60(void *p);
extern void func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgMenuMsgBoxWaitState_4fcc20(void)
{
    s32 v;

    v = func_28E170(D_004844A0, D_004B2570, 0, 0);
    func_28EC60(D_004844A0);
    if ((v == 1) || (v == 2)) {
        func_28EDE0(D_00484498, 0x560D, 0);
    }
    return 1;
}
