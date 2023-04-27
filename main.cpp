/* All stdlib */
#include <bits/stdc++.h>

/* Types */
using u8 = uint8_t;

/* STRING MACRO HELPER */
#define MAKE_STR(s) #s
#define STR(s) MAKE_STR(s)

/* LOGGER */
template<typename ... Args> auto log(Args&& ... args)->void{(std::cout<<...<<std::forward<Args>(args));} 

/* VARIABLE DEBUGGER */
#define DEBUG(variable) log("[Line: ",__LINE__,"] ",MAKE_STR(variable)," = ",variable,'\n'); 

#define FIELD(typename, fieldname) typename fieldname;
#define PRINT_FIELD(typename, fieldname) ss << STR(fieldname) << ": " << STR(typename) << " = " << this->fieldname << ", ";

#define STRUCT(struct_name) \
struct struct_name { \
  FIELDS(FIELD) \
  const char* name { #struct_name }; \
  std::string stringify() const { std::stringstream ss; ss << "struct " << STR(struct_name) << "{ "; FIELDS(PRINT_FIELD); ss << "}"; return ss.str(); } \
  friend std::ostream& operator<<(std::ostream& os, const struct_name & obj) { os << obj.stringify(); return os; } \
} 

// src: https://www.scs.stanford.edu/~dm/blog/va-opt.html#the-for_each-macro
#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define FIELDS(x) \
  x(int, a); \
  x(int, b);
STRUCT(Something);
#undef FIELDS

#define FIELDS(x) \
  x(int, a); \
  x(Something, smth); 
STRUCT(SomethingElse);
#undef FIELDS


int main() 
{
  auto smth = SomethingElse { 10, Something { 1, 2 } };
  DEBUG(smth);
  smth.a = 22;
  DEBUG(smth);
}
