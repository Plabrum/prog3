#include <iostream>
#include <string>
#include <fstream>
// #include <cmath>
// #include <chrono>
//Does this work?
using namespace std;

int kk(int* ints){
	// Perform Karmarkar-Karp Algorithm
	return 0;
}
int rr(int* ints){	
	// Perform Repeated Random Algorithm
	return 0;
}
int hc(int* ints){	
	// Perform Hill Climbing Algorithm
	return 0;
}
int sa(int* ints){	
	// Perform Simulated Annealing Algorithm
	return 0;
}
int prr(int* ints){	
	// Perform Prepartitioned Repeated random Algorithm
	return 0;
}
int phc(int* ints){	
	// Perform Prepartitioned Hill Climbing Algorithm
	return 0;
}
int psa(int* ints){	
	// Perform Prepartitioned Simulated Annealing Algorithm
	return 0;
}

int* read_in(string filename){
	fstream in_file(filename);
	if (in_file.is_open())
	{	string line;

		int i = 0;
		int *data = new int[100];

		while (getline(in_file,line)){
			data_all[i] = stoi(line)
			i++;
		}
		// Close file because we have already stored the array
		in_file.close();
		return data_all;
	}
	else {
		cout << "Unable to open file";
		return NULL;
	}
}

void write_out(string filename, int* data){
	fstream out_file(filename);
	if (out_file.is_open()){
		for (int i=0; i<100; i++){
			out_file << data[i] << "\n";
		}
		out_file.close();
	}
	else cout << "unable to open output file \n";
}

int main(int argc, char *argv[]){
	if (argc != 4){
		cout << "format is ./partition 0 algorithm inputfile";
		return 0;
	}

	int setting = stoi(argv[1]);
	int algorithm = stoi(argv[2]);
	string filename = argv[3];
	int* input_array = read_in(filename);
	int residue;

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

	// Change global debug bool to print out dims during strassen
	debug = false;

	if (setting == 0){
		// Run normal Program, no extraneous prints
		cout << residue << endl;
	}
	return 0;
}
