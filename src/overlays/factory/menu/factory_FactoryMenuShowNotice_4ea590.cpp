#include "types.h"
/* factory.bin overlay, 0x004EA590 -- open the factory HUD banner for one
 * message kind.  732 bytes, 184 instructions, 7 conditional branches, 28
 * calls (br/ins 0.038): the branch-light band.
 *
 * Relocation notes: D_0050CA00 and D_0050FDB0 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so both are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_004807E4 (_gp - 0x498C),
 * D_00484A70 (_gp - 0x700) and D_00484A84 (_gp - 0x6EC) are inside the window
 * and stay plain.
 *
 * The call at 0x004EA65C is `lw $25,0($4) / lw $25,0x70($25) / jalr $25`, so
 * this unit is .cpp: only a real C++ `virtual` gives `jalr $t9`.  Slot 0x70 is
 * index (0x70-8)/4 = 26 -- 26 placeholders, then the real one.  Same class as
 * factory_FactoryMoveShowPartInfo_4f4130.
 *
 * ★ ONE gp load into a callee-saved register, not one per use
 * ([[factory-count-the-gp-loads]]): `lw $16, -0x498C($28)` appears once and
 * every later site is `daddu $4, $16, $0`, so D_004807E4 is a NAMED LOCAL.
 *
 * ★ The style record is filled in ASCENDING FIELD-OFFSET order, and the last
 * store lands in func_28F3D0's delay slot because it is written before the
 * call.
 *
 * ★ `bgez / sra 1` twice is a signed `/ 2`, not a shift.
 *
 * ★★ THE ONE-CASE `switch`.  The 0x4189 arm is `beql $3,$2` carrying its own
 * store `addiu $17, $0, 0x4189` in the delay slot.  A plain `if (t == 4)`
 * gives `bne` + `b` with the store in the `b`'s slot -- three words wrong at
 * the right length.  [[overlay-c-pipeline]]'s discriminator decides it: a
 * SWITCH's converted branch carries a CASE BODY'S STORE, a chain's carries the
 * NEXT GUARD'S CONSTANT.  Eight spellings in one probe build; `if`, `else if`,
 * a ternary, two `goto` forms and a three-arm `switch` are all 3 bad or the
 * wrong length, and only the ONE-CASE switch nested in the `else` is exact.
 */

struct Tex {
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
    virtual void *pick(s16 id);
};

typedef struct Res { s16 f00; } Res;

typedef struct Buf {
    u8  pad00[0xC];
    s32 f0C;
    u8  pad10[0x9C];
} Buf;                                          /* 0xAC */

typedef struct Sty {
    s32 f00;
    s32 f04;
    s32 f08;
    u8  pad0C[0x4];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x10];
    s16 f30;
    u8  pad32[0x2];
} Sty;                                          /* 0x34 */

typedef struct Job { u8 pad00[0x8]; s32 f08; } Job;

typedef struct Bank { u8 pad00[0x8]; void *f08; } Bank;
typedef struct Zone { u8 pad00[0x40]; Bank *f40; } Zone;
typedef struct Ctx  { u8 pad00[0x8]; Zone *f08; } Ctx;

extern "C" void *D_004807E4;                    /* _gp - 0x498C */
extern "C" void *D_00484A70;                    /* _gp - 0x700  */
extern "C" u8    D_00484A84;                    /* _gp - 0x6EC  */
extern "C" u8 D_0050CA00[];
extern "C" u8 D_0050FDB0[];

extern "C" void  factory_FactoryMenuBannerSetStyle_4eae00(s32 on);
extern "C" void  func_131B60(void *p, s32 v, s32 n);
extern "C" void  func_28A9A0(void *p, void *s, void *a, s32 n);
extern "C" void  func_28AA00(void *p);
extern "C" void *func_28AA30(void *bank, s32 id);
extern "C" void  func_28D0C0(Sty *s, s32 a, s32 b, s32 c);
extern "C" s32   func_28F3D0(void *w, u16 id, s32 k);
extern "C" void  func_28F510(void *w, u16 id, void *p, s32 k);
extern "C" s32   func_28F620(void *w, u16 id, s32 k);
extern "C" void  func_28FD10(void *w, u16 id, s32 a, s32 b, s32 c);
extern "C" s32   func_28FE10(void *w, u16 id, s32 k);
extern "C" void  func_290010(void *w, u16 id, s32 a, s32 b);
extern "C" void  func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern "C" void  func_291110(void *w, u16 id, s32 a, s32 b);
extern "C" Job  *func_367EC0(void);
extern "C" Ctx  *func_1FEDE0(void);
extern "C" void *func_15DE80(void);
extern "C" s32   func_1451D0(void *h);

extern "C" void factory_FactoryMenuShowNotice_4ea590(s32 kind);

void factory_FactoryMenuShowNotice_4ea590(s32 kind)
{
    Buf   buf;
    Sty   sty;
    void *w;
    Tex  *tex;
    Res  *res;
    Ctx  *ctx;
    s32   id;
    s32   n;
    s32   t;

    factory_FactoryMenuBannerSetStyle_4eae00(0);
    w = D_004807E4;
    func_28F510(w, 0x1A, D_0050CA00, 0);
    if (kind == 0xAA) {
        func_28AA00(&buf);
        func_131B60(&buf, 0, 0xAC);
        func_131B60(D_0050FDB0, 0, 0x20);
        t = func_367EC0()->f08;
        id = -1;
        if (t != 2) {
            switch (t) {
            case 4:
                id = 0x4189;
                break;
            }
        } else {
            id = 0x418F;
        }
        ctx = func_1FEDE0();
        if (ctx == 0) {
            return;
        }
        tex = (Tex *)ctx->f08->f40->f08;
        res = (Res *)tex->pick(id);
        if (res == 0) {
            return;
        }
        buf.f0C = res->f00;
        func_28A9A0(D_0050FDB0, func_28AA30(D_00484A70, kind), &buf, 1);
        func_28F510(w, 0x1A, D_0050FDB0, 0);
    } else {
        func_28F510(w, 0x1A, func_28AA30(D_00484A70, kind), 0);
    }
    func_28F510(w, 0x1A, D_0050CA00, 1);
    func_28F510(w, 0x1A, D_0050CA00, 2);
    func_131B60(&sty, 0, 0x34);
    sty.f00 = func_28FE10(w, 0x1A, 0);
    sty.f04 = func_28F620(w, 0x1A, 0);
    sty.f08 = 0xAA;
    sty.f10 = 0x3B;
    sty.f14 = 0x13;
    sty.f18 = 0x29;
    sty.f1C = 0xB;
    sty.f30 = 1;
    n = func_28F3D0(w, 0x1A, 0) + 0x13;
    func_28FD10(w, 0x1B, 0xB9, func_1451D0(func_15DE80()) / 2 - n / 2 + 8, 0);
    func_28D0C0(&sty, 0, 0, 0);
    D_00484A84 = 0;
    func_290010(w, 0x1A, 1, -1);
    func_291110(w, 0x1B, 1, 1);
    func_291110(w, 0x1C, 0, 1);
    func_291110(w, 0x1D, 0, 1);
    func_290690(w, 0x1A, 1.0f, 0.125f, -1.0f);
}
