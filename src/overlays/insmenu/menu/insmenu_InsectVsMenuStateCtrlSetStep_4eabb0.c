#include "types.h"

/* insmenu 0x004EABB0 (508 bytes, 127 instructions, 16 calls) -- the map-view
 * confirm handler.  ⚠ The flag is `$5`, the SECOND parameter; the first is
 * never read.
 *
 * The three-way dispatch is an if/else CHAIN, not a switch: the case bodies
 * come out in the same order as the tests.
 *
 * ★ `D_00484314` is declared WITH A SIZE.  Without one the two indexed accesses
 * come out as `lui`/`addiu` of an absolute address instead of one gp-relative
 * `addiu $2, $28, -0xE5C`, two words each.
 * ★ Guard polarity in the toggle: the one-store arm (`= 0`) is retail's BRANCH
 * TARGET, carried in a `bnel` delay slot, so it is the `else`.  Written the
 * other way round it costs two words.
 * ★ The `func_28EA40(...)->field14 = 1` store is SPLIT from its call, or mwcc
 * materialises the stored 1 before the call and has to spend a callee-saved
 * register on it instead of reusing the compare's `$3`.
 */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x12];
    s16 field12;
};

typedef struct Slot Slot;
struct Slot {
    u8  pad00[0x14];
    s16 field14;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern u8  D_00484304;      /* gp - 0xE6C */
extern u8  D_00484314[2];   /* gp - 0xE5C */
extern f32 D_0047D488;      /* gp - 0x7CE8 */
extern f32 D_0047D49C;      /* gp - 0x7CD4 */

extern void func_28EA90(const void *a, s32 b, s32 c);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern s32  func_28E100(const void *a, const void *b, const void *c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern Slot *func_28EA40(const void *a, s32 b);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern s32  func_184960(const void *a);
extern void insmenu_InsectVsCtrlSetRefreshRows_4eb050(void);

s32 insmenu_InsectVsMenuStateCtrlSetStep_4eabb0(s32 p1, s32 open)
{
    Panel *pan;
    Slot *slot;
    s32 mode;

    if (open != 0) {
        func_28EA90(D_004FA1A0, 0x7533, 0);
        func_290690(D_004FA180, 0xF, 1.0f, D_0047D488, -1.0f);
        func_290690(D_004FA180, 0xE, 1.0f, D_0047D488, -1.0f);
    }
    D_00484304 = 0;
    mode = func_28E100(D_004FA1A0, D_004B2570, D_004B27E0, 4);
    pan = func_28EC60(D_004FA1A0);
    if (mode == 1) {
        D_00484304 = 1;
        func_290690(D_004FA180, 0xF, 0.0f, D_0047D49C, -1.0f);
        func_290690(D_004FA180, 0xE, 0.0f, D_0047D49C, -1.0f);
        insmenu_InsectVsConfirmDialogOpen_4ee7c0(0xA);
    } else if (mode == 2) {
        D_00484304 = 1;
        func_290690(D_004FA180, 0xA, 0.0f, D_0047D49C, -1.0f);
        func_28EDE0(&D_004842E8, 0x7539, 0);
        slot = func_28EA40(D_004FA1A0, 0x7532);
        slot->field14 = 1;
    } else {
        if ((func_1839F0(D_004B2570, 0xA000) != 0) ||
            ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0xA000) != 0))) {
            if (D_00484314[pan->field12] == 0) {
                if (func_184960(D_004B27E0) != 0) {
                    D_00484314[pan->field12] = 1;
                }
            } else {
                D_00484314[pan->field12] = 0;
            }
            insmenu_InsectVsCtrlSetRefreshRows_4eb050();
        }
    }
    return 1;
}
