#include "types.h"

class Handler {
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
    virtual void Attach(void *);
};

struct Mgr {
    u8 pad[0x18];
    s32 unk18;
};

struct Ent {
    s16 unk0;
    u8 pad2[0x6C - 2];
    s32 unk6C;
    s8 unk70;
    s8 unk71;
};

extern "C" {
s32 GetActionMgr_1fdb50(void);
Mgr *GetGameData_1fede0(void);
Ent *CharaGetExecInfo_2149f0(s32);
void CharaExecInfoInit_219100(Ent *);
s32 ActionMgrFindById_233b50(s32, s32);
s32 ExecInfoInitFromInvItem_3a7430(Ent *, s32, s32, s32);
Handler *ActorCastToUnit_3b8770(s32);
Handler *ActorCastToChara_3b87b0(s32);
s32 PartyAllIncapacitated_3c07c0(s32, s32);
s32 ActorFindById_3eb870(Mgr *, s32);
}

extern "C" s32 CharaQueueItemUse_2ef680(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4)
{
    Mgr *o;
    s32 h;
    s32 id;
    s32 r;
    Ent *e;
    Handler *p;
    bool found;

    o = GetGameData_1fede0();
    h = GetActionMgr_1fdb50();
    id = ActorFindById_3eb870(o, arg0);
    if (id == 0) {
        return 0;
    }
    r = ActionMgrFindById_233b50(h, arg0);
    if (r == 0) {
        return 0;
    }
    e = CharaGetExecInfo_2149f0(r);
    CharaExecInfoInit_219100(e);
    if (PartyAllIncapacitated_3c07c0(o->unk18, 1) != 0) {
        return 0;
    }
    if (ExecInfoInitFromInvItem_3a7430(e, arg0, arg1, 0) == 0) {
        return 0;
    }
    e->unk71 = arg3;
    if (arg4 != -1) {
        e->unk0 = arg4;
    }
    found = false;
    p = ActorCastToChara_3b87b0(id);
    if (p != 0) {
        p->Attach(e);
        found = true;
    }
    p = ActorCastToUnit_3b8770(id);
    if (p != 0) {
        p->Attach(e);
        found = true;
    }
    if (!found) {
        CharaExecInfoInit_219100(e);
        return 0;
    }
    e->unk6C = arg2;
    e->unk70 = 1;
    return 1;
}
