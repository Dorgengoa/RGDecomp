#include "types.h"
/* factory.bin overlay, 0x004F4130 -- rebuild the recipe-detail panel for the
 * currently selected blueprint.  688 bytes, 172 instructions, 8 conditional
 * branches, 26 calls (br/ins 0.047): the branch-light band.
 *
 * A near-twin of factory_FactoryRemoveShowPartInfo_4fc620 (0.988 by mnemonic sequence) and a close
 * relative of the already-matched factory_FactoryPartsSelect_4f02c0, whose tail -- the
 * 0xAC scratch record, the func_28A9A0 fill and the two func_134690 icon
 * appends -- is the same code.
 *
 * Relocation notes: D_0050CBD0 and D_0050FEB0 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so they are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_00484A70 (_gp - 0x700) is inside
 * the window and stays plain.
 *
 * The call at 0x004F41DC is `lw $25,0($4) / lw $25,0x70($25) / jalr $25`.  A
 * struct of function pointers gives `jalr $v0`; only a real C++ `virtual`
 * gives `jalr $t9`, so this unit is .cpp for that one call.  mwcc puts the
 * first virtual at vtable slot +0x08, so slot 0x70 is index (0x70-8)/4 = 26 --
 * 26 placeholders, then the real one.  The class is never constructed here, so
 * no vtable is emitted into the object.
 *
 * ★ `factory_FactoryPartGroupToMsgId_4f4000` is declared `s16` HERE and defined `s32` in its own
 * unit: retail truncates its result at this call site (`dsll32/dsra32`) and
 * then re-extends it for func_28AA30's s16 parameter.  Same pair as
 * factory_FactoryPartGroupToMsgId_4ef9f0 in factory_FactoryPartsSelect_4f02c0.
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

typedef struct Res { u8 pad00[0xC]; void *f0C; } Res;

typedef struct Group { u8 pad00[0x6]; s16 f06; } Group;

typedef struct Game { u8 pad000[0x2E8]; s16 f2E8; } Game;

typedef struct Bank { u8 pad00[0x8]; void *f08; } Bank;
typedef struct Zone { u8 pad00[0x40]; Bank *f40; } Zone;
typedef struct Ctx  { u8 pad00[0x8]; Zone *f08; } Ctx;

typedef struct Buf { s32 f00; u8 pad04[0xA8]; } Buf;    /* 0xAC */

typedef struct Panel { u8 pad00[0x60]; void *f60; } Panel;

extern "C" void *D_00484A70;                    /* _gp - 0x700 */
extern "C" u8 D_0050CBD0[];
extern "C" u8 D_0050FEB0[];

extern "C" s32    factory_FactoryPartGroupToItemId_4f4070(Panel *o, s32 slot);
extern "C" s16    factory_FactoryPartGroupToMsgId_4f4000(Panel *o, s32 slot);
extern "C" s32    factory_FactoryPartGroupUnderCursor_4ffa90(Game *h, u8 *out);
extern "C" Group *factory_FactoryPartGroupFindById_504080(Game *h, s32 k);
extern "C" void   func_131B60(void *p, s32 v, s32 n);
extern "C" void   func_134690(void *p, void *s);
extern "C" void   func_28A9A0(void *p, void *s, void *a, s32 n);
extern "C" void   func_28AA00(void *p);
extern "C" void  *func_28AA30(void *bank, s16 id);
extern "C" void   func_28F510(void *w, u16 id, void *p, s32 k);
extern "C" void   func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern "C" void   func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern "C" Game  *func_367F30(void);
extern "C" Ctx   *func_1FEDE0(void);

extern "C" void factory_FactoryMoveShowPartInfo_4f4130(Panel *o);

void factory_FactoryMoveShowPartInfo_4f4130(Panel *o)
{
    Buf    buf;
    u8     c;
    Game  *h;
    Ctx   *w;
    Tex   *tex;
    Res   *res;
    Group *g;
    s32    i;
    s32    id;
    s32    n;
    s32    k;

    func_290690(o->f60, 0x4F, 0.0f, -0.125f, -1.0f);
    h = func_367F30();
    if (h == 0) {
        return;
    }
    c = 0;
    i = h->f2E8;
    if (i < 0) {
        i = factory_FactoryPartGroupUnderCursor_4ffa90(h, &c);
    }
    if (i < 0) {
        return;
    }
    id = factory_FactoryPartGroupToItemId_4f4070(o, i);
    w = func_1FEDE0();
    if (w == 0) {
        return;
    }
    tex = (Tex *)w->f08->f40->f08;
    res = (Res *)tex->pick(id);
    if (res == 0) {
        return;
    }
    func_290690(o->f60, 0x4F, 1.0f, 0.125f, -1.0f);
    if (c != 0) {
        func_28F670(o->f60, 0x50, 0, 0, 0, 0, 0);
        func_28F670(o->f60, 0x50, 0x2A, 0x1A, 0x2A, 0x1A, 1);
    } else {
        func_28F670(o->f60, 0x50, 0x2A, 0x1A, 0x2A, 0x1A, 0);
        func_28F670(o->f60, 0x50, 0, 0, 0, 0, 1);
    }
    func_131B60(D_0050FEB0, 0, 0x20);
    func_28F510(o->f60, 0x4F, D_0050CBD0, 0);
    func_28F510(o->f60, 0x4F, D_0050CBD0, 1);
    g = factory_FactoryPartGroupFindById_504080(h, i);
    n = 0;
    if (g != 0) {
        n = g->f06;
    }
    func_28AA00(&buf);
    func_131B60(&buf, 0, 0xAC);
    buf.f00 = n;
    func_28A9A0(D_0050FEB0, func_28AA30(D_00484A70, 0x1C), &buf, 1);
    k = factory_FactoryPartGroupToMsgId_4f4000(o, i);
    if (k > 0) {
        func_134690(D_0050FEB0, func_28AA30(D_00484A70, 0x78));
        func_134690(D_0050FEB0, func_28AA30(D_00484A70, k));
    }
    func_28F510(o->f60, 0x4F, res->f0C, 0);
    func_28F510(o->f60, 0x4F, D_0050FEB0, 1);
}
