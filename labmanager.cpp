/*********************************************************************
  CISC 2000   Fordham University   Fall 2019
  Instructor: Vincent Mierlak

  HW 5.  Computer Lab Logging Program.
  
  This program uses dynamic arrays to store login information for
  four computer labs.  Each of the four labs is referenced by the labs[] array
  which is indexed from 0-3.  Each element of the labs[] arrays is a
  pointer to a dynamic array whose size is the number of computers in that
  lab.

  Written by: Peter Hughes 
  Last modified on: 10/5/19
  Known bugs: none
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Type definition for an int * pointer
typedef int* IntPtr;

// Global constant
constexpr int NUMLABS = 4;

// Function prototypes

/*
 Creates the dynamic arrays for the labs.
 @param labs: the array of labs,
 @param labsizes: contains the size (or number of computers) of each lab
  This dictates the size of the dynamic array.
 @precondition: labsize[0] is the # of computers in lab1,
                labsize[1] is the # of computers in lab2, ...
 @postcondition: labs[0] points to lab1's array (of size given by labsize[0])
      labs[1] points to lab2's array (of size given by labsize[1])
        ...
*/
void create_arrays(IntPtr labs[], int labsizes[]);


/* 
 Releases the memory we allocated with "new".
*/
void free_arrays(IntPtr labs[]);


/*
 Displays the status of all labs (who is logged into which computer).
*/
void show_labs(IntPtr labs[], int labsizes[]);


// ======================
// login:
// Simulates a user login by asking for the login info from
// the console.
// ======================
void login(IntPtr labs[], int labsizes[]);


// ======================
// logoff:
// Searches through the arrays for the input user ID and if found
// logs that user out.
// ======================
void logoff(IntPtr labs[], int labsizes[]);


// ======================
// search:
// Searches through the arrays for the input user ID and if found
// outputs the station number.
// ======================
void search(IntPtr labs[], int labsizes[]);



int main()
{
    IntPtr labs[NUMLABS]; 	// store the pointers to the dynamic array for each lab
    int labsizes[NUMLABS];	// Number of computers in each lab
    int choice = -1;

    cout <<"Welcome to the LabMonitorProgram!\n";

    // Prompt the user to enter labsizes 
    cout <<"Please enter the number of computer stations in each lab:\n"; 
    for (int i=0; i< NUMLABS; i++)
    {
        do
        {
            cout <<"How many computers in Lab "<< i+1<<"? ";
            cin >> labsizes[i]; 
        } while (labsizes[i]<0); 
    }

    // Create ragged array structure
    create_arrays(labs, labsizes);

    // Main Menu
    while (choice != 0)
    {
        cout << endl;
        show_labs(labs, labsizes);
        cout << "MAIN MENU" << endl;
        cout << "0) Quit" << endl;
        cout << "1) Simulate login" << endl;
        cout << "2) Simulate logoff" << endl;
        cout << "3) Search" << endl;
        cin >> choice;
        if (choice == 1)
        {
            login(labs, labsizes);
        }
        else if (choice == 2)
        {
            logoff(labs, labsizes);
        }
        else if (choice == 3)
        {
            search(labs, labsizes);
        }
    }

    free_arrays(labs);		// Free memory before exiting
    return 0;
}


void create_arrays(IntPtr labs[], int labsizes[])
{
  //TODO: My function initiates pointers for each index of the labs array and
  // assigns them to a new array the size of however many computers are in the
  // lab. The function then goes through each of the four arrays, assigning 
  // every value to -1 so that each of the computers appear as empty.
  // Hint: for each of the 4 labs, dynamically
  // allocate an int array of size given by the number of computers in the lab. 
  // Initialize each element in the array to -1 (meaning an unused computer).
  // Store the array in labs.
    
   for (int i = 0; i < 4; i++)
   {
       labs[i] = new int[labsizes[i]];
       
       for (int j = 0; j < labsizes[i]; j++)
       {
           labs[i][j] = -1;
       }
   }


}

/* TODO: This function frees the dynamic memory allocated when each of the 
 * labs[] array indexes were assigned to point to their own seperate array.
 * These commands use the keyword delete followed by bracket operators and the
 * name of each array in order to open the memory. 
 */
void free_arrays(IntPtr labs[])
{
  //TODO BY STUDENT
    
    delete [] labs[0];
    delete [] labs[1];
    delete [] labs[2];
    delete [] labs[3];

}


void show_labs(IntPtr labs[], int labsizes[])
{

    int i;
    int j;

    cout << "LAB STATUS" << endl;
    cout << "Lab #   Computer Stations" << endl;
    for (i=0; i < NUMLABS; i++)
    {
        cout << i+1 << "       ";
        for (j=0; j < labsizes[i]; j++)
        {
            cout << (j+1) << ": ";
            if (labs[i][j] == -1)
            {
                cout << "empty ";
            }
            else
            {
                cout << setfill('0') << setw(4) << labs[i][j] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
    return;
}


void login(IntPtr labs[], int labsizes[])
{
    int id, lab, num = -1;

    // read user id 
    do
    {
        cout << "Enter the 4 digit ID number of the user logging in:" << endl;
        cin >> id;
    } while ((id < 0) || (id > 9999));

    // read the lab number 
    do 
    {
        cout << "Enter the lab number the user is logging in from (1-" <<
            NUMLABS << "):" << endl;
        cin >> lab;
    } while ((lab < 0) || (lab > NUMLABS));

    //read computer number 
    do
    {
        cout << "Enter computer station number the user is logging in to " <<
            "(1-" << labsizes[lab-1] << "):" << endl;
        cin >> num;
    } while ((num < 0) || (num > labsizes[lab-1]));

    // Check to see if this station is free
    if (labs[lab-1][num-1]!=-1)
    {
        cout << "ERROR, user " << labs[lab-1][num-1] <<
            " is already logged into that station." << endl;
        return;
    }
    // Assign this station to the user
    labs[lab-1][num-1] = id;
    return;
}


void logoff(IntPtr labs[], int labsizes[])
{
    int id, i,j;

    // Get input from the keyboard, validating data ranges
    do
    {
        cout << "Enter the 4 digit ID number of the user to find:" << endl;
        cin >> id;
    } while ((id < 0) || (id > 9999));


    for (i=0; i<NUMLABS; i++) // check for each lab 
    {
        for (j=0; j<labsizes[i]; j++) //if the user is using any computer in the lab
        {
            if (labs[i][j]==id) //if so, log the user off... 
            {
                // Log the user off by setting the entry to -1
                labs[i][j] = -1;
                cout << "User " << id << " is logged off." << endl;
                return;
            }
        }
    }
    cout << "That user is not logged in." << endl;
    return;
}

/*  TODO: The search function asks the user for the ID number of the user they
 *  would like to locate. It then searches each of the four stations for a
 *  matching ID by testing the equality between each of the ID values in the
 *  labs[] array and the user input ID. If the ID is found, the function 
 *  returns the station number and computer number where the matching value 
 *  was found.
 */
void search(IntPtr labs[], int labsizes[])
{
  //TODO BY STUDENT
 
    int entry_id;
    cout << "Enter the four digit ID of the user to find: ";
    cin >> entry_id;
    cout << endl;
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < labsizes[i]; j++)
        {
            if (*(labs[i]+j) == entry_id)
            {
                cout << "User " << entry_id << " is at Lab " << i+1;
                cout << " Computer " << j+1 << endl;
            }
        }
    }
}

