/**
 * comp2017 - assignment 3
 * Matan Cohen
 * mcoh5893
 */
 //gcc -o spx_exchange spx_exchange.c -DEBUG
 //./spx_exchange products.txt ./trader_a ./asas

#include "spx_exchange.h"

int main(int argc, char **argv) {
	
	//First read in product file.
	errno = 0;
	FILE *file;
	file = fopen(argv[1], "r");

	if (errno != 0) {
		perror("Error");
		return 1;
	}
	errno = 0;

	//Get the expected number of products
	int num_of_products;
	int return_value = fscanf(file, "%d", &num_of_products);
	printf("got num of products %d\n", num_of_products);
	if (return_value != 1) {
		perror("Error");
		return 1;
	}
	char *product_list;
	product_list = (char*)malloc(num_of_products * (MAX_NAME_LENGTH * (sizeof(char))));

	DEBUG("created list");

	//Read in the products
	int i = 0;
	int product_list_actual = 0;
	while(i < num_of_products) {
		fscanf(file, "%s", &product_list[i]);
		if (&product_list[i] != NULL && &product_list[i] != "\n") {
			product_list_actual++;
		}
		printf("got product %s\n", &product_list[i]);
		i++;
	}
	printf("products.txt vs actual: %d %d\n", num_of_products, product_list_actual);


	/*need to validate product list vs products.txt
	check dupes
	check empty lines*/
	//ISNT WORKING: prob not checking blank lines properly
	for (i = 0; i < num_of_products; i++ ) {
		if (&product_list[i] == NULL || &product_list[i] == "\n") {
			printf("Warning: Blank product entry, line %d\n", i);
		} else {
			for (int j = 0; j < num_of_products; j++ ) {
				if (i != j && &product_list[i] == &product_list[j]) {
					printf("Warning: Duplicate product %s\n", &product_list[i]);
				}
			} 
		}
	} 

	/*get trader IDs
	validate dupes
	create pipes*/

	//Get and validate traders
	int num_of_traders = argc - 2;
	char actually_dot = '.';
	char actually_slash = '/';

	char *trader_list = (char*)malloc(0);
	int actual_ntraders = 0;


	for (i = 0; i < num_of_traders; i++ ) {
		printf("checking trader %s\n", argv[argc - num_of_traders + i]);
		char fullstop = argv[argc - num_of_traders + i ][0];
		char slash = argv[argc - num_of_traders + i ][1];
		if ( (strcmp(&fullstop, &actually_dot) == 0 ) && (strcmp(&slash, &actually_slash ) != 0 ) ) {//check this out
			printf("bad trader format %s\n", argv[argc - num_of_traders + i]);
		} else {
			actual_ntraders ++;
			trader_list = (char*)realloc(trader_list, sizeof(char)*MAX_NAME_LENGTH);
			strcpy(&trader_list[actual_ntraders], argv[argc - num_of_traders + i]);
			DEBUG("Added a trader.");
			//printf("got trader %s", &trader_list[actual_ntraders]);
		}
	}

	printf("actually read %d traders from expected %d\n", actual_ntraders, num_of_traders);

	//Open pipe
	/*Add 2 when concatenating to shift pointer index*/
	char *default_exchange_name = "/tmp/spx_exchange_";
	char *default_trader_name = "/tmp/spx_trader_";

	char *trader_pipe_names = (char*)malloc(0);

	DEBUG("prepping names, pipes, and processes...");
	for (i = 2; i < (actual_ntraders + 2); i++ ) {
		char *initialiser_trader_name = (char*)malloc( sizeof(char) * (strlen(default_trader_name) + strlen(argv[i] -2)) );
		strncpy(initialiser_trader_name, default_trader_name, strlen(default_trader_name) + 1);
		strcat(initialiser_trader_name, (argv[i] + 2) );
		char *initialiser_exhange_name = (char*)malloc( sizeof(char) * (strlen(default_exchange_name) + strlen(argv[i] -2)) );
		strcpy(initialiser_exhange_name, default_trader_name);
		strcat(initialiser_exhange_name, (argv[i] + 2));	
		trader_pipe_names = (char*)realloc(trader_pipe_names, sizeof(char)*strlen(initialiser_exhange_name));
		strcpy(&trader_pipe_names[actual_ntraders -i-2], initialiser_exhange_name);
		DEBUG("Added a name to the pipe list.");

		printf("trader pipe name: %s\n", initialiser_trader_name);	
		


		//now open pipe
		return_value = 0;
		return_value = mkfifo(initialiser_trader_name, S_IRWXU | S_IRWXG);
		if (return_value < 0) {
			perror("Error");
		}
		return_value = mkfifo(initialiser_exhange_name, S_IRWXU | S_IRWXG);
		if (return_value < 0) {
			perror("Error");
		}
		

		free(initialiser_exhange_name);
		free(initialiser_trader_name);

		DEBUG("Processed a trader - name, pipe, process.\n");
	}
	printf("hereeee\n");
	
	printf("trader pipes: %s\n", &trader_pipe_names[0]);



	return_value = 0;
	//return_value = 
	if (return_value < 0) {
		perror("Error");
	}

	free(product_list);
	free(trader_list);
	free(trader_pipe_names);



	return 0;
}




/*
TODO
concurrent trader and exchange: use fork and exec from exchange, will init trader
open pipe from trader to exchange and vice versa
	first check that can read and write through at all
setup command processing so exchange can read in commands
exhange matching -> old java exchange process code?

exhange stores orders: linked list containing 



from the spec:
exchange reads from product file
creates 2 pipes for each trader, read and write
fork and exec for each trader
exhange sends MARKET OPEN to each trader
trader writes order to pipe
trader sends SIGUSR1 signal
exchange receives signal
exchange writes receipt to trader pipe
exchange writes order to other traders
*/
