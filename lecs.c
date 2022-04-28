#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>//for stuff like INT_MIN
#include <signal.h>//signals
#include <sys/types.h>
#include <errno.h>//errno: extern int errno;
#include <unistd.h>//for processes and system stuff, pipes
#include <wait.h>//wait fork
#include <sys/select.h>//select

#define hundred 100
//you can redefine a value, throws a warning

#define min(a,b) ((a < b) ? (a) : (b) )
#define square(a) (a*a)

//JOHNS RECOMMENDED DEBUGGING STUFF, LEC 6 149
//add compile flag -DEBUG (-D(var for define))
#ifdef EBUG
	#define DEBUG(s) (printf("debug: %s\n", s))
#else
	#define DEBUG(s) //null
#endif

//COMPILING
//gcc -o outputFilename inputFile.c
//can also forgo the -o flag and outputFilename, will then be a.out
//run with ./outputFilename

int sum(int a, int b) {
	return a + b;
}

int product(int a, int b) {
	return a * b;
}

struct node {
	int value;
	struct node *next;
};



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
//john drinks hot water, he prefers to tea or coffee or cold water.lol

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
	//dis motherfucker john just assumes you're fucking fluent in bitshifts and masking
	// lec now overtime, another 45 to go. fuck
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
	//guess where this int goes? well done. (static aka global aka static/global)
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
	
	printf("after free() the malloced 4xints, can still use ptr, but get junk: address %p contaied 11: now %d\n", &ptr, *ptr);
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

else if (lec_n == 5) {
	//function pointers, signals, low level I/O
	
	//imagine if c compiled into a high level language/version of assembly.
	//if in c == cmpl in asm. and jmp to skip to a specific line, if the if wasn't fulfilled
	//when we call a function, we are essentially doing a jump
	//cos we go down program instructions, and then jump to another section of code to do something else
	//in asm call functionname

	//we can make an address pointer to a function
	//return_type (*function_name)(param declaration);
	int (*func_pointer)() = sum;
	printf("using a function pointer for 3+3: %d\n", func_pointer(3,3));
	func_pointer = product;
	printf("reassigned function pointer, now 3*3 : %d\n", func_pointer(3,3));
	//now we can use *func_pointer to change what function it is referencing
	//call func_pointer with: func_pointer();
	//in asm: call *r18 == call dereference(value in register 18)
	
	//can practical for basically calling a func after an if
	//if param set function pointer to this, else to that. then call function pointer
	//OR eg function to process, user can flag simple or complex, process_pointer = complex;
	//use: AI in a game, can level be changed during play? if yes, prob using function pointers

	//signals - relates to architecture
	//I/O will stop running processes, and will instead process the I/O
	//different levels, hardware, OS, application
	//application level = signals
	//aka software interrupt. the current running state needs to be saved, and then we go run code elsewhere

	//use signals like:
	//signal(signal_type, void_function);
	
	//in bash: kill -9 <program ID>
	//get PID from ps -A|grep a.out = 18013
	//eg: kill -s SIGSEGV PID
	//whole load of different signals and codes, 2 is SIGINTerrupt

	//side: keyword volatile int val = 5;
	//tells compiler not to apply optimisations at all to this

	//new type: sighandler_t
	//typedef void (*sighandler_t)(int);
	
	//errno = error number
	//instead of using exceptions, c has a global error number, which is set when something errors
	//errno is set to int based on the last failed operation, if something succeeded after, won't know
	
	FILE *fp = fopen("this don't exist", "r");
	printf("errno: %d, ENOENT error no entity\n", errno);
	//after checking with errno: reset to 0
	errno = 0;
	//fread and fwrite can trigger interrupts, and set errno

	//low level file I/O
	//file descriptors, 0 for stdint, 1 stdout, 2 stderror
	//creat, open, close, read, write, ioctl (I/O control), unmask
	//creat is creat, not create
	
	//error will return -1, errno will also be set
	//then save the errno as another int, so that if anything else goes wrong, you'll still have the OG errno
	//man open 2 has all the errors
	
	//sigaction() is a newer version of signal(), to catch signals from sys
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	//sigaction struct holds a bunch of things
	//need to pass it sa_flags = error code to catch

	//Linked Lists: "There will be a heavy emphasis on this in the examination"
}

