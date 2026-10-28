/* rgp:protos */
#line 1
/* ★★★★★★★★ SESSION 45 (n45v): BYTE-IDENTICAL, 236/236 words, MERGED.
 * The twin of normal_BtlChgPageWeaponGridScrollRow_504410; read that unit's header FIRST -- levers 1
 * (the 64-bit read-back rvalue `z64 = a->f04;`) and 2 (`b = 0;` BELOW
 * `func_290460(h, 0x55)`) transfer verbatim, and lever 3 transfers as
 * `n = i + mode * 8;` at the loop top feeding `e = ctx->f7C[n];` (retail keeps
 * `$30 = mode * 8` and spends `addu $2,$21,$30` in the loop-head block; without
 * the temp mwcc strength-reduces the whole index into the base pointer,
 * `sll v0,s5,0x5` / `addu s7,s7,v0`).  ⚠ Reusing `j` or `k` for that temp is
 * length-wrong AND semantically wrong -- both are live later in the body.
 *
 * FOUR MORE, all specific to this unit and all measured:
 *
 * 4. `a = (Box *)w->f20;` moves UP, directly under `if (w == 0) return 0;` and
 *    ABOVE the `a == 0` test -- retail loads it in that branch's DELAY SLOT
 *    (0x005047F8 `lw $18,0x20($2)`).  Worth -2 words on its own.
 *
 * 5. `uid = (u16)id;` moves to the TOP (under the thunk call) and the FIRST
 *    `func_290460` takes `uid`, so `(u16)id` gets its OWN register ($21) and
 *    the call spends a separate `daddu $5,$21,$0` instead of folding the `andi`
 *    into `$a1`.  The LOOP calls then take `(u16)uid` -- an explicit re-narrow
 *    that is retail 0x00504884 `andi $22,$21,0xFFFF`, hoisted out of the loop,
 *    after which $21 is reused as `i`.  ⚠ `id` / `(u16)id` / a plain `uid` in
 *    those calls are all length-wrong.
 *
 * 6. `Ent *e;` is declared AFTER `s32 i;`.  That one move is 56 bad -> 40 and
 *    empties a whole two-web GPR swap (retail e=$20 / i=$21; we had them the
 *    other way round).  [[levers.d/mwcc-callee-saved-creation-order]].
 *
 * 7. THE LAST TWO WORDS ARE A CROSS ([[two-edit-cross-beats-count-ranking]]),
 *    and each half ALONE is length-wrong:
 *      (a) a `u16 uid2 = (u16)id;` shared by func_291110 AND func_2905B0.
 *          Retail narrows ONCE (`andi $20,$20,0xFFFF`) and feeds both from
 *          `$20`; with `id` left s32 every u16 parameter re-converts it.
 *          ⚠ `id = (u16)id;` fixes only the FIRST call -- the second still
 *          re-narrows; so does passing `uid`.  Declaring func_2905B0's or
 *          func_291110's `id` parameter s32/u32 is byte-identical too, but that
 *          is a claim about an EXTERNAL function, so the local is preferred.
 *      (b) in the `i >= count` early-out, `a++;` is written ABOVE
 *          `if (b != 0) b++;`.  Retail uses a PLAIN `beqz $16` with
 *          `addiu $18,$18,0x20` in its delay slot; with `a++` below the guard
 *          mwcc picks `beqzl` and DUPLICATES `a++`, one word long.
 *          ⚠ `a++; c++;` or `c++; a++;` before the guard are exact length but
 *          5 bad -- the order is a++, guard, c++.
 *
 * ⚠ `if (a == 0) return 0;` reads `a` BEFORE lever 4 assigns it in the old
 * source; that was an m2c artefact and lever 4 removes it.
 */
#include "types.h"
/* normal 0x005047A0 -- the sixteen-slot party rack builder, the wide sibling of
 * normal_BtlChgPageWeaponGridScrollRow_504410.  It fetches the rack widget (`id`) and its 0x55 shadow,
 * clears both rows, and for the first `count` slots lays the icon out in two
 * columns of eight, reads the member's 0x2E sprite index out of its model and
 * splits it into a 8x8 cell (`% 8` and `/ 8`, both scaled by 32).  Members that
 * are full (slot 56's count vs slot 26's limit) get func_290BD0 with +1, the
 * rest with -1, and func_3D4C20 decides whether the shadow row is written too.
 *
 * THREE VIRTUAL calls, so the unit is .cpp -- a struct of function pointers
 * gives `jalr $v0`.  The slots are (0xE8-8)/4 = 56 on Node and (0x70-8)/4 = 26
 * on Ent, the same two classes normal_FUN_004FE750 already carries.
 * `$4` is spilled to 0xAC and `$6` to 0xA8 and both are re-read inside the
 * loop, so they stay ordinary parameters.
 * `sd` of a dsll32/dsra32'd zero is an s16 zero widened into the 64-bit 0x8
 * member.
 * `sra 3` with a `+7` correction and `andi 7` with a `-8` correction are the
 * signed `/ 8` and `% 8` expansions, not shifts. */

typedef struct Mdl { u8 pad00[0x2E]; s16 f2E; } Mdl;

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x1C - 0x10];
    u16 f1C;
    u8  pad1E[2];
} Box;

