#include "types.h"

class C {
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
    virtual s32 v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual s32 v74(s32 f);
};

struct Ctx {
    u8    pad000[0x14];
    void *m14;
    u8    pad018[0x4];
    void *m1C;
};

extern "C" Ctx *GetGameData_1fede0(void);
extern "C" C *CharaMgrPoolFindById_3a8c60(void *t, s32 id);
extern "C" C *ObjFindById_3bb3a0(void *t, s32 id);

extern "C" s32 ActorGetMpById_2cd780(s32 id, s32 *out)
{
    Ctx *ctx;
    C   *o;
    s32  res;

    ctx = GetGameData_1fede0();
    res = 0;
    if (out != 0) {
        *out = 0;
    }
    if (id < 12) {
        o = CharaMgrPoolFindById_3a8c60(ctx->m14, id);
        if (o != 0) {
            res = o->v65();
            if (out != 0) {
                *out = o->v74(1);
            }
        }
    } else {
        o = ObjFindById_3bb3a0(ctx->m1C, id);
        if (o != 0) {
            res = o->v65();
            if (out != 0) {
                *out = o->v74(1);
            }
        }
    }
    return res;
}
