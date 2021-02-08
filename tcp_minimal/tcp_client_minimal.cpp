#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[]) {
    sockaddr_in saddr = {AF_INET, htons(4000)}; //htons takes 16bit argument, htonl 32bit

    // set default address
    inet_pton(AF_INET, "127.0.0.1", &(saddr.sin_addr));

    // received address as argument
    if (argc > 1) {
        inet_pton(AF_INET, argv[1], &(saddr.sin_addr));
    }

    char addrStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(saddr.sin_addr), addrStr, INET_ADDRSTRLEN);
    cout << "Connecting to IPv4 address " << addrStr << endl;
    cout << argv[0] << endl;

    while(true) {
        int s = socket(AF_INET, SOCK_STREAM, 0);

        connect(s, (sockaddr*)&saddr, sizeof(saddr));

        uint32_t value = 1;
        send(s, &value, 4, 0);

        uint32_t payload;
        recv(s, &payload, 4, 0);

        cout << "State=" << payload <<endl;

        close(s);
    }
}
