#include <stdio.h>
#define Total_People 3

int Number_Of_People = 0;
int Index_Email = -1;
int Index_Pw = -1;

struct person_data {
    int age;
    char name[50];
    char email[50];
    char password[50];
};

struct person_data person[Total_People];

//Taking Action 
void create_data_person();
void info_person();
void fileHanlder();

void get_Data();

void Sign_Up();
void Start_Login();


int Email(char input[50]);
int Email_Index(char inputEmail[50]);
int Pw_Index(char inputPwd[50]);
int Email_auth(char inputEmail[50]);
int Email_Check(char inputEmail[50], char userEmail[50]);
int Pw_Check(char inputPassword[50], char userPassword[50]);

void lobby();
int getStrLength(char str[50]);

int main() {
    get_Data();
    info_person();
    lobby();

    return 0;
}

void fileHanlder() {
    FILE *fptr = fopen("./data/workers.txt", "w");

    if(fptr == NULL) {
        printf("File Not Found!");
        return;
    }

    printf("\n Saving Initial Data \n");

    for (int i = 0; i < Number_Of_People; i++)
    {
        fprintf(fptr, "%d %s %s %s\n", person[i].age, person[i].name, person[i].email, person[i].password);
    }
    
    fclose(fptr);
}



void get_Data() {
    FILE *fptr = fopen("./data/workers.txt", "r");

    if(fptr == NULL) {
        printf("File not found!");
        return;
    }

    for(int i = 0; i < Total_People; i++) {

        if(fscanf(fptr, "%d %s %s %s", &person[i].age, person[i].name, person[i].email, person[i].password) == EOF) {
            return;
        }
        Number_Of_People++;
    }


    fclose(fptr);
}

void create_data_person() {
    int count = 0;
    while (count < Total_People)
    {
        printf("Enter Age: ");
        scanf("%d", &person[count].age);

        printf("Enter Name: ");
        scanf(" %[^\n]", person[count].name);
        
        printf("Enter Email: ");
        scanf(" %[^\n]", person[count].email);

        printf("Enter Password: ");
        scanf(" %[^\n]", person[count].password);

        printf("=\n");

        Number_Of_People++;
        count++;
    }
};

void info_person() {
    int count = 0;

    printf(" Printing Data  (%d)\n", Number_Of_People);

    while(count < Number_Of_People) {
        printf("Name: %s  Age: %d  Email: %s  Password: %s\n", person[count].name, person[count].age, person[count].email, person[count].password);

        count++;
    }
}

void Sign_Up() {
    int ageInput = 0;
    char nameInput[50];
    char emailInput[50];
    char pwdInput[50];

    printf("\n SIGN UP FORM \n");

    do {
        printf("Enter your age: ");
        scanf("%d", &ageInput);
    } while(ageInput == 0 || ageInput < 16);

    
    do {
        printf("Enter your name: ");
        scanf(" %[^\n]", nameInput);
    } while(0);

    do {
        printf("Enter your email: ");
        scanf(" %[^\n]", emailInput);

    } while(!Email(emailInput) || Email_auth(emailInput));
    
    printf("name: %s, age: %d, email: %s, pwd: %s", nameInput, ageInput, emailInput, pwdInput);
 
}

void Start_Login() {
    char emailInput[50];
    char pwdInput[50];
    Index_Email = -1;
    Index_Pw = -1;

    printf("\n= Start_Login FORM =\n");

    printf("Enter your email: ");
    scanf(" %[^\n]", emailInput);

    if(!Email(emailInput)) {
        printf("Invalid Email!\n");
        Start_Login();
        return;
    }
    
    printf("Enter your password: ");
    scanf(" %[^\n]", pwdInput);

    Index_Email = Email_Index(emailInput);
    
    if(Index_Email == -1) {
        printf("Invalid Email %d!\n", Index_Email);
        Start_Login();
        return;
    }

    Index_Pw = Pw_Index(pwdInput);

    if(Index_Pw == -1) {
        printf("Wrong Password %d!\n", Index_Pw);
        Start_Login();
        return;
    }

    if(Index_Email != Index_Pw) {
        Start_Login();
        return;
    }

    printf("email: %d, password: %d\n", Index_Email, Index_Pw);
    printf("\nWelcome Sir: %s\n\n", person[Index_Email].name);
}

int getStrLength(char str[50]) {
 
    int count = 0;

    for(int i = 0; i < 50; i++) {
        if(str[i] == '\0') {
            return count;
        }
        count++;
    }

    return count;
}

int Email_auth(char inputEmail[50]) {
    int count = 0;

    while(count < Number_Of_People) {
        if(Email_Check(inputEmail, person[count].email)) {
            return 1;
        }

        count++;
    }

    return 0;
}

int Email(char input[50]) {
  
    char MAIL_EXTENSION[10] = "@gmail.com";
    int inputLength = getStrLength(input);

    if(inputLength <= 10) {
        return 0;
    }

    for(int i = (inputLength - 10); i < inputLength; i++) {
        int mailIndex = (i + 10) - inputLength;

        if(input[i] != MAIL_EXTENSION[mailIndex]) {
            return 0;
        }
    }

    return 1;
}




int Email_Index(char inputEmail[50]) {
    int userIndex = -1;
    int count = 0;

    while(count < Number_Of_People) {
        if(Email_Check(inputEmail, person[count].email)) {
            userIndex = count;
            return userIndex;
        }
        count++;
    }

    return userIndex;
}

int Email_Check(char inputEmail[50], char userEmail[50]) {
    int inputEmailLength = getStrLength(inputEmail);
    int userEmailLength = getStrLength(userEmail);

    if(inputEmailLength != userEmailLength) {
        return 0;
    }

    for (int i = 0; i < inputEmailLength; i++)
    {
        if (inputEmail[i] != userEmail[i]) {
            return 0;
        }
    }
    
    return 1;
}


int Pw_Index(char inputPwd[50]) {
    int userIndex = -1;
    int count = 0;

    while(userIndex < Number_Of_People) {
        if(Pw_Check(inputPwd, person[count].password)) {
            userIndex = count;
            return userIndex;
        }

        count++;
    }

        return userIndex;
}


void lobby() {
    int choice = 0;

    printf("\n Welcome to Lobby \n");
    printf("Press 1 to Register\n");
    printf("Press 2 to Start_Login\n");
    printf("Press 3 to Exit\n");

    do {
        printf("Press number: ");
        scanf(" %d", &choice);
    } while (choice != 1 && choice != 2 && choice != 3);

    if(choice == 1) {
        Sign_Up();
    } else if(choice == 2) {
        Start_Login();
    } 


}
int Pw_Check(char inputPassword[50], char userPassword[50]) {
    int inputPwdLength = getStrLength(inputPassword);
    int userPwdLength = getStrLength(userPassword);

    if(inputPwdLength != userPwdLength) {
        return 0;
    }

    for (int i = 0; i < inputPwdLength; i++)
    {
        if (inputPassword[i] != userPassword[i]) {
            return 0;
        }
    }
    
    return 1;
}
