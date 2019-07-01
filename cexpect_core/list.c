
#include "internal/memory_allocation.h"
#include "internal/list.h"


struct ListItemData {
	ListItem *next;
	void *value;
};


struct ListData {
	ListItem *first;
};


static void free_list_item_recursively(ListItem *list_item) {
	if (!list_item)
		return;

	if (list_item->next)
		free_list_item_recursively(list_item->next);

	deallocate_memory(list_item);
}


/*
 * List Functions
 */
List *make_list(void) {
	List *list = allocate_memory(1, sizeof(List));
	list->first = NULL;
	return list;
}


void free_list(List *list) {
	free_list_item_recursively(list_first(list));
	deallocate_memory(list);
}


void add_to_list(List *list, void *value) {
	ListItem *new_item = allocate_memory(1, sizeof(ListItem));
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


void *list_value(ListItem *item) {
	return item->value;
}
