#include "types.h"

struct Def {
    u8 pad0[2];
    s16 m2;
    u8 pad4[4];
    s16 m8;
};

class Unit {
public:
    virtual void u0();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual void u5();
    virtual void u6();
    virtual void u7();
    virtual void u8();
    virtual void u9();
    virtual void u10();
    virtual void u11();
    virtual void u12();
    virtual void u13();
    virtual void u14();
    virtual void u15();
    virtual void u16();
    virtual void u17();
    virtual void u18();
    virtual void u19();
    virtual void u20();
    virtual void u21();
    virtual void u22();
    virtual void u23();
    virtual void u24();
    virtual void u25();
    virtual void u26();
    virtual void u27();
    virtual void u28();
    virtual void u29();
    virtual void u30();
    virtual void u31();
    virtual void u32();
    virtual void u33();
    virtual void u34();
    virtual void u35();
    virtual void u36();
    virtual void u37();
    virtual void u38();
    virtual void u39();
    virtual void u40();
    virtual void u41();
    virtual void u42();
    virtual void u43();
    virtual void u44();
    virtual s32 isActive();
    virtual void u46();
    virtual void u47();
    virtual void u48();
    virtual void u49();
    virtual void u50();
    virtual void u51();
    virtual void u52();
    virtual void u53();
    virtual s32 letter();
    virtual void setLetter(s8);
    virtual void u56();
    virtual void u57();
    virtual void u58();
    virtual void u59();
    virtual void u60();
    virtual void u61();
    virtual void u62();
    virtual void u63();
    virtual void u64();
    virtual void u65();
    virtual void u66();
    virtual void u67();
    virtual void u68();
    virtual void u69();
    virtual void u70();
    virtual void u71();
    virtual void u72();
    virtual void u73();
    virtual void u74();
    virtual void u75();
    virtual void u76();
    virtual void u77();
    virtual void u78();
    virtual void u79();
    virtual void u80();
    virtual void u81();
    virtual void u82();
    virtual void u83();
    virtual void u84();
    virtual void u85();
    virtual void u86();
    virtual void u87();
    virtual void u88();
    virtual void u89();
    virtual void u90();
    virtual void u91();
    virtual void u92();
    virtual void u93();
    virtual void u94();
    virtual void u95();
    virtual void u96();
    virtual void u97();
    virtual void u98();
    virtual void u99();
    virtual void u100();
    virtual void u101();
    virtual void u102();
    virtual void u103();
    virtual void u104();
    virtual void u105();
    virtual void u106();
    virtual void u107();
    virtual void u108();
    virtual void u109();
    virtual void u110();
    virtual void u111();
    virtual void u112();
    virtual void u113();
    virtual void u114();
    virtual void u115();
    virtual void u116();
    virtual void u117();
    virtual void u118();
    virtual void u119();
    virtual void u120();
    virtual void u121();
    virtual void u122();
    virtual void u123();
    virtual void u124();
    virtual void u125();
    virtual void u126();
    virtual void u127();
    virtual void u128();
    virtual void u129();
    virtual void u130();
    virtual void u131();
    virtual void u132();
    virtual void u133();
    virtual void u134();
    virtual void u135();
    virtual void u136();
    virtual void u137();
    virtual void u138();
    virtual void u139();
    virtual void u140();
    virtual void u141();
    virtual void u142();
    virtual void u143();
    virtual void u144();
    virtual void u145();
    virtual void u146();
    virtual void u147();
    virtual void u148();
    virtual void u149();
    virtual void u150();
    virtual void u151();
    virtual void u152();
    virtual void u153();
    virtual void u154();
    virtual void u155();
    virtual void u156();
    virtual void u157();
    virtual void u158();
    virtual void u159();
    virtual void u160();
    virtual void u161();
    virtual void u162();
    virtual void u163();
    virtual void u164();
    virtual void u165();
    virtual void u166();
    virtual void u167();
    virtual void u168();
    virtual void u169();
    virtual void u170();
    virtual void u171();
    virtual void u172();
    virtual void u173();
    virtual void u174();
    virtual void u175();
    virtual void u176();
    virtual void u177();
    virtual void u178();
    virtual void u179();
    virtual void u180();
    virtual void u181();
    virtual void u182();
    virtual void u183();
    virtual void u184();
    virtual void u185();
    virtual void u186();
    virtual void u187();
    virtual void u188();
    virtual void u189();
    virtual void u190();
    virtual void u191();
    virtual void u192();
    virtual void u193();
    virtual void u194();
    virtual void u195();
    virtual void u196();
    virtual void u197();
    virtual void u198();
    virtual void u199();
    virtual void u200();
    virtual void u201();
    virtual void u202();
    virtual void u203();
    virtual void u204();
    virtual void u205();
    virtual void u206();
    virtual void u207();
    virtual void u208();
    virtual void u209();
    virtual Def *def();
    virtual void u211();
    virtual void u212();
    virtual void u213();
    virtual void u214();
    virtual void u215();
    virtual void u216();
    virtual void u217();
    virtual void u218();
    virtual bool accept(s32, Def *);
};

