#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson{
public:
    struct stTransferLogRecord{
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;
    };

private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Separator = "#//#"){
        vector <string> vClientData;
        vClientData  = clsString::Split(Line,Separator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
    }

    static string _ConvertClientObjectToLine(clsBankClient Client,string Separator = "#//#"){
        string stClientRecord = "";

        stClientRecord += Client.FirstName() + Separator;
        stClientRecord += Client.LastName() + Separator;
        stClientRecord += Client.Email() + Separator;
        stClientRecord += Client.Phone() + Separator;
        stClientRecord += Client.AccountNumber() + Separator;
        stClientRecord += Client.GetPinCode() + Separator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

    static vector <clsBankClient>  _LoadClientsDataFormFile(){
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if(MyFile.is_open()){
            string Line;
            while (getline(MyFile,Line)){
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients){
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;

        if(MyFile.is_open()){
            for(clsBankClient C : vClients){
                if(C.MarkForDelete() == false){
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
                
            }
            MyFile.close();
        }
    }

    void _Update(){
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFormFile();

        for(clsBankClient &C : _vClients){
            if(C.AccountNumber() == AccountNumber()){
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine){
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if(MyFile.is_open()){
            MyFile << stDataLine <<endl;
            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject(){
        return clsBankClient(enMode::EmptyMode,"","","","","","",0);
    }

    string _PrepareTransferLogRecord(double Amount,clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
    {
        string TransferLog = "";
        TransferLog += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLog += AccountNumber() + Seperator;
        TransferLog += DestinationClient.AccountNumber() + Seperator;
        TransferLog += to_string(Amount) + Seperator;
        TransferLog += to_string(GetAccountBalance()) + Seperator;
        TransferLog += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        TransferLog += UserName;

        return TransferLog;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
        
        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::out | ios::app); 

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }


    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#"){
        stTransferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }

public:

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)
        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _PinCode = PinCode;
            _AccountBalance = AccountBalance;
        }

    bool MarkForDelete(){
        return _MarkForDelete;
    }

    bool IsEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber(){
        return _AccountNumber;
    }

    void SetPinCode(string PinCode){
        _PinCode = PinCode;
    }

    string GetPinCode(){
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance){
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance(){
        return _AccountBalance;
    }

    // No UI Related code iside object.
    // void Print(){
    //     cout << "\nClient Card:";
    //     cout << "\n___________________";
    //     cout << "\nFirstName    : "<< FirstName();
    //     cout << "\nLastName     : "<< LastName();
    //     cout << "\nFullName     : "<< FullName();
    //     cout << "\nEmail        : "<< Email();
    //     cout << "\nPhone        : "<< Phone();
    //     cout << "\nAcc.Number   : "<<_AccountNumber;
    //     cout << "\nPassword     : "<<_PinCode;
    //     cout << "\nBalance      : "<<_AccountBalance;
    //     cout << "\n___________________\n";
    // }

    static clsBankClient Find(string AccountNumber){
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if(MyFile.is_open()){
            string Line;
            while(getline(MyFile,Line)){
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if(Client.AccountNumber() == AccountNumber){
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }


    static clsBankClient Find(string AccountNumber, string PinCode){
        // fstream MyFile;
        // MyFile.open("Clients.txt", ios::in);
        // if (MyFile.is_open()){
        //     string Line;
        //     while(getline(MyFile,Line)){
        //         clsBankClient Client = _ConvertLinetoClientObject(Line);
        //         if(Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode){
        //             MyFile.close();
        //             return Client;
        //         }
        //     }
        //     MyFile.close();
        // }

        // فكره من Ai حلوه فشخ #//#
        clsBankClient Client = Find(AccountNumber);

        if(!Client.IsEmpty() && Client.GetPinCode() == PinCode){
            return Client;
        }

        return _GetEmptyClientObject();
        
    }


    enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};

    enSaveResults Save(){
        switch(_Mode){
            case enMode::EmptyMode:
                return enSaveResults::svFaildEmptyObject;

            case enMode::UpdateMode:
                _Update();
                return enSaveResults::svSucceeded;
                break;
            case enMode::AddNewMode:
                if(clsBankClient::IsClientExist(_AccountNumber))
                    return enSaveResults::svFaildAccountNumberExists;
                else{
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
        }
        return enSaveResults::svFaildEmptyObject;
    }

    static bool IsClientExist(string AccountNumber){
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete(){
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFormFile();

        for(clsBankClient &C : _vClients){
            if(C.AccountNumber() == _AccountNumber){
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
        
        *this = _GetEmptyClientObject();
        return true;
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber){
        return (clsBankClient(enMode::AddNewMode,"","","","",AccountNumber,"",0));
    }

    static vector <clsBankClient> GetClientsList(){
        return _LoadClientsDataFormFile();
    }

    static double GetTotalBalances(){
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances =0;
        for (clsBankClient Client : vClients){
            TotalBalances += Client.GetAccountBalance();
        }
        return TotalBalances;
    }

    void Deposit(double Amount){
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount){
        if(Amount > _AccountBalance){
            return false;
        }
        else{
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(double Amount, clsBankClient &DestinationClient, string UserName)
    {
        if (Amount > GetAccountBalance())
        {
            return false;
        }
    
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;

    }


    static  vector <stTransferLogRecord> GetTransfersLogList()
    {
        vector <stTransferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::in);//read Mode

        if (MyFile.is_open()){
            string Line;

            stTransferLogRecord TransferRecord;

            while (getline(MyFile, Line)){
                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }
    

};