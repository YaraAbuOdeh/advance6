#include<stdio.h>
#include<conio.h>
#include<windows.h>
struct Date {
    int Day;
    int Month;
    int Year;
};
 
struct Date date;


struct Remainder {
    int day;
    int month;
    char Note[50];
};
struct Remainder R;
COORD coordinates = { 0, 0 };
char Color=0x0F;
int NumberOfMonth=12;
void gotoxy(int x, int y)
{
    coordinates.X = x; coordinates.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void SetColor(int ForGroundColor)
{
    WORD WordColor;
    HANDLE HandelStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(HandelStdOut, &csbi))
    {
		char 
        WordColor = (csbi.wAttributes & Color) + (ForGroundColor & Color);
        SetConsoleTextAttribute(HandelStdOut, WordColor);
    }
    return;
}


void ClearConsoleToColors(int ForgroundClor, int BackColor){
    WORD WordColor = ((BackColor & Color) << 4) + (ForgroundClor & Color);
    HANDLE HandelStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(HandelStdOut, WordColor);
    if (GetConsoleScreenBufferInfo(HandelStdOut, &csbi))
    {
        FillConsoleOutputCharacter(HandelStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coordinates, &count);

        FillConsoleOutputAttribute(HandelStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coordinates, &count);
        SetConsoleCursorPosition(HandelStdOut, coordinates);
    }
    return;
}

void SetColorAndBackground(int ForgroundColor, int BackColor)
{
    WORD WordColor = ((BackColor & Color) << 4) + (ForgroundColor & Color);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WordColor);
    return;
}

