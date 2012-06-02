#include <cstring>
#include <string>
#include <cstdlib>
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS /* empty */
# define END_C_DECLS /* empty */
#endif

BEGIN_C_DECLS
#include <mysql.h>
END_C_DECLS

#include "FFIInterpreter_stub.h"

#ifdef _WIN32
#define EXPORT _declspec(dllexport)
#else
#define EXPORT
#endif

BEGIN_C_DECLS
EXPORT my_bool hs_eval_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
EXPORT void hs_eval_deinit(UDF_INIT* initid);
EXPORT char* hs_eval(UDF_INIT* initid, UDF_ARGS* args, char* result,
                     unsigned long* length, char* is_null, char* error);
EXPORT void __stginit_FFIInterpreter(void);
END_C_DECLS

namespace {
static void init(void) __attribute__((constructor));
static void init(void)
{
    static char *argv[] = { (char*)"hs_eval.so", NULL }, **argv_ = argv;
    static int argc = 1;
    hs_init(&argc, &argv_);
    hs_add_root(__stginit_FFIInterpreter);
}

static void exit(void) __attribute__((destructor));
static void exit(void)
{
    hs_exit();
}

} // anonymous namespace

EXPORT
my_bool
hs_eval_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
    return 0;
}

EXPORT
void
hs_eval_deinit(UDF_INIT* initid)
{}

EXPORT
char*
hs_eval(UDF_INIT* initid, UDF_ARGS* args, char* result,
        unsigned long* length, char* is_null, char* error)
{
    if (0 == args->lengths[0])
    {
        *is_null = 1;
        return NULL;
    }
    std::string ans((const char*)eval(args->args[0]));
    *length = ans.size();
    char* p = (char*)std::malloc(ans.size()+1);
    std::strcpy(p, ans.c_str());
    return p;
}
