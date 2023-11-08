#include <common.h>
#include <xcommon.h>
#include <__nsocket.h>

#define _IP              "127.0.0.1" // IP 주소
#define _PORT            "7810" // 포트 번호
#define _COMPORT         "/dev/ttyAMA1" // 시리얼 포트 경로
#define _COMBAUDRATE     "115200" // 통신 속도

#if __NSOCKET__ 

void main(int argc, char** argv)
{
    cnsocket socket;
    memset(&socket, 0, sizeof(cnsocket)); // socket 선언하고 초기화 

    socket.io.argv[0], _IP;
    socket.io.argv[1], _PORT;
    socket.io.argv[2], "TCP";
    socket.io.argv[3], "CLIENT";
    socket.io.argv[4],  "STREAM"; // socket.io.argv에 복사





    // 소켓 열기(성공하면 0 또는 양수 반환)
    int32_t open_result = nsocket_open(&socket);
    if (open_result < 0)
    {
        printf("Failed to open socket. Error code: %d\n", open_result);

    }
    else
    {
        printf("Socket opened successfully!\n");

    }


    // 데이터 입력
    char user_input[256];
    printf("Enter data to send to the server: ");
    fgets(user_input, sizeof(user_input), stdin);
    int data_length = strlen(user_input);

    int32_t write_result = nsocket_write(socket._imtif.h, 0, (int8_t*)user_input, data_length, 0, &socket);



    // 소켓 읽기
    int8_t read_buffer[256];
    int32_t read_result = nsocket_read(socket._imtif.h, 0, read_buffer, sizeof(read_buffer), 0, &socket);

    read_buffer[read_result] = '\0';  // 마지막에 NULL 값 추가 -> 문자열 종료
    printf("Received data from server: %s\n", read_buffer);

    // 소켓 닫기
    nsocket_close(&socket);
}

#endif