if (lec_n == 6) {
	printf("loads of stuff on compilation: preprocessor, assembler, linker.\n");
	//compiling: how to we go from source code to a binary executable file
	/* .c and .h goes into preprocessor, outputs assembly .s
	then assembler: assembly plus stuff for linking, outputs .o object
	then linker joins all the library files into usable formats and addresses
	outputs .out, executable binary files
	*/
	//compiler uses all these, but we can trigger them individually
		//preprocessor: gcc -E
		//assembler: gcc -s, gcc -c
		//linker: 

	//assembler makes symbols, and linker does symbol resolution
	//meaning you can use vars declared in separate files when you join them in the linker
	
	//strace ./program
	//traces all calls and processes from running a program

	//static vs dynamic linked executable
	//stuff that is #include vs stuff that is fed into linker together

	//gcc --help gives list of flags incl aforementioned

	//preprocessor lines start with #, it takes and then dumps text
	//this also means that pushing code through preprocessor will not show any errors
	//#define will search for the name and replace it with the value everywhere in the program
	//also means if you #define twenty 10+10, the preprocessor will output that as 10+10
		//means that something like a = 5 * twenty will give 5*10+10
		//so if using define expressions, use brackets

	//define macro
	//ternary operator: (boolean expression) ? output if true: output if false
	//basically use as a mini function
	

	printf("using a macro for min value (300, 4) %d\n", min(300,4));

	printf("macro multiplies %d\n", square(4));

	//quite a few functions are actually macros, can check in the .h or man pages
	//eg isupper(), getc()

	//preprocess conditional exclusion
	//allows us to exclude text if we so desire, good for debugging
	/*
	#ifdef checks if identifier exists. if exists, will include the next text section
		otherwise jumps to the next #ifdef
	#if computes an expression, will include the next text, or go to
	#else
	#elif
	#undef opposite of ifdef, checks if identifier does not exist
	#endif ends the conditional statements
	*/

	/*debug mode example, final version will have a final_version defined:
	#ifdef final_version
	#define LINES 100
	#else
	#define LINES 100000
	*/
	//can also do something like #if WINDOWSIZE > 600 and then actual code

	//for debug prints: can define a macro for printfs. see up.

	DEBUG("compiled with -D flag, input EBUG for define.");	

	//predefined symbols
	//__LINE__ is a symbol that contains the current line being run
	//same for __FILE__, current file being accessed

	//<> or ""
	//<> are system include directories, searches a few computer paths for it
	//"" are user include directories, default loc is pwd
} 

if (lec_n == 7) {//@Gfuz9r4

	printf("\nprocesses: an abstraction of convenience\n");

	/*Stack heap static code*/
	//program binaries are in static and code, stored on disk, static
	/*but theres another section, and all of it encompassed by the process image, which is all things needed
	for executing*/
	//includes the OS, kernel
	//process is basically how a program runs, data, storage, exectuion and all of it
	//OS is designed to run processes without clashes in memory and calculations

	//system memory has 2 spaces: kernel is protected, OS functions and related, only interface to hardware
	//user memory space is everything else, prgram binaries. accesses kernel space through system calls

	//fork
	//clones a user operation, deep copy
	//OS needs to distinguish between them, so it gets a process identifier, which is the only difference
	
	//virtual address space
	//range of user memory that OS allocates to a process. has hard limits, makes it easier to jump around
	//layouts differ between OS, not real differences between them


	//everything in a program starts at main, and we can add char *envp[] to the main params
	//like char *argv[], this is an array of pointers, each pointer points at a string of an environement var
	//eg user, display, path
	//using environment variables, we can check where the process is running from, who is running it
		//screen size, all sorts of external info
	//main, argc and argv are all in the stack
	
	//intiate process with exec() function, various forms specifically too
	//it doesn't create a process, just replaces the current process with target one
	//if exec() is successful, nothing will return, if something does, something went wrong
	//this also means that everything in code after an exec() should never actually be reached
	//execl(), execlp(), execle()
	//getpid() from unistd.h will return the same, as the process id is the same

	/*if you want to jump to a process and then return to the original: fork*/
	//#include <sys/types.h>, <unistd.h>
	//fork clones a process by duplicating the calling one, and will give a new PID
	//including program counter and everything, the state is also duplicatd
	//the processes run in parallel, the only way we can check which is which

	//fork() returns an int: 
	/* 0 means the current process running is the child
	-1 is error
	a number will be the PID of the child, meaning the current running process is the parent
	*/
	//different OS will run parent and child in different orders

	printf("pre-fork PID: %d\n", getpid());
	int cur_process = getpid();//if use this before calling fork() can have process conditional code
	int fork_result = fork();
	if (fork_result > 0 || getpid() == cur_process) {//can use saved PID if using multiple forks
		printf("pausing the parent until end of child w/ wait()\n");
		int status;
		int x = wait(&status);
		if (status == 0) {
			printf("returned 0 from child, running the parent process, PIDs match.\n\n");
		}
	} else if (fork_result == 0) { //return 0 means running child
		printf("running child rn, PID %d\n", getpid());
		printf("returning 0 from child\n");
		return 0;
	}
	//can fork a fork etc, and if the child 
	printf("btw usleep to delay by microsec. can use this to influence the order of running processes\n");
	//sleep is for seconds
	//if using this to disrupt processes, there will be no sychronisation, and stuff will execute random order
	//process runs in parallel, depends on cores in cpu

	//so: link the 2 concepts, first fork(), then execl() the child. 
	//control which runs first/wait while running one
	//can use pid_t wait(int *status) where status is the return of the child process

	//obviously, be super careful when forking in a loop, can really fuck up
	//called a fork bomb, overloads memory and cpu, but fixable by shutdown

	//opendir and readdir to navigate directory paths to find other files
}

