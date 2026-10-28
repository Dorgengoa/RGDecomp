/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuGetCommandRow_501230 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00501230 -- read side of the gp byte table at gp-0xCA8.  A NULL
 * context short-circuits to 0xFF; otherwise the index comes from func_3C3120
 * applied to the +0x18 handle and normal_BtlChgPageGetMember_505f90's slot. */

typedef struct Ctx { u8 pad000[0x18]; void *f018; } Ctx;

extern u8    D_004844C8[8];       /* gp - 0xCA8 */
extern void *D_00484454;          /* gp - 0xD1C */

/*rgp*/
/*rgp*/
/*rgp*/

u8 normal_BtlChgMenuGetCommandRow_501230(void)
{
    Ctx *c;

    c = ((Ctx *)GetGameData_1fede0());
    if (c == NULL) {
        return 0xFF;
    }
    return D_004844C8[PartyGetSlotId_3c3120(c->f018, normal_BtlChgPageGetMember_505f90(D_00484454))];
}
