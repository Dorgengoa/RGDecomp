#include "types.h"

/* lane N4 family leader: EffDefCmdMdsModel_19f680 / EffDefCmdMdsModel_19f680 (500 B each).
   Substitutions: alloc size 0x1C, ctor EffModelResCtor_1a8380, init EffModelResInitFromMds_1a81e0. */

typedef struct { s32 w0; s32 w1; } Name;

typedef struct Node Node;
struct Node { Node *next; s32 val; };

typedef struct {
    u8 pad00[0x60];
    Node *f60;
    s32 f64;
} Lst;

typedef struct A A;
struct A {
    void *f0;
    s32 f4;
    u8 pad08[0x18];
    s32 f20;
    Lst *f24;
};

extern s8 *SlotGetInt_15f720(Name *);
extern s32 ArchiveGetFileData_181dd0(s32, s8 *, s32 *);
extern void *MemStackNew_14e230(s32, s32);
extern void *EffModelResCtor_1a8380(void *);
extern void ModelResRelocate_14bfd0(s32 *, s32);
extern void EffModelResInitFromMds_1a81e0(void *, s32 *, s32);
extern void EffHdlAddByName_1a3420(void **, void *, s8 *, void **);
extern void EffHdlRemove_1a3360(void *, s32);

s32 EffDefCmdMdsModel_19f680(Name *arg0, s32 arg1, A **arg2)
{
    s32 h;
    s8 *nm;
    s32 tag;
    void *obj;
    A *a;
    Lst *lst;
    Node *nd;
    Node *e;
    s32 *slot;
    s8 *s;
    s32 c;
    s8 *r;
    s32 ok;
    s32 sp9C;
    void *sp98;
    void *sp94;
    f32 sp90;
    s32 sp88[2];

    a = *arg2;
    h = a->f20;
    nm = SlotGetInt_15f720(arg0++);
    tag = ArchiveGetFileData_181dd0(a->f4, nm, &sp9C);
    if (tag == 0) {
        return 0;
    }
    obj = MemStackNew_14e230(0x1C, h);
    if (obj != 0) {
        obj = EffModelResCtor_1a8380(obj);
    }
    if (obj == 0) {
        return 0;
    }
    sp88[0] = 0;
    ModelResRelocate_14bfd0(sp88, tag);
    EffModelResInitFromMds_1a81e0(obj, sp88, a->f20);
    r = 0;
    if (arg1 >= 2) {
        r = SlotGetInt_15f720(arg0);
    }
    s = nm;
    while ((c = *s) != 0) {
        if ((s8)c == 0x2E) {
            *s = 0;
            break;
        }
        s++;
    }
    if (r == 0) {
        r = nm;
    }
    sp94 = obj;
    EffHdlAddByName_1a3420(&sp98, (u8 *)a->f0 + 0x14, r, &sp94);
    ok = !(sp98 != 0);
    if (ok != 0) {
        return 0;
    }
    lst = a->f24;
    nd = MemStackNew_14e230(8, h);
    if (nd != 0) {
        nd->val = 0;
        nd->next = 0;
    }
    if (nd == 0) {
        slot = 0;
    } else {
        lst->f64 = 0;
        e = lst->f60;
        if (e != 0) {
            while (e != 0) {
                if (e->next == 0) {
                    break;
                }
                e = e->next;
            }
            e->next = nd;
        } else {
            lst->f60 = nd;
        }
        slot = &nd->val;
    }
    if (slot == 0) {
        sp90 = *(f32 *)&sp98;
        EffHdlRemove_1a3360((u8 *)a->f0 + 0x14, *(s32 *)&sp90);
        return 0;
    }
    *slot = (s32)sp98;
    return 1;
}
