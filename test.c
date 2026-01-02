#include <stdio.h>
#include <unistd.h>

int main() {
    // Write C code here
    execve("/usr/bin/python3", (char *[]){"python3","-c", "import subprocess;", "subprocess.run([\"ls\"], capture_output=True)",NULL}, NULL);

    return 0;
}
