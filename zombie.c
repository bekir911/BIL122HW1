/** M Bekir Ozturk
 * 19120205061
 * zombie.c
 * Zombie Simulator
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SLAYER_NUMBER 	0x0003
#define ZOMBIE_NEEDED 	0x0064
#define _2_MS 		0x07D0

typedef pthread_mutex_t mutex;
typedef pthread_cond_t cond;

/* Number of zombies in the game: 
you should synchronize threads editing this variable */
int slayerArr[SLAYER_NUMBER];

int writing1 			= 0;
int writers1 			= 0;
int writing2 			= 0;
int writers2 			= 0;
int reading1 			= 0;
int reading2 			= 0;
int zombieCounter 		= 0;
int totalZombies 		= 0;

mutex m1 	= PTHREAD_MUTEX_INITIALIZER;
mutex m2 	= PTHREAD_MUTEX_INITIALIZER;
cond c1 	= PTHREAD_COND_INITIALIZER;
cond c2 	= PTHREAD_COND_INITIALIZER;

/* Keeps track of number of zombies entered. */
void zombieEntered() {
	pthread_mutex_lock(&m1);
	++writers1;

	while (reading1 || writing1) {
		pthread_cond_wait(&c1, &m1);
	}

	++writing1;
	pthread_mutex_unlock(&m1);

	++zombieCounter;
	++totalZombies;

	pthread_mutex_lock(&m1);
	--writing1;
	--writers1;
	pthread_cond_broadcast(&c1);
	pthread_mutex_unlock(&m1);
}

/* Keeps track of number of zombies killed.*/
void zombieKilled() {
	pthread_mutex_lock(&m1);
	++writers1;

	while (reading1 || writing1) {
		pthread_cond_wait(&c1, &m1);
	}

	++writing1;
	pthread_mutex_unlock(&m1);

	--zombieCounter;

	pthread_mutex_lock(&m1);
	--writing1;
	--writers1;
	pthread_cond_broadcast(&c1);
	pthread_mutex_unlock(&m1);
}

/* Returns true if number of zombies in the room are 
greater than or equal to 100. */
int tooManyZombiesInTheRoom() {
	pthread_mutex_lock(&m1);

	while (writers1) {
		pthread_cond_wait(&c1, &m1);
	}

	++reading1;
	pthread_mutex_unlock(&m1);

	int result = zombieCounter >= ZOMBIE_NEEDED;

	pthread_mutex_lock(&m1);
	--reading1;
	pthread_cond_signal(&c1);
	pthread_mutex_unlock(&m1);

	return result;
}

/* Returns true if there is at least one zombies in the room. */
int zombiesExist() {
	pthread_mutex_lock(&m1);

	while (writers1) {
		pthread_cond_wait(&c1, &m1);
	}

	++reading1;
	pthread_mutex_unlock(&m1);

	int result = zombieCounter > 0;

	pthread_mutex_lock(&m1);
	--reading1;
	pthread_cond_signal(&c1);
	pthread_mutex_unlock(&m1);

	return result;
}

/* Returns the number of zombies in the room. */
int getInTheRoomCount() {
	pthread_mutex_lock(&m1);

	while (writers1) {
		pthread_cond_wait(&c1, &m1);
	}

	++reading1;
	pthread_mutex_unlock(&m1);

	int result = zombieCounter;

	pthread_mutex_lock(&m1);
	--reading1;
	pthread_cond_signal(&c1);
	pthread_mutex_unlock(&m1);

	return result;
}

/* Returns the number of zombies killed. */
int getKilledCount() {
	pthread_mutex_lock(&m2);

	while (writers2) {
		pthread_cond_wait(&c2, &m2);
	}

	++reading2;
	pthread_mutex_unlock(&m2);

	int result = slayerArr[0] + slayerArr[1] + slayerArr[2];

	pthread_mutex_lock(&m2);
	--reading2;
	pthread_cond_signal(&c2);
	pthread_mutex_unlock(&m2);

	return result;
}

