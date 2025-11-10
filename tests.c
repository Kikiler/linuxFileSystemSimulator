//
// Created by Killian Evouna on 21/09/2025.
//
#include "commands.h"
#include <assert.h>

void test_mkdir(void) {
    puts("Test mkdir started");
    initRoot();
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

void test_rmdir(void) {
    puts("Test rmdir started");
    initRoot();

    //create the files
    mkdir("/Eldest00/");
    mkdir("/Brother01/");
    mkdir("/Sister02/");

    mkdir("/Eldest00/Eldest10/");
    mkdir("/Eldest00/Brother11/");
    mkdir("/Eldest00/Sister12/");

    mkdir("/Eldest00/Eldest10/Eldest20/");
    mkdir("/Eldest00/Eldest10/Brother21/");
    mkdir("/Eldest00/Eldest10/Sister22/");

    //non empty directory check
    assert(-1 == rmdir("/Eldest00/"));
    assert(-1 == rmdir("/Eldest00/Eldest10/"));

    //non existent directory
    assert(-1 == rmdir("/Eldest00/Eldest10/Eldest20/lol"));
    assert(-1 == rmdir("/Eldest00/Eldest10/lol/"));

    //suppress all of them
    assert(!rmdir("/Eldest00/Eldest10/Eldest20/"));
    assert(1==rmdir("/Eldest00/Eldest10/Sister22/"));
    assert(!rmdir("/Eldest00/Eldest10/Brother21/"));

    assert(!rmdir("/Eldest00/Eldest10/"));
    assert(!rmdir("/Eldest00/Brother11/"));
    assert(!rmdir("/Eldest00/Sister12/"));

    assert(!rmdir("/Eldest00/"));
    assert(!rmdir("/Brother01/"));
    assert(!rmdir("/Sister02/"));

    //check if every file has been suppressed
    assert(ROOT->child == NULL);

    puts("Test rmdir done");
}

void test_CWD(void) {
    puts("Test CWD started : functions in test -> PWD and CD");
    initRoot();




}

int main(void) {
    test_mkdir();
    test_rmdir();
    puts("All tests passed");
}