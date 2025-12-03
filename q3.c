#include<stdio.h>
struct employee {
	int id;
	char name[50];
	char designation[50];
	float salary;
	
};
void displayemployees(struct employee e[],int n);
void findhighestsalary(struct employee e[],int n);
void searchemployees(struct employee e[],int n);
void givebonus(struct employee e[],int n,float threhold);

int main(){

	int i,n;
	printf("enter nno of employees\n");
	scanf("%d",&n);
		struct employee e[n];
	for(i=0;i<n;i++){
		printf("employee id:\n");
		scanf("%d",&e[i].id);
		
			printf("name:\n");
		scanf("%s",&e[i].name);
		
			printf("designation:\n");
		scanf("%s",&e[i].designation);
		
			printf("salary:\n");
		scanf("%f",&e[i].salary);
	}
	printf("employees records\n");
	displayemployees(  e, n);
	
	printf("highest salary employee\n");
    findhighestsalary( e, n);
    
    printf("search employees\n");
    searchemployees(e, n);
    
    printf("10percent discount to below 50000\n");
    givebonus(e, n,50000);
    
    printf("updated record\n");
    displayemployees(  e, n);
    
    return 0;

	
}

void displayemployees(struct employee e[], int n) {
    int i;

    printf("\n%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("--------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-20s %-10.2f\n",
               e[i].id, e[i].name, e[i].designation, e[i].salary);
    }
}

void findhighestsalary(struct employee e[], int n) {
    int i, index = 0;
    float max = e[0].salary;

    for (i = 1; i < n; i++) {
        if (e[i].salary > max) {
            max = e[i].salary;
            index = i;
        }
    }

    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           e[index].id, e[index].name, e[index].designation, e[index].salary);
}

void searchemployees(struct employee e[], int n) {
    int choice;
    printf("Search by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id, i, found = 0;
        printf("Enter ID to search: ");
        scanf("%d", &id);

        for (i = 0; i < n; i++) {
            if (e[i].id== id) {
                printf("Employee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                found = 1;
                break;
            }
        }
        if (!found) printf("Employee with ID %d not found.\n", id);

    } else if (choice == 2) {
        char name[50];
        int i, found = 0;
        printf("Enter Name to search: ");
        scanf("%s", name);

        for (i = 0; i < n; i++) {
            if (strcmp(e[i].name, name) == 0) {
                printf("Employee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                found = 1;
                break;
            }
        }
        if (!found) printf("Employee named %s not found.\n", name);

    } else {
        printf("Invalid choice.\n");
    }
}

void givebonus(struct employee e[], int n, float threshold) {
    int i;
    for (i = 0; i < n; i++) {
        if (e[i].salary < threshold) {
            e[i].salary = e[i].salary + e[i].salary * 0.10;
        }
    }
    printf("Bonus added successfully!\n");
}
