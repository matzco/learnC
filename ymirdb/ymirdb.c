/**
 * comp2017 - assignment 2
 * NAME
 * NUMBER
 */
 
/*
BUGS:
set a 1, pop a, max a: expect none/undefined, gets -2^32. likewise for min a.

*/

/*
Is a library allowed? 
Check if its here: https://en.cppreference.com/w/c/header
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "ymirdb.h"

/*
Concept:
2D dangling doubly linked list: list of entries, with each entry having a dangling list of elems for values. 
Max modularity for functions

FOLLOW THE LAWS
Keep all functions as abstract as possible, make them reusable
keep logic out of main, and chunk it as much as possible/sensible
pointers are prefereable
if something is freed, make sure pointers at nodes on BOTH sides are redirected


Use:
memcpy to copy structs for snapshots
bubble sort too slow for sort
uniq - will have to check all possibles: prev == NULL, 

*/


void command_bye() {
	printf("bye\n");
	exit(0);
}

void command_help() {
	printf("%s\n", HELP);
}

int free_entries(struct entry *entry) {
	/*Recursive freeing makes it easy not to free an entry that still has entries linked to it*/
	if (entry -> next != NULL) {
		free_entries(entry -> next);
		if (entry -> values != NULL) {
			free_elements(entry -> values);
		}
		free(entry);
	} else {
		if (entry -> values != NULL) {
			free_elements(entry -> values);
		}
		free(entry);
	}
	return 0;
}

int free_elements(struct element *elem) {
	/*Recursive freeing makes it easy not to free an elem that still has entries linked to it*/
	if (elem -> next != NULL) {
		free_elements(elem -> next);
		free(elem);
	} else {
		free(elem);
		return 1;
	}
	return 0;
}

void add_entry(char new_key[], struct entry *head_head) {
	/*Entries are appended*/
		while (head_head -> next != NULL) {
			head_head = head_head -> next;
		}
		struct entry *n = (struct entry*)malloc(sizeof(struct entry));
		strncpy(n -> key, new_key, MAX_KEY);
		head_head -> next = n;
		n -> next = NULL;
		n -> prev = head_head;
		n -> values = NULL;
}

void add_value(struct entry *cur_entry, char new_value[]) {
	struct element *temp = cur_entry -> values;
	struct element * v = (struct element*)malloc(sizeof(struct element));
	v -> value = atoi(new_value);
	if (cur_entry -> values == NULL) {
		cur_entry -> values = v;
		v -> next = NULL;
		v -> prev = NULL;
		return;
	} else {
		while (temp -> next != NULL) {
			temp = temp -> next;
		}
		temp -> next = v;
		v -> next = NULL;
		v -> prev = temp;
		return;
	}
}

int entries_contain(struct entry *head_head, char entry_key[]) {
	if (head_head -> next == NULL) {
		return 0;
	} else {
		while (head_head != NULL) {
			if (strcmp(head_head->key, entry_key) == 0) {
				return 1;
			}
			head_head = head_head -> next;
		}
		return 0;
	}
}

void print_entry_values(struct entry *cur_entry) {
	/*Called for 'get' and 'list entries' commands.*/
	if (cur_entry == NULL) {
		return;
	} else if (cur_entry -> values == NULL) {
		printf("[]\n");
		return;
	} else {
		struct element *cursor = cur_entry -> values;
		printf("[");
		while (cursor -> next != NULL) {
			printf("%d ", cursor -> value);
			cursor = cursor -> next;
		}
		printf("%d]\n", cursor -> value);
		return;
	}
}

void print_entries(struct entry *head_head, bool only_keys) {
	/*'only_keys' used to distinguish between list entries and list keys commands.*/
	while (head_head -> next != NULL) {
		head_head = head_head -> next;
	}
	while (head_head -> prev != NULL) {
		if (only_keys) {
			printf("%s\n", head_head -> key);
		} else {
			printf("%s ", head_head -> key);
			print_entry_values(head_head);
		}
		head_head = head_head -> prev;
	}
}

