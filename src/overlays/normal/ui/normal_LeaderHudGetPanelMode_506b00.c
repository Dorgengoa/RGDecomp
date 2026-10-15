#include "types.h"
typedef struct Obj { u8 pad00[0x72]; s8 f72; } Obj;
extern s8 normal_LeaderHudGetPanelMode_506b00(Obj *p);
s8 normal_LeaderHudGetPanelMode_506b00(Obj *p) { return p->f72; }
