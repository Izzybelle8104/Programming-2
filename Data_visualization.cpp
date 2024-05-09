#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main(){
  string title;
  string column_1;
  string column_2;
  string data_point;
  string datapoint_1;
  int datapoint_2;


  vector<string> stringVector;

  vector<int> intVector;

  cout << "Enter a title for the data:" << endl;
  getline(cin, title);
  cout << "You entered: " << title << endl;
  cout << "Enter the column 1 header:" << endl;
  getline(cin,column_1);
  cout << "You entered: " << column_1 << endl;

  cout << "Enter the column 2 header:" << endl;
  getline(cin, column_2);
  cout << "You entered: " << column_2 << endl;

  while (true){
    cout << "Enter a data point (-1 to stop input):" << endl;
    getline(cin, data_point);


    if (data_point == "-1") {
      break;
    }    
    
    size_t posnum = data_point.find(",");

    if (posnum == string::npos) {
      cout << "Error: No comma in string." << endl;
      continue;
    
    }

    if (data_point.find(",", posnum + 1) != string::npos) {
      cout << "Error: Too many commas in input." << endl;
      continue;

    }

    try {
      datapoint_1 = data_point.substr(0, posnum);
      datapoint_2 = stoi(data_point.substr(posnum + 1));

      cout << "Data string: " << datapoint_1 << endl;
      cout << "Data integer: " << datapoint_2 << endl;

      stringVector.push_back(datapoint_1);
      intVector.push_back(datapoint_2);

    } catch (const invalid_argument& e) {
        cout << "Error: Comma not followed by an integer." << endl;
        continue;

    }

  }

  cout << endl;
  cout << setw(33) << title << endl;
  cout << setw(20) << left << column_1 << "|" << setw(23) << right << column_2 << endl;
  cout << "--------------------------------------------" << endl;
  for (size_t i = 0; i < stringVector.size(); ++i) {
    cout << setw(20) << left << stringVector[i] << "|" << setw(23) << right << intVector[i] << endl;
  }
  
  cout << endl;

  for (size_t i = 0; i < stringVector.size(); ++i){
    string stars(intVector[i], '*');
    cout << setw(20) << stringVector[i] << " " << stars << endl;

  }

  cout << "=========================" << endl;


  return 0;

}

