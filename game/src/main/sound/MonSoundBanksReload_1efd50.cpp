#include "types.h"

typedef struct Slot {
    s16 x0;
    s16 x2;
    s16 x4;
    u8 pad6;
    u8 state;
    u8 pad08[0x5E];
    u8 on : 1;
    u8 rest : 7;
    u8 pad67;
} Slot;

typedef struct Def {
    s16 x0;
    u8 pad02[0xE];
    s32 x10;
} Def;

typedef struct Res {
    u8 pad[0x20];
    Def *def;
} Res;

class Table {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Res * find(s16 id) { return VCM(Res *, (void *, s16), 0x70, id); }
};

typedef struct Sub64 {
    u8 pad[0xC];
    Table *table;
} Sub64;

typedef struct Sys {
    u8 pad[0x64];
    Sub64 *sub;
} Sys;

typedef struct Actor {
    u8 pad[0x4FC];
    s32 x4FC;
} Actor;

typedef struct Ent {
    u8 pad[0x20];
    s32 x20;
} Ent;

typedef struct Msg {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
    char *text;
    s32 f7;
    s32 f8;
    s32 f9;
    s32 f10;
    s32 f11;
    s32 f12;
    s32 f13;
} Msg;

extern "C" {
extern char D_0045B760[];
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetCharaDataMgr_1fdb70(void);
extern Sys *GetWorldDataMgr_1fedf0(void);
extern Actor *ObjRecGetLiveObject_1c4a90(s32 a, s32 b);
extern void SoundBankPartFree_1b9b00(s32 h);
extern Ent *CharaDataFindNode_1ed6d0(s32 a, s32 id, s32 b, s32 c);
extern void Sprintf_1343b8(char *dst, const char *fmt, s32 x);
extern void CharaDataLoadSubRecById_1eda70(s32 a, Msg *m);
}

extern "C" void MonSoundBanksReload_1efd50(Slot *slots)
{
    char text[128] __attribute__((aligned(16)));
    s32 seen[128] __attribute__((aligned(16)));
    Msg m __attribute__((aligned(16)));
    Slot *p;
    s32 i;
    s32 ctx;
    s32 hud;
    Sys *sys;
    s32 count;
    s32 j;
    s32 kind;
    Actor *a;
    Ent *e;
    Res *r;
    Def *d;

    for (i = 0, p = slots; i < 32; i++, p++) {
        if (p->state == 3) {
            return;
        }
    }
    ctx = GetCurrentScene_1f5be0();
    hud = GetCharaDataMgr_1fdb70();
    sys = GetWorldDataMgr_1fedf0();
    count = 0;
    p = slots;
    for (i = 0; i < 32; i++, p++) {
        if (p->state != 2) {
            continue;
        }
        p->on = 1;
        for (j = 0; j < count; j++) {
            s32 *s = &seen[j];
            if (*s == p->x4) {
                break;
            }
        }
        if (j < count) {
            continue;
        }
        kind = p->x2;
        seen[count++] = p->x4;
        a = ObjRecGetLiveObject_1c4a90(ctx, p->x0);
        if (a != 0) {
            SoundBankPartFree_1b9b00(a->x4FC);
            a->x4FC = -1;
        } else {
            e = CharaDataFindNode_1ed6d0(hud, p->x4, 5, 5);
            if (e != 0 && e->x20 != -1) {
                SoundBankPartFree_1b9b00(e->x20);
            }
        }
        r = sys->sub->table->find(kind);
        if (r == 0) {
            continue;
        }
        d = r->def;
        if (d == 0) {
            continue;
        }
        m.f0 = -1;
        m.f1 = -1;
        m.f2 = -1;
        m.f3 = -1;
        m.f4 = -1;
        m.f5 = -1;
        m.text = 0;
        m.f7 = -1;
        m.f8 = 0;
        m.f9 = -1;
        m.f10 = 0;
        m.f11 = 0;
        m.f12 = -1;
        m.f13 = 0;
        m.f0 = d->x0;
        m.f1 = 1;
        m.f2 = 5;
        m.f3 = 5;
        m.f5 = d->x0;
        m.f9 = 5;
        m.text = text;
        Sprintf_1343b8(text, D_0045B760, d->x10);
        CharaDataLoadSubRecById_1eda70(hud, &m);
    }
}
