#pragma once
#include "clsScreen.h"
#include <iomanip>
class clsTransferLogScreen : protected clsScreen
{
private:
	struct _stTransferLogRecord {
		string DateTime;
		string SenderAccountNumber;
		string ReceiverAccountNumber;
		float Amount;
		float SenderBalanceAfter;
		float ReceiverBalanceAfter;
		string UserName;
	};
	static _stTransferLogRecord _ConvertTransferLogLineToRecord(string Line)
	{
		_stTransferLogRecord Record;

		vector<string> DataLine = clsMyString::Split(Line, "#//#");

		if (DataLine.size() < 7)
			return Record;

		Record.DateTime = DataLine[0];
		Record.SenderAccountNumber = DataLine[1];
		Record.ReceiverAccountNumber = DataLine[2];
		Record.Amount = stof(DataLine[3]);
		Record.SenderBalanceAfter = stof(DataLine[4]);
		Record.ReceiverBalanceAfter = stof(DataLine[5]);
		Record.UserName = DataLine[6];

		return Record;
	}
    static vector<_stTransferLogRecord> GetTransferLogList()
    {
        vector<_stTransferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                    vTransferLogRecord.push_back(_ConvertTransferLogLineToRecord(Line));
            }
            MyFile.close(); 
        }

        return vTransferLogRecord;
    }
public:
    static void ShowTransactionLogScreen()
    {
        system("cls");
        _DrawScreenHeader("Bank System", "Transfer Log");

        vector<_stTransferLogRecord> vRecords = GetTransferLogList();

        if (vRecords.empty())
        {
            cout << "\n  \033[90mNo transfer records found.\033[0m\n";
            return;
        }

        string RESET = "\033[0m";
        string CYAN = "\033[1;36m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GREEN = "\033[1;32m";
        string GRAY = "\033[90m";

        // Header
        cout << CYAN
            << left
            << setw(5) << "#"
            << setw(22) << "Date & Time"
            << setw(12) << "Sender"
            << setw(12) << "Receiver"
            << setw(12) << "Amount"
            << setw(16) << "Sender Bal."
            << setw(16) << "Receiver Bal."
            << setw(12) << "Username"
            << RESET << "\n";

        cout << GRAY << string(105, '-') << RESET << "\n";

        // Rows
        int Counter = 1;
        for (_stTransferLogRecord& Record : vRecords)
        {
            cout << GRAY << left << setw(5) << Counter++
                << WHITE << setw(22) << Record.DateTime
                << setw(12) << Record.SenderAccountNumber
                << setw(12) << Record.ReceiverAccountNumber
                << YELLOW << setw(12) << fixed << setprecision(2) << Record.Amount
                << GREEN << setw(16) << Record.SenderBalanceAfter
                << setw(16) << Record.ReceiverBalanceAfter
                << WHITE << setw(12) << Record.UserName
                << RESET << "\n";
        }

        cout << GRAY << string(105, '-') << RESET << "\n";
        cout << WHITE << "  Total Records: " << YELLOW << vRecords.size() << RESET << "\n\n";
    }
};
