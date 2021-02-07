#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    uint32_t addr = 0x0100007f; // 127.0.0.1
    sockaddr_in saddr = {AF_INET, htons(4000), {addr}};

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
