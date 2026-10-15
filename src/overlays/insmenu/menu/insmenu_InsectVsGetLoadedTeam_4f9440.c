#include "types.h"

/* insmenu 0x004F9440 (320 bytes) -- sibling of insmenu_FUN_004F7610 /
 * insmenu_FUN_004ECD10: same id-dispatch family, different constants
 * (0x12F / 0x130 / 0x192), reads the bitfield byte at Item+4 and writes ONE
 * halfword through the out-parameter.
 *
 * Chain reading (branch polarity per test):
 *   beq  $16,0x12F -> .L004F9488   : first term of an `||`, jumps INTO the body
 *   bnel $16,0x130 -> .L004F9520   : second term false -> the else-if, likely
 *                                    slot carries the NEXT constant 0x192
 * so the arm order is AS WRITTEN.
 *
 * The inner guard is the `||` join: `bnel $16,0x12F` past the first term,
 * `bnel bit1,0` INTO the body (whole condition already true), the explicit
 * `addiu $3,$0,0x130` at 0x004F94BC is the non-likely copy of the second
 * term's constant, and the last term ends on a plain `beqz` into the shared
 * `daddu $2,$0,$0` at .L004F9568.
 */

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

typedef struct Rec Rec;
struct Rec {
    u8 pad00[600];
};

typedef struct ItemA ItemA;
struct ItemA {
    s32 field00;
    u8  bit0 : 1;
    u8  bit1 : 1;
    u8  bit2 : 1;
    u8  pad05[8];
    s8  sel[2];
    u8  pad0F[1];
    Rec rec[2];
};

typedef struct ItemB ItemB;
struct ItemB {
    s32 field00;
    u8  bit0 : 1;
    u8  bit1 : 1;
    u8  pad05[11];
    s32 field10;
    u8  tail[4];
};

extern Handle *func_1FEDE0(void);
extern ItemA *func_430B70(Ctx *a);
extern ItemB *func_430B50(Ctx *a);

void *insmenu_InsectVsGetLoadedTeam_4f9440(s16 *out)
{
    Handle *hnd;
    ItemA *ia;
    ItemB *ib;
    s32 id;
    s32 v;

    hnd = func_1FEDE0();
    if (hnd == 0) {
        return 0;
    }
    id = hnd->field24->field1188->field08;
    if (!(id != 0x12F && id != 0x130)) {
        ia = func_430B70(hnd->field24);
        if (ia == 0) {
            return 0;
        }
        if ((id == 0x12F && ia->bit1) || (id == 0x130 && ia->bit2)) {
            v = 0;
            if (id == 0x130) {
                v = 1;
            }
            *out = ia->sel[(s16)v];
            return &ia->rec[(s16)v];
        }
    } else if (id == 0x192) {
        ib = func_430B50(hnd->field24);
        if (ib == 0) {
            return 0;
        }
        if (id == 0x192 && ib->bit0) {
            *out = ib->field10;
            return ib->tail;
        }
    }
    return 0;
}
