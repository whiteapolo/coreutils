#include <stdio.h>
#include <unistd.h>
#include <z_string.h>

void print_usage()
{
    printf("tr <target> <replacment>\n");
}

void tr(const char *target, const char *replacment)
{
    char buf[BUFSIZ];
    Z_Heap_Auto heap = {0};

    while (fgets(buf, BUFSIZ, stdin)) {
        Z_String replaced = z_str_new(&heap, "%s", buf);
        z_str_replace(&replaced, z_sv(target), z_sv(replacment));
        z_sv_print(z_sv(replaced));
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        print_usage();
        return 1;
    }

    tr(argv[1], argv[2]);

    return 0;
}
