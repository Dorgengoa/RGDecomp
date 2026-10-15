#include "types.h"
/* normal 0x004FE5E0 -- the +/-0x32 flick on widget 0x23 re-lays the whole
 * 0x26/0x55/0x27 row and posts 0x5601.  Only the SECOND out-parameter of
 * func_2910A0 is read; the first func_28EA40 result is discarded and the call
 * is issued again inside the arm. */

typedef struct Rec { u8 pad00[0x1A]; s16 f1A; } Rec;
typedef struct Ctx { u8 pad00[0x7A]; s16 f7A; } Ctx;

extern void    *D_0048449C;       /* gp - 0xCD4 */
extern void    *D_004844A0;       /* gp - 0xCD0 */
extern void    *D_00484498;       /* gp - 0xCD8 */
extern Ctx     *D_00484454;       /* gp - 0xD1C */
extern const u8 D_005278E0[];

extern void  func_2910A0(void *p, s32 id, s32 *outX, s32 *outY);
extern Rec  *func_28EA40(void *p, s32 id);
extern void  func_290F60(void *p, s32 id, s32 c, s32 d);
extern void  normal_BtlChgPageWeaponGridLayout_5047a0(Ctx *p, s32 id, s32 c, s32 d);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_28D820(const void *p, s32 a);

s32 normal_BtlChgMenuWeaponListScrollState_4fe5e0(void)
{
    Rec *r;
    s32  x;
    s32  y;

    func_2910A0(D_0048449C, 0x23, &x, &y);
    func_28EA40(D_004844A0, 0x55F4);
    if ((y == 0x32) || (y == -0x32)) {
        r = func_28EA40(D_004844A0, 0x55F4);
        func_290F60(D_0048449C, 0x23, 0, 0);
        func_290F60(D_0048449C, 0x26, 0x1A, 0x1D);
        func_290F60(D_0048449C, 0x55, 0x1A, 0x1D);
        func_290F60(D_0048449C, 0x27, 0x3C, 0x37);
        normal_BtlChgPageWeaponGridLayout_5047a0(D_00484454, 0x26, D_00484454->f7A, r->f1A);
        func_28EDE0(D_00484498, 0x5601, 0);
    }
    func_28D820(D_005278E0, 0x28);
    return 1;
}
