#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<Windows.h>
#include<ctype.h>
#pragma warning(disable:4996)
SYSTEMTIME t;

#define basketball 150 // per session per court
#define kaeraoke 25 // per session per room
#define swimming 25 // per session per person
#define dancing 80 // per session per room
#define archery 50 // per session 
#define meeting 150  // per session 
#define maintance 1.25 //maintaiance fee


typedef struct {
    char regDate[10];
    char expDate[10];
}Date;
struct member {
    int id;
    char name[51];
    char gender;
    char ic[13];
    char contactNum[12];
    char address[99];
    Date d;
};
struct Salary {
    double salary, payrate;
};
typedef struct {
    char Spass[20], StaffName[70], StaffPosition[50], StaffGender[7], sicNo[15], sphoneNo[15];
    int StaffID;
    struct Salary salary;
}StaffInfo;
typedef struct {
    char bookingID[6], facID[4], currentdate[11], timeslot[10], memberID[7], staffID[6], bdate[11], status;
    double fee;
}booking;
typedef struct {
    char from_hour[5], till_hour[5];
}hours;
typedef struct {
    char fac_id[4], type[21], venue[11], descrip[31], max_user[5];
    hours hour;
}details;
typedef struct {
    char timeslot[11];
}timeslot;
typedef struct {
    char facilityID[4];
    timeslot time[6];
}facility;
typedef struct {
    char facID[20], memberID[20], bookingDate[20], bookingTime[20], status[20], noUse1[20], noUse2[20], noUse3[20], noUse5;
    double nouse4;
}addFacUsageStatusRecord;

time_t tm;
booking book[99];
details facdet[20];
facility fac[99];

void menu();

//member
void membermain();
void displayMember();
void addMember();
void searchMember();
void membermodify();
void memberdelete();
void memberreport();
int membergenerateId();
int membernumOfRecord(int num);


//staff
void sadd();
char* spositionassign();
void smodify();
void sDelete();
void sreport();
void CalculateOT();
char* staff[6];

//facility 
void facmain();
void searchRecord();
void addRecord();
void displayRecord();
void report();
void editRecord();
void deleteRecord();
void valID(char ID[5]);
void valType(char type[21]);
void backtofacmain();

//facility usage 
void facusageMain();
void addFacUsageStatus();
void addtimeslot(char facID[4]);
void modify_updaterecord();
void searchStatus();
void facudeleteRecord();
void displayAllFacStatus();
void generate_report();

//everyone can use
char getValidGender(char* gender);
char* getValidIc();
char* getValidContactNum();
char* getValidname();

//color
void cyan() {
    printf("\033[0;36m");
}
void red() {
    printf("\033[1;31m");
}
void yellow() {
    printf("\033[1;33m");
}
void reset() {
    printf("\033[0m");
}

//start main menu
void menu() {

    int choice;
    do {
        system("cls");
        yellow();
        printf("[1] Booking\n");
        printf("[2] Facility Usage\n");
        printf("[3] Facility \n");
        printf("[4] Member\n");
        printf("[5] Staff\n");
        printf("[0] Exit\n\n");

        printf("Enter ur choice > ");
        cyan();
        scanf("%d", &choice);
        reset();
        if (choice > 6 || choice < 0){
            red();
            printf("invalid option");
            reset();
        }
    } while (choice > 6 || choice < 0);
    reset();
    switch (choice)
    {
    case 1:
        bookingmain();
        break;
    case 2:
        facusageMain();
        break;
    case 3:
        facmain();
        break;
    case 4:
        membermain();
        break;
    case 5:
        smenu();
        break;
    case 0:
        exit(0);
        break;
    }


}

//login 
int welcomepage() {
    system("cls");
    reset();
    printf("\n\n\n\n\t\t\t\t============="
        "============================="
        "===========");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
        "~~~~~");
    printf("\n\t\t\t\t==================="
        "============================="
        "=====");
    yellow();
    printf("\n\t\t\t\t[|:::>:::>  "
        "\tNIRVANA LAKE CLUB     <::<::<::"
        "<:::|]\t");
    reset();
    printf("\n\t\t\t\t==================="
        "============================="
        "=====");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
        "~~~");
    printf("\n\t\t\t\t====================="
        "================================\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t""\n\n\t\t\t\t");

    printf("Develop by Team Hair Loss \n\n\t\t\t\t\n");

}