/* Returns true if more than 100 zombies have been killed. */
int killed100Zombies() {
	return getKilledCount() >= ZOMBIE_NEEDED;
}

/* Increases the number of slayer's kills */
void zombieSlayed(int i) {
	pthread_mutex_lock(&m2);
	++writers2;

	while (reading2 || writing2) {
		pthread_cond_wait(&c2, &m2);
	}

	++writing2;
	pthread_mutex_unlock(&m2);

	++slayerArr[i];

	pthread_mutex_lock(&m2);
	--writers2;
	--writing2;
	pthread_cond_broadcast(&c2);
	pthread_mutex_unlock(&m2);
}

/* Doorman thread */
void *doorMan(void *p) {
	int r = 0;

	while (!killed100Zombies() && !tooManyZombiesInTheRoom()) {
		r = rand() % 2;

		if (r) {
			zombieEntered();
		}

		usleep(_2_MS);
	}

	pthread_exit(NULL);
}

/* Slayer thread */
void *slayer(void *p) {
	long i = (long)((long*)p);

	while (!killed100Zombies() && !tooManyZombiesInTheRoom()) {
		if (zombiesExist()) {
			zombieSlayed(i);
			zombieKilled();
		}

		usleep(_2_MS);
	}

	pthread_exit(NULL);
}

/* Frees/destroys mutexes, condition variables and memory location */
void destroyAll(pthread_t* t, mutex* m1, mutex* m2, cond* c1, cond* c2) {
	pthread_mutex_destroy(m1);
	pthread_mutex_destroy(m2);
	pthread_cond_destroy(c1);
	pthread_cond_destroy(c2);
	free(t);
}

/* Prints game info when finished */
void endGame() {
	printf("Game ended cause ");

	if (killed100Zombies()) {
		printf("100 zombies are killed.\n");
	}
	else {
		printf("there were more than 100 zombies in the room.\n");
	}

	printf("%d zombies are created.\n", totalZombies);
	printf("%d zombies have been killed.\n", getKilledCount());
	printf("%d zombies are in the room.\n", getInTheRoomCount());

	for (int i = 0; i < SLAYER_NUMBER; ++i) {
		printf("%d. slayer has slayed %d zombies.\n", i + 1, slayerArr[i]);
	}
}

/* Simulator main thread */
int main(int argc, char **argv) {
	/* 12 doormans seem reasonable */
	int n = atoi(argv[1]);
	srand(time(NULL));
	slayerArr[0] = 0;
	slayerArr[1] = 0;
	slayerArr[2] = 0;
	int r = 0;
	
	pthread_t slayers[SLAYER_NUMBER];
	pthread_t* doorMans = (pthread_t*)malloc(sizeof(pthread_t) * n);

	/* If malloc fails */
	if (NULL == doorMans) {
		perror("malloc error");
		destroyAll(doorMans, &m1, &m2, &c1, &c2);
		return -1;
	}

	/* doorMans create */
	for (int i = 0; i < n; ++i) {
		r = pthread_create(&doorMans[i], NULL, doorMan, NULL);

		if (r) {
			perror("thread error doorMan");
			destroyAll(doorMans, &m1, &m2, &c1, &c2);
			return -2;
		}
	}

	/* slayers create */
	for (long i = 0; i < SLAYER_NUMBER; ++i) {
		/* Value of i changes in main, that's why it is not reference */
		r = pthread_create(&slayers[i], NULL, slayer, (void*)i);

		if (r) {
			perror("thread error slayer");
			destroyAll(doorMans, &m1, &m2, &c1, &c2);
			return -3;
		}
	}

	/* doorMans join */
	for (int i = 0; i < n; ++i) {
		pthread_join(doorMans[i], NULL);
	}

	/* slayers join */
	for (int i = 0; i < SLAYER_NUMBER; ++i) {
		pthread_join(slayers[i], NULL);
	}

	endGame();

	destroyAll(doorMans, &m1, &m2, &c1, &c2);
	
	return 0;
}
