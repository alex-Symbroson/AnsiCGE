/*
 *  @author alex-Symbroson
 */

#include "AnsiCGE.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


FILE* fifo = NULL;
int fifod = 0;

void handleCmd(std::list<string> &cmd) {
    const string name = cmd.front();

    switch (hash(name.c_str())) {
        case hash("exit"): prog_exit(0, "exited.");
            break;
        case hash("greet"): printf("Hello!\n");
            break;
        default: fprintf(stderr, "unknown command '%s'\n", name.c_str());
    }
}

int main(int argc, const char* argv[]) {
    if (signal(SIGINT, [](int sig) {
            prog_exit(SIGINT, "program interrupted");
        }) == SIG_ERR) prog_exit(1, "couldnt set signal handler");
    if (signal(SIGTERM, [](int sig) {
            prog_exit(SIGTERM, "program terminated");
        }) == SIG_ERR) prog_exit(1, "couldnt set signal handler");
    if (signal(SIGTSTP, [](int sig) {
            prog_exit(SIGSTOP, "program kb stopped");
        }) == SIG_ERR) prog_exit(1, "couldnt set signal handler");
    if (signal(SIGQUIT, [](int sig) {
            prog_exit(SIGQUIT, "program exited");
        }) == SIG_ERR) fprintf(stderr, "couldnt set signal handler");
    if (signal(SIGALRM, [](int sig) {
            printf("alarm received\n");
        }) == SIG_ERR) prog_exit(1, "couldnt set signal handler");


    fifo = fopen("pid", "w");
    if (!fifo) prog_exit(1, "couldn't open file for writing");
    fprintf(fifo, "%i", getpid());
    fclose(fifo);

    const char* name = "cmd"; // fifo name
    mkfifo(name, 0666); // create fifo
    fifo = fopen(name, "r"); // open fifo for reading
    fifod = open(name, O_WRONLY); // keep fifo in write mode to prevent EOF
    if (!fifo) prog_exit(1, "couldn't open fifo for reading");

    string word;
    std::list<string> cmd;
    char c;
    int cmdEnd = 0;

    do {
        c = getc(fifo);
        switch (c) {
            case '\0': break;
            
            case '\f': // parameter separator
            case ' ': cmd.push_back(word);
                word.clear();
                break;
                
            case '\n': // command separator
                cmd.push_back(word);
                word.clear();
                handleCmd(cmd);
                cmd.clear();
                break;
                
            default: word += c;
        }
    } while (c != EOF);

    prog_exit(0, "ended.");
}

/**
 * Close files and exit program
 */
void prog_exit(int ret, const char* err) {
    if(fifo) fclose(fifo);
    if(fifod) close(fifod);
    if (*err) fprintf(stderr, "%s\n", err);
    exit(ret);
}