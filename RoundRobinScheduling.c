/* Nama : Dean Christoper / 14116052

  Tugas : Algoritma struktur Data
  			ROUND ROBIN SCHEDULING
*/

/* File : roundrobinScheduling */
/* ADT roundrobinScheduling menggunankan List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */

#include "ListSirkuler.h"

/****************** PROSES ROUND ROBIN SCHEDULING ******************/
void RRS(List *L, infotype Quantum)
{
	int sum=0;
	int sw=1;
	address P;
	address Q;
	P = First(*L);

	while(!IsEmpty(*L)){
		Q = Next(P);

		if(Info(P)>0){
			Info(P)=Info(P)-Quantum;
				if(Info(P)>0){
					printf(" | %c   	  |	     %d | >> %c = %d\n", Data(P), Quantum, Data(P), Info(P));
				}else{
					printf(" | %c   	  |	     %d | >> %c = %d. Dispose %c\n", Data(P), Quantum, Data(P), Info(P), Data(P));
				}

				sum=sum+Quantum+sw;
					if(Info(P)<=0){
						if(P == Q){
						break;
						}
					}
			printf(" | Switch |	     %d |\n", sw);

		}else{
			DelP(&(*L),&P);
			Dealokasi(P);
			P = Q;
		}
		P = Q;
		}
		printf(" +---------------------+\n");
		printf(" | Total  |	     %d|\n", sum-1);
		printf(" +---------------------+\n");
}

int main(){
	int jumlah, quantum,quanta;
	char data;
	address P;
	int i;
	List L;
	CreateEmpty(&L);
	printf(" _______________________________________________\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("+--------   |||||||||||  V  |||||||||||   ------+\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("+<<<<<<<<<<<<_ROUND ROBIN SCHEDULING_>>>>>>>>>>>+\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("+--------   |||||||||||  V  |||||||||||   ------+\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("+-----------------------------------------------+\n");
	printf("\n\n");
	printf(" INPUT DATA \n\n");
	printf(" Jumlah Data        : ");
	scanf("%d", &jumlah);

	printf(" Quantum Per Proses : ");
	scanf("%d", &quantum);
	printf("\n");

	for(i=0; i<jumlah;i++){
		printf(" Simpul #%d\n",i+1);
		printf(" Data   #%d  : ",i+1);
		scanf("%s",&data);
		printf(" Quanta #%d  : ",i+1);
		scanf("%d", &quanta);
		printf("\n");
		InsertFirst(&L,Alokasi(quanta,data));
	}

	printf("  Data  >>\n");
	printf(" +--------+-------------+\n");
	printf(" | Data   |   Quanta	|\n");
	printf(" +----------------------+\n");
	PrintInfo(L);
	printf(" +----------------------+\n");
	printf("\n");

    printf("  Proses  >>\n");
    printf(" +--------+------------+\n");
	printf(" | Data   |     Quantum|\n");
	printf(" +---------------------+\n");
	RRS(&L, quantum);

	return 0;
}
