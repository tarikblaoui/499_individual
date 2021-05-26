// By Tarik Blaoui
// Class CSCI 49900
// Porfessor Soumik Dey
// This file is for individual project


#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <typeinfo>
#include <bitset>
#include <cmath>
#include <ctime>
using namespace std;
#include <sstream>
#include <algorithm>

class FsFunctions {

	private:
		string current_directory = "/";

		/*

		int linked_sys_read(string file_name){
			string bin_filename = strToBinary(file_name);
			int file_start = 0;
			fstream File("linked_filesystem.txt", ios::in | ios::out );
			while (true){
				File.seekg(file_start, ios::beg);
				char F[77];
			    File.read(F, 77);
			    F[77] = 0;
			    cout << F << endl;
			    cout << bin_filename << endl;
			    if (F == bin_filename ) {
			    	cout << "file found" << endl;
			    	break;
			    }
			    file_start + 87;
			    cin.get();
			}

			return 0;
		}

		int linked_sys_write(string file_name,int starting_block,int file_size){
			double  block_needed = ceil(file_size/512.0); // required number of blocks
			int block_used = 0;
			srand(time(NULL));
			cout << "blocks needed: ";
			cout <<  block_needed << endl;
			
			fstream File("linked_disk", ios::in | ios::out );
		    while (block_used <= block_needed){
		    	int current_block;
		    	if (block_used == 0) {current_block = starting_block;};
		  
		    	int next_block = (rand()%(1000-0+1)+0);
		    	string bit_next_block = std::bitset< 10 >( next_block ).to_string();
		    	int start_bit = current_block * 512;
	
		    	if (block_used == block_needed) { bit_next_block= "1111111111"; };

		    	cout << next_block << endl;
		    	cout << bit_next_block << endl;
			
		    	string write_data = bit_next_block + "0101010101010101010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		
			  	File.seekg(start_bit, ios::beg);
			    char F[512];
			    File.read(F, 512);
			    F[512] = 0	;
			    const char * C = write_data.c_str();
			    File.seekg(start_bit, ios::beg);
			    File.write(C, 512);
	
			    block_used +=1;
	
			    current_block = next_block;
				}
		    File.close();

		    string bin_filename = strToBinary(file_name);
		    std::string bin_starting_block = std::bitset< 10 >( starting_block ).to_string();

		    ofstream outfile;
			outfile.open("linked_filesystem.txt", ios_base::app | ios_base::out);
			outfile << bin_filename; 
			outfile << bin_starting_block;
			outfile.close();

			return 0;
		}

		int indexed_sys_write(string file_name,int starting_block,int file_size){

			return 0;
		}

		int contig_sys_write(string file_name,int starting_block,int file_size){

			if (file_name.length() > 11){
				cout << "Error file name too long" << endl;
				return 1;
			}

			if (file_size > 34359720776 ){
				cout << "File too large, must be smaller than 4GB" << endl;
				return 2;
			}

			if (starting_block > 3906250000 ) {
				cout << "Disk too big, must be smaller than 2TB" << endl;
				return 3;
			}

			 std::string bin_file_size = std::bitset< 35 >( file_size ).to_string(); // 35 bits to make 34,359,720,776
			 std::string bin_starting_block = std::bitset< 32 >( starting_block ).to_string(); // there are 3,906,250,000 blocks in 2TB disk
			 string bin_filename = strToBinary(file_name); // 77 bits
			 


			 ofstream outfile;
			 cout << bin_filename << endl;
			 outfile.open("filesystem.txt", ios_base::app | ios_base::out); // append instead of overwrite
			 outfile << bin_filename; 
			 outfile << bin_file_size;
			 outfile << bin_starting_block;
			 outfile.close(); // 144 bits per entry total
			 return 0;
		}

		int sys_read(string file_name){
			string bin_filename = strToBinary(file_name);
			return 0;
		}

		*/
		std::vector<std::string> split(const std::string &str, const std::string &delim)
			{
			    std::vector<std::string> tokens;
			    size_t prev = 0, pos = 0;
			    do
			    {
			        pos = str.find(delim, prev);
			        if (pos == std::string::npos)
			            pos = str.length();
			        std::string token = str.substr(prev, pos - prev);
			        if (!token.empty())
			            tokens.push_back(token);
			        prev = pos + delim.length();
			    } while (pos < str.length() && prev < str.length());
			    return tokens;
			}


		std::vector<int> linked_get_free(){
			fstream File("linked_disk", ios::in | ios::out );

			int in = 0;
			int *next_index = &in;

			std::vector<int> return_vec;

			while (true) {
				int current_block  = *next_index;
				*next_index = *next_index * 20;
	
				int* file_start = next_index;
				File.seekg(*file_start, ios::beg);
				char F[20];
			    File.read(F, 20);
			    F[20] = 0;
			    
				string s(F);
				string next_block = s.substr(0,3);
				
				stringstream degree(next_block);
			    
			    int x = 0;
	    		degree >> x;

				if (s.back() == ' ') return {current_block,x};
				if (next_block == "|||") return {-1,-1};

				

	    		next_index = &x;

    		}
    		return {-1,-1};
		}

		std::vector<string> file_exists(string file_name,char type){

			std::vector<string> name_vec = split(file_name,"/");

			char path_start = file_name.at(0);

			
			string found_name = "null";
			string found_block  = "null";
			string found_type  = "null";

			std::ifstream file("linked_filesystem.txt");
			std::string str;
			while (std::getline(file, str)) {
				std::vector<string> str_vec = split(str,"|");
				if ( (str_vec[0] ==  file_name) && ( str_vec[2].front() == type ) ){
					found_name = str_vec[0];
					found_block = str_vec[1];
					found_type = str_vec[2];

					break;
				}
			 }

			return {found_name,found_block,found_type};
		}

		

