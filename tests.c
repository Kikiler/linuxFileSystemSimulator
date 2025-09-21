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
    assert(!mkdir("/lol/omegatroll/"));
    assert(!mkdir("/lol/omegatroll/lolol/"));
    assert(!mkdir("/ggmec/"));
    assert(!mkdir("/ggmec/lol/"));

    // unknown directory detection
    assert(0 != mkdir("/false/trolleur/"));
    assert(0 != mkdir("/ggmec/trolleur/lol/"));
    assert(0 != mkdir("/lol/omegatroll/lolol/pasbon/inbon/"));
    puts("Test mkdir done");

    //TO DO : tests for the case where one of the directory has the name as the last one and when all the directories have the same names
}

int main(void) {
test_mkdir();
}