 /*

 Name: Preeti Singh

 ID:1002013566

 */



#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <stdlib.h>



//Creating macro for storing lists of 15 commands entered by user.

#define SIZE 15

//Initializing the variables with values.

int currentPointer = -1,ind=0;

//Defining a character pointer with size defined above.

char *commHis[SIZE];

//Defining cd method.

int cd(char **param);



//Function to change-directory(cd)

int cd(char **param)

{

	 if(chdir(param[1]) < 0)

	 {	   //Printing an error message to stderr

		   perror(param[1]);

	 }



	 printf("Changing directory to %s\n", param[1]);

	 return 1;

}



//Function to analyze the input string entered by the user and execute them.

int result(char *input)

{

	 //Initializing the variables that will store values.

     int i,stat,previousPointer = 0, pointer = currentPointer,l;

     char *delimeter = " ";

     char *str;

     int j = 0;

     char **com = malloc(64 * sizeof(char*));



     //Breaking the input string using the delimeter defined above.

     str = strtok(input, delimeter);



     //Saving the above tokens into another char variable until NULL.

     while (str != NULL)

     {

    	com[j] = str;

        j++;

        str = strtok(NULL, delimeter);

     }



     com[j] = NULL;



     //Checking if the command entered by user is NULL.

     if(com[0] == NULL)

     {

        return 1;

     }



     char **newvar = com;



     // Checking if the user entered command "history". The below code will execute only when the user enters the command "history"

     if(strcmp(com[0], "history") == 0)

     {

        //Checking if the currentpointer has not reached the size of 15 defined above, add 1 and save it to the previouspointer

    	if(currentPointer != SIZE && commHis[currentPointer + 1] != NULL)

    	{

    		previousPointer = currentPointer + 1;

    	}

    	// Getting the count of number of commands entered by user

    	ind = (currentPointer - previousPointer + SIZE) % SIZE + 1;



    	//Checking if the command is present in the history of commands.

    	if(currentPointer == -1 || commHis[currentPointer] == NULL)

    	{

    		printf("Command not in history.\n");

    		exit(1);

    	}



    	printf("User entered %d commands:\n",ind);

    	printf("*******Listing last %d Commands entered by user:******\n",ind);



    	//Looping through the number of commands the user has entered and printing it.

    	for (l=0;l<ind;l++)

    	{

    		printf("%d: %s\n", l+1,commHis[l]);

    	}



    	return 0;

     }



     currentPointer = (currentPointer + 1) % SIZE;

     // Allocating the memory dynamically

     commHis[currentPointer] = malloc(64 * sizeof(char));



     //While loop to append, until the new variable is not NULL

     while(*newvar != NULL)

     {  //Using strcat method to append

        strcat(commHis[currentPointer], *newvar);

        strcat(commHis[currentPointer], " ");

        newvar++;

     }



     //Checking if the user entered command "EXIT/QUIT". The below code will execute only when the user enters the command "EXIT/QUIT"

     if((strcmp(com[0], "exit") == 0) || (strcmp(com[0], "quit") == 0))

     {

         printf("You entered <EXIT/QUIT> command, Exited successfully with status %d\n", 0);

         exit(0);



     }



     //Checking if the user entered command "cd". The below code will execute only when the user enters the command "cd"

     if(strcmp(com[0], "cd") == 0)

     {   // This will run and execute the cd method defined.

         return cd(com);

     }



     //Defining datatype to represent PID

     pid_t childPid;



     // Forking the PID

     childPid = fork();



     //Checking if the user entered command "pidhistory". The below if code will execute only when the user enters the command "pidhistory"

     if((strcmp(com[0], "pidhistory") == 0))

     {

     	 printf("PidHistory:\n");

         printf("%d\n%d\n",getpid(),childPid);

         exit(0);

     }



     //Checking if the PID value after fork is less than 0.

     if(childPid<0)

     {

    	 printf("Fork Didn't happen");

         exit(1);

     }

     //Checking if the PID value is 0. That means the forking is a success.

     if (childPid == 0)

     {

         //Calling execvp method of exec family of functions. This replaces the current process with a new process.

    	 if (execvp(com[0], com) < 0)

    	 {

    		printf("%s: Command not found.\n",com[0]);

            exit(1);

         }



      }

      else

      {   // Parent process waiting for the child process to exit.

    	  waitpid(childPid, &stat, 0);



      }



      return 1;

}



//Function to read input from the user.

char *readfromstdin()

{

	 //Initializing the variables that will store the values.

     int k = 0;

     char *temp= NULL;

     // Allocating the memory dynamically

     char *mem = malloc(sizeof(char) * 64);



     //While loop to take input from the user.

     while(1)

     {  //Taking the input from the user using getchar method and saving it into a char variable.

    	char in = getchar();

    	// Checking if the character entered by user is an Enter. If user enters, it will add '\0'.

        if(in == '\n')

        {   //Adding the last character as '\0'.

            mem[k] = '\0';

           return mem;

        }

        else

        {   //This will keep on adding the characters into the mem variable.

            mem[k] = in;

        }

        k++;



     }

}



//Main function that will prompt user with msh>, take input and execute them.

int main()

{

	 //While loop to take inputs from the user,prompt them with msh>, parse them and execute.

	 while(1)

	 {   //Prompting user with msh> to accept input.

		printf("msh>");

		//Calling readfromstdin method and saving it into the pointer to a char variable.

	    char* input = readfromstdin();

	    //Calling result method, passing the output from the previous method(readfromstdin) as a parameter and saving it into an integer variable.

	    int parse = result(input);

	 }

    exit(0);

}

