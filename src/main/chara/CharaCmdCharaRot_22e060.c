#include "types.h"

extern void *GetCurrentScene_1f5be0(void);
extern void *ObjRecGetLiveObject_1c4a90(void *w, s32 id);
extern s32   ScriptArgGetInt_302d70(char *s);
extern void *GetLiveObjById_1ce420(s32 id, s32 v);
extern f32   ScriptArgGetFloat_302cf0(char *s);
extern void  ModelSetRot_151080(void *obj, f32 *v);

s32 CharaCmdCharaRot_22e060(s32 *self, char *s, s32 argc)
{
    void *w;
    void *t;
    void *obj;
    f32 b;
    f32 a;
    f32 c;

    if (argc != 4) {
        return 0;
    }
    w = GetCurrentScene_1f5be0();
    if (w == NULL) {
        return 1;
    }
    t = ObjRecGetLiveObject_1c4a90(w, *self);
    if (t == NULL) {
        return 1;
    }
    obj = GetLiveObjById_1ce420(*self, ScriptArgGetInt_302d70(s));
    if (obj == NULL) {
        return 1;
    }
    a = ScriptArgGetFloat_302cf0(s + 0xF);
    b = ScriptArgGetFloat_302cf0(s + 0xA);
    c = ScriptArgGetFloat_302cf0(s + 0x5);
    {
        f32 v[4] = {0};

        v[0] = c;
        v[1] = b;
        v[2] = a;
        ModelSetRot_151080(obj, v);
    }
    return 1;
}
