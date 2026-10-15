#include "types.h"
/* normal 0x00509520 -- (re)binds the 0x35 portrait slot of the D_00527C40
 * panel to `e`.  When func_3D4610 says the roster is in its plain state the
 * slot just takes the entity's own 0x10->0x30 descriptor and the 0x7B/0x7C/0x7D
 * decorations are hidden; otherwise the entity is handed the 0x527CB0
 * descriptor through its virtual slot 17, the four decoration handles are
 * collected into a 0x10-byte frame block and pushed back into it through
 * func_289F30, and the decorations are shown.  Either way the slot is moved to
 * (x, y) and faded to `s`; with no entity at all only the fade runs, at -s.
 *
 * SIX parameters and `$5` IS NEVER WRITTEN before func_28F620 -- the second
 * parameter rides straight through as that call's second argument, the same
 * reading normal_ShopMenuBuyRowsRefresh_50b5c0 records for normal_ShopMenuBuyRowIconsRefresh_50dae0.  Under EABI the
 * float lands in $f12 independently of the five integers in $4..$8, so the
 * `mov.s $f20,$f12` in the entry guard's delay slot is the SIXTH parameter.
 * ONE VIRTUAL call (`lw $25,0($20) / lw $25,0x4C($25) / jalr $25`), so the unit
 * is .cpp -- a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08, so
 * 0x4C is slot (0x4C-8)/4 = 17.
 * `lw $25,0x0($20)` rides the func_3D4610 guard's LIKELY SLOT, so the vtable
 * fetch belongs to the arm, not to the test.
 * func_3D4610 TAKES `e`, even though its own delay slot is a `nop`: the
 * `daddu $4,$20,$0` that sets it up rides the PRECEDING guard's likely slot.
 * Written against a (void) prototype the unit is right length and two bad --
 * a missing argument can hide entirely inside an earlier branch.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is mwcc SHARING the constant between
 * arguments 3 and 4 of func_291110, not two source constants. */

struct Desc {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void attach(const void *p);    /* slot 17 -> vtable +0x4C */
    u8    pad04[0x10 - 4];
    void *f10;
};

typedef struct Slot { u8 pad00[2]; s16 f02; s32 f04; u8 pad08[0x14 - 8]; s32 f14; } Slot;
typedef struct Info { u8 pad00[0x30]; s32 f30; } Info;

extern const u8 D_00527C40[];
extern const u8 D_00527CB0[];

extern "C" void  func_131B60(void *p, s32 c, s32 n);
extern "C" void  func_289F30(Desc *e, void *p);
extern "C" Slot *func_28F620(const void *p, s32 id, s32 c);
extern "C" s32   func_28FE10(const void *p, s32 id, s32 c);
extern "C" void  func_290690(const void *p, s32 id, f32 x, f32 y, f32 z);
extern "C" void  func_290F60(const void *p, s32 id, s32 x, s32 y);
extern "C" void  func_291110(const void *p, s32 id, s32 c, s32 d);
extern "C" s32   func_3D4610(Desc *e);

extern "C" s32 normal_ShopMenuItemInfoShow_509520(Desc *e, s32 wid, s32 id, s32 x, s32 y, f32 s);

s32 normal_ShopMenuItemInfoShow_509520(Desc *e, s32 wid, s32 id, s32 x, s32 y, f32 s)
{
    Slot *w;
    s32   buf[4];

    if (e != 0) {
        w = func_28F620(D_00527C40, wid, 0);
        if (w == 0) {
            return 0;
        }
        if (func_3D4610(e) != 0) {
            w->f02 = 9;
            w->f04 = ((Info *)e->f10)->f30;
            w->f14 = 0;
            func_291110(D_00527C40, 0x35, 0, 1);
            func_291110(D_00527C40, 0x7C, 0, 1);
            func_291110(D_00527C40, 0x7B, 0, 1);
            func_291110(D_00527C40, 0x7D, 0, 1);
        } else {
            e->attach(D_00527CB0);
            w->f02 = 9;
            w->f04 = (s32)D_00527CB0;
            w->f14 = ((Info *)e->f10)->f30;
            func_291110(D_00527C40, 0x35, 1, 1);
            func_131B60(buf, 0, 0x10);
            buf[0] = func_28FE10(D_00527C40, 0x7C, 0);
            buf[1] = func_28FE10(D_00527C40, 0x7B, 0);
            buf[2] = (s32)func_28F620(D_00527C40, 0x7B, 0);
            buf[3] = func_28FE10(D_00527C40, 0x7D, 0);
            func_291110(D_00527C40, 0x7C, 1, 1);
            func_291110(D_00527C40, 0x7B, 1, 1);
            func_291110(D_00527C40, 0x7D, 1, 1);
            func_289F30(e, buf);
        }
        func_290F60(D_00527C40, id, x, y);
        func_290690(D_00527C40, id, 1.0f, s, -1.0f);
    } else {
        func_290690(D_00527C40, id, 0.0f, -s, -1.0f);
    }
    return 1;
}
