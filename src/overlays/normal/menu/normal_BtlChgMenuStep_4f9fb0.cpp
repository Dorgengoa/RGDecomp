#include "types.h"
/* normal 0x004F9FB0 -- the field menu's per-frame driver.  Bails while the
 * 0x484464 lock is set; otherwise re-arms the 0x47 page, stamps the two pad
 * bytes into the context, and runs the 0x48444C phase machine (0/1 = open or
 * re-page a member, 2 = request close).  The tail re-lays the 0x46 banner from
 * whether a sub-page is up and fires the close hook.
 *
 * TWO `lw $25,0($2) / lw $25,0xF0($25) / jalr $25` sites -> C++ virtual,
 * vptr 0, slot (0xF0-8)/4 = 58.
 * The phase machine is a `switch` whose cases are in SOURCE order 0,1,2 while
 * the compare chain runs 2,1,0, and case 0 FALLS THROUGH into case 1.
 * `addiu $2,$28,-0x4C9E` with the SAME scaled index is the .y half of the same
 * table, but retail materialises BOTH bases, so it is spelled as two objects.
 * The 4-iteration tint loop is BOTTOM-tested -- write `do {} while`. */

struct Ent {
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
    virtual void s045();
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
    virtual s32 count();   /* slot 58 -> vtable +0xF0 */
};

typedef struct Pair { s16 x; s16 y; } Pair;
typedef struct Ctx  { u8 pad000[0x43C]; s16 f43C; u8 pad43E[0x44C - 0x43E];
                      s16 f44C; s16 f44E; u8 pad450[4]; u8 f454; u8 f455; } Ctx;
typedef struct Top  { u8 pad00[0x18]; s32 f18; } Top;

extern const u8 D_00527020[];
extern const u8 D_00527820[];

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern s32   D_00484448;          /* gp - 0xD28 */
extern s32   D_0048444C;          /* gp - 0xD24 */
extern s32   D_00484460;          /* gp - 0xD10 */
extern s16   D_00484464;          /* gp - 0xD0C */
extern s16   D_00484468;          /* gp - 0xD08 */
extern s32   D_0048446C;          /* gp - 0xD04 */
extern u8    D_00484470;          /* gp - 0xD00 */
extern Pair  D_004804D0[2];       /* gp - 0x4CA0, declared SHORT for small data */
extern Pair  D_004804D2[2];       /* gp - 0x4C9E, the .y half as its own object */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047DA6C;          /* gp - 0x7704 */
extern f32   D_0047DA70;          /* gp - 0x7700 */

extern "C" {

extern Top  *func_1FEDE0(void);
extern void  func_290690(const u8 *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F50(const u8 *w, s32 id, s32 x, s32 y, s32 k, f32 t);
extern void  func_291110(const u8 *w, s32 id, s32 c, s32 d);
extern void  func_2913A0(const u8 *w);
extern s32   func_3C2010(s32 a, s32 b, s32 c);
extern Ent  *func_3C2420(s32 a, s32 i);
extern Ent  *func_3C2820(s32 a);
extern void  normal_FieldHudPanelSelectRaise_4f4dc0(const u8 *w, s32 k);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *w, s32 k);
extern void  normal_FieldHudPanelsDim_4f4f80(const u8 *w, s32 k);
extern void  normal_BtlChgMenuClose_4f9d70(void);
extern void  normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870(void);
extern void  normal_BtlChgMenuPanelGlowMaybe_4faf20(s32 a, s32 b);
extern void  normal_BtlChgMenuCursorTrailMove_4fb110(const u8 *w, s16 a, s32 b);
extern u8    normal_BtlChgMenuOpenBurstUpdate_4fb280(const u8 *w);
extern void  normal_BtlChgPageUpdate_505e70(Ctx *p);
extern void  normal_BtlChgPageSetState_505f30(Ctx *p, s32 id);
extern s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern s32   normal_BtlChgPageGetCloseCode_505fb0(Ctx *p);
extern s32   normal_BtlChgPageIsActive_506000(Ctx *p);
extern void  normal_BtlChgPageStart_506030(Ctx *p, s32 k);

}

