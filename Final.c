#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CLEAN_BUFFER fseek(stdin, 0, SEEK_END)
//אופק שמש 313559601
//ברק ליבוביץ 314772682

int num_added = 0;  //Global integer that count how many people inserted to database.

typedef struct {      //Date of birth struct.
	int year;
	char month;
	char day;
}DateOfBirth;

typedef struct {      //Person struct.
	double id;
	char* name;
	char* family;
	DateOfBirth birthday;
	double partnerid;
	double motherid;
	double fatherid;
	char numofchildren;
	double* childrenptr;
}person;

typedef struct {    //Main database struct. "Manager"
	person* ptr;
	int num_of_people;
}db_mgr;

typedef struct {  // Get_gen "HELPER" struct
	double* gen_id;
	int howmany;
}gen_helper;

void allocation_check(void* ptr_allocated)  //Recieving a pointer to a dynamically allocated memory and making sure allocation succeeded.
{
	if (ptr_allocated == NULL)
	{
		printf("Memory allocation failed..\nEnding program...");
		exit(0);
	}
}

int db_init(db_mgr* db_mgr)    // Defining dynamic array of people in our town and updates the main database struct "Manager".
{
	if (db_mgr->num_of_people > 0)
	{
		person* civilians = (person*)malloc(db_mgr->num_of_people * sizeof(person));
		allocation_check(&civilians);
		db_mgr->ptr = civilians;
		return 1;
	}
	else return 0;
}

int menu() { // Main menu function. Returning the user's choice from the menu.
	int userchoice;
	for (;;)
	{
		printf("Database System Menu:\n\n1.Add Person\n2.Search a person\n3.Search parents\n4.Delete a person\n5.Get generation\n6.Print Database\n7.Search by name\n8.Quit\nEnter a number: ");
		scanf(" %d", &userchoice);
		if (userchoice > 8 || userchoice <= 0)
		{
			printf("Error! Please Enter Number between 1 - 8.\n");
		}
		else
			printf("\n\n");
		return userchoice; 
	}

}

void* norealloc (void* oldarr, const int newsize, const int oldsize)  // Set new array in appropiate size. Copy the old one and release it from the memory
{
	void* newarr = malloc(newsize);
	allocation_check(&newarr);
	memcpy(newarr, oldarr, oldsize);
	free(oldarr);
	return newarr;
}

void print_person(const person* printer) // Print specific person's data from database
{
	printf("This person's details are as follows:\n");
	printf("ID: %.lf\n", printer->id);
	printf("First name: %s\n", printer->name);
	printf("Last name: %s\n", printer->family);
	printf("Date of birth: %d/%d/%d\n", printer->birthday.day, printer->birthday.month, printer->birthday.year);
	if (printer->partnerid != 0)
		printf("ID of partner: %.lf\n", printer->partnerid);
	if (printer->motherid != 0)
		printf("ID of mother: %.lf\n", printer->motherid);
	if (printer->fatherid != 0)
		printf("ID of father: %.lf\n", printer->fatherid);
	if (printer->numofchildren != 0)
		for (int i = 0; i < printer->numofchildren; i++)
			printf("ID for child #%d is: %.lf\n", i + 1, printer->childrenptr[i]);
	printf("\n\n");
}

