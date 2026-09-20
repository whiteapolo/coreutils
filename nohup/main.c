#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void print_usage()
{
    printf("nohup [command] [arguments+]\n");
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        print_usage();
        return 1;
    }

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;

    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        return 1;
    }

    execvp(argv[1], argv + 1);

    return 0;
}
