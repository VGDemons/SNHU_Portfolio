// AirgeadBankingApp.h
// Declares the AirgeadBankingApp class.
// This class handles all user interaction: input gathering, validation,
// formatted display, and the main program loop.
// Follows Airgead Banking Standards: header guards, m_ prefix, t_ prefix.

#ifndef AIRGEAD_BANKING_AIRGEADBANKINGAPP_H_  // Header guard to prevent multiple inclusion
#define AIRGEAD_BANKING_AIRGEADBANKINGAPP_H_  // Define the guard symbol

#include <string>   // Needed for std::string
#include <vector>   // Needed for std::vector
#include "InvestmentCalculator.h"  // Needed for ReportRow struct

// Class that manages the full application lifecycle.
// Keeps main() minimal per Airgead Banking Standards (Portability section).
class AirgeadBankingApp {
public:
    // Entry point — runs the entire application input/output loop.
    void run();

private:
    // Removes leading and trailing whitespace from a string.
    // Used to clean user input before parsing.
    static std::string trim(const std::string& t_text);

    // Attempts to safely parse a double from a string.
    // Returns true if parsing succeeded, false otherwise.
    // Uses try/catch per Standards doc (Maintainability section).
    static bool tryParseDouble(const std::string& t_text, double& t_outValue);

    // Attempts to safely parse an integer from a string.
    // Returns true if parsing succeeded, false otherwise.
    // Uses try/catch per Standards doc (Maintainability section).
    static bool tryParseInt(const std::string& t_text, int& t_outValue);

    // Repeatedly prompts the user until a valid positive double is entered.
    // Used for Initial Investment Amount, Monthly Deposit, and Annual Interest.
    static double getPositiveDouble(const std::string& t_promptText);

    // Repeatedly prompts the user until a valid positive integer is entered.
    // Used for Number of Years.
    static int getPositiveInt(const std::string& t_promptText);

    // Displays the "Data Input" banner matching the screenshot on page 1.
    static void displayInputScreenHeader();

    // Displays the user's entered values in formatted form with $ and % symbols.
    // Matches the second screenshot on page 1 of the requirements.
    static void displayEnteredValues(double t_initialInvestmentAmount,
        double t_monthlyDeposit,
        double t_annualInterestRate,
        int t_numberOfYears);

    // Pauses execution and waits for the user to press Enter.
    // Satisfies the "Press any key to continue" requirement on page 1.
    static void waitForUserContinue();

    // Displays a formatted year-end report table with title, headers, and data rows.
    // Called twice: once for "Without Deposits" and once for "With Deposits."
    // Satisfies Requirement #2 on page 2.
    static void displayReport(const std::string& t_titleText,
        const std::vector<ReportRow>& t_rows);

    // Asks the user whether they want to run another scenario with different values.
    // Satisfies Requirement #3 on page 2.
    static bool askRunAgain();
};

#endif  // AIRGEAD_BANKING_AIRGEADBANKINGAPP_H_  // End of header guard