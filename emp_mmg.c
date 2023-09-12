#include<stdio.h>

// Structure for Hire-Date
struct Date {
    int dd, mm, yy;
};

// Structure for Employee-Data
struct Employee {
    int empno;                  // Emp Number
    char empname[100];         // Emp Name
    struct Date hiredate;      // Hire Date (struture variable declared inside another struture)
    float basic_salary;        // basic salary
    float net_salary;          // net salary
};

int isValidDate(struct Date hiredate) {
    
    //basic condition to check hire date
    if (hiredate.mm < 1 || hiredate.mm > 12) return 0;    
    
    // number of days in month 
    /*The array daysInMonth is designed in such a way that 
    the index corresponds to the month number, 
    and the value at that index gives the number of days in that month*/
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // if hire date is leap year
    if ((hiredate.yy % 4 == 0 && hiredate.yy % 100 != 0) || (hiredate.yy % 400 == 0))
        daysInMonth[2] = 29;  // updating Leap year
    
    // if hire date is less than 1 and hire date is greater than the number of days in month 
    if (hiredate.dd < 1 || hiredate.dd > daysInMonth[hiredate.mm]) return 0; 
    
    return 1; // for valid date 1 is returned
}

// Function to accept Employee Data
void acceptEmployeeData(struct Employee *emp) {   // call by reference

    // When scanf attempts to read an integer, it will return the number of successfully read items
    printf("Enter Employee Number: ");
    while (scanf("%d", &emp->empno) != 1) getchar();  /* GETCHAR() - reads the next available 
                                                character from the standard input */

    printf("Enter Employee Name (max 99 characters): ");
    scanf(" %[^\n]", emp->empname);  // to read string with spaces

    do {
        printf("Enter Hire Date (dd mm yyyy): ");
        scanf("%d %d %d", &emp->hiredate.dd, &emp->hiredate.mm, &emp->hiredate.yy); // hire date input
        getchar();  /* GETCHAR() - reads the next available 
                    character from the standard input */
        if (!isValidDate(emp->hiredate)) // date validation check
            printf("Invalid date entered. Please enter a valid date.\n");
    } while (!isValidDate(emp->hiredate)); // it will repeat unitl a valid date is given as an input

    printf("Enter Basic Salary: ");
    // checking salary - if it is not empty and is not negative
    while (scanf("%f", &emp->basic_salary) != 1 || emp->basic_salary < 0) { 
        printf("Salary cannot be negative. Please enter a valid salary.\n");
        getchar();  /* GETCHAR() - reads the next available 
                    character from the standard input */
    }
}

// Function to calculate net pay
void calculateNetPay(struct Employee *emp) {
    float DA = 0.4 * emp->basic_salary;         
    float TA = 0.1 * emp->basic_salary;
    float PF = 0.05 * emp->basic_salary;
    emp->net_salary = emp->basic_salary + DA + TA - PF;
}

// Function to display Employee Data
// the integers 6, 30, 2, 4 Specifies the width that how much space it will ocuppy
/* in float values 10.2 10 specifies the width and .2 Ensures that the floating-point number 
is displayed with exactly 2 decimal places */
void showData(struct Employee *emp) {
    printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║ Employee Number: %-6d                                          ║\n", emp->empno);
    printf("║ Employee Name  : %-30s                                       ║\n", emp->empname);
    printf("║ Hire Date      : %02d/%02d/%04d                                   ║\n", emp->hiredate.dd, emp->hiredate.mm, emp->hiredate.yy);
    printf("║ Basic Salary   : %-10.2f                                        ║\n", emp->basic_salary);
    printf("║ Net Salary     : %-10.2f                                        ║\n", emp->net_salary);
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
}

int main() {
    struct Employee emp;

    acceptEmployeeData(&emp);  
    calculateNetPay(&emp);
    showData(&emp);

    return 0;
}

