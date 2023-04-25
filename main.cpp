/* All stdlib */
#include <bits/stdc++.h>

/* Types */
using u8 = uint8_t;

/* STRING MACRO HELPER */
#define MAKE_STR(s) #s

/* LOGGER */
template<typename ... Args> auto log(Args&& ... args)->void{(std::cout<<...<<std::forward<Args>(args));} 

/* VARIABLE DEBUGGER */
#define DEBUG(variable) log("[Line: ",__LINE__,"] ",MAKE_STR(variable)," = ",variable,'\n'); 

int main() {}