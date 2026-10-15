#include "types.h"
/* normal 0x00501640 -- refreshes the four 0x51..0x54 action buttons of the
 * field menu from the current party member's state.  With no menu object, or
 * no member, it bails; when the member reports slot-45 non-zero every button
 * is greyed (005036d0) and re-tinted, otherwise each button is enabled or
 * greyed from its own guard chain and the same four tints are applied.
 *
 * THREE `lw $25,0($19) / lw $25,K($25) / jalr $25` sites -> C++ virtual,
 * vptr at offset 0, slots (0xBC-8)/4 = 45, (0x274-8)/4 = 155, (0x368-8)/4 = 216.
 * `dsll32/dsra32 ..,16` off the plain `lh` is an s32 local plus an explicit
 * `(s16)` cast, not an s16 local.
 * Each guard is spelled as an OR-chain that selects the GREY call, because the
 * grey call is the fall-through arm and the enable call sits after the `b`. */

struct Obj {
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
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual s32 mode();   /* slot 45 -> vtable +0xBC */
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual s32 canUse(s32 k);   /* slot 155 -> vtable +0x274 */
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual s32 locked();   /* slot 216 -> vtable +0x368 */
    u8   pad04[0x0C - 4];
    s32  f0C;
    u8   pad10[0x4B4 - 0x10];
    u8   f4B4;
};

typedef struct Owner { u8 pad0000[0x42D0]; u8 f42D0; } Owner;
typedef struct Top   { u8 pad00[0x10]; void *f10; u8 pad14[4]; Owner *f18; } Top;
typedef struct Ctx   { u8 pad000[0x44E]; s16 f44E; } Ctx;

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern "C" {

extern Top  *func_1FEDE0(void);
extern void *func_28FE10(void *w, u16 id, s32 k);
extern void  func_2905B0(void *w, u16 id, f32 r, f32 g, f32 b, f32 t);
extern s32   func_2F5320(s32 a);
extern s32   func_3ADD30(Obj *o, s32 b, s32 c, s32 d);
extern s32   func_3AE1A0(Obj *o);
extern s32   func_3AE200(Obj *o, s32 b);
extern s32   func_3C2010(Owner *o, s32 b, s32 c);
extern Obj  *func_3C2FB0(Owner *o, s32 k);
extern s32   func_3CCD70(void *h, s32 id);
extern s32   func_1FB1F0(s32 a);
extern void  normal_BtlChgMenuSpritesSetFlag8_503680(void *w, s32 k);
extern void  normal_BtlChgMenuSpritesClearFlag8_5036d0(void *w, s32 k);
extern s32   normal_BtlChgPageGetMember_505f90(Ctx *p);

}

extern "C" s32 normal_BtlChgMenuCommandRowsRefresh_501640(void)
{
    Top  *t;
    Obj  *o;
    void *w;
    s32   k;

    t = func_1FEDE0();
    if (t == 0) {
        return 1;
    }
    o = func_3C2FB0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
    if (o == 0) {
        return 0;
    }
    if (o->mode() != 0) {
        normal_BtlChgMenuSpritesSetFlag8_503680(func_28FE10(D_0048449C, 0x53, 0), 5);
        w = func_28FE10(D_0048449C, 0x52, 0);
        if (o->locked() != 0 || func_2F5320(o->f0C) != 0 ||
            (func_3CCD70(t->f10, 0xB6) != 0 && o->f0C == 0)) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 0x10);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 0x10);
        }
        w = func_28FE10(D_0048449C, 0x51, 0);
        k = D_00484454->f44E;
        if (func_3AE200(o, 0) == 0 || (o->f4B4 & 1) != 0 ||
            ((t->f18->f42D0 & 1) != 0 && o->f0C != 0) ||
            o->canUse(-1) == 0 || func_3ADD30(o, 0, -1, 0) == 0 ||
            (s16)k != 0 || func_1FB1F0(o->f0C) == 0) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 9);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 9);
        }
        w = func_28FE10(D_0048449C, 0x54, 0);
        if (func_3AE200(o, 0) == 0 || (o->f4B4 & 1) != 0 ||
            ((t->f18->f42D0 & 1) != 0 && o->f0C != 0) ||
            func_3C2010(t->f18, 1, 1) == 1 || func_3AE1A0(o) != 0) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 0x11);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 0x11);
        }
        func_2905B0(D_0048449C, 0x51, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x52, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x53, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x54, 0.5f, 0.5f, 0.5f, -1.0f);
    } else {
        normal_BtlChgMenuSpritesClearFlag8_5036d0(func_28FE10(D_0048449C, 0x51, 0), 9);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(func_28FE10(D_0048449C, 0x52, 0), 0x10);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(func_28FE10(D_0048449C, 0x53, 0), 5);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(func_28FE10(D_0048449C, 0x54, 0), 0x11);
        func_2905B0(D_0048449C, 0x51, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x52, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x53, 0.5f, 0.5f, 0.5f, -1.0f);
        func_2905B0(D_0048449C, 0x54, 0.5f, 0.5f, 0.5f, -1.0f);
    }
    return 0;
}
