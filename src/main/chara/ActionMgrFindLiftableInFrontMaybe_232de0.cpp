#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Info {
    u8 pad0[4];
    s8 sub : 4;
    s8 kind : 4;
} Info;

class Unit {
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
    virtual s32 isBusy();
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
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual Info *getInfo();
};

typedef struct World {
    u8 pad[0x1C];
    s32 x1C;
} World;

extern "C" {
extern s32 GetCurrentScene_1f5be0(void);
extern s32 DListGetHead_42ea60(void *list);
extern s32 DListGetNext_42eb30(s32 node);
extern s32 CharaGetId_214a80(s32 e);
extern s32 CharaGetActionMode_213850(s32 e);
extern u32 ObjRecGetFlags_1c3d90(s32 a, s32 b, s32 c);
extern World *GetGameData_1fede0(void);
extern f32 Sinf_128fd0(f32 a);
extern f32 Cosf_128d30(f32 a);
extern Unit *ObjFindById_3bb3a0(s32 a, s32 b);
extern void CharaGetPos_2388a0(s32 e, Vec *v);
extern void VecSub_1cbd00(Vec *d, Vec *a, Vec *b);
extern f32 VecLengthSqXZ_1cb450(Vec *v);
extern f32 CharaGetCollRadius_2386a0(s32 e);
extern void VecNormalize_1cbb80(Vec *d, Vec *s);
extern f32 VecDot3_1cba90(Vec *a, Vec *b);
extern f32 D_0045B080[0x100];
}

extern "C" s32 ActionMgrFindLiftableInFrontMaybe_232de0(u8 *self, Vec *at, f32 ang, f32 rad)
{
    Vec dir;
    Vec pos;
    Vec d;
    s32 ctx;
    s32 node;
    s32 e;
    World *w;
    s32 best;
    f32 lo;
    f32 hi;
    f32 dist;
    Unit *u;
    Info *info;

    ctx = GetCurrentScene_1f5be0();
    node = DListGetHead_42ea60(self + 0x20);
    while (node != 0) {
        e = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (CharaGetId_214a80(e) < 0x80) {
            continue;
        }
        if (!(CharaGetId_214a80(e) < 0x9C)) {
            continue;
        }
        if (CharaGetActionMode_213850(e) == 0x12) {
            return -1;
        }
        if (!(ObjRecGetFlags_1c3d90(ctx, 1, CharaGetId_214a80(e)) & 0x800000)) {
            return -1;
        }
    }
    w = GetGameData_1fede0();
    {
        u8 *p = (u8 *)&dir;
        u32 n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
    }
    dir.x = Sinf_128fd0(ang);
    dir.z = Cosf_128d30(ang);
    hi = D_0045B080[0];
    lo = -0.5f * hi;
    best = -1;
    node = DListGetHead_42ea60(self + 0x20);
    while (node != 0) {
        e = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (CharaGetId_214a80(e) < 0x80) {
            continue;
        }
        if (!(CharaGetId_214a80(e) < 0x9C)) {
            continue;
        }
        if (CharaGetActionMode_213850(e) == 0x12) {
            continue;
        }
        u = ObjFindById_3bb3a0(w->x1C, CharaGetId_214a80(e));
        if (u == 0) {
            continue;
        }
        if (u->isBusy() != 0) {
            continue;
        }
        info = u->getInfo();
        if (info == 0) {
            continue;
        }
        if (info->kind == 0) {
            continue;
        }
        CharaGetPos_2388a0(e, &pos);
        VecSub_1cbd00(&d, &pos, at);
        if (d.y < lo) {
            continue;
        }
        if (!(d.y <= hi)) {
            continue;
        }
        dist = VecLengthSqXZ_1cb450(&d);
        if (!(dist <= (rad + CharaGetCollRadius_2386a0(e)) * (rad + CharaGetCollRadius_2386a0(e)))) {
            continue;
        }
        d.y = 0.0f;
        VecNormalize_1cbb80(&d, &d);
        if (VecDot3_1cba90(&d, &dir) < 0.5f) {
            continue;
        }
        if (ObjFindById_3bb3a0(w->x1C, CharaGetId_214a80(e)) == 0) {
            continue;
        }
        best = CharaGetId_214a80(e);
    }
    return best;
}
