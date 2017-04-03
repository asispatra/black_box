
void create_server(char* PORT, void (*fun_ptr)(int clientfd));
void create_client(char* hostname, char* CLIENTPORT, void (*fun_ptr)(int clientfd));
void tx(int fd, char* msg);
int rx(int fd, char *buf, int length);
