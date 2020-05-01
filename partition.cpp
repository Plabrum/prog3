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
#include <Climits> //my machine needs this to know what LLONG_MAX is

typedef unsigned long long pint;

const bool debug = false;
const int iterations = 25000;

using namespace std;

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

int parent(int i){
	return (floor(i/2));
}

//this is for readability lol
int left_child (int i){
	return (2*(i+1) -1);
}

int right_child (int i){
	return (2*(i +1));
}


vector <pint> max_heapify(vector<pint> input, int node){
	int length = input.size();
	//cout << "length is" << length << endl;
	//cout << "maxheapify initiated";
	//It's literally just an implementation of c++ make_heap
	//cout << node;
	int left = left_child(node);
	int right = right_child(node);
	int largest = node;
	//cout << "left is" << left << endl;
	if (left < length && input[left] > input[node]) {
		//cout << "left child exists and is bigger than node" << endl;
		largest = left;
		//cout << "Largest reassigned to" << left << "with value of " << input[left];
	}
	if (right < length && input[right] > input[largest]) {
		//cout << "right child exists and is bigger than largest" << endl;
		largest = right;
		//cout << "Largest reassigned to" << right << "with value of " << input[right];
	}
	if (largest != node){
		 //cout << input[node] << input[largest];
     swap(input[node], input[largest]); //This works Im pretty sure.
     //cout << input[node] << input[largest];
	   input = max_heapify(input, largest);
  }

	return (input);
}

vector <pint> make_heap_2_the_sequel (vector <pint> input){
    //cout << "started makeheap" << endl;
    int size = input.size();
    for (int i = size - 1; i >= 0; --i){
        //cout << i;
        //cout << "maxheapify called  ";
        input = max_heapify(input, i);
    }
    //cout << "Vector after heapification: ";
    //print_vec(input);
    return (input);
}

pint kk(vector<pint> inputvector){  
	  //int length = inputvector.size();
	  //cout << "Doing KK" << endl;
    inputvector = make_heap_2_the_sequel(inputvector);
   	if (debug) print_vec(inputvector);
   	
   	while (inputvector[secondlargest(inputvector)] != 0){
   		pint subtractor = inputvector[secondlargest(inputvector)];
   		
   		if (debug) cout << "subtractor is: " << subtractor << " largest number is: " << inputvector[0] << endl;

   		inputvector[0] = inputvector[0] - subtractor;
   		inputvector[secondlargest(inputvector)] = 0;
      //cout << "Vector after subtraction: ";
      //print_vec(inputvector);

   		inputvector = make_heap_2_the_sequel(inputvector);
   		if (debug) print_vec(inputvector);
   	}

   	if (debug){
   		//cout << "end ofintermediate heaps" << endl;
   		print_vec(inputvector);
   		//cout << "End of printed vector: " << inputvector.front() << endl;
   	}
   	return inputvector.front();
}

