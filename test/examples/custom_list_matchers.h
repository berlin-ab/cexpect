//
// Created by Adam Berlin on 2019-06-03.
//

#ifndef CEXPECT_CUSTOM_LIST_MATCHERS_H
#define CEXPECT_CUSTOM_LIST_MATCHERS_H

#include "cexpect_list.h"
#include "cexpect_cmatchers.h"

Matcher *list_is_empty();
Matcher *list_has_size(void *size);

#endif //CEXPECT_CUSTOM_LIST_MATCHERS_H
