// OS_LAB5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <windows.h>




using namespace std;

bool flag = true;
sem_t sem;

void* func1(void* arg) {
	int num = 2;
	ofstream fout("newFile.txt", ios_base::app);
	while (flag) {
		sem_wait(&sem);
		if (fout.is_open()) {
			for (int i = 0; i < 5; i++) {
				if (!flag) {
					break;
				}
				fout << num;
				cout << num << " ";
				cout.flush();
				Sleep(1);
			}
		}
		else {
			cout << "File does not exist!";
		}
		sem_post(&sem);
		Sleep(1);
		}
		fout.close();
		return NULL;
	}
int main() {
	sem_open("/sem", O_CREAT, 0644, 1);
	pthread_t thread1;
	pthread_create(&thread1, NULL, func1, NULL);
	flag = false;
	pthread_join(thread1, NULL);
	sem_close(&sem);
	sem_unlink("/sem");
	return 0;
}

