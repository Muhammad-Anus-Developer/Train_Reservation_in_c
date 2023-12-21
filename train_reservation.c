/********** LIBRARIES AND MACROS **********/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define SIZE 50 // Size for various arrays of characters
#define QTY 30 // Number of trains in the database

#define PASS_STR(arg)   #arg
// Modify these two macros' arguments for user's USERNAME and PASSWORD
#define GET_UNAME PASS_STR(user)
#define GET_PWORD PASS_STR(user123)

// These macros are ASCII values for specific escape characters
#define ENTER 13
#define TAB 9
#define BKSP 8

/********** GLOBAL VARIABLES **********/

typedef struct train {
    int num;
    char trName[SIZE];
    int orig, dest;
    int date[2];    // DD/MM
    int time[2];    // HH:MM
} train;

typedef struct user {
    char uName[SIZE], pass[SIZE];
    char psgName[SIZE];
    int class, numPsg, seat[2]; // seat[0]: Car, seat[1]: Seat
    int cost;
    train usrTrn;
} user;

user usr;           // User's database declaration
train trn[QTY];    // Trains' database declaration

time_t timer;       // Storing calendar time in seconds since epoch
struct tm tm;       // Storing clock time and calendar date data

/********** MODULAR FUNCTIONS DECLARATION **********/

void getData(user*, train*);        // Database. Defines/stores value for user's and trains' data
void dateAssign(int*, int, int);    // Parameter: (dateArray, day, month). dateArray uses pointer for passing value

void login(user*);
void printMap();
void inputLoc(user*);

void trListInput(user*, train*);    // Prints train catalog and asks for user's train input
void printTrain(train*);
void inputTrain(user*, train*, int);
void inputPsg(user*);

int confirm(user*);
void calcCost(user*);
void receipt(user*);
void fileReceipt(user*);

int reset();
int inputRange(int, int);   // For limiting inputs. Parameter: (lower bound, upper bound)
void screenHold();

/********** MAIN FUNCTION **********/

int main() {
    getData(&usr, &trn);
    
    do {
        login(&usr);

        do {
            printMap();
            inputLoc(&usr);
            
            trListInput(&usr, &trn);
            inputPsg(&usr);

        } while(confirm(&usr) == 0);
        
        calcCost(&usr);
        receipt(&usr);

    } while(reset() == 1);

    system("cls");
    printf("Thank You.");
    printf("\n\n- Group 2 | Dasar Komputer-03");
    printf("\n\n\nPress any key to end. ");
    getch();

    return 0;
}

/********** MODULAR FUNCTIONS DEFINITION **********/