pint rr(vector<pint> inputvector, int max_iter){		
	if (debug){
		cout << "Started rr with ";
		print_vec(inputvector);
	}

	int length = inputvector.size();

   	// vector <pint> solution; - this doesnt seem to be used here
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

pint hc(vector<pint> inputvector, int max_iter){	
	// Perform Hill Climbing Algorithm
	if (debug){
		cout << "Started hc with ";
		print_vec(inputvector);
	}
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

// Cooling Schedule for Simulated annealing
pint T(pint iter){
	// Cooling schedule suggested in spec
	return pow(10,10) * pow(0.8, (iter / 300)) ; 
}

pint sa(vector<pint> inputvector, int max_iter){	
	// Perform Hill Climbing Algorithm
	if (debug) {
		cout << "Started sa with ";
		print_vec(inputvector);
	}
	int length = inputvector.size();

   	vector <pint> solution;
   	vector<pint> best_solution; // S"
   	for (int j = 0; j < length; j++){
		solution.push_back(rand() % 2);
	}
   	signed long long best_residue = LLONG_MAX;
   	signed long long residue = LLONG_MAX;
   	for (int iter = 0; iter < max_iter; iter++){
   		// Pick two random positions
   		int pos_one = rand() % length; //changed this from length+1, if length is 50 we want mod50 because that group has 50 elements
   		int pos_two = rand() % length;
   		while (pos_two == pos_one){
   			pos_two = rand() % length; //we need i =/= j. interestingly, this change brings our worst-case runtime to infinity
   		}
   		bool change_one = 1; //I believe they want us to implement this such that the first change always happens and the second change happens 1/2 the time. Why? I have no idea.
   		bool change_two = rand() %2;

   		// Move to random neightbor of P
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

     	if (current_residue < residue){
     		if (debug) cout << "Found a better residue" << endl;
     		residue = current_residue;
     		solution = s; 
     	}
     	else{
     		double probability = exp(-(current_residue - best_residue)) / T(iter);
     		if (debug) cout << "Probability of move to worse solution: "<< probability << endl;
     		if (rand() < probability*RAND_MAX){
     			cout << "Worse move" << endl;
     			residue = current_residue;
     		}
     	}

     	if (residue < best_residue){
     		best_residue = residue;
     	}
     	
    }
   	return best_residue;
}

vector<pint> p_to_a_prime(vector<pint> a, vector<pint> p){
	vector<pint> a_prime;
	int length = p.size();
	// Look for all elements in the ith partition
	for (int i = 0; i < length; i++){
		// sum for ith partition
		pint a_sum = 0;
		for (int j=0; j < length; j++){
			//loop through p
			if (p[j] == (pint) i){
				a_sum += a[i];
			}
		}
		a_prime.push_back(a_sum);
	}
	return a_prime;
}

pint prr(vector<pint> inputvector, int max_iter){
	// Perform Prepartitioned Repeated random Algorithm		
	if (debug){
		cout << "Started prr with ";
		print_vec(inputvector);
	}

	int length = inputvector.size();
  vector <pint> solution;
  signed long long best_residue = LLONG_MAX; //hardcoded intmax for sll
   	for (int iter = 0; iter < max_iter; iter++){

   		// Generate a random P
   		vector<pint> p;
   		for(int i=0; i<length;i++){
   			p.push_back(rand() % length);
   		}
   		// generate an a_prime from a and p
   		vector<pint> a_prime = p_to_a_prime(inputvector, p);

   		signed long long current_residue = kk(a_prime);

       	// Determine if this new residue is the best seen
     	if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

     	if (current_residue < best_residue){
     		if (debug) cout << "Found new best residue" << endl;
     		best_residue = current_residue;
     	}
    }
   	return best_residue;
}

pint phc(vector<pint> inputvector, int max_iter){
	// Perform Prepartitioned Hill Climbing Algorithm
	if (debug){
		cout << "Started phc with ";
		print_vec(inputvector);
	}
	int length = inputvector.size();

   	// Generate a random initial p
	vector<pint> solution;
	for(int i=0; i<length;i++){
		solution.push_back(rand() % length);
	}
	// initialise best_residue to be as large as possible
  signed long long best_residue = LLONG_MAX;
 	for (int iter = 0; iter < max_iter; iter++){
 		// Pick two random positions
 		int coordinate = rand() % length; //changed this from length+1, if length is 50 we want mod50 because that group has 50 elements
 		pint newvalue = rand() % length;
 		while (solution[coordinate] == newvalue){
 			newvalue = rand() % length; //we need i =/= j. interestingly, this change brings our worst-case runtime to infinity
 		}
    /*
    Here's the old code for jumping to a neighbor in case I was wrong
 		bool change_one = 1; //I believe they want us to implement this such that the first change always happens and the second change happens 1/2 the time. Why? I have no idea.
 		bool change_two = rand() %2;
    */

 		// Move to a random neighbor of P
 		vector<pint> current_p = solution;
    current_p[coordinate] = newvalue;
    /*
    Here's the old code for jumping to a neighbor in case I was wrong
 		current_p[pos_one] = (current_p[pos_one] + change_one) % 2;
 		current_p[pos_two] = (current_p[pos_two] + change_two) % 2;
    */

 		// generate an a_prime from a and p
 		vector<pint> a_prime = p_to_a_prime(inputvector, current_p);
 		signed long long current_residue = kk(a_prime);

    // Determine if this new residue is the best seen
   	//if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

   	if (current_residue < best_residue){
   		if (debug) cout << "Found new best residue" << endl;
   		solution = current_p;
   		best_residue = current_residue;
   	}
  }
  return best_residue;

	return 0;
}

pint psa(vector<pint> inputvector, int max_iter){
	// Perform Prepartitioned Simulated Annealing Algorithm
	cout << "Started psa with";
	print_vec(inputvector);
	int length = inputvector.size();

  // Generate a random initial p
	vector<pint> solution;
	for(int i=0; i<length; i++){
		solution.push_back(rand() % length);
	}
	// initialise best_residue to be as large as possible
  signed long long best_residue = LLONG_MAX;
  signed long long residue = LLONG_MAX;

   	for (int iter = 0; iter < max_iter; iter++){

   		// Pick two random positions
   		int coordinate = rand() % length; //changed this from length+1, if length is 50 we want mod50 because that group has 50 elements
      pint newvalue = rand() % length;
      while (solution[coordinate] == newvalue){
        newvalue = rand() % length; //we need i =/= j. interestingly, this change brings our worst-case runtime to infinity
      }
      /*
   		bool change_one = 1; //I believe they want us to implement this such that the first change always happens and the second change happens 1/2 the time. Why? I have no idea.
   		bool change_two = rand() %2;
      */
   		// Move to a random neighbor of P
      vector<pint> current_p = solution;
      current_p[coordinate] = newvalue;
   		
      /*
      current_p[pos_one] = (current_p[pos_one] + change_one) % 2;
   		current_p[pos_two] = (current_p[pos_two] + change_two) % 2;
      */
   		// generate an a_prime from a and p
   		vector<pint> a_prime = p_to_a_prime(inputvector, current_p);

   		signed long long current_residue = kk(a_prime);
      // Determine if this new residue is the best seen
     	if (debug) cout << "New residue: " << current_residue << " Current Best residue: " << best_residue << endl;  

     	if (current_residue < residue){
     		if (debug) cout << "Found a better residue" << endl;
     		residue = current_residue;
     		solution = current_p; 
     	}
     	else{
     		double probability = exp(-(current_residue - best_residue)) / T(iter);
     		if (debug) cout << "Probability of move to worse solution "<< probability << endl;
     		if (rand() < probability*RAND_MAX){
     			residue = current_residue;
     		}
     	}

     	if (residue < best_residue){
     		best_residue = residue;
     	}
    }
   	return best_residue;
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
		// in order to hit 40 random bits we need 9 more from rand
		pint a = rand();
		// get the last 9 bits
		pint b = rand() % 512;
		a = a << 9;
		pint combined = a + b;
		data.push_back(combined);
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
	if (!(argc == 3) || (argc==4)) {
		cout << "format is ./partition 0 algorithm inputfile.txt \n";
		return 0;
	}

	int setting = stoi(argv[1]);
	const int iterations = 25000;

	// Seed rand
	srand ( time(NULL) );

	if (setting == 0){
		// Run normal Program, no extraneous prints

		int algorithm = stoi(argv[2]);
		string filename = argv[3];
		vector<pint> input_vec = read_in(filename);
		signed long long residue;

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
					residue = prr(input_vec, iterations);
				break;
			case 12 :
					// Use Prepartitioned Hill Climbing Algorithm
					residue = phc(input_vec, iterations);
				break;
			case 13:
					// Use Prepartitioned Simulated Annealing Algorithm
					residue = psa(input_vec, iterations);
				break;
		}
		cout << residue << endl;
	}
	else if (setting == 1){

		string filename = argv[2];

		fstream out_file(filename);
		if (out_file.is_open()){
			// Iterate through 100 instances of generated data
			string header = ",KK,,RR,,HC,,SA,,PRR,,PHC,,PSA, \n Iteration,Result,Runtime,Result,Runtime,Result,Runtime,Result,Runtime,Result,Runtime,Result,Runtime,Result,Runtime";
			out_file << header << "\n";	
			for (int i=0; i <100; i++){
				vector<pint> test_set = generate(100);
				cout << "Iteration: " << i << endl;
				out_file << i << ",";

				auto time0 = chrono::high_resolution_clock::now();
				pint residue1 = kk(test_set);
				auto time1 = chrono::high_resolution_clock::now();
				pint residue2 = rr(test_set, iterations);
				auto time2 = chrono::high_resolution_clock::now();
				pint residue3 = hc(test_set, iterations);
				auto time3 = chrono::high_resolution_clock::now();
				pint residue4 = sa(test_set, iterations);
				auto time4 = chrono::high_resolution_clock::now();
				pint residue5 = prr(test_set, iterations);
				auto time5 = chrono::high_resolution_clock::now();
				pint residue6 = phc(test_set, iterations);
				auto time6 = chrono::high_resolution_clock::now();
				pint residue7 = psa(test_set, iterations);
				auto time7 = chrono::high_resolution_clock::now();

				// calculating durations
				auto duration1 = duration_cast<chrono::microseconds>(time1 - time0);
				auto duration2 = duration_cast<chrono::microseconds>(time2 - time1);
				auto duration3 = duration_cast<chrono::microseconds>(time3 - time2);
				auto duration4 = duration_cast<chrono::microseconds>(time4 - time3);
				auto duration5 = duration_cast<chrono::microseconds>(time5 - time4);
				auto duration6 = duration_cast<chrono::microseconds>(time6 - time5);
				auto duration7 = duration_cast<chrono::microseconds>(time7 - time6);

				out_file << residue1 << "," << duration1.count() << ",";
				out_file << residue2 << "," << duration2.count() << ",";
				out_file << residue3 << "," << duration3.count() << ",";
				out_file << residue4 << "," << duration4.count() << ",";
				out_file << residue5 << "," << duration5.count() << ",";
				out_file << residue6 << "," << duration6.count() << ",";
				out_file << residue7 << "," << duration7.count() << "\n";
			}
			out_file.close();
		}
		else cout << "unable to open output file \n";
	}

	return 0;
}
