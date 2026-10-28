/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwBattleEnter_4ed850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004ED850 (80 bytes, 20 instructions, 5 calls) -- open the record
 * at +0x350, blank its 0x8F-byte text buffer, close it and set the dirty flag.
 * Near-twin of insmenu_InsectVsRegPwEnter_4ed0a0 (different opener, different offset).
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field024;
};

extern u8 D_00484304;       /* gp - 0xE6C */

/*rgp*/
/*rgp*/
extern void memset(void *a, s32 b, s32 c);
/*rgp*/

s32 insmenu_InsectVsPwBattleEnter_4ed850(void)
{
    Handle *h;
    void *r;

    h = ((Handle *)GetGameData_1fede0());
    r = RecordGetPayloadIfKind28_430b50(h->field024);
    memset((u8 *)r + 0x350, 0, 0x8F);
    RecordAdvanceState_430bf0(h->field024, 0);
    D_00484304 = 1;
    return 1;
}
