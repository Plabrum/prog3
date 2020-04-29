#include <iostream>
#include <string>
#include <fstream>
// #include <cmath>
#include <chrono>
#include <stdint.h>
#include <random>
#include <bitset>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <functional>


typedef unsigned long long pint;

using namespace std;

const bool debug = true;
const int iterations = 25;

void print_out(pint* dat){
	for (int i=0; i<5; i++){
		cout << i+1 << ": " << dat[i] << "\n";
	}
}

//Helper functions
pint secondlargest(vector<pint> v){
	//We assume v is a binary heap
	//cout << "top two: " << v[1] << ", " << v[2] << endl;
	if (v[1] > v[2]){
		//cout << v[1] << endl;
		return 1;
	}
	else {
		//cout << v[2];
		return 2;
	}
}

int kk(vector<pint> inputvector){
	//TODO get size of array
	int length = inputvector.size();
	cout << "Doing KK" << endl;
	// Print input list
	// cout << "Input list: \n" << endl;
	// print_out(int_list);

 //    vector <pint> inputvector;
 //   	for (int i = 0; i < length; i++){
 //   		inputvector.push_back(int_list[i]);
 //   	}
   	make_heap(inputvector.begin(), inputvector.end());
   	if (debug){
   		for (int i = 0; i < length; i++){
   			cout << inputvector[i] << endl;
   		}
   	}
   	

   	while (inputvector[secondlargest(inputvector)] != 0){
   		pint subtractor = inputvector[secondlargest(inputvector)];
   		if (debug){
   			cout << "subtractor is: " << subtractor << endl;
   			cout << "largest number is: " << inputvector[0] << endl;
   		}
   		inputvector[0] = inputvector[0] - subtractor;
   		inputvector[secondlargest(inputvector)] = 0;

   		make_heap(inputvector.begin(), inputvector.end());
   		for (int i = 0; i < length; i++){
   			if (debug == true){
   				cout << inputvector[i] << "    ";
   			}
   		}
   		if (debug){
   			cout << endl;
   		}
   	}
   	if (debug == true){
   		cout << "end ofintermediate heaps" << endl;
   		for (int i = 0; i < length; i++){
   			cout << inputvector[i] << endl;
   		}
   		cout << "End of printed vector";
   		cout << inputvector.front();
   	}
   	return inputvector.front();

	//vector<pint> v{ begin(int_list), end(int_list)};
	
	return 0;
}

int rr(vector<pint> inputvector, int max_iter){		
	cout << "Started rr";
	int length = inputvector.size();
   	vector <pint> solution;
   	for (int i = 0; i < max_iter; i++){
   		cout << "i is " << i << endl;
   		for (int j = 0; j < length; j++){
     		cout << "j is " << j << endl;
     		solution.push_back((rand() % 2));
     		cout << solution[j] << endl;
     		if (solution[j] == 0){
     			solution[j] = solution[j] - 1;
     		}
        	if (debug){
        		cout << solution[j] << endl;
        	}
        }
       	//Calculate the residue


        //RIP this elegant way of getting the residue
        //Try it.
        //pint currentresidue = inner_product(inputvector.begin(), inputvector.end(), solution.begin(), 0);

   	}
   	
   	pint residue = 0;

   	return residue;
}
int hc(vector<pint> inputvector){	
	// Perform Hill Climbing Algorithm
	return 0;
}
int sa(vector<pint> inputvector){	
	// Perform Simulated Annealing Algorithm
	return 0;
}
int prr(vector<pint> inputvector){	
	// Perform Prepartitioned Repeated random Algorithm
	return 0;
}
int phc(vector<pint> inputvector){	
	// Perform Prepartitioned Hill Climbing Algorithm
	return 0;
}
int psa(vector<pint> inputvector){	
	// Perform Prepartitioned Simulated Annealing Algorithm
	return 0;
}


vector<pint> read_in(string filename){
	fstream in_file(filename);
	vector<pint> data_out;
	if (in_file.is_open())
	{	string line;
		while (getline(in_file,line)){
			data_out.push_back(stoull(line));
		}
		// Close file
		in_file.close();
		return data_out;
	}
	else {
		cout << "Unable to open file";
		return data_out;
	}
}

vector<pint> generate(int length){
	vector<pint> data;
	for (int i=0; i < length; i++){
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
		data.push_back(combined + b);
	}
	return data;
}

void write_out(string filename, vector<pint> v){
	fstream out_file(filename);
	if (out_file.is_open()){
		for (vector<pint>::iterator i = v.begin(); i!=v.end(); ++i){
			cout << "writing out: " << *i <<endl;
			// out_file << v[i] << "\n";
		}
		// for (int i=0; i<100; i++){
		// 	out_file << data[i] << "\n";
		// }
		out_file.close();
	}
	else cout << "unable to open output file \n";
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
		cout << "format is ./partition 0 algorithm inputfile.txt";
		return 0;
	}

	int setting = stoi(argv[1]);
	int algorithm = stoi(argv[2]);
	string filename = argv[3];
	int residue = 0;

	vector<pint> input_vec = read_in(filename);

	// Seed rand
	srand ( time(NULL) );

	switch(algorithm) {
	case 0 :
			// Use Karmarkar-Karp Algorithm
			residue = kk(input_vec);
		break;
	case 1 :
			// Use Repeated Random Algorithm
			residue = rr(input_vec, iterations);
		break;
	case 2 :
			// Use Hill Climbing Algorithm
			residue = hc(input_vec);
		break;
	case 3 :
			// Use Simulated Annealing Algorithm
			residue = sa(input_vec);
		break;
	case 11 :
			// Use Prepartitioned Repeated random Algorithm
			residue = prr(input_vec);
		break;
	case 12 :
			// Use Prepartitioned Hill Climbing Algorithm
			residue = phc(input_vec);
		break;
	case 13:
			// Use Prepartitioned Simulated Annealing Algorithm
			residue = psa(input_vec);
		break;
   }

	if (setting == 0){
		// Run normal Program, no extraneous prints
		cout << residue << endl;
	}
	if (setting == 1){
		// Run normal Program, no extraneous prints
		cout << residue << endl;
	}

	return 0;
}
