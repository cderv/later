#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#include <stdint.h> // for uint64_t

/* FIXME:
Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _later_ensureInitialized();
extern SEXP _later_execCallbacks(SEXP, SEXP, SEXP);
extern SEXP _later_idle(SEXP);
extern SEXP _later_execLater(SEXP, SEXP, SEXP);
extern SEXP _later_cancel(SEXP, SEXP);
extern SEXP _later_nextOpSecs(SEXP);
extern SEXP _later_testCallbackOrdering();
extern SEXP _later_createCallbackRegistry(SEXP);
extern SEXP _later_deleteCallbackRegistry(SEXP);
extern SEXP _later_existsCallbackRegistry(SEXP);
extern SEXP _later_list_queue_(SEXP);
extern SEXP _later_log_level(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"_later_ensureInitialized",   (DL_FUNC) &_later_ensureInitialized,   0},
  {"_later_execCallbacks",       (DL_FUNC) &_later_execCallbacks,       3},
  {"_later_idle",                (DL_FUNC) &_later_idle,                1},
  {"_later_execLater",           (DL_FUNC) &_later_execLater,           3},
  {"_later_cancel",              (DL_FUNC) &_later_cancel,              2},
  {"_later_nextOpSecs",          (DL_FUNC) &_later_nextOpSecs,          1},
  {"_later_testCallbackOrdering", (DL_FUNC) &_later_testCallbackOrdering, 0},
  {"_later_createCallbackRegistry", (DL_FUNC) &_later_createCallbackRegistry, 1},
  {"_later_deleteCallbackRegistry", (DL_FUNC) &_later_deleteCallbackRegistry, 1},
  {"_later_existsCallbackRegistry", (DL_FUNC) &_later_existsCallbackRegistry, 1},
  {"_later_list_queue_",         (DL_FUNC) &_later_list_queue_,         1},
  {"_later_log_level",           (DL_FUNC) &_later_log_level,           1},
  {NULL, NULL, 0}
};

uint64_t execLaterNative(void (*func)(void*), void* data, double secs, int loop);

void R_init_later(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_RegisterCCallable("later", "execLaterNative", (DL_FUNC)&execLaterNative);
}
