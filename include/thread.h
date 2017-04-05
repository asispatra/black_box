#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*thread_fn_t)(void *dummy);

void create_thread(thread_fn_t fun_ptr, void *future);

#ifdef __cplusplus
}
#endif
