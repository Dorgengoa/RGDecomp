/* rgp:protos */
#define RGP_SELF_TaskDrawStatus_2058b0 1
#include "port/game_protos.h"
#line 1
#define KW 1
#define KT 5
#define KE 1
#define KF 6
#include "types.h"
#ifndef KT
#define KT 0
#endif

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { void *obj; f32 val; s32 type; } Ent;
typedef struct { s32 a, b, c, d; } Cell;
typedef struct { Cell c[2]; } Tbl;
#if KW
typedef struct { s32 x, y, z, w; } Scr;
#else
typedef struct { s32 x, y, z; } Scr;
#endif

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004BC470[];
extern u8 D_004BC6C0[];
extern u8 D_004BC310[];
extern u8 D_0045C440[];
extern Tbl D_0044B750;
extern u8 D_0045B080[0x400];
extern f32 D_0047D83C;
extern f32 D_0047D858;
extern f32 D_0047D1FC;

void TaskDrawStatus_2058b0(void)
{
#if KS == 1
    Scr scr __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    Ent ents[8] __attribute__((aligned(16)));
#elif KS == 2
    Ent ents[8] __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    Scr scr __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
#elif KS == 3
    Scr scr __attribute__((aligned(16)));
    Ent ents[8] __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
#else
    Ent ents[8] __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Scr scr __attribute__((aligned(16)));
#endif
    u8 *g;
    void *sys;
    s32 h;
    s32 cnt;
    s32 n;
    s32 i;
    s32 id;
    void *c;
    Ent *e;
    void *gp;
    void *pk;
    void *tex;
    f32 f20;
    u8 *o;
    f32 s;
    f32 a;
    s32 w;
    Cell *q;

    g = ((u8 *)GetGameData_1fede0());
    sys = GetCurrentScene_1f5be0();
    HpGaugeDrawThin_31d2d0(D_004BC470);
    HpGaugeDraw_31d090(D_004BC6C0);
    ScreenMarkerDrawAll_31af50(D_004BC310);
    DamagePopupDrawAll_2d2ea0(GetDamagePopupList_2d9020());
    if (((unsigned char)IsInBattle_288420()) == 0) return;
    h = ((s32)GetActionMgr_1fdb50());
    cnt = 0;
    n = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
    for (i = 0; i < n; i++) {
        id = ((short)PartyGetMemberId_3c2490(*(s32 *)(g + 0x18), i));
        c = ActionMgrFindById_233b50(h, id);
        if (c == 0) continue;
        if (((u8 *)ObjRecGetLiveObject_1c4a90(sys, id)) == 0) continue;
        if (CharaGaugeFullFxGetAlphaMaybe_2141f0(c) < 1.0f) {
            e = &ents[cnt];
            e->obj = c;
            e->val = CharaGaugeFullFxGetAlphaMaybe_2141f0(c);
            e->type = 1;
            cnt++;
        } else if (CharaGaugeDrainFxGetAlphaMaybe_214220(c) < 1.0f) {
            e = &ents[cnt];
            e->obj = c;
            e->val = CharaGaugeDrainFxGetAlphaMaybe_214220(c);
            cnt++;
            e->type = 0;
        }
    }
    if (cnt <= 0) return;
    gp = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(gp, 0x32B, 1.0f);
    pk = DrawListBeginPrim_141b00(gp);
    tex = GetDrawCtxNameTable_15de40();
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 1);
    GsPktSetBlendMode_13e4f0(pk, 1);
    GsPktEnableAlphaTest_13e4d0(pk, 1);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetFrameMask_13e420(pk, 1);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetTexFilter_13e3d0(pk, 1);
    GsPktSetTextured_13e400(pk, 0);
    GsPktOpenPrim_13f730(pk, 0);
    GsPktSetRGBAQ_13ee40(pk, 0, 0x80, 0, 0x80);
    GsPktSetXYZf_13f060(pk, 0.0f, 0.0f, -1.0f);
    GsPktClose_13f5b0(pk);
    GsPktSetTextured_13e400(pk, 1);
    GsPktSetUseUV_13e3e0(pk, 1);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetTexture_13ec00(pk, ((s32)NameTableFindByName_159fb0(tex, D_0045C440, 0x32B)));
#if KT == 0
    tbl = D_0044B750;
#elif KT == 1
    {
        s32 *s_ = (s32 *)&D_0044B750;
        s32 *d_ = (s32 *)&tbl;
        s32 n_ = 4;
        do {
            s32 a_ = s_[0];
            n_--;
            {
                s32 b_ = s_[1];
                d_[0] = a_;
                d_[1] = b_;
                s_ += 2;
                d_ += 2;
            }
        } while (n_ > 0);
    }
#elif KT == 3
    {
        s32 *s_ = (s32 *)&D_0044B750;
        s32 *d_ = (s32 *)&tbl;
        s32 n_ = 4;
        s32 b_;
        s32 a_;
        do {
            a_ = s_[0];
            n_--;
            b_ = s_[1];
            d_[0] = a_;
            d_[1] = b_;
            s_ += 2;
            d_ += 2;
        } while (n_ > 0);
    }
