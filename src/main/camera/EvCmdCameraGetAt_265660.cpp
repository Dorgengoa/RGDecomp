#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

class Base {
public:
    u8 pad000[0xC0];
};

class C : public Base {
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
    virtual void v40(f32 *out);
};

extern "C" C *EventSceneGetCamera_265980(void);
extern "C" void ScriptSetRefFloat_26a1c0(E8 *q, f32 v);

extern "C" s32 EvCmdCameraGetAt_265660(E8 *q, s32 n)
{
    f32 v[4];
    C  *o;

    if (n < 3) {
        return 0;
    }
    o = EventSceneGetCamera_265980();
    if (o == 0) {
        return 0;
    }
    o->v40(v);
    ScriptSetRefFloat_26a1c0(q++, v[0]);
    ScriptSetRefFloat_26a1c0(q++, v[1]);
    ScriptSetRefFloat_26a1c0(q, v[2]);
    return 1;
}
