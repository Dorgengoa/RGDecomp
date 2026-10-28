/* rgp:protos */
#define RGP_SELF_normal_HelpMenuListFill_522e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00522E30 -- eight formatted lines, one per row of a 118-byte
 * record array based at the gp pointer 0x004849E8.  The index is the caller's
 * base plus the loop counter; mwcc strength-reduces the *118 into the
 * shift/subtract chain in the listing. */
typedef struct E {
    u8  pad000[0x6];
    u8  f006[0x70];
} E;

extern void *D_004849E8;
extern u8 normal_D_00528180[];

/*rgp*/

void normal_HelpMenuListFill_522e30(s32 base)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        UiSetTextString_28f510(normal_D_00528180, 0x2A, ((E *)D_004849E8)[base + i].f006, i);
    }
}
