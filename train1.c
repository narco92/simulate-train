
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>


/* Les gares */
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4


/* Code des threads */
void* chemain_ABCBA(void* arg);
void* chemain_ABDCBA(void* arg);
void* chemain_ABDCEA(void* arg);

pthread_mutex_t mut_AB;
pthread_mutex_t mut_BC;
pthread_mutex_t mut_DB;

/* Gestion du chemin de fer  */
void utiliser_le_chemain(int gare_depart, int gare_arrivee){

	if  ( (gare_depart == A) && (gare_arrivee == B) )
		pthread_mutex_lock(&mut_AB);
	else
		if  ( (gare_depart == B) && (gare_arrivee == C) )
			pthread_mutex_lock(&mut_BC);
		else
			
			pthread_mutex_lock(&mut_DB);
}


void liberer_le_chemain(int gare_depart, int gare_arrivee){
	if  ( (gare_depart == A) && (gare_arrivee == B) )
		pthread_mutex_unlock(&mut_AB);
	else
		if  ( (gare_depart == B) && (gare_arrivee == C) )
			pthread_mutex_unlock(&mut_BC);
		else
			pthread_mutex_unlock(&mut_DB);
}


int main(int argc, char* argv[])
{
	
	pthread_t   train1;
	pthread_t   train2;
	pthread_t   train3;
	

	pthread_mutex_init(&mut_AB,0);
	pthread_mutex_init(&mut_BC,0);
	pthread_mutex_init(&mut_DB,0);
	
	
	pthread_create(&train1, NULL, chemain_ABDCBA, NULL);
	pthread_create(&train2, NULL, chemain_ABDCBA, NULL);
	pthread_create(&train3, NULL, chemain_ABDCEA, NULL);

	pthread_join(train1, NULL)
	pthread_join(train2, NULL)
	pthread_join(train3, NULL)
		

	pthread_exit(NULL);
}


void* chemain_ABCBA(void* arg)
{
	utiliser_le_chemain(A, B);
	printf("Train %d : utilise AB \n",pthread_self());
	attendre(6);
	liberer_le_chemain(A, B);

	utiliser_le_chemain(B, C);
	printf("Train %d : utilise BC \n",pthread_self());
	attendre(6);
	liberer_le_chemain(B, C);

	utiliser_le_chemain(C, B);
	printf("Train %d : utilise CB \n",pthread_self());
	attendre(6);
	liberer_le_chemain(C, B);

	utiliser_le_chemain(B, A);
	printf("Train %d : utilise AB \n",pthread_self());
	attendre(6);
	liberer_le_chemain(B, A);

	pthread_exit(NULL);
}

void* chemain_ABDCBA(void* arg)
{
	utiliser_le_chemain(A, B);
	printf("Train %d : utilise AB \n",pthread_self());
	attendre(5);
	liberer_le_chemain(A, B);

	utiliser_le_chemain(B, D);
	printf("Train %d : utilise BD \n",pthread_self());
	attendre(5);
	liberer_le_chemain(B, D);

	utiliser_le_chemain(D, C);
	printf("Train %d : utilise DC \n",pthread_self());
	attendre(5);
	liberer_le_chemain(D, C);

	utiliser_le_chemain(C, B);
	printf("Train %d : utilise CB \n",pthread_self());
	attendre(6);
	liberer_le_chemain(C, B);

	utiliser_le_chemain(B, A);
	printf("Train %d : utilise AB \n",pthread_self());
	attendre(6);
	liberer_le_chemain(B, A);

	pthread_exit(NULL);
}

void* chemain_ABDCEA(void* arg)
{
	utiliser_le_chemain(A, B);
	printf("Train %d : utilise AB \n",pthread_self());
	attendre(5);
	liberer_le_chemain(A, B);

	utiliser_le_chemain(B, D);
	printf("Train %d : utilise BD \n",pthread_self());
	attendre(5);
	liberer_le_chemain(B, D);

	

	pthread_exit(NULL);
}





int tirage_aleatoire(double max)
{
        int j=(int) (max*rand()/(RAND_MAX+1.0));
        if(j<1)
                j=1;
        return j;
}



void attendre(double max)
{
        struct timespec delai;

        delai.tv_sec=tirage_aleatoire(max);
        delai.tv_nsec=0;
        nanosleep(&delai,NULL);
}