void add_person(db_mgr* add)  // Function to collect all the person data and insert his data to the main database. 
{
	if (num_added == add->num_of_people)
	{
		add->ptr = norealloc(add->ptr, ((num_added + 1) * sizeof(person)), num_added * sizeof(person));
		add->num_of_people++;
	}
	person* temp = add->ptr + num_added;
	char tempname[256];
	printf("Please enter person ID number:\n");
	scanf("%lf", &temp->id);
	CLEAN_BUFFER;
	while (temp->id < 0)
	{
		printf("Invalid ID, try again:\n");
		scanf("%lf", &temp->id);
		CLEAN_BUFFER;
	}
	printf("Please enter person First Name:\n");
	scanf("%s", &tempname);
	CLEAN_BUFFER;
	temp->name = (char*)malloc((strlen(tempname) + 1) * sizeof(char));
	allocation_check(temp->name);
	strcpy(temp->name, tempname);
	printf("Please enter person Last Name:\n");
	scanf("%s", &tempname);
	CLEAN_BUFFER;
	temp->family = (char*)malloc((strlen(tempname) + 1) * sizeof(char));
	allocation_check(temp->family);
	strcpy(temp->family, tempname);
	printf("Please enter person Year of Birth:\n");
	scanf("%d", &temp->birthday.year);
	CLEAN_BUFFER;
	while (temp->birthday.year > 2021 || temp->birthday.year <= 0)
	{
		printf("Error! Please enter a valid year:\n");
		scanf("%d", &temp->birthday.year);
		CLEAN_BUFFER;
	}
	printf("Please enter person Month of Birth:\n");
	scanf("%d", (int*)&temp->birthday.month);
	CLEAN_BUFFER;
	while (temp->birthday.month > 12 || temp->birthday.month <= 0)
	{
		printf("Error! Please enter a valid month:\n");
		scanf("%d", (int*)&temp->birthday.month);
		CLEAN_BUFFER;
	}
	printf("Please enter person Day of Birth:\n");
	scanf("%d", (int*)&temp->birthday.day);
	CLEAN_BUFFER;
	while (temp->birthday.day > 30 || temp->birthday.day <= 0)
	{
		printf("Error! Please enter a valid day:\n");
		scanf("%d", (int*)&temp->birthday.day);
		CLEAN_BUFFER;
	}
	char choice; //בדיקת כן/לא
	printf("Does the person have a partner?(y/n):\n");
	scanf("%c", &choice);
	CLEAN_BUFFER;
	while (choice != 'y'  && choice != 'Y'  && choice != 'n'  && choice != 'N')
	{
		printf("Please answer the question with Y/N:\n");
		scanf("%c", &choice);
		CLEAN_BUFFER;
	}
	if (choice == 'y' || choice == 'Y')
	{
		printf("Please enter person's partner's ID number:\n");
		scanf("%lf", &temp->partnerid);
		CLEAN_BUFFER;
		while (temp->partnerid <= 0)
		{
			printf("Error! invalid ID number inserted. Please try again:\n");
			scanf("%lf", &temp->partnerid);
			CLEAN_BUFFER;
		}
	}
	else
		temp->partnerid = 0;

	printf("Does the person have a mother?(y/n):\n");
	scanf("%c", &choice);
	CLEAN_BUFFER;
	while (choice != 'y'  && choice != 'Y'  && choice != 'n'  && choice != 'N')
	{
		printf("Please answer the question with Y/N:\n");
		scanf("%c", &choice);
		CLEAN_BUFFER;
	}
	if (choice == 'y' || choice == 'Y')
	{
		printf("Please enter person's mother's ID number:\n");
		scanf("%lf", &temp->motherid);
		CLEAN_BUFFER;
		while (temp->motherid < 0)
		{
			printf("Error! invalid ID number inserted. Please try again:\n");
			scanf("%lf", &temp->motherid);
			CLEAN_BUFFER;
		}
	}
	else
		temp->motherid = 0;

	printf("Does the person have a father?(y/n):\n");
	scanf("%c", &choice);
	CLEAN_BUFFER;
	while (choice != 'y'  && choice != 'Y'  && choice != 'n'  && choice != 'N')
	{
		printf("Please answer the question with Y/N:\n");
		scanf("%c", &choice);
		CLEAN_BUFFER;
	}
	if (choice == 'y' || choice == 'Y')
	{
		printf("Please enter person's father's ID number:\n");
		scanf("%lf", &temp->fatherid);
		CLEAN_BUFFER;
		while (temp->fatherid <= 0)
		{
			printf("Error! invalid ID number inserted. Please try again:\n");
			scanf("%lf", &temp->fatherid);
			CLEAN_BUFFER;
		}
	}
	else
		temp->fatherid = 0;

	printf("Please enter person's Number of Children:\n");
	scanf("%d", (int*)&temp->numofchildren);
	CLEAN_BUFFER;
	while (temp->numofchildren < 0)
	{
		printf("Error! invalid number inserted. please try again.\n");
		CLEAN_BUFFER;
		scanf("%d", (int*)&temp->numofchildren);
	}
	if (temp->numofchildren > 0)
	{
		temp->childrenptr = (double*)malloc(temp->numofchildren * sizeof(double));
		allocation_check(temp->childrenptr);
		for (int i = 0; i < temp->numofchildren; i++)
		{
			printf("Enter ID for child #%d: ", i + 1);
			scanf("%lf", temp->childrenptr + i);
			CLEAN_BUFFER;
		}
	}
	person* compare = add->ptr;
	for (int i = 0; i < num_added; i++)   // Sorting array by ID numbers.
	{
		if (compare[i].id > temp->id)
		{
			person holder;
			holder = *temp;
			for (int q = num_added; q >= i; q--)
				compare[q] = compare[q - 1];
			compare[i] = holder;
			break;
		}
	}
	num_added++;
	printf("\n\n");
}

