
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date *date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;
    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData *data)
{
    int selection;
    do
    {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    displayPatientTableHeader();
    int i; // counter
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0) // checking wheather the index is empty or not
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n");
        printf("==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
            break;
            // default case is not require as we are using function of range
        }
    } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i = 0, index = -1, repeat = 1;
    while (i < max && repeat)
    {
        // search for empty field to input patient data.
        if (patient[i].patientNumber == 0)
        {
            index = i;
            repeat = 0;
        }
        i++;
    }
    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int number, index;
    printf("Enter the patient number: ");
    scanf("%d", &number);
    clearInputBuffer();
    putchar('\n');
    index = findPatientIndexByPatientNum(number, patient, max);
    // Function return -1 if the number is not found
    if (index != -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int number, index;
    int confirm;
    printf("Enter the patient number: ");
    scanf("%d", &number);
    putchar('\n');
    clearInputBuffer();
    index = findPatientIndexByPatientNum(number, patient, max);
    // Function return -1 if the number is not found
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        confirm = (inputCharOption("yn") == 'y');
        if (confirm == 1)
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData *data)
{
    int i, patientIndex;
    displayScheduleTableHeader(NULL, AllRECORD);
    for (i = 0; (data->appointments[i].patientNumber != 0 &&
                 i < data->maxAppointments);
         i++)
    {
        // just finding patient index for printing patient details
        patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
                                                     data->patients, data->maxAppointments);
        displayScheduleData(&data->patients[patientIndex],
                            &data->appointments[i], WITHDATE);
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData *data)
{
    int patientIndex;
    struct Appointment tmp;
    int i;
    // takes input of date according to requirement
    // here it would be without hours
    inputDate(&tmp, !WITHHOURS);
    putchar('\n');
    displayScheduleTableHeader(&tmp.date, !AllRECORD);
    for (i = 0; (data->appointments[i].patientNumber != 0 &&
                 i < data->maxPatient);
         i++)
    {
        if(comparedate(&tmp, &data->appointments[i]))
        {
            patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
                                                        data->patients, data->maxAppointments);
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], !WITHDATE);
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
// ToDo: You will need to create this function!
void addAppointment(struct Appointment appoints[], int maxappointment,
                    struct Patient patients[], int maxPatient)
{
    // creating an tmp struct for storing data temperory
    struct Appointment tmp = {0};
    // i is a index,
    // EmptyIndex is the empty field index in appointment where i am going to store data
    int i, EmptyIndex, patientIndex;
    // checking exact number of appointments
    for (i = 0; appoints[i].patientNumber != 0; i++)
    {
        ;
    }
    // index store the index number of Appointment which is empty
    EmptyIndex = i;
    if (EmptyIndex == maxappointment)
    {
        printf("there is no avalabile appointent\n");
    }
    else
    {
        int match;
        do
        {
            patientIndex = inputPatientNum(patients, maxPatient);
            tmp.patientNumber = patients[patientIndex].patientNumber;
        } while (patientIndex == -1);
        do
        {
            match = 0;
            inputDate(&tmp, WITHHOURS);
            for (i = 0; (i < maxappointment && match == 0 && appoints[i].patientNumber != 0); i++)
            {
                // checking is this appoint would overlap with other
                if ((comparedate(&tmp, &appoints[i]) &&
                     tmp.time.hour == appoints[i].time.hour &&
                     tmp.time.min == appoints[i].time.min))
                {
                    match = 1;
                }
            }
            if (match == 1)
            {
                putchar('\n');
                printf("ERROR: Appointment timeslot is not available!\n\n");
            }
        } while (match);
    }
    // after getting all checks done then i copy all tmp to the empty index
    appoints[EmptyIndex] = tmp;
    // sorting after taking input
    sort(appoints, maxappointment);
    putchar('\n');
    printf("*** Appointment scheduled! ***\n\n");
    return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appoint[], int maxAppointment, struct Patient patients[], int maxPatient)
{
    int patientIndex = 0, i, index = -1, match = 0;
    char selection;
    struct Appointment tmp;
    patientIndex = inputPatientNum(patients, maxPatient);
    tmp.patientNumber = patients[patientIndex].patientNumber;
    if(patientIndex != -1)
    {
        inputDate(&tmp, !WITHHOURS);
        for (i = 0; i < maxAppointment && appoint[i].patientNumber != 0 && match == 0; i++)
        {
            if ( tmp.patientNumber == appoint[i].patientNumber)
            {
                match = comparedate(&tmp, &appoint[i]);
            }
            
            // match = (comparedate(&tmp, &appoint[i]) && tmp.patientNumber == appoint[i].patientNumber);
        }
        index = i - 1;
        printf("%d\n", index);
        if (match == 0)
        {
            printf("record not found\n");
        }
        else
        {
            putchar('\n');
            displayPatientData(&patients[patientIndex], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            selection = inputCharOption("yn");
            if (selection == 'y')
            {
                // this loop rearrange all appointments after an appointment being removed
                for (i = index; i < maxAppointment && appoint[i].date.year != 0; i++)
                {
                    appoint[i] = appoint[i + 1];
                }
                appoint[i].patientNumber = 0;
                appoint[i].date.year = 0;
                putchar('\n');
                printf("Appointment record has been removed!\n\n");
            }
            else
            {
                printf("Remove aborted\n\n");
            }
        }
    }
    return;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int number, index;
    printf("Search by patient number: ");
    scanf("%d", &number);
    clearInputBuffer();
    putchar('\n');
    index = findPatientIndexByPatientNum(number, patient, max);
    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phonenumber[PHONE_LEN + 1] = {0};
    int i = 0, found = 0;
    printf("Search by phone number: ");
    inputCString(phonenumber, 10, 10);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            if (strcmp(phonenumber, patient[i].phone.number) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
                found = 1;
            }
        }
    }
    if (found == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maximum = 0;
    int i = 0;
    while (i < max)
    {
        if (patient[i].patientNumber > maximum)
        {
            maximum = patient[i].patientNumber;
        }
        i++;
    }
    return maximum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            return i;
        }
    }
    return -1;
}

