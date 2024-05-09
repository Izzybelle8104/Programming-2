
#ifndef LAB6_INHERITANCE_BANKACCOUNT_H
#define LAB6_INHERITANCE_BANKACCOUNT_H

#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

class BankAccount {
private:
    int id;
    string name;

public:
    BankAccount(string name, int id){
        this->name = name;
        this->id = id;
    }


    string getName(){
        return name;
    }

    int getID(){
        return id;
    }

    virtual void Display() = 0;

    virtual void Deposit(float amount) = 0;

    virtual float getAmount() = 0;

};

class CheckingAccount: virtual public BankAccount {
private:
    float amount;

public:
    CheckingAccount(float amount, int id, string name) : BankAccount(name, id){
        this->amount = amount;
    }

    void setAmount (float amount){
        this->amount = amount;
    }

    float getAmount() override{
        return amount;
    }

    bool Withdraw(float money){
        if (money <= getAmount()){
            amount -= money;
            return true;
        }
        else{
            return false;
        }
    }

    void Display() override{
        cout << fixed << setprecision(2);
        cout << getName() << " (" << getID() << "):" << endl;
        cout << "\tChecking Account: $" << getAmount() << endl;
    }


    void Deposit(float money) override{
        amount += money;
    }


};

class SavingsAccount : virtual public BankAccount{
private:
    float amount;

public:
    SavingsAccount (float amount, int id, string name) : BankAccount(name, id) {
        this->amount = amount;

    }

    void setAmount (float amount){
        this->amount = amount;
    }

    float getAmount() override{
        return amount;
    }

    bool Transfer(CheckingAccount& account, float amount){
        if (amount <= getAmount()){
            account.Deposit(amount);
            setAmount((getAmount() - amount));
            return true;
        }
        else{
            return false;
        }

    }

    virtual float CompoundEarnings(float percent){
        float i_amount = amount;
        setAmount(amount*(1+percent));
        return (amount - i_amount);
    }

    void Display() override{
        cout << fixed << setprecision(2);
        cout << getName() << " (" << getID() << "):" << endl;
        cout << "\tSavings Account: $" << getAmount() << endl;
    }

    void Deposit(float money) override{
        amount += money;
    }

};

class InvestmentAccount : public CheckingAccount, private SavingsAccount {
private:
    float amount;

public:
    InvestmentAccount(float amount, int id, string name) : BankAccount(name, id), CheckingAccount(0, id, name),
                                                           SavingsAccount(amount, id, name) {
        this->amount = amount;
    }

    float getAmount() override{
        return (SavingsAccount::getAmount() + CheckingAccount::getAmount());
    }

    void Display() override{
        cout << fixed << setprecision(2);
        cout << getName() << " (" << getID() << "):" << endl;
        cout << "\tTotal: $" << getAmount() << "\n"
                                                    "\t\tImmediate Funds: $" << CheckingAccount::getAmount() << "\n"
                                                                                          "\t\tInvestment: $" << SavingsAccount::getAmount() << endl;
    }


    void Deposit(float money) override{
        SavingsAccount::Deposit(money);
    }

    void setAmount (float amount){
        this->amount = amount;
    }


    float CompoundEarnings(float percent) override{
        float i_amount = getAmount();
        setAmount(getAmount()*(1+percent));
        float to_transfer = (amount - i_amount);
        CheckingAccount::Deposit(to_transfer);
        return to_transfer;
    }


};

#endif //LAB6_INHERITANCE_BANKACCOUNT_H
