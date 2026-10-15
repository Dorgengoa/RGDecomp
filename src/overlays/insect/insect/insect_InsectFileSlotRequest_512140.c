#include "types.h"
/* insect 0x00512140 -- 300 bytes, 75 instructions, 9 calls, 2 conditional
 * branches.  A path-string builder: nine `func_1343B8` format strings selected
 * by a kind, into the buffer at the head of the object.
 *
 * ★ THE TABLE IS BIASED, AND THAT NAMES THE CASE SET.  `addiu $3, $6, 0x1`
 * before `sltiu $1, $3, 0x9` means the index is `kind + 1`, so the nine entries
 * of jtbl_00525210 are cases **-1 through 7**, not 0 through 8.  All nine
 * targets are distinct, so every case has a body and there is no `default`
 * block -- out of range falls straight to the epilogue.  (Contrast
 * insect_InsectBattleFlowSelectVictoryCond_502a30 / 00502c20, where an UNbiased table with repeated exit
 * entries names empty cases -- see [[insect-jump-table-density]].)
 *
 * ⚠ NOTHING IS MARSHALLED for `func_134A98`: `$4` and `$5` still hold the
 * incoming parameters, untouched, so the call is the two-argument
 * `func_134A98(o, name)` its other three insect call sites already fix.  m2c
 * reads `$6` -- which by then holds the JUMP TABLE'S OWN ADDRESS -- as a third
 * argument.  That is the leftover-argument trap with an unusually loud tell.
 *
 * ★★★★★★ THE FORMAT STRING'S CONVERSION COUNT NAMES THE CALL'S ARITY, and it
 * is what explains an argument-register assignment that reads as arbitrary.
 * func_1343B8 is an sprintf -- UNPROTOTYPED, because it is called with three,
 * four and five arguments from this one function:
 *
 *   case 3  'snd2/mon/%s.snd'    1 conversion  -> 3 args; `$7` is LEFTOVER,
 *                                                still the `o->f24` guard load
 *   cases 0,2,4,5  two %s        2 conversions -> 4 args ($6, $7)
 *   cases 6,7      three %s      3 conversions -> 5 args ($6, $7, **$8**)
 *
 * `$8` is the fifth argument register in this ABI, so `name` HAS to live in
 * `$8` -- which is why retail copies it there in the guard's delay slot and
 * spends a `daddu $7,$8,$0` at each two-conversion site.  Reading case 3 as a
 * four-argument call instead puts `name` in `$7`, deletes those four moves and
 * adds two of its own: **3 words short, and the allocation looks like a
 * compiler difference.**
 *
 * The three gp globals (-0x4170/-0x416C/-0x4168 = 0x00481000/04/08) are inside
 * the gp window 0x47D170..0x48D170 and must stay PLAIN externs; only the
 * `D_0052xxxx` overlay-data format strings take `const`.
 */

typedef struct Buf {
    u8  f00[0x24];              /* the destination string buffer */
    s32 f24;                    /* +0x24 */
    s32 f28;                    /* +0x28 */
} Buf;

extern const u8 D_00525180[];
extern const u8 D_00525190[];
extern const u8 D_005251A0[];
extern const u8 D_005251B0[];
extern const u8 D_005251C0[];
extern const u8 D_005251D8[];
extern const u8 D_005251F0[];

extern const u8 *D_00481000;    /* gp window: PLAIN */
extern const u8 *D_00481004;
extern const u8 *D_00481008;

extern void func_134A98(void *a, void *b);
extern void func_1343B8();     /* variadic: 3, 4 and 5 args at the sites below */

void insect_InsectFileSlotRequest_512140(Buf *o, void *name, s32 kind)
{
    s32 t;

    t = o->f24;
    if (t == -1) {
        o->f28 = 1;
        switch (kind) {
        case -1:
            func_134A98(o, name);
            break;
        case 0:
            func_1343B8(o, D_00525180, D_00481004, name);
            break;
        case 1:
            func_134A98(o, name);
            break;
        case 2:
            func_1343B8(o, D_00525190, D_00481000, name);
            break;
        case 3:
            func_1343B8(o, D_005251A0, name);
            break;
        case 4:
            func_1343B8(o, D_005251B0, D_00481004, name);
            break;
        case 5:
            func_1343B8(o, D_005251C0, D_00481004, name);
            break;
        case 6:
            func_1343B8(o, D_005251D8, D_00481000, D_00481008, name);
            break;
        case 7:
            func_1343B8(o, D_005251F0, D_00481000, D_00481008, name);
            break;
        }
    }
}