// sort the appointment data
void sort(struct Appointment appoints[], int max)
{
    int i, j, counter = 0;
    for (i = 0; i < max && appoints[i].patientNumber != 0; i++)
    {
        counter++;
    }
    for (i = counter; i > 0; i--)
    {
        for (j = 0; j < i - 1; j++)
        {
            if (appoints[j].date.year > appoints[j + 1].date.year)
            {
                swap(&appoints[j], &appoints[j + 1]);
            }
            else if (appoints[j].date.year == appoints[j + 1].date.year)
            {
                if (appoints[j].date.month > appoints[j + 1].date.month)
                {
                    swap(&appoints[j], &appoints[j + 1]);
                }
                else if (appoints[j].date.month == appoints[j + 1].date.month)
                {
                    if (appoints[j].date.day > appoints[j + 1].date.day)
                    {
                        swap(&appoints[j], &appoints[j + 1]);
                    }
                    else if (appoints[j].date.day == appoints[j + 1].date.day)
                    {
                        if (appoints[j].time.hour > appoints[j + 1].time.hour)
                        {
                            swap(&appoints[j], &appoints[j + 1]);
                        }
                        else if (appoints[j].time.hour == appoints[j + 1].time.hour)
                        {
                            if (appoints[j].time.min > appoints[j + 1].time.min)
                            {
                                swap(&appoints[j], &appoints[j + 1]);
                            }
                        }
                    }
                }
            }
        }
    }
}
// swap is a function which swap 2 appointment objects used in sort function
void swap(struct Appointment *a, struct Appointment *b)
{
    struct Appointment tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone *phone)
{
    char selection;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        break;

    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        break;

    case 4:
        strcpy(phone->description, "TBD");
        break;
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char *datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;
    int counter = 0;
    fp = fopen(datafile, "r"); // check here in argument part
    if (fp != NULL)
    {
        int i;
        for (i = 0; (i < max && !feof(fp)); i++)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|", &patients[i].patientNumber, patients[i].name, patients[i].phone.description);
            if (!(strcmp(patients[i].phone.description, "TBD") == 0))
            {
                fscanf(fp, "%s", patients[i].phone.number);
            }
            fgetc(fp);
            counter++;
        }
        fclose(fp);
    }
    return counter;
}
// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char *datafile, struct Appointment appoints[], int max)
{
    FILE *fp = NULL;
    fp = fopen(datafile, "r"); // check here in argument part
    int i, counter = 0;
    if (fp == NULL)
    {
        printf("patient record not found\n");
    }
    else
    {
        for (i = 0; (i < max && !feof(fp)); i++)
        {
            fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber,
                   &appoints[i].date.year,
                   &appoints[i].date.month,
                   &appoints[i].date.day,
                   &appoints[i].time.hour,
                   &appoints[i].time.min);
            counter++;
        }
    }
    // sorting just after taking input
    sort(appoints, max);
    fclose(fp);
    return counter;
}

// it will prompt and take date and time as input and validate it accordingly
void inputDate(struct Appointment *appoints, int WithHours)
{
    printf("Year        : ");
    scanf("%d", &appoints->date.year);
    printf("Month (1-12): ");
    appoints->date.month = inputIntRange(1, 12);
    if (appoints->date.month == 2)
    {
        if ((appoints->date.year % 100 == 0 && appoints->date.year % 400 == 0) || (appoints->date.year % 4 == 0 && appoints->date.year % 100 != 0)) // change this logic to actually accomodate leap year
        {
            printf("Day (1-29)  : ");
            appoints->date.day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            appoints->date.day = inputIntRange(1, 28);
        }
    }
    else if (appoints->date.month == 2 || appoints->date.month == 4 || appoints->date.month == 6 || appoints->date.month == 9 || appoints->date.month == 11)
    {
        printf("Day (1-30)  : ");
        appoints->date.day = inputIntRange(1, 30);
    }
    else
    {
        printf("Day (1-31)  : ");
        appoints->date.day = inputIntRange(1, 31);
    }

    if (WithHours)
    {
        int repeat;
        do
        {
            repeat = 1;
            printf("Hour (0-23)  : ");
            appoints->time.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            appoints->time.min = inputIntRange(0, 59);
            if (appoints->time.hour == MAXTIME && appoints->time.min != 0)
            {
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", MINTIME, MAXTIME, APPT_TIME_INTERVAL);
            }
            else if ((appoints->time.hour <= MAXTIME && appoints->time.hour >= MINTIME) && appoints->time.min % APPT_TIME_INTERVAL == 0)
            {
                repeat = 0;
            }
            else
            {
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", MINTIME, MAXTIME, APPT_TIME_INTERVAL);
            }
        } while (repeat);
    }
}
int comparedate(const struct Appointment *apt1, const struct Appointment *apt2)
{
    int match = 0;
    if ((apt1->date.year == apt2->date.year &&
         apt1->date.month == apt2->date.month &&
         apt1->date.day == apt2->date.day))
    {
        match = 1;
    }
    return match;
}

// inputting patient number and validate them.
int inputPatientNum(struct Patient patients[], int maxPatient){
    int patientnum, patientIndex = -1;
    printf("Patient Number: ");
    scanf("%d", &patientnum);
    clearInputBuffer();
    patientIndex = findPatientIndexByPatientNum(patientnum, patients, maxPatient);
    if (patientIndex == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    return patientIndex;
}