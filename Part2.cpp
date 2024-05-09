#include<iostream>
#include<fstream>
#include<map>
#include <vector>
#include"BankAccount.h"
using namespace std;


struct AccountReader{
    //Containers
    map <int, BankAccount*> ID;
    map <string, BankAccount*> Name;

    vector<CheckingAccount*> checking_type;
    vector<SavingsAccount*> savings_type;
    vector<InvestmentAccount*> investment_type;
    vector<BankAccount*> all_accounts;


    //function to help read csv file
    vector <string> split(string& a_string, char delimiter){
        vector<string> tokens;
        string token;
        for (char c : a_string){
            if (c == delimiter){
                tokens.push_back(token);
                //clear empties the string
                token.clear();
            }
            else{
                token += c;
            }
        }
        //last token
        tokens.push_back(token);
        //should have 4 indexes: type,name,amount,id
        return tokens;

    }

    void operator()(string filePath) {
        // Load all accounts into the containers!

        //variables
        vector<string> storage;
        int type;
        int amount;
        int id;
        string name;

        //file reading
        ifstream file;
        file.open(filePath);

        string line;
        while (getline(file, line)){

            //get a vector of the 4 contents
            storage = split(line, ',');
            if (storage[0] == "Type"){
              continue;
            }
            type = stoi(storage[0]);
            name = storage[1];
            amount = stoi(storage[2]);
            id = stoi(storage[3]);

            //now we have 0:type, 1:name, 2: amount, 3:ID
            //create bank account objects depending on type and populate containers

            if (type == 1){
                //Checkings
                CheckingAccount* checking = new CheckingAccount(float(amount),id,name);
                checking_type.push_back(checking);
                all_accounts.push_back(checking);
                //Maps
                ID[id] = checking;
                Name[name] = checking;
            }
            else if (type == 2){
                //Savings
                SavingsAccount* savings = new SavingsAccount(float(amount),id,name);
                savings_type.push_back(savings);
                all_accounts.push_back(savings);
                //Maps
                ID[id] = savings;
                Name[name] = savings;
            }
            else if (type == 3){
                //Investment
                InvestmentAccount* invest = new InvestmentAccount(float(amount),id,name);
                investment_type.push_back(invest);
                all_accounts.push_back(invest);
                //Maps
                ID[id] = invest;
                Name[name] = invest;
            }
        }

        cout << "1. Display all accounts" << endl;
        cout << "2. Display all of account type" << endl;
        cout << "3. Find account" << endl;
        string optionS;
        int option;
        getline(cin, optionS);
        option = stoi(optionS);

        //OPTION 1 -----------------------------------------------------------------------------------------------------
        if (option == 1){
            for (int i = 0; i < all_accounts.size(); ++i){
                //-> dereferences, could've also done (BankAccount* account : all_accounts), account->Display();
                all_accounts[i]->Display();
            }
        }

        //OPTION 2 -----------------------------------------------------------------------------------------------------
        else if (option == 2){
            string option2;
            int option_2;
            getline(cin, option2);
            option_2 = stoi(option2);

            if (option_2 == 1){
                //Checkings
                for (int i = 0; i < checking_type.size(); ++i){
                    checking_type[i]->Display();
                }
            }

            else if (option_2 == 2){
                for (int i = 0; i < savings_type.size(); ++i){
                    savings_type[i]->Display();
                }
            }

            else if (option_2 == 3){
                for (int i = 0; i < investment_type.size(); ++i){
                    investment_type[i]->Display();
                }
            }
        }

        //OPTION 3 -----------------------------------------------------------------------------------------------------
        else if (option == 3){
            string option3;
            int option3_ID;
            getline(cin, option3);

            // cout << option3 << endl;
            //check 3,7,11
            if (Name.find(option3) != Name.end()) {
                Name.at(option3)->Display();
            }
            else{
                //try catch for names that don't exist and aren't ids
                try
                {
                option3_ID = stoi(option3);
                }
                catch(exception &err){
                  cout << "Could not find account!" << endl;
                  return;
                }

                if (ID.find(option3_ID) != ID.end()){
                    ID.at(option3_ID)->Display();
                }
                else{
                    cout << "Could not find account!" << endl;
                }

            }
        }

    }
};

int main(int argc, char** argv) {
    //argc means argument count
    //argv means argument vector

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    string file_path = argv[1];
    AccountReader account_reader;
    account_reader(file_path);


    return 0;
}
