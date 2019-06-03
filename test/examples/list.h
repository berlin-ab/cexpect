//
// Created by Adam Berlin on 2019-06-03.
//

#ifndef CEXPECT_LIST_H
#define CEXPECT_LIST_H

typedef struct ListItemData ListItem;
typedef struct ListData List;

List *make_list(void);
void add_to_list(List *list, void *value);
int list_size(List *list);

#endif //CEXPECT_LIST_H
