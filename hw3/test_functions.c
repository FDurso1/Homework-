#include <assert.h>
#include <stdio.h>

#include "functions.h"

#define TEST_RESTRICTION_1 10
#define TEST_RESTRICTION_2 2
#define TEST_RESTRICTION_3 5
#define TEST_RESTRICTION_4 30

#define MAX_WORD_NUM 1024

void test_read_files() {
  FILE* fptr = fopen("test_file_1.txt", "w");
  fprintf(fptr, "5\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa");
  fclose(fptr);
}

void test_match_regex() {
    assert(match("abc", "abc", TEST_RESTRICTION_1) == 1);
    assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
    assert(match("", "", TEST_RESTRICTION_1) == 1);
    assert(match("A", "a", TEST_RESTRICTION_1) == 0);
    assert(match("123", "123", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_star() {
    assert(match("abcd*", "abc", TEST_RESTRICTION_1) == 1);
    assert(match("abc*d", "abcccccccd", TEST_RESTRICTION_1) == 1);
    assert(match("abc*de", "abcccccccd", TEST_RESTRICTION_1) == 0);
    assert(match("a*b*c*d*", "", TEST_RESTRICTION_1) == 1);
    assert(match("a*a*a*a*", "aaa", TEST_RESTRICTION_1) == 1);
    assert(match("a*b", "ba", TEST_RESTRICTION_1) == 0);
}

void test_match_regex_question() {
    assert(match("a?", "", TEST_RESTRICTION_1) == 1);
    assert(match("a?", "b", TEST_RESTRICTION_1) == 0);
    assert(match("a?", "a", TEST_RESTRICTION_1) == 1);
    assert(match("a?a?a?a?a?", "", TEST_RESTRICTION_1) == 1);
    assert(match("aa?", "aaa", TEST_RESTRICTION_1) == 0);
    assert(match("a?b?", "b", TEST_RESTRICTION_1) == 1);
    assert(match("a?a", "aa", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_tilde() {
    assert(match("~", "aaaa", TEST_RESTRICTION_1) == 1);
    assert(match("~", "", TEST_RESTRICTION_1) == 1);
    assert(match("~", "a", TEST_RESTRICTION_1) == 1);
    assert(match("~~~~", "", TEST_RESTRICTION_1) == 1);
    assert(match("~~a~~", "zzzz", TEST_RESTRICTION_1) == 0);
    assert(match("a~a~a~a", "ababababababa", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_multiple() {
    assert(match("!2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
                 TEST_RESTRICTION_1) == 1);
    assert(match("!~2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
                 TEST_RESTRICTION_1) == 1);
    assert(match("~abc", "sda12!$2", TEST_RESTRICTION_1) == 0);
    assert(match("p?h?~el*o?o?o*~", "hello", TEST_RESTRICTION_1) == 1);
    assert(match("po~t?t*ery", "pottery", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_tilde_restriction() {
    assert(match("a~a", "abbba", TEST_RESTRICTION_2) == 0);
    assert(match("a~a", "abbba", TEST_RESTRICTION_4) == 1);
    assert(match("a~a", "azzzzazazazazzzzzzzzzzza", TEST_RESTRICTION_4) == 1);
    assert(match("a~a~a", "azzazazaa", TEST_RESTRICTION_3) == 1);
}

int main() {
    printf("Starting Tests...\n");
    test_read_files();
    test_match_regex();
    test_match_regex_star();
    test_match_regex_question();
    test_match_regex_tilde();
    test_match_regex_multiple();
    test_match_regex_tilde_restriction();
    printf("All tests passed!!!\n");
}
