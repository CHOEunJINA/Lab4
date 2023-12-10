#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define MYPORT 3490
#define BACKLOG 10
#define MAXBUF 100

int main()
{
    int ssock, csock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    char buf[MAXBUF];
    int sin_size;

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(MYPORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ssock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(ssock, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    while (1)
    {
        sin_size = sizeof(struct sockaddr_in);
        if ((csock = accept(ssock, (struct sockaddr *)&clnt_addr, &sin_size)) == -1)
        {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s\n", inet_ntoa(clnt_addr.sin_addr));

        while (1)
        {
            memset(buf, 0, MAXBUF);

            // 클라이언트로부터 데이터 받기
            if (recv(csock, buf, MAXBUF - 1, 0) <= 0)
            {
                perror("recv");
                break;
            }

            // 받은 데이터 출력
            printf("Received: %s\n", buf);

            // 클라이언트에게 데이터 전송
            if (send(csock, buf, strlen(buf), 0) == -1)
            {
                perror("send");
                break;
            }
        }

        // 클라이언트와의 연결 종료
        close(csock);
    }

    // 소켓 닫기
    close(ssock);

    return 0;
}

