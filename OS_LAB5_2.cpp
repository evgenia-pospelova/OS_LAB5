// OS_LAB5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>






using namespace std;

bool flag = true;
sem_t* sem;
FILE* fileName;

void* func1(void* ) {
	const char num = '2';
	while (flag) {
		sem_wait(sem);
			for (int i = 0; i < 5; i++) {
				if (!flag) {
					break;
				}
				fputs(&num,fileName);
                cout << num << endl;
                sleep(1);
            }
		
		sem_post(sem);
		sleep(1);		
	}
    return NULL;
}
int main() {
	sem = sem_open("/sem", O_CREAT, 0644, 10);
    fileName = fopen("test.txt","a"); //"a" - дописывает инф. к конфу файла
	pthread_t thread1;
	pthread_create(&thread1, NULL, func1, NULL);
	flag = false;
	pthread_join(thread1, NULL);
	sem_close(sem);
	sem_unlink("/sem");
    fclose(fileName);
	return 0;
}
