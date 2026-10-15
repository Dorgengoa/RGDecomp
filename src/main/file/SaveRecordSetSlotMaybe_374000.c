#include "types.h"
typedef struct{u8 flag:1;u8 rest:7;s8 a,b,c;}T;extern u8*GetGameData_1fede0(void);extern T*RecordGetStateSaveSlotMaybe_430690(s32);
void SaveRecordSetSlotMaybe_374000(u8*a){T*p=RecordGetStateSaveSlotMaybe_430690(*(s32*)(GetGameData_1fede0()+0x24));if(p){p->flag=0;p->a=*(s16*)(a+0x4EC);p->b=*(s16*)(a+0x4EE);p->c=-1;}}
