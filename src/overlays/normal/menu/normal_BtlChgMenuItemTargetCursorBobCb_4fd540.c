#include "types.h"
#pragma usefloatacc off
/* normal 0x004FD540 -- the 0x2A gauge: on the short path post a single value,
 * otherwise refill the widget's 0x20 slot table from D_00525100 and post the
 * scaled value. */

typedef struct Obj {
    u8  pad000[0x10];
    s16 f10;
} Obj;

typedef struct Slot {
    s16 f00;
    u8  pad02[0x1E];
} Slot;                         /* 0x20 */

typedef struct Rec {
    u8    pad000[0x20];
    Slot *f20;
} Rec;

typedef struct Src {
    u8    pad000[0x18];
    void *f18;
} Src;

extern s32   D_00525100[];
extern s32   D_00525104[3];

extern void *D_004844C4;        /* gp - 0xCAC */
extern f32   D_004844B8;        /* gp - 0xCB8 */
extern void *D_0048449C;        /* gp - 0xCD4 */
extern f32   D_0047D3D0;        /* gp - 0x7DA0 */

extern s32   func_3D4F00(void *p);
extern void  func_28B630(f32 *out, f32 v);
extern f32   func_128FD0(f32 v);
extern Src  *func_1FEDE0(void);
extern s32   func_3C2010(void *p, s32 a, s32 b);
extern Rec  *func_290460(void *p, u16 id);
extern void  func_290F50(void *p, u16 id, s32 a, s32 b, s32 c, f32 v);
extern void  func_290F60(void *p, u16 id, s32 a, s32 b);

s32 normal_BtlChgMenuItemTargetCursorBobCb_4fd540(Obj *p)
{
    Src *src;
    Slot *slot;
    Rec *rec;
    s32 n;
    s32 i;
    f32 v;

    if (D_004844C4 == NULL) {
        return 0;
    }
    if (func_3D4F00(D_004844C4) == 0) {
        func_28B630(&D_004844B8, D_0047D3D0);
        v = 12.0f * func_128FD0(D_004844B8);
        func_290F50(D_0048449C, 0x2A, (s32)(v + (f32)D_00525100[p->f10 * 2]),
                    D_00525104[0] + 6, 0, 0.5f);
        return 1;
    }
    func_28B630(&D_004844B8, D_0047D3D0);
    v = 12.0f * func_128FD0(D_004844B8);
    src = func_1FEDE0();
    if (src == NULL) {
        return 0;
    }
    n = func_3C2010(src->f18, 1, 1);
    rec = func_290460(D_0048449C, 0x2A);
    if (rec != NULL) {
        slot = rec->f20;
        if (slot != NULL) {
            for (i = 0; i < n; i++) {
                slot[i].f00 = D_00525100[i * 2];
            }
            slot[n].f00 = -1;
        }
    }
    func_290F60(D_0048449C, 0x2A, (s32)v, D_00525104[0] + 6);
    return 1;
}
