#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

int main()
{
    // Log-in and Sign-up

    int init_ip;
    int user_count;
    char yon;

    char names[100][100] = {0};
    char passwords[100][100] = {0};
    char acc_nos[100][100] = {0};
    int balances[100] = {0};
    long int positions[100] = {0};

    printf("\nWhat do you want to do?\n");
    printf("\n1. Create account\n");
    printf("\n2. Log in\n");

    printf("\nEnter: \n");
    scanf("%d",&init_ip);
    fflush(stdin);

    system("cls");


    // starting the code
    FILE *ptr_create;
    if(init_ip == 1)
    {
        ptr_create = fopen("users.txt","a");

        char name[100];
        char password[100];
        char acc_no[100];
        int balance;

        printf("\nName: \n");
        scanf("%[^\n]s",&name);
        fprintf(ptr_create, "%s@", name);
        fflush(stdin);

        printf("\nPassword: \n");
        scanf("%[^\n]s",&password);
        fprintf(ptr_create, "%s@", password);
        fflush(stdin);

        printf("\nAccount number: \n");
        scanf("%[^\n]s",&acc_no);
        fprintf(ptr_create, "%s@", acc_no);
        fflush(stdin);

        printf("\nDeposit: \n");
        scanf("%d",&balance);
        fprintf(ptr_create, "%d@", balance);
        fflush(stdin);

        fprintf(ptr_create, "/");

        printf("\nYour account has been created\n");
        fclose(ptr_create);

    }
    else if(init_ip == 2)
    {
        int i=0, balancesPos[1000],namesPos[1000];

        ptr_create = fopen("users.txt","r");

        char c;
        while(c != EOF)
        {
            namesPos[i] = ftell(ptr_create);
            fscanf(ptr_create, "%[^@]s", &names[i][100]);
            fseek(ptr_create, 1, SEEK_CUR);

            fscanf(ptr_create, "%[^@]s", &passwords[i][100]);
            fseek(ptr_create, 1, SEEK_CUR);

            fscanf(ptr_create, "%[^@]s", &acc_nos[i][100]);
            fseek(ptr_create, 1, SEEK_CUR);
            balancesPos[i] = ftell(ptr_create);

            fscanf(ptr_create, "%d", &balances[i]);
            fseek(ptr_create, 1, SEEK_CUR);

            fseek(ptr_create, -1, SEEK_CUR);

            fseek(ptr_create, 1, SEEK_CUR);

            if(c == '/') user_count++;

            i++;
            c = fgetc(ptr_create);
        }

        fclose(ptr_create);


        int u_check=0, position_storage,uip;
        char name_check[100];
        char password_check[100];
        char acc_no_check[100];

        log_in:
            {
                printf("\nLOG IN PAGE\n");

                printf("\nAccount number: \n");
                scanf("%[^\n]s",&acc_no_check);
                fflush(stdin);

                printf("\nPassword: \n");
                scanf("%[^\n]s",&password_check);
                fflush(stdin);


                for(i=0; i<=user_count; i++)
                {
                    if((strcmp(passwords[i],password_check)==0) && (strcmp(acc_nos[i],acc_no_check)==0))
                    {
                        u_check++;
                        position_storage = i;
                    }
                }
            }
            if(u_check == 1)
            {
                // coding the user page
                printf("\nUSER EXISTS\n");
//
                sleep(1);
                system("cls");

                printf("\tHello %s\n",names[position_storage]);

                printf("\nYour account number is: %s\n",acc_nos[position_storage]);

                printf("\nBalance: %d\n",balances[position_storage-1]);

                restart:
                printf("\nWhat do you want to do?\n");
                printf("\n1. Deposit\n");
                printf("\n2. Withdraw\n");
                printf("\n3. Close the account\n");


                printf("\nYour choice: ");
                scanf("%d",&uip);
                fflush(stdin);

                int depo;
                char uip2;

                if(uip == 1)
                {
                    //1. Deposit
                    printf("\nHow much money do you want to deposit?\n");
                    scanf("%d",&depo);

                    FILE *ptr_create_temp;

                    ptr_create = fopen("users.txt","r");
                    fseek(ptr_create, balancesPos[position_storage-1],SEEK_SET);

                    char cdd; int t_cntn=0;
                    while(cdd != '@')
                    {
                        t_cntn++;
                        cdd = fgetc(ptr_create);
                    }

                    fclose(ptr_create);


                    // yaha se wapis se starting
                    char buf[500];
                    ptr_create = fopen("users.txt","r");
                    fread(buf, sizeof(char), balancesPos[position_storage-1], ptr_create);
                    buf[balancesPos[position_storage-1]] = '\0';


                    // ab update kravaenge
                    ptr_create_temp = fopen("temp.txt","w");
                    int data = balances[position_storage-1]+depo;


                    char c; int total_count=0;
                    while(c != EOF)
                    {
                        total_count++;
                        c = fgetc(ptr_create);
                    }


                    char new_buf[500];

                    fseek(ptr_create, balancesPos[position_storage-1]+t_cntn-1, SEEK_SET);
                    fread(new_buf, sizeof(char),1000, ptr_create);
                    new_buf[total_count+1] = '\0';




                    // printing the data
                    fprintf(ptr_create_temp,"%s",buf);
                    fprintf(ptr_create_temp,"%d", data);
                    fprintf(ptr_create_temp,"%s", new_buf);

                    fclose(ptr_create);
                    fclose(ptr_create_temp);



                    int value1, value2;
                    // File name is changed here
                    value1 = rename("users.txt", "old.txt");
                    value2 = rename("temp.txt", "users.txt");

                    // Print the result v1
                    if (!value1) {
                        printf("%s", "\nDeposited successfully\n");
                    }
                    else {
                        perror("Error v1");
                    }

                    // Print the result v2
                    if (!value2) {
                        printf("");
                    }
                    else {
                        perror("Error v2");
                    }
                }
                else if(uip==2)
                {
                    //1. Deposit
                    printf("\nHow much money do you want to withdraw?\n");
                    scanf("%d",&depo);

                    FILE *ptr_create_temp;

                    ptr_create = fopen("users.txt","r");
                    fseek(ptr_create, balancesPos[position_storage-1],SEEK_SET);

                    char cdd; int t_cntn=0;
                    while(cdd != '@')
                    {
                        t_cntn++;
                        cdd = fgetc(ptr_create);
                    }

                    fclose(ptr_create);


                    // yaha se wapis se starting
                    char buf[500];
                    ptr_create = fopen("users.txt","r");
                    fread(buf, sizeof(char), balancesPos[position_storage-1], ptr_create);
                    buf[balancesPos[position_storage-1]] = '\0';


                    // ab update kravaenge
                    ptr_create_temp = fopen("temp.txt","w");
                    int data = balances[position_storage-1]-depo;



                    char c; int total_count=0;
                    while(c != EOF)
                    {
                        total_count++;
                        c = fgetc(ptr_create);
                    }


                    char new_buf[500];

                    fseek(ptr_create, balancesPos[position_storage-1]+t_cntn-1, SEEK_SET);
                    fread(new_buf, sizeof(char),1000, ptr_create);
                    new_buf[total_count+1] = '\0';


                    // printing the data
                    fprintf(ptr_create_temp,"%s",buf);
                    fprintf(ptr_create_temp,"%d", data);
                    fprintf(ptr_create_temp,"%s", new_buf);

                    fclose(ptr_create);
                    fclose(ptr_create_temp);



                    int value1, value2;
                    // File name is changed here
                    value1 = rename("users.txt", "old.txt");
                    value2 = rename("temp.txt", "users.txt");

                    // Print the result v1
                    if (!value1) {
                        printf("\nWithdrawn successfully\n");
                    }
                    else {
                        perror("Error v1");
                    }

                    // Print the result v2
                    if (!value2) {
                        printf("");
                    }
                    else {
                        perror("Error v2");
                    }
                }
                else if(uip==3)
                {
                    printf("\nAre you sure?(y/n) ");
                    scanf("%c",&uip2);

                    if(uip2=='y')
                    {
                        FILE *ptr_create_temp;

                        fclose(ptr_create);


                        // yaha se wapis se starting
                        char buf[5000];
                        ptr_create = fopen("users.txt","r");
                        fread(buf, sizeof(char), namesPos[position_storage-1], ptr_create);
                        buf[namesPos[position_storage]] = '\0';



                        // ab update kravaenge
                        ptr_create_temp = fopen("temp.txt","w");


                        char c; int total_count=0;
                        while(c != EOF)
                        {
                            total_count++;
                            c = fgetc(ptr_create);
                        }


                        char new_buf[5000];

                        fseek(ptr_create, namesPos[position_storage], SEEK_SET);
                        fread(new_buf, sizeof(char),5000, ptr_create);
                        new_buf[total_count+1] = '\0';


                        // printing the data
                        fprintf(ptr_create_temp,"%s",buf);
                        fprintf(ptr_create_temp,"%s", new_buf);

                        fclose(ptr_create);
                        fclose(ptr_create_temp);



                        int value1, value2;
                        // File name is changed here
                        value1 = rename("users.txt", "old.txt");
                        value2 = rename("temp.txt", "users.txt");

                        // Print the result v1
                        if (!value1) {
                            printf("%s", "\nAccount closed successfully\n");
                        }
                        else {
                            perror("Error v1");
                        }

                        // Print the result v2
                        if (!value2) {
                            printf("");
                        }
                        else {
                            perror("Error v2");
                        }
                    }
                    else
                    {
                        printf("\nOkay!\n");
                        goto restart;
                    }
                }
                else
                {
                    printf("\nWrong input! Quitting\n");
                    exit(0);
                }

            }
            else
            {
                printf("\nUnable to identify...Please re-enter...\n");
                goto log_in;
            }

    }

    return 0;
}