#elif KT == 5
    {
        s32 *s_ = (s32 *)&D_0044B750;
        s32 *d_ = (s32 *)&tbl;
        s32 n_ = 4;
        do {
            n_--;
            d_[0] = s_[0];
            d_[1] = s_[1];
            s_ += 2;
            d_ += 2;
        } while (n_ > 0);
    }
#elif KT == 6
    {
        s32 *s_ = (s32 *)&D_0044B750;
        s32 *d_ = (s32 *)&tbl;
        s32 n_ = 4;
        do {
            s32 b_ = s_[1];
            n_--;
            {
                s32 a_ = s_[0];
                d_[0] = a_;
                d_[1] = b_;
                s_ += 2;
                d_ += 2;
            }
        } while (n_ > 0);
    }
#elif KT == 7
    {
        s32 *s_ = (s32 *)&D_0044B750;
        s32 *d_ = (s32 *)&tbl;
        s32 n_ = 4;
        do {
            s32 a_ = s_[0];
            s32 b_ = s_[1];
            n_--;
            d_[0] = a_;
            d_[1] = b_;
            s_ += 2;
            d_ += 2;
        } while (n_ > 0);
    }
#elif KT == 4
    {
        s32 *d_ = (s32 *)&tbl;
        s32 *s_ = (s32 *)&D_0044B750;
        s32 n_ = 4;
        do {
            s32 a_ = s_[0];
            n_--;
            {
                s32 b_ = s_[1];
                d_[0] = a_;
                d_[1] = b_;
                s_ += 2;
                d_ += 2;
            }
        } while (n_ > 0);
    }
#else
    {
        s32 i_;
        for (i_ = 0; i_ < 8; i_++) ((s32 *)&tbl)[i_] = ((s32 *)&D_0044B750)[i_];
    }
#endif
    f20 = 0.25f * *(f32 *)D_0045B080;
#if KE
    for (e = ents, i = 0; i < cnt; i++, e++) {
#else
    for (i = 0, e = ents; i < cnt; i++, e++) {
#endif
        o = ((u8 *)ObjRecGetLiveObject_1c4a90(sys, ((short)CharaGetId_214a80(e->obj))));
        *(u128 *)&pos = *(u128 *)(o + 0x180);
#if KF == 2
        {
            f32 r_ = ModelObjGetScaledHeight_23b110(o);
            pos.y = pos.y + (r_ + f20);
        }
#elif KF == 3
        pos.y = ModelObjGetScaledHeight_23b110(o) + f20 + pos.y;
#elif KF == 4
        pos.y = pos.y + ModelObjGetScaledHeight_23b110(o) + f20;
#elif KF == 5
        {
            f32 r_ = ModelObjGetScaledHeight_23b110(o) + f20;
            pos.y += r_;
        }
#elif KF == 6
        {
            f32 r_ = ModelObjGetScaledHeight_23b110(o);
            r_ += f20;
            pos.y += r_;
        }
#elif KF == 7
        {
            f32 k_ = f20;
            pos.y += ModelObjGetScaledHeight_23b110(o) + k_;
        }
#elif KF == 8
        pos.y = pos.y + (f20 + ModelObjGetScaledHeight_23b110(o));
#elif KF == 9
        pos.y += ModelObjGetScaledHeight_23b110(o) - -f20;
#elif KF
        pos.y += f20 + ModelObjGetScaledHeight_23b110(o);
#else
        pos.y += ModelObjGetScaledHeight_23b110(o) + f20;
#endif
        if (ProjectToScreenOffset_15d160(&scr, &pos) == 0) continue;
        s = D_0047D83C * e->val;
        a = 1.0f;
        if (!(s <= D_0047D858)) a = (D_0047D83C - s) / D_0047D858;
        if (!(s <= D_0047D1FC)) s = D_0047D1FC;
        s = Sinf_128fd0(s);
        scr.y -= (s32)(16.0f * (8.0f + 32.0f * s));
        GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, (s32)(128.0f * a));
        w = TexelToUVFixed_205e20(tbl.c[e->type].a);
        GsPktSetUVFixed_13ed90(pk, w, TexelToUVFixed_205e20(tbl.c[e->type].b));
        GsPktSetXYZ_13ef10(pk, scr.x - (tbl.c[e->type].c << 3), scr.y - (tbl.c[e->type].d << 3), scr.z);
        q = &tbl.c[e->type];
        w = TexelToUVFixed_205e20(q->a + q->c);
        GsPktSetUVFixed_13ed90(pk, w, TexelToUVFixed_205e20(q->b + q->d));
        GsPktSetXYZ_13ef10(pk, scr.x + (tbl.c[e->type].c << 3), scr.y + (tbl.c[e->type].d << 3), scr.z);
    }
    GsPktClose_13f5b0(pk);
    DrawListEndPrim_141a20(gp);
}
