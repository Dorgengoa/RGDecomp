#include "types.h"

typedef struct Queue {
    u8 pad0[8];
} Queue;

typedef struct Ent {
    u8 pad0[0x80];
    s16 h80;
    u8 pad82[0x16];
} Ent;

typedef struct Mgr {
    s32 x0;             /* +0x00 */
    u8 pad4[4];
    s32 x8;             /* +0x08 */
    u8 padc;
    u8 b0d;             /* +0x0D */
    u8 pade[2];
    Ent *list;          /* +0x10 */
    s32 count;          /* +0x14 */
    s32 active;         /* +0x18 */
    s32 peak;           /* +0x1C */
    Queue q20;          /* +0x20 */
    Queue q28;          /* +0x28 */
    Queue q30;          /* +0x30 */
} Mgr;

typedef struct Unit {
    u8 pad0[0x82];
    s16 h82;            /* +0x82 */
    u8 pad84[4];
    s32 x88;            /* +0x88 */
    s32 x8c;            /* +0x8C */
    s32 x90;            /* +0x90 */
    s32 x94;            /* +0x94 */
} Unit;

typedef struct Info {
    u8 pad0[8];
    s32 x8;             /* +0x08 */
    u8 padc[0x100];
    s32 x10c;           /* +0x10C */
    s32 x110;           /* +0x110 */
} Info;

extern s16 *S16ArrayGetData_1ce1c0(Queue *);
extern s32 S16ArrayGetCount_1ce1b0(Queue *);
extern void S16ArrayRemoveAt_1ce0a0(Queue *, s32);
extern void S16ArrayAppend_1ce110(Queue *, s16);
extern Unit *LoaderGetUnit_1cde10(Mgr *, s16);
extern Info *FileReqFindByName_182720(Unit *);
extern void LoaderUnitFree_1ce300(Unit *, s32);
extern void FileReqReleaseByName_1826a0(Unit *);
extern s32 GetStreamMgr_207ea0(void);
extern s32 StreamMgrGetMinRemainFrames_1d62f0(s32);
extern void LoaderSetWaitFrames_1cd5a0(Mgr *, s32);
extern s32 FileReqAnyIncomplete_1825f0(void);
extern s32 FileGetSizeByPath_181ee0(Unit *, s32 *);
extern s32 LoaderUnitHasUserBuf_1ce250(Unit *);
extern s32 MemStackHeapAllocFrontAlign64_14dd00(s32, u32);
extern s32 LoaderUseSyncRead_1cd890(Mgr *);
extern s32 FileReqSubmitWhole_1829f0(Unit *, s32, s32);
extern void ResidentFileReadLocalizedMaybe_1c2860(Unit *, s32, s32 *);
extern void PadWaitReady_1849e0(void *);
extern void FileReqThreadResume_182670(void);
extern u8 D_004B2570[];

