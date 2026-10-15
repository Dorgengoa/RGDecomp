#include "types.h"

/* title.bin overlay, 0x004EFEB0 -- build the OPTIONS panel's widget set, then
 * drive its two-state fade-out.
 *
 * The first-run arm caches three gp pointers into a second trio
 * (D_00484250/54/58) and then does the whole layout through them.  The tail is
 * an if/else-if chain on D_0048425C, NOT a switch: `bnel $3,$0,.L004F0408`
 * carries `addiu $2,$0,0x1`, the NEXT GUARD'S CONSTANT, which is the
 * discriminator recorded in [[overlay-c-pipeline]].
 */

typedef struct Ent_title_FUN_004efeb0 {
    u8 pad000[0x4];
    s16 field004;
    s16 field006;
    s16 field008;
    u8 pad00A[0xA];
    s16 field014;
    s16 field016;
} Ent_title_FUN_004efeb0;

typedef struct Cfg_title_FUN_004efeb0 {
    u8 pad000[0x1A];
    s16 field01A;
} Cfg_title_FUN_004efeb0;

typedef struct Sys_title_FUN_004efeb0 {
    u8 pad000[0xC];
    Cfg_title_FUN_004efeb0 *field00C;
} Sys_title_FUN_004efeb0;

extern f32 D_0047D248;
extern f32 D_0047D518;
extern f32 D_0047D550;
extern f32 D_0047D554;
extern f32 D_0047D558;
extern s16 D_00480428;
extern s16 D_0048042A;
extern s16 D_0048042C;
extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484170;
extern void *D_00484180;
extern void *D_00484250;
extern void *D_00484254;
extern void *D_00484258;
extern s32 D_0048425C;
extern s16 D_00484260;
extern s16 D_00484262;

extern void func_1CF740(void *a, s32 b);
extern void *func_1F5BE0(void);
extern Sys_title_FUN_004efeb0 *func_1FEDE0(void);
extern s32 func_28AA30(void *a, s32 b);
extern Ent_title_FUN_004efeb0 *func_28EA40(void *a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_28F510(void *a, s32 b, s32 c, s32 d);
extern void func_28F970(void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern void func_2905B0(void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern f32 func_290770(void *a, s32 b);
extern void func_2907A0(void *a, s32 b, f32 v);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);
extern void func_290F60(void *a, s32 b, s32 x, s32 y);
extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern void title_TitleSceneOverlayModeOn_4eaa40(void);
extern void title_TitleOptionsRefreshAll_4ef710(void);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);

s32 title_TitleOptionsOpen_4efeb0(void *unused, s32 first)
{
    u16 ids[3];
    Ent_title_FUN_004efeb0 *p;
    s32 i;
    s32 t;

    if (first != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        D_00484250 = D_00484158;
        D_00484254 = D_00484170;
        D_00484258 = D_0048415C;
        func_290010(D_00484170, 1, 0, -1);
        func_291110(D_00484254, 0xA, 1, 1);
        func_2907A0(D_00484254, 0xA, 0.0f);
        func_290690(D_00484254, 0xA, 1.0f, D_0047D554, -1.0f);
        func_290F60(D_00484254, 0xD, 5, 5);
        func_2905B0(D_00484254, 0xD, 0.0f, 0.0f, 0.0f, D_0047D558);
        func_291110(D_00484254, 7, 1, 1);
        func_2907A0(D_00484254, 7, 0.0f);
        func_290690(D_00484254, 7, 1.0f, D_0047D554, -1.0f);
        func_291110(D_00484254, 0x62, 0, 1);
        func_291110(D_00484254, 0x63, 0, 1);
        func_291110(D_00484254, 0x64, 0, 1);
        func_291110(D_00484254, 0x65, 0, 1);
        i = 0;
        do {
            func_28F510(D_00484254, 0x49, func_28AA30(D_00484180, i + 0x3C), i);
            i = i + 1;
        } while (i < 0xA);
        i = 0;
        ids[0] = D_00480428;
        ids[1] = D_0048042A;
        ids[2] = D_0048042C;
        do {
            func_291110(D_00484254, ids[i], 0, 1);
            i = i + 1;
        } while (i < 3);
        func_291110(D_00484254, 0x43, 0, 1);
        func_291110(D_00484254, 0x44, 0, 1);
        func_291110(D_00484254, 0x17, 0, 1);
        func_291110(D_00484254, 0xE, 0, 1);
        func_291110(D_00484254, 0xF, 0, 1);
        func_290010(D_00484254, 0x48, 1, -1);
        func_290F60(D_00484254, 0x48, 0x200, 0x3C);
        func_290F50(D_00484254, 0x48, 0x4D, 0x3C, 0, 0.25f);
        func_290690(D_00484254, 0x48, 1.0f, D_0047D550, 0.0f);
        func_291110(D_00484254, 0x47, 1, 1);
        func_290F60(D_00484254, 0x47, 0x206, 0x41);
        func_290F50(D_00484254, 0x47, 0x53, 0x41, 0, 0.25f);
        func_2905B0(D_00484254, 0x47, 0.0f, 0.0f, 0.0f, D_0047D558);
        func_28F970(D_00484254, 0x14, 0xC0, 0x92, 0);
        func_290F60(D_00484254, 0x14, 0x30, 0xF);
        func_290F60(D_00484254, 0x12, -0x12, 0xC);
        func_290F60(D_00484254, 0x11, -0xF, 0xF);
        func_2905B0(D_00484254, 0x11, 0.0f, 0.0f, 0.0f, D_0047D558);
        func_290F50(D_00484254, 0x12, 0x5A, 0xC, 0, 0.25f);
        func_290F50(D_00484254, 0x11, 0x5D, 0xF, 0, 0.25f);
        func_290690(D_00484254, 0x12, 1.0f, D_0047D554, -1.0f);
        func_290690(D_00484254, 0x11, D_0047D558, D_0047D550, -1.0f);
        func_291110(D_00484254, 0x13, 1, 1);
        func_290F60(D_00484254, 0x4A, 0, 0);
        func_2907A0(D_00484254, 0x4A, D_0047D248);
        p = func_28EA40(D_00484258, 0x7536);
        title_TitleOptionsRefreshAll_4ef710();
        t = func_1FEDE0()->field00C->field01A & 1;
        if (t == 1) {
            p->field014 = 0;
        } else if (t == 0) {
            p->field014 = 1;
        }
        p->field016 = 0;
        D_00484260 = p->field014;
        D_00484262 = 0;
        func_291110(D_00484254, 0x60, 1, 1);
        func_290690(D_00484254, 0x60, 1.0f, D_0047D550, -1.0f);
        func_290F60(D_00484254, 0x60,
                    p->field004 + p->field014 * p->field008, p->field006);
        D_0048425C = 0;
        title_TitleSetNoAnalogPause_4f13b0(0);
    }
    if (D_0048425C == 0) {
        if (!(func_290770(D_00484254, 7) < 1.0f)) {
            D_0048425C = 1;
            func_290690(D_00484254, 8, 1.0f, D_0047D554, -1.0f);
            func_290F50(D_00484254, 8, 0, 0, 0, D_0047D518);
            func_1CF740(func_1F5BE0(), 0xA);
        }
    } else if (D_0048425C == 1) {
        func_28EDE0(D_00484250, 0xC, 0);
    }
    return 1;
}