		int write_root_fs(string file_name,char type, string write_data){

			string type_name = "Folder";

			if (type == 'F') type_name = "File" ;
			
			std::vector<string> file_info = file_exists(file_name,type);

			if (file_info[0] != "null" ) {
				cout << "Error: " << type_name << " " << file_name << " already exists" << endl;
				return 1;
			}

			std::vector<int> free_block = linked_get_free();

			if (free_block[0] == -1) {
				cout << "Error: Could not create "<< type_name << " " << file_name << " device full" << endl;
				return 2;
			}

			int block_needed = ceil(write_data.length() / 16.0 ) ;

			if (block_needed == 0 )block_needed = 1;
			

			int end_position = block_needed * 16;

			int pad_needed = end_position - write_data.length();

    		int start_position = ((free_block[0] ) * 20) ;

    		const char * C;
    		if (write_data.length() > 0){
	    		string* padded_string = &write_data;

	    		for(int i = 0; pad_needed > i; i++ ) {
	    			*padded_string = *padded_string + "|";
	    		}
	    		  C = padded_string->c_str();
    		}else{
    			  C = "|";
    		}


    		int left_to_write = block_needed;
    		cout << block_needed << endl;
    		for (int i=0; i < block_needed;){
		
			    string block_data = read_from_file(start_position,20,"linked_disk");
			    cout << block_data << endl;

			    stringstream degree(block_data.substr(0,3));
			    int next_block = 0;
	    		degree >> next_block;

	    		if (block_data.back() == ' ') {
	    			if (left_to_write == 1){
	    				string tbr = block_data.substr(0,3) + write_data.substr(i*16,-1) + "]";
	  					cout << tbr << endl;
	    				write_to_file(start_position,20,tbr,"linked_disk");

	    			}else {
	    		
	    				while (true) {
		    				int next_start_position = next_block * 20;
		    				string data_next = read_from_file(next_start_position,20,"linked_disk");

		    				stringstream degree(data_next.substr(0,3));
				   		 	int next_block = 0;
		    				degree >> next_block;

		    				if ( data_next.back() == ' '){
		   						string tbr = block_data.substr(0,3) + write_data.substr(i*16, 16) + "[";
		   						cout << tbr << endl;
		   						cout << i*16 <<" "<< (i*16) + 16 << endl;
		   						write_to_file(start_position,20,tbr,"linked_disk");
		   						start_position = next_start_position;
		    					break;
		    				}
		    				else {
		    					cout << "else block" << endl;
		    					cout << block_data.substr(0,3) << endl;
		    					cin.get();
		    				}
		    				
	    				}

	    			}
	    		
	    		}
	    		i++;
	    		left_to_write --;
	    		cin.get();

			 }
			return 0;
		}

		int find_empty_block (int start_block){
			int start_position = start_block * 20;
			std::stack<int> block_stack;
			block_stack.push(start_block);
			while (true){
				string data =  read_from_file(start_position,20,"linked_disk");
				int next_block = str_to_int(data.substr(0,3));
				int next_start_position = next_block * 20;
				block_stack.push(next_block);
				string next_data =  read_from_file(start_position,20,"linked_disk");
				if (next_data.back() == ' '){block_stack.pop();return block_stack.top();}
				start_position = next_start_position;
			}
			return 0;
		}

		string int_to_str (int &block) {

			string str_block = to_string(block);

			cout << &block << endl;

			switch(str_block.length()){
				case (1):
					str_block = "0" + str_block; 
					break;
			}

			return str_block;
		}

		int str_to_int (string str) {
			stringstream degree(str);
   		 	int conv = 0;
			degree >> conv;
			return conv;
		}

		string read_disk(int starting_block){
			int start_position = starting_block * 20;
			string final_data;
			while (true){
				string data =  read_from_file(start_position,20,"linked_disk");
				int next_block = str_to_int(data.substr(0,3));
				final_data = final_data + data.substr(3,16);
				final_data.erase(std::remove(final_data.begin(), final_data.end(), '|'), final_data.end());
				start_position = next_block * 20 ;
				if (data.back() == ']') break; 

			}
			return final_data;
		}

		string read_root_fs(string entry_name,char type){

			std::vector<string> file_info = file_exists(entry_name,type);

			if (file_info[1] == "null" )  return nullptr;

			int start_block = str_to_int(file_info[1]);

			return read_disk(start_block);
		}

		std::string read_from_file(int start_position,int number_char,string file_name){
			 	fstream File(file_name, ios::in | ios::out );
				File.seekg(start_position, ios::beg);
				char F[number_char];
			    File.read(F, number_char);
			    F[number_char] = 0;
			    string block_data(F);
			    return block_data;
			 }

		void write_to_file(int start_position, int number_char, string data , string file_name){
			const char * C = data.c_str();
			fstream Disk("linked_disk", ios::in | ios::out );
			Disk.seekg(start_position, ios::beg);
			char F[number_char];
			Disk.read(F, number_char);
			F[number_char] = 0;
			Disk.seekg(start_position, ios::beg);
			Disk.write(C,number_char);
		}

	public:	
		int user_write(string file_name){
			
			write_root_fs("test4",'F',"This is the file i am trying to put lets see if it works i try to");
			//string test = read_disk(82);
			//cout << read_root_fs("test.txt",'D') << endl;
			//cout << find_empty_block(0) << endl;

			

			return 0;
		}	
	};


int main(){
	FsFunctions Obj;
	Obj.user_write("test3");
	return 0;

}