person* search_id(db_mgr* manager, const double idsearched) //Searching the ID in the database and returning a pointer to that person or NULL if not found.
{
	person* search = manager->ptr;
	for (int i = 0; i < num_added; i++)
	{
		if (idsearched == search[i].id)
			return &search[i];
	}
	return NULL;
}

person* find_person(db_mgr* mgr)  //Getting an ID from the user and returning a pointer to him using search_id.
{
	double idsearched; // ID to search
	printf("Please enter the ID of the required person:\n");
	scanf(" %lf", &idsearched);
	person* person_to_print = search_id(mgr, idsearched);
	return person_to_print; //Pointer to the person in the database.
}

void search_person(db_mgr* mgr) //Searching and printing all details about a person in the database from his ID.
{
	person* person_to_print = find_person(mgr); //Using helper function.
	if (person_to_print == NULL)
		printf("Person not found\n\n");
	else
		print_person(person_to_print);
}

void search_parents(db_mgr* mgr)  //Printing details of a person's parents from his ID.
{
	person* person_to_print = find_person(mgr); //Calling helper function to find the person in the database.
	if (person_to_print == NULL)
		printf("Person not found\n\n");
	else
	{
		if (person_to_print->motherid == 0)
			printf("This person doesn't have a mother in the database\n");
		else
			printf("This person's mother's ID is: %.lf\n", person_to_print->motherid);
		if (person_to_print->fatherid == 0)
			printf("This person doesn't have a father in the database\n");
		else
			printf("This person's father's ID is: %.lf\n", person_to_print->fatherid);
	}
}

void print_db(db_mgr* mgr) // Function to print all the database.
{
	person* printer = mgr->ptr;
	for (int i = 0; i < num_added; i++)
	{
		printf("Person #%d data is:\n", i + 1);
		print_person(printer + i);
	}
}

void search_by_name(db_mgr* mgr)  //Search by name function. Printing database of people that have the searched name.
{
	char firstname[256], lastname[256];
	char found = 0;
	person* tourist = mgr->ptr;
	printf("Please enter First name of the person you want to search:\n");
	scanf(" %s", firstname);
	printf("Please enter Last name of the person you want to search:\n");
	scanf(" %s", lastname);
	printf("\nloading...\n\n");
	for (int i = 0; i < num_added; i++)
	{
		if (strcmp(tourist[i].name,firstname) == 0)
			if (strcmp(tourist[i].family, lastname) == 0)
			{
				print_person(tourist + i);
				found++;
			}
	}
	if (found == 0)
		printf("No match has been found\n\n");
}

void erase_child(person* erase, int i) //Delete child and set new array size.
{
	for (; i < erase->numofchildren - 1; i++)
		erase->childrenptr[i] = erase->childrenptr[i + 1];
	erase->numofchildren--;
	erase->childrenptr = norealloc(erase->childrenptr, erase->numofchildren * sizeof(double), erase->numofchildren * sizeof(double));
}

void delete_person(db_mgr* mgr)  // Delete a person and all his data from the database.
{
	person* deleted = find_person(mgr);
	if (deleted != NULL)
	{
		person* eraser;
		if (deleted->numofchildren > 0)
			for (int i = 0; i < deleted->numofchildren; i++)  //Delete "Father" section.
			{
				eraser = search_id(mgr, (deleted->childrenptr[i]));
				if (eraser == NULL)
					break;
				if (deleted->id == eraser->fatherid)
					eraser->fatherid = 0;
				else
					eraser->motherid = 0;
			}
		if (deleted->partnerid != 0)  // Delete "Partner" section.
		{
			do {
				eraser = search_id(mgr, deleted->partnerid);
				if (eraser == NULL)
					break;
				eraser->partnerid = 0;
				break;
			} while (1);
		}
		if (deleted->motherid != 0)  // Delete child from mother's child array.
		{
			eraser = search_id(mgr, deleted->motherid);
			do {
				if (eraser == NULL)
					break;
				for (int i = 0; i < eraser->numofchildren; i++)
					if (deleted->id == eraser->childrenptr[i])
					{
						erase_child(eraser, i);
						break;
					}
				break;
			} while (1);
		}
		if (deleted->fatherid != 0)  // Delete child from father's child array.
		{
			eraser = search_id(mgr, deleted->fatherid);
			do {
				if (eraser == NULL)
					break;
				for (int i = 0; i < eraser->numofchildren; i++)
					if (deleted->id == eraser->childrenptr[i])
					{
						erase_child(eraser, i);
						break;
					}
				break;
			} while (1);
		}
		for (int i = 0; i < num_added - 1; i++)  //Creating new array of people after deleting the person.
			deleted[i] = deleted[i + 1];
		if (num_added == mgr->num_of_people)
		{
			mgr->num_of_people--;
			mgr->ptr = norealloc(mgr->ptr, mgr->num_of_people * sizeof(person), mgr->num_of_people * sizeof(person));
		}
		else
			mgr->ptr = norealloc(mgr->ptr, mgr->num_of_people * sizeof(person), (num_added - 1) * sizeof(person));
		num_added--;
		printf("The selected person has been deleted from the database\n");
	}
	else
		printf("No match found\n");
}