int checkLeapYear(int year) { 
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

void increaseMonth(int* Month, int* Year) { 
    ++* Month;

    if (*Month > NumberOfMonth) {
        ++* Year;
        *Month = *Month - NumberOfMonth;
    }
}

void decreaseMonth(int* Month, int* Year) { 
    --* Month;
    if (*Month < 1) {
        --* Year;
        if (*Year < 1600) {
            printf("No record available");
            return;
        }
        *Month = *Month + NumberOfMonth;
    }
}
int getNumberOfDays(int month, int year) { 
    switch (month) {                          
    case 1: return(31);
    case 2: if (checkLeapYear(year) == 1)
        return(29);
          else
        return(28);
    case 3: return(31);
    case 4: return(30);
    case 5: return(31);
    case 6: return(30);
    case 7: return(31);
    case 8: return(31);
    case 9: return(30);
    case 10: return(31);
    case 11: return(30);
    case 12: return(31);
    default: return(-1);
    }
}

char* getName(int day) {
    switch (day) {
    case 0:return("Sunday");
    case 1:return("Monday");
    case 2:return("Tuesday");
    case 3:return("Wednesday");
    case 4:return("Thursday");
    case 5:return("Friday");
    case 6:return("Saturday");
    default:return("Error in getName() module.Invalid argument passed");
    }
}


int DayNumber(int day, int month, int year) { //retuns the day number
    int result = 0, t1, t2, y = year;
    year = year - 1600;
    while (year >= 100) {
        result = result + 5;
        year = year - 100;
    }
    result = (result % 7);
    t1 = ((year - 1) / 4);
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    t1 = (t1 % 7);
    result = result + t1;
    result = result % 7;
    t2 = 0;
    for (t1 = 1; t1 < month; t1++) {
        t2 += getNumberOfDays(t1, y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    result = result + t2;
    result = result % 7;
    if (y > 2000)
        result = result + 1;
    result = result % 7;
    return result;
}

char* getDay(int Day, int month, int year) {
    int day;
	int min_of_month=1;
	int max_of_day=12;
    if (!(month >= min_of_month && max_of_day <= 12)) {
        return("Invalid month value");
    }
    if (!(day >= 1 && day <= getNumberOfDays(month, year))) {
        return("Invalid date");
    }
    if (year >= 1600) {
        day = DayNumber(day, month, year);
        day = day % 7;
        return(getName(day));
    }
    else {
        return ("Please give year more than 1600");
    }
}

int checkNote(int day, int month) {
    FILE* fp;
    fp = fopen("note.dat", "rb");
    if (fp == NULL) {
        printf("Error in Opening the file");
    }
    while (fread(&R, sizeof(R), 1, fp) == 1) {
        if (R.day == day && R.month == month) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printMonth(int month, int year, int x, int y) { //prints the month with all days
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0,MinOfMonth=1,MaxOfMonth=12;
    if (!(month >= MinOfMonth && month <= MaxOfMonth)) {
        printf("INVALID MONTH");
        getch();
        return;
    }
    if (!(year >= 1600)) {
        printf("INVALID YEAR");
        getch();
        return;
    }
    gotoxy(20, y);
    // Print date 
    printf("---------------------------\n");
    gotoxy(25, 6);
    switch (month) {
    case 1: printf("January"); break;
    case 2: printf("February"); break;
    case 3: printf("March"); break;
    case 4: printf("April"); break;
    case 5: printf("May"); break;
    case 6: printf("June"); break;
    case 7: printf("July"); break;
    case 8: printf("August"); break;
    case 9: printf("September"); break;
    case 10: printf("October"); break;
    case 11: printf("November"); break;
    case 12: printf("December"); break;
    }
    printf(" , %d", year);
    gotoxy(20, 7);
    printf("---------------------------");

    y += 3;
    gotoxy(x, y);
    printf("S   M   T   W   T   F   S   ");
    y++;
    nod = getNumberOfDays(month, year);
    day = DayNumber(d, month, year);
    switch (day) { //locates the starting day in calender
    case 0:
        x = x;
        cnt = 1;
        break;
    case 1:
        x = x + 4;
        cnt = 2;
        break;
    case 2:
        x = x + 8;
        cnt = 3;
        break;
    case 3:
        x = x + 12;
        cnt = 4;
        break;
    case 4:
        x = x + 16;
        cnt = 5;
        break;
    case 5:
        x = x + 20;
        cnt = 6;
        break;
    case 6:
        x = x + 24;
        cnt = 7;
        break;
    default:
        printf("INVALID DATA FROM THE getOddNumber()MODULE");
        return;
    }
    gotoxy(x, y);
    if (cnt == 1) {
        SetColor(12);
    }
    if (checkNote(d, month) == 1) {
        SetColorAndBackground(15, 12);
    }
    printf("%02d", d);
    SetColorAndBackground(15, 1);
    for (d = 2; d <= nod; d++) {
        if (cnt % 7 == 0) {
            y++;
            cnt = 0;
            x = x1 - 4;
        }
        x = x + 4;
        cnt++;
        gotoxy(x, y);
        if (cnt == 1) {
            SetColor(12);
        }
        else {
            //Clear color
            SetColor(15);
        }
        if (checkNote(d, month) == 1) {
            SetColorAndBackground(15, 12);
        }
        printf("%02d", d);
        SetColorAndBackground(15, 1);
    }
    gotoxy(8, y + 2);
    SetColor(14);
    printf("Press 'n'  to Next, Press 'p' to Previous and 'q' to Quit");
    gotoxy(8, y + 3);
    printf("Red Background indicates the NOTE, Press 's' to see note: ");
    //Clear color
    SetColor(15);
}

void AddNote() {
    FILE* fp;
    fp = fopen("note.dat", "ab+");
    system("cls");
    gotoxy(5, 7);
    printf("Enter the date(DD/MM): ");
    scanf("%d%d", &R.day, &R.month);
    gotoxy(5, 8);
    printf("Enter the Note(50 character max): ");
    fflush(stdin);
    scanf("%[^\n]", R.Note);
    if (fwrite(&R, sizeof(R), 1, fp)) {
        gotoxy(5, 12);
        puts("Note is saved sucessfully");
        fclose(fp);
    }
    else {
        gotoxy(5, 12);
        SetColor(12);
        puts("\aFail to save!!\a");
        //Clear color
        SetColor(15);
    }
    gotoxy(5, 15);
    printf("Press any key............");
    getch();
    fclose(fp);
}

void showNote(int month) {
    FILE* fp;
    int i = 0, isFound = 0;
    system("cls");
    fp = fopen("note.dat", "rb");
    if (fp == NULL) {
        printf("Error in opening the file");
    }
    while (fread(&R, sizeof(R), 1, fp) == 1) {
        if (R.month == month) {
            gotoxy(10, 5 + i);
            printf("Note %d Day = %d: %s", i + 1, R.day, R.Note);
            isFound = 1;
            i++;
        }
    }
    if (isFound == 0) {
        gotoxy(10, 5);
        printf("This Month contains no note");
    }
    gotoxy(10, 7 + i);
    printf("Press any key to back.......");
    getch();

}

int main() {
    ClearConsoleToColors(15, 1);
   // SetConsoleTitle("Calender Project - Programming-technique.blogspot.com");
    int choice;
    char ch = 'a';
    while (1) {
        system("cls");
        printf("1. Find Out the Day\n");
        printf("2. Print all the day of month\n");
        printf("3. Add Note\n");
        printf("4. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
        case 1:
            printf("Enter date (DD MM YYYY) : ");
            scanf("%d %d %d", &date.Day, &date.Month, &date.Year);
            printf("Day is : %s", getDay(date.Day, date.Month, date.Year));
            printf("\nPress any key to continue......");
            getch();
            break;
        case 2:
            printf("Enter month and year (MM YYYY) : ");
            scanf("%d %d", &date.Month, &date.Year);
            system("cls");
            while (ch != 'q') {
                printMonth(date.Month, date.Year, 20, 5);
                ch = getch();
                if (ch == 'n') {
                    increaseMonth(&date.Month, &date.Year);
                    system("cls");
                    printMonth(date.Month, date.Year, 20, 5);
                }
                else if (ch == 'p') {
                    decreaseMonth(&date.Month, &date.Year);
                    system("cls");
                    printMonth(date.Month, date.Year, 20, 5);
                }
                else if (ch == 's') {
                    showNote(date.Month);
                    system("cls");
                }
            }
            break;
        case 3:
            AddNote();
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}
