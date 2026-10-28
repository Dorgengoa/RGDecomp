/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwInputStep_4ecd10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004ECD10 (268 bytes) -- the 004ECCD0 opener (latch the gp byte
 * flag from insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20) followed by a two-arm dispatch on the
 * panel object's s16 at 0xE6.
 *
 * `lw $2, -0x106C($28)` sits in the beql's LIKELY slot, i.e. it is the FIRST
 * instruction of the fall-through block, and the `sb $0` that clears the flag
 * is in the following beqz's plain delay slot -- so the load of D_00484104
 * happens BEFORE the store to D_00484304.  A load will not cross a store to a
 * global, so the pointer is NAMED first and the flag cleared after it.
 *
 * `bnel $18, 2` branches PAST the first arm, so this is an if/else chain in
 * source order, not a switch.
 *
 * The else arm's `andi $2, $0, 0x1` / `sll 1` / `sll 2` is the one-bit
 * bitfield insert of a literal ZERO -- mwcc masks the value to the field width
 * even when it is 0 and CSEs that andi across both inserts.  The taken arm
 * folds the same two inserts to the constants 2 and 4.
 */

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    s32 field24;
};

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0xE6];
    s16 fieldE6;
};

typedef struct Rec Rec;
struct Rec {
    s32 field00;
    u8  bit0 : 1;
    u8  bit1 : 1;
    u8  bit2 : 1;
    u8  pad05[0xE7];
    s32 fieldEC;
};

extern u8 D_00484304;       /* gp - 0xE6C */
extern Obj *D_00484104;     /* gp - 0x106C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsRegPwInputStep_4ecd10(void)
{
    Handle *hnd;
    Rec *slot;
    Obj *obj;
    s32 mode;

    if (insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20() != 0) {
        D_00484304 = 1;
        return 1;
    }
    obj = D_00484104;
    D_00484304 = 0;
    if (obj != 0) {
        mode = obj->fieldE6;
        if (mode != 0) {
            hnd = ((Handle *)GetGameData_1fede0());
            slot = ((Rec *)RecordGetPayloadIfKind3C_430b10(hnd->field24));
            TextEntryGetString_435640(D_00484104, &slot->fieldEC);
            if (mode == 2) {
                slot->bit1 = 1;
                slot->bit2 = 1;
                RecordSetStateClamped_430db0(hnd->field24, 0x25C, 0);
            } else {
                slot->bit1 = 0;
                slot->bit2 = 0;
                RecordSetStateClamped_430db0(hnd->field24, 0x259, 0);
            }
        }
    }
    return 1;
}
