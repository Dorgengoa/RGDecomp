#include "types.h"

struct GObj {
    u8 pad000[0x1B0];
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
    virtual void v15(f32);
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
};

struct MObj {
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
    virtual s32 w72();
};

extern GObj *D_004832F8;
extern s32 D_004832FC;
extern f32 D_004832F0;
extern f32 D_004832F4;
extern f32 D_0047FBC0, D_0047FBC4, D_0047FBC8, D_0047FBCC;
extern f32 D_0047D410, D_0047D414, D_0047D3B4, D_0047D288;
extern u8 D_00463EC0[];

extern "C" {
void GetDrawCtxNameTable_15de40(void);
void MemStackReset_14d830(s32);
void ModelObjExCopy_1aff40(void *, void *, s32);
void ModelSetPos_151110(void *, f32 *);
void ModelSetRot_151080(void *, f32 *);
void ModelSetScale_150ff0(void *, f32 *);
void ModelObjPlayMotionByName_1867a0(void *, void *, s32);
s32 MenuObjInsectGetDefId_386d70(void *);
void *InsectCageAdjFindById_3916e0(s32);
void InsectModelApplyColorRec_3913f0(void *, s32, s32);
void InsectCagePreviewModelSetup_389370(void *ent, s32 mode);
}

void InsectCagePreviewModelSetup_389370(void *ent, s32 mode)
{
    volatile f32 va[4];
    f32 vb[4];
    f32 vc[4];
    f32 vd[4];
    f32 ve[4];
    GObj *o1;
    u8 *q;
    u32 n;
    s32 id;
    void *o;
    f32 t;

    GetDrawCtxNameTable_15de40();
    MemStackReset_14d830(D_004832FC);
    D_004832F8->v21();
    if (ent != 0) {
        ModelObjExCopy_1aff40(ent, D_004832F8, D_004832FC);
        va[0] = D_0047FBC0;
        va[1] = D_0047FBC4;
        va[2] = D_0047FBC8;
        va[3] = D_0047FBCC;
        va[2] = 70.0f;
        va[0] = 0.0f;
        va[1] = 0.0f;
        ModelSetPos_151110(D_004832F8, (f32 *)va);
        o1 = D_004832F8;
        q = (u8 *)vb;
        n = 0x10;
        if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
        vb[0] = D_0047D410;
        vb[1] = D_0047D414;
        vb[2] = 0.0f;
        ModelSetRot_151080(o1, vb);
        *(s32 *)((u8 *)D_004832F8 + 0x450) = 0;
        ModelObjPlayMotionByName_1867a0(D_004832F8, (u8 *)ent + 0x974, 0);
        D_004832F8->v15(1.0f);
        o = InsectCageAdjFindById_3916e0(MenuObjInsectGetDefId_386d70(ent));
        id = *(s32 *)((u8 *)ent + 0x970);
        switch (mode) {
        case 0:
            D_004832F0 = 1940;
            D_004832F4 = 1998;
            if (o != 0) {
                D_004832F0 = *(f32 *)((u8 *)o + 0x8);
                D_004832F4 = *(f32 *)((u8 *)o + 0xC);
                t = *(f32 *)((u8 *)o + 0x4);
                o1 = D_004832F8;
                q = (u8 *)vc;
                n = 0x10;
                if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
                vc[0] = t;
                vc[1] = t;
                vc[2] = t;
                ModelSetScale_150ff0(o1, vc);
            } else {
                D_004832F0 = 1940;
                D_004832F4 = 1988;
                o1 = D_004832F8;
                q = (u8 *)vd;
                n = 0x10;
                if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
                vd[0] = D_0047D3B4;
                vd[1] = D_0047D3B4;
                vd[2] = D_0047D3B4;
                ModelSetScale_150ff0(o1, vd);
                if (*(s8 *)((u8 *)ent + 0x984) != 0) {
                    D_004832F4 = D_004832F4 + 30.0f;
                }
            }
            break;
        case 1:
            D_004832F0 = 1855;
            D_004832F4 = 1888.0f;
            if (*(s8 *)((u8 *)ent + 0x984) != 0) {
                D_004832F4 = D_004832F4 + 9.5f;
            }
            o1 = D_004832F8;
            q = (u8 *)ve;
            n = 0x10;
            if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
            ve[0] = D_0047D288;
            ve[1] = D_0047D288;
            ve[2] = D_0047D288;
            ModelSetScale_150ff0(o1, ve);
            break;
        }
        ModelObjPlayMotionByName_1867a0(D_004832F8, D_00463EC0, 4);
        D_004832F8->v15(1.0f);
        InsectModelApplyColorRec_3913f0(D_004832F8, id, ((MObj *)*(void **)((u8 *)ent + 0x96C))->w72());
    }
}
