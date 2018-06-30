//https://segmentfault.com/a/1190000009172560
// 在c语言中这个必须写成inline static int eif
inline int eif(){
    static int n=0;
    return ++n;
}
static inline  int iif(){
    static int n=0;
    return ++n;
}
static int nif() {
    static int n=0;
    return ++n;
}
int eig();
int iig();
int nig();