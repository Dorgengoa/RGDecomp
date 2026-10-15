#include "types.h"
/* normal 0x004F4C10 -- per-party-member row tint on panel `w`.  For each of the
 * normal_FieldHudPartyRowCount_4f9c50 rows it takes the 0xB widget of the i*7 block, and when
 * the row's 64-bit 0x08 count is positive tints the 0x6 widget white only if
 * the member's slot-58/slot-72 ratio clears 0.2, otherwise greys it and fades.
 *
 * C++ virtual: 0xF0 -> slot 58, 0x128 -> slot 72.
 * `sll 3 / subu` is `i * 7`, written ONCE and reused by both widget ids. */
class Ent {
public:
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
    virtual s32 s058();
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
    virtual s32 s072(s32 a);
};

typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Row  { u8 pad00[8]; s64 f08; } Row;
typedef struct Hold { u8 pad00[0x24]; Row *f24; } Hold;
typedef struct Pan  { u8 pad000[0x378]; s16 f378; } Pan;

extern "C" {
extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047DA64;          /* gp - 0x770C */
extern f32   D_0047DA68;          /* gp - 0x7708 */

extern Ctx  *func_1FEDE0(void);
extern Hold *func_290460(Pan *p, u16 id);
extern Ent  *func_3C2420(s32 w, s32 i);
extern void  func_2904E0(Pan *p, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  func_2905B0(Pan *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern s32   normal_FieldHudPartyRowCount_4f9c50(Pan *p);
}

extern "C" void normal_FieldHudPanelTintUpdateMaybe_4f4c10(Pan *w)
{
    Ctx  *c;
    Hold *h;
    Row  *row;
    s32   n;
    s32   i;
    Ent  *e;
    s32   base;
    u16   id;
    f32   r;

    if (w->f378 == 0) {
        return;
    }
    c = func_1FEDE0();
    if (c == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50(w);
    for (i = 0; i < n; i++) {
        base = i * 7;
        h = func_290460(w, (u16)(base + 0xB));
        if (h == 0) {
            continue;
        }
        row = h->f24;
        if (row == 0) {
            continue;
        }
        e = func_3C2420(c->f18, i);
        if (e == 0) {
            continue;
        }
        r = (f32)e->s058() / (f32)e->s072(1);
        id = (u16)(base + 6);
        if (row->f08 > 0) {
            if (r > D_0047D5D0) {
                func_2904E0(w, id, 1.0f, 1.0f, 1.0f, 1.0f, D_0047DA64);
            }
        } else {
            func_2904E0(w, id, D_0047D248, D_0047D248, D_0047D248, 1.0f, D_0047DA68);
            func_2905B0(w, id, D_0047D248, D_0047D248, D_0047D248, -1.0f);
        }
    }
}
