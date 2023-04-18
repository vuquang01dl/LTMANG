#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    // Khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi cua server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000); 

    // Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        printf("Khong ket noi duoc den server!");
        return 1;
    }
   char ten_may_tinh[50];
    int so_luong_o_dia;
    char o_dia[10][50];
    int kich_thuoc_o_dia[10];

    // Nhập tên máy tính từ bàn phím
    printf("Nhập tên máy tính: ");
    scanf("%s", ten_may_tinh);

    // Nhập số lượng ổ đĩa từ bàn phím
    printf("Nhập số lượng ổ đĩa: ");
    scanf("%d", &so_luong_o_dia);

    // Nhập thông tin về từng ổ đĩa
    for (int i = 0; i < so_luong_o_dia; i++) {
        printf("Nhập tên ổ đĩa %d: ", i + 1);
        scanf("%s", o_dia[i]);
        printf("Nhập kích thước ổ đĩa %d (GB): ", i + 1);
        scanf("%d", &kich_thuoc_o_dia[i]);
    }


    // Đóng gói và gửi dữ liệu tới info_server
    send(client, ten_may_tinh, sizeof(ten_may_tinh), 0);
    send(client, &so_luong_o_dia, sizeof(so_luong_o_dia), 0);
    for (int i = 0; i < so_luong_o_dia; i++) {
        send(client, o_dia[i], sizeof(o_dia[i]), 0);
        send(client, &kich_thuoc_o_dia[i], sizeof(kich_thuoc_o_dia[i]), 0);
    }
     printf("Đã gửi dữ liệu thành công tới info_server\n");

    // Ket thuc, dong socket
    close(client);

    return 0;
}