class Tbl {
public:
    virtual void t0();
    virtual void t1();
    virtual void t2();
    virtual void t3();
    virtual void t4();
    virtual void t5();
    virtual void t6();
    virtual void t7();
    virtual void t8();
    virtual void t9();
    virtual void t10();
    virtual void t11();
    virtual void t12();
    virtual void t13();
    virtual void t14();
    virtual void t15();
    virtual void t16();
    virtual void t17();
    virtual void t18();
    virtual void t19();
    virtual void t20();
    virtual void t21();
    virtual void t22();
    virtual void t23();
    virtual void t24();
    virtual void t25();
    virtual Def *get(s16);
};

struct TblHolder {
    u8 pad0[0xC];
    Tbl *mC;
};

struct Mgr {
    u8 pad0[0x14];
    s32 m14;
};

struct Slot {
    s16 id;
    s8 ch;
    u8 pad3;
};

struct Self {
    u8 pad0[0xC];
    TblHolder *mC;
    Mgr *m10;
    Slot m14[16];
};

extern "C" {
Unit *PoolGetUsedElem_36acb0(Mgr *, s32);
Unit *ObjAllocByKind_3bb980(Self *, s32);
}

extern "C" Unit *ObjSpawnFromDef_3bb5e0(Self *self, s32 idx, s32 key) {
    Def *d;
    Unit *obj;
    bool found;
    s32 grp;
    s32 n;
    Unit *o;
    Def *dd;
    Slot *slot;
    Slot *fr;
    s32 j;
    s32 q;
    Unit *ob;
    TblHolder *th;
    Slot *e;
    s32 k;
    bool used;
    s32 m;
    Unit *o2;
    s32 i;



    if (idx < 0 || key < 0) {
        return 0;
    }
    th = self->mC;
    if (th == 0 || self->m10 == 0) {
        return 0;
    }
    d = th->mC->get(key);
    if (d == 0) {
        return 0;
    }
    obj = ObjAllocByKind_3bb980(self, d->m2);
    if (obj == 0) {
        return 0;
    }
    if (obj->accept(idx, d) == 0) {
        return 0;
    }
    found = false;
    grp = d->m8;
    n = self->m10->m14;
    for (i = 0; i < n; i++) {
        o = PoolGetUsedElem_36acb0(self->m10, i);
        if (o == 0) {
            continue;
        }
        if (o == obj) {
            continue;
        }
        dd = o->def();
        if (dd == 0) {
            continue;
        }
        if (dd->m8 != grp) {
            continue;
        }
        found = true;
        break;
    }
    if (found) {
        slot = 0;
        fr = 0;
        for (j = 0; j < 16; j++) {
            e = &self->m14[j];
            if (e->id == grp) {
                slot = e;
                break;
            }
            if (fr == 0 && e->id < 0) {
                fr = e;
            }
        }
        if (slot == 0 && fr != 0) {
            fr->id = grp;
            slot = fr;
            fr->ch = 0x40;
        }
        if (slot != 0) {
            for (q = 0; q < n; q++) {
                ob = PoolGetUsedElem_36acb0(self->m10, q);
                if (ob == 0) {
                    continue;
                }
                dd = ob->def();
                if (dd == 0) {
                    continue;
                }
                if (dd->m8 != grp) {
                    continue;
                }
                if (ob->letter() != 0) {
                    continue;
                }
                for (k = 0; k < 26; k++) {
                    slot->ch++;
                    if (slot->ch > 0x5A) {
                        slot->ch = 0x41;
                    }
                    used = false;
                    for (m = 0; m < n; m++) {
                        o2 = PoolGetUsedElem_36acb0(self->m10, m);
                        if (o2 == 0) {
                            continue;
                        }
                        dd = o2->def();
                        if (dd == 0) {
                            continue;
                        }
                        if (dd->m8 != grp) {
                            continue;
                        }
                        if (o2->isActive() == 0) {
                            continue;
                        }
                        if (slot->ch != o2->letter()) {
                            continue;
                        }
                        used = true;
                        break;
                    }
                    if (!used) {
                        ob->setLetter(slot->ch);
                        break;
                    }
                }
            }
        }
    }
    return obj;
}
