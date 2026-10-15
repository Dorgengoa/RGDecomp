#include "types.h"

typedef struct Arg {
    s32 type;
    s32 val;
} Arg;

typedef struct Lnk {
    struct Lnk *next;
    struct Lnk *prev;
    s32 x8;
    s32 xC;
} Lnk;

typedef struct List {
    Lnk *head;
    s32 x4;
    s32 x8;
} List;

typedef struct Base {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
} Base;

typedef struct Obj {
    Lnk lnk;
    Base base;
    u8 pad2C[0x34];
    u8 x60[0xE0];
    void **vt;
    u8 pad144[0xC];
} Obj;

typedef struct Root {
    u8 pad0[0x60];
    List list;
} Root;

typedef struct Ctx {
    Root *root;
    s32 cnt;
    s32 heap;
} Ctx;

typedef struct Game {
    u8 pad0[0x18];
    s32 x18;
} Game;

class Ent {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 Kind();
};

class VObj {
public:
    u8 data[0x140];
    virtual void Init();
};

extern "C" {
extern char *SlotGetInt_15f720(Arg *);
extern s32 VariantGetInt_15f780(Arg *);
extern s32 EventCastTypeFromName_2502e0(char *);
extern void MemStackAlign64_14d8e0(s32);
extern void *MemStackNew_14e230(s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern void HeadLookInit_1c5c50(void *);
extern void EventCastRecordInit_24e080(void *);
extern s32 EventCastResolveEquipNameMaybe_24fd10(char *, char *, s32 *, s32 *);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneGetEventSoundPath_1d14f0(s32, char *, s32);
extern char *InsectBattleBuildNpcPath_3195b0(s32);
extern void EventCastRecordSetMaybe_24e060(Base *, char *, char *, s32, char *);
extern void EventCastRecordSetCharaMaybe_24e040(Base *, char *, char *, s32, char *, s32, s32);
extern Game *GetGameData_1fede0(void);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Ent *PartyGetMemberChara_3c2420(s32, s32);
extern s32 CharaIdMakeChrPath_2501d0(s32, char *);
extern u32 strlen(const char *);
extern char *strncpy(char *, const char *, u32);
extern s32 strcmp(const char *, const char *);
extern s32 atoi(const char *);
extern Ctx *D_00481F54;
extern void *D_004714A8[];
extern char D_0045EBC0[];
extern char D_0045EBD0[];
extern char D_0045EBF0[];
extern char D_0044CDF0[];
extern char D_0044CE10[];
extern char D_0044CE30[];
}

#define DUP(d, s) { MemStackAlign64_14d8e0(heap); if ((d = (char *)MemStackNew_14e1b0(strlen(s) + 1, heap)) != 0) { strncpy(d, s, strlen(s) + 1); } }
static inline Base *NewObj(Ctx *c, s32 heap) {
    s32 cnt = c->cnt;
    List *list = &c->root->list;
    Obj *o;
    Lnk *p;
    MemStackAlign64_14d8e0(heap);
    o = (Obj *)MemStackNew_14e230(0x150, heap);
    if (o != 0) {
        o->vt = D_004714A8;
        HeadLookInit_1c5c50(o->x60);
        EventCastRecordInit_24e080(&o->base);
        ((VObj *)o)->Init();
    }
    if (o == 0) {
        return 0;
    } else {
        o->lnk.xC = cnt;
        o->lnk.x8 = 0;
        list->x4 = 0;
        list->x8 = 0;
        p = list->head;
        if (p != 0) {
            while (p != 0) {
                if (p->next == 0) {
                    break;
                }
                p = p->next;
            }
            p->next = &o->lnk;
            if (o != 0) {
                o->lnk.prev = p;
            }
        } else {
            list->head = &o->lnk;
        }
        return &o->base;
    }
}

typedef struct Str19 {
    char c[0x13];
} Str19;

extern "C" s32 EventCastCmdObject_24d420(Arg *a) {
    s32 v28C;
    s32 v288;
    char buf200[0x88];
    char buf180[0x80];
    char buf160[0x20];
    char buf140[0x20];
    char buf120[0x20];
    char bufA0[0x80];

    if (a[1].type == 0) {
        Ctx *c;
        char *name;
        char *s2;
        char *t;
        char *s4;
        s32 type;
        s32 heap;
        Base *res;
        char *d1;
        s32 r;
        char *d2;
        char *d3;

        name = SlotGetInt_15f720(a++);
        s2 = SlotGetInt_15f720(a++);
        t = SlotGetInt_15f720(a++);
        s4 = SlotGetInt_15f720(a);
        type = EventCastTypeFromName_2502e0(t);
        if (type == 0) {
            return 0;
        }
        c = D_00481F54;
        heap = c->heap;
        res = NewObj(c, heap);
        if (res == 0) {
            return 0;
        }
        DUP(d1, name);
        r = EventCastResolveEquipNameMaybe_24fd10(s2, buf200, &v288, &v28C);
        if (r > -1) {
            MemStackAlign64_14d8e0(heap);
            if ((d2 = (char *)MemStackNew_14e1b0(strlen(buf200) + 1, heap)) != 0) {
                strncpy(d2, buf200, strlen(buf200) + 1);
                res->x10 = r;
                res->x14 = v28C;
                res->x18 = v288;
            }
        } else if (type == 9) {
            if (!(GameSceneGetEventSoundPath_1d14f0(GetCurrentScene_1f5be0(), buf180, atoi(s2)) & 0xFF)) {
                return 0;
            }
            DUP(d2, buf180);
        } else if (strcmp(s2, D_0045EBC0) == 0) {
            t = InsectBattleBuildNpcPath_3195b0(1);
            *(Str19 *)buf160 = *(Str19 *)D_0044CDF0;
            if (t == 0) {
                t = buf160;
            }
            DUP(d2, t);
        } else if (strcmp(s2, D_0045EBD0) == 0) {
            t = InsectBattleBuildNpcPath_3195b0(0);
            *(Str19 *)buf140 = *(Str19 *)D_0044CE10;
            if (t == 0) {
                t = buf140;
            }
            DUP(d2, t);
        } else if (strcmp(s2, D_0045EBF0) == 0) {
            t = InsectBattleBuildNpcPath_3195b0(1);
            *(Str19 *)buf120 = *(Str19 *)D_0044CE30;
            if (t == 0) {
                t = buf120;
            }
            DUP(d2, t);
        } else {
            DUP(d2, s2);
        }
        DUP(d3, s4);
        EventCastRecordSetMaybe_24e060(res, d1, d2, type, d3);
        D_00481F54->cnt++;
    } else {
        Ctx *c;
        char *name;
        s32 idx;
        char *t;
        char *s4;
        s32 type;
        Game *g;
        s32 n;
        s32 i;
        Ent *e;
        s32 v;
        s32 heap;
        Base *res;
        char *d1;
        char *d3;
        char *d2;

    name = SlotGetInt_15f720(a++);
    idx = VariantGetInt_15f780(a++);
    t = SlotGetInt_15f720(a++);
    s4 = SlotGetInt_15f720(a);
    type = EventCastTypeFromName_2502e0(t);
    if (type == 0) {
        return 0;
    }
    if (idx < 0) {
        g = GetGameData_1fede0();
        { s32 t_n = PartyCountMembers_3c2010(g->x18, 1, 1); n = t_n; }
        for (i = 0; i < n; i++) {
            e = PartyGetMemberChara_3c2420(g->x18, i);
            v = e->Kind();
            if (v == 0x2AF9) {
                continue;
            }
            if (idx == -1) {
                idx = v;
                break;
            }
            idx++;
        }
    }
    c = D_00481F54;
    heap = c->heap;
    res = NewObj(c, heap);
    if (res == 0) {
        return 0;
    }
    DUP(d1, name);
    DUP(d3, s4);
    if (CharaIdMakeChrPath_2501d0(idx, bufA0) != 0) {
        DUP(d2, bufA0);
    }
    EventCastRecordSetCharaMaybe_24e040(res, d1, d2, type, d3, 0, idx);
    D_00481F54->cnt++;
    }
    return 1;
}
