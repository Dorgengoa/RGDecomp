/* rgp:protos */
#define RGP_SELF_MapAreaModelBuildObjTablesMaybe_18d940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 n;
    void **p;
} Tab18D940;

typedef struct {
    u8 pad0[0x4B0];
    u8 lists[7][12];
    Tab18D940 tab[10];
    u8 pad554[0x38];
    void *x58C;
    void *x590;
    void *x594;
} O18D940;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapAreaModelBuildObjTablesMaybe_18d940(O18D940 *o, s32 heap) {
    void *hd[7];
    s32 sz[7] __attribute__((aligned(16)));
    s32 cnt[10] __attribute__((aligned(16)));
    s32 i;
    s32 t;
    Tab18D940 *tp;
    void *n;
    void *e;
    s32 *p;
    s32 k;

    o->tab[0].n = 0;
    for (i = 0; i < 7; i++) {
        hd[i] = ListGetHead_18e080(o->lists[i]);
        if (hd[i] != 0) {
            p = &sz[(s32)(u32)i];
            *p = ListCountFromNode_18e050(hd[i]);
        } else {
            p = &sz[i];
            *p = 0;
        }
        o->tab[0].n += *p;
    }
    t = sz[0] + *(volatile s32 *)&sz[1];
    o->tab[1].n = sz[2] + t;
    o->tab[2].n = sz[5] + t;
    o->tab[3].n = sz[0];
    o->tab[4].n = sz[3];
    o->tab[5].n = sz[4];
    o->tab[6].n = sz[0];
    o->tab[7].n = sz[0];
    o->tab[8].n = sz[5];
    o->tab[9].n = sz[6];
    for (i = 0; i < 10; i++) {
        tp = &o->tab[i];
        tp->p = (void **)MemStackNew_14e1b0(tp->n * 4, heap);
        if (tp->p == 0) {
            tp->n = 0;
        }
        cnt[i] = 0;
    }
    for (n = hd[0]; n != 0; n = ListNodeNext_18e030(n)) {
        e = ListNodeGetData_18a370(n);
        if (e != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = e;
            }
            if (o->tab[1].n > cnt[1]) {
                o->tab[1].p[cnt[1]++] = e;
            }
            if (o->tab[2].n > cnt[2] && NodeObjHasCollBounds_18e040(e) != 0) {
                o->tab[2].p[cnt[2]++] = e;
            }
            if (o->tab[3].n > cnt[3]) {
                o->tab[3].p[cnt[3]++] = e;
            }
            if (o->tab[6].n > cnt[6] && NodeObjAnyChildCollFlag10Maybe_194360(e) != 0) {
                o->tab[6].p[cnt[6]++] = e;
            }
            if (o->tab[7].n > cnt[7]) {
                o->tab[7].p[cnt[7]++] = e;
            }
        }
    }
    for (e = hd[1]; e != 0; e = ListNodeNext_18e030(e)) {
        n = ListNodeGetData_18a370(e);
        if (n != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = n;
            }
            if (o->tab[1].n > cnt[1]) {
                o->tab[1].p[cnt[1]++] = n;
            }
            if (o->tab[2].n > cnt[2] && NodeObjHasCollBounds_18e040(n) != 0) {
                o->tab[2].p[cnt[2]++] = n;
            }
        }
    }
    for (n = hd[2]; n != 0; n = ListNodeNext_18e030(n)) {
        e = ListNodeGetData_18a370(n);
        if (e != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = e;
            }
            if (o->tab[1].n > cnt[1]) {
                o->tab[1].p[cnt[1]++] = e;
            }
        }
    }
    for (n = hd[3]; n != 0; n = ListNodeNext_18e030(n)) {
        e = ListNodeGetData_18a370(n);
        if (e != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = e;
            }
            if (o->tab[4].n > cnt[4]) {
                o->tab[4].p[cnt[4]++] = e;
            }
        }
    }
    for (n = hd[4]; n != 0; n = ListNodeNext_18e030(n)) {
        e = ListNodeGetData_18a370(n);
        if (e != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = e;
            }
            if (o->tab[5].n > cnt[5]) {
                o->tab[5].p[cnt[5]++] = e;
            }
        }
    }
    for (e = hd[5]; e != 0; e = ListNodeNext_18e030(e)) {
        n = ListNodeGetData_18a370(e);
        if (n != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = n;
            }
            if (o->tab[8].n > cnt[8]) {
                o->tab[8].p[cnt[8]++] = n;
            }
            if (o->tab[2].n > cnt[2] && NodeObjHasCollBounds_18e040(n) != 0) {
                o->tab[2].p[cnt[2]++] = n;
            }
        }
    }
    for (n = hd[6]; n != 0; n = ListNodeNext_18e030(n)) {
        e = ListNodeGetData_18a370(n);
        if (e != 0) {
            if (o->tab[0].n > cnt[0]) {
                o->tab[0].p[cnt[0]++] = e;
            }
            if (o->tab[9].n > cnt[9]) {
                o->tab[9].p[cnt[9]++] = e;
            }
        }
    }
    o->tab[1].n = cnt[1];
    o->tab[2].n = cnt[2];
    o->tab[3].n = cnt[3];
    o->tab[4].n = cnt[4];
    o->tab[5].n = cnt[5];
    o->tab[6].n = cnt[6];
    o->tab[7].n = cnt[7];
    o->tab[8].n = cnt[8];
    o->tab[9].n = cnt[9];
    o->x58C = MemStackNew_14e1b0(o->tab[1].n * 4, heap);
    o->x590 = MemStackNew_14e1b0(o->tab[8].n * 4, heap);
    o->x594 = MemStackNew_14e1b0(o->tab[9].n * 4, heap);
}
