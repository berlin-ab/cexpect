
#include "internal/memory_allocation.h"
#include "internal/list.h"


struct Cexpect_ListItemData {
	Cexpect_ListItem *next;
	void *value;
};


struct Cexpect_ListData {
	Cexpect_ListItem *first;
};


/*
 * Cexpect_List Functions
 */
Cexpect_List *make_list(void) {
	Cexpect_List *list = allocate_memory(1, sizeof(Cexpect_List));
	list->first = NULL;
	return list;
}


void add_to_list(Cexpect_List *list, void *value) {
	Cexpect_ListItem *new_item = allocate_memory(1, sizeof(Cexpect_ListItem));
	new_item->next = NULL;
	new_item->value = value;

	if (list->first == NULL) {
		list->first = new_item;
		return;
	}

	Cexpect_ListItem *item;
	
	for(item = list_first(list); list_next(item); item = list_next(item)) {
		// do nothing
	}

	item->next = new_item;
}


int list_size(Cexpect_List *list) {
	int size = 0;
	
	for (Cexpect_ListItem *item = list_first(list); item; item = list_next(item)) {
		size++;
	}

	return size;
}


Cexpect_ListItem *list_first(Cexpect_List *list) {
	return list->first;
}


Cexpect_ListItem *list_next(Cexpect_ListItem *item) {
	return item->next;
}


void *list_value(Cexpect_ListItem *item) {
	return item->value;
}
