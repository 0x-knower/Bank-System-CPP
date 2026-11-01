#pragma once
#include <iostream>
using namespace std;

class clsPerson{
    private:
        string _FirstName;
        string _LastName;
        string _Email;
        string _Phone;

    public:

        clsPerson(string FirstName, string LastName, string Email, string Phone){
            _FirstName = FirstName;
            _LastName = LastName;
            _Email = Email;
            _Phone = Phone;
        }    

      
        void SetFirstName(string FirstName){
            _FirstName = FirstName;
        }

        string FirstName(){
            return _FirstName;
        }

        void SetLastName(string LastName){
            _LastName = LastName;
        }

        string LastName(){
            return _LastName;
        }

        string FullName(){
            return _FirstName + " " + _LastName;
        }

        void SetEmail(string Email){
            _Email = Email;
        }

        string Email(){
            return _Email;
        }

        void SetPhone(string Phone){
            _Phone = Phone;
        }

        string Phone(){
            return _Phone;
        }

        void Print(){
            cout << "\nInfo: ";
            cout << "\n_____________________";
            cout << "\nFirstName : " << _FirstName;
            cout << "\nLastName  : " << _LastName;
            cout << "\nFullName  : " << FullName();
            cout << "\nEmail     : " << _Email;
            cout << "\nPhone     : " << _Phone;
            cout << "\n_____________________";
        }

       
        
};