#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//COMPILING
//gcc -o outputFilename inputFile.c
//can also forgo the -o flag and outputFilename, will then be a.out
//run with ./outputFilename

#define INT_MIN

//must have a main func
//doesn't need to be int, can be void etc, but must be called main
//don't need any params either
int main (int argc, char **argv)
{
	printf("Hello World!\n");
	int lec_n;
	printf("Which lecture? ");
	scanf("%d", &lec_n);

	if (lec_n == 1) {
//LEC 1
	//calling int will reserve an ints worth of bytes for this var, same as we're used to
	//even though we haven't yet passed a value, it could already contain junk old values
	//memory is NOT initialised to 0
	int ftemp;
	printf("Enter a temp in f: ");

	//scanf goes to stdio and takes in the given input in the format specified, here %d == int
	//& ampersand indicates the memory address of ftemp
	//scanf doesn't know the size of the memory buffer allocated, so it can technically overflow if you input something too big
	scanf("%d", &ftemp);

	//printf will return the number of chars printed, or a negative number if failed for any reason, we can used this as error checking
	//this will still work perfectly
	int ret = printf("%d f is %d in celsius\n", ftemp, (ftemp-32)*5/9);

	//we can print addresses of vars too
	printf("ftemp input was stored at memory loc %p\n", &ftemp);
	printf("end lec 1\n");
	

//TUTE 1
	//C types
	//C is static, so any var must have a type assigned to it
	//also most types have unsigned versions, which remove the sign bit from the encoding

	//C array size must be defined at creation, either explicitly or by listing values
	int demo_array_1 [10];
	int demo_array_2 [] = {1, 2, 3, 4};
	//can also overstate the number of elements in declaring and partially filling, the array will have declared length
	//side: char is 1 byte
	char helloarray[] = {'h', 'e', 'l', 'l', 'o' };
	//chars need '' instead of ""
	//strings need ""
	//%c is the char format symbol
	printf("print the last char in the array: %c\n\n", helloarray[4]);
	}


	if (lec_n == 2) {
//LEC 2
	//pointers

	//address operator &, indirection operator *

	//for a string, make an array of chars. its format symbol is s
	//can just use a blank size modifier to init size
	//"bouldering" has 10 chars, plus a null byte = 11 bytes (null = \0)
	char my_hobby[] = "bouldering";
	printf("I enjoy %s\n", my_hobby);
	//to create a pointer
	char capitala = 'A';
	char * whereisthea = &capitala;
	//the asterisk is the important bit, it means there is a memory address being saved
	printf("pointer at %p prints contents as ascii %s\n", whereisthea, whereisthea);

	//you can also reserve memory for a pointer
	int *age_pointer;
	//the amount is dependant on architecture, if its 32 bit system, needs 4 bytes for an address
	//can also assign pointer address afterwards
	int my_age = 22;
	age_pointer = &my_age;
	//remember asterisk indicates a pointer, so we can go to the memory address of value stored at age_pointer
	//imagine it like a fetch command
	printf("get value from pointer to int: %d\n", *age_pointer);
	//age_pointer == &my_age

	//we aren't allowed to use dynamic inits for arrays
	//int n = scanf();
	//int nums[n];
	//ARE NOT ALLOWED, EVEN IF IT WORKS ITS BANNED. variable length arrays don't know memory to allocate at compile time, and things break easily

	//can double up pointers
	int* * inception = &age_pointer;
	//type* * new_pointer_name = old_pointerl
	printf("double indirection, pointer->pointer = %d\n", **inception);

	//scanf requires an address, which is why it takes &

	//could use pointers for string slicing. can add 1 or subrtact from a pointer to increment memory address
	char message[] = "greetings";
	char *phrase_1 = &message[3];
	printf("string slicing kinda with pointers %c%c\n", *phrase_1, *(phrase_1 + 1) );
	//NEED TO KNOW THIS STUFF, IF DIFFERENT POINTER FORMATS ARE VALID

	//to cycle through a string:
	char helloarray[] = {'h', 'e', 'l', 'l', 'o' };
	char * str = &helloarray[0];
	while(*str != '\0') {
		str++;
	}
	//also
	while (*str) {//while (*str == true), or while *str isn't null
		//do stuff
	}

	int **data;
	//1. data is the address of another address that stores the address of an int
	//2. data is an array of separate addresses, and each of those addresses holds an int
	//3. data is the address of an array of ints
	//4. data is an array of addresses, and each of those addresses is the start of an array of ints
	//think of each * as an array, where some might just length = 1, but not neccesarily

	//now char ** argv from main makes more sense, its case 4
	//char * argv[]
	//get the 2nd char from 5th cmd line string:
	char second_fifth = *( *(argv + 4) + 1);
	//note: var* + 1 doesn't add 1 to the address, it adds sizeof(var_type)

	//if you want to increment by byte, recast to char, which is 1 byte per char. so you can take a 4 byte int and use a pointer byte by byte
	//void is a non-type

	//note: int is not always 4 bytes, some systems don't

	//sizeof() returns the number of bytes
	sizeof(message);
	//this is 10, 9 chars + null

	//const means the value cannot be changed
	const int birthday = 11;
	//birthday is now a read-only var
	//similarly, fileheadermainvar is now a read-only pointer, the address it contains cannot be changed
	char * const fileheadermainvar = "P1";

	//signed and unsigned numerical values
	//cannot assume signage, although some default to signed

	//fgets
	//char *line = fgets(buffer, length_of_buffer, file_name);
	//fgets runs until EOF, \n, or buffer fills
	//fgets needs a buffer, so declare it before. ours will have 7
	char buffer_fgets[7];
	//also needs a file
	FILE *file;
	file = fopen("hello.c", "w");

	char *fgets_words = fgets(buffer_fgets, 7, file);

	printf("%s", buffer_fgets);

	fclose(file);

	//enums
	//same as in other langs
	enum day_name {mon, tues, wed, thurs, fri, sat};
	enum month_name {jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	}

	if (lec_n == 3) {
//LEC 3
//john drinks hot water, implied prefer to tea/etc. wtf

	//enums
	//same as in other langs
	enum day_name {mon, tues, wed, thurs, fri, sat};
	enum month_name {jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

	//struct
	//array of different data types, a blob of memory
	//basically a class or type from other languages
	//except for methods, none of that
	//all types in the struct NEED to be known before creation, so that the compiler can run sizeof() to malloc properly
	//similarly variable length arrays won't work
	struct date {
		int day_num;
		enum day_name day;
		int month_num;
		enum month_name month;
	};
	//needs keyword struct, and a semicolon after, this is a statement
	//can also declare a struct at the same time
	//enum month_name month;
	//} bday {
	//	tues. 11. 1. jan
	//};
	//recomended to initialise separate to declare

	//can point, of course
	//also use . to access individual fields
	struct date my_bday = {11, tues, 1, jan};
	int intof_bday = my_bday.day_num;
	//this gets the address of bday, and goes to the starting byte of day_num

	//another pointer trick
	struct date *my_date;
	my_date = &my_bday;
	int my_bday_date;
	my_bday_date = my_date->day_num;
	//-> is a dereferencer for struct and also field accesser, means that go to the struct address of my_date and go to the day_num var

	//can also use typedef struct to define the name, but generally not good. basically means that struct name can be rewritten as something else
	typedef struct car_details{} Car;
	//now Car is the struct car_details, but later in code might not be clear what Car actually is

	//when using a struct in a function, the struct is ALWAYS copied, UNLESS you use const and or pointers
	//therefore use pointers

	//har *ptr = (char*)&my_bday;

	//array of dates
	struct date chagim[2];
	chagim[0].day_num = 14;
	chagim[1].month_num = 11;

	//stringcopy strncpy(destination, source, bytes);
	char demo[2];
	strncpy(demo, "a", 1);
	//can also use strcpy
	strcpy(demo, "b");
	printf("using strcpy %s\n", demo);
	
	//padding
	//when using a struct, say there is a char, the compiler will add padding, so that the char takes up a 'word' of space
	//eg a struct with 2 chars 1 int will take 8 bits = (1 + 3) * 2 + 8
	//you can order types to make stuff fit better, eg short and char adjacent, rather than short int then char
	//aka memory alignment
	//even though the compiler pads the bytes, this will only show using sizeof(struct)
		//but if you sum sizeof(struct.field), you will get the expected bytes, minus padding
		//same if you subtract the memory addresses from each other, will be able to find the alignment
	//TLDR make sure you know where the data in a struct is

	//union: we want different variants of a struct, but don't want to use more memory
	//but we want to re-use field with another struct or variable
	enum holding_type{book, film};

	struct catalog {
		char * title;
		enum holding_type type;

		union {
			struct {
				char * author; //4 byte address
				char * isbn;//4 byte address
				bool hardcover;//1 byte bool -> pads +3
			} book_info;

			struct {
				char * director;//4 byte address
				char * producer;//another
				char * studio;//another
			} film_info;
		} media_info;
	};
	//above is a struct called catalog, which has fields str title, enum holding_type, and either struct book or struvt film
	//at compile, checks which of the unions is larger, reserves that amount of memory
		//if we didn't use union, sizeof(catalog) would include BOTH sub-structs for book and film.
	
	//also note we cannot tell which field of the union is active, that's mainly why we use another var for type

	union {
		int happytime;
		char letters;
	} x;
	x.happytime = 11223344;
	x.letters = 'c';
	printf("char byte in the union that is also an int byte, ASCII for 'c': %d\n", x.letters);
	//won't use this so much, mainly in devices and stuff where space is a real issue
	
	//side: use (void*) when doing arithmetic with addresses/pointers, so that you cast each type to void* to get rid of warnings
	//here, how many bytes between the enum month and the int day_num
	printf("using void* for address arithmetic dif: %ld\n", (void*)&(my_bday.month) - (void*)&(my_bday.day_num) );

	//bitfields
	//structs where we specify the number of bits in a byte are reserved
	//packing in data for real. there is still padding. popular for small devices, metadata. 
	struct yesno {
		unsigned lefty: 1;
		unsigned eyecolor: 2;
		unsigned gend: 1;
		unsigned padding: 4;
	};

	struct yesno stanley = {0, 0, 1};
	printf("from bitfield struct, stanley lefty? %d\n", stanley.lefty);
	//bitfields are difficult to make portable
	//bitshifts and bitwise shifts??
	//shift right/left >> <<
	//bitwise AND &, OR |, XOR ^, NOT ~
	//dis motherfucker just assumes you're fucking fluent in bitshifts and masking. lec now overtime, another 45 to go. fuck
	//later in lec: you should have learnt this in first year, youre 2nd year now...?

	//files
	//means we don't have to go flip registers or switches, can tell an OS to go to that
	//variable length, useful metadata, stored in different ways, places, configurations
	//in order to read/write, we do system calls, separate to user access, to check if we are doing valid commands, permissions etc
	//files are accessed for read/write through a stream. can work within streams, open or close them.
	//FILE is a typedef struct

	//fopen modes
	//r read, w write, rb wb for binary
	//fscanf and fprintf for file versions I/O
	//fclose
	//they also return a value, so you can verify they worked

	//ftell
	//tells the byte we're at relative from the beginning of file
	//fseek can navigate to a specific byte

	//feof() checks for EOF byte
	//while (! feof(file)) {}

	//buffer holds data from source before it reaches destination, aggregates data preprocessing
	//unbuffered, fully buffered, line buffered that ends with /EOF
	//how fast do you want the thing to execute, but also consider how much stuff will be executed immediately/how big buffer
	
	//flush
	//stop everything at this point until all operations have been completed
	//fflush

	}

//LEC 4
if (lec_n == 4) {
	printf("dynamic memory management!\n\n");
	//memory areas - we work with 4
	//stack: automatically managed memory, local variables, function args
	//stack management is automatic for us thanks to libc, stuff like printf
	//heap: dynamically allocated memory, request a chunk of memory, for the user to manage
	//must free memory that isn't used
	//global/static: global variables, and static data that is part of the compiled binary
	//code: program instructions
	
	//memory layout
	//code is basically fixed, first in the memory space, and static/global is also, at compile time
	//above these areas are heap, then some free space, then stack
	//heap has a fixed start address after the static/global area, and stack has fixed end address, at the end of the memory space
	//the stack will grow down towards the heap, into the free space
	//if you grow heap and stack too much they'll eat all the free space, and stuff will fail
		//stack overflow -> into the heap
	//c strings go to static
	
	static int value = 1;
	//guess where this int goes? well done. 
	int val = 90;
	//yeah, this one to stack

	/*stack
	after a function call, all args of a function get pushed straight to the stack, in order
	push return address, which will prob be the next line of code: this is the address in the code memory area for next line
		basically the program counter, but abstracted
	libc executes the stack//
	inside the function:
	increment the stack pointer to find the correct variables
	and reserve space for them
	execute the code, increment program counter, go there and do
	returning, you need to pop all the stuff we don't need on the stack anymore
	save the return address on the side for a sec, and then push the return value of the func
	even if func return is void, the execution will pretend its int, easier to work with
	*/

	/* heap
	dynamically allocated at run-time
	eg: if you take a string from scanf, you either need to preallocate and hope enough
		or dynamically allocate
	same in Java etc, when you create an object, it goes into heap, not stack
	*/
	
	//he doesn't check the time in the corner of his laptop, rather $ date
		//writes a script to count down 300 to show a 5 min break
			//holy shit dude

	/* memory allocation functions return a pointer to void: void *ptr;
	then must cast the pointer to a specific type
	need to #include <stdlib.h>
	*/

	//void *malloc(size_t size);
	//this returns a pointer to the address if everything is fine
		//otherwise returns NULL pointer, run out of space
	//size_t basically means int that cannot be negative, unsigned
	
	//create a pointer to an int
	//malloc 20x ints, 4bytes * 20 = 80 bytes, and cast that void* to int*
	//good idea to init pointers to NULL so that you know they're working
	int *ptr = NULL;
	ptr = (int*) malloc(sizeof(int)*4);
	*ptr = 11;
	//this will still work without casting to int*
	printf("heap reserved 4x 4byte ints at %p, first one is %d\n", &ptr, *ptr);

	//can also use calloc to init all the memory to 0, and get rid of garbage: contiguous allocation
	int *zeroes = (int*)calloc(1, sizeof(int));
	//calloc(number of items, size of items). above: 1 int
	printf("used calloc to preset int at %p in the heap to %d\n", &zeroes, *zeroes);
	
	//free(ptr) deallocates the memory
	//same like when writing a while, immediately write i++, malloc, free, and ptr = NULL must be typed together
	
	free(ptr);
	
	printf("after free() the malloced 4xints, can still use ptr, but get junk: address %p contains %d: prev 11\n", &ptr, *ptr);
	//therefore, its good habit to NULL pointers so that you don't use shit left in the heap
	ptr = NULL;
	
	//if you change your mind on the size of needed space, use realloc: expand or shrink existing allocation
	//will return NULL if no contiguous block that works, and also might not neccessarily use the same original address
	//this also copies over all of the existing values in memory
	zeroes = (int*)realloc(zeroes, sizeof(int)*2);
	printf("realloced calloc to %p, check if it is the same. sometimes yes, sometimes no\n\n", &zeroes);
	free(zeroes);

	//can also use realloc like malloc
	char* names = (char*)realloc(NULL, sizeof(char)*5);
	//will start from NULL and use that to 'copy', means you just allocate 5 new bytes for chars in *names
	free(names);
	names = NULL;

	//malloc sizeof(struct) and cast :(struct struct_name*)malloc
	//remember can also use ptr->struct_field = value
	
	/* important
	1. always use free()
	2. never just free(0xA123)
	3. never use deallocated memory
		!!! if you type malloc(), IMMEDIATELY add free() and ptr = NULL;
	4. know how many bytes you need
		use sizeof(type)*num
			remember strings need a '\0'
	5. check for success, make sure ptr != NULL
	*/

	//linked lists
	//a list can be defined recursively: an element followed by a list
	//we only gonna be working with singly linked

	struct node_demo {
		void* data;//pointer for some data, 4 bytes. void can be something else
		struct node *next;//pointer for the next node, 4 bytes. end node, next = NULL
	}; 
	int eight = sizeof(struct node_demo);

	//funcs will mimic c string funcs, which terminate with \0

	//struct node, init pointer, malloc, assign pointer, fill struct fields in malloced
	struct node {
		int data;
		struct node * next;
	};
	struct node *n1;
	n1 = (struct node*)malloc(sizeof(struct node));
	n1->data = 11;
	n1->next = NULL;
	//pointer to first node
	struct node *head = n1;

	struct node *n2 = (struct node*)malloc(sizeof(struct node));
	n2->data = 22;
	//reassign next pointers
	n1->next = n2;
	n2->next = NULL;

	printf("reaching from head to get data in 2nd nodein LL: %d\n", head->next->data);

	

	struct node *n3 = (struct node*)malloc(sizeof(struct node));
	n2->next = n3;
	n3->data = 33;
	n3->next = NULL;
	
	struct node *n5 = (struct node*)malloc(sizeof(struct node));
	n5->next = n1;
	head = n5;//BE CAREFUL NOT TO DO head->next!!! head IS A POINTER, NOT A NODE
	n5->data = 55;

	struct node *cursor;
	printf("LL node data in order: inserted at head: ");
	cursor = head;
	while (cursor != NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
//side, some compilers/arch remove freed mem from heap access -> give it to stack, most just mark it as unused
	free(n1);
	free(n2);
	free(n3);
	free(n5);
}





	return 0;
}

