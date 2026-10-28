/* rgp:protos */
#line 1
#include "types.h"
/* factory.bin overlay, 0x004FC620 -- rebuild the recipe-detail panel for the
 * currently selected blueprint.  672 bytes, 168 instructions, 7 conditional
 * branches, 26 calls (br/ins 0.042): the branch-light band.
 *
 * A near-twin of factory_FactoryMoveShowPartInfo_4f4130 (0.988 by mnemonic sequence) and a close
 * relative of the already-matched factory_FactoryPartsSelect_4f02c0, whose tail -- the
 * 0xAC scratch record, the func_28A9A0 fill and the two func_134690 icon
 * appends -- is the same code.
 *
 * Relocation notes: factory_D_0050CDF0 and factory_D_0050FFF0 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so they are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_00484A70 (_gp - 0x700) is inside
 * the window and stays plain.
 *
 * The call at 0x004FC6D4 is `lw $25,0($4) / lw $25,0x70($25) / jalr $25`.  A
 * struct of function pointers gives `jalr $v0`; only a real C++ `virtual`
 * gives `jalr $t9`, so this unit is .cpp for that one call.  mwcc puts the
 * first virtual at vtable slot +0x08, so slot 0x70 is index (0x70-8)/4 = 26 --
 * 26 placeholders, then the real one.  The class is never constructed here, so
 * no vtable is emitted into the object.
 *
 * ★ `factory_FactoryPartGroupToMsgId_4fc4f0` is declared `s16` HERE and defined `s32` in its own
 * unit: retail truncates its result at this call site (`dsll32/dsra32`) and
 * then re-extends it for func_28AA30's s16 parameter.  Same pair as
 * factory_FactoryPartGroupToMsgId_4ef9f0 in factory_FactoryPartsSelect_4f02c0.
 */

struct Tex {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * pick(s16 id) { return VCM(void *, (void *, s16), 0x70, id); }
};

typedef struct Res { u8 pad00[0xC]; void *f0C; } Res;

typedef struct Group { u8 pad00[0x6]; s16 f06; } Group;

typedef struct Game { u8 pad000[0x2E8]; } Game;

typedef struct Bank { u8 pad00[0x8]; void *f08; } Bank;
typedef struct Zone { u8 pad00[0x40]; Bank *f40; } Zone;
typedef struct Ctx  { u8 pad00[0x8]; Zone *f08; } Ctx;

typedef struct Buf { s32 f00; u8 pad04[0xA8]; } Buf;    /* 0xAC */

typedef struct Panel { u8 pad00[0x68]; void *f68; } Panel;

extern "C" void *D_00484A70;                    /* _gp - 0x700 */
extern "C" u8 factory_D_0050CDF0[];
extern "C" u8 factory_D_0050FFF0[];

extern "C" s32    factory_FactoryPartGroupToItemId_4fc560(Panel *o, s32 slot);
extern "C" s16    factory_FactoryPartGroupToMsgId_4fc4f0(Panel *o, s32 slot);
extern "C" s32    factory_FactoryPartGroupUnderCursor_4ffa90(Game *h, u8 *out);
extern "C" Group *factory_FactoryPartGroupFindById_504080(Game *h, s32 k);
extern "C" void   memset(void *p, s32 v, s32 n);
extern "C" void   strcat(void *p, void *s);
extern "C" void   MsgFormat_28a9a0(void *p, void *s, void *a, s32 n);
extern "C" void   MsgFormatParamsCtor_28aa00(void *p);
extern "C" void  *MsgTableLookup_28aa30(void *bank, s16 id);
extern "C" void   UiSetTextString_28f510(void *w, u16 id, void *p, s32 k);
extern "C" void   UiSetSpriteSizeUvSize_28f670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern "C" void   UiFadeWidgetAlpha_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern "C" Game  *GetFactoryObj_367f30(void);
extern "C" Ctx   *GetGameData_1fede0(void);

extern "C" void factory_FactoryRemoveShowPartInfo_4fc620(Panel *o);

void factory_FactoryRemoveShowPartInfo_4fc620(Panel *o)
{
    Buf    buf __attribute__((aligned(16)));
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

    UiFadeWidgetAlpha_290690(o->f68, 0x56, 0.0f, -0.125f, -1.0f);
    h = GetFactoryObj_367f30();
    if (h == 0) {
        return;
    }
    i = factory_FactoryPartGroupUnderCursor_4ffa90(h, &c);
    if (i < 0) {
        return;
    }
    id = factory_FactoryPartGroupToItemId_4fc560(o, i);
    w = GetGameData_1fede0();
    if (w == 0) {
        return;
    }
    tex = (Tex *)w->f08->f40->f08;
    res = (Res *)tex->pick(id);
    if (res == 0) {
        return;
    }
    UiFadeWidgetAlpha_290690(o->f68, 0x56, 1.0f, 0.125f, -1.0f);
    if (c != 0) {
        UiSetSpriteSizeUvSize_28f670(o->f68, 0x57, 0, 0, 0, 0, 0);
        UiSetSpriteSizeUvSize_28f670(o->f68, 0x57, 0x2A, 0x1A, 0x2A, 0x1A, 1);
    } else {
        UiSetSpriteSizeUvSize_28f670(o->f68, 0x57, 0x2A, 0x1A, 0x2A, 0x1A, 0);
        UiSetSpriteSizeUvSize_28f670(o->f68, 0x57, 0, 0, 0, 0, 1);
    }
    memset(factory_D_0050FFF0, 0, 0x20);
    UiSetTextString_28f510(o->f68, 0x56, factory_D_0050CDF0, 0);
    UiSetTextString_28f510(o->f68, 0x56, factory_D_0050CDF0, 1);
    g = factory_FactoryPartGroupFindById_504080(h, i);
    n = 0;
    if (g != 0) {
        n = g->f06;
    }
    MsgFormatParamsCtor_28aa00(&buf);
    memset(&buf, 0, 0xAC);
    buf.f00 = n;
    MsgFormat_28a9a0(factory_D_0050FFF0, MsgTableLookup_28aa30(D_00484A70, 0x1C), &buf, 1);
    k = factory_FactoryPartGroupToMsgId_4fc4f0(o, i);
    if (k > 0) {
        strcat(factory_D_0050FFF0, MsgTableLookup_28aa30(D_00484A70, 0x78));
        strcat(factory_D_0050FFF0, MsgTableLookup_28aa30(D_00484A70, k));
    }
    UiSetTextString_28f510(o->f68, 0x56, res->f0C, 0);
    UiSetTextString_28f510(o->f68, 0x56, factory_D_0050FFF0, 1);
}
