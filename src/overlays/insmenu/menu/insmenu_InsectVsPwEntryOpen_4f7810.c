#include "types.h"

/* insmenu 0x004F7810 (376 bytes) -- the insmenu_FUN_004ECD10 / 004F7610 family's
 * TEMPLATE PAIR member: the same 0x1F6 / 0x1F7 / 0x193 table-id chain, but here
 * READING the bit at +4 into a flag instead of inserting it, then -- only when
 * the flag is set -- clearing a 0x100-byte stack buffer and handing it to
 * func_4319F0 / func_4356D0.
 *
 * The id chain is an if/else-if chain, case order AS WRITTEN: test 1 is a plain
 * `bne` (its delay slot carries the `flag = 0` init), test 2 is a `bnel` PAST
 * the arm carrying `addiu $2, $0, 0x193` in its likely slot, test 3 is a plain
 * `bne` + `nop`.  Same reading as 004F7610.
 *
 * The 0x100-byte clear is the confirmed inline block from
 * `insmenu_InsectVsTeamViewState_4f8a00` (byte-identical): `p = buf; n = 0x100; if (p != 0) do
 * { *p = 0; n -= 1; p += 1; } while (n != 0);` -- the redundant `p != 0` guard
 * on a stack address is what produces `beqz $4, .L004F7940`, and the two `nop`s
 * inside the loop body come with it.
 *
 * `D_00484360 = 1;` sits in the delay slot of the PLAIN `beqz $4` that guards
 * the D_00484104 null test, so it executes unconditionally -- it is written
 * BEFORE the null test in the source, not inside the arm.
 *
 * `D_00484104->fieldE6 = 0;` sinks into the `jal func_1FEDE0` delay slot.
 *
 * `Kind::field08` is s32 here (`lw $3, 0x8($3)`), not the s16 that 004F8A00 and
 * 004F3030 declare for their own `lh` -- read the LOAD WIDTH per unit.
 *
 * Reading `it->bit0` is `lbu 0x4` + `andi 1`; reading `it->bit1` is `lbu 0x4` +
 * `dsll32 30` / `dsrl32 31` (unsigned, so the field is `u8`, not `s8`).
 *
 * MEASURED, and the whole residue of this unit: the boolean `flag` must be
 * `u8` and its test must be BARE (`if (flag)`).  `s32 flag` and `s64 flag`
 * BOTH emit `addiu $17, $0, 0x1` where retail has `daddiu` -- 3 wrong words,
 * and s64 is INERT against s32 (identical object).  `u8` + a bare test is the
 * spelling `insmenu_InsectVsBattleTeamPending_4f9680` (byte-identical) already settled: it is what
 * gives `daddiu` for the 1 and `beql $17, $0` with no re-masking.
 */

typedef struct Obj Obj;
struct Obj {
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

extern u8   D_004842E8;         /* gp - 0xE88, passed by address */
extern u8   D_00484360;         /* gp - 0xE10 */
extern Obj *D_00484104;         /* gp - 0x106C */

extern Handle *func_1FEDE0(void);
extern void func_436450(Obj *a, s32 b);
extern void func_434410(Obj *a, s32 b, s32 c);
extern Item *func_430B30(Ctx *a);
extern Item *func_430B50(Ctx *a);
extern s32  func_430580(Ctx *a, s32 b);
extern void func_4319F0(Ctx *a, char *b, s32 c);
extern void func_4356D0(Obj *a, s32 b, char *c);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsPwEntryOpen_4f7810(s32 p1, s32 arg1)
{
    Handle *hnd;
    Item *it;
    s32 id;
    u8  flag;
    s32 tag;
    char buf[0x100];
    char *p;
    u32 n;

    if (arg1 != 0) {
        D_00484360 = 1;
        if (D_00484104 != 0) {
            func_436450(D_00484104, 0);
            func_434410(D_00484104, 0x6D61, 1);
            D_00484104->fieldE6 = 0;
            hnd = func_1FEDE0();
            id = hnd->field24->field1188->field08;
            flag = 0;
            if (id == 0x1F6) {
                it = func_430B30(hnd->field24);
                if (it != 0) {
                    if (it->bit0 != 0) {
                        flag = 1;
                    }
                }
            } else if (id == 0x1F7) {
                it = func_430B30(hnd->field24);
                if (it != 0) {
                    if (it->bit1 != 0) {
                        flag = 1;
                    }
                }
            } else if (id == 0x193) {
                it = func_430B50(hnd->field24);
                if (it != 0) {
                    if (it->bit1 != 0) {
                        flag = 1;
                    }
                }
            }
            if (flag) {
                tag = func_430580(hnd->field24, 0);
                p = buf;
                n = 0x100;
                if (p != 0) {
                    do {
                        *p = 0;
                        n -= 1;
                        p += 1;
                    } while (n != 0);
                }
                func_4319F0(hnd->field24, buf, tag);
                func_4356D0(D_00484104, 0, buf);
            }
        }
    }
    func_28EDE0(&D_004842E8, 0x88CA, 0);
    return 1;
}
