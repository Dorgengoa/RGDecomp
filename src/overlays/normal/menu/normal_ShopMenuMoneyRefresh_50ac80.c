#include "types.h"
/* normal 0x0050AC80 -- pairs two widget ids: both are enabled, both records
 * are looked up, then the 0x160 handle and two func_3C7BA0 results are stored
 * as 64-bit values. */
typedef struct Rec { u8 pad00[8]; s64 f08; u8 pad10[0x28 - 0x10]; s64 f28; } Rec;
typedef struct Src { u8 pad00[0x160]; s64 f160; } Src;
typedef struct Sys { u8 pad00[0x18]; Src *f18; } Sys;

extern const u8 D_00527C40[];

extern Sys *func_1FEDE0(void);
extern void func_291110(const void *p, u16 id, s32 c, s32 d);
extern Rec *func_28F2B0(const void *p, u16 id, s32 n);
extern s32  func_3C7BA0(Src *p, s32 a, s32 b, s32 c);

s32 normal_ShopMenuMoneyRefresh_50ac80(u16 a, u16 b)
{
    Sys *sys;
    Rec *ra;
    Rec *rb;

    func_291110(D_00527C40, a, 1, 1);
    func_291110(D_00527C40, b, 1, 1);
    sys = func_1FEDE0();
    ra = func_28F2B0(D_00527C40, a, 0);
    if (ra == NULL) {
        return 0;
    }
    rb = func_28F2B0(D_00527C40, b, 0);
    if (rb == NULL) {
        return 0;
    }
    ra->f08 = sys->f18->f160;
    rb->f08 = func_3C7BA0(sys->f18, 0, -1, 0);
    rb->f28 = func_3C7BA0(sys->f18, 1, -1, 0);
    return 1;
}
