#include "types.h"
/* normal 0x004FD6D0 -- D_00525100 is OVERLAY data (0x00525100, far outside the
 * gp window at _gp 0x00485170), so it must be `const` to take %hi/%lo.  The
 * 8-byte element stride is what produces `sll $6, $4, 3`. */
typedef struct Ent { void *f0; s32 f4; } Ent;
typedef struct Obj { u8 pad00[0x10]; s16 f10; } Obj;

extern const Ent D_00525100[];
extern const s32 D_00525104;
extern void *D_0048449C;
extern void  func_290F50(void *a, s32 b, void *c, s32 d, s32 e, f32 x);
extern void  func_1F5BE0(void);
extern void *func_207DF0(void);
extern void  func_1B9520(void *a, s32 b, s32 c, f32 x);

s32 normal_BtlChgMenuItemTargetCursorMoveCb_4fd6d0(Obj *p)
{
    func_290F50(D_0048449C, 0x2A, D_00525100[p->f10].f0, D_00525104 + 6, 0, 0.5f);
    func_1F5BE0();
    func_1B9520(func_207DF0(), 4, 0, 1.0f);
    return 1;
}
