#include "types.h"

extern struct { s32 v; s32 pad[3]; } D_00465D78;
extern s32 D_004838EC;
extern s16 D_004801DE[4];

struct Sub { u8 pad[0x27]; s8 lv; };
class VE {
public:
    virtual s32 v0(s32);
    virtual s32 v1(s32);
    virtual s32 v2(s32);
    virtual s32 v3(s32);
    virtual s32 v4(s32);
    virtual s32 v5(s32);
    virtual s32 v6(s32);
    virtual s32 v7(s32);
    virtual s32 v8(s32);
    virtual s32 v9(s32);
    virtual s32 v10(s32);
    virtual s32 v11(s32);
    virtual s32 v12(s32);
    virtual s32 v13(s32);
    virtual s32 v14(s32);
    virtual s32 v15(s32);
    virtual s32 v16(s32);
    virtual s32 v17(s32);
    virtual s32 v18(s32);
    virtual s32 v19(s32);
    virtual s32 v20(s32);
    virtual s32 v21(s32);
    virtual s32 v22(s32);
    virtual s32 v23(s32);
    virtual s32 v24(s32);
    virtual s32 v25(s32);
    virtual s32 v26(s32);
    virtual s32 v27(s32);
    virtual s32 v28(s32);
    virtual s32 v29(s32);
    virtual s32 v30(s32);
    virtual s32 v31(s32);
    virtual s32 v32(s32);
    virtual s32 v33(s32);
    virtual s32 v34(s32);
    virtual s32 v35(s32);
    virtual s32 v36(s32);
    virtual s32 v37(s32);
    virtual s32 v38(s32);
    virtual s32 v39(s32);
    virtual s32 v40(s32);
    virtual s32 v41(s32);
    virtual s32 v42(s32);
    virtual s32 v43(s32);
    virtual s32 v44(s32);
    virtual s32 v45(s32);
    virtual s32 v46(s32);
    virtual s32 v47(s32);
    virtual s32 v48(s32);
    virtual s32 v49(s32);
    virtual s32 v50(s32);
    virtual s32 v51(s32);
    virtual s32 v52(s32);
    virtual s32 v53(s32);
    virtual s32 v54(s32);
    virtual s32 v55(s32);
    virtual s32 v56(s32);
    virtual s32 v57(s32);
    virtual s32 v58(s32);
    virtual s32 v59(s32);
    virtual s32 v60(s32);
    virtual s32 v61(s32);
    virtual s32 v62(s32);
    virtual s32 v63(s32);
    virtual s32 v64(s32);
    virtual s32 v65(s32);
    virtual s32 v66(s32);
    virtual s32 v67(s32);
    virtual s32 v68(s32);
    virtual s32 v69(s32);
    virtual s32 v70(s32);
    virtual s32 v71(s32);
    virtual s32 v72(s32);
    virtual s32 v73(s32);
    virtual s32 v74(s32);
    virtual s32 v75(s32);
    virtual s32 v76(s32);
    virtual s32 v77(s32);
    virtual s32 v78(s32);
    virtual s32 v79(s32);
    virtual s32 v80(s32);
    virtual s32 v81(s32);
    virtual s32 v82(s32);
    virtual s32 v83(s32);
    virtual s32 v84(s32);
    virtual s32 v85(s32);
    virtual s32 v86(s32);
    virtual s32 v87(s32);
    virtual s32 v88(s32);
    virtual s32 v89(s32);
    virtual s32 v90(s32);
    virtual s32 v91(s32);
    virtual s32 v92(s32);
    virtual s32 v93(s32);
    virtual s32 v94(s32);
    virtual s32 v95(s32);
    virtual s32 v96(s32);
    virtual s32 v97(s32);
    virtual s32 v98(s32);
    virtual s32 v99(s32);
    virtual s32 v100(s32);
    virtual s32 v101(s32);
    virtual s32 v102(s32);
    virtual s32 v103(s32);
    virtual s32 v104(s32);
    u8 pad4[0x14];
    Sub *p18;
};

extern "C" s32 InsectItemGetNextLevelExp_3d1820(VE *o)
{
    return o->v104(o->p18->lv + 1);
}

extern "C" s32 func_003D1840(VE *o, s32 n)
{
    if (n <= 1 || D_00465D78.v + 1 < n) return 0;
    if (D_004838EC) return D_004801DE[n];
    return 0;
}