struct entry* get_entry(struct entry *head_head, char entry_key[]) {
	if (head_head -> next == NULL) {
		return NULL;
	} else {
		while (head_head != NULL) {
			if (strcmp(head_head->key, entry_key) == 0) {
				return head_head;
			}
			head_head = head_head -> next;
		}
		return NULL;
	}
}

void del_entry(struct entry *cur_entry) {
	if (cur_entry -> values != NULL) {
		free_elements(cur_entry -> values);
	}
	/*Reassigns pointers depending on the entry location in the entry list.*/
	if (cur_entry -> next == NULL) {
		cur_entry -> prev -> next = NULL;
	} else {
		/*"Reach" back and direct pointer forward, and vice versa*/
		cur_entry -> prev -> next = cur_entry -> next;
		cur_entry -> next -> prev = cur_entry -> prev;
		free(cur_entry);
	}
}

int pop_element(struct entry *cur_entry) {
	/*Due to the int return type, param verification is done prior to calling this function.*/
	struct element *temp = cur_entry -> values;
	int to_pop = temp -> value;
	if (temp -> next == NULL) {
		cur_entry -> values = NULL;
	} else {
		cur_entry -> values = temp -> next;
		temp -> next -> prev = NULL;
	}
	free(temp);
	return to_pop;
}

void get_key(char key[]) {
	/*Used to get char key[] with the same format as recorded by the set command.
	set uses strtok() and adds '\0' to the key, so here '\n' must be replaced by '\0' at the end of the key.*/
	char *key_input = strtok(NULL, " ");
	strncpy(key, key_input, MAX_KEY);
	int add_space = strlen(key);
	key[add_space-1] = '\0';
}

int get_element_index(struct entry *cur_entry, int index, bool pluck) {
	/*Due to the int return type, param verification is done prior to calling this function.
	bool pluck is used to differentiate between pick and pluck commands.*/
	struct element *temp = cur_entry -> values;
	int index_value = index - 1;
	while (index > 1) {
		temp = temp -> next;
		index --;
	}
	index_value = temp -> value;
	if (pluck) {
		/*If the elem is on the ends of the elem list, prev || next == NULL, thus each case needs its own handling.*/
		/*If the elem is the only elem...*/
		if (temp -> next == NULL && temp -> prev == NULL) {
			cur_entry -> values = NULL;
		/*... or the first elem...*/
		} else if (temp -> prev == NULL) {
			cur_entry -> values = temp -> next;
		/*... or the last elem...*/
		} else if (temp -> next == NULL) {
			temp -> prev -> next = NULL;
		/*... or is somewhere in the middle.*/
		} else {
			temp -> prev -> next = temp -> next;
			temp -> next -> prev = temp -> prev;
		}
		free(temp);
	}
	return index_value;
}

int number_of_elements(struct entry *cur_entry) {
	int count = 0;
	if (cur_entry -> values == NULL) {
		return count;
	} else {
		struct element *temp = cur_entry -> values;
		while (temp != NULL) {
			temp = temp -> next;
			count ++;
		}
		return count;
	}
}

void push_element(struct entry *cur_entry, int new_value) {
	struct element *temp = cur_entry -> values;
	struct element * v = (struct element*)malloc(sizeof(struct element));
	v -> value = new_value;
	v -> prev = NULL;
	if (temp == NULL) {
		cur_entry -> values = v;
		v -> next = NULL;
	} else {
		cur_entry -> values = v;
		temp -> prev = v;
		v -> next = temp;
	} 
}

void append_element (struct entry *cur_entry, int new_value) {
	struct element * v = (struct element*)malloc(sizeof(struct element));
	v -> value = new_value;
	v -> next = NULL;
	if (cur_entry -> values == NULL) {
		cur_entry -> values = v;
		v -> prev = NULL;
	} else {
		struct element *temp = cur_entry -> values;
		while (temp -> next != NULL) {
			temp = temp -> next;
		}
		temp -> next = v;
		v -> prev = temp;
	}
}

