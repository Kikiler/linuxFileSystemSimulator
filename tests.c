//
// Created by Killian Evouna on 21/09/2025.
//
#include "commands.h"
#include <assert.h>

void test_mkdir(void) {
    puts("Test mkdir started");
    ROOT = malloc(sizeof(node));
    ROOT->child = NULL;
    ROOT->sibling = NULL;
    ROOT->fileType = 'D';
    ROOT->name = "/";
    ROOT->parent = NULL;
    CWD = ROOT;
    assert(!mkdir("/lol/"));

    // siblings working correctly
    assert(!mkdir("/lol/lolol/"));
    assert(1 == mkdir("/lol/omegatroll/"));
    assert(!mkdir("/lol/omegatroll/lolol/"));
    assert(1 == mkdir("/ggmec/"));
    assert(!mkdir("/ggmec/lol/"));

    // unknown directory detection
    puts("unknown directory test");
    assert(-1 == mkdir("/false/trolleur/"));
    assert(-1 == mkdir("/ggmec/trolleur/lol/"));
    assert(-1== mkdir("/lol/omegatroll/lolol/pasbon/inbon/"));

    puts("directories with same names");
    //tests for the case where one of the directory has the name as the last one and when all the directories have the same names
    assert(1 == mkdir("/false/"));
    assert(!mkdir("/false/false/"));
    assert(!mkdir("/false/false/false/"));

    puts("duplicate directory tests");
    //duplicate directories
    assert(2==mkdir("/false/"));
    assert(2==mkdir("/false/false/"));
    assert(2==mkdir("/false/false/false/"));


    puts("Test mkdir done");
}

int main(void) {
test_mkdir();
}