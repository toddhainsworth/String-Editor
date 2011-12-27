/* Basic String Editor written in C, hacks by Geisst
 * Original Source: Page 463, "Program Design and Problem Solving in C"
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN    100
#define NOT_FOUND -1

char *delete(char *source, int index, int n);
char *do_edit(char *source, char command);
char get_command(void);
char *insert(char *source, const char *to_insert, int index);
int  pos(const char *source, const char *to_find);

int main(void)
{
	char source[MAX_LEN], command;
	printf("Enter the source string: \n");
	gets(source);

	for (command = get_command(); command != 'Q'; command = get_command()) {
		do_edit(source, command);
		printf("New source: %s\n\n", source);
	}

	printf("String after editing: %s\n", source);
	return(0);
}

/* Delete function
 * ---------------
 * Delete's parts of the entered string
 */
char *delete(char *source, int index, int n)
{
	char rest_str[MAX_LEN]; // The rest of the string

	// No characters after the deleted portion? Delete ALL!

	if(strlen(source) <= index + n) {
		source[index] = '\0';
	} else {
		strcpy(rest_str, &source[index + n]);
		strcpy(&source[index], rest_str);
	}
	return(source);
}

/* Edit Function
 * -------------
 * Edits the string with what ever modification the user wishes
 */

char *do_edit(char *source, char command)
{
	char str[MAX_LEN]; // String that the editor will work with
	int index;

	switch(command) {
	case 'D':
		printf("String to delete: \n");
		gets(str);
		index = pos(source, str);
		if(index == NOT_FOUND)
			printf("'%s' not found!\n", str);
		else
			delete(source, index, strlen(str));
		break;
	case 'I':
		printf("String to insert: \n");
		gets(str);
		printf("Position of insertion: \n");
		scanf("%d", &index);
		insert(source, str, index);
		break;
	case 'F':
		printf("String to find: \n");
		gets(str);
		index = pos(source, str);
		if(index == NOT_FOUND)
			printf("'%s' not found\n", str);
		else
			printf("'%s' found at position: %d\n", str, index);
		break;
	default:
		printf("Invalid command: '%c'\n", command);
	}
	return(source);
}

/* Command Listener
 * ----------------
 * Listens for commands and interprets them
 */
char get_command(void)
{
	char command, ignore;

	printf("Enter (D)elete, (I)nsert, (F)ind or (Q)uit: ");
	scanf(" %c", &command);

	do
		ignore = getchar();
	while(ignore != '\n');

	return(toupper(command));
}

/* Insert Function
 * ---------------
 * Inserts text into the string
 */
char *insert(char *source, const char *to_insert, int index)
{
	char rest_str[MAX_LEN]; // Rest of the string

	if(strlen(source) <= index) {
		strcat(source, to_insert);
	} else {
		strcpy(rest_str, &source[index]);
		strcpy(&source[index], to_insert);
		strcat(source, rest_str);
	}
	return(source);
}

/* Position function
 * -----------------
 * Returns index of first occurance of to_find in source or
 * value of NOT_FOUND if to_find is not in source.
 */
int pos(const char *source, const char *to_find)
{
	int i = 0, find_len, found = 0, position;
	char substring[MAX_LEN];

	find_len = strlen(to_find);

	while(!found && i <= strlen(source) - find_len) {
		strncpy(substring, &source[i], find_len);
		substring[find_len] = '\0';

		if(strcmp(substring, to_find) == 0)
			found = 1;
		else
			++i;
	}

	if(found)
		position = i;
	else
		position = NOT_FOUND;

	return(position);
}
