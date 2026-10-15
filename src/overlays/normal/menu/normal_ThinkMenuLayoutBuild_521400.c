#include "types.h"
/* normal 0x00521400 -- opens the shop/talk transaction page on `h`: builds the
 * 0x32D record through func_42B840/func_202BE0, binds slot 3's record to the
 * 0x484920 panel, then measures the 0x7533 body text.  Text wider than 480
 * arms the 0x484958 scroller (start, end and travel written into the four
 * 0x48495C..0x484964 floats plus the two 0x48078C/0x480790 speeds) and hides
 * the 0x7548 marker; text that fits clears the scroller instead.  Finally
 * slot 3's second record is pushed at the 0x528030 panel and the 0x528050
 * page flag is cleared.
 *
 * `lhu 0xA / dsll32 16 / dsrl32 18` is the `u16 :2 / u16 :14` bitfield at
 * offset 0xA -- the same Rec normal_HelpMenuStep_522fd0 and normal_TransMenuLayoutBuild_516e20 use.
 * `lbu / addiu -2 / andi 1 / and / or / sb` on D_00528050 is a ONE-BIT
 * BITFIELD AT BIT 0 assigned 0; the whole insert survives only because the
 * assigned value is 0 -- `= 1` folds to a plain store.
 * `daddu $17,$2,$0` in func_2912E0's DELAY SLOT captures func_42C500's result,
 * so the guard below tests THAT, and func_2912E0's own result is discarded.
 * `lui $2,0x4200 / sw $2,-0x49E4($28)` is an f32 store of a CONSTANT through a
 * GPR -- mwcc materialises the pattern once and both stores it and moves it
 * into $f0 for the sum.
 * THE SIX SCROLLER STORES ARE A STATEMENT-ORDER SEARCH and the order is the
 * whole residue: 17 permutations measured, 3 of them the wrong LENGTH (the
 * mtc1 hazard nop before the 64.0f add appears only when the 64.0f constant
 * is materialised late), 16/15/7 bad for others, and MATCH for
 * -w / 1 / w / 32.0f / sum / 90.0f.  The 7-bad cell is a pure rotation of the
 * 90.0f store, which has to sink BELOW the sum so 64.0f can take its own
 * register.  Five spellings share the winning object, so what the compiler
 * reads is (-w, 1, w) in any order, then 32.0f, then the sum, then 90.0f.
 * Every D_00528xxx extern is an INCOMPLETE ARRAY: as plain scalars they fall
 * under the small-data threshold and come out GPREL16 where retail has
 * lui/%lo (levers.d/normal-small-data-threshold). */

typedef struct Rec {
    u8   pad00[4];
    s32  f04;
    u8   pad08[2];
    u16  fA_lo : 2;
    u16  fA_hi : 14;
} Rec;

typedef struct Blk   { u8 pad00[8]; s32 f08; } Blk;
typedef struct Flags { u8 b0 : 1; u8 rest : 7; } Flags;

extern const u8 D_00526860[];
extern const u8 D_00528030[];
extern const u8 D_00528090[];
extern s32      D_00528048[];
extern Flags    D_00528050[];
extern s8       D_00528051[];

extern f32   D_0048078C;          /* gp - 0x49E4 */
extern f32   D_00480790;          /* gp - 0x49E0 */
extern void *D_00484918;          /* gp - 0x858  */
extern Blk  *D_00484920;          /* gp - 0x850  */
extern u8    D_00484958;          /* gp - 0x818  */
extern f32   D_0048495C;          /* gp - 0x814  */
extern f32   D_00484960;          /* gp - 0x810  */
extern f32   D_00484964;          /* gp - 0x80C  */

extern void *func_202BE0(void *h, const void *p, void *q, s32 id, s32 c);
extern void *func_206A40(void);
extern s32   func_207DF0(void);
extern void  func_28E0C0(const void *p, void *q, s32 c);
extern void  func_28EB70(const void *p, s32 c, void *q);
extern void  func_28EC80(const void *p);
extern void  func_28F300(void *p, s32 id, s32 c, s32 d);
extern s32   func_28F400(void *p, s32 id, s32 c);
extern void  func_28F510(void *p, s32 id, const void *q, s32 d);
extern void  func_2901D0(void *p, s32 c, s32 d, s32 e);
extern void  func_290390(void *p, void *q, s32 c);
extern void  func_290450(void *p);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern void *func_2912E0(void *p);
extern void  func_42B840(void *o, s32 a, s32 b, void *q, void *h);
extern Rec  *func_42C040(void *o, s32 a);
extern Rec  *func_42C500(void *o, s32 a);
extern void  normal_ThinkMenuPromptScrollStep_521660(f32 x);

void normal_ThinkMenuLayoutBuild_521400(void *h)
{
    void *o;
    Rec  *r;
    Rec  *m;
    f32   w;

    o = func_206A40();
    func_42B840(o, 2, 7, D_00484918, h);
    func_202BE0(h, D_00526860, D_00484918, 0x32D, 0);
    r = func_42C500(o, 3);
    func_2912E0(D_00484920);
    if (r != 0) {
        func_290390(D_00484920, D_00484918, r->fA_hi);
        func_2901D0(D_00484920, r->f04, 0, 0);
    }
    D_00484920->f08 = 0x32D;
    func_290450(D_00484920);
    func_28F510(D_00484920, 0x7533, D_00528090, 0);
    func_28F300(D_00484920, 0x7533, 0x100, 0);
    w = (f32)func_28F400(D_00484920, 0x7533, 0);
    if (w > 480.0f) {
        D_00484964 = -w;
        D_00484958 = 1;
        D_0048495C = w;
        D_0048078C = 32.0f;
        D_00484960 = w + 32.0f + 64.0f;
        D_00480790 = 90.0f;
        func_28F510(D_00484920, 0x7533, D_00528090, 1);
        func_291110(D_00484920, 0x7548, 0, 1);
        normal_ThinkMenuPromptScrollStep_521660(0.0f);
    } else {
        D_00484958 = 0;
        func_291110(D_00484920, 0x7548, 0, 1);
        func_28F510(D_00484920, 0x7533, 0, 1);
    }
    m = func_42C040(o, 3);
    func_28EC80(D_00528030);
    if (m != 0) {
        func_28E0C0(D_00528030, D_00484918, m->fA_hi);
        func_28EB70(D_00528030, m->f04, D_00484920);
    }
    D_00528048[0] = func_207DF0();
    D_00528050[0].b0 = 0;
    D_00528051[0] = 0;
}