if (lec_n == 8) {//from last year
	printf("after midsem: ");
	/*recap: use fork then exec for running new processes.
	also wait(), can control order or process running
	*/
	//signals can be used between processes
	//they can be triggered whenever, but can also be lost if signal arrives while another is processed
	//limited to a single int

	//pipes.
	//files: fopen, fseek, fread, fclose, all used to manage low level files, easy to use
	//pipes are unmanaged, low level I/O, only have an int to control things
	/*low level I/O: creat, open close read write, ioctl*/
	
	/*pipes are for getting data from a process, put into intermediary space, and process 2 fetches it
	use a queue, so process 2 gets in reverse order
	pipes are unidirectional!!! have a write end and a read end
	
	1. ask for pipe
	2. kernel returns a file descriptor for read and another for write: 
	*/

	//array of 2 ints
	int fd[2] = {-1, -1};
	
	int ret = pipe(fd);//pipe param is address of array[2]
	printf("called pipe(), pipes using return vals %d for read, %d for write\n", fd[0], fd[1]);
	//should be 3 and 4, bc 0, 1, 2 are already file descriptors for stdin, stdout and error

	//write to pipe: write(fd[write], string/char*, len + null byte)
	char *msg = "hazek ahi tithazek";
	write(fd[1], msg, (strlen(msg) + 1) );

	//read from pipe
	char buffer[5];
	int read_error = read(fd[0], buffer, 5);
	if (read_error <= 0) {
		perror("couldn't read from pipe\n");
	} else {
		//because we aren't reading the whole string, must make the last char null byte
		buffer[5] = '\0';
		printf("read 5 chars from pipe: %s\n", buffer);
	}

	//the kernel orders the data
	read_error = read(fd[0], buffer, 5);
	if (read_error <= 0) {
		perror("couldn't read from pipe\n");
	} else {
		//because we aren't reading the whole string, must make the last char null byte
		buffer[5] = '\0';
		printf("read 5 more chars from pipe: %s\n", buffer);
	}

	//should ofc
	close(fd[0]);
	close(fd[1]);
	printf("closed the pipes but still the vals %d and %d\n", fd[0], fd[1]);

	/*kernel doesn't have inf space, but more flexible than a signal, and won't have problem of lost signal
	kernel storage is a circular buffer, an array w 2 cursors
	1 for where was last write, 1 for last read*/
	//john thinks of names for a pipe demo file, decides party_pipe sounds bad lol

	/*comms between processes need to know the file descriptors for each pipe read/write, and also ideally 
	can have a pipe to each other
	create 2 pipes
	int pid = fork()
	if (pid != 0) we're in parent
	else we in child
	parent write to pipe
	child has a read(), which is a blocking op: it will just wait for data in pipe
		so that parent will continue running
	note that when running parent, can close child write and parent read pipe ends, viceversa in child
	*/

	//when creating a pipe, make sure the pipe exists before forking if you want parent to access
	//esp if a child forks again, grandparent won't be able to use the child-gchild pipe

	//select() - monitors file descriptors for events
	//read, write are synchronous, they are blocking
	//needs a set of target file descriptors
	//SELECT WILL NOT WAIT THE FULL DELAY IF IT CATCHES AN EVENT, WILL TRIGGER IMMEDIATELY

	//init set of file descriptors, type fd_set: just a bunch of bits where index = fdnum
	fd_set allfds;

	//resets the entire set/
	FD_ZERO(&allfds);

	//adds the 1st param fd to the set
	FD_SET(0, &allfds);
	FD_SET(2, &allfds);

	//rm an fd from fd_set type
	FD_CLR(2, &allfds);

	//max_fd should be set to the largest fd in the fd_set + 1
	int max_fd = 0 + 1;
	
	//timeval struct, contains 2 long type fields for second and microsec
	struct timeval timeout;
	
	//set time fields
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;

	//select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
	int select_return = select(max_fd, &allfds, NULL, NULL, &timeout);

	if (select_return == -1) {
		fprintf(stderr, "select() errored.\n");
	} else if (select_return == 0) {//0 == no event
		printf("select() waited 2s, found no input for stdin.\n");
	} else {//returns the number of fds that had events
		printf("select() caught fd event before timeout.\n");
		int is_changed = FD_ISSET(0, &allfds);
		printf("event was on fd: %d\n", is_changed);
		//could put all lines from setting timeouts into a while(1) read, strcmp
	}

	if (1)
		;//valid code btw

	//similarly
	msg = "printf is for bitches\n";
	write(1, msg, strlen(msg)+1 );
} else if (lec_n == 9) {

	
}
	
	return 0;
}