void main() {

    StaffInfo sinfo;

    char pass[10];
    char staffID[6], staffID2[6];
    int error;

    do {
        FILE* fs = fopen("staff.txt", "r");
        if (fs == NULL)
        {
            red();
            printf("Error");
            reset();
        }
        system("cls");
        welcomepage();
        yellow();
        printf("\t\t\t\tEnter Staff ID > ");
        cyan();
        rewind(stdin);
        scanf("%s", &staffID);
        for (int i = 0; i < strlen(staffID); i++)
        {
            if (isalpha(staffID[i]))
            {
                staffID[i] = toupper(staffID[i]);
            }
        }
        yellow();
        printf("\t\t\t\tEnter password > ");
        cyan();
        rewind(stdin);
        scanf("%s", &pass);
        reset();
        while (!feof(fs)) {

            fscanf(fs, "%s %s || %[^||] ||%s %s %[^|]| %s %lf\t%lf\n", &staffID2, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

            if ((strcmp(staffID, staffID2) == 0) && (strcmp(pass, sinfo.Spass) == 0))
            {
                reset();
                printf("\n\t\t\t\tlogin succesfully\n");
                strcpy(staff, staffID);
                error = 0;
                break;
            }
            else
                error = 1;
        }

        if (error == 1) {
            red();
            printf("\n\t\t\t\tInvalid staffID or password\n");
            reset();
        }
        system("pause");
        fclose(fs);
    } while (error == 1);

    reset();
    menu();

}

//booking module
int bookingmenu() {

    system("cls");
    int choice;
    do {
        system("cls");
        yellow();
        printf("   [1] Reservation\n");
        printf("   [2] Search booking details\n");
        printf("   [3] change booking payment status\n");
        printf("   [4] Cancel Booking\n");
        printf("   [5] Earning report\n");
        printf("   [0] Back to main menu\n\n");

        printf("Enter ur choice > ");
        cyan();
        scanf("%d", &choice);
        if (choice < 0 || choice > 6) {
            red();
            printf("\n\ninvalid option");
            reset();
        }
    } while (choice < 0 || choice > 6);
    reset();
    return choice;

}

int bookingmain() {
    yellow();
    while (1)
    {
        system("cls");
        int choice = bookingmenu();
        switch (choice)
        {
        case 1:
            reservation();
            break;
        case 2:
            searchBookingDetails();
            break;
        case 3:
            changestatus();
            break;
        case 4:
            cancelbooking();
            break;
        case 5:
            earningreport();
            break;
        case 0:
            menu();
            break;
        }

    }
}

int reservation() {

    FILE* fb = fopen("booking.txt", "a");
    FILE* fd = fopen("date.txt", "r");

    if (fd == NULL)
    {
        red();
        printf("unable to open file");
        reset();
        exit(0);
    }

    if (fb == NULL)
    {
        red();
        printf("unable to open file");
        reset();
        exit(0);
    }



    int bookID = bookinggenerateID() + 1 + 100;

    char date[14];
    char facilityID[4];
    double fee;
    char paid;
    char slot[11];
    char cont;
    int memberID;
    char staffId[6];
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    do {
        //validation of reservation day -start
        int datekey;
        do {
            system("cls");
            yellow();
            printf("Booking ID : BO%03d\n\n", bookID);
            datekey = validationOfDate();
        } while (datekey != 1);
        reset();
        //validation of reservation day -end

        //member -start

        validationOfmemberID(&memberID);

        //member -end

        //choose facility and timeslot -start

        choosefacility(&facilityID);
        system("cls");
        adjustedtimeslot(facilityID);
        displaytimeslot(&slot);
        yellow();
        printf("%s\t", facilityID);
        printf("%s\n`", slot);
        system("pause");
        //choose facility and timeslot -end
        //payment
        reset();
        calculatefees(facilityID, &fee, &paid);

        //scan date
        fscanf(fd, "%s", date);
        reset();
        printf("BO%03d  %3s %02d-%02d-%4d %s %9s ME%4d %5s %6.2lf %c\n", bookID, facilityID, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, date, slot, memberID, &staff, fee, paid);
        yellow();
        printf("Please ensure the details are correct\n");
        printf("type N if not correct or type any character to save the reservation detail > ");
        rewind(stdin);
        cyan();
        scanf("%c", &cont);
        cont = toupper(cont);
    } while (cont == 'N');

    //record
    fprintf(fb, "BO%03d  %3s %02d-%02d-%4d   %s    %9s ME%4d %5s %6.2lf %c\n", bookID, facilityID, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, date, slot, memberID, &staff, fee, paid);

    yellow();
    printf("\nrecorded successfully\n");
    system("pause");

    fclose(fb);
    fclose(fd);


}

int searchBookingDetails() {

    int booking = addintoarray();
    system("cls");
    int choice;
    int x;
    char temp[13];
    do {
        yellow();
        printf("search with \n");
        printf("[1] booking ID\n");
        printf("[2] booking date\n");
        printf("[3] member ID\n");
        printf("[4] display all booking\n\n");

        printf("Enter your choice > ");
        cyan();
        scanf("%d", &choice);
        if (choice > 3)
        {
            red();
            printf("invalid choice");
        }

    } while (choice > 4);

    int invalid = 0;
    yellow();
    system("cls");
    switch (choice)
    {
    case 1:
        printf("Enter bookingID > ");
        cyan();
        scanf("%s", &temp);

        for (int k = 0; k < strlen(temp); k++)
        {
            if (isalpha(temp[k]))
            {
                temp[k] = toupper(temp[k]);
            }
        }
        displaytop();
        for (int i = 0; i < booking; i++)
        {
            if (strcmp(book[i].bookingID, temp) == 0)
            {
                reset();
                printf("%-10s  %-10s   %-12s  %-12s  %-10s  %-7s %-7s %-6.2lf  %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
                invalid = 0;
                break;
            }
            else
                invalid = 1;
        }

        if (invalid == 1)
        {
            red();
            printf("record not found\n");
            yellow();
        }
       
        system("pause");
        break;
    case 2:

        x = validationofdate2();
        while (x != 1)
        {
            x = validationofdate2();
        }

        FILE* fd = fopen("date.txt", "r");
        if (fd == NULL)
        {
            red();
            printf("error");
        }

        char date[13];
        fscanf(fd, "%s", date);

        system("cls");
        displaytop();
        for (int i = 0; i < booking; i++)
        {
            if (strcmp(book[i].bdate, date) == 0)
            {
                reset();
                printf("%-10s  %-10s   %-12s  %-12s  %-10s  %-7s %-7s %-6.2lf  %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
                invalid = invalid + 1;
            }
        }

        if (invalid == 0)
        {
            red();
            printf("record not found\n");
            yellow();
        }
        system("pause");
        fclose(fd);
        break;
    case 3:
        printf("Enter member ID > ");
        cyan();
        scanf("%s", &temp);

        for (int k = 0; k < strlen(temp); k++)
        {
            if (isalpha(temp[k]))
            {
                temp[k] = toupper(temp[k]);
            }
        }
        displaytop();
        for (int i = 0; i < booking; i++)
        {
            if (strcmp(book[i].memberID, temp) == 0)
            {
                reset();
                printf("%-10s  %-10s   %-12s  %-12s  %-10s  %-7s %-7s %-6.2lf  %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
                invalid = invalid + 1;

            }
        }

        if (invalid == 0)
        {
            red();
            printf("record not found\n");
            yellow();
        }
        system("pause");
        break;
    case 4:
        displaytop();
        for (int i = 0; i < booking; i++)
        {
            reset();
            printf("%-10s  %-10s   %-12s  %-12s  %-10s  %-7s %-7s %-6.2lf  %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
        }
        system("pause");

    }

    return 0;


}

int changestatus() {

    int booking = addintoarray();

    int i;
    char bookingID[10];
    system("cls");
    yellow();
    printf("Enter booking ID > ");
    rewind(stdin);
    cyan();
    scanf("%s", &bookingID);
    yellow();
    //make all become uppercase
    for (int k = 0; k < strlen(bookingID); k++)
    {
        if (isalpha(bookingID[k]))
        {
            bookingID[k] = toupper(bookingID[k]);
        }
    }
    //find the booking details
    int error;
    for (i = 0; i < booking; i++)
    {
        if (strcmp(book[i].bookingID, bookingID) == 0)
        {
            printf("%s  %s %s %s %s %s %s %6.2lf %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
            error = 0;
            break;

        }
        else
            error = 1;
    }

    if (error == 1)
    {
        printf("no record found\n");
        system("pause");
        return 0;
    }
    //change payment details
    char paid;
    if (error == 0)
    {
        do {
            printf("type Y if the payment done, type N if not > ");
            rewind(stdin);
            cyan();
            scanf("%c", &paid);
            yellow();
            paid = toupper(paid);
        } while (paid != 'Y' && paid != 'N');

    }

    book[i].status = paid;

    FILE* fbw = fopen("booking.txt", "w");
    if (fbw == NULL)
    {
        printf("error");

    }
    for (int j = 0; j < booking; j++)
    {
        fprintf(fbw, "%s  %3s %s %12s %12s %5s %5s %6.2lf %c\n", book[j].bookingID, book[j].facID, book[j].currentdate, book[j].bdate, book[j].timeslot, book[j].memberID, book[j].staffID, book[j].fee, book[j].status);

    }
    printf("\nchanged succesfully\n");


    system("pause");

    fclose(fbw);

    return 0;
}

int cancelbooking() {

    int booking = addintoarray();


    char bookingID[10];
    system("cls");
    yellow();
    printf("Enter booking ID > ");
    rewind(stdin);
    cyan();
    scanf("%s", &bookingID);
    yellow();
    //make all become uppercase
    for (int k = 0; k < strlen(bookingID); k++)
    {
        if (isalpha(bookingID[k]))
        {
            bookingID[k] = toupper(bookingID[k]);
        }
    }


    //find the booking details
    int i = 0;
    for (i = 0; i < booking + 1; i++)
    {
        if (strcmp(book[i].bookingID, bookingID) == 0)
        {
            printf("%s  %s %s %s %s %s %s %6.2lf %c\n", book[i].bookingID, book[i].facID, book[i].currentdate, book[i].bdate, book[i].timeslot, book[i].memberID, book[i].staffID, book[i].fee, book[i].status);
            break;

        }
    }

    char  temp;


    printf("type Y to cancel, type any key to cancel the request > ");
    rewind(stdin);
    cyan();
    scanf("%c", &temp);
    temp = toupper(temp);
    yellow();
    if (temp == 'Y')
    {
        book[i].fee = book[i].fee / 2;
        strcpy(book[i].timeslot, "canceled");
        strcpy(book[i].bdate, "canceled");

        FILE* fbw = fopen("booking.txt", "w");
        if (fbw == NULL)
        {
            printf("error");
        }

        for (int j = 0; j < booking; j++)
        {
            fprintf(fbw, "%s  %3s %s %12s %12s %5s %5s %6.2lf %c\n", book[j].bookingID, book[j].facID, book[j].currentdate, book[j].bdate, book[j].timeslot, book[j].memberID, book[j].staffID, book[j].fee, book[j].status);

        }
        printf("\ncancel succesfully\n");
        fclose(fbw);
    }

    system("pause");


}

int earningreport() {
    system("cls");

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    int day[99], month[99], year[99];

    int booking = addintoarray();

    double total = 0;
    for (int i = 0; i < booking + 1; i++)
    {
        total = total + book[i].fee;
    }


    double annualmaintance = 150;
    do {
        yellow();
        printf("Enter the maintance fees > ");
        cyan();
        scanf("%lf", &annualmaintance);
        yellow();
        if (annualmaintance < 0) {

            printf("invalid");
            system("pause");
            system("cls");
        }

    } while (annualmaintance < 0);


    system("cls");
    printf("\tEarning Report\t\t\t%02d-%02d-%4d\n", tm.tm_mday, tm.tm_mon, tm.tm_year + 1990);
    printf("-----------------------------------------------------\n");
    printf("\ttotal booking  = %d\n", booking);
    printf("\ttotal earning  = RM%-6.2lf\n", total);
    printf("\tmaintenance    = RM%-6.2lf\n", annualmaintance);
    printf("\ttotal profit   = RM%-6.2lf\n\n", total - annualmaintance);


    system("pause");


}

int addintoarray() {

    FILE* fb = fopen("booking.txt", "r");

    if (fb == NULL) {
        red();
        printf("Error!!");
        reset();
    }
    int booking = 0;

    while (!feof(fb))
    {
        fscanf(fb, "%s  ", book[booking].bookingID);
        fscanf(fb, "%s ", book[booking].facID);
        fscanf(fb, "%s ", book[booking].currentdate);
        fscanf(fb, "%s ", book[booking].bdate);
        fscanf(fb, "%s ", book[booking].timeslot);
        fscanf(fb, "%s ", book[booking].memberID);
        fscanf(fb, "%s ", book[booking].staffID);
        fscanf(fb, "%lf ", &book[booking].fee);
        fscanf(fb, "%s\n", &book[booking].status);

        booking++;

    }
    fclose(fb);
    return booking;

}

int displaytop() {
    yellow();
    printf(" bookingID  facilityID   currentdate   booking date   timeslot  memberID staffID  fees   status\n");
    printf("========== ==========    ============  ============  ========== =======  ======= ======= ======\n");
    reset();
}

int bookinggenerateID() {

    FILE* fp = fopen("booking.txt", "r");
    if (fp == NULL)
    {
        printf("unable to open file\n");
        exit(0);
    }

    int count = 0;  // Line counter (result)
    char c;  // To store a character read from file

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') // Increment count if this character is newline
        {
            count = count + 1;
        }
    }

    fclose(fp);
    return count;

}

int validationOfDate() {

    FILE* fd = fopen("date.txt", "w");
    if (fd == NULL)
    {
        printf("error");
        exit(0);
    }

    int  key = 0, temp = 0;

    int day, month, year;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("current date > %2d-%2d-%4d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("\n\nenter booking day > ");
    cyan();
    scanf("%d", &day);
    yellow();
    printf("enter booking month > ");
    cyan();
    scanf("%d", &month);
    yellow();
    printf("enter booking year > ");
    cyan();
    scanf("%d", &year);
    yellow();

    printf("\nvalidating the date...\n");

    if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11))
        temp = 1;
    else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 8 || month == 10 || month == 12))
        temp = 1;
    else if ((day >= 1 && day <= 28) && month == 2)
        temp = 1;
    else if ((day >= 1 && day <= 29) && month == 2 && year % 4 == 0)
        temp = 1;

    if (temp == 1)
    {
        if (year == tm.tm_year + 1900 || year >= tm.tm_year + 1900)
        {
            if (month >= tm.tm_mon + 1 && month <= 12)//validate on month
            {
                if (day - tm.tm_mday >= 1 && month >= tm.tm_mon + 1) //more day same month
                    key = 1;
                else if (day == tm.tm_mday && month > tm.tm_mon + 1)//same day more month
                    key = 1;
                else if (day<tm.tm_mday && month > tm.tm_mon + 1) //less day more month
                    key = 1;
            }
        }
    }

    if (key == 0)
    {
        printf("\n\nInvalid date\n\n");
        system("pause");
        system("cls");
    }
    else if (temp == 1 && key == 1)
    {
        fprintf(fd, "%02d-%02d-%4d", day, month, year);
        printf("\nvalidation complete");
    }


    fclose(fd);
    return key;
}

int choosefacility(char* facID[4]) {

    int choice;
    system("cls");
    FILE* ff = fopen("facility.bin", "rb");
    if (ff == NULL)
    {
        printf("error");
        exit(0);
    }


    int i = 0;
    do {
        while (fread(&facdet[i], sizeof(facdet[i]), 1, ff) != 0)
        {

            printf("\t[%02d] %s\n", i + 1, facdet[i].descrip);
            i++;
        }
        do
        {
            printf("\n\tEnter your choice > ");
            cyan();
            scanf("%d", &choice);
            yellow();
        } while (choice > i + 1);
        printf("\t");
        system("pause");
        system("cls");
    } while (choice > i + 1 || choice < 1);
    strcpy(facID, facdet[choice - 1].fac_id);
    return 0;
}

int adjustedtimeslot(char facID[4]) {

    FILE* ft = fopen("timeslot.txt", "r"); //extract timeslot and facID
    FILE* fd = fopen("date.txt", "r"); // extract date to compare
    FILE* fat = fopen("adjusted timeslot.txt", "w"); //store into it

    if (ft == NULL || fd == NULL || fat == NULL)
    {
        printf("error");
    }

    //scan booking 
    int booking = addintoarray();

    //scan timeslot.txt
    int totaloftimeslot;
    int w = 0;
    while (!feof(ft))
    {
        fscanf(ft, "ID :%s\n", fac[w].facilityID);
        for (totaloftimeslot = 0; totaloftimeslot < 5; totaloftimeslot++)
        {
            fscanf(ft, "%s\n", fac[w].time[totaloftimeslot].timeslot);
        }
        fscanf(ft, "\n");
        w++;
    }

    //scan date
    char date[15];
    fscanf(fd, "%s", &date);


    //save timeslot into file
    for (int i = 0; i < booking + 1; i++)
    {
        if (strcmp(fac[i].facilityID, facID) == 0)
        {
            printf("%s", facID);
            for (int p = 0; p < 5; p++)
            {
                if ((strcmp(date, book[i].bdate) == 0) && (strcmp(book[i].timeslot, fac[i].time[p].timeslot) == 0))
                    fprintf(fat, "%s\n", "this slot is booked");
                else
                    fprintf(fat, "%s\n", fac[i].time[p].timeslot);

            }
            break;
        }

    }

    fclose(ft);
    fclose(fd);
    fclose(fat);
    return 0;
}

int displaytimeslot(char* slot[10]) {

    FILE* fat = fopen("adjusted timeslot.txt", "r");

    if (fat == NULL)
    {
        printf("error");
        exit(0);
    }

    timeslot adj[99];

    int i = 0;
    int option;
    char temp[20] = "this slot is booked";

    do
    {
        system("cls");
        printf("\n");
        while (!feof(fat))
        {
            fscanf(fat, "%[^\n]\n", adj[i].timeslot);
            printf("[%d] %s\n", i + 1, adj[i].timeslot);
            i++;
        }
        printf("enter the booking slot > ");
        rewind(stdin);
        cyan();
        scanf("%d", &option);
        yellow();
        strcpy(slot, adj[option - 1].timeslot);

    } while (strcmp(temp, slot) == 0 || option > 5 || option < 1);

    fclose(fat);
    return 0;

}

int calculatefees(char facID[4], double* fee, char* paid)
{

    FILE* fp = ("price.txt", "a");
    if (fp == NULL)
    {
        printf("error");
    }
    double total = 0;

    if (strcmp(facID, "SP1") == 0)
    {
        total = swimming;
    }
    else if (strcmp(facID, "KA1") == 0 || strcmp(facID, "KA2") == 0)
    {
        total = kaeraoke;
    }
    else if (strcmp(facID, "DR1") == 0 || strcmp(facID, "DR1") == 0)
    {
        total = dancing;
    }
    else if (strcmp(facID, "BC1") == 0 || strcmp(facID, "BC2") == 0)
    {
        total = basketball;
    }
    else if (strcmp(facID, "AR1") == 0 || strcmp(facID, "AR2") == 0)
    {
        total = archery;
    }
    else if (strcmp(facID, "MR1") == 0)
    {
        total = meeting;
    }
    total = total * maintance;
    double temp;
    yellow();
    printf("\n\ntotal = %.2lf\n", total);

    char temp1;
    do {
        printf("paid? (Y/N) > ");
        rewind(stdin);
        cyan();
        scanf("%c", &temp1);
        
        temp1 = toupper(temp1);
    } while (temp1 != 'Y' && temp1 != 'N');

    *paid = temp1;
    *fee = total;
    return 0;

}

int validationofdate2() {


    FILE* fd = fopen("date.txt", "w");
    if (fd == NULL)
    {
        printf("error");
        exit(0);
    }

    int day, month, year;
    int temp = 0;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("current date > %2d-%2d-%4d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);


    printf("\n\nenter booking day > ");
    cyan();
    scanf("%d", &day);
    yellow();
    printf("enter booking month > ");
    cyan();
    scanf("%d", &month);
    yellow();
    printf("enter booking year > ");
    cyan();
    scanf("%d", &year);
    yellow();

    printf("\nvalidating the date...\n");
    if (year >= tm.tm_year + 1900) {
        if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11))
            temp = 1;
        else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 8 || month == 10 || month == 12))
            temp = 1;
        else if ((day >= 1 && day <= 28) && month == 2)
            temp = 1;
        else if ((day >= 1 && day <= 29) && month == 2 && year % 4 == 0)
            temp = 1;
    }



    if (temp == 1)
    {
        fprintf(fd, "%02d-%02d-%4d", day, month, year);
        printf("\nvalidation complete");
    }
    else
    {
        printf("\n\nInvalid date\n\n");
        system("pause");
        system("cls");

    }
    fclose(fd);
    return temp;

}