void LoaderTick_1ccc30(Mgr *m)
{
    Queue *qs[2];
    s32 tmp;
    u32 n;
    s32 j;
    Unit *w;
    s16 *d;
    s32 g;
    u32 t;
    Info *v;
    Ent *p;
    s32 sz;
    Queue **qp;
    s32 k;
    s32 i;
    Unit *u;
    s16 *pp;

    if (m->x0 == 0) {
        return;
    }
    p = m->list;
    m->active = 0;
    for (i = 0; i < m->count; i++, p++) {
        if (p->h80 < 0) {
            continue;
        }
        m->active++;
    }
    if (m->peak < m->active) {
        m->peak = m->active;
    }
    d = S16ArrayGetData_1ce1c0(&m->q28);
    for (j = 0; j < S16ArrayGetCount_1ce1b0(&m->q28); j++) {
        pp = &d[j];
        w = LoaderGetUnit_1cde10(m, *pp);
        if (w == 0) {
            S16ArrayRemoveAt_1ce0a0(&m->q28, j);
            j--;
            continue;
        }
        v = FileReqFindByName_182720(w);
        if (v == 0) {
            LoaderUnitFree_1ce300(w, m->x0);
            S16ArrayRemoveAt_1ce0a0(&m->q28, j);
            j--;
            continue;
        }
        if (v->x8 == 0) {
            continue;
        }
        w->x90 = v->x10c;
        w->x94 = v->x110;
        FileReqReleaseByName_1826a0(w);
        S16ArrayAppend_1ce110(&m->q30, *pp);
        S16ArrayRemoveAt_1ce0a0(&m->q28, j);
        j--;
    }
    { u8 *p_ = (u8 *)qs; u32 n_ = 8; if (p_ != 0) { do { *p_ = 0; n_--; p_++; } while (n_ != 0); } }
    qs[0] = &m->q30;
    qs[1] = &m->q20;
    k = 0;
    do {
        qp = &qs[k];
        d = S16ArrayGetData_1ce1c0(*qp);
        for (i = 0; i < S16ArrayGetCount_1ce1b0(*qp); i++) {
            u = LoaderGetUnit_1cde10(m, d[i]);
            if (u == 0) {
                continue;
            }
            if (u->h82 == 1) {
                LoaderUnitFree_1ce300(u, m->x0);
                S16ArrayRemoveAt_1ce0a0(*qp, i);
                i--;
            }
        }
        k++;
    } while (k < 2);
    if (S16ArrayGetCount_1ce1b0(&m->q30) > 0) {
        d = S16ArrayGetData_1ce1c0(&m->q30);
        while (S16ArrayGetCount_1ce1b0(&m->q30) > 0) {
            if (*d != 0x3FFF) {
                break;
            }
            S16ArrayRemoveAt_1ce0a0(&m->q30, 0);
        }
    }
    if (S16ArrayGetCount_1ce1b0(&m->q20) > 0 && S16ArrayGetCount_1ce1b0(&m->q30) + S16ArrayGetCount_1ce1b0(&m->q28) <= 0) {
        d = S16ArrayGetData_1ce1c0(&m->q20);
        while (S16ArrayGetCount_1ce1b0(&m->q20) > 0) {
            if (*d != 0x3FFF) {
                break;
            }
            S16ArrayRemoveAt_1ce0a0(&m->q20, 0);
        }
    }
    g = StreamMgrGetMinRemainFrames_1d62f0(GetStreamMgr_207ea0());
    m->x8--;
    if (g < S16ArrayGetCount_1ce1b0(&m->q28) + 2) {
        LoaderSetWaitFrames_1cd5a0(m, 2);
    }
    if (S16ArrayGetCount_1ce1b0(&m->q20) > 0 && m->x8 <= 0) {
        LoaderSetWaitFrames_1cd5a0(m, 0);
        if (S16ArrayGetCount_1ce1b0(&m->q20) > 0 && FileReqAnyIncomplete_1825f0() == 0) {
            d = S16ArrayGetData_1ce1c0(&m->q20);
            for (i = 0; i < S16ArrayGetCount_1ce1b0(&m->q20); i++) {
                pp = &d[i];
                if (*pp == 0x3FFF) {
                    break;
                }
                if (S16ArrayGetCount_1ce1b0(&m->q28) >= 4) {
                    break;
                }
                u = LoaderGetUnit_1cde10(m, *pp);
                if (u == 0) {
                    S16ArrayRemoveAt_1ce0a0(&m->q20, i);
                    i--;
                    continue;
                }
                sz = FileGetSizeByPath_181ee0(u, &tmp);
                if (sz <= 0) {
                    LoaderUnitFree_1ce300(u, m->x0);
                    S16ArrayRemoveAt_1ce0a0(&m->q20, i);
                    i--;
                    continue;
                }
                if (FileReqFindByName_182720(u) != 0) {
                    break;
                }
                if (LoaderUnitHasUserBuf_1ce250(u) == 0) {
                    t = sz + 0x800;
                    if (t & 0xF) {
                        n = (t >> 4) + 1;
                    } else {
                        n = t >> 4;
                    }
                    u->x8c = n;
                    u->x88 = MemStackHeapAllocFrontAlign64_14dd00(m->x0, n);
                }
                if (u->x88 == 0) {
                    break;
                }
                if (LoaderUseSyncRead_1cd890(m) == 0) {
                    if (FileReqSubmitWhole_1829f0(u, u->x88, 0) != 0) {
                        FileReqFindByName_182720(u);
                        S16ArrayAppend_1ce110(&m->q28, *pp);
                        S16ArrayRemoveAt_1ce0a0(&m->q20, i);
                        i--;
                        continue;
                    }
                    LoaderUnitFree_1ce300(u, m->x0);
                    S16ArrayRemoveAt_1ce0a0(&m->q20, i);
                    i--;
                    continue;
                }
                ResidentFileReadLocalizedMaybe_1c2860(u, u->x90 = u->x88, &u->x94);
                u->h82 = 0;
                S16ArrayAppend_1ce110(&m->q30, *pp);
                S16ArrayRemoveAt_1ce0a0(&m->q20, i);
                i--;
                if (m->b0d != 0) {
                    PadWaitReady_1849e0(D_004B2570);
                }
            }
        }
    }
    if (S16ArrayGetCount_1ce1b0(&m->q20) > 0 && S16ArrayGetCount_1ce1b0(&m->q30) + S16ArrayGetCount_1ce1b0(&m->q28) <= 0) {
        d = S16ArrayGetData_1ce1c0(&m->q20);
        while (S16ArrayGetCount_1ce1b0(&m->q20) > 0) {
            if (*d != 0x3FFF) {
                break;
            }
            S16ArrayRemoveAt_1ce0a0(&m->q20, 0);
        }
    }
    FileReqThreadResume_182670();
}
