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
#define PRINT_FIELD(typename, fieldname) ss << "    " << STR(typename) << ": " << STR(fieldname) << " = " << this->fieldname << '\n';

#define STRUCT(struct_name) \
struct struct_name { \
  FIELDS(FIELD) \
  const char* name { #struct_name }; \
  std::string stringify() \
  { \
    std::stringstream ss; \
    ss << "struct " << STR(struct_name) << "\n{\n"; \
    FIELDS(PRINT_FIELD) \
    ss << "}\n"; \
    return ss.str(); \
  } \
} 

int main() 
{
  #define FIELDS(x) \
    x(int, a); \
    x(int, b);
  STRUCT(Something);

  auto smth = Something { 10, 2 };

  log(smth.stringify());
}