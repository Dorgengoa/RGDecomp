#include "types.h"
#pragma optimization_level 3

typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad0[0xC]; s32 f0C; f32 f10; } Hit;
typedef struct { u8 pad0[0x3D0]; u64 f3D0; s32 f3D8; u8 pad3DC[0xA44 - 0x3DC]; s32 fA44; } Chr;
typedef struct { s32 f0; s16 f4; s16 f6; } Grp;
typedef struct { u8 pad0[0x40]; s16 f40; } Slot;
typedef struct { u8 pad0[0x18E]; s16 f18E; } Pty;
typedef struct { u8 pad0[0x18]; Pty *f18; } Fd;
typedef struct { u8 pad0[0x180C]; s32 f180C; } World;
typedef struct { s32 p; s32 n; } Buf;
typedef struct {
    s32 id;
    s32 f4;
    s32 cap;
    Buf b[4];
    V4 *hits;
    s32 nhit;
    s32 pad34[2];
    f32 f3C;
    f32 f40;
} Ctx;
typedef struct { u8 pad0[0x20]; s32 f20; } Team;

class PC {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void Act();
};

extern "C" {
Fd *GetGameData_1fede0(void);
World *GetCurrentScene_1f5be0(void);
s32 ObjRecHasFlags6_1c3eb0(World *, s32, s32);
Chr *ObjRecGetLiveObject_1c4a90(World *, s32);
Hit *ObjGetNthAttachPointPos_1ade20(Chr *, s32, s32, V4 *);
s32 DListGetHead_42ea60(s32 *);
s32 DListGetNext_42eb30(s32);
s32 CharaGetId_214a80(Chr *);
f32 ModelObjGetBodyWeight_23b0f0(Chr *);
void GetMapMgr_201a90(void);
s32 GetEventObjMgr_2d1960(void);
s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
s32 MemStackNew_14e1b0(s32, s32);
s32 ConstructNewArray_100710(s32, s32, s32, s32, s32);
void MemStackReturnToOwnerMaybe_14dad0(s32);
void MemStackHeapFree_14dcb0(s32, s32);
s32 CharaGetActionTable_214cd0(Chr *);
s32 CharaIsDeadVanishedMaybe_210a90(Chr *);
f32 GameSceneGetTimeStep_1ceba0(World *);
s32 IsInBattle_288420(void);
void CharaAddCollIgnoreMask_238920(Chr *, s32);
s32 CharaHasEvObjContact_214960(Chr *);
Grp *CharaGetEvObjContact_214990(Chr *);
s32 EventObjMgrFindObjByName_2e9920(s32, s32, s32);
s32 ObjTypeMonographGetTargetKind5Id_372760(s32);
s32 CharaGetAttachParentId_213890(Chr *);
Slot *CharaGetGroundTri_238450(Chr *, s32);
void EventObjMgrGetPosRecPosById_2e8950(s32, V4 *, s32);
void CharaSetPlatformVelMaybe_2384c0(Chr *, V4 *);
s32 CharaGetActionMode_213850(Chr *);
void CharaUpdateMovement_20a7d0(Chr *, Ctx *);
PC *ActorFindById_3eb870(Fd *, s32);
f32 CharaGetWaterDepthMaybe_238370(Chr *);
Slot *CharaGetWaterTriMaybe_2383d0(Chr *, s32);
extern f32 D_0045B080[];
extern f32 D_0047DB14;
extern f32 D_0047DB18;
extern f32 D_0047DAC0;
extern f32 D_0047D344;

void ActionMgrMoveAll_231720(Team *self) {
    V4 hits[256];
    Chr *list[224];
    Ctx ctx;
    V4 name;
    f32 r;
    s32 n;
    Fd *fd;
    s32 leader;
    World *w;
    s32 i;
    Chr *o;
    s32 j;
    Hit *h;
    s32 m;
    s32 mi;
    s32 node;
    Chr **p;
    f32 best;
    f32 f;
    Chr *t;
    s32 tbl;
    s32 mark;
    f32 k1;
    f32 k;
    f32 k2;
    f32 k3;
    Chr *c;
    s32 myid;
    s32 excl;
    Grp *q;
    s32 x;
    s32 id;
    s32 grp;
    PC *pc;
    s32 j2;
    Chr *o2;

    n = 0;
    fd = GetGameData_1fede0();
    leader = fd->f18->f18E;
    w = GetCurrentScene_1f5be0();
    k = D_0047DB14 * *(volatile f32 *)D_0045B080;
    for (i = 0xC0; i <= 0xDF; i++) {
        if (ObjRecHasFlags6_1c3eb0(w, 1, i) == 0) {
            continue;
        }
        o = ObjRecGetLiveObject_1c4a90(w, i);
        if (o == 0) {
            continue;
        }
        for (j = 0; (h = ObjGetNthAttachPointPos_1ade20(o, 0x78, j, &hits[n])) != 0; ) {
            j++;
            if (h->f0C == 0) {
                continue;
            }
            if (h->f10 <= 0.0f) {
                continue;
            }
            hits[n].w = h->f10 * k;
            n++;
        }
    }
    m = 0;
    for (node = DListGetHead_42ea60(&self->f20); node != 0; node = DListGetNext_42eb30(node)) {
        list[m++] = (Chr *)(node + 0x10);
    }
    for (i = 0; i < m; i++) {
        p = &list[i];
        best = ModelObjGetBodyWeight_23b0f0(ObjRecGetLiveObject_1c4a90(w, CharaGetId_214a80(*p)));
        for (j = i + 1; j < m; j++) {
            f = ModelObjGetBodyWeight_23b0f0(ObjRecGetLiveObject_1c4a90(w, CharaGetId_214a80(list[j])));
            if (best < f) {
                t = *p;
                *p = list[j];
                list[j] = t;
                best = f;
            }
        }
    }
    for (i = 0; i < m; i++) {
        if (leader != CharaGetId_214a80(list[i])) {
            continue;
        }
        t = list[i];
        for (j = i - 1; j >= 0; j--) {
            list[j + 1] = list[j];
        }
        list[0] = t;
    }
    for (i = 0; i < m; i++) {
        p = &list[i];
        t = *p;
        if (!(t->fA44 & 0x20)) {
            continue;
        }
        for (j = i + 1; j < m; j++) {
            list[j - 1] = list[j];
        }
        list[m - 1] = t;
    }
    for (i = 0; i < m; i++) {
        p = &list[i];
        t = *p;
        if (!(t->fA44 & 0x40)) {
            continue;
        }
        for (j = i + 1; j < m; j++) {
            list[j - 1] = list[j];
        }
        list[m - 1] = t;
    }
    {
    s32 pool;
    GetMapMgr_201a90();
    tbl = GetEventObjMgr_2d1960();
    ctx.cap = 0x100;
    pool = w->f180C;
    mark = MemStackHeapAlloc_14db10(pool, 2, 0, 0x40);
    ctx.b[0].p = ConstructNewArray_100710(MemStackNew_14e1b0(ctx.cap * 0x60 + 0x10, pool), 0, 0, 0x60, ctx.cap);
    ctx.b[1].p = ConstructNewArray_100710(MemStackNew_14e1b0(ctx.cap * 0x60 + 0x10, pool), 0, 0, 0x60, ctx.cap);
    ctx.b[2].p = ConstructNewArray_100710(MemStackNew_14e1b0(ctx.cap * 0x60 + 0x10, pool), 0, 0, 0x60, ctx.cap);
    ctx.b[3].p = ConstructNewArray_100710(MemStackNew_14e1b0(ctx.cap * 0x60 + 0x10, pool), 0, 0, 0x60, ctx.cap);
    MemStackReturnToOwnerMaybe_14dad0(pool);
    k1 = D_0047DB18 * D_0045B080[0];
    k2 = D_0047DAC0 * D_0045B080[0];
    k3 = D_0047D344 * D_0045B080[0];
    for (mi = 0; mi < m; mi++) {
        c = list[mi];
        if (c == 0) {
            continue;
        }
        myid = CharaGetId_214a80(c);
        if (c == 0 || CharaGetActionTable_214cd0(c) == 0) {
            continue;
        }
        if (c->fA44 & 0x8000000) {
            continue;
        }
        if (CharaIsDeadVanishedMaybe_210a90(c) != 0) {
            continue;
        }
        if (c->fA44 & 0x80000) {
            continue;
        }
        ctx.f40 = GameSceneGetTimeStep_1ceba0(w);
        ctx.b[0].n = 0;
        ctx.hits = hits;
        ctx.b[1].n = 0;
        ctx.b[2].n = 0;
        ctx.b[3].n = 0;
        ctx.nhit = n;
        if (!(c->f3D0 & 0x80000000000ULL)) {
            r = ModelObjGetBodyWeight_23b0f0(ObjRecGetLiveObject_1c4a90(w, CharaGetId_214a80(c)));
            if (IsInBattle_288420() == 0 && leader == CharaGetId_214a80(c)) {
                CharaAddCollIgnoreMask_238920(c, 2);
            }
            excl = -1;
            if (CharaHasEvObjContact_214960(c) != 0) {
                q = CharaGetEvObjContact_214990(c);
                if (q->f4 == 5 && (q->f6 & 1)) {
                    x = EventObjMgrFindObjByName_2e9920(tbl, q->f0, q->f4);
                    if (x != 0) {
                        excl = ObjTypeMonographGetTargetKind5Id_372760(x);
                    }
                }
            }
            for (j2 = 0; j2 < m; j2++) {
                if (mi == j2) {
                    continue;
                }
                p = &list[j2];
                if (excl == CharaGetId_214a80(*p)) {
                    continue;
                }
                if (CharaIsDeadVanishedMaybe_210a90(*p) != 0) {
                    continue;
                }
                if ((*p)->f3D0 & 0x200000000000ULL) {
                    continue;
                }
                if (myid == CharaGetAttachParentId_213890(*p)) {
                    continue;
                }
                id = CharaGetId_214a80(*p);
                if (ObjRecHasFlags6_1c3eb0(w, 1, id) == 0) {
                    continue;
                }
                o2 = ObjRecGetLiveObject_1c4a90(w, id);
                if (o2 == 0) {
                    continue;
                }
                if (!(r <= 2.0f * ModelObjGetBodyWeight_23b0f0(o2))) {
                    continue;
                }
                for (j = 0; (h = ObjGetNthAttachPointPos_1ade20(o2, 0x78, j, &hits[ctx.nhit])) != 0; ) {
                    j++;
                    if (h->f0C == 0) {
                        continue;
                    }
                    if (h->f10 <= 0.0f) {
                        continue;
                    }
                    hits[ctx.nhit].w = h->f10 * k;
                    ctx.nhit++;
                }
            }
        }
        grp = -1;
        if (c->f3D8 & 1) {
            grp = CharaGetGroundTri_238450(c, 0)->f40;
        }
        EventObjMgrGetPosRecPosById_2e8950(tbl, &name, grp);
        CharaSetPlatformVelMaybe_2384c0(c, &name);
        ctx.id = CharaGetId_214a80(c);
        ctx.f4 = CharaGetActionMode_213850(c);
        ctx.f3C = k1;
        if (leader == CharaGetId_214a80(c)) {
            ctx.f3C = k2;
        }
        CharaUpdateMovement_20a7d0(c, &ctx);
        pc = ActorFindById_3eb870(fd, CharaGetId_214a80(c));
        if (pc == 0) {
            continue;
        }
        if (!(c->f3D8 & 0x10)) {
            continue;
        }
        if (CharaGetWaterDepthMaybe_238370(c) <= k3) {
            continue;
        }
        if (CharaGetWaterTriMaybe_2383d0(c, 0)->f40 < 0x40 || CharaGetWaterTriMaybe_2383d0(c, 0)->f40 >= 0x50) {
            pc->Act();
        }
    }
    MemStackHeapFree_14dcb0(pool, mark);
    }
}
}
