#include "types.h"

typedef struct Obj {
    u8  pad00[0x68];
    s16 f68;
    u8  pad6A[0x6];
    u8  f70;
} Obj;

extern void *D_004807E8;                        /* _gp - 0x4988 */
extern f32   D_0047D4E8;                        /* _gp - 0x7C88 */
extern f32   D_0047D4EC;                        /* _gp - 0x7C84 */
extern f32   D_0047D488;                        /* _gp - 0x7CE8 */
extern f32   D_0047D418;                        /* _gp - 0x7D58 */

extern f32  func_290770(void *h, s32 id);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryHelpPageArrowBlink_4f1510(Obj *o)
{
    if (o->f70 == 0) {
        return;
    }
    if (o->f68 == 0) {
        if (func_290770(D_004807E8, 0x96) > D_0047D4E8) {
            func_290690(D_004807E8, 0x96, D_0047D488, D_0047D418, -1.0f);
            o->f68 = 1;
        }
    } else if (o->f68 != 0) {
        if (func_290770(D_004807E8, 0x96) < D_0047D4EC) {
            func_290690(D_004807E8, 0x96, 1.0f, D_0047D418, -1.0f);
            o->f68 = 0;
        }
    }
}
