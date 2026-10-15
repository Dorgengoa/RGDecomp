#include "types.h"
/* normal 0x00514560 -- the gameplay HUD/panel builder: one long call sequence
 * on a single object.
 *
 * `lhu 0xA / dsll32 16 / dsrl32 18` is a 14-BIT BITFIELD at bits 2..15 of the
 * halfword, and both it and `rec->f4` are read BEFORE the intervening
 * func_2912E0 call, so each needs its own local.
 * `p->f8 = 0x32D;` is written BEFORE func_290450(p) so the `sw` fills that
 * call's delay slot. */
typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    u16   fA_lo : 2;
    u16   fA_hi : 14;
} Rec;

typedef struct Obj {
    u8  pad00[8];
    s32 f08;
    u8  pad0C[0x14 - 0x0C];
    s8  f14;
} Obj;

extern void *D_004846B0;
extern void *D_00481BBC;
extern void *func_206A40(void);
extern Rec  *func_42C500(void *a, s32 b);
extern void  func_2912E0(Obj *p);
extern void  func_290390(Obj *p, void *b, s32 c);
extern void  func_2901D0(Obj *p, void *b, s32 c, s32 d);
extern void  func_290450(Obj *p);
extern void  func_291110(Obj *p, s32 b, s32 c, s32 d);
extern void  func_290F60(Obj *p, s32 b, s32 c, s32 d);
extern void  func_290010(Obj *p, s32 b, s32 c, s32 d);
extern void *func_28AA30(void *a, s32 b);
extern void  func_28F510(Obj *p, s32 b, void *c, s32 d);
extern void  normal_SpaceMenuPanelsLayout_514270(Obj *p);
extern void  normal_SpaceMenuMapBuild_5135f0(Obj *p);
extern void  normal_SpaceMenuSelectionRefresh_512a70(Obj *p);
extern void  normal_SpaceMenuOpenAnimStart_512e20(Obj *p);

s32 normal_SpaceMenuBuild_514560(Obj *p)
{
    Rec *r;
    void *t;
    s32 n;

    r = func_42C500(func_206A40(), 0xE);
    t = r->f04;
    n = r->fA_hi;
    func_2912E0(p);
    func_290390(p, D_004846B0, n);
    func_2901D0(p, t, 0, 0);
    p->f08 = 0x32D;
    func_290450(p);
    func_291110(p, 2, 1, 1);
    func_290F60(p, 2, 0, 0);
    func_291110(p, 0x27, 1, 1);
    func_290F60(p, 0x27, 0, 0);
    func_290010(p, 0x20, 1, -1);
    func_290F60(p, 0x20, 0, 0);
    func_28F510(p, 0x21, func_28AA30(D_00481BBC, 0x57), 0);
    normal_SpaceMenuPanelsLayout_514270(p);
    normal_SpaceMenuMapBuild_5135f0(p);
    normal_SpaceMenuSelectionRefresh_512a70(p);
    normal_SpaceMenuOpenAnimStart_512e20(p);
    p->f14 = 1;
    return 0;
}
