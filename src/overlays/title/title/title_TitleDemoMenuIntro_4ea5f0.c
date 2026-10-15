#include "types.h"

/* title.bin overlay, 0x004EA5F0 -- the title logo's four-state entrance
 * animation, ticked once a frame.  The state lives in D_004841B0 and the four
 * arms are an if/else-if CHAIN in source order 0,1,2,3: every converted `bnel`
 * carries THE NEXT GUARD'S CONSTANT and the last guard is a plain `bne` with a
 * nop slot, which is the chain signature, not a switch's.
 *
 * The 0x65 placement block appears TWICE, in the reset prologue and in state
 * 3, and retail emits it both times, so it is a `static inline` helper -- the
 * recorded form of the cold-block recipe for a REPEATED block.
 *
 * `mult` + `mult1` are the R5900's two multiply pipelines, which is what a
 * pair of INDEPENDENT s16 products compiles to; nothing in the source says so.
 * `cvt.w.s` reaches the listing as a bare `.word`, so read that region from the
 * encodings and not from any opcode-driven instrument.
 *
 * The callees take the widget id as u16 while the loop counter is s32, which is
 * why `andi $5, $17, 0xFFFF` is re-issued at EVERY call site instead of once at
 * the assignment.
 */

typedef struct Rec_title_FUN_004ea5f0 {
    u8 pad00[0x4];
    s16 field04;
    s16 field06;
    s16 field08;
    s16 field0A;
    u8 pad0C[0x8];
    s16 field14;
    s16 field16;
} Rec_title_FUN_004ea5f0;

extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484170;
extern s32 D_004841AC;
extern s16 D_004841B0;
extern s16 D_004841B4;
extern u8 D_004841B8[3];
extern s16 D_0048418C;
extern f32 D_0047D518;
extern f32 D_0047D520;

extern void title_TitleSceneOverlayModeOn_4eaa40(void);
extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern void func_291110(void *a, u16 b, s32 c, s32 d);
extern void func_2907A0(void *a, u16 b, f32 c);
extern void func_290690(void *a, u16 b, f32 c, f32 d, f32 e);
extern void func_290F60(void *a, u16 b, s32 c, s32 d);
extern void func_290F50(void *a, u16 b, s32 c, s32 d, s32 e, f32 f);
extern f32 func_290770(void *a, u16 b);
extern void func_2910A0(void *a, u16 b, s32 *c, s32 *d);
extern Rec_title_FUN_004ea5f0 *func_28EA40(void *a, s32 b);
extern void func_28EA90(void *a, s32 b, s32 c);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern s32 func_1F5BE0(void);
extern void func_1CF740(s32 a, s32 b);
extern void func_1D05C0(s32 a, s32 b, f32 c);

static inline void title_FUN_004ea5f0_place(void)
{
    Rec_title_FUN_004ea5f0 *p;

    p = func_28EA40(D_0048415C, 0x7537);
    if (p != 0) {
        func_290F60(D_00484170, 0x65,
                    (s32)(-6.0f + (f32)(p->field04 + p->field14 * p->field08)),
                    p->field06 + p->field16 * p->field0A);
    }
}

s32 title_TitleDemoMenuIntro_4ea5f0(s32 a, s32 b)
{
    s32 sp40[4];
    s32 sp30[4];
    s32 i;
    s32 id;
    s32 *q;
    u8 *f;
    s16 st;

    if (b != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        func_290010(D_00484170, 1, 0, -1);
        D_004841B4 = 0;
        D_004841B0 = 0;
        D_004841AC = 0;
        func_291110(D_00484170, 0x61, 1, 1);
        func_2907A0(D_00484170, 0x61, 0.0f);
        func_290690(D_00484170, 0x61, 1.0f, D_0047D520, -1.0f);
        func_2907A0(D_00484170, 0x62, 0.0f);
        func_290F60(D_00484170, 0x62, 0x100, 0);
        func_2907A0(D_00484170, 0x63, 0.0f);
        func_290F60(D_00484170, 0x63, 0x1C8, 0);
        func_2907A0(D_00484170, 0x64, 0.0f);
        func_290F60(D_00484170, 0x64, 0x290, 0);
        func_2907A0(D_00484170, 0x65, 0.0f);
        title_FUN_004ea5f0_place();
        D_004841B8[0] = 0;
        D_004841B8[1] = 0;
        D_004841B8[2] = 0;
    }
    st = D_004841B0;
    if (st == 0) {
        if (!(func_290770(D_00484170, 0x61) < 1.0f)) {
            D_004841B0 = 1;
            func_290690(D_00484170, 0x61, 1.0f, D_0047D520, -1.0f);
            func_290F50(D_00484170, 0x61, 0, 0, 0, D_0047D518);
            func_1CF740(func_1F5BE0(), 0xA);
        }
    } else if (st == 1) {
        i = 0;
        D_004841B0 = 2;
        do {
            id = i + 0x62;
            func_290690(D_00484170, id, 1.0f, D_0047D518, -1.0f);
            func_290F50(D_00484170, id, 0, 0, 1, 20.0f);
            i = i + 1;
        } while (i < 3);
    } else if (st == 2) {
        i = 0;
        do {
            q = &sp40[i];
            func_2910A0(D_00484170, i + 0x62, q, &sp30[i]);
            if (*q < 0xC8) {
                f = &D_004841B8[i];
                if (*f == 0) {
                    func_1D05C0(func_1F5BE0(), 1, 1.0f);
                    *f = 1;
                }
            }
            i = i + 1;
        } while (i < 3);
        if ((D_004841B8[0] != 0) && (D_004841B8[1] != 0) && (D_004841B8[2] != 0)
            && (sp40[0] == sp40[2])) {
            D_004841B0 = 3;
        }
    } else if (st == 3) {
        func_290690(D_00484170, 0x65, 1.0f, D_0047D520, -1.0f);
        title_FUN_004ea5f0_place();
        func_291110(D_00484170, 0x65, 1, 1);
        func_28EA90(D_0048415C, 0x7537, 0);
        func_28EDE0(D_00484158, 0x10, 0);
        D_0048418C = 0;
    }
    return 1;
}