int sum_elements (struct entry *cur_entry) {
	int total = 0;
	struct element *temp = cur_entry -> values;
	while (temp != NULL) {
		total += temp -> value;
		temp = temp -> next;
	}
	return total;
}

int max_element(struct entry *cur_entry) {
	int maximum = INT_MIN;
	struct element *temp = cur_entry -> values;
	while (temp != NULL) {
		if ( (temp -> value) > maximum) {
			maximum = temp -> value;
		}
		temp = temp -> next;
	}
	return maximum;
}

int min_element(struct entry *cur_entry) {
	int minimum = INT_MAX;
	struct element *temp = cur_entry -> values;
	while (temp != NULL) {
		if ( (temp -> value) < minimum) {
			minimum = temp -> value;
		}
		temp = temp -> next;
	}
	return minimum;
}

/*						##### MAIN ######                            */

int main(void) {

	char line[MAX_LINE];

	/*head_head pointer - used as the head of all entries and elements. Its fields are filled but not used.*/
	struct entry *head_head = (struct entry*)malloc(sizeof(struct entry));
	strncpy(head_head->key, "unassigned", MAX_KEY);
	head_head -> next = NULL;
	head_head -> values = NULL;
	head_head -> prev = NULL;

	//Snapshots head pointer: to be implemented fully...
	struct snapshot *snapshot_head = (struct snapshot*)malloc(sizeof(struct snapshot));
	snapshot_head -> id = 0;
	snapshot_head -> next = NULL;

	while (true) {
		printf("> ");

		fgets(line, MAX_LINE, stdin);
		
		/*Take cmd input, and lowercase.*/
		char *cmd;
		cmd = strtok(line, " ");
		for (int i = 0; i < strlen(cmd); i++ ) {
			cmd[i] = tolower(cmd[i]);
		}

		
/*				##### INPUT PROCESSING #####					 */
		

		if (strcmp(cmd, "bye\n") == 0) {
			free_entries(head_head);
			command_bye();
		} /*else if (cmd == NULL) {
			free_entries(head_head);
			command_bye();
		}*/
		else if (strcmp(cmd, "help\n") == 0) {
			command_help();
		} 
		else if (strcmp(cmd, "set") == 0) {
			char key[MAX_KEY];
			char *key_input = strtok(NULL, " ");
			strncpy(key, key_input, MAX_KEY);
			if (entries_contain(head_head, key) == 1) {
				/*Overwriting is permitted, but the entry's elements must be freed first.*/
				struct entry *cur_entry = get_entry(head_head, key);
				if (cur_entry -> values != NULL) {
					free_elements(cur_entry -> values);
				}
				cur_entry -> values = NULL;
			} else {
				add_entry(key, head_head);
			}
			/*The entry has been set/cleared; now the elements.*/
			char *input_item;
			/*strtok() continues from previous call location if passed a NULL parameter (man strtok).*/
			while ((input_item = strtok(NULL, " ")) != NULL) {
				struct entry *cur_entry = get_entry(head_head, key);
				add_value(cur_entry, input_item);
			}	
			printf("ok\n\n");
		}
		else if (strcmp(cmd, "get") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				print_entry_values(temp);
				printf("\n");
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "del") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				del_entry(temp);
				printf("ok\n\n");
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "pop") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				/*pop can still be called if the entry contains no elements.*/
				if (temp -> values == NULL) {
					printf("nil\n\n");
				} else {
					printf("%d\n\n", pop_element(temp));
				}
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "pick") == 0) {
			char key[MAX_KEY];
			char *key_input = strtok(NULL, " ");
			strncpy(key, key_input, MAX_KEY);
			if (entries_contain(head_head, key) == 1) {
				struct entry *cur_entry = get_entry(head_head, key);
				int count_elems = number_of_elements(cur_entry);
				/*The element index must be read in as a string, and converted to int after.*/
				char *element_index_char = strtok(NULL, " ");
				int element_index = atoi(element_index_char);
				if (element_index < 1 || element_index > count_elems) {
					printf("index out of range\n\n");
				} else {
					printf("%d\n\n", get_element_index(cur_entry, element_index, false));
				}
			} else {
				printf("no such key\n\n");
			}
		} 
		else if (strcmp(cmd, "pluck") == 0) {
			char key[MAX_KEY];
			char *key_input = strtok(NULL, " ");
			strncpy(key, key_input, MAX_KEY);
			if (entries_contain(head_head, key) == 1) {
				struct entry *cur_entry = get_entry(head_head, key);
				int count_elems = number_of_elements(cur_entry);
				/*Element index is input as char string, and converted to int before being validated.*/
				char *element_index_char = strtok(NULL, " ");
				int element_index = atoi(element_index_char);
				/*Validation must be done before calling get_element_index(), and it is indirectly
				done through the above function call number_of_elements().*/
				if (element_index < 1 || element_index > count_elems) {
					printf("index out of range\n\n");
				} else {
					printf("%d\n\n", get_element_index(cur_entry, element_index, true));
				}
			} else {
				printf("no such key\n\n");
			}
		} 
		else if (strcmp(cmd, "push") == 0) {
			char key[MAX_KEY];
			char *key_input = strtok(NULL, " ");
			strncpy(key, key_input, MAX_KEY);
			if (entries_contain(head_head, key) == 1) {
				struct entry *cur_entry = get_entry(head_head, key);
				char *char_input_value;
				/*Push must allow for pushing of multiple elements.*/
				while ( (char_input_value = (strtok(NULL, " "))) != NULL) {
					int input_value = atoi(char_input_value);
					push_element(cur_entry, input_value);
				}
				printf("ok\n\n");
			} else {
				printf("no such key\n\n");
			}
		}
		/*More implementation needed - interaction with snapshots.*/
		else if (strcmp(cmd, "purge") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				del_entry(temp);
				printf("ok\n\n");
			} else {
				printf("ok\n\n");
			}
		}
		else if (strcmp(cmd, "append") == 0) {
			char key[MAX_KEY];
			char *key_input = strtok(NULL, " ");
			strncpy(key, key_input, MAX_KEY);
			if (entries_contain(head_head, key) == 1) {
				struct entry *cur_entry = get_entry(head_head, key);
				char *char_input_value;
				while ( (char_input_value = (strtok(NULL, " "))) != NULL) {
					int input_value = atoi(char_input_value);
					append_element(cur_entry, input_value);
				}
				printf("ok\n\n");
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "uniq") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				/*Implement uniq()*/
				printf("ok\n\n");
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "sort") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				/*Implement sort()*/
				printf("ok\n\n");
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "len") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				printf("%d\n\n", number_of_elements(temp));
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "sum") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				printf("%d\n\n", sum_elements(temp));
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "max") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				printf("%d\n\n", max_element(temp));
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "min") == 0) {
			char key[MAX_KEY];
			get_key(key);
			if (entries_contain(head_head, key) == 1) {
				struct entry *temp = get_entry(head_head, key);
				printf("%d\n\n", min_element(temp));
			} else {
				printf("no such key\n\n");
			}
		}
		else if (strcmp(cmd, "list") == 0) {
			/*list is the primary command, the secondary list command must be input and lowercased.*/
			char *list_cmd;
			list_cmd = strtok(NULL, " ");
			for (int i = 0; i < strlen(list_cmd); i++ ) {
				list_cmd[i] = tolower(list_cmd[i]);
			}
			if (strcmp(list_cmd, "keys\n") == 0) {
				if (head_head -> next == NULL) {
					printf("no keys\n\n");
				} else {
					print_entries(head_head, true);
					printf("\n");
				}
			} else if (strcmp(list_cmd, "entries\n") == 0) {
				if (head_head -> next == NULL) {
					printf("no entries\n\n");
				} else {
					print_entries(head_head, false);
					printf("\n");
				}
			} else if (strcmp(list_cmd, "snapshots\n") == 0) {
				if (snapshot_head -> next == NULL) {
					printf("no snapshots\n\n");
				} else {
					/*TODO: implement snapshots.*/
				}
			}
		}
		
  	}
	return 0;
}

