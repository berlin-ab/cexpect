#ifndef CEXPECT_LIST_H
#define CEXPECT_LIST_H


typedef struct ListItemData ListItem;
typedef struct ListData List;


/*
 * List
 */
List *make_list(void);
void add_to_list(List *list, void *value);
int list_size(List *list);


/*
 * List items
 */
ListItem *list_next(ListItem *item);
ListItem *list_first(List *list);
void *list_value(ListItem *item);


#endif //CEXPECT_LIST_H
