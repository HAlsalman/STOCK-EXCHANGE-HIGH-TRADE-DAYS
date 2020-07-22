// Hassan Alsalman
//******************************************************************
//                 HEADER FILES USED IN THE PROJECT                *
//******************************************************************
#include "pch.h"    //VS required header, also must be the 1st header.
#include <iostream> //input / output.
#include <fstream>  //to import files.
#include <iomanip>  //manipulate parameters.
#include <string>   //string library.
#include <vector>   //vector library.
#include <Windows.h>//for directory search.

using namespace std;

//******************************************************************
//                      STRUCT FOR STOCK DATA                      *
//******************************************************************
struct stock {
	string date;
	float open, adjClose, change;
};

//******************************************************************
//              CSV FILE SEARCH FROM CURRENT DIRECTORY             *
//referenced from Prof. Harris on march 10, 2019                   *
//******************************************************************
void Compute_1_Filenames(string &filename) {
	WIN32_FIND_DATAA findData;
	HANDLE hfind;
	string extention = "*.csv";

	string directory_file_ext = extention;
	hfind = FindFirstFileA(directory_file_ext.c_str(), &findData);

	if (hfind != INVALID_HANDLE_VALUE) {
		filename = findData.cFileName;
	}
	else {
		cout << "No .csv file was found in the same directory as this project." << endl;
	}
}

/**************************************************************************************************************/
int main(){
	ifstream in;
	string CSV;                          //variable to the name of csv file to be opened.
	string 	data, date;                  //variables.
	float open, adj_close;               //variables.
	int p=0,                             //to hold number of trading days.
		records=0;                       //variable for user input for number of records to display.

	Compute_1_Filenames(CSV);            //Searches current directory and returns the first .csv file that was found.
	in.open(CSV);                        //open .csv file.

	vector <stock> stk;                  //vector of struct.
	getline(in, data);                   //ignore first line.

//******************************************************************
//          IMPORT STOCK DATA FROM .CSV INTO STOCK STRUCT          *
//******************************************************************
	while (in.good()) {
		getline(in, date, ',');
			if (date != "") {           //check if last input was a space which means end of the file.
				stk.push_back(stock()); //create an index in the vector.
				stk[p].date = date;

				in >> open;             //import as a float instead of string
				stk[p].open = open;
			
				getline(in, data, ','); //high
				getline(in, data, ','); //low
				getline(in, data, ','); //close
				getline(in, data, ','); //close

				in >> adj_close;        //import as a float instead of string.
				stk[p].adjClose = adj_close;

				getline(in, data);      //volume

				stk[p].change = ((stk[p].adjClose - stk[p].open)/stk[p].open *100);  //percent change saved as a float instead of string.           
				p++;                    //number of trading days.

			}
	}

//******************************************************************
//                        OPENING STATEMENT                        *
//******************************************************************
	cout << "This program will analyze " << CSV.erase(CSV.find(".")) <<
		" from " << stk[0].date << " to " << stk[p - 1].date << endl;
	cout << p << " trading day(s) exist in the file." << endl;
	cout << "How many increase records do you want to find? ";
	cin >> records;
	while (records > p) {            //ask for how many record days, also validate.
		cout << endl << "The file does not contain enough trading days" << endl;
		cout << "There are only " << p << " trading days." << endl;
		cout << "How many increase records do you want to find? ";
		cin >> records;
	}

//******************************************************************
//                     SELECTION SORT ALGORITHM                    *
//******************************************************************
	int minIndex;                                                 //
	double minValue;                                              // 
	for (int start = 0; start < (stk.size() - 1); start++) {      //      
		minIndex = start;                                         //
		minValue = stk[start].change;                             //
		for (int index = start + 1; index < stk.size(); index++) {//
			if (stk[index].change > minValue) {                   //
				minValue = stk[index].change;                     //
				minIndex = index;                                 //
			}                                                     //
		}                                                         //
		swap(stk[minIndex].date, stk[start].date);                //
		swap(stk[minIndex].open, stk[start].open);                //
		swap(stk[minIndex].adjClose, stk[start].adjClose);        //
		swap(stk[minIndex].change, stk[start].change);            //
	}/************************************************************/

//******************************************************************
//               PRINT THE RECORDS REQUESTED BY USER               *
//******************************************************************
	cout << endl << "Date\t\t" << "Open\t" << "A.close\t" << "Percentage change\n";
	for (int n = 0; n < records; n++) {
		cout << stk[n].date << "\t";
		cout << stk[n].open << "\t";
		cout << stk[n].adjClose << "\t";
		cout << stk[n].change << endl;
	}

in.close();

system("pause"); // to display "Press any key to continue..."
}
/**************************************************************************************************************/
//******************************************************************
//                        END OF THE PROJECT                       *
//******************************************************************