void getData(user* pUsr, train* pTrn) { 
    /* User's Username and Password Login Data */
    strcpy(pUsr->uName, GET_UNAME);
    strcpy(pUsr->pass, GET_PWORD);


    /* Current Time and Date Data */
    timer = time(NULL);
    tm = *localtime(&timer);
    int day = tm.tm_mday, mon = tm.tm_mon + 1;


    /* Trains Data */
    int i = 0;

    /* Train 1 */
    strcpy((pTrn + i)->trName, "Green Line Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 2;
    dateAssign((pTrn + i)->date, day + 1, mon);
    (pTrn + i)->time[0] = 10, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 2 */
    strcpy((pTrn + i)->trName, "Green Line Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 3;
    dateAssign((pTrn + i)->date, day + 1, mon);
    (pTrn + i)->time[0] = 10, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 3 */
    strcpy((pTrn + i)->trName, "Karachi Express");
    (pTrn + i)->orig = 1,(pTrn + i)->dest = 4;
    dateAssign((pTrn + i)->date, day + 2, mon);
    (pTrn + i)->time[0] = 11, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 4 */
    strcpy((pTrn + i)->trName, "National Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 1;
    dateAssign((pTrn + i)->date, day + 2, mon);
    (pTrn + i)->time[0] = 12, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 5 */
    strcpy((pTrn + i)->trName, "National Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 3;
    dateAssign((pTrn + i)->date, day + 2, mon);
    (pTrn + i)->time[0] = 14, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 6 */
    strcpy((pTrn + i)->trName, "Karachi Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 3, mon);
    (pTrn + i)->time[0] = 10, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 7 */
    strcpy((pTrn + i)->trName, "Fareed Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 5;
    dateAssign(&(pTrn + i)->date, day + 3, mon);
    (pTrn + i)->time[0] = 13, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 8 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 3, (pTrn + i)->dest = 2;
    dateAssign(&(pTrn + i)->date, day + 4, mon);
    (pTrn + i)->time[0] = 13, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 9 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 3, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 5, mon);
    (pTrn + i)->time[0] = 7, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 10 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 3, (pTrn + i)->dest = 5;
    dateAssign(&(pTrn + i)->date, day + 5, mon);
    (pTrn + i)->time[0] = 9, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 11 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 4, (pTrn + i)->dest = 1;
    dateAssign(&(pTrn + i)->date, day + 5, mon);
    (pTrn + i)->time[0] = 12, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 12 */
    strcpy((pTrn + i)->trName, "Tezgam");
    (pTrn + i)->orig = 4, (pTrn + i)->dest = 2;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 7, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 13 */
    strcpy((pTrn + i)->trName, "Fareed Express");
    (pTrn + i)->orig = 4, (pTrn + i)->dest = 3;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 9, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 14 */
    strcpy((pTrn + i)->trName, "Bullet Express");
    (pTrn + i)->orig = 4, (pTrn + i)->dest = 5;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 14, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 15 */
    strcpy((pTrn + i)->trName, "Burrak Express");
    (pTrn + i)->orig = 5, (pTrn + i)->dest = 3;
    dateAssign(&(pTrn + i)->date, day + 8, mon);
    (pTrn + i)->time[0] = 10, (pTrn + i)->time[1] = 15;
    i++;

    /* Train 16 */
    strcpy((pTrn + i)->trName, "Karachi Express");
    (pTrn + i)->orig = 5, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 9, mon);
    (pTrn + i)->time[0] = 12, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 17 */
    strcpy((pTrn + i)->trName, "Karachi Express");
    (pTrn + i)->orig = 5, (pTrn + i)->dest = 3;
    dateAssign(&(pTrn + i)->date, day + 9, mon);
    (pTrn + i)->time[0] = 15, (pTrn + i)->time[1] = 15;
    i++;

    /* Train 18 */
    strcpy((pTrn + i)->trName, "Green Line Express");
    (pTrn + i)->orig = 5, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 11, mon);
    (pTrn + i)->time[0] = 9, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 19 */
    strcpy((pTrn + i)->trName, "Mehar Express");
    (pTrn + i)->orig = 5, (pTrn + i)->dest = 2;
    dateAssign(&(pTrn + i)->date, day + 13, mon);
    (pTrn + i)->time[0] = 7, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 20 */
    strcpy((pTrn + i)->trName, "Burrak Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 5;
    dateAssign(&(pTrn + i)->date, day + 14, mon);
    (pTrn + i)->time[0] = 13, (pTrn + i)->time[1] = 0;
    i++;

    /* Train 21 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 2;
    dateAssign(&(pTrn + i)->date, day + 5, mon);
    (pTrn + i)->time[0] = 12, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 22 */
    strcpy((pTrn + i)->trName, "Mehar Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 2;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 7, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 23 */
    strcpy((pTrn + i)->trName, "Karachi Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 1;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 9, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 24 */
    strcpy((pTrn + i)->trName, "Bullet Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 1;
    dateAssign(&(pTrn + i)->date, day + 7, mon);
    (pTrn + i)->time[0] = 14, (pTrn + i)->time[1] = 30;
    i++;

    /* Train 25 */
    strcpy((pTrn + i)->trName, "National Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 8, mon);
    (pTrn + i)->time[0] = 10, (pTrn + i)->time[1] = 15;
    i++;

    /* Train 26 */
    strcpy((pTrn + i)->trName, "Green Line Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 9, mon);
    (pTrn + i)->time[0] = 12, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 27 */
    strcpy((pTrn + i)->trName, "Shalimar Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 9, mon);
    (pTrn + i)->time[0] = 15, (pTrn + i)->time[1] = 15;
    i++;

    /* Train 28 */
    strcpy((pTrn + i)->trName, "Tezgam");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 4;
    dateAssign(&(pTrn + i)->date, day + 11, mon);
    (pTrn + i)->time[0] = 9, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 29 */
    strcpy((pTrn + i)->trName, "Fareed Express");
    (pTrn + i)->orig = 1, (pTrn + i)->dest = 3;
    dateAssign(&(pTrn + i)->date, day + 13, mon);
    (pTrn + i)->time[0] = 7, (pTrn + i)->time[1] = 45;
    i++;

    /* Train 30 */
    strcpy((pTrn + i)->trName, "Green Line Express");
    (pTrn + i)->orig = 2, (pTrn + i)->dest = 1;
    dateAssign(&(pTrn + i)->date, day + 14, mon);
    (pTrn + i)->time[0] = 13, (pTrn + i)->time[1] = 0;
    i++;

}

void dateAssign(int* date, int day, int mon) {
    if(mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10) { // Months with 31 days, except December
        
        if(day > 31) {
            day -= 31;
            *date = day;
            mon++;
            *(date + 1) = mon;
        } else {
            *date = day;
            *(date + 1) = mon;
        }

    } else if(mon == 2) { // February

        if(day > 28) {
            day -= 28;
            *date = day;
            mon++;
            *(date + 1) = mon;
        } else {
            *date = day;
            *(date + 1) = mon;
        }

    } else if(mon == 12) { // December

        if(day > 31) {
            day -= 31;
            *date = day;
            mon = 1;
            *(date + 1) = mon;
        } else {
            *date = day;
            *(date + 1) = mon;
        }

    } else { // Months with 30 days

        if(day > 30) {
            day -= 30;
            *date = day;
            mon++;
            *(date + 1) = mon;
        } else {
            *date = day;
            *(date + 1) = mon;
        }

    }

}


void login(user* pUsr) {
    char uName[SIZE], pwd[SIZE], temp;
    int i;

    while(1) {
        system("cls");
        
        printf("Username: %s\t\t\t", pUsr->uName);
        printf("Password: %s\n", pUsr->pass);
        printf("==================================================\n\n\n");

        printf("\t\tWELCOME TO BROS TRAIN.COM \n\n\n");
        printf("Please enter your login credentials.\n\n");

        /* Asks for user's username */
        printf("Username: ");
        scanf("%s", &uName);

        /* Asks for user's password */
        i = 0;
        printf("Password: ");
        while(1) {
        temp = getch(); // Inputs one single character of password without printing to terminal

            /* Evaluating the ASCII value of the current one single character of password */
            if(temp == ENTER || temp == TAB) {
                pwd[i] = '\0';
                break;
            } else if(temp == BKSP) {
                if(i > 0) {
                    i--;
                    printf("\b \b"); // Backspace one character
                }
            } else {
                pwd[i] = temp;
                printf("*");
                i++;
            }

        }

        /* Evaluates login credentials */
        if(strcmp(uName, pUsr->uName) != 0 || strcmp(pwd, pUsr->pass) != 0) {
            printf("\n\nInvalid login.\n\n\nPress any key to try again. ");
            getch();
        } else {
            break;
        }

    }

    printf("\n\nLogin successful.");
    screenHold();

}

void printMap() {
    system("cls");

    printf("                                          { APNI TRAINS }                                           \n");
    // printf("                                                                                                    \n");	
    // printf("         K          KK                                                                              \n");
    // printf("       KNWWWWNXXXXKNWWWNK                                                                           \n");
    // printf("       XMMMMMWWNW( 1 )MMWNNNNXKKKK                                                                  \n");
    // printf("      XWMMMMWNWWWWWMMMMMMMMMMMWMMWX                        XNNK                                     \n");
    // printf("O   KNWWWWMMWWMMMMMMMMMMMMMMMMMMMMWX  O                   XMMMWXKKXXK                               \n");
    // printf("  KKKKKKKKXNNNWMMMMMMMMMMMMMMMMMMMMWWXXNNXXXXXXXKKKKKK  KXWMMMMMMMMWNNNNXKKKXK   KKKKKXKKKXXK       \n");
    // printf("              NWMMMMMMMMMMM( 2 )MMMWWNWMMMMMMMMMMW( 3 )WWMMMMMMMMMWNWMMMM( 5 )X KNWWWWWWNNXXK       \n");
    // printf("             KWWWMMMMMMMMMMMMMMMMMWNWWMMMMMMMMMMMMMMMMMMMMMMMMMWWWWWWMMMMMMMMMWXK    KKK  O         \n");
    // printf("               KKKKKXXXXNWWMMMMMMMWWWWMMMMMMMMMMMMMMMMMMMMMMMWNWWWMMMMMMMMMMMMMWK                   \n");
    // printf("                          KXNNWWWWWNXKXXNXNNNWW( 4 )WWWWWWMMMMWNWMMMMMMMMMMMMMMWNXXK    K  KXXK     \n");
    // printf("                               KKK            KKKXXXXNWWWWWWMMMWWWMMMMMMMMMMMMMMMMMMMMMMWWWWMMWWNK  \n");
    // printf("                                                      KXNWNNWWWWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWX  \n");
    // printf("                                                           KKKKXXXNNNNNNNNWWWMMMMWWNNNWWMMMMMMMMN   \n");
    // printf("                                                                            KKXXKK     KXNWWWMMMN   \n");
    // printf("                                                                                           KKXXXXK  \n");
    // printf("                                                                                               O  K \n");

    printf("Cities:");
    printf("\n1. Karachi\n2. Quetta\n3. Lahore\n4. Islamabad\n5. Peshawar");
    printf("\n\n");

}

void inputLoc(user* pUsr) {
    /* Asks for origin city */
    printf("Insert your train origin\t(number): ");
    pUsr->usrTrn.orig = inputRange(1, 5);
    
    /* Asks for destination city */
    printf("Insert your train destination\t(number): ");
    while(1) {
        pUsr->usrTrn.dest = inputRange(1, 5);

        /* Evaluates destination city (destination != origin) */
        if(pUsr->usrTrn.dest == pUsr->usrTrn.orig) {
            printf("Origin and destination cannot be the same location.\n\n");
            printf("Please re-input: ");
        } else {
            break;
        }
    }

    screenHold();

}


void trListInput(user* pUsr, train* pTrn) {
    int avail = 0, i; // Avail: How many train is available for specific origin-destination cities based on user's input

    system("cls");
    printf("Current Time\t: %s\n", __TIME__);
    printf("Current Date\t: %s\n\n", __DATE__);

    /* Prints train catalog */
    printf("Train Number\tName\t\tOrigin\t\tDestination\tDate\tTime\n");
    printf("--------------------------------------------------------------------------------\n");
    
    /* Searches train(s) from train database that match user's origin-destination cities input */
    for(i = 0; i < QTY; i++) {
        if((pTrn + i)->orig == pUsr->usrTrn.orig && (pTrn + i)->dest == pUsr->usrTrn.dest) {
            avail++;
            (pTrn + i)->num = avail;
            printTrain(pTrn + i); // Prints one single line of train data to train catalog
        } else {
            (pTrn + i)->num = 0;
        }
    }

    /* Evaluates train availability */
    if(avail != 0) {
        inputTrain(&usr, &trn, avail);  // Asks for user's train input if there is/are train(s) available
    } else {
        printf("No train is available for now.\n");
        pUsr->usrTrn.num = 0;           // Instruction if there's no train available
    }

}

void printTrain(train* pTrn) {
    char temp[15];

    /* Prints train number */
    printf("\t%d\t", pTrn->num);

    /* Prints train name */
    if(strlen(pTrn->trName) >= 8) {
        printf("%.15s\t", pTrn->trName);
    } else {
        printf("%.15s\t\t", pTrn->trName);
    }

    switch(pTrn->orig) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
        default: printf("Invalid city.");
                 break;
    }

    /* Prints origin city */
    if(strlen(temp) >= 8) {
        printf("%.15s\t", temp);
    } else {
        printf("%.15s\t\t", temp);
    }

    switch(pTrn->dest) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
        default: printf("Invalid city.");
                 break;
    }

    /* Prints destination city */
    if(strlen(temp) >= 8) {
        printf("%.15s\t", temp);
    } else {
        printf("%.15s\t\t", temp);
    }

    switch(pTrn->date[1]) {
        case 1: strcpy(temp, "Jan");
                break;
        case 2: strcpy(temp, "Feb");
                break;
        case 3: strcpy(temp, "Mar");
                break;
        case 4: strcpy(temp, "Apr");
                break;
        case 5: strcpy(temp, "May");
                break;
        case 6: strcpy(temp, "Jun");
                break;
        case 7: strcpy(temp, "Jul");
                break;
        case 8: strcpy(temp, "Aug");
                break;
        case 9: strcpy(temp, "Sep");
                break;
        case 10: strcpy(temp, "Oct");
                break;
        case 11: strcpy(temp, "Nov");
                break;
        case 12: strcpy(temp, "Dec");
                break;
        default: printf("Invalid month.");
                 break;
    }

    /* Prints date DD MM */
    printf("%02d %s\t", pTrn->date[0], temp);

    /* Prints time HH:MM */
    printf("%02d:%02d", pTrn->time[0], pTrn->time[1]);

    /* Prints new line */
    printf("\n");

}

void inputTrain(user* pUsr, train* pTrn, int avail) {
    int i;
    
    /* Asks for user's train number input */
    printf("\n\nSelect your train (number): ");
    pUsr->usrTrn.num = inputRange(1, avail);

    /* Searches one specific train from train database that matches user's train number input */
    for(i = 0; i < QTY; i++) {
        if(pUsr->usrTrn.num == (pTrn + i)->num) {
            strcpy(pUsr->usrTrn.trName, (pTrn + i)->trName);    // Copies train name from trains' database to user's train data
            pUsr->usrTrn.date[0] = (pTrn + i)->date[0];               // Copies train date of day from trains' database to user's train data
            pUsr->usrTrn.date[1] = (pTrn + i)->date[1];               // Copies train date of month from trains' database to user's train data
            pUsr->usrTrn.time[0] = (pTrn + i)->time[0];               // Copies train time of hour from trains' database to user's train data
            pUsr->usrTrn.time[1] = (pTrn + i)->time[1];               // Copies train time of minute from trains' database to user's train data
        }
    }

    screenHold();

}

void inputPsg(user* pUsr) {
    char temp; // Temp is used for clearing buffer after inputting an int
    
    /* Evaluates whether or not ask for user's passenger data input based on train availability */
    if(pUsr->usrTrn.num != 0) {
        system("cls");

        /* Asks for passenger class */
        printf("Available classes:\n1. Business\n2. Economy");
        printf("\n\nSelect your class (number): ");
        pUsr->class = inputRange(1, 2);

        /* Asks for number of passenger */
        printf("\n\nNumber of passenger (up to 4): ");
        pUsr->numPsg = inputRange(1, 4);

        /* Asks for passenger seat(s) */
        if(pUsr->class == 1) {
            printf("\n\nAvailable cars:\n1. A\n2. B");
            printf("\n\nSelect your car (number): ");
            pUsr->seat[0] = inputRange(1, 2);

            printf("\n\nAvailable seats: 1 to 16");
            printf("\nSelect your seat (number): ");
            pUsr->seat[1] = inputRange(1, 16);
        } else {
            printf("\n\nAvailable cars:\n1. C\n2. D\n3. E\n4. F\n5. G\n6. H\n7. I\n8. J");
            printf("\n\nSelect your car (number): ");
            pUsr->seat[0] = inputRange(1, 8);
            pUsr->seat[0] += 2;

            printf("\n\nAvailable seats: 1 to 20");
            printf("\nSelect your seat (number): ");
            pUsr->seat[1] = inputRange(1, 20);
        }

        /* Asks for passenger's name */
        printf("\n\nInsert your name: ");
        scanf("%c", &temp);  // Clearing buffer after inputting int
        scanf("%[^\n]", &pUsr->psgName); // Allowing for spaces input to register
        
    }
    
}


int confirm(user* pUsr) {
    char input;

    /* Evaluates whether or not ask for user's order confirmation based on train availability */
    if(pUsr->usrTrn.num != 0) {

        /* Instructions if there is/are train available */
        printf("\n\n\nDo you confirm your order? ");
        printf("(Y/y or N/n): ");

        while(1) {
            scanf(" %c", &input);

            if(input == 'Y' || input == 'y' || input == 'N' || input == 'n') {
                break;
            } else {
                printf("Invalid input.\n\nPlease re-input: ");
            }
        }

        if(input == 'Y' || input == 'y') {
            return 1;
        } else {
            return 0;
        }

    } else {

        /* Instructions if there is no train available */
        printf("\n\n\nPress any key to go back. ");
        getch();
        return 0;

    }

}

void calcCost(user* pUsr) {
    /* Set initial cost based on passenger class and number of passenger */
    if(pUsr->class == 1) {
        pUsr->cost = 3000 * pUsr->numPsg;
    } else {
        pUsr->cost = 1000 * pUsr->numPsg;
    }
    
    /* Adds extra price based on train's company */
    if(strcmp(pUsr->usrTrn.trName, "Karachi Express") == 0) {
        pUsr->cost += 10000;
    } else if(strcmp(pUsr->usrTrn.trName, "National Express") == 0) {
        pUsr->cost += 8000;
    } else if(strcmp(pUsr->usrTrn.trName, "Bullet Express") == 0) {
        pUsr->cost += 7500;
    } else if(strcmp(pUsr->usrTrn.trName, "Burrak Express") == 0) {
        pUsr->cost += 6500;
    } else if(strcmp(pUsr->usrTrn.trName, "Shalimar Express") == 0) {
        pUsr->cost += 5500;
    } else if(strcmp(pUsr->usrTrn.trName, "Green Line Express") == 0) {
        pUsr->cost += 5000;
    } else if(strcmp(pUsr->usrTrn.trName, "Fareed Express") == 0) {
        pUsr->cost += 4500;
    } else if(strcmp(pUsr->usrTrn.trName, "Tezgam") == 0) {
        pUsr->cost += 4000;
    } else if(strcmp(pUsr->usrTrn.trName, "Mehar Express") == 0) {
        pUsr->cost += 4000;
    }

}

void receipt(user* pUsr) {
    char temp[15], input;

    system("cls");

    /* Prints Boarding Pass header */
    printf("\tBOARDING PASS\n\n");


    /* Prints line 1 header */
    printf("Name\t\t\tBooking Code\n");

    /* Prints passenger name */
    if(strlen(pUsr->psgName) >= 16) {
        printf("%.20s\t", pUsr->psgName);
    } else if(strlen(pUsr->psgName) >= 8) {
        printf("%.20s\t\t", pUsr->psgName);
    } else {
        printf("%.20s\t\t\t", pUsr->psgName);
    }

    if(strcmp(pUsr->usrTrn.trName, "Karachi Express") == 0) {
       strcpy(temp, "KAE");
    } else if(strcmp(pUsr->usrTrn.trName, "National Express") == 0) {
        strcpy(temp, "NAE");
    } else if(strcmp(pUsr->usrTrn.trName, "Bullet Express") == 0) {
        strcpy(temp, "BUE");
    } else if(strcmp(pUsr->usrTrn.trName, "Burrak Express") == 0) {
        strcpy(temp, "BRE");
    } else if(strcmp(pUsr->usrTrn.trName, "Shalimar Express") == 0) {
        strcpy(temp, "SHE");
    } else if(strcmp(pUsr->usrTrn.trName, "Green Line Express") == 0) {
        strcpy(temp, "GLE");
    } else if(strcmp(pUsr->usrTrn.trName, "Fareed Express") == 0) {
        strcpy(temp, "FRE");
    } else if(strcmp(pUsr->usrTrn.trName, "Tezgam") == 0) {
        strcpy(temp, "TZM");
    } else if(strcmp(pUsr->usrTrn.trName, "Mehar Express") == 0) {
        strcpy(temp, "MHE");
    }

    /* Prints booking code */
    printf("%s%d%d", temp, pUsr->usrTrn.orig, pUsr->usrTrn.dest);
    printf("%02d%02d", pUsr->usrTrn.date[0], pUsr->usrTrn.date[1]);
    printf("%02d%02d", pUsr->usrTrn.time[0], pUsr->usrTrn.time[1]);
    printf("%d%d%02d\n\n", pUsr->numPsg, pUsr->seat[0], pUsr->seat[1]);


    /* Prints line 2 header */
    printf("Class\t\t\tNo. of Passenger\n");

    /* Prints class */
    switch(pUsr->class) {
        case 1: strcpy(temp, "Business");
                printf("%s\t\t", temp);
                break;
        case 2: strcpy(temp, "Economy");
                printf("%s\t\t\t", temp);
                break;
    }

    /* Prints number of passenger */
    printf("%d\n\n", pUsr->numPsg);


    /* Prints line 3 header */
    printf("Train\t\t\tCar\tSeat\n");

    /* Prints train name */
    if(strlen(pUsr->usrTrn.trName) >= 16) {
        printf("%.20s\t", pUsr->usrTrn.trName);
    } else if(strlen(pUsr->usrTrn.trName) >= 8) {
        printf("%.20s\t\t", pUsr->usrTrn.trName);
    } else {
        printf("%.20s\t\t\t", pUsr->usrTrn.trName);
    }
 
    switch(pUsr->seat[0]) {
        case 1: strcpy(temp, "A");
                break;
        case 2: strcpy(temp, "B");
                break;
        case 3: strcpy(temp, "C");
                    break;
        case 4: strcpy(temp, "D");
                    break;
        case 5: strcpy(temp, "E");
                    break;
        case 6: strcpy(temp, "F");
                break;
        case 7: strcpy(temp, "G");
                break;
        case 8: strcpy(temp, "H");
                break;
        case 9: strcpy(temp, "I");
                break;
        case 10: strcpy(temp, "J");
                break;
    }

    /* Prints car */
    printf("%s\t", temp);

    /* Prints seat */
    switch(pUsr->numPsg) {
        case 1: printf("%d", pUsr->seat[1]);
                strcpy(temp, "A");
                printf("%s\n\n", temp);
                break;
        case 2: printf("%d", pUsr->seat[1]);
                strcpy(temp, "A");
                printf("%s-", temp);
                printf("%d", pUsr->seat[1]);
                strcpy(temp, "B");
                printf("%s\n\n", temp);
                break;
        case 3: printf("%d", pUsr->seat[1]);
                strcpy(temp, "A");
                printf("%s-", temp);
                printf("%d", pUsr->seat[1]);
                strcpy(temp, "C");
                printf("%s\n\n", temp);
                break;
        case 4: printf("%d", pUsr->seat[1]);
                strcpy(temp, "A");
                printf("%s-", temp);
                printf("%d", pUsr->seat[1]);
                strcpy(temp, "D");
                printf("%s\n\n", temp);
                break;
    }


    /* Prints line 4 header */
    printf("Departure\t\tDestination\n");

    switch(pUsr->usrTrn.orig) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
    }

    /* Prints origin city */
    if(strlen(temp) >= 8) {
        printf("%.20s\t\t", temp);
    } else {
        printf("%.20s\t\t\t", temp);
    }

    switch(pUsr->usrTrn.dest) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
    }

    /* Prints destination city */
    printf("%.20s\n", temp);

    switch(pUsr->usrTrn.date[1]) {
        case 1: strcpy(temp, "Jan");
                break;
        case 2: strcpy(temp, "Feb");
                break;
        case 3: strcpy(temp, "Mar");
                break;
        case 4: strcpy(temp, "Apr");
                break;
        case 5: strcpy(temp, "May");
                break;
        case 6: strcpy(temp, "Jun");
                break;
        case 7: strcpy(temp, "Jul");
                break;
        case 8: strcpy(temp, "Aug");
                break;
        case 9: strcpy(temp, "Sep");
                break;
        case 10: strcpy(temp, "Oct");
                break;
        case 11: strcpy(temp, "Nov");
                break;
        case 12: strcpy(temp, "Dec");
                break;
        default: printf("Invalid month.");
                 break;
    }

    /* Prints date DD MM */
    printf("%02d %s ", pUsr->usrTrn.date[0], temp);

    /* Prints time HH:MM */
    printf("%02d:%02d\n\n", pUsr->usrTrn.time[0], pUsr->usrTrn.time[1]);


    /* Prints line 5 */
    printf("Rs. %d.00", pUsr->cost);


    printf("\n\n\nDo you want to print your receipt? ");
    printf("(Y/y or N/n): ");

    while(1) {
        scanf(" %c", &input);

        if(input == 'Y' || input == 'y' || input == 'N' || input == 'n') {
            break;
        } else {
            printf("Invalid input.\n\nPlease re-input: ");
        }
    }

    if(input == 'Y' || input == 'y') {
        fileReceipt(&usr);
    }
    
}

void fileReceipt(user* pUsr) {
    char filename[SIZE], temp[15];

    sprintf(filename, "%s.txt", pUsr->psgName);

    FILE* fp = fopen(filename, "w");
    
    /* Prints Boarding Pass header */
    fprintf(fp, "\tBOARDING PASS\n\n");


    /* Prints line 1 header */
    fprintf(fp, "Name\t\t\t\tBooking Code\n");
    
    /* Prints passenger name */
    if(strlen(pUsr->psgName) >= 16) {
        fprintf(fp, "%.20s\t\t", pUsr->psgName);
    } else if(strlen(pUsr->psgName) >= 8) {
        fprintf(fp, "%.20s\t\t\t", pUsr->psgName);
    } else {
        fprintf(fp, "%.20s\t\t\t\t", pUsr->psgName);
    }

    if(strcmp(pUsr->usrTrn.trName, "Karachi Express") == 0) {
       strcpy(temp, "KAE");
    } else if(strcmp(pUsr->usrTrn.trName, "National Express") == 0) {
        strcpy(temp, "NAE");
    } else if(strcmp(pUsr->usrTrn.trName, "Bullet Express") == 0) {
        strcpy(temp, "BUE");
    } else if(strcmp(pUsr->usrTrn.trName, "Burrak Express") == 0) {
        strcpy(temp, "BRE");
    } else if(strcmp(pUsr->usrTrn.trName, "Shalimar Express") == 0) {
        strcpy(temp, "SHE");
    } else if(strcmp(pUsr->usrTrn.trName, "Green Line Express") == 0) {
        strcpy(temp, "GLE");
    } else if(strcmp(pUsr->usrTrn.trName, "Fareed Express") == 0) {
        strcpy(temp, "FRE");
    } else if(strcmp(pUsr->usrTrn.trName, "Tezgam") == 0) {
        strcpy(temp, "TZM");
    } else if(strcmp(pUsr->usrTrn.trName, "Mehar Express") == 0) {
        strcpy(temp, "MHE");
    }

    /* Prints booking code */
    fprintf(fp, "%s%d%d", temp, pUsr->usrTrn.orig, pUsr->usrTrn.dest);
    fprintf(fp, "%02d%02d", pUsr->usrTrn.date[0], pUsr->usrTrn.date[1]);
    fprintf(fp, "%02d%02d", pUsr->usrTrn.time[0], pUsr->usrTrn.time[1]);
    fprintf(fp, "%d%d%02d\n\n", pUsr->numPsg, pUsr->seat[0], pUsr->seat[1]);


    /* Prints line 2 header */
    fprintf(fp, "Class\t\t\t\tNo. of Passenger\n");

    /* Prints class */
    switch(pUsr->class) {
        case 1: strcpy(temp, "Business");
                fprintf(fp, "%s\t\t\t", temp);
                break;
        case 2: strcpy(temp, "Economy");
                fprintf(fp, "%s\t\t\t\t", temp);
                break;
    }

    /* Prints number of passenger */
    fprintf(fp, "%d\n\n", pUsr->numPsg);


    /* Prints line 3 header */
    fprintf(fp, "Train\t\t\t\tCar\tSeat\n");

    /* Prints train name */
    if(strlen(pUsr->usrTrn.trName) >= 16) {
        fprintf(fp, "%.20s\t\t", pUsr->usrTrn.trName);
    } else if(strlen(pUsr->usrTrn.trName) >= 8) {
        fprintf(fp, "%.20s\t\t\t", pUsr->usrTrn.trName);
    } else {
        fprintf(fp, "%.20s\t\t\t\t", pUsr->usrTrn.trName);
    }
 
    switch(pUsr->seat[0]) {
        case 1: strcpy(temp, "A");
                break;
        case 2: strcpy(temp, "B");
                break;
        case 3: strcpy(temp, "C");
                break;
        case 4: strcpy(temp, "D");
                break;
        case 5: strcpy(temp, "E");
                break;
        case 6: strcpy(temp, "F");
                break;
        case 7: strcpy(temp, "G");
                break;
        case 8: strcpy(temp, "H");
                break;
        case 9: strcpy(temp, "I");
                break;
        case 10: strcpy(temp, "J");
                break;
    }

    /* Prints car */
    fprintf(fp, "%s\t", temp);

    /* Prints seat */
    switch(pUsr->numPsg) {
        case 1: fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "A");
                fprintf(fp, "%s\n\n", temp);
                break;
        case 2: fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "A");
                fprintf(fp, "%s-", temp);
                fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "B");
                fprintf(fp, "%s\n\n", temp);
                break;
        case 3: fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "A");
                fprintf(fp, "%s-", temp);
                fprintf("%d", pUsr->seat[1]);
                strcpy(temp, "C");
                fprintf(fp, "%s\n\n", temp);
                break;
        case 4: fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "A");
                fprintf(fp, "%s-", temp);
                fprintf(fp, "%d", pUsr->seat[1]);
                strcpy(temp, "D");
                fprintf(fp, "%s\n\n", temp);
                break;
    }


    /* Prints line 4 header */
    fprintf(fp, "Departure\t\t\tDestination\n");

    switch(pUsr->usrTrn.orig) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
    }

    /* Prints origin city */
    if(strlen(temp) >= 8) {
        fprintf(fp, "%.20s\t\t\t", temp);
    } else {
        fprintf(fp, "%.20s\t\t\t\t", temp);
    }

    switch(pUsr->usrTrn.dest) {
        case 1: strcpy(temp, "Karachi");
                break;
        case 2: strcpy(temp, "Quetta");
                break;
        case 3: strcpy(temp, "Lahore");
                break;
        case 4: strcpy(temp, "Islamabad");
                break;
        case 5: strcpy(temp, "Peshawar");
                break;
    }

    /* Prints destination city */
    fprintf(fp, "%.20s\n", temp);

    switch(pUsr->usrTrn.date[1]) {
        case 1: strcpy(temp, "Jan");
                break;
        case 2: strcpy(temp, "Feb");
                break;
        case 3: strcpy(temp, "Mar");
                break;
        case 4: strcpy(temp, "Apr");
                break;
        case 5: strcpy(temp, "May");
                break;
        case 6: strcpy(temp, "Jun");
                break;
        case 7: strcpy(temp, "Jul");
                break;
        case 8: strcpy(temp, "Aug");
                break;
        case 9: strcpy(temp, "Sep");
                break;
        case 10: strcpy(temp, "Oct");
                break;
        case 11: strcpy(temp, "Nov");
                break;
        case 12: strcpy(temp, "Dec");
                break;
    }

    /* Prints date DD MM */
    fprintf(fp, "%02d %s ", pUsr->usrTrn.date[0], temp);

    /* Prints time HH:MM */
    fprintf(fp, "%02d:%02d\n\n", pUsr->usrTrn.time[0], pUsr->usrTrn.time[1]);


    /* Prints line 5 */
    fprintf(fp, "Rs. %d.00", pUsr->cost);

    fclose(fp);

}


int reset() {
    char input;

    system("cls");
    printf("Do you want to reset the program? ");
    printf("(Y/y or N/n): ");

    while(1) {
        scanf(" %c", &input);

        if(input == 'Y' || input == 'y' || input == 'N' || input == 'n') {
            break;
        } else {
            printf("Invalid input.\n\nPlease re-input: ");
        }
    }

    if(input == 'Y' || input == 'y') {
        return 1;
    } else {
        return 0;
    }
}

int inputRange(int low, int up) {
    int input;

    /* Evaluates lower and upper bound mathematical relationship validity */
    if(low <= up) {

        /* Instructions if bound is valid */
        while(1) {
            scanf("%d", &input);

            if(input >= low && input <= up) {
                break;
            } else {           
                printf("Option %d is not available.\n\n", input);
                printf("Please re-input: ");
            }
        }

    } else {
        /* Programmer's note if bound is invalid */
        printf("Invalid argument. Lower bound must be less than or equal to upper bound.\n\n");
    }

    return input;
}

void screenHold() {
    printf("\n\n\nPress any key to continue. ");
    getch();

}

