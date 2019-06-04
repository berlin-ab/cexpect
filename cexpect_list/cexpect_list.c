#include <stdlib.h>


#include "cexpect_list.h"


struct ListItemData {
	ListItem *next;
	void *value;
};


struct ListData {
	ListItem *first;
};


/*
 * List Functions
 */
List *make_list(void) {
	List *list = calloc(1, sizeof(List));
	list->first = NULL;
	return list;
}


void add_to_list(List *list, void *value) {
	ListItem *new_item = calloc(1, sizeof(ListItem));
	new_item->next = NULL;
	new_item->value = value;

	if (list->first == NULL) {
		list->first = new_item;
		return;
	}

	ListItem *item;
	
	for(item = list_first(list); list_next(item); item = list_next(item)) {
		// do nothing
	}

	item->next = new_item;
}


int list_size(List *list) {
	int size = 0;
	
	for (ListItem *item = list_first(list); item; item = list_next(item)) {
		size++;
	}

	return size;
}

ListItem *list_first(List *list) {
	return list->first;
}


ListItem *list_next(ListItem *item) {
	return item->next;
}


bool list_has_next(ListItem *item) {
	return item->next != NULL;
}


void *list_value(ListItem *item) {
	return item->value;
}
