/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 mode() { return VCM0(s32, 0xBC); }   /* slot 45 -> vtable +0xBC */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 canUse(s32 k) { return VCM(s32, (void *, s32), 0x274, k); }   /* slot 155 -> vtable +0x274 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 locked() { return VCM0(s32, 0x368); }   /* slot 216 -> vtable +0x368 */
    u8   pad04[0x0C - 4];
    s32  f0C;
    u8   pad10[0x4B4 - 0x10];
    u8   f4B4;
};

typedef struct Owner { u8 pad0000[0x42D0]; u8 f42D0; } Owner;
typedef struct Top   { u8 pad00[0x10]; void *f10; u8 pad14[4]; Owner *f18; } Top;
typedef struct Ctx   { u8 pad000[0x44E]; s16 f44E; } Ctx;

extern "C" Ctx  *D_00484454;          /* gp - 0xD1C */
extern "C" void *D_0048449C;          /* gp - 0xCD4 */

extern "C" {

extern Top  *GetGameData_1fede0(void);
extern void *UiGetWidgetSprite_28fe10(void *w, u16 id, s32 k);
extern void  UiSetWidgetColor_2905b0(void *w, u16 id, f32 r, f32 g, f32 b, f32 t);
extern s32   CharaGetControlStateMaybe_2f5320(s32 a);
extern s32   CharaCountAbilitiesFilteredMaybe_3add30(Obj *o, s32 b, s32 c, s32 d);
extern s32   CharaIsPartyLeader_3ae1a0(Obj *o);
extern s32 CharaCanBeLeader_3ae200(Obj *, s32, int, int);
extern s32   PartyCountMembers_3c2010(Owner *o, s32 b, s32 c);
extern Obj  *PartyGetSlotChara_3c2fb0(Owner *o, s32 k);
extern s32   StateFlagTest_3ccd70(void *h, s32 id);
extern s32   CharaModeIsNormalByIdMaybe_1fb1f0(s32 a);
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

    t = GetGameData_1fede0();
    if (t == 0) {
        return 1;
    }
    o = PartyGetSlotChara_3c2fb0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
    if (o == 0) {
        return 0;
    }
    if (o->mode() != 0) {
        normal_BtlChgMenuSpritesSetFlag8_503680(UiGetWidgetSprite_28fe10(D_0048449C, 0x53, 0), 5);
        w = UiGetWidgetSprite_28fe10(D_0048449C, 0x52, 0);
        if (o->locked() != 0 || CharaGetControlStateMaybe_2f5320(o->f0C) != 0 ||
            (StateFlagTest_3ccd70(t->f10, 0xB6) != 0 && o->f0C == 0)) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 0x10);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 0x10);
        }
        w = UiGetWidgetSprite_28fe10(D_0048449C, 0x51, 0);
        k = D_00484454->f44E;
        if (CharaCanBeLeader_3ae200(o, 0, 0, 0) == 0 || (o->f4B4 & 1) != 0 ||
            ((t->f18->f42D0 & 1) != 0 && o->f0C != 0) ||
            o->canUse(-1) == 0 || CharaCountAbilitiesFilteredMaybe_3add30(o, 0, -1, 0) == 0 ||
            (s16)k != 0 || CharaModeIsNormalByIdMaybe_1fb1f0(o->f0C) == 0) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 9);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 9);
        }
        w = UiGetWidgetSprite_28fe10(D_0048449C, 0x54, 0);
        if (CharaCanBeLeader_3ae200(o, 0, 0, 0) == 0 || (o->f4B4 & 1) != 0 ||
            ((t->f18->f42D0 & 1) != 0 && o->f0C != 0) ||
            PartyCountMembers_3c2010(t->f18, 1, 1) == 1 || CharaIsPartyLeader_3ae1a0(o) != 0) {
            normal_BtlChgMenuSpritesClearFlag8_5036d0(w, 0x11);
        } else {
            normal_BtlChgMenuSpritesSetFlag8_503680(w, 0x11);
        }
        UiSetWidgetColor_2905b0(D_0048449C, 0x51, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x52, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x53, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x54, 0.5f, 0.5f, 0.5f, -1.0f);
    } else {
        normal_BtlChgMenuSpritesClearFlag8_5036d0(UiGetWidgetSprite_28fe10(D_0048449C, 0x51, 0), 9);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(UiGetWidgetSprite_28fe10(D_0048449C, 0x52, 0), 0x10);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(UiGetWidgetSprite_28fe10(D_0048449C, 0x53, 0), 5);
        normal_BtlChgMenuSpritesClearFlag8_5036d0(UiGetWidgetSprite_28fe10(D_0048449C, 0x54, 0), 0x11);
        UiSetWidgetColor_2905b0(D_0048449C, 0x51, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x52, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x53, 0.5f, 0.5f, 0.5f, -1.0f);
        UiSetWidgetColor_2905b0(D_0048449C, 0x54, 0.5f, 0.5f, 0.5f, -1.0f);
    }
    return 0;
}
