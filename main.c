#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int client_fd; //文件描述符
    struct sockaddr_in client_addr,server_addr;// ip port 文件
//    const char* server="120.26.192.16";
    const char* server="127.0.0.1";
    int res_connect=-1,len_data,portt=9003;

    client_fd= socket(AF_INET,SOCK_STREAM,0);
    if (client_fd < 0) {
        perror("socket");
        return 0;
    }
    bzero(&client_addr,sizeof (client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(0);
    if( bind(client_fd,(struct sockaddr *)&client_addr,sizeof (client_addr)) <0 ){
        perror("bind");
        return 0;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;//IVP4
    inet_aton(server,&server_addr.sin_addr);
    server_addr.sin_port = htons(portt);//服务器端口

    res_connect= connect(client_fd,(struct sockaddr*)& server_addr,sizeof (server_addr));
    if(res_connect<0){
        perror("connect");
        return 0;
    }
    int nbytes;
    char buffer[101]="test";
    char res[101];
//    printf("%s\n",buffer);
//    printf("%d\n", strlen(buffer));
    nbytes = write(client_fd, buffer, strlen(buffer));
    printf("nbytes: %d\n",nbytes);
    read(client_fd,res,sizeof (res));
    printf("res: %s\n",res);
    close(client_fd);

    return 0;
}



