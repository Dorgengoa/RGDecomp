/* rgp:protos */
#line 1
#include "types.h"

struct Chr {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v16() { return VCM0(s32, 0x48); }
};

struct It {
    s32 a;
    s16 n;
    s16 b;
};

struct Arg {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

struct Ent {
    s16 id;
    u8 flag;
    u8 kind;
    s32 val;
    s32 name;
};

struct Rect {
    s16 x0;
    s16 y0;
    s16 x;
    s16 y;
    s16 u;
    s16 pad;
    s16 w;
    s16 h;
};

struct Cell {
    s16 x0;
    s16 y0;
    s16 x;
    s16 y;
    s16 u;
    s16 pad;
    s16 w;
    s16 h;
    u8 padx[0xC];
    u16 flags;
    u16 pad1e;
};

struct Txt {
    s32 a;
    s32 b;
    s64 id;
    u8 pad10[6];
    s16 w;
    s16 h;
};

struct Col {
    s32 a;
    s32 name;
    s32 b;
    u32 color;
};

struct Wnd {
    u8 pad0[0x20];
    void *a;
    void *b;
    void *c;
};

struct Pair {
    s16 key;
    s16 idx;
};

struct Self {
    u8 pad0[0x5C];
    s32 ui;
    u8 pad60[0x10];
    s16 cnt;
};

extern "C" {
u8 *GetGameData_1fede0();
s32 PartyGetSlotChara_3c2fb0(s32, s32);
void CharaAbilityViewCtor_3a8180(Arg *, s32, s32, s32);
void IterInit_370170(It *, Arg *, int, int);
Ent * IterSeek_36fff0(It *, s32, int, int);
Ent *IterNext_370040(It *);
Wnd *UiFindWidget_290460(s32, u16);
void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
Chr *CharaFindSlotByRecId_3ad390(s32, s16);
s32 EquipSlotGetScaledCost_3a05c0(Chr *);
s32 AbilityDataGetCost_3f5ca0(Ent *);
extern Pair D_00462BC0[9];
extern s16 D_00462BA0[];
extern f32 D_0047D288 __attribute__((section(".sdata")));
}

extern "C" s32 MenuTacticsAbilityListRefreshMaybe_355d20(Self *self, s32 key, s32 base)
{
    s32 h;
    Arg arg __attribute__((aligned(16)));
    It it __attribute__((aligned(16)));
    s32 cnt;
    Ent *ent;
    Wnd *w;
    Cell *rects;
    Cell *cells;
    s32 i;
    Cell *r1;
    Txt *t;
    Col *c;
    Chr *chr;
    Cell *r;
    Arg arg2 __attribute__((aligned(16)));
    u16 id;
    It it2 __attribute__((aligned(16)));
    Ent *e2;
    Cell *cl;
    Cell *p;
    s32 o;
    u16 *f;
    s32 j;

    {
        s32 t = PartyGetSlotChara_3c2fb0(*(s32 *)(GetGameData_1fede0() + 0x18), key);
        h = t;
        if (t == 0) {
            return 0;
        }
        CharaAbilityViewCtor_3a8180(&arg, t, 3, -1);
    }
    IterInit_370170(&it, &arg, 0, 0);
    cnt = it.n;
    self->cnt = cnt;
    ent = IterSeek_36fff0(&it, base, 0, 0);
    w = UiFindWidget_290460(self->ui, 0xD3);
    if (w == 0) {
        return 0;
    }
    rects = (Cell *)w->a;
    if (rects == 0) {
        return 0;
    }
    w = UiFindWidget_290460(self->ui, 0xD5);
    if (w == 0) {
        return 0;
    }
    cells = (Cell *)w->a;
    if (cells == 0) {
        return 0;
    }
    UiSetWidgetColor_2905b0(self->ui, 0xD5, D_0047D288, D_0047D288, D_0047D288, 1.0f);
    for (i = 0; i < 6; i++) {
        id = i + 0xCA;
        w = UiFindWidget_290460(self->ui, id);
        if (w == 0) {
            return 0;
        }
        r1 = (Cell *)w->a;
        if (r1 == 0) {
            return 0;
        }
        t = (Txt *)w->b;
        if (t == 0) {
            return 0;
        }
        c = (Col *)w->c;
        if (c == 0) {
            return 0;
        }
        if (i < cnt && ent != 0) {
            c->name = ent->name;
            r1->w = 0x14;
            r1->x = 0x14;
            r1->h = 0x10;
            r1->y = 0x10;
            chr = CharaFindSlotByRecId_3ad390(h, ent->id);
            if (chr != 0) {
                t->id = EquipSlotGetScaledCost_3a05c0(chr);
            } else {
                t->id = AbilityDataGetCost_3f5ca0(ent);
            }
            t->w = 0xC;
            t->h = 0x10;
            r = &rects[(u32)i];
            r->h = 0x10;
            r->w = 0x10;
            r->y = 0x10;
            r->x = 0x10;
            if (ent->flag != 0) {
                r1->w = 0;
                r1->h = 0;
                t->w = 0;
                t->h = 0;
            }
            CharaAbilityViewCtor_3a8180(&arg2, h, 3, -1);
            IterInit_370170(&it2, &arg2, 0, 0);
            e2 = IterSeek_36fff0(&it2, base + i, 0, 0);
            if (e2 == 0) {
                return 0;
            }
            chr = CharaFindSlotByRecId_3ad390(h, e2->id);
            if (chr != 0) {
                if (chr->v16() != 0) {
                    o = i << 5;
                    r->u = 0x60;
                    c->color = 0xFF303030;
                    UiSetWidgetColor_2905b0(self->ui, id, 1.0f, 1.0f, 1.0f, 1.0f);
                    ((Cell *)((u8 *)cells + o))->flags |= 8;
                } else {
                    o = i << 5;
                    r->u = 0x70;
                    c->color = 0xFF202020;
                    { f32 k_ = *(const f32 *)&D_0047D288; UiSetWidgetColor_2905b0(self->ui, id, k_, k_, k_, 1.0f); }
                    if (((Cell *)((u8 *)cells + o))->flags & 8) {
                        ((Cell *)((u8 *)cells + o))->flags ^= 8;
                    }
                }
            }
            cl = (Cell *)((u8 *)cells + (i << 5));
            cl->w = 0x18;
            cl->x = 0x18;
            cl->h = 0x17;
            cl->y = 0x17;
            for (j = 0; j < 9; j++) {
                if (e2->kind == D_00462BC0[j].key) {
                    cl->u = D_00462BA0[D_00462BC0[j].idx];
                }
            }
        } else {
            c->name = 0;
            r1->h = 0;
            r1->w = 0;
            r1->y = 0;
            r1->x = 0;
            t->h = 0;
            t->w = 0;
            rects[i].h = 0;
            rects[i].w = 0;
            rects[i].y = 0;
            rects[i].x = 0;
            cells[i].h = 0;
            cells[i].w = 0;
            cells[i].y = 0;
            cells[i].x = 0;
        }
        ent = IterNext_370040(&it);
    }
    return 1;
}