void get_gen(db_mgr* mgr)  // Count the generation of specific person based on the database.
{
	person* current = find_person(mgr);
	if (current != NULL)
	{
		gen_helper* generation = (gen_helper*)malloc(sizeof(gen_helper));
		allocation_check(&generation);
		generation->gen_id = (double*)malloc(1 * sizeof(double));
		allocation_check(&generation->gen_id);
		generation[0].gen_id[0] = current->id;
		generation[0].howmany = 1;
		int gen_num = 1;
		for (int i = 0; i < gen_num; i++)  //creating a dynamic array that contains the id's of each generation.
		{
			generation = (gen_helper*)realloc(generation, (gen_num + 1) * sizeof(gen_helper));
			allocation_check(&generation);
			generation[i + 1].howmany = 0;
			generation[i + 1].gen_id = (double*)malloc(sizeof(double));
			allocation_check(&generation[i + 1].gen_id);
			for (int q = 0; q < generation[i].howmany; q++)
			{
				current = search_id(mgr, generation[i].gen_id[q]);
				if (current == NULL)
					continue;
				if (current->numofchildren > 0)
				{
					generation[i + 1].gen_id = (double*)realloc(generation[i + 1].gen_id, generation[i].howmany * sizeof(double) + current[i + 1].numofchildren * sizeof(double));
					allocation_check(&generation[i + 1].gen_id);
					generation[i + 1].howmany += current->numofchildren;
					for (int r = 0; r < current->numofchildren; r++)
					{
						if (current->childrenptr[r] > 0)
							generation[i + 1].gen_id[r] = current->childrenptr[r];
					}
				}
			}
			if (generation[i + 1].howmany > 0)
				gen_num++;
		}
		for (int i = 0; generation[i].howmany != 0; i++)
			free(generation[i].gen_id);
		free(generation);
		printf("This person has %d generations\n\n", gen_num); //printing the number of generations.
	}
	else printf("No match found\n\n");
}

void quit(db_mgr* mgr) // Funtion to end the program and release the memory.
{
	printf("Ending program...\n\n");
	for (int i = 0; i < num_added; i++)
	{
		free(mgr->ptr[i].name);
		free(mgr->ptr[i].family);
		if (mgr->ptr[i].numofchildren != 0)
			free(mgr->ptr[i].childrenptr);
	}
	free(mgr->ptr);
}

int main()
{
	db_mgr town;
	for (;;)
	{
		printf("Enter the number of people in your town: ");
		scanf(" %d", &town.num_of_people);
		if (db_init(&town) != 0)
			break;
		printf("Number must be higher than 0\n\n");
	}
	printf("\n\n");
	for (;;)
	{
		int userchoice = menu();
		switch (userchoice)
		{
		case 1: {
			add_person(&town); //Add a person to the database.
			break;
		}
		case 2: {
			search_person(&town); //Searching and printing a person's details by his ID.
			break;
		}
		case 3: {
			search_parents(&town); //Print information about a person's parents by his ID.
			break;
		}
		case 4: {
			delete_person(&town); //Delete a person and his references from the database.
			break;
		}
		case 5: {
			get_gen(&town); //Finding the number of generations a person has.
			break;
		}
		case 6: {
			print_db(&town); //Print the entire database.
			break;
		}
		case 7: {
			search_by_name(&town); //Search and print the details of all the people with a certain name.
			break;
		}
		case 8: {
			quit(&town); //Release the dynamic memory and end the program.
			return 0;
		}
		}
	}
}