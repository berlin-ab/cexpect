#ifndef CEXPECT_LIST_H
#define CEXPECT_LIST_H

typedef struct Cexpect_ListItemData Cexpect_ListItem;
typedef struct Cexpect_ListData Cexpect_List;

// Cexpect_List
Cexpect_List *make_list(void);
void add_to_list(Cexpect_List *list, void *value);
int list_size(Cexpect_List *list);

// Cexpect_List items
Cexpect_ListItem *list_next(Cexpect_ListItem *item);
Cexpect_ListItem *list_first(Cexpect_List *list);
void *list_value(Cexpect_ListItem *item);

#endif //CEXPECT_LIST_H
