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
    u16   fA_lo : 2;
    u16   fA_hi : 14;
} Rec;

extern const u8 D_002931A0[];
extern void  *D_004843E0;
extern S100  *D_004843C8;
extern S80   *D_004843CC;
extern S40   *D_004843D0;
extern S40   *D_004843D4;
extern S40   *D_004843D8;
extern S40   *D_004843DC;

extern void *func_207DF0(void);
extern void *func_206A40(void);
extern Rec  *func_42C500(void *a, s32 b);
extern void  func_2912E0(void *a);
extern void  func_290390(void *a, void *b, s32 c);
extern void  func_2901D0(void *a, void *b, s32 c, s32 d);
extern void  func_290450(void *a);
extern void *func_14E1B0(s32 size, void *heap);
extern void *func_100710(void *a, const void *b, s32 c, s32 d, s32 e);
extern void  func_131B60(void *a, s32 b, s32 c);
extern void  func_290B90(void *a, u16 id, void *b);
extern void  func_28EEC0(void *a, u16 id, void *b);

void normal_MenuBattleEndInit_4ee600(Obj *p, void *heap)
{
    s32 id;
    Rec *r;
    void *t;
    s32 n;
    s32 i;
    s32 j;
    s32 k;

    D_004843E0 = func_207DF0();
    r = func_42C500(func_206A40(), 0xF);
    t = r->f04;
    n = r->fA_hi;
    func_2912E0(&p->f014);
    func_290390(&p->f014, heap, n);
    func_2901D0(&p->f014, t, 0, 0);
    p->f01C = 0x32D;
    func_290450(&p->f014);
    p->f028 = 9;
    p->f02C = func_14E1B0(0x1D4, heap);
    p->f0EC = func_14E1B0(0x60, heap);
    t = func_100710(func_14E1B0(0x90, heap), D_002931A0, 0, 0x10, 8);
    p->f108 = t;
    func_131B60(t, 0, 0x80);
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
    D_004843C8 = func_14E1B0(0x800, heap);
    D_004843CC = func_14E1B0(0x400, heap);
    D_004843D0 = func_14E1B0(0x200, heap);
    D_004843D4 = func_14E1B0(0x200, heap);
    D_004843D8 = func_14E1B0(0x100, heap);
    D_004843DC = func_14E1B0(0x100, heap);
    func_131B60(D_004843C8, 0, 0x800);
    func_131B60(D_004843CC, 0, 0x400);
    func_131B60(D_004843D0, 0, 0x200);
    func_131B60(D_004843D4, 0, 0x200);
    func_131B60(D_004843D8, 0, 0x100);
    func_131B60(D_004843DC, 0, 0x100);
    for (i = 0; i < 8; i++) {
        k = i * 3;
        D_004843C8[i].f0E0 = -1;
        D_004843CC[i].f060 = -1;
        D_004843D0[i].f020 = -1;
        D_004843D4[i].f020 = -1;
        id = k + 0x15;
        func_290B90(&p->f014, id, &D_004843C8[i]);
        func_28EEC0(&p->f014, id, &D_004843CC[i]);
        func_28EEC0(&p->f014, k + 0x17, &D_004843D0[i]);
        func_290B90(&p->f014, k + 0x16, &D_004843D4[i]);
    }
    for (j = 0; j < 4; j++) {
        k = j * 3;
        D_004843D8[j].f020 = -1;
        D_004843DC[j].f020 = -1;
        func_290B90(&p->f014, k + 3, &D_004843D8[j]);
        func_290B90(&p->f014, k + 5, &D_004843DC[j]);
    }
}
