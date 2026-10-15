#include "types.h"

class VO231 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 v5C();
    virtual void e22();
    virtual void e23();
    virtual void e24();
    virtual void e25();
    virtual void e26();
    virtual void e27();
    virtual void e28();
    virtual void e29();
    virtual void e30();
    virtual void e31();
    virtual void e32();
    virtual void e33();
    virtual void e34();
    virtual void e35();
    virtual void e36();
    virtual void e37();
    virtual void e38();
    virtual void e39();
    virtual void e40();
    virtual void e41();
    virtual void e42();
    virtual void e43();
    virtual void e44();
    virtual void e45();
    virtual void e46();
    virtual void e47();
    virtual void e48();
    virtual void e49();
    virtual void e50();
    virtual void e51();
    virtual void e52();
    virtual void e53();
    virtual void e54();
    virtual void e55();
    virtual void e56();
    virtual void e57();
    virtual void e58();
    virtual void e59();
    virtual void e60();
    virtual void e61();
    virtual void e62();
    virtual void e63();
    virtual void e64();
    virtual void e65();
    virtual void e66();
    virtual void e67();
    virtual void e68();
    virtual void e69();
    virtual void e70();
    virtual void e71();
    virtual void e72();
    virtual void e73();
    virtual void e74();
    virtual void e75();
    virtual void e76();
    virtual void e77();
    virtual void e78();
    virtual void e79();
    virtual void e80();
    virtual void e81();
    virtual void e82();
    virtual void e83();
    virtual void e84();
    virtual void e85();
    virtual void e86();
    virtual void e87();
    virtual void e88();
    virtual void e89();
    virtual void e90();
    virtual void e91();
    virtual void e92();
    virtual void e93();
    virtual void e94();
    virtual void e95();
    virtual void e96();
    virtual void e97();
    virtual void e98();
    virtual void e99();
    virtual void e100();
    virtual void e101();
    virtual void e102();
    virtual void e103();
    virtual void e104();
    virtual void e105();
    virtual void e106();
    virtual void e107();
    virtual void e108();
    virtual void e109();
    virtual void e110();
    virtual void e111();
    virtual void e112();
    virtual void e113();
    virtual void e114();
    virtual void e115();
    virtual void e116();
    virtual void e117();
    virtual void e118();
    virtual void e119();
    virtual void e120();
    virtual void e121();
    virtual void e122();
    virtual void e123();
    virtual void e124();
    virtual void e125();
    virtual void e126();
    virtual void e127();
    virtual void e128();
    virtual s32 v20C();
    virtual void e130();
    virtual void e131();
    virtual void e132();
    virtual void e133();
    virtual void e134();
    virtual void e135();
    virtual void e136();
    virtual void e137();
    virtual void e138();
    virtual void e139();
    virtual void e140();
    virtual void e141();
    virtual void e142();
    virtual void e143();
    virtual void e144();
    virtual void e145();
    virtual void e146();
    virtual void e147();
    virtual void e148();
    virtual void e149();
    virtual void v260(s32);
    virtual void e151();
    virtual void e152();
    virtual void e153();
    virtual void e154();
    virtual void e155();
    virtual void e156();
    virtual void e157();
    virtual void e158();
    virtual void e159();
    virtual void e160();
    virtual void e161();
    virtual void e162();
    virtual void e163();
    virtual void e164();
    virtual void e165();
    virtual void e166();
    virtual void e167();
    virtual s32 v2A8();
    virtual s32 v2AC();
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
    St231 st;
    Obj231 *list[226];
    u8 buf[0x50];
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
        if (CharaGetId_214a80(o) < 0 || CharaGetId_214a80(o) >= 12) {
            for (j = i + 1; j < n; j++) {
                o = *(Obj231 **)((u32)&list[j]);
                if (CharaGetId_214a80(o) >= 0 && CharaGetId_214a80(o) < 12) {
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
    if (r != 0 && MapDataIsJasterOnly_1e7a90(r) != 0 && id == 0) {
        flag = true;
    }
    for (i = 0; i < n; i++) {
        t = list[i];
        st.o = ActorFindById_3eb870(sys, CharaGetId_214a80(t));
        st.f = GameSceneGetTimeStep_1ceba0(cam);
        on = StateFlagTest_3ccd70(sys->m10, 0x7FA) & 0xFF;
        if (st.o != 0 && st.o->v5C() == 0x30DB) {
            on = 0;
        }
        t->mA44 = on ? (t->mA44 | 0x400000) : (t->mA44 & ~0x400000);
        if (flag && CharaGetId_214a80(t) >= 0 && CharaGetId_214a80(t) < 12 && id != CharaGetId_214a80(t)) {
            CharaAddFlags_212460(t, (u64)0x80000 << 32);
        }
        if (st.o != 0) {
            ok = true;
            switch (CharaGetActionKind_213840(t)) {
            case 21:
            case 22:
            case 23:
                ok = false;
            default:
                if (st.o->v2A8() != 0) {
                    if (CharaGetActionKind_213840(t) != 0x1D) {
                        CharaClearFlags_2124a0(t);
                        if (st.o->v2AC() != 0) {
                            CharaAddFlags_212460(t, (u64)0x8000 << 32);
                        } else {
                            CharaAddFlags_212460(t, (u64)0x20000 << 32);
                        }
                        CharaAddFlags_212460(t, (u64)0x1000 << 32);
                    } else {
                        CharaClearFlags_2124a0(t);
                        if (ParamTableGetAlpha_1cfb40(cam, CharaGetId_214a80(t)) <= 0.0f) {
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
