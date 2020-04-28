#include <iostream>
#include <string>
#include <fstream>
// #include <cmath>
#include <chrono>
#include <stdint.h>
#include <random>
#include <bitset>
#include <algorithm>

typedef unsigned long long pint;

using namespace std;

int kk(pint* int_list){
	//TODO get size of array
	int length = 100;
	sort(int_list, int_list + length); 
	pint sum = 0; 
	while (sum != -1){
		//Check to see if we are done
		sum = 0;
		for (int i = 0; i < length - 1; i++) 
			//We use length - 1 here because we are done exactly when the second-to-last element is assigned to zero
			sum = sum + int_list[i];
		sum = sum - 1; 
		//This is a hacky way to ensure the program only terminates when the sum is nonzero.
	//update
	}
	return 0;
}

int rr(pint* int_list){	
	// Perform Repeated Random Algorithm
	return 0;
}
int hc(pint* int_list){	
	// Perform Hill Climbing Algorithm
	return 0;
}
int sa(pint* int_list){	
	// Perform Simulated Annealing Algorithm
	return 0;
}
int prr(pint* int_list){	
	// Perform Prepartitioned Repeated random Algorithm
	return 0;
}
int phc(pint* int_list){	
	// Perform Prepartitioned Hill Climbing Algorithm
	return 0;
}
int psa(pint* int_list){	
	// Perform Prepartitioned Simulated Annealing Algorithm
	return 0;
}


pint* read_in(string filename, pint* data){
	fstream in_file(filename);
	if (in_file.is_open())
	{	string line;

		int i = 0;
		// pint data[100];

		while (getline(in_file,line)){
			cout << "reading in line " << i << ": " << line << " as : " << stoull(line) << "\n";
			data[i] = stoull(line);
			cout << "stored as: " << data[i] << endl;
			i++;
		}
		// Close file because we have already stored the array
		in_file.close();
		return data;
	}
	else {
		cout << "Unable to open file";
		return NULL;
	}
}

pint* generate(){
	pint data[100];
	for (int i=0; i < 100; i++){
		// rand only provides 31 randomized bits on Mac OS
		unsigned int a = rand();
		unsigned int b = rand();
		unsigned int c = rand() % 2;
		unsigned int d = rand() % 2;	

		c = c << 31;
		a = c+a;
		d = d << 31;
		b = d+b;

		pint combined = a;
		combined = combined << 32;
		combined += b;
		data[i] = combined + b;
	}
	return data;
}

void write_out(string filename, pint* data){
	fstream out_file(filename);
	if (out_file.is_open()){
		for (int i=0; i<100; i++){
			out_file << data[i] << "\n";
		}
		out_file.close();
	}
	else cout << "unable to open output file \n";
}

void print_out(pint* dat){
	for (int i=0; i<100; i++){
		cout << i+1 << ": " << dat[i] << "\n";
	}
}

string to_bin_32(pint inp){
	std::string bin = std::bitset<32>(inp).to_string();
	return bin;
}

string to_bin_64(pint inp){
	std::string bin = std::bitset<64>(inp).to_string();
	return bin;
}

int main(int argc, char *argv[]){
	if (argc != 4){
		cout << "format is ./partition 0 algorithm inputfile";
		return 0;
	}

	int setting = stoi(argv[1]);
	int algorithm = stoi(argv[2]);
	string filename = argv[3];
	int residue = 0;

	pint input_array[100];
	read_in(filename, input_array);

	// Seed rand
	srand ( time(NULL) );

	switch(algorithm) {
	case 0 :
			// Use Karmarkar-Karp Algorithm
			residue = kk(input_array);
		break;
	case 1 :
			// Use Repeated Random Algorithm
			residue = rr(input_array);
		break;
	case 2 :
			// Use Hill Climbing Algorithm
			residue = hc(input_array);
		break;
	case 3 :
			// Use Simulated Annealing Algorithm
			residue = sa(input_array);
		break;
	case 11 :
			// Use Prepartitioned Repeated random Algorithm
			residue = prr(input_array);
		break;
	case 12 :
			// Use Prepartitioned Hill Climbing Algorithm
			residue = phc(input_array);
		break;
	case 13:
			// Use Prepartitioned Simulated Annealing Algorithm
			residue = psa(input_array);
		break;
   }

	if (setting == 0){
		// Run normal Program, no extraneous prints
		cout << residue << endl;
	}

	return 0;
}
