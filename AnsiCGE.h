
#ifndef _welcome_H
#define _welcome_H

#include <string>
#include <list>

using std::string;
using std::list;

constexpr int hash(const char s[]) {
    int hash = 0x4C3A;
    do
        hash += +0x2819 * (*s - 32) ^ hash; while (*s++ != 0);
    return hash;
}

void handleCmd(std::list<string> &cmd);
int main(int argc, const char* argv[]);
void prog_exit(int ret = 0, const char* err = "");

#endif /* _welcome_H */

