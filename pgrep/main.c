#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include "zlib/include/z_error.h"
#include "zlib/include/z_file.h"
#include "zlib/include/z_heap.h"
#include "zlib/include/z_string.h"

bool parse_pid(const char *s, int *pid)
{
    if (*s == '\0') {
        return false;
    }

    *pid = 0;

    for (const char *curr = s; *curr; curr++) {
        if (!isdigit(*curr)) {
            return false;
        }

        *pid *= 10;
        *pid += *curr - '0';
    }

    return true;
}

void print_usage()
{
    printf("pgrep [name]\n");
}

bool get_proccess_name(int pid, Z_String *name)
{
    Z_Heap_Auto heap = {0};
    Z_String path = z_str_new(&heap, "/proc/%d/comm", pid);
    Z_File_Auto *fp = fopen(path.ptr, "r");

    if (!fp) {
        return false;
    }

    return z_file_read_line(fp, name) > 0;
}

bool is_proccess_match(int pid, const char *pattern)
{
    Z_Heap_Auto heap = {0};
    Z_String process_name = z_str_new(&heap, "");

    if (!get_proccess_name(pid, &process_name)) {
        return false;
    }

    return z_sv_contains(z_sv(process_name), z_sv(pattern));
}

void handle_proc_entry(const char *entry, const char *pattern)
{
    int pid;

    if (!parse_pid(entry, &pid)) {
        return;
    }

    if (!is_proccess_match(pid, pattern)) {
        return;
    }

    printf("%d\n", pid);
}

int pgrep(const char *pattern)
{
    Z_Dir_Auto *dir = opendir("/proc");

    if (!dir) {
        z_perror_format("/proc");
        return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir))) {
        handle_proc_entry(entry->d_name, pattern);
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        print_usage();
        return 1;
    }

    return pgrep(argv[1]);
}