typedef struct Rec {
    s16 f00;
    u8  pad02[6];
    s64 f08;
    u8  pad10[0x1C - 0x10];
    s16 f1C;
    s16 f1E;
} Rec;

typedef struct Hold { u8 pad00[0x20]; void *f20; } Hold;

struct Node {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0xE8); }                   /* slot 56 -> vtable +0xE8 */
};

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 limit() { return VCM0(s32, 0x70); }                   /* slot 26 -> vtable +0x70 */
    u8   pad04[0x10 - 4];
    Mdl *f10;
};

typedef struct Ctx { u8 pad00[0x7C]; Ent *f7C[1]; } Ctx;

extern "C" f32   D_0047D528;      /* gp - 0x7C48 */

extern "C" void *normal_UiPageGetLayout_289b60(Ctx *p);
extern "C" Rec  *UiGetWidgetSubItem_28f2b0(void *p, u16 id, s32 a);
extern "C" Hold *UiFindWidget_290460(void *p, u16 id);
extern "C" void  UiSetWidgetColor_2905b0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void UiSetSpriteFlags_290bd0(void *, u16, long long, s32, s32, s32);
extern "C" void  UiSetWidgetsVisibleById_291110(void *p, u16 id, s32 c, s32 d);
extern "C" s32   ItemIsWeapon_3d46c0(Ent *e);
extern "C" s32   PartyFindItemHolder_3d4c20(Ent *e);
extern "C" Node *ItemFindOwnerChara_3d4d80(Ent *e, s32 a);

extern "C" s32 normal_BtlChgPageWeaponGridLayout_5047a0(Ctx *ctx, s32 id, s32 count, s32 mode);

s32 normal_BtlChgPageWeaponGridLayout_5047a0(Ctx *ctx, s32 id, s32 count, s32 mode)
{
    void *h;
    Hold *w;
    Box  *a;
    Rec  *c;
    Box  *b;
    Node *nd;
    s32   i;
    Ent  *e;
    s32   j;
    s32   k;
    s32   n;
    s32   t;
    u16   uid;
    u16   uid2;
    s64   z64;

    h = normal_UiPageGetLayout_289b60(ctx);
    uid = (u16)id;
    w = UiFindWidget_290460(h, uid);
    if (w == 0) {
        return 0;
    }
    a = (Box *)w->f20;
    if (a == 0) {
        return 0;
    }
    c = UiGetWidgetSubItem_28f2b0(h, 0x27, 0);
    if (c == 0) {
        return 0;
    }
    w = UiFindWidget_290460(h, 0x55);
    b = 0;
    if (w != 0) {
        b = (Box *)w->f20;
    }
    uid2 = (u16)id;
    UiSetWidgetsVisibleById_291110(h, uid2, 1, 1);
    UiSetWidgetColor_2905b0(h, uid2, D_0047D528, D_0047D528, D_0047D528, -1.0f);
    for (i = 0; i < 0x10; i++) {
        n = i + mode * 8;
        a->f0E = 0;
        a->f0C = 0;
        a->f06 = 0;
        a->f04 = 0;
        z64 = a->f04;
        if (b != 0) {
            b->f0E = 0;
            b->f04 = b->f06 = b->f0C = z64;
        }
        c->f08 = c->f1C = c->f1E = 0;
        if (i >= count) {
            a++;
            if (b != 0) {
                b++;
            }
            c++;
            continue;
        }
        {
            if (i < 8) {
                j = i;
                k = 0;
            } else {
                j = i - 8;
                k = 1;
            }
            a->f00 = j * 0x2C + 2;
            a->f02 = k * 0x32 - 1;
            if (b != 0) {
                b->f00 = (s16)(j * 0x2C + 2);
                b->f02 = (s16)(k * 0x32 - 1);
            }
            e = ctx->f7C[n];
            if (e != 0) {
                if (ItemIsWeapon_3d46c0(e) != 0) {
                    nd = ItemFindOwnerChara_3d4d80(e, 0);
                    n = nd->count();
                    if (n >= e->limit()) {
                        UiSetSpriteFlags_290bd0(h, (u16)uid, (long long)(0x20), 1, i, 0);
                    } else {
                        UiSetSpriteFlags_290bd0(h, (u16)uid, (long long)(0x20), -1, i, 0);
                    }
                }
                t = e->f10->f2E;
                a->f04 = 0x28;
                a->f06 = 0x2D;
                a->f0C = 0x20;
                a->f0E = 0x20;
                a->f08 = (s16)((t % 8) * 32);
                a->f0A = (s16)((t / 8) * 32);
                a->f1C = a->f1C | 2;
                if (PartyFindItemHolder_3d4c20(e) != 0 && b != 0) {
                    t = e->f10->f2E;
                    b->f04 = 0x28;
                    b->f06 = 0x2D;
                    b->f0C = 0x20;
                    b->f0E = 0x20;
                    b->f08 = (s16)((t % 8) * 32);
                    b->f0A = (s16)((t / 8) * 32);
                    b->f1C = b->f1C | 2;
                }
            }
        }
        if (b != 0) {
            b++;
        }
        a++;
        c++;
    }
    a->f00 = -1;
    if (b != 0) {
        b->f00 = -1;
    }
    c->f00 = -1;
    return 1;
}
