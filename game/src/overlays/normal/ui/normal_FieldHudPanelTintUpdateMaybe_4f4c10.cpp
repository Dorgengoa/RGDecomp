/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s058() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s072(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
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

extern Ctx  *GetGameData_1fede0(void);
extern Hold *UiFindWidget_290460(Pan *p, u16 id);
extern Ent  *PartyGetMemberChara_3c2420(s32 w, s32 i);
extern void  UiFadeWidgetColor_2904e0(Pan *p, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  UiSetWidgetColor_2905b0(Pan *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern s32 normal_FieldHudPartyRowCount_4f9c50(void);
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
    c = GetGameData_1fede0();
    if (c == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        base = i * 7;
        h = UiFindWidget_290460(w, (u16)(base + 0xB));
        if (h == 0) {
            continue;
        }
        row = h->f24;
        if (row == 0) {
            continue;
        }
        e = PartyGetMemberChara_3c2420(c->f18, i);
        if (e == 0) {
            continue;
        }
        r = (f32)e->s058() / (f32)e->s072(1);
        id = (u16)(base + 6);
        if (row->f08 > 0) {
            if (r > D_0047D5D0) {
                UiFadeWidgetColor_2904e0(w, id, 1.0f, 1.0f, 1.0f, 1.0f, D_0047DA64);
            }
        } else {
            UiFadeWidgetColor_2904e0(w, id, D_0047D248, D_0047D248, D_0047D248, 1.0f, D_0047DA68);
            UiSetWidgetColor_2905b0(w, id, D_0047D248, D_0047D248, D_0047D248, -1.0f);
        }
    }
}
