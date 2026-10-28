/* rgp:protos */
#line 1
#include "types.h"

class VO231 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5C() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20C() { return VCM0(s32, 0x20C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v260(s32 a0) { VCM(void, (void *, s32), 0x260, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v2A8() { return VCM0(s32, 0x2A8); }
    s32 v2AC() { return VCM0(s32, 0x2AC); }
};

typedef struct Obj231 {
    u8 pad0[0xA44];
    u32 mA44;
} Obj231;

typedef struct Sub18 {
    u8 pad0[0x30];
    s16 m30;
    u8 pad32[0x18E - 0x32];
    s16 m18E;
} Sub18;

typedef struct Sys231 {
    u8 pad0[0x10];
    s32 m10;
    u8 pad14[0x18 - 0x14];
    Sub18 *m18;
} Sys231;

typedef struct St231 {
    VO231 *o;
    f32 f;
} St231;

extern "C" {
void SrtCtor_1c7320(void *);
f32 GameSceneGetTimeStep_1ceba0(s32);
f32 ParamTableGetAlpha_1cfb40(s32, s32);
s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
s32 MapDataIsJasterOnly_1e7a90(s32);
s32 GetCurrentScene_1f5be0(void);
Sys231 *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
void CharaActDispatch_20d190(Obj231 *, St231 *);
void CharaAddFlags_212460(Obj231 *, u64);
void CharaClearFlags_2124a0(Obj231 *);
s32 CharaGetActionCategory_213690(Obj231 *);
s32 CharaGetActionKind_213840(Obj231 *);
s32 CharaGetId_214a80(Obj231 *);
void CharaEnterDeathStateMaybe_217a00(Obj231 *);
void CharaGetSrt_238910(Obj231 *, void *);
s32 StateFlagTest_3ccd70(s32, s32);
VO231 *ActorFindById_3eb870(Sys231 *, s32);
u8 *DListGetHead_42ea60(u8 *);
u8 *DListGetNext_42eb30(u8 *);
void SrtCopyThunk_1c71f0(Obj231 *, void *);
void ActionMgrRunActions_231f90(u8 *arg0);
}

void ActionMgrRunActions_231f90(u8 *arg0)
{
    St231 st __attribute__((aligned(16)));
    Obj231 *list[226];
    u8 buf[0x50] __attribute__((aligned(16)));
    Sys231 *sys;
    s32 cam;
    s32 n;
    u8 *it;
    Obj231 *o;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    Obj231 **pp;
    Obj231 **q;
    u32 v;
    Obj231 *t;
    s32 id;
    bool flag;
    s32 r;
    s32 on;
    bool ok;

    sys = GetGameData_1fede0();
    cam = GetCurrentScene_1f5be0();
    n = 0;
    it = DListGetHead_42ea60(arg0 + 0x20);
    while (it != 0) {
        o = (Obj231 *)(it + 0x10);
        SrtCtor_1c7320(buf);
        CharaGetSrt_238910(o, buf);
        SrtCopyThunk_1c71f0(o, buf);
        list[n++] = o;
        it = DListGetNext_42eb30(it);
    }
    for (i = 0; i < n; i++) {
        pp = &list[i];
        o = *pp;
        if (((short)CharaGetId_214a80(o)) < 0 || ((short)CharaGetId_214a80(o)) >= 12) {
            for (j = i + 1; j < n; j++) {
                o = *(Obj231 **)((u32)&list[j]);
                if (((short)CharaGetId_214a80(o)) >= 0 && ((short)CharaGetId_214a80(o)) < 12) {
                    break;
                }
            }
            if (j >= n) {
                break;
            }
            t = list[j];
            for (; i < j; j--) {
                list[j] = list[j - 1];
            }
            *pp = t;
        }
    }
    for (k = 0; k < n; k++) {
        pp = &list[k];
        if (!((*pp)->mA44 & 0x80000)) {
            for (m = k + 1; m < n; m++) {
                if (list[m]->mA44 & 0x80000) {
                    break;
                }
            }
            if (m >= n) {
                break;
            }
            t = list[m];
            for (; k < m; m--) {
                list[m] = list[m - 1];
            }
            *pp = t;
        }
    }
    id = sys->m18->m18E;
    flag = false;
    r = MapSlotsFindActiveBlockById_1e4730(GetMapMgr_201a90(), *(s16 *)(*(u8 **)((u8 *)sys + 0x18) + 0x30), 0);
    if (r != 0 && ((unsigned char)MapDataIsJasterOnly_1e7a90(r)) != 0 && id == 0) {
        flag = true;
    }
    for (i = 0; i < n; i++) {
        t = list[i];
        st.o = ActorFindById_3eb870(sys, ((short)CharaGetId_214a80(t)));
        st.f = GameSceneGetTimeStep_1ceba0(cam);
        on = StateFlagTest_3ccd70(sys->m10, 0x7FA) & 0xFF;
        if (st.o != 0 && st.o->v5C() == 0x30DB) {
            on = 0;
        }
        t->mA44 = on ? (t->mA44 | 0x400000) : (t->mA44 & ~0x400000);
        if (flag && ((short)CharaGetId_214a80(t)) >= 0 && ((short)CharaGetId_214a80(t)) < 12 && id != ((short)CharaGetId_214a80(t))) {
            CharaAddFlags_212460(t, (u64)0x80000 << 32);
        }
        if (st.o != 0) {
            ok = true;
            switch (((short)CharaGetActionKind_213840(t))) {
            case 21:
            case 22:
            case 23:
                ok = false;
            default:
                if (st.o->v2A8() != 0) {
                    if (((short)CharaGetActionKind_213840(t)) != 0x1D) {
                        CharaClearFlags_2124a0(t);
                        if (st.o->v2AC() != 0) {
                            CharaAddFlags_212460(t, (u64)0x8000 << 32);
                        } else {
                            CharaAddFlags_212460(t, (u64)0x20000 << 32);
                        }
                        CharaAddFlags_212460(t, (u64)0x1000 << 32);
                    } else {
                        CharaClearFlags_2124a0(t);
                        if (ParamTableGetAlpha_1cfb40(cam, ((short)CharaGetId_214a80(t))) <= 0.0f) {
                            CharaEnterDeathStateMaybe_217a00(t);
                        }
                    }
                } else if (ok) {
                    switch (st.o->v20C()) {
                    case 1:
                        CharaAddFlags_212460(t, (u64)0x800 << 32);
                        break;
                    case 2:
                        CharaAddFlags_212460(t, (u64)0x10000 << 32);
                        break;
                    case 4:
                        CharaAddFlags_212460(t, (u64)0x10 << 32);
                        break;
                    case 5:
                        CharaAddFlags_212460(t, (u64)0x80 << 32);
                        break;
                    case 6:
                        CharaAddFlags_212460(t, (u64)0x40 << 32);
                        break;
                    case 7:
                    case 26:
                    case 27:
                    case 28:
                        CharaAddFlags_212460(t, (u64)0x20 << 32);
                        break;
                    case 10:
                        CharaAddFlags_212460(t, (u64)0x100 << 32);
                        break;
                    }
                }
                break;
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
                break;
            }
        }
        CharaActDispatch_20d190(t, &st);
        if (st.o != 0) {
            st.o->v260(CharaGetActionCategory_213690(t));
        }
    }
}
