/* Nama :Dean Christoper
  Tugas : Algoritma struktur Data
  			ROUND ROBIN SCHEDULING

*/

/* File : roundrobin */
/* ADT roundrobin menggunankan List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* Definisi type boolean */

#ifndef _BOOLEAN_h
#define _BOOLEAN_h

#define boolean unsigned char
#define true 1
#define false 0

#endif

#define Nil NULL

/* Representasi berkait dengan address adalah pointer */
/* infotype adalah integer */
/*infochar adalah character */

typedef int infotype;
typedef char infochar;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
	infotype info;
	infochar data;
	address next;
} ElmtList;
typedef struct {
	address First;
} List;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list: jika addressnya Last, maka Next(Last)=First(L) */

/* Notasi Akses */
#define Info(P) (P)->info
#define Data(P) (P)->data
#define Next(P) (P)->next
#define First(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return (First(L)==Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
		First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X, infochar Y)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	address P;
	P = (address) malloc (sizeof(ElmtList));
	if(P!=NULL){
		Info(P)=X;
		Data(P)=Y;
		Next(P)=Nil;
		return P;
	}else
		return Nil;
}
void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	address Q = First(*L);
	if(Q==Nil){ // empty list
		First(*L) = P;
		Next(P) = P;
	}else{
		Next(P) = Q;
		while(Next(Q)!=First(*L))
			Q = Next(Q);
		First(*L) = P;
		Next(Q) = P;
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	address Q = First(*L);
	*P = First(*L);
	if(Next(Q) == Q){ // one element
		First(*L) = Nil;
	}else{
		while(Next(Q)!=First(*L))
			Q = Next(Q);
		First(*L) = Next(First(*L));
		Next(Q) = First(*L);
	}
}

void DelP (List *L, address *P)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	address precP = Nil;
	address Q = First(*L);
		// searching element before P
		while(Q != *P){
			precP = Q;
			Q = Next(Q);
		}
			if(precP == Nil){
				DelFirst(&(*L), &(*P));
			}else{
				Next(precP) = Next(Q);
				Next(Q) = Nil;
			}
			
			Dealokasi(*P);
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	address P = First(L);

	if(P!=Nil){
		printf("| %c      |      %d   |\n", Data(P), Info(P));
		P=Next(P);
		while (P!=First(L)){
			printf("| %c      |      %d   |\n",Data(P), Info(P));
			P = Next(P);
		}
	} else {
		printf("List Kosong\n");
	}
}

/****************** PROSES ROUND ROBIN SCHEDULING ******************/
void RRS (List *L, infotype Quantum)
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
					printf("| %c   	 |	     %d| >> %c = %d\n", Data(P), Quantum, Data(P), Info(P));
				}else{
					printf("| %c   	 |	     %d| >> %c = %d. Dispose %c\n", Data(P), Quantum, Data(P), Info(P), Data(P));
				}
				sum=sum+Quantum+sw;
					if(Info(P)<=0){
						if(P ==Q){
						break;
							
					}
			}
			printf("| Switch |	     %d|\n", sw);
	
		}else{
			DelP(&(*L),&P);
			Dealokasi(P);
			P = Q;
		}
				P = Q;
					
		}
	
		
		
		printf("+---------------------+\n");
		printf("| Total    |	    %d|\n", sum-1);
		printf("+---------------------+\n");
}


int main(){
	int jumlah, quantum,quanta;
	char data;
	address P;
	int i;
	List L;
	CreateEmpty(&L);
	printf("Jumlah Data        : ");
	scanf("%d", &jumlah);

	printf("Quantum Per Proses : ");
	scanf("%d", &quantum);
	printf("\n");

	for(i=0; i<jumlah;i++){
		printf("Simpul #%d\n",i+1);
		printf("Data   #%d  : ",i+1);
		scanf("%s",&data);
		printf("Quanta #%d  : ",i+1);
		scanf("%d", &quanta);
		printf("\n");
		InsertFirst(&L,Alokasi(quanta,data));
	}

	printf(" Data  >>\n");
	printf(" +--------+-----------+\n");
	printf(" | Data   |     Quanta|\n");
	printf(" +--------------------+\n");
	PrintInfo(L);
	printf("+--------------------+\n");
	printf("\n");
        
    printf("Proses  >>\n");
    printf("+--------+------------+\n");
	printf("| Data   |     Quantum|\n");
	printf("+---------------------+\n");
	RRS(&L, quantum);
        
	return 0;
}
