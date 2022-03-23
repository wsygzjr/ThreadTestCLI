#include "ThreadTestCli.h"
using namespace std;
#pragma   comment(lib, "Ws2_32.lib")

bool init_Socket()
{
    //socket版本，传出参数
    WSADATA wsadata;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
    {
        cout << "WSAStartup failed" << endl;
        return false;
    }
    return true;
}


bool close_Socket()
{
    if (0 != WSACleanup())
    {
        cout << "WSACleanup" << endl;
        return false;
    }
    return true;
}

SOCKET CreateClientSocket()
{
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(8008);
    //cliaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &cliaddr.sin_addr.S_un.S_addr);

    bind(client, (sockaddr*)&client, sizeof(client));
    connect(client, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    return client;
}


void rec(SOCKET con)
{
    char buf[1024] = { '1','2','3','4','5','6','7','8','9','0','\0' };
    while (true)
    {
        memset(buf, 0, 1024);
        // if(0 < recv(con, buf, 0, 0))
        recv(con, buf, 1024, 0);
        cout << buf << endl;
    }
}

void sen(SOCKET con)
{
    char buf[1024] = { '1','2','3','4','5','6','7','8','9','0','\0' };
    while (true)
    {
        memset(buf, 0, 1024);
        // if(0 < recv(con, buf, 0, 0))
        cin >> buf;
        send(con, buf, 1024, 0);
        //cout << buf << endl;
    }
}

int main()
{
    init_Socket();

    SOCKET client = CreateClientSocket();
    SOCKET con;


    //listen(client, 5);

    char buf[1024] = "hello world";
    send(client, buf, strlen(buf), 0);
    memset(buf, 0, 1024);

    thread th1(rec, client);
    //thread th2(sen, client);
    th1.detach();
    //th2.join();
    sen(client);

    closesocket(client);

    close_Socket();
    
}