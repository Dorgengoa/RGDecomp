#include "types.h"
/* normal 0x00510D90 -- gated on the 0x20-slot allocation succeeding, then on
 * two bytes of the gp record. */
typedef struct Rec { u8 pad00[0x14]; u8 f14; u8 pad15[0x6C - 0x15]; u8 f6C; } Rec;

extern u8   D_004B2570[];
extern Rec *D_004846B8;               /* gp - 0xAB8 */
extern s16  D_004846A8;               /* gp - 0xAC8 */

extern void *func_1839F0(const void *p, s32 n);
extern void  normal_SpaceMenuCancel_5117e0(void);

s32 normal_SpaceMenuMainState_510d90(void)
{
    Rec *r;

    if (func_1839F0(D_004B2570, 0x20) != NULL) {
        r = D_004846B8;
        if (r->f14 != 5) {
            if (r->f6C == 0) {
                normal_SpaceMenuCancel_5117e0();
                D_004846A8 = 2;
            }
        }
    }
    return 1;
}
