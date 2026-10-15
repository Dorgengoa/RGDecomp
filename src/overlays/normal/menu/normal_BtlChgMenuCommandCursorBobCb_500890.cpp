#include "types.h"
/* normal 0x00500890 -- the two-arrow scroller frame.  It runs the 0x14/0x107
 * background updater, reads the page mode out of func_3C2010 and animates the
 * 0x31/0x32 arrows off one shared sine (func_128FD0 of the frame counter over
 * 30), then raises or lowers each arrow according to the mode and the panel's
 * 0x10 index.  Last it clears the 0x44E "needs refresh" flag if the context's
 * live entity says so through virtual slot 45 ((0xBC-8)/4).
 *
 * ONE VIRTUAL call, so the unit is .cpp -- a struct of function pointers gives
 * `jalr $v0`, only a real C++ `virtual` gives `jalr $t9`.
 * `$5` is never written before normal_BtlChgMenuCursorBob_503750, so parameter 2 passes
 * straight through as that call's second argument.
 * `adda.s`/`madd.s` is plain `K + C * t`; the two arrow positions differ only
 * in their two constants.
 * `mov.s $f20,$f0` sits in normal_BtlChgMenuCommandRowsRefresh_501640's DELAY SLOT and captures
 * func_128FD0's result, i.e. the statement BEFORE that call. */

typedef struct Panel { u8 pad00[0x10]; s16 f10; } Panel;
typedef struct Ctx   { u8 pad00[0x44E]; s16 f44E; } Ctx;
typedef struct Own   { u8 pad00[0x18]; s32 f18; } Own;

struct Ent {
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
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual s32 kind();               /* slot 45 -> vtable +0xBC */
};

extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" s32   D_004844D8;      /* gp - 0xC98  */
extern "C" f32   D_0047D1FC;      /* gp - 0x7F74 */

extern "C" f32   func_128FD0(f32 a);
extern "C" Own  *func_1FEDE0(void);
extern "C" void  func_2907A0(void *p, u16 id, f32 a);
extern "C" void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern "C" void  func_291110(void *p, u16 id, s32 c, s32 d);
extern "C" s32   func_3C2010(s32 a, s32 b, s32 c);
extern "C" Ent  *func_3C2820(s32 a);
extern "C" void  normal_BtlChgMenuCommandRowsRefresh_501640(void);
extern "C" void  normal_BtlChgMenuStatusIconsUpdate_501a70(s16 a);
extern "C" void  normal_BtlChgMenuSetMemberFace_501d40(s32 a, s16 b);
extern "C" void  normal_BtlChgMenuCursorBob_503750(Panel *a, s32 b, s32 c, s32 d);
extern "C" void  normal_BtlChgPageGetScrollStep_505d70(Ctx *p);

extern "C" s32 normal_BtlChgMenuCommandCursorBobCb_500890(Panel *a, s32 b);

s32 normal_BtlChgMenuCommandCursorBobCb_500890(Panel *a, s32 b)
{
    Own *o;
    Ent *e;
    s32  mode;
    s32  k;
    f32  t;

    normal_BtlChgMenuCursorBob_503750(a, b, 0x14, 0x107);
    o = func_1FEDE0();
    if (o == 0) {
        return 0;
    }
    mode = func_3C2010(o->f18, 1, 1);
    t = func_128FD0(D_0047D1FC * (f32)D_004844D8 / 30.0f);
    normal_BtlChgMenuCommandRowsRefresh_501640();
    D_004844D8 = D_004844D8 + 1;
    if (D_004844D8 >= 0x1E) {
        D_004844D8 = 0;
    }
    func_290F60(D_0048449C, 0x31, (s32)(-78.0f + -6.0f * t), 0x17);
    func_290F60(D_0048449C, 0x32, (s32)(48.0f + 6.0f * t), 0x17);
    func_2907A0(D_0048449C, 0x31, t);
    func_2907A0(D_0048449C, 0x32, t);
    normal_BtlChgMenuSetMemberFace_501d40(0x30, a->f10);
    if (mode == 1) {
        func_291110(D_0048449C, 0x31, 0, 1);
        func_291110(D_0048449C, 0x32, 0, 1);
    } else if (mode == 2) {
        if (a->f10 == 0) {
            func_291110(D_0048449C, 0x31, 0, 1);
            func_291110(D_0048449C, 0x32, 1, 1);
        } else {
            func_291110(D_0048449C, 0x31, 1, 1);
            func_291110(D_0048449C, 0x32, 0, 1);
        }
    } else if (mode == 3) {
        k = a->f10;
        if (k == 0) {
            func_291110(D_0048449C, 0x31, 0, 1);
            func_291110(D_0048449C, 0x32, 1, 1);
        } else if (k == 1) {
            func_291110(D_0048449C, 0x31, 1, 1);
            func_291110(D_0048449C, 0x32, 1, 1);
        } else {
            func_291110(D_0048449C, 0x31, 1, 1);
            func_291110(D_0048449C, 0x32, 0, 1);
        }
    }
    normal_BtlChgMenuStatusIconsUpdate_501a70(a->f10);
    if (D_00484454->f44E != 0) {
        e = func_3C2820(o->f18);
        if (e != 0 && e->kind() != 0) {
            D_00484454->f44E = 0;
        }
    }
    normal_BtlChgPageGetScrollStep_505d70(D_00484454);
    return 1;
}
