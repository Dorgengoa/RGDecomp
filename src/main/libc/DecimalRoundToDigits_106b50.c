#include "types.h"
#pragma cplusplus on
#pragma inline_depth(8)
struct Iter { char *p; Iter() {} Iter(char *q):p(q) {} };

static inline char &operator*(Iter a) {return *a.p;}
static inline bool operator==(Iter a,char *b) {return a.p==b;}
static inline bool operator<(Iter a,Iter b) {return a.p<b.p;}

struct Str;
extern "C" void StringCopyCtor_107c30(Str *,Str *);
extern "C" void StringDtor_107b00(Str *,int);
struct Str {
 Str(Str *x,int n);
 Str() {u.l.cap=0;u.l.size=0;u.l.data=0;}
 Str(Str &x) {StringCopyCtor_107c30(this,&x);}
 ~Str();
 union {
  struct { u32 cap; u32 size; char *data; } l;
  struct { u8 flag:1; u8 size:7; char buf[11]; } s;
 } u;
 bool small() { return !(u.l.cap & 1); }
 u32 size() { return small() ? u.s.size : u.l.size; }
 char *data() { return small() ? u.s.buf : u.l.data; }
 char *end() { char *p; u32 n; if (!(u.l.cap & 1)) {p=u.s.buf;n=u.s.size;} else {p=u.l.data;n=u.l.size;} return p+n; }
};
struct Decimal { Str sig; s16 exp; s16 cls; };
extern "C" void StringCtorSubstr_107b70(Str *,Str *,u32,u32);
extern "C" u32 StringFindChar_107550(Str *,char,u32);
extern "C" Iter StringInsertChar_107a60(Str *,Iter,char);
extern "C" void StringResize_106e20(Str *,u32,char);
extern "C" void StringCopyCtor_107c30(Str *,Str *);
extern "C" void StringDtor_107b00(Str *,int);
inline Str::Str(Str *x,int n) {StringCtorSubstr_107b70(this,x,0,n);}
// Preserve the retail local string's stack placement; reserved bytes are unused.
struct RoundStorage {
 // Stack-only storage: no allocation is owned by the generated deleting destructor.
 static void operator delete(void *) {}
 char reserved[8];
 Str s;
 RoundStorage(Str *x,int n):s(x,n) {}
};

static inline int compare(Str *s,u32 pos) {
 bool small=!(s->u.l.cap&1);
 u32 n=small?s->u.s.size:s->u.l.size;
 if(pos>=n)return -1;
 char *p=small?s->u.s.buf:s->u.l.data;
 char c=p[pos];
 if(c>5)return 1;
 if(c<5)return -1;
 if (StringFindChar_107550(s,0,pos+1)==(u32)-1) return 0;
 return 1;
}
extern "C" Str DecimalRoundToDigits_106b50(Decimal *d,int count,int *exp) {
 if(count<=0) return Str();
 RoundStorage frame(&d->sig,count);

 *exp=d->exp;
 if((u32)count<d->sig.size()) {
  int cmp=compare(&d->sig,count);
  if(cmp>=0) {
   Iter it(frame.s.end()-1);
   bool up=cmp==1;
   if(cmp==0)up=*it.p%2!=0;
   if(up) {
    for(;;) {

     if(*it<9) {++*it;break;}
     *it=0;
     if(it==frame.s.data()) {
      StringInsertChar_107a60(&frame.s,Iter(frame.s.data()),1);
      StringResize_106e20(&frame.s,frame.s.size()-1,0);
      ++*exp;
      break;
     }
     --it.p;
    }
   }
  }
 }
 Iter end(frame.s.end());
 char *p=frame.s.data();
 Iter it;
 for(;it.p=p,it<end;p=it.p+1)*it+='0';
 return frame.s;
}
