#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class box {
private:
    string name;
    int ac;
    int value;
    int pin;
    box *next;

public:
    box(int value = 0, int pin = 0, int ac = 0, string name = "") {
        this->name = name;
        this->value = value;
        this->pin = pin;
        this->ac = ac;
        this->next = nullptr;
    }

    static int generateRandomPin() {
        return 1000 + rand() % 9000;
    }

    static int generateRandomAc() {
        return 100000000 + rand() % 900000000;
    }

    static void create(string name, int value, box *&head) {
        int pin = generateRandomPin();
        int ac = generateRandomAc();
        box *p = new box(value, pin, ac, name);

        if (head == nullptr) {
            head = p;
        } else {
            box *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = p;
        }
        cout << "\nAccount created successfully!";
        cout << "\nAccount Holder: " << name;
        cout << "\nAccount Number: " << ac;
        cout << "\nInitial Balance: " << value;
        cout << "\nIMPORTANT: Your PIN is " << pin << ". Keep it secure!";
    }

    static void display(box *&head) {
        if (head == nullptr) {
            cout << "\nNo accounts available to display!\n";
            return;
        }
        
        box *temp = head;
        cout << "\nList of Accounts:\n";
        while (temp != nullptr) {
            cout << "----------------------------------------\n";
            cout << "Account Holder: " << temp->name << "\n";
            cout << "Account Number: " << temp->ac << "\n";
            cout << "Balance: " << temp->value << "\n";
            cout << "----------------------------------------\n";
            temp = temp->next;
        }
    }

    static void saveData(box *&head) {
        ofstream out("data.txt");
        if (!out.is_open()) {
            cout << "\nError saving data!\n";
            out.close();
            return;
        }
        
        box *temp = head;
        while (temp != nullptr) {
            out << temp->name << " " << temp->value << " " << temp->pin << " " << temp->ac << endl;
            temp = temp->next;
        }
        out.close();
    }

    static void retrieveData(box *&head) {
        ifstream in("data.txt");
        if (!in.is_open()) {
            cout << "\nNo previous data found. Starting fresh.\n";
            return;
        }

        string name;
        int value, pin, ac;
        while (in >> name >> value >> pin >> ac) {
            box *p = new box(value, pin, ac, name);
            if (head == nullptr) {
                head = p;
            } else {
                box *temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = p;
            }
        }
        in.close();
        cout << "\nData retrieved successfully!\n";
    }

    static void deleteByPin(box *&head, int pin) {
        if (!head) {
            cout << "\nNo accounts available to delete!\n";
            return;
        }

        box *temp = head;
        box *prev = nullptr;

        if (head->pin == pin) {
            head = head->next;
            delete temp;
            cout << "\nAccount deleted successfully!\n";
            return;
        }

        while (temp && temp->pin != pin) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "\nAccount with the given PIN not found!\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "\nAccount deleted successfully!\n";
    }


    static void addmoney(box *&head, int pin, int amount) {
        if (!head) {
            cout << "\nNo account available!\n";
            return;
        }

        box *temp = head;
        while(temp != nullptr) {

            if (temp->pin == pin) {
                if(amount<0){
                    if((temp->value+amount)<0){
                        cout<<"\nyou have not enough amount to withdraw !";
                        cout<<"\nyour amount is : "<<temp->value;
                        return;
                    }
                    cout << "\nMoney Withdrawal successfully !";
                    temp->value += amount;
                    cout << "\nCurrent Balance: " << temp->value << "\n";
                    return;
                }
                temp->value += amount;
                cout << "\nMoney Added Successfully!";
                cout << "\nCurrent Balance: " << temp->value << "\n";
                return;
            }
            temp = temp->next;
        }

        cout << "\nAccount not found for the given PIN!\n";
    
    }

    static void deleteAllAcount(box *&head){
        box *newptr = head;
        box *temp=nullptr;
        while(newptr){
            temp = newptr;
            delete temp;
            newptr = newptr->next;
        }
        cout << "\nAll Acounts Deletion Successfully !";
    }
    static void erasefiledata(){
        ofstream out("data.txt");
        out<<"";
        out.close();
        return;
    }

};

int main() {
    srand(time(0));
    
    int opt, value, pin,amount;
    string name;
    box *head = nullptr;

    box::retrieveData(head);

    do {
        cout << "\n============================\n";
        cout << "BANK ACCOUNT MANAGEMENT SYSTEM\n";
        cout << "============================\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Delete Account\n";
        cout << "4. Add Money\n";
        cout << "5. Withdrawal\n";
        cout << "6. Delete All Accounts";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> opt;
        cin.ignore();

        switch (opt) {
            case 1:
                cout << "\nEnter your full name: ";
                getline(cin, name);
                cout << "\nEnter the initial deposit (min 1000, in multiples of 100): ";
                do {
                    cin >> value;
                    if (value < 1000 || value % 100 != 0) {
                        cout << "\nInvalid amount. Please enter again: ";
                    }
                } while (value < 1000 || value % 100 != 0);

                box::create(name, value, head);
                box::saveData(head);
                break;

            case 2:
                box::display(head);
                break;

            case 3:
                cout << "\nEnter PIN of the account to delete: ";
                cin >> pin;
                box::deleteByPin(head, pin);
                box::saveData(head);
                break;

            case 4:
                cout << "\nEnter PIN of the account to add money: ";
                cin>>pin;
                do{
                    cout << "\nEnter Amount to add (multiple of 100/-): ";
                    cin>>amount;
                }while(amount%100!=0);
                
                box::addmoney(head, pin, amount);
                box::saveData(head);
                break;
            case 5:
                cout << "\nEnter PIN of the account to Withdrawal: ";
                cin>>pin;
                do{
                    cout << "\nEnter The Amount (multiple of 100/-): ";
                    cin>>amount;
                }while(amount%100!=0);
                amount*=(-1);
                
                box::addmoney(head, pin, amount);
                box::saveData(head);
                break;

            case 6:
                box::deleteAllAcount(head);
                box::erasefiledata();
                break;
            case 0:
                cout << "\nThank you for using our system. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid option! Please choose again.\n";
        }
    } while (opt != 0);

    return 0;
}