int validationOfmemberID(int* memberID)
{
    system("cls");
    struct member mbrs[99];

    FILE* fm = fopen("memberInfo.txt", "r");

    if (fm == NULL) {
        printf("Error unable to open file!");
    }

    int i = 0, invalid = 1, member;

    do {
        system("cls"); 
        yellow();
        printf("enter member ID > ME");
        rewind(stdin);
        cyan();
        scanf("%d", &member);
        yellow();
        while (!feof(fm)) {
            fscanf(fm, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs[i].id, &mbrs[i].name, &mbrs[i].gender, &mbrs[i].ic, &mbrs[i].contactNum, &mbrs[i].d.regDate, &mbrs[i].d.expDate, &mbrs[i].address);
            i++;
        }

        for (int a = 0; a < i; a++)
        {
            if (mbrs[a].id == member)
            {
                printf("validation complete\n");
                *memberID = member;
                invalid = 0;
                break;
            }
            else
                invalid = 1;
        }
        if (invalid == 1)
        {
            printf("member ID not found\n");
        }
        system("pause");

    } while (invalid == 1);

    fclose(fm);
}


// member module
void membermain() {
    system("cls");
    int menu1;

    do
    {
        yellow();
        printf("Member Infromation Menu : \n");
        printf("[1] Display member information\n");
        printf("[2] Add new member\n");
        printf("[3] Search member\n");
        printf("[4] Modify member information\n");
        printf("[5] Delete member information\n");
        printf("[6] Report\n");
        printf("[0] Back to main menu \n");

        do
        {
            printf("Please select one of the above : ");
            cyan();
            scanf("%d", &menu1);
            yellow();
            printf("\n");

            if (menu1 < 0 || menu1 > 7)
            {
                red();
                printf("Please enter 1 to 7 ONLY!!!\n");
                yellow();
            }
        } while (menu1 < 0 || menu1 > 7);

        system("cls");

        switch (menu1)
        {
        case 1:
            displayMember();
            break;

        case 2:
            addMember();
            break;

        case 3:
            searchMember();
            break;

        case 4:
            membermodify();
            break;

        case 5:
            memberdelete();
            break;

        case 6:
            memberreport();
            break;

        case 0:
            menu();
            break;
        }

        system("pause");
        system("cls");
    } while (1);
}

void displayMember() {
    // array struct
    struct member mbrs[50];

    int i = 0, total = 0;

    //declare file
    FILE* fpDis;
    fpDis = fopen("memberInfo.txt", "r");

    //validate file
    if (fpDis == NULL) {
        printf("Error unable to open file!");
    }

    printf("Member ID Name\t\t\tGender \t I.C. \t\tContact Number\tDate of Register Date of Expiry\tAddress\n");
    printf("========= ========\t\t====== \t ==== \t\t==============\t================ ==============\t========\n");

    while (!feof(fpDis)) {
        fscanf(fpDis, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs[i].id, &mbrs[i].name, &mbrs[i].gender, &mbrs[i].ic, &mbrs[i].contactNum, &mbrs[i].d.regDate, &mbrs[i].d.expDate, &mbrs[i].address);
        total += 1;
        i++;
    }

    for (int a = 0; a < total; a++)
    {
        printf("ME%d \t  %-20s\t%c \t %-14s %-12s\t%-10s\t%10s\t%-s\n", mbrs[a].id, mbrs[a].name, mbrs[a].gender, mbrs[a].ic, mbrs[a].contactNum, mbrs[a].d.regDate, mbrs[a].d.expDate, mbrs[a].address);
    }

    fclose(fpDis);
}

