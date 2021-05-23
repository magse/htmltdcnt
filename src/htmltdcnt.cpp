// This software is under licensing according to the attached projects LICENSE file.

#include "config.h"

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

#include <cassert>
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;

struct options {
	int quotation=0;
	int trynumerical=0;
	int trytimestamp=0;
	int printindex=2;
	size_t R1=0;
	size_t R2=numeric_limits<size_t>::max();
	size_t D1=0;
	size_t D2=numeric_limits<size_t>::max();
	string inputfilename;
	int version(int ret) {
		cout << "htmltdcnt " << htmltdcnt_VERSION_MAJOR << "." << htmltdcnt_VERSION_MINOR << endl;
		return ret;
	}
	int help(int ret) {
		cout << "No help yet!" << endl;
		return ret;
	}
	int error_message(int err,const char* msg,char* ext=nullptr) {
		cout << "ERROR:" << msg;
		if(ext) cout << ext;
		cout << endl;
		return err;
	}
	int parse(int argc,char* argv[]) {
		for(int a=1; a<argc; a++) {
			if(!strcmp(argv[a], "-h") || !strcmp(argv[a], "--help") ) {
				return help(-1);
			} else if(!strcmp(argv[a], "-V") || !strcmp(argv[a], "--version") ) {
				return version(-1);
			} else if(!strcmp(argv[a], "-Q") || !strcmp(argv[a], "--quotation")) {
				quotation++;
			} else if(!strcmp(argv[a], "-N") || !strcmp(argv[a], "--numerical")) {
				trynumerical++;
			} else if(!strcmp(argv[a], "-n") || !strcmp(argv[a], "--noindex")) {
				printindex--;
			} else if(!strcmp(argv[a], "-T") || !strcmp(argv[a], "--timestamp")) {
				trytimestamp++;
			} else if(!strcmp(argv[a], "-R") || !strcmp(argv[a], "--rows")) {
				if((a+1)>(argc-1)) return error_message(-1,"Missing rows specification");
				a++;
				string str=string(argv[a]);
				for(auto& c:str) if(':'==c || ','==c) c=' ';
				istringstream ss(str);
				ss >> R1 >> R2;
			} else if(!strcmp(argv[a], "-C") || !strcmp(argv[a], "--columns")) {
				if((a+1)>(argc-1)) return error_message(-1,"Missing columns specification");
				a++;
				string str=string(argv[a]);
				for(auto& c:str) if(':'==c || ','==c) c=' ';
				istringstream ss(str);
				ss >> D1 >> D2;
			} else if(!strcmp(argv[a], "-i") || !strcmp(argv[a], "--input")) {
				if((a+1)>(argc-1)) return error_message(-1,"Missing input file name");
				a++;
				inputfilename=argv[a];
			} else {
				if(a == argc-1) break;
				return error_message(-1,"Invalid command line option",argv[a]);
			}
		}
		return 0;
	}
};

bool to_numerical(string& data) {
	string str;
	for(auto& c:data) {
		if('0'<=c && c<='9') str+=c;
		if('+'==c || c=='-') str+=c;
		if('E'==c || c=='e') str+=c;
		if('G'==c || c=='g') str+=c;
		if('.'==c || c==',') str+='.';
	}
	auto x=atof(str.c_str());
	if(isnormal(x)) {
		data=str;
		return true;
	}
	return false;
}

void print_td(string& data,size_t Rcnt,size_t Dcnt,options& opt) {
	if(data.length() && opt.R1<=Rcnt && Rcnt<=opt.R2 && opt.D1<=Dcnt && Dcnt<=opt.D2) {
		cout << ",";
		if(opt.printindex) cout << "(" << Rcnt << "," << Dcnt << "):";
		bool num=false;
		if(opt.trynumerical) num=to_numerical(data);
		if(opt.quotation && !num) cout << "\"";
		cout << data;
		if(opt.quotation && !num) cout << "\"";
	}
}

int main(int argc,char* argv[]) {
	
	options opt;
	opt.parse(argc,argv);
	
	ifstream inputfile(opt.inputfilename);
	char c=0;
	string data;
	size_t D_counter=1;
	size_t R_counter=1;
	
	cout << R_counter;
	
	while(inputfile.good()) {
		inputfile.get(c);
		if('<'==c) {
			c=' ';
			while(inputfile.good() && isspace(c)) inputfile.get(c);
			if('/'==c) {
				c=' ';
				while(inputfile.good() && isspace(c)) inputfile.get(c);
				if('T'==toupper(c)) {
					c=' ';
					while(inputfile.good() && isspace(c)) inputfile.get(c);
					if('D'==toupper(c)) {
						while(inputfile.good() && '>'!=c) inputfile.get(c);
						inputfile.putback(c);
						print_td(data,R_counter,D_counter,opt);
						D_counter++;
					} else {
						if('R'==toupper(c)) {
							while(inputfile.good() && '>'!=c) inputfile.get(c);
							inputfile.putback(c);
							R_counter++;
							D_counter=1;
							cout << endl << R_counter;
						} else {
							while(inputfile.good() && '>'!=c) inputfile.get(c);
							inputfile.putback(c);
						}
					}
				}
			} else {
				while(inputfile.good() && '>'!=c) inputfile.get(c);
				inputfile.putback(c);
			}
		} else {
			if('>'==c) {
				data.clear();
			} else {
				data+=c;
			}
		}
	}
	
	return 0;
}

// This software is inspired by:
// https://developer.mozilla.org/en-US/docs/Learn/HTML/Tables/Basics
// https://www.w3schools.com/html/html_tables.asp
// https://www.w3schools.com/css/css_table.asp

