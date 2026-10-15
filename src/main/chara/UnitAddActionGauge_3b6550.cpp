#include "types.h"

extern "C" {
extern const struct { s32 v; s32 pad[3]; } D_00465CD0;
extern struct { s32 v; s32 pad[3]; } D_00465CD8;
extern void *ActorCastToChara_3b87b0(void *);
extern s32 CharaIsPartyLeader_3ae1a0(void *);
extern void *GetCurrentScene_1f5be0(void);
extern void ActionPacketReset_3e3d00(void *req);
extern void ActionPacketInitGaugeEmpty_3e3030(void *req, void *x, void *o);
extern void EventFireTriggers_3e2660(void *req, s32 z);
}

class C {
public:
    virtual s32 v0(f32);
    virtual s32 v1(f32);
    virtual s32 v2(f32);
    virtual s32 v3(f32);
    virtual s32 v4(f32);
    virtual s32 v5(f32);
    virtual s32 v6(f32);
    virtual s32 v7(f32);
    virtual s32 v8(f32);
    virtual s32 v9(f32);
    virtual s32 v10(f32);
    virtual s32 v11(f32);
    virtual s32 v12(f32);
    virtual s32 v13(f32);
    virtual s32 v14(f32);
    virtual s32 v15(f32);
    virtual s32 v16(f32);
    virtual s32 v17(f32);
    virtual s32 v18(f32);
    virtual s32 v19(f32);
    virtual s32 v20(f32);
    virtual s32 v21(f32);
    virtual s32 v22(f32);
    virtual s32 v23(f32);
    virtual s32 v24(f32);
    virtual s32 v25(f32);
    virtual s32 v26(f32);
    virtual s32 v27(f32);
    virtual s32 v28(f32);
    virtual s32 v29(f32);
    virtual s32 v30(f32);
    virtual s32 v31(f32);
    virtual s32 v32(f32);
    virtual s32 v33(f32);
    virtual s32 v34(f32);
    virtual s32 v35(f32);
    virtual s32 v36(f32);
    virtual s32 v37(f32);
    virtual s32 v38(f32);
    virtual s32 v39(f32);
    virtual s32 v40(f32);
    virtual s32 v41(f32);
    virtual s32 v42(f32);
    virtual s32 v43(f32);
    virtual s32 v44(f32);
    virtual s32 v45(f32);
    virtual s32 v46(f32);
    virtual s32 v47(f32);
    virtual s32 v48(f32);
    virtual s32 v49(f32);
    virtual s32 v50(f32);
    virtual s32 v51(f32);
    virtual s32 v52(f32);
    virtual s32 v53(f32);
    virtual s32 v54(f32);
    virtual s32 v55(f32);
    virtual s32 v56(f32);
    virtual s32 v57(f32);
    virtual s32 v58(f32);
    virtual s32 v59(f32);
    virtual s32 v60(f32);
    virtual s32 v61(f32);
    virtual s32 v62(f32);
    virtual s32 v63(f32);
    virtual s32 v64(f32);
    virtual s32 v65(f32);
    virtual s32 v66(f32);
    virtual s32 v67(f32);
    virtual s32 v68(f32);
    virtual s32 v69(f32);
    virtual s32 v70(f32);
    virtual s32 v71(f32);
    virtual s32 v72(f32);
    virtual s32 v73(f32);
    virtual s32 v74(f32);
    virtual s32 v75(f32);
    virtual s32 v76(f32);
    virtual s32 v77(f32);
    virtual s32 v78(f32);
    virtual s32 v79(f32);
    virtual s32 v80(f32);
    virtual s32 v81(f32);
    virtual s32 v82(f32);
    virtual s32 v83(f32);
    virtual s32 v84(f32);
    virtual s32 v85(f32);
    virtual s32 v86(f32);
    virtual s32 v87(f32);
    virtual s32 v88(f32);
    virtual s32 v89(f32);
    virtual s32 v90(f32);
    virtual s32 v91(f32);
    virtual s32 v92(f32);
    virtual s32 v93(f32);
    virtual s32 v94(f32);
    virtual s32 v95(f32);
    virtual s32 v96(f32);
    virtual s32 v97(f32);
    virtual s32 v98(f32);
    virtual s32 v99(f32);
    virtual s32 v100(f32);
    virtual s32 v101(f32);
    virtual s32 v102(f32);
    virtual s32 v103(f32);
    virtual s32 v104(f32);
    virtual s32 v105(f32);
    virtual s32 v106(f32);
    virtual s32 v107(f32);
    virtual s32 v108(f32);
    virtual s32 v109(f32);
    virtual s32 v110(f32);
    virtual s32 v111(f32);
    virtual s32 v112(f32);
    virtual s32 v113(f32);
    virtual s32 v114(f32);
    virtual s32 v115(f32);
    virtual s32 v116(f32);
    virtual s32 v117(f32);
    virtual s32 v118(f32);
    virtual s32 v119(f32);
    virtual s32 v120(f32);
    virtual s32 v121(f32);
    virtual s32 v122(f32);
    virtual s32 v123(f32);
    virtual s32 v124(f32);
    virtual s32 v125(f32);
    virtual s32 v126(f32);
    virtual s32 v127(f32);
    virtual s32 v128(f32);
    virtual s32 v129(f32);
    virtual s32 v130(f32);
    virtual s32 v131(f32);
    virtual s32 v132(f32);
    virtual s32 v133(f32);
    virtual s32 v134(f32);
    virtual s32 v135(f32);
    virtual s32 v136(f32);
    virtual s32 v137(f32);
    virtual s32 v138(f32);
    virtual s32 v139(f32);
    virtual s32 v140(f32);
    virtual s32 v141(f32);
    virtual s32 v142(f32);
    virtual s32 v143(f32);
    virtual s32 v144(f32);
    virtual s32 v145(f32);
    virtual s32 v146(f32);
    virtual s32 v147(f32);
    virtual s32 v148(f32);
    virtual s32 v149(f32);
    virtual s32 v150(f32);
    virtual s32 v151(f32);
    virtual s32 v152(f32);
    virtual s32 v153(f32);
    u8 pad4[0x1C0 - 4];
    bool f0 : 1;
    f32 val;
    bool g0 : 1;
};

extern "C" s32 UnitAddActionGauge_3b6550(C *o, s32 n)
{
    return o->v153((f32)((s32)o->val + n));
}

extern "C" s32 func_003B6580(C *o, f32 v)
{
    f32 lim;
    s32 m;
    s32 r;
    void *p;
    void *x;
    u8 req[0x30];
    r = o->f0;
    o->val = v;
    m = D_00465CD0.v;
    if (!(o->val < (f32)m)) {
        o->val = (f32)m;
        o->f0 = true;
        o->g0 = false;
    }
    if (o->val <= 0.0f) {
        lim = (f32)D_00465CD8.v;
        if (o->val < lim) o->val = lim;
        o->f0 = false;
        o->g0 = true;
        p = ActorCastToChara_3b87b0(o);
        if (p != 0 && CharaIsPartyLeader_3ae1a0(p) != 0) {
            x = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(req);
            ActionPacketInitGaugeEmpty_3e3030(req, x, o);
            EventFireTriggers_3e2660(req, 0);
        }
    }
    return r;
}
