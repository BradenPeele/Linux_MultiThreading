#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void *runner(void *param);

int main(int argc, char *argv[]) {

	pthread_attr_t attr;
	string filename;
	int numThreads;
	string password;
	
	cout << "Filename: ";
	cin >> filename;
	
	// open file
	ifstream inFile(filename);
	if(!inFile.is_open()) {
		cout << "File error" << endl;
		exit(EXIT_FAILURE);
	}
	
	cout << "Number of threads: ";
	cin >> numThreads;
	
	cout << endl;
	
	pthread_t threadArr[numThreads];
	pthread_attr_init(&attr);
	
	// main loop for using threads
	while(!inFile.eof()) {
		for(int n = 0; n < numThreads; n++) {
			getline(inFile, password);
			if(inFile.eof()) // stop if done with file 
				return 0;
			pthread_create(&threadArr[n], &attr, runner, &password);
			pthread_join(threadArr[n], NULL);
		}
	}
	
	return 0;
}

void *runner(void *param) {
	
	string &password = *(static_cast<string*>(param));
	int length = password.length();
	char* charArr = new char[length+1];
	strcpy(charArr, password.c_str());
	
	// last char stored
	char temp = charArr[length-1];

	// shift letters
	for(int n = length-1; n >= 1; n--)
		charArr[n] = charArr[n-1];
		
	// reassign temp
	charArr[0] = temp;
	
	cout << "Password: " << password << "    Encryption: ";
	
	// increment letter values
	for(int n = 0; n < length; n++) {
		charArr[n] = charArr[n] + 1;
		cout << charArr[n];
	}
	
	cout << endl << endl;
	
	pthread_exit(0);
	return NULL;
}
