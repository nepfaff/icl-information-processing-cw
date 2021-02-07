#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    uint32_t addr = 0x0100007f; // 127.0.0.1
    sockaddr_in saddr = {AF_INET, htons(4000), {addr}};

    while(true) {
        uint32_t value = 1;
        sendto(s, &value, sizeof(value), 0, (sockaddr*)&saddr, sizeof(saddr));

        uint32_t state;
        recvfrom(s, &state, sizeof(state), 0, nullptr, nullptr);

        cout << "State=" << state <<endl;
    }
}
