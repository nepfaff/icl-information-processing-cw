#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in laddr = {AF_INET, htons(4000), {INADDR_ANY}};
    bind(s, (const sockaddr*)&laddr, sizeof(laddr));

    uint32_t accumulator = 0;
    while(true) {
        sockaddr_in raddr;
        socklen_t raddr_len = sizeof(raddr);

        uint32_t payload;
        recvfrom(s, &payload, sizeof(payload), 0, (sockaddr*)&raddr, &raddr_len);

        accumulator += payload;

        cout << "Updated accumulator value = " << accumulator << endl;

        sendto(s, &accumulator, sizeof(accumulator), 0, (const sockaddr*)&raddr, raddr_len);
    }
}
