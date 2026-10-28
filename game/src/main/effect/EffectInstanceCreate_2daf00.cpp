/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

class Sub {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v5C() { VCM0(void, 0x5C); }
};

class Obj {
public:
    u8 pad0[2];
    s16 x2;
    u8 pad4[4];
    s32 x8;
    s32 xC;
    s32 x10;
    u8 pad14[0x1C - 0x14];
    s32 x1C;
    u8 pad20[0x190 - 0x20];
    VC_VPTR_MEMBER; void v08() { VCM0(void, 0x8); }
    
    
    
    Sub * v18() { return VCM0(Sub *, 0x18); }
    void * v1C() { return VCM0(void *, 0x1C); }
    
    
    
    s32 v2C() { return VCM0(s32, 0x2C); }
    
    
    void v38(s32 a0) { VCM(void, (void *, s32), 0x38, a0); }
    void v3C(s32 a0) { VCM(void, (void *, s32), 0x3C, a0); }
    
    
    
    
    
    void v54(s32 a0) { VCM(void, (void *, s32), 0x54, a0); }
};

class Node {
public:
    Node *next;
    Node *prev;
    s32 x8;
    s32 id;
    Obj *obj;
    VC_VPTR_MEMBER; void v08() { VCM0(void, 0x8); }
};

struct Mgr {
    u8 pad0[0x28];
    s32 m28;
};

struct Self {
    Node *head;
    Node *cur;
    s32 done;
    s16 type;
    u8 padE[0x14 - 0xE];
    s16 x14;
    u8 pad16[0x80 - 0x16];
    s32 x80;
    u8 pad84[0x90 - 0x84];
    s32 x90;
    u8 pad94[0xA8 - 0x94];
    Mgr *mgr;
    s32 id;
    s32 xB0;
    s16 xB4;
    s16 xB6;
};

extern "C" {
s32 MemStackAllocQw_14d950(Mgr *, s32);
void MemStackReturnToOwnerMaybe_14dad0(Mgr *);
s32 MemStackHeapAlloc_14db10(Mgr *, s32, s32, s32);
void MemStackHeapFree_14dcb0(Mgr *, s32);
u8 *MemStackNew_14e230(s32, Mgr *);
void ScriptVmSetCmdTable_176ae0(void *, void *, s32);
void ScriptVmInit_176af0(void *, s32, s32, s32, s32, s32);
void ScriptVmCtor_176be0(void *);
void ModelObjExCopy_1aff40(s32, Sub *, Mgr *);
void Character2Ctor_1ef2d0(void *, int, int, int);
void EffectEntryReleaseNode_2da6c0(Self *, Obj *, int, int);
void EffectNodeStepScript_2dad50(Self *, Obj *);
void TargetRefCtorWrap_2db800(void *);
void EffectInstanceCtor_2db830(void *);
void TargetRefCtor_2e71f0(void *);
extern u8 D_00471670[0x400];
extern u8 D_004716D8[0x400];
extern u8 D_004716F0[0x400];
extern u8 D_00471760[0x400];
extern u8 D_004E8050[0x400];
s32 EffectInstanceCreate_2daf00(Self *self, s16 arg1, s32 arg2);
}

static inline s32 busy(Mgr *m)
{
    return m->m28 != 0;
}

#define BEGIN(s) \
    if ((s)->cur == 0) { \
        (s)->cur = (s)->head; \
        (s)->done = 0; \
    }

#define FINDID(s) { \
    Obj **rec; \
    s32 c9; \
    Node *c; \
    Node *nx; \
    BEGIN(s) \
    for (;;) { \
        c = (s)->cur; \
        if (c == 0) { \
            rec = 0; \
        } else { \
            rec = &c->obj; \
            nx = c->next; \
            (s)->cur = nx; \
            if (nx == 0) { \
                (s)->done = 1; \
            } \
        } \
        if (rec == 0) { \
            break; \
        } \
        if (*rec != 0 && (c9 = (*rec)->x8, (s)->id == c9)) { \
            (s)->id++; \
            (s)->cur = 0; \
            (s)->done = 0; \
            BEGIN(s) \
        } \
    } \
    (s)->cur = 0; \
    (s)->done = 0; \
}