extern "C" void normal_BtlChgMenuStep_4f9fb0(u8 a, u8 b)
{
    Top *t;
    Ent *e;
    s32  n;
    s32  i;
    s32  idx;
    Ctx *c;
    s32  done;

    done = 0;
    t = func_1FEDE0();
    n = func_3C2010(t->f18, 1, 1);
    if (D_00484464 != 0) {
        return;
    }
    if (D_00484470 != 0) {
        normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870();
        e = func_3C2820(t->f18);
        if (e != 0 && e->count() > 0) {
            D_00484470 = 0;
            D_00484454->f44E = 0;
        }
    } else {
        func_291110(D_00527820, 0x47, 0, 1);
        D_00484454->f44E = 0;
    }
    if (normal_BtlChgMenuOpenBurstUpdate_4fb280(D_00527820) == 1) {
        D_00484454->f44C = 0;
    }
    c = D_00484454;
    c->f454 = a;
    c->f455 = b;
    switch (D_00484448) {
    case 1:
        switch (D_0048444C) {
        case 0:
            if (D_00484454->f454 == 0) {
                return;
            }
            D_0048444C = 1;
            /* fallthrough */
        case 1:
            if (normal_BtlChgPageIsActive_506000(D_00484454) == 0) {
                if (*(volatile s32 *)&D_00484460 < 0) {
                    D_00484460 = n - 1;
                }
                if (*(volatile s32 *)&D_00484460 >= n) {
                    D_00484460 = 0;
                }
                idx = *(volatile s32 *)&D_00484460;
                normal_BtlChgMenuCursorTrailMove_4fb110(D_00527820, D_004804D0[idx].x,
                                    D_004804D2[idx].x + 6);
                D_00484468 = 2;
                e = func_3C2420(t->f18, D_00484460);
                if (e != 0 && e->count() > 0) {
                    normal_BtlChgMenuPanelGlowMaybe_4faf20(D_00484460, 0);
                }
                normal_BtlChgPageStart_506030(D_00484454, D_00484460);
                normal_BtlChgPageSetState_505f30(D_00484454, 0x55F6);
                i = 0;
                do {
                    func_290690(D_00527820, (u16)(i + 1), 0.0f, D_0047DA6C,
                                -1.0f);
                    i++;
                } while (i < 4);
                normal_FieldHudPanelsDim_4f4f80(D_00527020, D_00484460);
                normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, D_00484460);
                normal_FieldHudPanelSelectRaise_4f4dc0(D_00527020, -1);
            }
            break;
        case 2:
            done = 1;
            D_0048444C = -1;
            break;
        }
        break;
    }
    func_2913A0(D_00527820);
    normal_BtlChgPageUpdate_505e70(D_00484454);
    if (normal_BtlChgPageIsActive_506000(D_00484454) != 0) {
        if (D_00484454->f43C != 0) {
            D_00484468 = 2;
            func_290F50(D_00527820, 0x46, -0x20, 0x78, 1, 10.0f);
            func_290690(D_00527820, 0x46, 0.0f, D_0047DA70, -1.0f);
        } else {
            func_290F50(D_00527820, 0x46, 0x12, 0x78, 1, 10.0f);
            func_290690(D_00527820, 0x46, 1.0f, D_0047D5D0, -1.0f);
            D_00484468 = 1;
        }
    } else {
        if (D_0048446C == 1) {
            func_290F50(D_00527820, 0x46, 0x12, 0x78, 1, 10.0f);
            func_290690(D_00527820, 0x46, 1.0f, D_0047D5D0, -1.0f);
            D_00484460 = normal_BtlChgPageGetMember_505f90(D_00484454);
        }
        D_00484468 = 1;
    }
    D_0048446C = normal_BtlChgPageIsActive_506000(D_00484454);
    if (normal_BtlChgPageGetCloseCode_505fb0(D_00484454) == 2) {
        done = 1;
    }
    if (done != 0) {
        normal_BtlChgMenuPanelGlowMaybe_4faf20(-1, 1);
        normal_BtlChgMenuClose_4f9d70();
    }
}
