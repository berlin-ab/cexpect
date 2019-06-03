#include <stdlib.h>

#include "cexpect.h"
#include "cexpect_cmatchers.h"


typedef struct ListData {} List;


bool is_list_empty() {
}


Matcher *list_is_empty() {
    Matcher *matcher = make_inspection_matcher(is_list_empty);

    return matcher;
}


List *make_list(void) {
    return calloc(1, sizeof(List));
}


void a_list_starts_as_empty(Test *test) {
    List *list = make_list();

    expect(test, list, list_is_empty());
}


int main(int args[]) {
  Suite *suite = make_suite("List test");
  add_test(suite, a_list_starts_as_empty);
  cexpect_start(suite);
}
