#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 typedef struct{
 	int employeeid;
 	char name[20];
 	char designation[20];
 	float salary;
 }employee;
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

 
 void displayrecord(employee employees[],int n){
 	int i;
 	printf("\n=============================\n");
 	printf("%-10s %-20s %-20s %-10s\n","ID","NAME","DESIGNATION","SALARY");
 	printf("\n==============================\n");
 	for(i=0;i<n;i++){
 	printf("%-10d %-20s   %-20s %-10f\n",employees[i].employeeid,employees[i].name,employees[i].designation,employees[i].salary);
 	}printf("\n=============================\n");
	 }
	 void highestsalary(employee employees[],int n){
	 	int maxindex=0,i=0;
	 	for(i=0;i<n;i++){
	 		if(employees[i].salary>employees[maxindex].salary){
	 			maxindex=i;
	 			
			 }}
    printf("ID: %d\n", employees[maxindex].employeeid);
    printf("Name: %s\n", employees[maxindex].name);
    printf("Designation: %s\n", employees[maxindex].designation);
    printf("Salary: %.2f\n", employees[maxindex].salary);
}
			 
	 		
	 		
		 
	 void applybonus(employee employees[],int n,int t){
	 int i=0;
	 	for(i=0;i<n;i++){
	 		if(employees[i].salary<t)
	 		employees[i].salary=employees[i].salary+((10.0/100.0)*employees[i].salary);
		 }
		 displayrecord(employees,n);
	}
	
	void searchemployee(employee employees[], int n) {

    int choice;
    printf("\nSearch by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);
    clear_input_buffer();

    if (choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);
int i;
        for (i=0; i<n; i++) {
            if (employees[i].employeeid == id) {
                printf("\nRecord Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       employees[i].employeeid,
                       employees[i].name,
                       employees[i].designation,
                       employees[i].salary);
                return;
            }
        }
        printf("Employee Not Found.\n");
    }

    else if (choice == 2) {
        char nameSearch[20];
        printf("Enter Employee Name: ");
        
        scanf("%[^\n]",nameSearch);
int i;
        for ( i=0; i<n; i++) {
            if (strcmp(employees[i].name,nameSearch) == 0) {
                printf("\nRecord Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       employees[i].employeeid,
                       employees[i].name,
                       employees[i].designation,
                       employees[i].salary);
                return;
            }
        }
        printf("Employee Not Found.\n");
    }

    else {
        printf("Invalid Choice!\n");
    }
}
	
	 	

	 
 	
 
 int main(){
 	int num;
 	
 	int i;
 	char opt;
 	printf("\nEnter number of employees in your company:\n");
 	scanf("%d",&num);
 	employee *employees=(employee*)malloc(num*sizeof(employee));
 	if(employees==NULL){
 		printf("memory allocation failed! exit program");
 		return;
	 }
 	for(i=0;i<num;i++){
 		printf("Enter %d employee ID:",i+1 );
 		scanf("%d",&employees[i].employeeid);

		 
 		printf("Enter name of %d employee:",i+1);
 		scanf(" %[^\n]",&employees[i].name);
 		printf("Enter designation of %d employee:",i+1,&employees[i].designation);
 		scanf(" %[^\n]",&employees[i].designation);
 		printf("\nEnter Salary of %d employee",i+1);
 		scanf("%f",&employees[i].salary);
 } 
 
 			
 			
			 
			
			do{
				printf("\nchoose an option\n");
				printf("ENTER d for displaying all record");
			printf("\nENTER h for higestsalary finding of the employee\n");
			printf("\nENTER s for searching specific employee data\n");
			printf("\nEnter b for increasing salary of employees whose salary is less than 50k\n ");
			printf("\nENTER e for exit\n");
			printf("\nChoose your option\n");
			scanf(" %c",&opt);
			
			switch(opt){
				case 'd':
					printf("\n===All employee record===\n");
					displayrecord(&employees,num);
					break;
					
			case 'h':
 			printf("\n===EMPLOYEE WITH HIGHEST SALARY===\n");
 			highestsalary(employees,num);
 			break;
 			case 's':
 			printf("\n===SEARCH EMPLOYESS===\n");
 			searchemployee(employees,num);
 			break;
 			case 'b':
 				applybonus(employees,num,50000);
 				break;
 				case 'e':
 					printf("\nEND program\n");
 					break;
 					default:
 						printf("\nINVALID input\n");}}
 		while(opt!='e');
 	free(employees);
 	employees=NULL;
 			
		 
		 return 0; }
 		
 		
 		
 	
