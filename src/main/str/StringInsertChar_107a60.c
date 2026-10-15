#pragma optimization_level 3
#pragma cplusplus on
typedef unsigned int U;
struct S { U flags,size;char *data; };
struct I { char *p; I(char *q):p(q){} };
extern "C" void StringReplace_106f90(S *, U, U, const char *, const char *, char);
/* The iterator arrives in one EE GPR; only its low 32 pointer bits are used. */
extern "C" I StringInsertChar_107a60(S *s,unsigned long long where,char c) {

 /* Preserve the runtime wrapper scratch frame and unused sixth argument. */
 struct C { char c; char end[3]; C(){} }; struct F { char pre[19];char c; char gap[8]; C dummy; } frame; frame.c=c;
 char *base;
 if(s->flags&1)base=s->data;else base=(char*)s+1;
 U pos=(char *)(int)where-base;
 C *dp=&frame.dummy;if(dp)dp=dp;
 StringReplace_106f90(s,pos,0,&frame.c,&frame.c+1,dp->c);
 if(s->flags&1)base=s->data;else base=(char*)s+1;
 return I(base+pos);
}
