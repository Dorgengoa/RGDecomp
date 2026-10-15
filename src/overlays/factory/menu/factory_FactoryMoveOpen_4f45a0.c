#include "types.h"

/* factory.bin overlay, 0x004F45A0 -- open the blueprint confirm prompt.  508
 * bytes, 128 instructions, 3 conditional branches, 22 calls (br/ins 0.023):
 * the branch-light band, and close to straight transcription.
 *
 * ★ The LAST struct store (`sty.f1C = 0xB`) fills func_28D0C0's delay slot and
 * `o->f5C = 0;` follows the call -- writing it before the call instead swaps
 * those two words, at the right length.
 *
 * D_00484A70 is _gp - 0x700 and stays plain.
 */

typedef struct Sty {
    s32 f00;
    s32 f04;
    u8  pad08[0x8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Sty;                                          /* 0x34 */

typedef struct Game { u8 pad000[0x2D0]; s32 f2D0; } Game;
typedef struct Job  { s32 f00; } Job;

typedef struct Panel {
    u8    pad00[0x5C];
    u8    f5C;
    u8    pad5D[0x3];
    void *f60;
    u8    pad64[0xC];
    u8    f70;
} Panel;

extern void *D_00484A70;                        /* _gp - 0x700 */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(Sty *s, s32 a, s32 b, s32 c);
extern void  func_28F510(void *w, u16 id, void *p, s32 k);
extern s32   func_28F620(void *w, u16 id, s32 k);
extern s32   func_28FE10(void *w, u16 id, s32 k);
extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_2907A0(void *w, u16 id, f32 v);
extern void  func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern Game *func_367F30(void);
extern Job  *func_367EC0(void);

void factory_FactoryMoveOpen_4f45a0(Panel *o)
{
    Sty   sty;
    Game *h;
    Job  *job;

    func_290BD0(o->f60, 0x4E, 0x200, 1, 0, 0);
    func_28F510(o->f60, 0x4E, func_28AA30(D_00484A70, 0x18), 0);
    func_28F510(o->f60, 0x4E, func_28AA30(D_00484A70, 8), 1);
    func_28F510(o->f60, 0x4E, func_28AA30(D_00484A70, 6), 2);
    func_28F510(o->f60, 0x4E, func_28AA30(D_00484A70, 7), 3);
    h = func_367F30();
    if (h == 0) {
        return;
    }
    job = func_367EC0();
    if (job == 0) {
        return;
    }
    job->f00 = 6;
    h->f2D0 = h->f2D0 & ~1;
    func_290010(o->f60, 0x4F, 1, -1);
    func_2907A0(o->f60, 0x4F, 0.0f);
    if (o->f70 == 0) {
        func_290010(o->f60, 0x4E, 1, -1);
    } else {
        func_290010(o->f60, 0x4E, 0, -1);
    }
    func_2907A0(o->f60, 0x51, 0.0f);
    func_28F510(o->f60, 0x51, func_28AA30(D_00484A70, 0xA0), 0);
    func_131B60(&sty, 0, 0x34);
    sty.f00 = func_28FE10(o->f60, 0x51, 0);
    sty.f04 = func_28F620(o->f60, 0x51, 0);
    sty.f10 = 0x1E;
    sty.f14 = 0x13;
    sty.f18 = 0xF;
    sty.f1C = 0xB;
    func_28D0C0(&sty, 0, 0, 0);
    o->f5C = 0;
}
