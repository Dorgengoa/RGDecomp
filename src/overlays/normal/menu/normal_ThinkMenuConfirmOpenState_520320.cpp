#include "types.h"
/* normal 0x00520320 -- the shop/talk portrait panel's one-shot build: the
 * 0x753C frame, three 0x753F sub-images taken out of D_00481BBC, the actor
 * model spawned through func_3C86E0 and pointed at the 0x753F widget, then the
 * four 0x753F corner offsets.  The tail runs on EVERY call.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`, and the function returns 1.
 * One VIRTUAL call (`lw $25,0($2) / lw $25,0x4C($25) / jalr $25`), so this unit
 * is .cpp: a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08, so
 * 0x4C is index (0x4C-8)/4 = 17; the placeholder list is expanded by
 * build/n_gen520320.py from that OFFSET so the index cannot drift.
 *
 * `w = func_28F620(...)` is captured in func_1FEDE0's DELAY SLOT, which reads
 * as the wrong call's result -- the two calls are consecutive statements.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is mwcc SHARING the constant between
 * arguments 3 and 4, not two source constants. */

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
    virtual void attach(void *p);  /* slot 17 -> vtable +0x4C */
};

typedef struct Hdl  { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[0x14 - 8];
                      s16 f14; s16 f16; } Hdl;
typedef struct Wgt  { u8 pad00[4]; void *f04; } Wgt;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Sess { u8 pad00[0x11]; s8 f11; } Sess;

extern const u8 D_00528030;

extern "C" f32    D_0047DADC;     /* gp - 0x7694 */
extern "C" void  *D_00481BBC;     /* gp - 0x35B4 */
extern "C" void  *D_00484920;     /* gp - 0x850  */
extern "C" s32    D_00484928;     /* gp - 0x848  */
extern "C" Sess  *D_00484934;     /* gp - 0x83C  */
extern "C" s32    D_00484944;     /* gp - 0x82C  */

extern "C" Ctx         *func_1FEDE0(void);
extern "C" f32          func_1CEBA0(s32 a);
extern "C" s32          func_1F5BE0(void);
extern "C" const void  *func_28AA30(void *a, s32 id);
extern "C" Hdl         *func_28EA40(const u8 *a, s32 id);
extern "C" void         func_28EDE0(void *a, s32 id, s32 c);
extern "C" void         func_28F300(void *a, u16 id, s32 c, s32 d);
extern "C" void         func_28F510(void *a, u16 id, const void *p, s32 d);
extern "C" Wgt         *func_28F620(void *a, u16 id, s32 c);
extern "C" void         func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern "C" void         func_290F60(void *a, u16 id, s32 x, s32 y);
extern "C" void         func_291110(void *a, u16 id, s32 c, s32 d);
extern "C" Ent         *func_3C86E0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern "C" void         normal_ThinkMenuPromptScrollStep_521660(f32 x);

extern "C" s32 normal_ThinkMenuConfirmOpenState_520320(void *a, s32 b);

s32 normal_ThinkMenuConfirmOpenState_520320(void *a, s32 b)
{
    Wgt *w;
    Ctx *c;
    Hdl *h;
    Ent *o;

    if (b != 0) {
        func_291110(D_00484920, 0x753C, 1, 1);
        func_290F60(D_00484920, 0x753C, 0x92, 0xA2);
        func_290690(D_00484920, 0x753C, 1.0f, D_0047DADC, 0.0f);
        func_28F510(D_00484920, 0x753F, func_28AA30(D_00481BBC, 0x56), 1);
        func_28F510(D_00484920, 0x753F, func_28AA30(D_00481BBC, 0x52), 2);
        func_28F510(D_00484920, 0x753F, func_28AA30(D_00481BBC, 0x53), 3);
        w = func_28F620(D_00484920, 0x753F, 0);
        c = func_1FEDE0();
        h = func_28EA40(&D_00528030, 0x7531);
        o = func_3C86E0(c->f18, 0, D_00484934->f11, h->f14, h->f16, 0);
        if (o != 0 && w != 0) {
            o->attach(w->f04);
        }
        h = func_28EA40(&D_00528030, 0x7532);
        func_290F60(D_00484920, 0x7543, h->f04, h->f06);
        func_28F300(D_00484920, 0x753F, 0x7B, 0);
        func_28F300(D_00484920, 0x753F, 0x7B, 1);
        func_28F300(D_00484920, 0x753F, 0x50, 2);
        func_28F300(D_00484920, 0x753F, 0xA0, 3);
        D_00484944 = 0;
    }
    normal_ThinkMenuPromptScrollStep_521660(func_1CEBA0(func_1F5BE0()));
    func_28EDE0(&D_00484928, 0x7535, 0);
    return 1;
}
