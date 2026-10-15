#include "types.h"
/* normal 0x00501230 -- read side of the gp byte table at gp-0xCA8.  A NULL
 * context short-circuits to 0xFF; otherwise the index comes from func_3C3120
 * applied to the +0x18 handle and normal_BtlChgPageGetMember_505f90's slot. */

typedef struct Ctx { u8 pad000[0x18]; void *f018; } Ctx;

extern u8    D_004844C8[8];       /* gp - 0xCA8 */
extern void *D_00484454;          /* gp - 0xD1C */

extern Ctx  *func_1FEDE0(void);
extern s32   normal_BtlChgPageGetMember_505f90(void *p);
extern s32   func_3C3120(void *h, s32 slot);

u8 normal_BtlChgMenuGetCommandRow_501230(void)
{
    Ctx *c;

    c = func_1FEDE0();
    if (c == NULL) {
        return 0xFF;
    }
    return D_004844C8[func_3C3120(c->f018, normal_BtlChgPageGetMember_505f90(D_00484454))];
}
