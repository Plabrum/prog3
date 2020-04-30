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
#include <Climits>

typedef unsigned long long pint;

using namespace std;

const bool debug = true;
const int iterations = 25;

void print_vec(vector<pint> vec){
	cout << "Vector: ";
	for (vector<pint>::iterator i = vec.begin(); i!=vec.end(); ++i){
		cout << *i << ", ";
	}
	cout << endl;
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

signed long long kk(vector<pint> inputvector){  
	int length = inputvector.size();
	cout << "Doing KK" << endl;

   	make_heap(inputvector.begin(), inputvector.end());
   	if (debug) print_vec(inputvector);
   	
   	while (inputvector[secondlargest(inputvector)] != 0){
   		pint subtractor = inputvector[secondlargest(inputvector)];
   		
   		if (debug) cout << "subtractor is: " << subtractor << " largest number is: " << inputvector[0] << endl;

   		inputvector[0] = inputvector[0] - subtractor;
   		inputvector[secondlargest(inputvector)] = 0;

   		make_heap(inputvector.begin(), inputvector.end());
   		if (debug) print_vec(inputvector);
   	}

   	if (debug){
   		cout << "end ofintermediate heaps" << endl;
   		print_vec(inputvector);
   		cout << "End of printed vector: " << inputvector.front() << endl;
   	}
   	return inputvector.front();
}

signed long long rr(vector<pint> inputvector, int max_iter){		
	cout << "Started rr with";
	print_vec(inputvector);
	int length = inputvector.size();

   	vector <pint> solution;
   	signed long long best_residue = LLONG_MAX; //hardcoded intmax for sll
   	for (int iter = 0; iter < max_iter; iter++){
   		// generate a random S 
   		vector<pint> s;
   		for (int j = 0; j < length; j++){
   			s.push_back(rand() % 2);
     	}
     	if (debug) print_vec(s);

     	// calculate the new residue with this S
     	signed long long current_residue = 0;
     	for(int k = 0; k<length; k++){
     		if (s[k] == 0){
     			current_residue -= inputvector[k];
     		}
     		else{
     			current_residue += inputvector[k];
     		}
     	}
     	current_residue = abs(current_residue);
     	if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

     	if (current_residue < best_residue){
     		if (debug) cout << "Found new best residue" << endl;
     		best_residue = current_residue;
     	}
    }
   	return best_residue;
}
signed long long hc(vector<pint> inputvector, int max_iter){	
	// Perform Hill Climbing Algorithm
	cout << "Started hc with";
	print_vec(inputvector);
	int length = inputvector.size();

   	vector <pint> solution;
   	for (int j = 0; j < length; j++){
		solution.push_back(rand() % 2);
	}
   	signed long long best_residue = LLONG_MAX;
   	for (int iter = 0; iter < max_iter; iter++){
   		// Pick two random positions
   		int pos_one = rand() % length; //changed this from length+1, if length is 50 we want mod50 because that group has 50 elements
   		int pos_two = rand() % length;
   		while (pos_two == pos_one){
   			pos_two = rand() % length; //we need i =/= j. interestingly, this change brings our worst-case runtime to infinity
   		}
   		bool change_one = 1; //I believe they want us to implement this such that the first change always happens and the second change happens 1/2 the time. Why? I have no idea.
   		bool change_two = rand() %2;
   		vector<pint> s = solution;
   		s[pos_one] = (s[pos_one] + change_one) % 2;
   		s[pos_two] = (s[pos_two] + change_two) % 2;
     	if (debug) print_vec(s);

     	// calculate the new residue with this S
     	signed long long current_residue = 0;
     	for(int k = 0; k<length; k++){
     		if (s[k] == 0){
     			current_residue -= inputvector[k];
     		}
     		else{
     			current_residue += inputvector[k];
     		}
     	}
     	current_residue = abs(current_residue);
     	if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

     	if (current_residue < best_residue){
     		if (debug) cout << "Found new best residue" << endl;
     		best_residue = current_residue;
     		solution = s; 
     	}
    }
   	return best_residue;
}
int sa(vector<pint> inputvector, int max_iter){	
	// Perform Hill Climbing Algorithm
	cout << "Started sa with";
	print_vec(inputvector);
	int length = inputvector.size();

   	vector <pint> solution;
   	for (int j = 0; j < length; j++){
		solution.push_back(rand() % 2);
	}
   	signed long long best_residue = LLONG_MAX;
   	for (int iter = 0; iter < max_iter; iter++){
   		// Pick two random positions
   		int pos_one = rand() % length; //changed this from length+1, if length is 50 we want mod50 because that group has 50 elements
   		int pos_two = rand() % length;
   		while (pos_two == pos_one){
   			pos_two = rand() % length; //we need i =/= j. interestingly, this change brings our worst-case runtime to infinity
   		}
   		bool change_one = 1; //I believe they want us to implement this such that the first change always happens and the second change happens 1/2 the time. Why? I have no idea.
   		bool change_two = rand() %2;
   		vector<pint> s = solution;
   		s[pos_one] = (s[pos_one] + change_one) % 2;
   		s[pos_two] = (s[pos_two] + change_two) % 2;
     	if (debug) print_vec(s);

     	// calculate the new residue with this S
     	signed long long current_residue = 0;
     	for(int k = 0; k<length; k++){
     		if (s[k] == 0){
     			current_residue -= inputvector[k];
     		}
     		else{
     			current_residue += inputvector[k];
     		}
     	}
     	current_residue = abs(current_residue);
     	if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

     	if (current_residue < best_residue){
     		if (debug) cout << "Found new best residue" << endl;
     		best_residue = current_residue;
     		solution = s; 
     	}
     	/*
     	else{
     		if (pow rand() % 100 )
     	}
     	*/
    }
   	return best_residue;
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
			out_file << *i << "\n";
		}
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
	signed long long residue = 0;

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
			residue = hc(input_vec, iterations);
		break;
	case 3 :
			// Use Simulated Annealing Algorithm
			residue = sa(input_vec, iterations);
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
		cout << "Residue: " << residue << endl;
	}
	if (setting == 1){
		// Run normal Program, no extraneous prints
		int zeros = 0;
		int ones = 0;
		for (int i = 0; i < 100000; i++){
			int ran = rand() % 2;
			if (ran == 0){
				zeros++;
			}
			else if (ran == 1){
				ones++;
			}
			else{
				cout << "we gotta a problem" << endl;
			}
		}

		cout << "ones: " << ones <<" zeros" << zeros <<endl;
	}

	return 0;
}
