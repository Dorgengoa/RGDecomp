#pragma optimization_level 3
#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;

class Chr {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v30() { VCM0(void, 0x80); }
    
    
    
    
    
    
    
    
    void v39(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
};

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    s32 a;
    f32 key;
} Node;

typedef struct {
    Node *prev;
    Node *next;
} Hdr;

typedef struct {
    s32 size;
    Hdr hdr;
} List;

class It {
public:
    Node *volatile p;
    Node &operator*() { return *p; }
    Node *operator->() { return &**this; }
    void next() { p = p->next; }
    bool operator==(It &o) { return p == o.p; }
    bool operator!=(It &o) { return p != o.p; }
};

typedef struct {
    s32 a;
    f32 key;
} Pair;

typedef struct {
    u8 pad0[0x18E];
    s16 f18E;
} PInfo;

typedef struct {
    u8 pad0[0x18];
    PInfo *f18;
} Party;

typedef struct {
    u8 pad0[0x4344];
    s32 f4344;
} Game;

typedef struct {
    u8 pad0[0xE0];
    u8 fE0[4];
} Self;

extern "C" {
Game *GetCurrentScene_1f5be0(void);
Chr *ObjRecGetLiveObject_1c3bc0(Game *, s32);
void Vec2ListCtorMaybe_2ed800(List *);
void ListEraseRange_2ed650(It *, List *, It *, It *);
void Vec2ListInsertMaybe_2ed700(It *, List *, It *, Pair *);
Party *GetGameData_1fede0(void);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, Vec4 *);
s32 DListGetHead_42ea60(u8 *);
s32 DListGetNext_42eb30(s32);
s32 EvDoorObjGetSidePoint_3039a0(s32, Vec4 *, Vec4 *, s32);
f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
s32 GetDrawCtx_15de80(void);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void EvDoorObjDrawCursor_303b30(s32);
extern f32 D_0047EF50;
extern f32 D_0047EF54;
extern f32 D_0047EF58;
extern f32 D_0047EF5C;
}

extern "C" void EventObjMgrDrawDoorCursorsMaybe_2e7e10(Self *self) {
    It itAC __attribute__((aligned(16)));
    It itA8 __attribute__((aligned(16)));
    It itA4 __attribute__((aligned(16)));
    It itA0 __attribute__((aligned(16)));
    It r9C __attribute__((aligned(16)));
    It r98 __attribute__((aligned(16)));
    It i94 __attribute__((aligned(16)));
    It i90 __attribute__((aligned(16)));
    It r8C __attribute__((aligned(16)));
    It i88 __attribute__((aligned(16)));
    It i84 __attribute__((aligned(16)));
    It i80 __attribute__((aligned(16)));
    It r7C __attribute__((aligned(16)));
    It i78 __attribute__((aligned(16)));
    It i74 __attribute__((aligned(16)));
    List list __attribute__((aligned(16)));
    Pair pair __attribute__((aligned(16)));
    Vec4 v50 __attribute__((aligned(16)));
    Vec4 color __attribute__((aligned(16)));
    Vec4 v30 __attribute__((aligned(16)));
    Game *g;
    Chr *ch;
    Party *p;
    s32 q;
    s32 it;
    bool less;

    g = GetCurrentScene_1f5be0();
    ch = ObjRecGetLiveObject_1c3bc0(g, g->f4344);
    if (ch == 0) {
        return;
    }
    ch->v39(&v50);
    Vec2ListCtorMaybe_2ed800(&list);
    i90.p = (Node *)&list.hdr;
    i94.p = list.hdr.next;
    ListEraseRange_2ed650(&r98, &list, &i94, &i90);
    color.x = D_0047EF50;
    color.y = D_0047EF54;
    color.z = D_0047EF58;
    color.w = D_0047EF5C;
    p = GetGameData_1fede0();
    q = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), p->f18->f18E);
    if (q != 0) {
        CharaGetPos_2388a0(q, &color);
    }
    for (it = DListGetHead_42ea60(self->fE0); it != 0; it = DListGetNext_42eb30(it)) {
        if (EvDoorObjGetSidePoint_3039a0(it + 0x10, &v30, &color, -1) != 0) {
            pair.a = it + 0x10;
            pair.key = VecDistSq_1cb3c0(&v30, &v50);
            itA8.p = (Node *)&list.hdr;
            itAC.p = list.hdr.next;
            for (;;) {
                if (itAC->key < pair.key) {
                    i80 = itAC;
                    Vec2ListInsertMaybe_2ed700(&r9C, &list, &i80, &pair);
                    break;
                }
                if (itAC.p == (Node *)&list.hdr) {
                    break;
                }
                itAC.next();
            }
        }
    }
    if (list.size != 0) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x32B, 1.0f);
        itA4.p = list.hdr.next;
        for (itA0.p = (Node *)&list.hdr; itA4 != itA0; itA4.next()) {
            EvDoorObjDrawCursor_303b30(itA4->a);
        }
    }
    i84.p = (Node *)&list.hdr;
    i88.p = list.hdr.next;
    ListEraseRange_2ed650(&r8C, &list, &i88, &i84);
    i74.p = (Node *)&list.hdr;
    i78.p = list.hdr.next;
    ListEraseRange_2ed650(&r7C, &list, &i78, &i74);
}
