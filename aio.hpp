/* All stdlib */
#include <bits/stdc++.h>

/* Types */
using u8  = uint8_t;    // 2^8 - 1
using u16 = uint16_t;   // 2^16 - 1
using u32 = uint32_t;   // 2^32 - 1
using u64 = uint64_t;   // 2^64 - 1
using i8  = int8_t;     // 2^7 - 1
using i16 = int16_t;    // 2^15 - 1
using i32 = int32_t;    // 2^31 - 1
using i64 = int64_t;    // 2^63 - 1

/* STRING MACRO HELPER */
#define MAKE_STR(s) #s
#define TKN_JOIN(t1, t2) t1 ## t2
#define STR_JOIN(s1, s2) MAKE_STR(TKN_JOIN(s1,s2))
#define STR(s) MAKE_STR(s)

/* LOGGER */
template<typename ... Args> auto log(Args&& ... args)->void{(std::cout<<...<<std::forward<Args>(args));} 

/* Type reflection */
// thanks to this amazing thread: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

/* VARIABLE DEBUGGER */
#define DEBUG(variable) log("[Line: ",__LINE__,"] ",MAKE_STR(variable),": ",type_name<decltype(variable)>()," = ",variable,'\n')

/* Reflective Struct */
#define FIELD(typename, fieldname) typename fieldname;
#define PARAMS(typename, fieldname) typename fieldname,
#define INIT_FIELD(typename, fieldname) fieldname(fieldname),
#define STRINGIFY_FIELD(typename, fieldname) ss << STR(fieldname) << ": " << STR(typename) << " = " << this->fieldname << ", ";
#define STRUCT(struct_name, ...) \
struct struct_name { \
  FIELDS(FIELD) \
  std::nullptr_t _ = nullptr; \
  struct_name(FIELDS(PARAMS)std::nullptr_t _=nullptr):FIELDS(INIT_FIELD)_(nullptr){}\
  struct_name() = default; \
  std::string stringify()const{std::stringstream ss;ss<<"struct "<< STR(struct_name)<<"{ ";FIELDS(STRINGIFY_FIELD);ss<<"}";return ss.str();} \
  friend std::ostream& operator<<(std::ostream& os, const struct_name& obj){os<<obj.stringify();return os;} \
  __VA_ARGS__ \
} 

/* FOR EACH LOOP */
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

/* Enum (Without needing to use xmacro, but it's not enum class) */
// src: https://www.scs.stanford.edu/~dm/blog/va-opt.html
#define STRINGIFY(x) case x: return #x;
#define MAKE_ENUM(type, ...) \
enum type { \
__VA_ARGS__ \
}; \
constexpr const char* stringify(type t) { \
  switch(t) { \
    FOR_EACH(STRINGIFY, __VA_ARGS__) \
    default: throw("Unreachable"); \
  } \
} \
std::ostream& operator<<(std::ostream& os, type t) { \
  os << stringify(t); \
  return os; \
}

/* Vector printer */ 
template<typename T> std::ostream & operator<<(std::ostream& os, std::vector<T> vec) { os<<"[ "; std::for_each(vec.begin(), vec.end(), [&os](auto& elem){os<<elem<<", ";}); os<<"] "; return os; }

/* Defer */
template<typename F> struct _Defer { F action; _Defer(F _action) : action(_action) {}  ~_Defer() { this->action(); } };
template<typename F> _Defer<F> make_defer(F&& action) { return _Defer<F>(std::forward<F>(action)); }
enum class DeferGuard {};
template<typename F> _Defer<F> operator+(DeferGuard, F&& action) { return make_defer(std::forward<F>(action)); }
#define DEFER_VAR(counter) TKN_JOIN(_defer, counter)
#define defer auto DEFER_VAR(__COUNTER__) = DeferGuard() + [&]()


/* Pattern matching if */
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define IIF(c) PRIMITIVE_CAT(IFF_, c)
#define IFF_0(t, ...) __VA_ARGS__
#define IFF_1(t, ...) t

/* Complement */
#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

// NOTE: If CHECK is only passed in one arg, 0 will be returned
#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

/* Parenthesis Detection Macro */
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

/* NOT operation */
// NOTE: Only one arg is passed in if invalid macro call (NOT_1), yielding 0
//       else we probe and returns 1
#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define EAT(...)
#define EXPAND_ARGS(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND_ARGS, EAT)


