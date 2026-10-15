#include "types.h"
extern "C" {

typedef struct Tri { s16 id; s16 msg; s16 key; } Tri;
typedef struct TriTbl { Tri t[8]; } TriTbl;
typedef struct Link { s32 m0; s16 *m4; } Link;
typedef struct Obj { u8 pad0[0x24]; s16 n; u8 pad26[2]; Link **links; } Obj;
typedef struct Elem { u8 pad0[0x10]; Obj *obj; } Elem;
typedef struct Grp { u8 pad0[9]; s8 n : 6; u8 pad0A[2]; Elem *elems; } Grp;
typedef struct Host { u8 pad0[0x28]; Grp *grp; } Host;
typedef struct Out { s16 m0; u8 pad2[6]; s16 m8; u8 padA[0x16]; } Out;
typedef struct Item { s16 m0; u8 pad2[2]; s32 m4; u8 pad8[8]; } Item;
typedef Item Out2;
typedef struct Elem20 { u8 pad0[0x10]; Obj *obj; } Elem20;

extern s32 MsgTableLookup_28aa30(s32, s32);
extern Host *ItemDefGetWeaponData_40e110(s32);
extern u8 D_0044F9B0[];

}
extern "C" s32 MenuWeaponCmdListBuildMaybe_289c90(s32 id, s32 arg1, Out *out, Out2 *out2)
{
    TriTbl tbl;
    Host *h;
    Grp *g;
    Elem *e;
    Obj *o;
    Link *l;
    s16 *p;
    s32 cnt;
    s32 i;
    s32 j;
    s32 k;
    bool found;
    s32 m;
    Tri *t;
    Item *o2;
    s32 ni;
    s32 nj;

    tbl = *(TriTbl *)D_0044F9B0;
    out2->m4 = MsgTableLookup_28aa30(arg1, 0x7D6);
    h = ItemDefGetWeaponData_40e110(id);
    if (h == 0) {
        return 0;
    }
    g = h->grp;
    if (g == 0) {
        return 0;
    }
    cnt = 0;
    ni = g->n;
    for (i = 0; i < ni; i++) {
        e = &g->elems[i];
        if (e == 0) {
            continue;
        }
        o = e->obj;
        if (o == 0) {
            continue;
        }
        nj = o->n;
        for (j = 0; j < nj; j++) {
            l = o->links[j];
            if (l == 0) {
                continue;
            }
            p = l->m4;
            if (p == 0) {
                continue;
            }
            for (k = 0; k < 8; k++) {
                if (*p != tbl.t[k].id) {
                    continue;
                }
                found = false;
                for (m = cnt - 1; m >= 0; m--) {
                    if (out[m].m8 == tbl.t[k].key) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
                out[cnt].m0 = 8;
                t = &tbl.t[(u32)k];
                o2 = &out2[cnt];
                out[cnt].m8 = t->key;
                o2[1].m0 = 0x1A;
                o2[1].m4 = MsgTableLookup_28aa30(arg1, t->msg);
                cnt++;
            }
        }
    }
    out[cnt].m0 = -1;
    out2[cnt + 1].m0 = -1;
    return cnt;
}
