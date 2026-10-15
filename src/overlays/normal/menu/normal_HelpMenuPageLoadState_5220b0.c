#include "types.h"
/* normal 0x005220B0 -- the item/skill description box.  `b != 0` opens it:
 * the 0x7534 frame, the caption built out of the 0x76-byte record at
 * D_004849E8[D_004849F8], and the request handle parked in D_004849E0.  Every
 * call then polls func_1CD4F0, and on state 1 the measured text is laid into
 * the box, the request is closed and the 0x753B hand-off fires.
 *
 * `daddu $16,$5,$0` is in func_1F59D0's DELAY SLOT, so the FIRST statement is
 * `g = func_1F59D0();` and the guard on `b` comes after it.
 * `sll 4 / subu / sll 2 / subu / sll 1` is a 0x76-byte array stride, i.e.
 * `&base[i]` with an s16 index -- recomputed at both use sites, so the record
 * pointer is NOT a shared local.
 * `bgez $3, .L / sra $2,$3,4` with the `addiu $2,$3,0xF` bias is a SIGNED
 * `/ 16`, not a shift.
 * `slti $1, $2, 0x2` writes $at at BOTH sites: the source token is `> 1`,
 * not `>= 2` ([[at-compare-class]]).
 * The two `bne` guards are PLAIN, not likely, and each carries its own gp
 * store in the delay slot -- the store is the statement before the test. */

typedef struct Rec { u8 pad00[4]; s16 f04; u8 pad06[0x76 - 6]; } Rec;
typedef struct Cap { u8 b[0x4C]; } Cap;
typedef struct Lbl { u8 b[0x20]; } Lbl;

extern const u8 D_005268B0[];
extern u8 D_005281A0[];
extern u8 D_005281C0[];

extern s32   D_004849A0;          /* gp - 0x7D0 */
extern s32   D_004849A8;          /* gp - 0x7C8 */
extern s32   D_004849E0;          /* gp - 0x790 */
extern s32   D_004849E4;          /* gp - 0x78C */
extern Rec  *D_004849E8;          /* gp - 0x788 */
extern s16   D_004849F8;          /* gp - 0x778 */
extern u8    D_004849FC;          /* gp - 0x774 */

extern s32   func_1F59D0(void);
extern void  func_28EA90(void *a, s32 b, s32 c);
extern s32   func_15DE40(void);
extern void  func_158AC0(s32 a, s32 b);
extern void  func_14D830(s32 a);
extern void  func_134A98(void *a, const void *b);
extern void  func_134690(void *a, const void *b);
extern void  func_1343B8(void *a, const void *b, u8 c);
extern s32   func_1CD870(s32 a, Cap *b, s32 c);
extern void  func_1CD670(s32 a);
extern s32   func_1CD4F0(s32 a, s32 b);
extern void  func_14D8E0(s32 a);
extern s32   func_14D9D0(s32 a, s32 b);
extern s32   func_1CD490(s32 a, s32 b, s32 *c);
extern void  func_14DA10(s32 a, s32 b);
extern void  func_1319A8(s32 a, s32 b, s32 c);
extern void  func_1594D0(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_1CD340(s32 a, s32 b);
extern void  func_290AC0(void *a, s32 b, Lbl *c);
extern void  func_28EDE0(void *a, s32 b, s32 c);

s32 normal_HelpMenuPageLoadState_5220b0(void *a, s32 b)
{
    s32  g;
    s32  box;
    s32  txt;
    s32  h;
    s32  n;
    Cap  cap;
    Lbl  lbl;

    g = func_1F59D0();
    if (b != 0) {
        func_28EA90(D_005281C0, 0x7534, 0);
        func_158AC0(func_15DE40(), 0x32C);
        h = func_1F59D0();
        func_14D830(D_004849A0);
        D_004849E0 = -1;
        D_004849E4 = 0;
        func_134A98(&cap, D_005268B0);
        func_134690(&cap, (const u8 *)&D_004849E8[D_004849F8] + 0x46);
        if (D_004849E8[D_004849F8].f04 > 1) {
            func_1343B8(&cap, &cap, D_004849FC);
        }
        D_004849E0 = func_1CD870(h, &cap, 0);
        if (D_004849E0 == -1) {
            return 0;
        }
        func_1CD670(h);
    }
    D_004849E4 = func_1CD4F0(g, D_004849E0);
    if (D_004849E4 == 1) {
        box = func_15DE40();
        func_14D8E0(D_004849A0);
        h = func_14D9D0(D_004849A0, 1);
        txt = func_1CD490(g, D_004849E0, &n);
        func_14DA10(D_004849A0, (n / 16) + 1);
        func_1319A8(h, txt, n);
        func_1594D0(box, h, 0x32C, D_004849A0, 0);
        func_1CD340(g, D_004849E0);
        D_004849E0 = -1;
        if (D_004849E8[D_004849F8].f04 > 1) {
            func_1343B8(&lbl, (const u8 *)&D_004849E8[D_004849F8] + 0x66,
                        D_004849FC);
        } else {
            func_134A98(&lbl, (const u8 *)&D_004849E8[D_004849F8] + 0x66);
        }
        func_290AC0(D_005281A0, 0x32, &lbl);
        func_28EDE0(&D_004849A8, 0x753B, 1);
    }
    return 1;
}