void addMember() {
    struct member mbrs;
    char condition;
    int check1;
    GetLocalTime(&t);

    //declare file
    FILE* fpAdd;
    fpAdd = fopen("memberInfo.txt", "a");

    //validate file
    if (fpAdd == NULL) {
        printf("Error unable to open file!");
    }

    do
    {

        //Generate Id
        mbrs.id = membergenerateId();
        printf("Member ID : ME%d\n", mbrs.id);

        //Name
        strcpy(mbrs.name, getValidname());

        //Get Valid Gender
        getValidGender(&mbrs.gender);

        //Get Valid IC
        strcpy(mbrs.ic, getValidIc());

        //Get Valid Contact Number
        strcpy(mbrs.contactNum, getValidContactNum());

        //Address
        printf("Address : ");
        rewind(stdin);
        cyan();
        gets(mbrs.address);
        yellow();

        //looping for more record
        printf("Anymore record?(Y/N) : ");
        rewind(stdin);
        cyan();
        scanf("%c", &condition);
        yellow();

        fprintf(fpAdd, "ME%d %s|%c %s %s %d-%d-%d|%d-%d-%d|%s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, t.wDay, t.wMonth, t.wYear, t.wDay, t.wMonth, t.wYear + 1, mbrs.address);

        //Making it more tidy (JUST A LINE SPACE)
        if (condition == 'Y' || condition == 'y')
        {
            printf("\n");
        }

    } while (condition == 'Y' || condition == 'y');
    
    fclose(fpAdd);

}

void searchMember() {
    struct member mbrs;
    int nameSearch;
    int search = 0;

    FILE* fpSearch;
    fpSearch = fopen("memberInfo.txt", "r");

    if (fpSearch == NULL) {
        printf("Error unable to open file!");
        exit(-1);
    }

    displayMember();

    printf("Enter member ID for search : ME");
    cyan();
    scanf("%d", &nameSearch);
    yellow();

    while (!feof(fpSearch)) {
        fscanf(fpSearch, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);

        if (nameSearch == mbrs.id) {
            system("cls");
            printf("Member ID Name\t\t\tGender \t I.C. \t\tContact Number\tDate of Register Date of Expiry\tAddress\n");
            printf("========= ========\t\t====== \t ==== \t\t==============\t================ ==============\t========\n");
            printf("ME%d \t  %-20s\t%c \t %-14s %-12s\t%-10s\t%10s\t%-s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
            search = 1;
        }
    }
    if (search == 0)
    {
        red();
        printf("\nID not found.\n\n");
        yellow();
    }

    fclose(fpSearch);
}

void membermodify() {
    struct member mbrs;
    int modifyId, found = 0;
    int cond;

    displayMember();
    printf("\n");

    FILE* fpModify, * temp;
    fpModify = fopen("memberInfo.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fpModify == NULL || temp == NULL) {
        printf("Error unable to open file!");
        exit(-1);
    }

    printf("Enter a member ID : ME");
    rewind(stdin);
    cyan();
    scanf("%d", &modifyId);
    yellow();

    while (!feof(fpModify))
    {
        fscanf(fpModify, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);

        if (modifyId == mbrs.id) {
            found = 1;

            
            printf("[1] Name\n");
            printf("[2] Gender\n");
            printf("[3] IC\n");
            printf("[4] Contact Number\n");
            printf("[5] Address\n");

            do
            {
                printf("Choose an number for modification : ");
                cyan();
                scanf("%d", &cond);
                yellow();

                if (cond < 1 || cond > 5) {
                    red();
                    printf("Please enter a number from 1 to 5.\n");
                    yellow();
                }
            } while (cond < 1 || cond > 5);
            cyan();

            switch (cond)
            {
            case 1:
                strcpy(mbrs.name, getValidname());
                break;
            case 2:
                //Get Valid Gender
                getValidGender(&mbrs.gender);
                break;
            case 3:
                //Get Valid IC
                strcpy(mbrs.ic, getValidIc());
                break;
            case 4:
                //Get Valid Contact Number
                strcpy(mbrs.contactNum, getValidContactNum());
                break;
            case 5:
                //Get Address
                yellow();
                printf("Enter a new Address : ");
                rewind(stdin);
                cyan();
                gets(mbrs.address);
                break;
            default:
                break;
            }
        }
        yellow();
        fprintf(temp, "ME%d %s|%c %s %s %s|%s|%s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
    }
    fclose(fpModify);
    fclose(temp);

    if (found == 1)
    {
        fpModify = fopen("memberInfo.txt", "w");
        temp = fopen("temp.txt", "r");

        while (!feof(temp))
        {
            fscanf(temp, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);
            fprintf(fpModify, "ME%d %s|%c %s %s %s|%s|%s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
        }

        fclose(fpModify);
        fclose(temp);

        printf("Modify successful.\n");
        remove("temp.txt");
    }
    else
    {
        red();
        printf("Id not found!!\n");
        yellow();
    }

    fclose(fpModify);
}

void memberdelete() {
    struct member mbrs;
    int deleteId, found = 0;
    char cond;

    displayMember();
    printf("\n");

    FILE* fpDelete, * temp;
    fpDelete = fopen("memberInfo.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fpDelete == NULL) {
        printf("Error unable to open file!");
        exit(-1);

    }

    printf("Enter a member ID to delete member information  : ME");
    cyan();
    scanf("%d", &deleteId);
    yellow();
    while (!feof(fpDelete))
    {
        fscanf(fpDelete, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);

        if (deleteId == mbrs.id) {

            printf("Are you sure you want to delete (enter 'Y' to delete) : ");
            cyan();
            rewind(stdin);
            scanf("%c", &cond);
            yellow();

            if (cond =='y' || cond == 'Y')
            {
                found = 1;
            }
            else {
                found = 2;
            }

            
        }
        else
        {
            fprintf(temp, "ME%d %s|%c %s %s %s|%s|%s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
        }
    }
    fclose(fpDelete);
    fclose(temp);

    if (found == 1)
    {
        fpDelete = fopen("memberInfo.txt", "w");
        temp = fopen("temp.txt", "r");

        while (!feof(temp))
        {
            fscanf(temp, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);
            fprintf(fpDelete, "ME%d %s|%c %s %s %s|%s|%s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
        }

        fclose(fpDelete);
        fclose(temp);

        printf("Delete successful.\n");
        remove("temp.txt");
    }
    else
    {
        if (found == 2)
        {
            red();
            printf("Delete unsuccessful.\n");
            yellow();
        }
        else if(found == 0) {
            red();
            printf("Id not found!!\n");
            yellow();
        }

    }

    fclose(fpDelete);
}

void memberreport() {
    struct member mbrs;
    int num = 0;

    FILE* fpReport1, * fpReport2;
    GetLocalTime(&t);

    fpReport1 = fopen("memberInfo.txt", "r");
    fpReport2 = fopen("Report.txt", "w");

    //validate file
    if (fpReport1 == NULL || fpReport2 == NULL) {
        printf("Error unable to open file!");
        exit(-1);
    }


    fprintf(fpReport2, "\t\t\tMember Information Report\n");
    fprintf(fpReport2, "\t\tGenerate Date : %d-%d-%d %02d:%02d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
    fprintf(fpReport2, "Member ID Name\t\t\t\t Gender  I.C. \t\t\tContact Number\tDate of Register Date of Expiry\tAddress\n");
    fprintf(fpReport2, "========= ========\t\t\t ======  ==== \t\t\t==============\t================ ==============\t========\n");

    while (!feof(fpReport1)) {
        fscanf(fpReport1, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);
        fprintf(fpReport2, "ME%d \t  %-20s\t%c\t %-13s  %-12s\t%-10s\t\t%10s\t\t%-s\n", mbrs.id, mbrs.name, mbrs.gender, mbrs.ic, mbrs.contactNum, mbrs.d.regDate, mbrs.d.expDate, mbrs.address);
    }

    fprintf(fpReport2, "\nTotal Records : %d", membernumOfRecord(num));

    fclose(fpReport1);
    fclose(fpReport2);
    yellow();
    printf("Report generated.\n");
}

int membergenerateId() {
    static struct member mbrs;

    //declare file
    FILE* fpId;
    fpId = fopen("memberInfo.txt", "r");

    //validate file
    if (fpId == NULL)
    {
        printf("Unable to open file!");
        exit(-1);
    }

    fscanf(fpId, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);

    if (mbrs.id == NULL) {
        mbrs.id = 1001;
    }
    else
    {

        while (!feof(fpId))
        {
            fscanf(fpId, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);
        }
        mbrs.id++;
    }
    fclose(fpId);
    return mbrs.id;
}

int membernumOfRecord(int num) {
    struct member mbrs;

    FILE* fpCount;

    fpCount = fopen("memberInfo.txt", "r");

    if (fpCount == NULL)
    {
        printf("Unable to open file!");
        exit(-1);
    }

    while (!feof(fpCount)) {
        fscanf(fpCount, "ME%d %[^|]|%c %s %s %[^|]|%[^|]|%[^\n]\n", &mbrs.id, &mbrs.name, &mbrs.gender, &mbrs.ic, &mbrs.contactNum, &mbrs.d.regDate, &mbrs.d.expDate, &mbrs.address);
        num++;
    }
    fclose(fpCount);

    return num;
}

//staff module

int smenu() {
    int smenuchoice;
    while (1)
    {
        yellow();
        system("cls");
        do {
            printf("\t\tStaff Menu Page\n");
            printf("-----------------------------------------------------------\n");
            printf("Please select a number : \n");
            printf("\t [1] Add Staff Details\n");
            printf("\t [2] Search Staff details \n");
            printf("\t [3] Display staff details\n");
            printf("\t [4] Modify Staff Details\n");
            printf("\t [5] Delete Staff Details\n");
            printf("\t [6] Generate staff report\n");
            printf("\t [7] Calculate OT\n");
            printf("\t [0] Back to main menu\n");

            printf("Enter your option :");
            cyan();
            scanf("%d", &smenuchoice);
            yellow();
        } while (smenuchoice < 0 || smenuchoice>7);

        switch (smenuchoice) {
        case 1:
            sadd();
            printf("\033[0m");       //default colour
            break;
        case 2:
            system("cls");
            staffsearchID();
            break;
        case 3:
            sdisplay();
            break;
        case 4:
            system("cls");
            smodify();
            break;
        case 5:
            system("cls");
            sDelete();
            break;
        case 6:
            system("cls");
            sreport();
            break;
        case 7:
            system("cls");
            CalculateOT();
            break;
        case 0:
            printf("\033[0m");
            menu();
            break;

        }
    }


}

void sadd() {
    char cont;
    system("cls");

    do {
        Sinfo();
        printf("Anymore record? Y/N :");
        rewind(stdin);
        cyan();
        scanf("%c", &cont);
        yellow();
        cont = toupper(cont);
    } while (cont == 'Y');
}

int Sinfo() {
    int checkSName;

    int i = 1;
    StaffInfo sinfo;
    //open f
    FILE* fstaff;
    fstaff = fopen("staff.txt", "a");
    //validate f
    if (fstaff == NULL)
    {
        printf("Error! Unable to open file!");
    }


    printf("Add staff details\n");
    printf("------------------------------------------------------\n");
    printf("Please key in your necassary details to the system\n");

    // info
    char next;
    //generate staffID
    sinfo.StaffID = staffgenerateID();


    do {
        //STAFF NAME------------
        strcpy(sinfo.StaffName, getValidname());

        //STAFF PASSWORD------------
        printf("Enter your prefered password : ");
        rewind(stdin);
        cyan();
        scanf("%[^\n]", &sinfo.Spass);
        yellow();
        // IC------
        strcpy(sinfo.sicNo, getValidIc());

        //phone number
        strcpy(sinfo.sphoneNo, getValidContactNum());
        //GENDER------------------------
        char gender;
        getValidGender(&gender);
        if (gender == 'M')
            strcpy(sinfo.StaffGender, "MALE");
        else
            strcpy(sinfo.StaffGender, "FEMALE");

        printf("\n");
        //STAFF POSITION---------------------------------------------
        strcpy(sinfo.StaffPosition, spositionassign());

        //STAFF SALARY
        printf("Enter salary: ");
        cyan();
        scanf("%lf", &sinfo.salary.salary);
        yellow();

        //STAFF PAYRATE
        printf("Enter pay rate: ");
        cyan();
        scanf("%lf", &sinfo.salary.payrate);
        yellow();

        printf("%15s %8s %-14s %12s %-7s %-10s %.2lf %.2lf", sinfo.StaffName, sinfo.Spass, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffGender, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
        printf("\nEnter Y if the details is correct > ");
        rewind(stdin);
        cyan();
        scanf("%c", &next);
        yellow();

        next = toupper(next);
    } while (next != 'Y');


    //write f
    fprintf(fstaff, "SF%03d\t ", sinfo.StaffID);
    fprintf(fstaff, "%-11s||\t", sinfo.Spass);
    fprintf(fstaff, "%-26s||", sinfo.StaffName);
    fprintf(fstaff, "%-14s", sinfo.sicNo);
    fprintf(fstaff, "%-13s", sinfo.sphoneNo);
    fprintf(fstaff, "%-18s|", sinfo.StaffPosition);
    fprintf(fstaff, "%-7s", sinfo.StaffGender);
    fprintf(fstaff, "%.2lf\t", sinfo.salary.salary);
    fprintf(fstaff, "%.2lf\n", sinfo.salary.payrate);

    printf("Record had been saved successfully.\n");
    printf("Your staff ID will be SF%03d\n", sinfo.StaffID);
    system("pause");

    //close f
    fclose(fstaff);
}

int staffsearchID() {
    StaffInfo sinfo;
    int idSearch;
    int search = 0;

    char another = 'Y';
    while (another == 'Y')
    {
        FILE* fstaff;
        fstaff = fopen("staff.txt", "r");

        if (fstaff == NULL) {
            printf("Error unable to open file!");
        }
        printf("Search Staff Page\n");
        printf("----------------------------------------------\n");
        printf("Enter staff ID number to search : SF");
        rewind(stdin);
        cyan();
        scanf("%d", &idSearch);
        yellow();


        while (!feof(fstaff)) {
            fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

            if (idSearch == sinfo.StaffID)
            {

                printf("\n\nID : SF%03d\n", sinfo.StaffID);
                printf("Name : %s\n", sinfo.StaffName);
                printf("IC number : %s\n", sinfo.sicNo);
                printf("Phone Number : %s\n", sinfo.sphoneNo);
                printf("Position : %s\n", sinfo.StaffPosition);
                printf("Gender : %s\n", sinfo.StaffGender);
                printf("Salary: %.2lf\n", sinfo.salary.salary);
                printf("Pay Rate : %.2lf\n", sinfo.salary.payrate);


                search = 1;
            }
        }
        if (search == 0)
        {
            printf("\nID not found.\n\n");
        }
        printf("\nWant to search another record ?(Y/N) :");
        rewind(stdin);
        cyan();
        scanf("%c", &another);
        yellow();

        another = toupper(another);

        fclose(fstaff);
    }
}

int sdisplay() {

    StaffInfo sinfo;
    FILE* fstaff, * fs;
    fstaff = fopen("staff.txt", "r");
    fs = fopen("staff.txt", "r");
    if (fstaff == NULL || fs == NULL) {
        printf("Error opening file!");
    }
    int displaychoice;
    int go;
    char temp[6];
    system("cls");
    while (!feof(fs)) // this part helped by kenneth
    {
        fscanf(fs, "SF%03d\t%[^|]||\t%[^|]||%s%s %[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

        sprintf(temp, "SF%03d", sinfo.StaffID);
        if ((strcmp(staff, temp) == 0) && (strcmp("MANAGER           ", sinfo.StaffPosition) == 0))
        {
            go = 1;
            break;
        }
        else
            go = 0;

        
    }
    fclose(fs);
    if (go == 1)
    {
        system("cls");
        printf("\n\t\Display Page\n");
        printf("-----------------------------------------------------------\n");
        printf("Please select a number : \n");
        printf("\t [1]Staff Info	\n");
        printf("\t [2]Salary Info \n");
        printf("Enter your option :");
        cyan();
        scanf("%d", &displaychoice);
        yellow();

        switch (displaychoice)
        {
        case 1:
            printf("\n\n");
            printf("ID\tPassword    Name\t\t       IC NUMBER      PhoneNumber      Position\t\t  Gender\n");
            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                printf("SF%03d\t", sinfo.StaffID);
                printf("%-12s", sinfo.Spass);
                printf("%-25s %-14s %-14s %-20s %-7s\n", sinfo.StaffName, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffPosition, sinfo.StaffGender);
            }
            fclose(fstaff);
            break;

        case 2:
            printf("\n\n");
            printf("ID\tName\t\t\t\t  Position\t    Salary\tPayrate\n");
            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                printf("SF%03d\t", sinfo.StaffID);
                printf("%20s\t", sinfo.StaffName);
                printf("%-20s", sinfo.StaffPosition);
                printf("%.2lf\t", sinfo.salary.salary);
                printf("%.2lf\n", sinfo.salary.payrate);
            }
            fclose(fstaff);
            break;
        default:
            printf("Your choice is not available");
        }
    }
    else if (go == 0)
    {
        printf("you are not eligible to access\n");
    }
    system("pause");

}

void smodify()
{
    StaffInfo sinfo;
    char another = 'Y';
    while (another == 'Y')
    {
        system("cls");
        FILE* fstaff;
        FILE* temp;
        fstaff = fopen("staff.txt", "r");
        temp = fopen("temp.txt", "w");

        int modifyId, found = 0;

        if (fstaff == NULL || temp == NULL) {
            printf("Error unable to open file!");
            exit(-1);

        }
        printf("\t\tStaff Modify Page\n");
        printf("-----------------------------------------------------------\n");
        printf("Enter a staff ID that needed to be modify: SF");
        cyan();
        scanf("%d", &modifyId);
        yellow();

        while (!feof(fstaff))
        {
            fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

            // Compare the employee id
            if (modifyId == sinfo.StaffID)
            {
                found = 1;
                //---------------------------------
                int checkSName = 0;
                char next;

                int modifychoice;
                int ICkey; int hpkey; char gen;
                do {
                    do {

                        printf("You will be editing (Press 0 if select wrong):\n");
                        printf("%15s %8s %-14s %12s %-7s %-10s %.2lf %.2lf\n", sinfo.StaffName, sinfo.Spass, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffGender, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);

                        printf("Please select deletails to be modified : \n");
                        printf("\t [1] Name\n");
                        printf("\t [2] Password \n");
                        printf("\t [3] IC Number\n");
                        printf("\t [4] Telephone number\n");
                        printf("\t [5] Position\n");
                        printf("\t [6] Gender\n");
                        printf("\t [7] Salary\n");
                        printf("\t [8] Pay Rate\n");
                        printf("\t [0] Back to main menu\n");

                        printf("Enter your option :");
                        cyan();
                        scanf("%d", &modifychoice);
                        yellow();

                    } while (modifychoice < 0 || modifychoice>8);
                    char gender;
                    switch (modifychoice) {
                    case 1:
                        strcpy(sinfo.StaffName, getValidname());
                        break;
                    case 2:
                        //STAFF PASSWORD------------
                        printf("Enter your prefered password : ");
                        rewind(stdin);
                        cyan();
                        scanf("%[^\n]", &sinfo.Spass);
                        yellow();

                        break;
                    case 3:
                        // IC------

                        strcpy(sinfo.sicNo, getValidIc());
                        break;

                    case 4:

                        ////phone number
                        strcpy(sinfo.sphoneNo, getValidContactNum());
                        break;

                    case 5:
                        //position
                        strcpy(sinfo.StaffPosition, spositionassign());
                        break;

                    case 6:
                        //gender
                        getValidGender(&gender);
                        if (gender == 'M')
                            strcpy(sinfo.StaffGender, "MALE");
                        else
                            strcpy(sinfo.StaffGender, "FEMALE");
                        break;

                    case 7:
                        printf("Enter salary: ");
                        cyan();
                        scanf("%lf", &sinfo.salary.salary);
                        yellow();

                        break;
                    case 8:
                        printf("Enter pay rate: ");
                        cyan();
                        scanf("%lf", &sinfo.salary.payrate);
                        yellow();

                        break;
                    case 0:
                        smenu();
                    default:
                        printf("invalid option");
                        break;
                    }


                    printf("\n");


                    printf("%15s %8s %-14s %12s %-7s %-9s %.2lf %.2lf", sinfo.StaffName, sinfo.Spass, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffGender, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                    printf("\nEnter Y if the details is correct > ");
                    cyan();
                    rewind(stdin);
                    scanf("%c", &next);
                    yellow();
                    next = toupper(next);
                } while (next != 'Y');

            }
            fprintf(temp, "SF%03d\t", sinfo.StaffID);
            fprintf(temp, "%-11s||\t", sinfo.Spass);
            fprintf(temp, "%-26s||", sinfo.StaffName);
            fprintf(temp, "%-14s", sinfo.sicNo);
            fprintf(temp, "%-2s", sinfo.sphoneNo);
            fprintf(temp, "%-20s|", sinfo.StaffPosition);
            fprintf(temp, "%-7s", sinfo.StaffGender);
            fprintf(temp, "%.2lf\t", sinfo.salary.salary);
            fprintf(temp, "%.2lf\n", sinfo.salary.payrate);



        }
        fclose(fstaff);
        fclose(temp);

        if (found == 1)
        {
            fstaff = fopen("staff.txt", "w");
            temp = fopen("temp.txt", "r");

            while (!feof(temp))
            {
                fscanf(temp, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

                fprintf(fstaff, "SF%03d\t", sinfo.StaffID);
                fprintf(fstaff, "%-12s||\t", sinfo.Spass);
                fprintf(fstaff, "%-23s||", sinfo.StaffName);
                fprintf(fstaff, "%-14s", sinfo.sicNo);
                fprintf(fstaff, "%-11s", sinfo.sphoneNo);
                fprintf(fstaff, "%-19s|", sinfo.StaffPosition);
                fprintf(fstaff, "%-7s", sinfo.StaffGender);
                fprintf(fstaff, "%.2lf\t", sinfo.salary.salary);
                fprintf(fstaff, "%.2lf\n", sinfo.salary.payrate);

            }

            fclose(fstaff);
            fclose(temp);

            printf("Modify successful.\n");
            remove("temp.txt");
            system("pause");
        }
        else
        {
            printf("Id not found!!\n");
        }

        fclose(fstaff);

        // Ask for modifying another record
        printf("\nWant to modify another record ?(Y/N) :");
        rewind(stdin);
         cyan();
        scanf("%c", &another);
         yellow();
        another = toupper(another);

    }
}

void sDelete() {         //Delete Staff Profile
    StaffInfo sinfo;
    char another = 'Y';
    while (another == 'Y') {
        FILE* fstaff;
        FILE* temp;
        fstaff = fopen("staff.txt", "r");
        temp = fopen("temp.txt", "w");

        int deleteID, found = 0;
        int modifychoice;

        if (fstaff == NULL || temp == NULL) {
            printf("Error unable to open file!");

        }


        printf("DELETE STAFF INFORMATION\n");
        printf("=====================================================\n");
        printf("Enter a staff ID to be deleted: SF");
        rewind(stdin);
        cyan();
        scanf("%d", &deleteID);
        yellow();
        while (!feof(fstaff))
        {
            fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

            // Compare the employee id
            if (deleteID == sinfo.StaffID) {

                found = 1;
                do {
                    printf("You will be deleting (Press 0 if select wrong):\n");
                    printf("%15s %8s %-14s %12s %-7s %-10s %.2lf %.2lf\n", sinfo.StaffName, sinfo.Spass, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffGender, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                    printf("\t [1] Delete\n");
                    printf("\t [0] Back to main menu\n");

                    printf("Enter your option :");
                    cyan();
                    scanf("%d", &modifychoice);
                    yellow();
                } while (modifychoice < 0 || modifychoice>8);
                switch (modifychoice) {
                case 1:
                    break;
                case 0:
                    smenu();
                    break;
                default:
                    printf("invalid option");
                    break;
                }
            }
            else
            {
                fprintf(temp, "SF%03d\t", sinfo.StaffID);
                fprintf(temp, "%-11s||\t", sinfo.Spass);
                fprintf(temp, "%-26s||", sinfo.StaffName);
                fprintf(temp, "%-14s", sinfo.sicNo);
                fprintf(temp, "%-s", sinfo.sphoneNo);
                fprintf(temp, "%-16s|", sinfo.StaffPosition);
                fprintf(temp, "%-7s", sinfo.StaffGender);
                fprintf(temp, "%.2lf\t", sinfo.salary.salary);
                fprintf(temp, "%.2lf\n", sinfo.salary.payrate);

            }
        }
        //---------------------------------

        fclose(fstaff);
        fclose(temp);

        if (found == 1)
        {
            fstaff = fopen("staff.txt", "w");
            temp = fopen("temp.txt", "r");

            while (!feof(temp))
            {
                fscanf(temp, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

                fprintf(fstaff, "SF%03d\t", sinfo.StaffID);
                fprintf(fstaff, "%-12s||\t", sinfo.Spass);
                fprintf(fstaff, "%-26s||", sinfo.StaffName);
                fprintf(fstaff, "%-14s", sinfo.sicNo);
                fprintf(fstaff, "%-s", sinfo.sphoneNo);
                fprintf(fstaff, "%-16s|", sinfo.StaffPosition);
                fprintf(fstaff, "%-7s", sinfo.StaffGender);
                fprintf(fstaff, "%.2lf\t", sinfo.salary.salary);
                fprintf(fstaff, "%.2lf\n", sinfo.salary.payrate);

            }

            fclose(fstaff);
            fclose(temp);

            printf("Delete successful.\n");
            remove("temp.txt");
            system("pause");
        }
        else
        {
            printf("ID not found!!\n");
        }

        fclose(fstaff);

        printf("\nWant to delete another record ?(Y/N) :");
        cyan();
        rewind(stdin);
        scanf("%c", &another);
         yellow();
        another = toupper(another);
    }

}

void sreport() {
    StaffInfo sinfo;
    FILE* fstaff, * fs;
    fstaff = fopen("staff.txt", "r");
    fs = fopen("staff.txt", "r");

    if (fstaff == NULL || fs == NULL) {
        printf("Error opening file!");
    }

    int reportchoice;
    int go;
    char temp[6];
    
    while (!feof(fs)) // this part helped by kenneth
    {
        fscanf(fs, "SF%03d\t%[^|]||\t%[^|]||%s%s %[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

        sprintf(temp, "SF%03d", sinfo.StaffID); 
        if ((strcmp(staff, temp) == 0) && (strcmp("MANAGER           ", sinfo.StaffPosition) == 0))
        {
            go = 1;
            break;
        }
        else
            go = 0;
        
    }
    fclose(fs);
    if (go == 1)
    {
        printf("\t\tStaff Report Page\n");
        printf("-----------------------------------------------------------\n");
        printf("Please select report type: \n");
        printf("\t [1] Total Staff Report\n");
        printf("\t [2] Staff Salary Report \n");
        printf("\t [0] Back to main menu\n");

        printf("Enter your option :");
        cyan();
        scanf("%d", &reportchoice);
        yellow();
        switch (reportchoice)
        {
        case 1:
            system("cls");
            printf("\a");		//To inform user a invoice is created
            system("color F0"); //black and white color so that it will look invoice printed on paper
            printf("\n\n\t\t\tTotal Staff Report\n");
            printf("____________________________________________________________________________________________\n");

            int totalstaff = staffgenerateID() - 1;
            printf("ID\tName\t\t           IC NUMBER      PhoneNumber      Position\t      Gender\n");


            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                printf("SF%03d\t", sinfo.StaffID);
                printf("%-25s %-14s %-14s %-20s %-7s\n", sinfo.StaffName, sinfo.sicNo, sinfo.sphoneNo, sinfo.StaffPosition, sinfo.StaffGender);

            }
            printf("____________________________________________________________________________________________\n");
            printf("End of report.\n");
            printf("Total Staff : %d\n\n\n\n", totalstaff);
            fclose(fstaff);
            system("pause");
            printf("\033[0;33m");    //yellow colour
            break;
        case 2:
            system("cls");
            printf("\a");		//To inform user a invoice is created
            system("color F0"); //black and white color so that it will look invoice printed on paper
            printf("\n\t\t\tStaff Salary Report\n");
            printf("_____________________________________________________________________\n");
            printf("\Report generated: %s", ctime(&tm)); //showcase time
            printf("ID\tName\t\t             Position\t      Salary\n");

            printf("Salary <1000\n");
            printf("--------------------------------------------------------------------\n");

            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                if (sinfo.salary.salary < 1000.00) {
                    printf("SF%03d\t", sinfo.StaffID);
                    printf("%-25s %-20s %.2lf %.2lf\n", sinfo.StaffName, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                }
            }
            printf("\nSalary 1000-1999\n");
            printf("--------------------------------------------------------------------\n");
            fclose(fstaff);

            fstaff = fopen("staff.txt", "r");

            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                if (sinfo.salary.salary < 2000.00 && sinfo.salary.salary >= 1000) {
                    printf("SF%03d\t", sinfo.StaffID);
                    printf("%-25s %-20s %.2lf %.2lf\n", sinfo.StaffName, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                }
            }
            printf("\nSalary 2000-2999\n");
            printf("--------------------------------------------------------------------\n");
            fclose(fstaff);
            fstaff = fopen("staff.txt", "r");
            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                if (sinfo.salary.salary < 3000.00 && sinfo.salary.salary >= 2000.00) {
                    printf("SF%03d\t", sinfo.StaffID);
                    printf("%-25s %-20s %.2lf %.2lf\n", sinfo.StaffName, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                }
            }
            printf("\nSalary 3000-3999\n");
            printf("--------------------------------------------------------------------\n");
            fclose(fstaff);
            fstaff = fopen("staff.txt", "r");
            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                if (sinfo.salary.salary < 4000.00 && sinfo.salary.salary >= 3000.00)
                {
                    printf("SF%03d\t", sinfo.StaffID);
                    printf("%-25s %-20s %.2lf %.2lf\n", sinfo.StaffName, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                }
            }
            printf("\nSalary >=4000\n");
            printf("--------------------------------------------------------------------\n");
            fclose(fstaff);
            fstaff = fopen("staff.txt", "r");
            while (!feof(fstaff))
            {
                fscanf(fstaff, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
                if (sinfo.salary.salary >= 4000.00) {
                    printf("SF%03d\t", sinfo.StaffID);
                    printf("%-25s %-20s %.2lf %.2lf\n", sinfo.StaffName, sinfo.StaffPosition, sinfo.salary.salary, sinfo.salary.payrate);
                }

            }
            printf("_____________________________________________________________________\n");
            printf("End of report.\n");
            fclose(fstaff);
            system("pause");
            printf("\033[0;33m");    //yellow colour

        case 0:
            smenu();
        default:
            printf("Your choice is not available");
        }
    }
    else if (go == 0)
    {
        printf("you are not eligible to access\n");
        system("pause");
    }
    
}

char* spositionassign() {
    StaffInfo sinfo;
    int choice;
    do
    {
        printf("Position\n");
        printf("--------------------------\n");
        printf("[1] Admin\n");
        printf("[2] Manager\n");
        printf("[3] HR Staff\n");
        printf("[4] Clerk\n");
        printf("[5] Front desk\n");
        printf("[6] Facility officer\n");
        printf("[7] Equipment officer\n");
        printf("Enter Position :");
        cyan();
        rewind(stdin);
        scanf("%d", &choice);
        yellow();

        switch (choice)
        {
        case 1:
            strcpy(sinfo.StaffPosition, "ADMIN");
            break;
        case 2:
            strcpy(sinfo.StaffPosition, "MANAGER");
            break;
        case 3:
            strcpy(sinfo.StaffPosition, "HR STAFF");
            break;
        case 4:
            strcpy(sinfo.StaffPosition, "CLERK");
            break;
        case 5:
            strcpy(sinfo.StaffPosition, "FRONT DESK");
            break;
        case 6:
            strcpy(sinfo.StaffPosition, "FACILITY OFFICER");
            break;
        case 7:
            strcpy(sinfo.StaffPosition, "EQUIPMENT OFFICER");
            break;
        default:
            printf("invalid option");
            break;
        }
    } while (choice > 7);

    return sinfo.StaffPosition;
}

double calculateOT(int wrkHrs, float rate, float otrate)

{
    double OT = 0;
    OT = wrkHrs * rate * otrate;
    return(OT);

}

void CalculateOT() {
    double OT, total;
    int hrs;
    float rate, otrate;
    int OTchoice;
    printf("Calculate OT\n");
    printf("================================================\n");
    printf("Enter Overtime hour: ");
    scanf("%d", &hrs);
    printf("Enter Payrate (2 decimal place): ");
    scanf("%f", &rate);
    printf("Enter OT rate (2 decimal place): ");
    scanf("%f", &otrate);
    OT = calculateOT(hrs, rate, otrate);
    total = OT;

    printf("\n\nTotal OT Pay is RM%.2lf\n", total);

    printf("Calculate again? 1=yes 0=No : ");
    cyan();
    scanf("%d", &OTchoice);
    yellow();
    switch (OTchoice) {
    case 1:
        printf("\n\n\n");
        CalculateOT();
    case 0:
        break;

    default:
        printf("Your choice is not available");
        smenu();				//exit system
        break;
    }
}

int staffgenerateID() {
    StaffInfo sinfo;

    //declare file
    FILE* fpId;
    fpId = fopen("staff.txt", "r");

    //validate file
    if (fpId == NULL)
    {
        printf("Unable to open file!");
        exit(-1);
    }

    fscanf(fpId, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);

    if (sinfo.StaffID == NULL) {
        sinfo.StaffID = 1001;
    }
    else
    {

        while (!feof(fpId))
        {
            fscanf(fpId, "SF%03d\t%[^|]||\t%[^|]||%s%s%[^|]|%s %lf\t%lf\n", &sinfo.StaffID, &sinfo.Spass, &sinfo.StaffName, &sinfo.sicNo, &sinfo.sphoneNo, &sinfo.StaffPosition, &sinfo.StaffGender, &sinfo.salary.salary, &sinfo.salary.payrate);
        }
        sinfo.StaffID++;
    }
    fclose(fpId);
    return sinfo.StaffID;
}


//facilty module

void facmain() {
    system("cls");
    int choice, ent = 0;
    do {
        yellow();
        printf("Facilities\n");
        printf("==========\n");
        printf("1. Add Record\n");
        printf("2. Search record\n");
        printf("3. Display record\n");
        printf("4. Edit Record\n");
        printf("5. Delete Record\n");
        printf("6. Report\n");
        printf("0. Back to main page\n\n");

        yellow();
        printf("Enter your choice: ");
        cyan();
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            searchRecord();
            break;
        case 3:
            displayRecord();
            break;
        case 4:
            editRecord();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            report();
            break;
        case 0:
            menu();
            break;
        default:
            ent++;
            if (ent != 0) {
                red();
                printf("Please enter your choice again\n\n");
            }
        }
    } while (ent);
}

void addRecord() {
    char cont = 'y';
    int i, valid = 0, ent = 0, pov, j, repeat;


    FILE* fptr;
    fptr = fopen("facility.bin", "ab");
    if (fptr == NULL) {
        printf("Error");
        exit(-1);
    }

    i = 0;
    do {
        yellow();
        printf("Enter the type of facility: ");

        rewind(stdin);
        cyan();
        scanf("%[^\n]", facdet[i].type);
        valType(facdet[i].type);
        FILE* fp;
        fp = fopen("facility.bin", "rb");
        if (fp == NULL) {
            printf("Error");
            exit(-1);
        }
        do {
            yellow();
            printf("Enter the ID of facility: ");
            rewind(stdin);
            cyan();
            scanf("%[^\n]", facdet[i].fac_id);
            valID(facdet[i].fac_id);
            j = 1;
            repeat = 0;
            //check for repeated facility id

            while (fread(&facdet[j], sizeof(facdet[j]), 1, fp) != 0) {

                if (strcmp(facdet[j].fac_id, facdet[i].fac_id) == 0) {
                    red();
                    printf("This facility id has been entered. Try another id\n\n");
                    repeat++;
                }

            }

        } while (repeat != 0);
        fclose(fp);
        yellow();
        printf("Enter the venue of facility: ");
        rewind(stdin);
        cyan();
        scanf("%[^\n]", facdet[i].venue);
        valType(facdet[i].venue);

        yellow();
        printf("Enter the description of facility: ");
        rewind(stdin);
        cyan();
        rewind(stdin);
        scanf("%[^\n]", facdet[i].descrip);
        valType(facdet[i].descrip);

        do {
            pov = 0;
            yellow();
            printf("Enter the maximum number of users of facility: ");
            rewind(stdin);
            cyan();
            scanf("%s", &facdet[i].max_user);
            for (int l = 0; l < strlen(facdet[i].max_user); l++)
            {
                if (isdigit(facdet[i].max_user[l]) == 0) {
                    pov++;
                    break;
                }
            }

            if (pov != 0)
            {
                red();
                printf("Please enter only positive number\n");

            }
        } while (pov != 0);//make sure the value entered is positive and is integer

        yellow();
        printf("Enter the opening hours of facility: \n");

        do {
            pov = 0;
            yellow();
            printf("      From: ");
            rewind(stdin);
            cyan();
            scanf("%[^\n]", &facdet[i].hour.from_hour);
            for (int l = 0; l < strlen(facdet[i].max_user); l++)
            {
                if (isdigit(facdet[i].hour.from_hour[l]) == 0) {
                    pov++;
                    break;
                }
            }

            if (pov != 0)
            {
                red();
                printf("Please enter only positive number\n");
            }
        } while (pov != 0);//make sure the value entered is positive and is integer

        do {
            pov = 0;
            yellow();
            printf("      To: ");
            rewind(stdin);
            cyan();
            scanf("%[^\n]", &facdet[i].hour.till_hour);
            for (int l = 0; l < strlen(facdet[i].hour.till_hour); l++)
            {
                if (isdigit(facdet[i].hour.till_hour[l]) == 0) {
                    pov++;
                    break;
                }
            }

            if (pov != 0)
            {
                red();
                printf("Please enter only positive number\n");

            }
        } while (pov != 0);//make sure the value entered is positive and is integer

        yellow();
        printf("%s\n", facdet[i].fac_id);
        addtimeslot(facdet[i].fac_id);
        FILE* fptr;
        fptr = fopen("facility.bin", "ab");
        if (fptr == NULL) {
            printf("Error");
            exit(-1);
        }
        fwrite(&facdet[i], sizeof(facdet[i]), 1, fptr);
        fclose(fptr);
        i++;

        yellow();
        printf("Do you want to continue?(Y=yes): ");
        rewind(stdin);
        cyan();
        scanf("%c", &cont);
        system("cls");
    } while ((cont) == 'Y' || cont == 'y');

    i = i;
    yellow();
    printf("You have added %d record\n\n", i);

    reset();
    backtofacmain();
}

void addtimeslot(char facID[4]) {
    facility fac[99];
    FILE* ft = fopen("timeslot.txt", "a");
    FILE* ftr = fopen("timeslot.txt", "r");
    if (ft == NULL || ftr == NULL)
    {
        printf("error");
    }

    //scan timeslot.txt
    int totaloftimeslot;
    int w = 0;
    while (!feof(ftr))
    {
        fscanf(ftr, "ID :%s\n", fac[w].facilityID);
        for (totaloftimeslot = 0; totaloftimeslot < 5; totaloftimeslot++)
        {
            fscanf(ftr, "%s\n", fac[w].time[totaloftimeslot].timeslot);
        }
        fscanf(ftr, "\n");
        w++;
    }

    w++;
    char timeslot[10];
    int count, r;
    for (int i = 0; i < 5; i++)
    {
        do
        {
            yellow();
            printf("Enter available timeslot %d (XXXX-XXXX)> ", i + 1);
            cyan();
            scanf("%s", &timeslot);
            count = 0;
            for (r = 0; r < strlen(timeslot); r++)
            {
                if (isalpha(timeslot[r]))
                {
                    red();
                    printf("Invalid timeslot\n");
                    break;
                }
                else
                {
                    count++;
                }
                if (timeslot[r] == '-')
                    r++;
                else if (r == 8)
                {

                    strcpy(fac[w].time[i].timeslot, timeslot);
                    break;
                }
            }
        } while (r != 8);

    }

    fprintf(ft, "ID :%s\n", facID);
    for (int k = 0; k < 5; k++)
    {
        fprintf(ft, "%s\n", fac[w].time[k].timeslot);

    }
    fprintf(ft, "\n");
    fclose(ft);
    fclose(ftr);

}

void edittimeslot(char facID[4]) {

    facility fac[99];
    FILE* ftr = fopen("timeslot.txt", "r");

    if (ftr == NULL)
    {
        printf("error");
    }

    //scan timeslot.txt
    int totaloftimeslot;
    int w = 0;
    while (!feof(ftr))
    {

        fscanf(ftr, "ID :%s\n", fac[w].facilityID);
        for (totaloftimeslot = 0; totaloftimeslot < 5; totaloftimeslot++)
        {
            fscanf(ftr, "%s\n", fac[w].time[totaloftimeslot].timeslot);
        }
        fscanf(ftr, "\n");
        w++;
    }
    w = w;

    fclose(ftr);

    char timeslot[10];
    int count, r;

    for (int l = 0; l < w; l++) {

        if (strcmp(facID, fac[l].facilityID) == 0) {

            for (int i = 0; i < 5; i++)
            {
                do
                {
                    yellow();
                    printf("Enter the new available timeslot %d (Total 5) (XXXX-XXXX)> ", i + 1);
                    cyan();
                    scanf("%s", &timeslot);
                    count = 0;
                    for (r = 0; r < strlen(timeslot); r++)
                    {
                        if (isalpha(timeslot[r]))
                        {
                            red();
                            printf("Invalid timeslot\n");
                            break;
                        }
                        else
                        {
                            count++;
                        }
                        if (timeslot[r] == '-')
                            r++;
                        else if (r == 8)
                        {

                            strcpy(fac[w].time[i].timeslot, timeslot);
                            break;
                        }
                    }
                } while (r != 8);

            }

        }

    }
    FILE* ft = fopen("timeslot.txt", "w");
    if (ft == NULL)
    {
        printf("error");
    }


    for (int j = 0; j < w; j++) {
        fprintf(ft, "ID :%s\n", fac[j].facilityID);
        for (int k = 0; k < 5; k++)
        {
            fprintf(ft, "%s\n", fac[j].time[k].timeslot);

        }
        fprintf(ft, "\n");
    }

    fclose(ft);


}

void searchRecord() {
    char type_search[21], id_search[5];
    int cat_search, i, vali = 0, ent = 0;

    FILE* fptr;
    fptr = fopen("facility.bin", "rb");
    if (fptr == NULL) {
        printf("ERROR");
        exit(-1);
    }

    printf("\n");
    do {
        yellow();
        printf("Which category you want to search: ");
        printf("\n1.Type\n");
        printf("2.ID\n");
        cyan();
        scanf("%d", &cat_search);

        system("cls");
        switch (cat_search) {
            //searching using type
        case 1:
            yellow();
            printf("What type are you searching for: ");
            rewind(stdin);
            cyan();
            gets(type_search);
            valType(type_search);


            i = 0;
            while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
                if (strcmp(type_search, facdet[i].type) == 0) {
                    vali++;
                    printf("\n");
                    yellow();
                    printf("ID: %s\nDescription: %s\nVenue: %s\nMaximum Users Allowed:%s\nOpen from %s to %s\n\n", facdet[i].fac_id, facdet[i].descrip, facdet[i].venue, facdet[i].max_user, facdet[i].hour.from_hour, facdet[i].hour.till_hour);
                }
                i++;

            }
            if (vali == 0) {
                red();
                printf("Record Not Found!!\n");
            }
            break;
            //searching using id
        case 2:
            yellow();
            printf("Enter the facility ID: ");
            rewind(stdin);
            cyan();
            gets(id_search);
            valID(id_search);

            i = 0;
            vali = 0;
            while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
                if (strcmp(id_search, facdet[i].fac_id) == 0) {
                    vali++;
                    printf("\n");
                    yellow();
                    printf("Type: %s\nDescription: %s\nVenue: %s\nMaximum Users Allowed:%s\nOpen from %s to %s\n\n", facdet[i].type, facdet[i].descrip, facdet[i].venue, facdet[i].max_user, facdet[i].hour.from_hour, facdet[i].hour.till_hour);
                }
                i++;

            }
            if (vali == 0) {
                red();
                printf("Record Not Found!!\n\n");
            }
            break;


        default:
            ent++;
            if (ent != 0) {
                red();
                printf("Please enter your choice again(1-2)\n\n");
            }
        }
    } while (ent != 0);
    fclose(fptr);
    //exit or go back
    reset();
    backtofacmain();
}

void displayRecord() {

    int i = 0, ent = 0;
    FILE* fptr;
    fptr = fopen("facility.bin", "rb");
    if (fptr == NULL) {
        printf("ERROR");
        exit(-1);
    }

    while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
        yellow();
        printf("%d.\n", i + 1);
        printf("Type:\t\t\t %s\nID:\t\t\t %s\nDescription:\t\t %s\nVenue:\t\t\t %s\nMaximum Users Allowed:   %s\nOpen from\t\t %s to %s\n\n", facdet[i].type, facdet[i].fac_id, facdet[i].descrip, facdet[i].venue, facdet[i].max_user, facdet[i].hour.from_hour, facdet[i].hour.till_hour);
        i++;
    }

    fclose(fptr);
    reset();
    backtofacmain();
}

void editRecord() {

    char edit_id[4], edit;
    int choice, valid = 0, ent = 0, pov;

    FILE* fptr, * fp;
    fptr = fopen("facility.bin", "rb");

    if (fptr == NULL) {
        printf("ERROR");
        exit(-1);
    }
    int i = 0;
    while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
        i++;
    }
    i = i;
    fclose(fptr);
    yellow();
    printf("Enter the facility ID you want to edit: ");
    rewind(stdin);
    cyan();
    gets(edit_id);

    valID(edit_id);



    for (int j = 0; j < i; j++) {
        if (strcmp(edit_id, facdet[j].fac_id) == 0) {
            valid++;
            yellow();
            printf("This is the record you entered: \n");
            printf("Type: %s\nDescription: %s\nVenue: %s\nMaximum Users Allowed:%s\nOpen from %04s to %04s\n\n", facdet[j].type, facdet[j].descrip, facdet[j].venue, facdet[j].max_user, facdet[j].hour.from_hour, facdet[j].hour.till_hour);
            do {
                yellow();
                printf("What do you want to edit?\n");
                printf("1. Type\n");

                printf("2. Description\n");
                printf("3. Venue\n");
                printf("4. Maximum Users Alowed\n");
                printf("5. Open Time and Close Time\n");
                cyan();
                scanf("%d", &choice);
                system("cls");


                //let the user choose category to edit
                switch (choice) {
                case 1:
                    yellow();
                    printf("Enter your new type:");
                    rewind(stdin);
                    cyan();
                    scanf("%[^\n]", &facdet[j].type);
                    valType(facdet[j].type);
                    break;
                case 2:
                    yellow();
                    printf("Enter your new description:");
                    rewind(stdin);
                    cyan();
                    scanf("%[^\n]", &facdet[j].descrip);
                    valType(facdet[j].descrip);
                    break;
                case 3:
                    yellow();
                    printf("Enter your new venue:");
                    rewind(stdin);
                    cyan();
                    scanf("%[^\n]", &facdet[j].venue);
                    valType(facdet[j].venue);
                    break;

                case 4:
                    do {
                        pov = 0;
                        yellow();
                        printf("Enter your new maximum user allowed: ");
                        rewind(stdin);
                        cyan();
                        scanf("%[^\n]", &facdet[j].max_user);



                        for (int l = 0; l < strlen(facdet[j].max_user); l++)
                        {
                            if (isdigit(facdet[j].max_user[l]) == 0) {
                                pov++;
                                break;
                            }
                        }

                        if (pov != 0)
                        {
                            red();
                            printf("Please enter only positive number\n");
                        }
                    } while (pov != 0);
                    break;

                case 5:
                    do {
                        pov = 0;
                        yellow();
                        printf("Enter your new open time: ");
                        rewind(stdin);
                        cyan();
                        scanf("%[^\n]", &facdet[j].hour.from_hour);

                        for (int l = 0; l < strlen(facdet[j].hour.from_hour); l++)
                        {
                            if (isdigit(facdet[j].hour.from_hour[l]) == 0) {
                                pov++;
                                break;
                            }
                        }
                        yellow();
                        printf("Enter your new close time: ");
                        cyan();
                        rewind(stdin);
                        scanf("%[^\n]", &facdet[j].hour.till_hour);

                        for (int l = 0; l < strlen(facdet[j].hour.till_hour); l++)
                        {
                            if (isdigit(facdet[j].hour.till_hour[l]) == 0) {
                                pov++;
                                break;
                            }
                        }
                        if (pov != 0)
                        {
                            red();
                            printf("Please enter only positive number\n");
                            yellow();
                        }




                    } while (pov != 0);
                    break;
                default:
                    ent++;
                    if (ent != 0) {
                        red();
                        printf("Please enter your choice again(1-5)\n\n");
                    }
                }
            } while (ent != 0);
            choice = choice;
            yellow();
            printf("Are you sure you want to edit the record? (Y for yes): ");
            rewind(stdin);
            cyan();
            scanf("%c", &edit);

            if (edit == 'y' || edit == 'Y') {
                if (choice == 5) {//if the user confirm want to edit the open/close time then new available timeslot need to be entered
                    edittimeslot(facdet[j].fac_id);
                }
                fp = fopen("facility.bin", "wb");
                if (fptr == NULL) {
                    printf("ERROR");
                }

                for (int j = 0; j < i; j++)
                    fwrite(&facdet[j], sizeof(facdet[j]), 1, fp);

                fclose(fp);
                yellow();
                printf("You have successfullly edit your record\n\n");
            }
            else {
                yellow();
                printf("Your records remain the same\n\n");
            }
        }



    }
    //if the record is not found
    if (valid == 0) {
        red();
        printf("Record Not Found!!\n\n");
    }





    //exit or go back
    reset();
    backtofacmain();
}

void deleteRecord() {

    int valid = 0, ent = 0, i;
    char delId[4], del;
    FILE* fptr, * temp;
    fptr = fopen("facility.bin", "rb");

    if (fptr == NULL) {
        printf("ERROR");
        exit(-1);
    }

    //read from file
    i = 0;
    while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
        i++;
    }
    fclose(fptr);

    yellow();
    printf("Enter the facility id: ");
    rewind(stdin);
    cyan();
    scanf("%[^\n]", &delId);

    valID(delId);



    for (int j = 0; j < i; j++) {
        if (strcmp(delId, facdet[j].fac_id) == 0) {
            valid++;
            yellow();
            printf("Are you sure you want to delete your records? (Y=yes): ");
            rewind(stdin);
            cyan();
            scanf("%c", &del);
            if (del == 'y' || del == 'Y') {
                yellow();
                printf("You have successfully delete your record\n");
                delInTimeslot(delId);
                temp = fopen("facility.bin", "wb");
                for (int j = 0; j < i; j++) {
                    if (strcmp(delId, facdet[j].fac_id) != 0) {

                        fwrite(&facdet[j], sizeof(facdet[j]), 1, temp);
                    }

                }
                fclose(temp);
            }
            else {
                yellow();
                printf("Your records remain the same\n\n");
            }
        }


    }
    if (valid == 0) {
        red();
        printf("Record Not Found!!\n\n");
    }

    //exit or go back
    reset();
    backtofacmain();
}

int delInTimeslot(char facID[4]) {

    FILE* ftr = fopen("timeslot.txt", "r");

    if (ftr == NULL)
    {
        printf("error");
    }

    //scan timeslot.txt
    int totaloftimeslot;
    int w = 0;
    while (!feof(ftr))
    {
        fscanf(ftr, "ID :%s\n", fac[w].facilityID);
        for (totaloftimeslot = 0; totaloftimeslot < 5; totaloftimeslot++)
        {
            fscanf(ftr, "%s\n", fac[w].time[totaloftimeslot].timeslot);
        }
        fscanf(ftr, "\n");
        w++;
    }

    fclose(ftr);

    FILE* ft = fopen("timeslot.txt", "w");

    if (ft == NULL)
    {
        printf("error");
    }

    for (int j = 0; j < w; j++)
    {
        if (strcmp(fac[j].facilityID, facID) == 0)
        {
            yellow();
            printf("The timeslots are deleted\n");
        }
        else
        {
            fprintf(ft, "ID :%s\n", fac[j].facilityID);
            for (totaloftimeslot = 0; totaloftimeslot < 5; totaloftimeslot++)
            {
                fprintf(ft, "%s\n", fac[j].time[totaloftimeslot].timeslot);
            }
            fprintf(ft, "\n");
        }

    }



    fclose(ft);


}

void report() {
    time_t y;
    y = time(NULL);
    struct tm year = *localtime(&y);
    char title[51] = "Monthly Report For";
    char line[30] = "=============================";
    char title2[51] = "Facility		Venue		Opening Hours";
    char line2[91] = "-----------------------------------------------------";
    int  i;
    FILE* fptr;
    fptr = fopen("facility.bin", "rb");
    if (fptr == NULL) {
        printf("ERROR");
        exit(-1);
    }
    //display report
    yellow();
    printf("%s 0%d-%d\n", title, year.tm_mon + 1, year.tm_year + 1900);
    printf("%s\n", line);
    printf("%s\n", title2);
    printf("%s\n", line2);
    i = 0;
    while (fread(&facdet[i], sizeof(facdet[i]), 1, fptr) != 0) {
        printf("%-16s        %-10s      %s-%s\n", facdet[i].type, facdet[i].venue, facdet[i].hour.from_hour, facdet[i].hour.till_hour);
        i++;
    }

    printf("                                        Total Facility: %d\n\n", i);
    fclose(fptr);


    //write the report into report file
    FILE* fp;
    fp = fopen("FacilityReport.txt", "w");

    char ttl[21] = "Total Facility: ";
    fprintf(fp, "%s 0%d-%d\n%s\nFacility		        Venue    		Opening Hours\n%s\n", title, year.tm_mon + 1, year.tm_year + 1900, line, line2);
    for (int j = 0; j < i; j++) {
        fprintf(fp, "%-16s        %-10s      %s-%s\n", facdet[j].type, facdet[j].venue, facdet[j].hour.from_hour, facdet[j].hour.till_hour);
    }
    fprintf(fp, "%s%d", ttl, i);
    fclose(fp);

    reset();
    backtofacmain();
}

void backtofacmain() {

    int choice1, ent1 = 0;
    do {
        yellow();
        printf("Do you want to exit or go back?\n");
        printf("1. facility menu\n");
        printf("2. main menu\n");
        printf("Enter your choice: ");
        cyan();
        scanf("%d", &choice1);
        yellow();
        system("cls");


        switch (choice1) {
        case 1:
            facmain();
            break;
        case 2:
            menu();
            break;
        default:
            ent1++;
            if (ent1 != 0)
                printf("Please enter your choice again(1-2)\n\n");
        }
    } while (ent1 != 0);
}

void valID(char id[4]) {//to make the id become uppercase

    for (int p = 0; p < strlen(id); p++) {
        if (isalpha(id[p])) {
            id[p] = toupper(id[p]);
        }
    }

}

void valType(char type[21]) {//make the letter become uppercase
    for (int p = 0; p <= strlen(type); p++) {
        if (p == 0) {
            type[p] = toupper(type[p]);
        }
        if (type[p] == 32) {
            type[p + 1] = toupper(type[p + 1]);
        }
    }


}


//facility usage 
void facusageMain() {
    int choice, i = 1;
    while (i == 1)
    {
        system("cls");
        do {
            system("cls");
            yellow();
            printf("[1] modify facility usage record\n");
            printf("[2] search facility usage record\n");
            printf("[3] delete facility usage record\n");
            printf("[4] display facility usage record\n");
            printf("[5] report \n");
            printf("[6] Renew the record \n");
            printf("[0] back to main menu\n\n");

            printf("Enter ur choice > ");
            cyan();
            scanf("%d", &choice);
            yellow();
        } while (choice < 0 || choice>6);
        char renew;
        switch (choice)
        {
        case 1:
            modify_updaterecord();
            break;
        case 2:
            searchStatus();
            break;
        case 3:
            facudeleteRecord();
            break;
        case 4:
            displayAllFacStatus();
            break;
        case 5:
            generate_report();
            break;
        case 6:
            addFacUsageStatus();
            printf("halo");
            break;
        case 0:
            menu();
            break;
        }
    }


}

void addFacUsageStatus() {

    addFacUsageStatusRecord add;
    strcpy(add.status, "Empty");
    
    //step 1
    FILE* fc, * fa;

    fc = fopen("booking.txt", "r");
    fa = fopen("facility_usage_record", "wb");
    //step 2 
    if (fc == NULL || fa == NULL)
    {
        red();
        printf("Error! Unable to open file!\n");
        reset();
        exit(-1);
    }
    system("cls");
    //step 3
    while (!feof(fc))
    {
        fscanf(fc, "%s %s %s %s %s %s %s %lf %c\n", &add.noUse1, &add.facID, &add.noUse2, &add.bookingDate, &add.bookingTime, &add.memberID, &add.noUse3, &add.nouse4, &add.noUse5);
        // *check printf("%s %s %s %s %s %s %s %lf %c\n", add.noUse1, add.facID, add.noUse2, add.bookingDate, add.bookingTime, add.memberID, add.noUse3, add.nouse4, add.noUse5);
        fwrite(&add, sizeof(add), 1, fa);

    }

    //step 4
    fclose(fc);
    fclose(fa);
    yellow();
    printf("renew successfully\n");
    reset();
    system("pause");
}

void modify_updaterecord() {
    char choice, facID[10], dateBook[20], timeBook[20], cont;
    int i = 0, status;

    addFacUsageStatusRecord add[100];
    system("cls");
    do {
        FILE* fd, * fe;
        fd = fopen("facility_usage_record", "rb");
        yellow();
        printf("Enter facility id: ");
        rewind(stdin);
        cyan();
        gets(facID);
        yellow();
        printf("Enter date book(e.g. 23-03-2022): ");
        rewind(stdin);
        cyan();
        gets(dateBook);
        yellow();
        printf("Enter time book(e.g. 1200-1400): ");
        rewind(stdin);
        cyan();
        gets(timeBook);
        yellow();
        printf("\n");

        int k = 0;
        while (fread(&add[k], sizeof(addFacUsageStatusRecord), 1, fd) != 0) {
            k++;
        }

        for (i = 0; i < k; i++) {
            if (strcmp(facID, add[i].facID) == 0 && strcmp(dateBook, add[i].bookingDate) == 0 && strcmp(timeBook, add[i].bookingTime) == 0) {
                reset();
                printf("This is the record found : \n");
                yellow();
                printf("Facility ID: %s\nMember ID: %s\nBooking Date: %s\nBooking Time: %s\n\n", add[i].facID, add[i].memberID, add[i].bookingDate, add[i].bookingTime);
                
                printf("Enter status (1. in used/ 2. empty):");
                cyan();
                scanf("%d", &status);
                yellow();
                if (status == 1) {
                    strcpy(add[i].status, "In used");
                }
                else if (status == 2)
                    strcpy(add[i].status, "Empty");
            }
        }

        fclose(fd);
        fe = fopen("facility_usage_record", "wb");
        for (i = 0; i < k; i++) {
            fwrite(&add[i], sizeof(add[i]), 1, fe);
        }
        fclose(fe);
        yellow();
        printf("Enter again? (Y/N): ");
        rewind(stdin);
        cyan();
        scanf("%c", &cont);
        reset();
        system("pause");
    } while (cont == 'y' || cont == 'Y');
}

void searchStatus() {
    char search, bookID[20], again;
    addFacUsageStatusRecord add[100];
    FILE* fp;
    fp = fopen("facility_usage_record", "rb");

    if (fp == NULL) {
        red();
        printf("Error ! unable to open file. \n");
        reset();
        exit(-1);
    }
    system("cls");
    yellow();
    printf("\nEnter booking ID to search: ");
    rewind(stdin);
    cyan();
    scanf("%[^\n]", &bookID);
    yellow();

    int k = 0;
    while (fread(&add[k], sizeof(addFacUsageStatusRecord), 1, fp) != 0) {
        k++;
    }

    for (int i = 0; i < k; i++) {
        if (strcmp(bookID, add[i].noUse1) == 0) {
            reset();
            printf("This is the record found : \n");
            yellow();
            printf("\nFacility ID  MemberID  Booking date  Booking Time  Status\n");
            printf("===========  ========  ============  ============  ======\n");
            printf("%s          %s    %s    %s     %s\n", add[i].facID, add[i].memberID, add[i].bookingDate, add[i].bookingTime, add[i].status);
            break;
        }
    }
    yellow();
    printf("\nEnter again to search? (Y/N): ");
    rewind(stdin);
    cyan();
    scanf("%c", &again);
    yellow();
    while (again == 'y' || again == 'Y') {
        yellow();
        printf("Enter booking ID to search: ");
        rewind(stdin);
        cyan();
        scanf("%[^\n]", &bookID);
        yellow();
        for (int i = 0; i < k; i++) {
            if (strcmp(bookID, add[i].noUse1) == 0) {
                reset();
                printf("This is the record found : \n");
                yellow();
                printf("\nFacility ID  MemberID  Booking date  Booking Time  Status\n");
                printf("===========  ========  ============  ============  ======\n");
                printf("%s          %s    %s    %s     %s\n", add[i].facID, add[i].memberID, add[i].bookingDate, add[i].bookingTime, add[i].status);
                break;
            }
        }
        yellow();
        printf("\nEnter again to search? (Y/N): ");
        rewind(stdin);
        cyan();
        scanf("%c", &again);
        yellow();
    }

    fclose(fp);
}

void facudeleteRecord() {
    char delete, bID[20], more;
    addFacUsageStatusRecord add[100];
    FILE* fp, * fw;
    int found = 0;
    fp = fopen("facility_usage_record", "rb");
    fw = fopen("facility_usage_record2", "wb");

    if (fp == NULL || fw == NULL) {
        red();
        printf("Error ! unable to open file. \n");
        reset();
        exit(-1);
    }
    system("cls");
    yellow();
    printf("Enter booking ID to delete: ");
    rewind(stdin);
    cyan();
    scanf("%[^\n]", &bID);
    yellow();
    int k = 0;
    while (fread(&add, sizeof(addFacUsageStatusRecord), 1, fp) != 0) {

        if (strcmp(bID, add[k].noUse1) == 0) {
            printf("A record with requested id found and deleted.\n\n");
            found = 1;
        }
        else {
            fwrite(&add[k], sizeof(addFacUsageStatusRecord), 1, fw);
        }
    }
    if (!found) {
        red();
        printf("No record(s) found with the requested ID: %s\n\n", bID);
        reset();
    }
    reset();
    fclose(fp);
    fclose(fw);

    remove("facility_usage_record");
    rename("facility_usage_record2", "facility_usage_record");
    system("pause");

}

void displayAllFacStatus() {
    addFacUsageStatusRecord add[100];
    char dis;
    FILE* fb;
    fb = fopen("facility_usage_record", "rb");

    system("cls");
    yellow();
    printf("\nFacility ID  MemberID  Booking date  Booking Time  Status\n");
    reset();
    printf("-----------  --------  ------------  ------------  ------\n");
    yellow();
    int k = 0;
    while (fread(&add[k], sizeof(addFacUsageStatusRecord), 1, fb) != 0) {
        printf("%s          %s    %12s    %10s   %-10s\n", add[k].facID, add[k].memberID, add[k].bookingDate, add[k].bookingTime, add[k].status);
        k++;

    }
    reset();
    fclose(fb);
    system("pause");
}

void generate_report() {
    addFacUsageStatusRecord add[100];
    int choice, num;
    char another;
    system("cls");
    do {
        yellow();
        printf("\nEnter type of report wanted to generate: \n");
        printf("1. Number of records\n");
        printf("2. Most frequently booked facility\n");
        printf("3. Most frequently booked time\n");
        printf("0. Exit\n");
        rewind(stdin);
        cyan();
        scanf("%d", &choice);
        yellow();
        printf("\n");

        if (choice == 1) {
            FILE* fz;
            fz = fopen("facility_usage_record", "rb");

            int k = 0;
            while (fread(&add[k], sizeof(addFacUsageStatusRecord), 1, fz) != 0) {
                k++;
            }
            num = k;
            reset();
            printf("Total has %d records\n", num);
            fclose(fz);
        }
		else if (choice == 2) {
			system("cls");
			FILE* fz;
			fz = fopen("facility_usage_record", "rb");
            yellow();
			printf("Booking ID   Member ID   Booking Date   Facility ID\n");
            reset();
			printf("==========   =========   ============   ===========\n");
            yellow();
			int k = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0;
			while (fread(&add[k], sizeof(addFacUsageStatusRecord), 1, fz) != 0) {
				printf("%s        %s      %s      %s\n", add[k].noUse1, add[k].memberID, add[k].bookingDate, add[k].facID);

				if (strcmp(add[k].facID, "SP1") == 0) {
					a++;
				}
				else if (strcmp(add[k].facID, "KA1") == 0) {
					b++;
				}
				else if (strcmp(add[k].facID, "KA2") == 0) {
					c++;
				}
				else if (strcmp(add[k].facID, "DR1") == 0) {
					d++;
				}
				else if (strcmp(add[k].facID, "DR2") == 0) {
					e++;
				}
				else if (strcmp(add[k].facID, "BC1") == 0) {
					f++;
				}
				else if (strcmp(add[k].facID, "BC2") == 0) {
					g++;
				}
				else if (strcmp(add[k].facID, "AR1") == 0) {
					h++;
				}
				else if (strcmp(add[k].facID, "AR2") == 0) {
					i++;
				}
				else if (strcmp(add[k].facID, "MR2") == 0) {
					j++;
				}
				k++;

			}
			printf("\n");
            reset();
			if (a >= b && a >= c && a >= d && a >= e && a >= f && a >= g && a >= h && a >= i && a >= j) {
				printf("SP1- swimming pool appear %d times.\n", a);

			}
			if (b >= a && b >= c && b >= d && b >= e && b >= f && b >= g && b >= h && b >= i && b >= j) {
				printf("KA1- kareoka 1 appear %d times.\n", b);

			}
			if (c >= a && c >= b && c >= d && c >= e && c >= f && c >= g && c >= h && c >= i && c >= j) {
				printf("KA2- kareoka 2 appear %d times.\n", c);

			}
			if (d >= a && d >= b && d >= c && d >= e && d >= f && d >= g && d >= h && d >= i && d >= j) {
				printf("DR1- dancing room 1 appear %d times.\n", d);

			}
			if (e >= a && e >= c && e >= b && e >= d && e >= f && e >= g && e >= h && e >= i && e >= j) {
				printf("DR2- dancing room 2 appear %d times.\n", e);

			}
			if (f >= a && f >= c && f >= d && f >= e && f >= b && f >= g && f >= h && f >= i && f >= j) {
				printf("BC1- basketball court 1 appear %d times.\n", f);

			}
			if (g >= a && g >= c && g >= d && g >= e && g >= f && g >= b && g >= h && g >= i && g >= j) {
				printf("BC2- basketball court 2 appear %d times.\n", g);

			}
			if (h >= a && h >= c && h >= d && h >= e && h >= f && h >= b && h >= g && h >= i && h >= j) {
				printf("AR1- Archery Range 1 appear %d times.\n", h);

			}
			if (i >= a && i >= c && i >= d && i >= e && i >= f && i >= b && i >= h && i >= g && i >= j) {
				printf("AR2- Archery Range 2 appear %d times.\n", i);

			}
			if (j >= a && j >= c && j >= d && j >= e && j >= f && j >= b && j >= h && j >= i && j >= g) {
				printf("MR1- Meeting Room 1 appear %d times.\n", j);

			}
			fclose(fz);
            reset();
		}
		else if (choice == 3) {
			system("cls");
			addFacUsageStatusRecord add[100];
			FILE* fz;
			fz = fopen("facility_usage_record", "rb");
            yellow();
			printf("Booking ID   Member ID   Booking time   Booking Date\n");
            reset();
			printf("==========   =========   ============   ============\n");
            yellow();
			int z = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
			while (fread(&add[z], sizeof(addFacUsageStatusRecord), 1, fz) != 0) {
				printf("%s        %s      %s      %s\n", add[z].noUse1, add[z].memberID, add[z].bookingTime, add[z].bookingDate);
				
				if (strcmp(add[z].bookingTime, "0800-1000") == 0) {
					a++;
				}
				else if (strcmp(add[z].bookingTime, "1000-1200") == 0) {
					b++;
				}
				else if (strcmp(add[z].bookingTime, "1200-1400") == 0) {
					c++;
				}
				else if (strcmp(add[z].bookingTime, "1400-1600") == 0) {
					d++;
				}
				else if (strcmp(add[z].bookingTime, "1500-1700") == 0) {
					e++;
				}
				else if (strcmp(add[z].bookingTime, "1600-1800") == 0) {
					f++;
				}
				else if (strcmp(add[z].bookingTime, "1800-2000") == 0) {
					g++;
				}
				else if (strcmp(add[z].bookingTime, "2000-2200") == 0) {
					h++;
				}
				z++;

			}
			printf("\n");
            reset();
			if (a >= b && a >= c && a >= d && a >= e && a >= f && a >= g && a >= h) {
				printf("Booking time 0800-1000 appear %d times.\n", a);

			}
			if (b >= a && b >= c && b >= d && b >= e && b >= f && b >= g && b >= h) {
				printf("Booking time 1000-1200 appear %d times.\n", b);

			}
			if (c >= a && c >= b && c >= d && c >= e && c >= f && c >= g && c >= h) {
				printf("Booking time 1200-1400 appear %d times.\n", c);

			}
			if (d >= a && d >= b && d >= c && d >= e && d >= f && d >= g && d >= h) {
				printf("Booking time 1400-1600 appear %d times.\n", d);

			}
			if (e >= a && e >= c && e >= b && e >= d && e >= f && e >= g && e >= h) {
				printf("Booking time 1500-1700 appear %d times.\n", e);

			}
			if (f >= a && f >= c && f >= d && f >= e && f >= b && f >= g && f >= h) {
				printf("Booking time 1600-1800 appear %d times.\n", f);

			}
			if (g >= a && g >= c && g >= d && g >= e && g >= f && g >= b && g >= h) {
				printf("Booking time 1800-2000 appear %d times.\n", g);

			}
			if (h >= a && h >= c && h >= d && h >= e && h >= f && h >= b && h >= g) {
				printf("Booking time 2000-2200 appear %d times.\n", h);

			}
			fclose(fz);
            reset();
		}
		else if (choice == 0) {

            break;
        }
        yellow();
        printf("\nGenerate another report? (Y/N): ");
        rewind(stdin);
        cyan();
        scanf("%c", &another);
        reset();
    } while (another == 'Y' || another == 'y');
    reset();
    system("pause");

}

// everyone can use
char getValidGender(char* gender) {

    do
    {
        yellow();
        printf("Gender 'M' Male 'F'Female: ");
        rewind(stdin);
        cyan();
        scanf("%c", &*gender);
        yellow();

        *gender = toupper(*gender);

        //validation for gender
        if (*gender != 'M' && *gender != 'F')
        {
            red();
            printf("Please enter M or F only....\n\n");
            reset();
        }
    } while (*gender != 'M' && *gender != 'F');

}

char* getValidIc() {
    char IC[13];
    int cond;

    do
    {
        cond = 0;
        yellow();
        printf("Enter IC : ");
        rewind(stdin);
        cyan();
        gets(IC);
        yellow();

        if (strlen(IC) == 12)
        {
            for (int i = 0; i < strlen(IC); i++)
            {
                if (isdigit(IC[i]) == 0) {
                    cond++;
                    break;
                }
            }
            if (cond != 0)
            {
                red();
                printf("Please enter only number!!\n\n");
                reset();
            }
        }
        else {
            red();
            printf("Please enter 12 digit number only!!\n\n");
            reset();
            cond++;
        }

    } while (cond != 0);

    return IC;
}

char* getValidContactNum() {
    char contact[12];
    int cond;

    do
    {
        cond = 0;
        yellow();
        printf("Contact Number : ");
        rewind(stdin);
        cyan();
        gets(contact);
        yellow();

        if (strlen(contact) == 10 || strlen(contact) == 11)
        {
            for (int i = 0; i < strlen(contact); i++)
            {
                if (isdigit(contact[i]) == 0) {
                    cond++;
                    break;
                }
            }
            if (cond != 0)
            {
                red();
                printf("Please enter only number!!\n\n");
                reset();
            }
        }
        else {
            red();
            printf("Please enter only 10~11 digit number only!!\n\n");
            reset();
            cond++;
        }


    } while (cond != 0);

    return contact;
}

char* getValidname() {

    char name[50];
    int checkName;
    do {
        checkName = 0;
        yellow();
        printf("Enter name:");
        cyan();
        rewind(stdin);
        scanf("%[^\n]", &name);
        yellow();
        for (int i = 0; i <= strlen(name); i++) {
            if (isdigit(name[i]))
            {
                checkName = 1;
                red();
                printf("Invalid name entered,Please ensure there is no number in the field\n");
                reset();
                break;
            }
            else if (name[i])
                name[i] = toupper(name[i]);
        }
    } while (checkName == 1);

    return name;
}