#define APPEND(s, node, nid, slot) { \
    Node *p; \
    Node *t; \
    if (node == 0) { \
        slot = 0; \
    } else { \
        node->id = nid; \
        node->x8 = 0; \
        (s)->cur = 0; \
        (s)->done = 0; \
        p = (s)->head; \
        if (p != 0) { \
            while (p != 0) { \
                t = p->next; \
                if (t == 0) { \
                    break; \
                } \
                p = t; \
            } \
            p->next = node; \
            if (node != 0) { \
                node->prev = p; \
            } \
        } else { \
            (s)->head = node; \
        } \
        slot = &node->obj; \
    } \
}

s32 EffectInstanceCreate_2daf00(Self *self, s16 arg1, s32 arg2)
{
    s32 h22;
    s32 a;
    s32 h2;
    void *buf;
    u8 *o;
    s32 h12;
    Node *node2;
    s32 a2;
    s32 id;
    Sub *sub2;
    Obj **slot2;
    Node *node;
    bool nolock2;
    s32 b2;
    s32 i;
    bool nolock;
    s32 b;
    s32 id2;
    Sub *sub;
    Obj **slot;
    s32 h1;

    if (self->xB4 == 0) {
        return -1;
    }
    if (self->xB6 != 0) {
        return -2;
    }
    if (self->type == 1) {
        nolock = !(bool)busy(self->mgr);
        h1 = nolock ? MemStackHeapAlloc_14db10(self->mgr, 3, self->xB0 + 0x10, 0x40) : 0;
        if (h1 == 0) {
            if (nolock) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            return -3;
        }
        if ((o = MemStackNew_14e230(0x280, self->mgr)) != 0) {
            *(void **)(o + 0x190) = D_004716F0;
            *(s32 *)(o + 0x2C) = 0;
            *(s32 *)(o + 0xC) = -1;
            *(s16 *)(o + 4) = -1;
            *(s32 *)(o + 8) = -1;
            *(s16 *)(o + 2) = -1;
            *(s16 *)(o + 6) = 1;
            *(s32 *)(o + 0x14) = 0;
            *(s32 *)(o + 0x18) = -1;
            *(u8 *)(o + 0x170) = 0;
            i = 0;
            do {
                *(s32 *)(o + 0xF0 + i * 4) = 0;
                *(s32 *)(o + 0x130 + i * 4) = 0;
                i++;
            } while (i < 4);
            *(s32 *)(o + 0x1C) = 0;
            *(s16 *)(o + 0x20) = 0;
            *(void **)(o + 0x190) = D_00471670;
            ScriptVmCtor_176be0(o + 0x1A8);
            TargetRefCtor_2e71f0(o + 0x200);
            ((Obj *)o)->v08();
        }
        if (o == 0) {
            if (nolock) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            return -3;
        }
        FINDID(self)
        id = self->id;
        node = (Node *)MemStackNew_14e230(0x18, self->mgr);
        if (node != 0) {
            *(void **)((u8 *)node + 0x14) = D_004716D8;
            node->v08();
        }
        APPEND(self, node, id, slot)
        if (slot == 0) {
            if (nolock) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            return -5;
        }
        *slot = (Obj *)o;
        *(s32 *)(o + 0x1C) = h1;
        *(s32 *)(o + 0x1A4) = 0;
        *(s32 *)(o + 0x10) = self->id;
        *(s32 *)(o + 8) = self->id;
        ((Obj *)o)->v38(-1);
        ((Obj *)o)->v3C(-1);
        *(s16 *)(o + 2) = arg1;
        ((Obj *)o)->v54(self->x14);
        if (nolock) {
            MemStackReturnToOwnerMaybe_14dad0(self->mgr);
        }
        nolock = !(bool)busy(self->mgr);
        *(s32 *)(o + 0x1FC) = nolock ? MemStackHeapAlloc_14db10(self->mgr, 3, 0x102, 0x40) : 0;
        if (((Obj *)o)->v2C() == 0) {
            if (nolock) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            EffectEntryReleaseNode_2da6c0(self, (Obj *)o, 0, 0);
            return -6;
        }
        a = MemStackAllocQw_14d950(self->mgr, 0x80);
        b = MemStackAllocQw_14d950(self->mgr, 1);
        buf = ((Obj *)o)->v1C();
        if (buf != 0) {
            ScriptVmInit_176af0(buf, self->x90, a, 0x100, b, 2);
            ScriptVmSetCmdTable_176ae0(buf, D_004E8050, 0x200);
        }
        if (nolock) {
            MemStackReturnToOwnerMaybe_14dad0(self->mgr);
        }
        ((Obj *)o)->v3C(0x64);
        EffectNodeStepScript_2dad50(self, *slot);
        ((Obj *)o)->v3C(0xC8);
        if (++self->id > 0xFFFF) {
            self->id = 0;
        }
        *(s32 *)(o + 0x270) = self->xB0;
        *(s32 *)(o + 0xC) = arg2;
        return *(s32 *)(o + 8);
    } else {
        nolock2 = !(bool)busy(self->mgr);
        h12 = nolock2 ? MemStackHeapAlloc_14db10(self->mgr, 3, self->xB0 + 0x10, 0x40) : 0;
        if (h12 == 0) {
            if (nolock2) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            return -0x22;
        }
        if ((o = MemStackNew_14e230(0x9D0, self->mgr)) != 0) {
            EffectInstanceCtor_2db830(o);
            *(void **)(o + 0x190) = D_00471760;
            Character2Ctor_1ef2d0(o + 0x1A0, 0, 0, 0);
            ScriptVmCtor_176be0(o + 0x930);
            TargetRefCtorWrap_2db800(o + 0x98C);
            ((Obj *)o)->v08();
        }
        if (o == 0) {
            if (nolock2) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            return -3;
        }
        FINDID(self)
        id2 = self->id;
        node2 = (Node *)MemStackNew_14e230(0x18, self->mgr);
        if (node2 != 0) {
            *(void **)((u8 *)node2 + 0x14) = D_004716D8;
            node2->v08();
        }
        APPEND(self, node2, id2, slot2)
        if (slot2 == 0) {
            if (nolock2) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            if (h12 != 0) {
                MemStackHeapFree_14dcb0(self->mgr, h12);
            }
            return -5;
        }
        *slot2 = (Obj *)o;
        sub2 = ((Obj *)o)->v18();
        ((Obj *)o)->v08();
        *(s32 *)(o + 0x1C) = h12;
        if (sub2 != 0) {
            sub2->v5C();
            ModelObjExCopy_1aff40(self->x80, sub2, self->mgr);
        }
        *(s32 *)(o + 0x984) = 0;
        *(s32 *)(o + 0x10) = self->id;
        *(s32 *)(o + 8) = self->id;
        ((Obj *)o)->v38(-1);
        ((Obj *)o)->v3C(-1);
        *(s16 *)(o + 2) = arg1;
        if (nolock2) {
            MemStackReturnToOwnerMaybe_14dad0(self->mgr);
        }
        nolock2 = !(bool)busy(self->mgr);
        *(s32 *)(o + 0x988) = nolock2 ? MemStackHeapAlloc_14db10(self->mgr, 3, 0x102, 0x40) : 0;
        if (((Obj *)o)->v2C() == 0) {
            if (nolock2) {
                MemStackReturnToOwnerMaybe_14dad0(self->mgr);
            }
            EffectEntryReleaseNode_2da6c0(self, (Obj *)o, 0, 0);
            return -6;
        }
        a2 = MemStackAllocQw_14d950(self->mgr, 0x80);
        b2 = MemStackAllocQw_14d950(self->mgr, 1);
        buf = ((Obj *)o)->v1C();
        if (buf != 0) {
            ScriptVmInit_176af0(buf, self->x90, a2, 0x100, b2, 2);
            ScriptVmSetCmdTable_176ae0(buf, D_004E8050, 0x200);
        }
        if (nolock2) {
            MemStackReturnToOwnerMaybe_14dad0(self->mgr);
        }
        ((Obj *)o)->v3C(0x64);
        EffectNodeStepScript_2dad50(self, *slot2);
        ((Obj *)o)->v3C(0xC8);
        if (++self->id > 0xFFFF) {
            self->id = 0;
        }
        *(s32 *)(o + 0xC) = arg2;
        return *(s32 *)(o + 8);
    }
}
