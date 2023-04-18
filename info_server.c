#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

int main() 
{
    // Tao socket
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener != -1)
        printf("Socket created: %d\n", listener);
    else
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    // Khai bao cau truc dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    // Gan dia chi voi socket
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr))) 
    {
        printf("bind() failed.\n");
        exit(1);
    }

    if (listen(listener, 5)) 
    {
        printf("listen() failed.\n");
        exit(1);
    }

    printf("Waiting for a new client ...\n");

    // Chap nhan ket noi
    int client = accept(listener, NULL, NULL);
    if (client == -1)
    {
        printf("accept() failed.\n");
        exit(1);
    }
    printf("New client connected: %d\n", client);
    char ten_may_tinh[50];
    int so_luong_o_dia;
    char o_dia[10][50];
    int kich_thuoc_o_dia[10];

    // Nhận dữ liệu từ info_client
    recv(client, ten_may_tinh, sizeof(ten_may_tinh), 0);
    recv(client, &so_luong_o_dia, sizeof(so_luong_o_dia), 0);
    for (int i = 0; i < so_luong_o_dia; i++) {
        recv(client, o_dia[i], sizeof(o_dia[i]), 0);
        recv(client, &kich_thuoc_o_dia[i], sizeof(kich_thuoc_o_dia[i]), 0);
    }

    printf("Thông tin nhận được từ info_client:\n");
    printf("+ Tên máy tính: %s\n", ten_may_tinh);
    printf("+ Số lượng ổ đĩa: %d\n", so_luong_o_dia);
    for (int i = 0; i < so_luong_o_dia; i++) {
        printf("%c - %dGB\n", o_dia[i][0], kich_thuoc_o_dia[i]);
    }
    
    // Dong ket noi
    close(client);
    close(listener);    

    return 0;
}