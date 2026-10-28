/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveScreenRequest_4f3250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F3250 (140 bytes) -- raise the "menu ready" event once the save
 * machine reaches one of the two finished states.
 *
 * ★ The compare chain runs 0xF, 0xE, 0xC and the arms land 0xC, 0xE: a switch,
 * whose chain is the REVERSE of the source case order and whose blocks follow
 * the source order.  The 0xF case is empty and its `beql` carries the
 * epilogue's `ld $31`. */

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    void *field24;
};

extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern u8 D_00484310;           /* gp - 0xE60 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSaveScreenRequest_4f3250(void)
{
    s32 st;

    st = RecordGetStateParamMaybe_430890(((Handle *)GetGameData_1fede0())->field24);
    switch (st) {
    case 0xC:
        if (D_00484310 == 0) {
            StateMachineSetState_28ede0(&D_004842E8, 0x88B9, 1);
        }
        break;
    case 0xE:
        if (D_00484310 == 0) {
            StateMachineSetState_28ede0(&D_004842E8, 0x88B9, 1);
        }
        break;
    case 0xF:
        break;
    }
    return 1;
}
