/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndInit_4ee600 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EE600 -- the gameplay HUD allocator/initialiser.  832 bytes.
 *
 * Six gp pointer globals hold arrays whose ELEMENT STRIDE is what the shifts
 * say: 0x100 (i << 8), 0x80 (i << 7) and 0x40 (i << 6).  The widget ids are
 * masked with `andi ..., 0xFFFF` at every call, which names the callee's
 * parameter type as u16.
 *
 * `p->f108` is assigned from a local rather than re-read: retail passes
 * func_100710's own `$2` straight on to func_131B60. */
typedef struct S100 { u8 pad000[0xE0]; s16 f0E0; u8 pad0E2[0x100 - 0xE2]; } S100;
typedef struct S80  { u8 pad000[0x60]; s16 f060; u8 pad062[0x80 - 0x62]; } S80;
typedef struct S40  { u8 pad000[0x20]; s16 f020; u8 pad022[0x40 - 0x22]; } S40;
typedef struct S20  { u8 pad000[0x10]; s16 f010; u8 pad012[0x20 - 0x12]; } S20;

typedef struct Obj {
    s32  f000;
    u8   pad004[0x14 - 0x04];
    u8   f014;
    u8   pad015[0x1C - 0x15];
    s32  f01C;
    u8   pad020[0x28 - 0x20];
    s32  f028;
    void *f02C;
    u8   pad030[0xEC - 0x30];
    void *f0EC;
    u8   pad0F0[0x102 - 0xF0];
    s16  f102;
    s16  f104;
    s16  f106;
    S20 *f108;
    u8   pad10C[0x10E - 0x10C];
    s16  f10E;
    s8   f110;
    s8   f111;
    s8   f112;
    s8   f113;
} Obj;

typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;

/* rgp text-alias: UiTextElemInit_2931a0 is the C function */
extern void  *D_004843E0;
extern S100  *D_004843C8;
extern S80   *D_004843CC;
extern S40   *D_004843D0;
extern S40   *D_004843D4;
extern S40   *D_004843D8;
extern S40   *D_004843DC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memset(void *a, s32 b, s32 c);
/*rgp*/
/*rgp*/

void normal_MenuBattleEndInit_4ee600(Obj *p, void *heap)
{
    s32 id;
    Rec *r;
    void *t;
    s32 n;
    s32 i;
    s32 j;
    s32 k;

    D_004843E0 = SceneSoundGetSlot0HandleCur_207df0();
    r = ((Rec *)ResGroupListFindById_42c500(GetMenuResGroup_206a40(), 0xF));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(&p->f014);
    UiInitWidgetPool_290390(&p->f014, heap, n);
    UiAddWidgets_2901d0(&p->f014, t, 0);
    p->f01C = 0x32D;
    UiTextStyleReset_290450();
    p->f028 = 9;
    p->f02C = MemStackNew_14e1b0(0x1D4, heap);
    p->f0EC = MemStackNew_14e1b0(0x60, heap);
    t = ConstructNewArray_100710(MemStackNew_14e1b0(0x90, heap), UiTextElemInit_2931a0, 0, 0x10, 8);
    p->f108 = t;
    memset(t, 0, 0x80);
    for (i = 0; i < 4; i++) {
        p->f108[i].f010 = -1;
    }
    p->f000 = -1;
    p->f110 = 0;
    p->f104 = 0;
    p->f111 = 0;
    p->f106 = 0;
    p->f112 = 0;
    p->f10E = 0;
    p->f113 = 0;
    p->f102 = 0;
    D_004843C8 = MemStackNew_14e1b0(0x800, heap);
    D_004843CC = MemStackNew_14e1b0(0x400, heap);
    D_004843D0 = MemStackNew_14e1b0(0x200, heap);
    D_004843D4 = MemStackNew_14e1b0(0x200, heap);
    D_004843D8 = MemStackNew_14e1b0(0x100, heap);
    D_004843DC = MemStackNew_14e1b0(0x100, heap);
    memset(D_004843C8, 0, 0x800);
    memset(D_004843CC, 0, 0x400);
    memset(D_004843D0, 0, 0x200);
    memset(D_004843D4, 0, 0x200);
    memset(D_004843D8, 0, 0x100);
    memset(D_004843DC, 0, 0x100);
    for (i = 0; i < 8; i++) {
        k = i * 3;
        D_004843C8[i].f0E0 = -1;
        D_004843CC[i].f060 = -1;
        D_004843D0[i].f020 = -1;
        D_004843D4[i].f020 = -1;
        id = k + 0x15;
        UiSetWidgetSprites_290b90(&p->f014, id, &D_004843C8[i]);
        UiSetWidgetSubItems_28eec0(&p->f014, id, &D_004843CC[i]);
        UiSetWidgetSubItems_28eec0(&p->f014, k + 0x17, &D_004843D0[i]);
        UiSetWidgetSprites_290b90(&p->f014, k + 0x16, &D_004843D4[i]);
    }
    for (j = 0; j < 4; j++) {
        k = j * 3;
        D_004843D8[j].f020 = -1;
        D_004843DC[j].f020 = -1;
        UiSetWidgetSprites_290b90(&p->f014, k + 3, &D_004843D8[j]);
        UiSetWidgetSprites_290b90(&p->f014, k + 5, &D_004843DC[j]);
    }
}
