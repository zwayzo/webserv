#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <cstdio>  // Include this for perr


void handleCtrlZ(int signum) {
    std::cout << "Ctrl+Z signal received (SIGTSTP)." << std::endl;
    // Handle Ctrl+Z as needed
}

int main() {
    // Set up the signal handler for Ctrl+Z
    signal(SIGTSTP, handleCtrlZ);

    // Set stdin to non-blocking mode
    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);

    fd_set read_fds;

    for (;;) {
        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);  // File descriptor 0 is stdin

        int result = select(1, &read_fds, NULL, NULL, NULL);

        if (result == -1) {
            perror("select");
            break;
        } else if (result > 0) {
            if (FD_ISSET(0, &read_fds)) {
                char buffer[256];
                ssize_t bytesRead = read(0, buffer, sizeof(buffer) - 1);
                if (bytesRead == -1) {
                    if (errno != EAGAIN) {
                        perror("read");
                        break;
                    }
                } else if (bytesRead == 0) {
                    std::cout << "EOF received. Exiting." << std::endl;
                    break;
                } else {
                    buffer[bytesRead] = '\0';
                    std::cout << "Read from stdin: " << buffer << std::endl;
                }
            }
        }
    }

    return 0;
}
