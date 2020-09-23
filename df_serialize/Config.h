// All STL usage is through these defined types.
// You can use different types with the same interfaces used if you'd like to avoid STL.

#define DFS_LOG(...) printf(__VA_ARGS__);

#ifndef TDYNAMICARRAY
#define TDYNAMICARRAY std::vector
#endif

#ifndef TSTATICARRAY
#define TSTATICARRAY std::array
#endif

#ifndef TSTRING
#define TSTRING std::string
#endif