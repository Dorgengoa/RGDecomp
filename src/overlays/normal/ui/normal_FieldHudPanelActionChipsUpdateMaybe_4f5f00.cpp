#include "types.h"
/* normal 0x004F5F00 -- retargets the two "recommended action" chips shown on
 * each party row of the field menu.  For every live member it walks the
 * D_005262A0 action table asking the member (virtual slot 101) which entries
 * it can perform, keeps at most two ids in `sel`, and then either seeds the
 * row's chip, leaves a matching one alone, or rotates to the other candidate
 * once the row's stickiness counter reaches 0x14 frames.
 *
 * `lw $25,0($16) / lw $25,0x19C($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x19C-8)/4 = 101.
 * `daddiu $6,$0,1` for the "already selected" flag is a C++ `bool`.
 * The `dsll32/dsra32 ..,16` pairs are s32 locals with explicit `(s16)` casts,
 * not s16 locals -- an s16 local is a measured null on this image. */

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
    virtual s32  has(s32 k);                       /* slot 101 -> vtable +0x19C */
};

typedef struct Act  { s16 f00; s16 f02; } Act;
typedef struct Chip { u8 pad000[0x354]; s16 f00; s16 f02; } Chip;
typedef struct Row  { s16 f00; s16 f02; } Row;
typedef struct Win  { u8 pad000[0x354]; Row chip[8]; } Win;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern Act D_005262A0[];

extern s16 D_004804A0;            /* gp - 0x4CD0 */
extern s16 D_004804A2;            /* gp - 0x4CCE */

extern "C" {

extern Root *func_1FEDE0(void);
extern void  func_28F9D0(Win *w, u16 id, s16 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28FC30(Win *w, u16 id, s32 a, s32 b, s32 c);
extern void  func_290010(Win *w, u16 id, s32 a, s32 b);
extern Ent  *func_3C2FB0(s32 w, s32 k);
extern s32   normal_FieldHudPartyRowCount_4f9c50(Win *w);

}

extern "C" void normal_FieldHudPanelActionChipsUpdateMaybe_4f5f00(Win *p)
{
    s16   sel[2];
    s32   i;
    s32   j;
    s32   cnt;
    Ent  *e;
    Root *t;
    s32   n;
    s32   v;
    s32   q;
    u16   id;
    u16   id2;
    s16  *cur;
    Chip *c;
    s16  *pn;
    bool  found;

    t = func_1FEDE0();
    if (t == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50(p);
    for (i = 0; i < n; i++) {
        e = func_3C2FB0(t->f18, i);
        if (e == 0) {
            continue;
        }
        j = 0;
        cnt = 0;
        sel[0] = D_004804A0;
        sel[1] = D_004804A2;
        while ((v = D_005262A0[(s16)j].f00) > 0) {
            if (e->has(v) != 0) {
                sel[(s16)cnt] = (s16)j;
                cnt = (s16)(cnt + 1);
                if (cnt >= 2) {
                    break;
                }
            }
            j = (s16)(j + 1);
        }
        id = (u16)(i + 0x1E);
        func_290010(p, id, 1, -1);
        if ((s16)cnt == 0) {
            p->chip[i].f00 = 0;
            p->chip[i].f02 = -1;
            func_290010(p, id, 0, -1);
        } else if ((s16)cnt > 0) {
            cur = &p->chip[i].f02;
            if (p->chip[i].f02 == -1) {
                *cur = sel[0];
            } else {
                found = false;
                for (q = 0; q < 2; q++) {
                    if (p->chip[i].f02 == sel[q]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    c = (Chip *)((s32)p + (u32)i * 4);
                    pn = &c->f00;
                    c->f00 = (s16)(c->f00 + 1);
                    if ((s16)c->f00 >= 0x14) {
                        if ((s16)cnt >= 2) {
                            *cur = sel[q ^ 1];
                        } else {
                            *cur = sel[0];
                        }
                        *pn = 0;
                    }
                } else {
                    ((Chip *)((u8 *)p + (u32)i * 4))->f00 = 0;
                    *cur = sel[0];
                }
            }
            id2 = (u16)(i + 0x21);
            func_28FC30(p, id2, 0x12, 0x12, 0);
            func_28F9D0(p, id2, D_005262A0[*cur].f02, 0x9E, 0x12, 0x12, 0);
            func_290010(p, id2, 1, -1);
        }
    }
}
