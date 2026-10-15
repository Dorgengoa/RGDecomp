#include "types.h"

typedef struct Elem2_0028DDE0 {
    u8 pad0[0x2C];
    s16 unk2C;
} Elem2_0028DDE0;

typedef struct Elem0028DDE0 {
    u8 pad0[0x10];
    Elem2_0028DDE0 *unk10;
} Elem0028DDE0;

class Obj0028DDE0 {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual void v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
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
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual void v224();
    virtual void v225();
    virtual Elem0028DDE0 *get390();
};

typedef struct Ctx0028DDE0 {
    u8 pad0[0x18];
    s32 unk18;
} Ctx0028DDE0;

typedef struct Rect0028DDE0 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect0028DDE0;

extern "C" {
void GetDrawCtxNameTable_15de40();
Ctx0028DDE0 *GetGameData_1fede0();
void WorkIconCopyItemIcon_28df20(Rect0028DDE0 *, s16);
Elem2_0028DDE0 *CharaGetIconRecMaybe_3ae3e0(Obj0028DDE0 *);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Obj0028DDE0 *PartyGetSlotChara_3c2fb0(s32, s32);
s32 WorkIconBuildPartyWeaponsMaybe_28dde0(void);
}

s32 WorkIconBuildPartyWeaponsMaybe_28dde0(void)
{
    Rect0028DDE0 r;
    Ctx0028DDE0 *ctx;
    Obj0028DDE0 *obj;
    Elem0028DDE0 *e;
    Elem2_0028DDE0 *e2;
    s32 n;
    s32 i;
    s32 x;

    ctx = GetGameData_1fede0();
    if (ctx == 0) {
        return 1;
    }
    n = ctx->unk18;
    n = PartyCountMembers_3c2010(n, 1, 1) + PartyCountReserve_3c1c20(n, 1, 1);
    for (i = 0; i < n; i++) {
        obj = PartyGetSlotChara_3c2fb0(ctx->unk18, i);
        if (obj == 0) {
            return 2;
        }
        e = obj->get390();
        if (e != 0) {
            GetDrawCtxNameTable_15de40();
            e2 = CharaGetIconRecMaybe_3ae3e0(obj);
            if (e2 != 0) {
                Elem2_0028DDE0 *q = e->unk10;
                s16 k;
                x = e2->unk2C;
                k = q->unk2C;
                r.x = (x % 8) << 5;
                r.y = (x / 8) << 5;
                r.w = 0x20;
                r.h = 0x20;
                WorkIconCopyItemIcon_28df20(&r, k);
            }
        }
    }
    return 0;
}
