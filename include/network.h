#ifdef __cplusplus
extern "C" {
#endif

typedef void (*rxtx_fn_t)(int clientfd, void *future);

void create_server(const char* PORT, rxtx_fn_t fun_ptr, void *future);
void create_client(const char* hostname, const char* CLIENTPORT, rxtx_fn_t fun_ptr, void *future);
void tx(int fd, const char* msg);
int rx(int fd, char *buf, int length);

#ifdef __cplusplus
}
#endif
