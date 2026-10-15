#include "types.h"
/* normal 0x00505E70 -- the close path.  f43E is re-read at both of its sites
 * (a fresh `lh` each time), so it stays a field reference. */

typedef struct Obj { u8 pad000[0x43E]; s16 f43E; } Obj;

extern void *normal_UiPageGetLayout_289b60(void *p);
extern s32   normal_BtlChgPageGetStateId_5061a0(Obj *p);
extern void  normal_BtlChgPageLayoutUpdate_506160(Obj *p);
extern s32   func_2899B0(void *p, s32 id);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_28ED70(void *p);

s32 normal_BtlChgPageUpdate_505e70(Obj *p)
{
    void *w;

    if (normal_BtlChgPageGetStateId_5061a0(p) == -1) {
        if (p->f43E == 0) {
            return 0;
        }
    }
    w = normal_UiPageGetLayout_289b60(p);
    if (w == 0) {
        return 0;
    }
    if (p->f43E != 0) {
        if (func_2899B0(p, 0x2B) != 0) {
            p->f43E = 0;
            func_290010(w, 0x2B, 0, -1);
        }
    }
    func_28ED70((u8 *)p + 0x28);
    normal_BtlChgPageLayoutUpdate_506160(p);
    return 1;
}
