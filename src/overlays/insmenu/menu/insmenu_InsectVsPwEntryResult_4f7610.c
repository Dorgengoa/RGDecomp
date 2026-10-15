#include "types.h"

/* insmenu 0x004F7610 (428 bytes) -- the insmenu_FUN_004ECD10 family's second
 * member: the panel-mode dispatch on the screen object's s16 at 0xE6, then the
 * 0x1F6 / 0x1F7 / 0x193 table-id chain with the read-modify-write bitfield
 * insert into the byte at +4.
 *
 * The mode arms are an if/else-if CHAIN, not a switch: `bnel $3, $2, .L004F7660`
 * branches PAST the mode==1 arm and carries the NEXT test's constant
 * (`addiu $2, $0, 0x2`) in its likely slot, so the case order is AS WRITTEN.
 * Same reading for the three id tests: two `bnel`s past the arm, then a plain
 * `bne` on the last.
 *
 * MEASURED, and the family's load-bearing decision: there is NO `return` in the
 * mode==1 arm.  EVERY path -- screen null, mode==1, mode not 1/2, id not
 * matched, item null -- converges on the SINGLE tail `return ret;`.  Writing
 * `return ret;` inside the mode==1 arm still produces its `b .L004F77A0` with
 * the shared `daddu $2, $16, $0` duplicated into the delay slot, but it also
 * makes mwcc convert the mode==2 test from `bne` + `nop` into `bnel` with the
 * SAME move duplicated a second time -- 2 wrong words.  With one tail return
 * mwcc spends the duplication once, on the unconditional `b`, and leaves the
 * conditional branch plain.  That is the same single-join reading 004ECD10
 * settled, and it is what produces all three encodings of the join here:
 * `beqz -> .L004F779C`, `bne -> .L004F779C` and `b -> .L004F77A0`.
 *
 * `t` MUST be declared before `p`: `p` takes $18 and `t` takes $19 only when
 * `t` comes first, and the wrong order is a clean 7-word $18/$19 swap.
 *
 * `D_00484360 = 0;` sits in the `jal func_28EDE0` delay slot -- a store SUNK
 * from before the call, the same shape as 004F4260's two arms.
 *
 * The bitfield insert is transcribed from 004ECD10, which is byte-identical:
 * `addiu $3, $0, -0x2` / `daddiu $4, $0, 0x1` / `and` / `or` / `sb` is mwcc's
 * one-bit field store of a literal 1 (mask materialised as a signed 32-bit
 * constant, value as a 64-bit one).  -2/1 is bit 0, -3/2 is bit 1.
 *
 * `lwc1 $f13, -0x7D10($28)` is the .lit4 pool float D_0047D460, the third
 * argument of func_290690 -- same spelling as 004F5110.
 */

typedef struct Screen Screen;
struct Screen {
    u8  pad00[0xE6];
    s16 fieldE6;
};

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

typedef struct Item Item;
struct Item {
    s32 field00;
    u8  bit0 : 1;
    u8  bit1 : 1;
};

extern const u8 D_004FA180[];
extern u8  D_004842E8;          /* gp - 0xE88, passed by address */
extern u8  D_00484360;          /* gp - 0xE10 */
extern Screen *D_00484104;      /* gp - 0x106C */
extern f32 D_0047D460;

extern Handle *func_1FEDE0(void);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void *func_430580(Ctx *a, s32 b);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern s32 insmenu_InsectVsBattleTeamPending_4f9680(void);
extern void func_379400(void *a, s32 b);
extern Item *func_430B30(Ctx *a);
extern Item *func_430B50(Ctx *a);

s32 insmenu_InsectVsPwEntryResult_4f7610(s32 arg0, s32 ret)
{
    Screen *scr;
    Handle *hnd;
    Item *it;
    s32 t;
    void *p;
    s32 mode;
    s32 id;

    scr = D_00484104;
    if (scr != 0) {
        mode = scr->fieldE6;
        if (mode == 1) {
            D_00484360 = 0;
            func_28EDE0(&D_004842E8, 0x88C6, 0);
        } else if (mode == 2) {
            hnd = func_1FEDE0();
            p = func_430580(hnd->field24, 0);
            if (p != 0) {
                func_291110(D_004FA180, 0x9CA7, 1, 1);
                func_290690(D_004FA180, 0x9CA7, 1.0f, D_0047D460, 0.0f);
                t = 0;
                if (insmenu_InsectVsBattleTeamPending_4f9680() != 0) {
                    t = 2;
                }
                func_379400(p, t);
                func_28EDE0(&D_004842E8, 0x88C4, 0);
            }
            id = hnd->field24->field1188->field08;
            if (id == 0x1F6) {
                it = func_430B30(hnd->field24);
                if (it != 0) {
                    it->bit0 = 1;
                }
            } else if (id == 0x1F7) {
                it = func_430B30(hnd->field24);
                if (it != 0) {
                    it->bit1 = 1;
                }
            } else if (id == 0x193) {
                it = func_430B50(hnd->field24);
                if (it != 0) {
                    it->bit1 = 1;
                }
            }
        }
    }
    return ret;
}
