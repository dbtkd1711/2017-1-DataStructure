#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size;
typedef struct employee{
	char name[20];
	int age;
	int salary;
	char department[20];
} employee;

void insert(employee * emp);
void delete(employee * emp, char * str);
int find(employee * emp, char * str);
void inform(employee * emp, char * str);
int avgBenefit(employee * emp, char * str);

int main(){

	employee * emp;
	char conduct[20];
	char whom[20];
	int i,n1, n2, cur;

	printf("set ");
	scanf("%d", &size);
	getchar();

	emp = (employee *)calloc(size, sizeof(employee));

	while(1){
		cur=0;
		while(1){
			conduct[cur] = getchar();
            // 1. Enter -> Finish the process
			if(conduct[0] == '\n')
				return 0;
            // 2. Others -> Continue
			if(conduct[cur] == ' ' || conduct[cur] == '\n'){
				conduct[cur] = '\0';
				break;
			}

            cur++;
        }

		if(strcmp(conduct, "insert")==0){
			insert(emp);
		}
		else if(strcmp(conduct, "delete")==0){
			scanf("%s", whom);
			getchar();
			delete(emp, whom);
		}
		else if(strcmp(conduct, "find")==0){
			scanf("%s", whom);
			getchar();
			n1=find(emp, whom);
			printf("%d \n", n1);
		}
		else if(strcmp(conduct, "inform")==0){
			scanf("%s", whom);
			getchar();
			inform(emp, whom);
		}
		else if(strcmp(conduct, "avg")==0){
			scanf("%s", whom);
			getchar();
			n2=avgBenefit(emp, whom);
			printf("%d \n", n2);
		}
		else
			printf("실행할 명령어를 다시 입력하시오.\n");
	}

	return 0;
}

void insert(employee * emp){

	int i, cur=0;

	for(i=0 ; i<size ; i++){
		if(strlen(emp[i].name)!=0)
			cur++;
		else
			break;
	}

	if(cur==size){
		printf("full\n");
		while(getchar()!='\n');
	}
	else{
		scanf("%s", emp[i].name);
		scanf("%d", &emp[i].age);
		scanf("%d", &emp[i].salary);
		scanf("%s", emp[i].department);
		getchar();
	}
}

void delete(employee * emp, char * str){

	int i, cur=0;

	for(i=0;i<size;i++){
		if(strcmp(emp[i].name, str)!=0)
			cur++;
		else{
			emp[i].name[0] = '\0';
			emp[i].age = 0;
			emp[i].salary = 0;
			emp[i].department[0] = '\0';
			break;
		}
	}

	if(cur==size)
		printf("Not found \n");

    return;
}

int find(employee * emp, char * str){

	int i, cur=0, result;

	for(i=0 ; i<size ; i++){
		if(strcmp(emp[i].name, str)!=0)
			cur++;
		else{
			result = i;
			return result;
		}
	}

	if(cur==size){
		result = -1;
		return result;
	}
}

void inform(employee * emp, char * str){

	int i, cur=0, flag=0;

	for(i=0 ; i<size ; i++){
		if(strcmp(emp[i].name, str)!=0)
			cur++;
	    else{
		    printf("%s ", emp[i].name);
		    printf("%d ", emp[i].age);
		    printf("%d ", emp[i].salary);
		    printf("%s\n", emp[i].department);
            flag=1;
	    }
	}

	if(flag==0)
		printf("not found \n");

    return;
}

int avgBenefit(employee * emp, char * str){

	int i, cur=0, sum=0;

	for(i=0 ; i<size ; i++){
		if(strcmp(emp[i].department, str)==0)
			sum += emp[i].salary;
		else
			cur++;
	}

	if(cur!=size)
		return sum/(size-cur);
	else
		return 0;
}
