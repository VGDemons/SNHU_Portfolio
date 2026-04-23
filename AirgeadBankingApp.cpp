// AirgeadBankingApp.cpp
// Implements the AirgeadBankingApp class.
// Handles all console input/output, input validation, report display,
// and drives the InvestmentCalculator class.
// Follows Airgead Banking Standards: try/catch, C++ casts, t_ prefix, m_ prefix.

#include "AirgeadBankingApp.h"  // Include the class declaration

#include <cctype>      // Needed for std::toupper
#include <iomanip>     // Needed for std::setw, std::setprecision, std::fixed
#include <iostream>    // Needed for std::cout, std::cin, std::cerr
#include <limits>      // Needed for std::numeric_limits
#include <stdexcept>   // Needed for std::exception

// Removes leading and trailing whitespace from a string.
// This prevents issues when the user accidentally types spaces before/after input.
std::string AirgeadBankingApp::trim(const std::string& t_text) {
    const std::string whitespace = " \t\n\r";  // Characters considered whitespace

    // Find the first character that is NOT whitespace.
    const size_t start = t_text.find_first_not_of(whitespace);

    // If the entire string is whitespace, return an empty string.
    if (start == std::string::npos) {
        return "";
    }

    // Find the last character that is NOT whitespace.
    const size_t end = t_text.find_last_not_of(whitespace);

    // Return the substring between start and end (inclusive).
    return t_text.substr(start, end - start + 1);
}

// Safely attempts to convert a string to a double value.
// Returns true if the conversion succeeded, false if it failed.
// Uses try/catch per Airgead Banking Standards (Maintainability: avoid assert, use try/catch).
bool AirgeadBankingApp::tryParseDouble(const std::string& t_text, double& t_outValue) {
    try {
        size_t idx = 0;                        // Will track how many characters stod consumed
        const std::string cleaned = trim(t_text);  // Remove whitespace from input

        // Empty strings are not valid numeric input.
        if (cleaned.empty()) {
            return false;  // Signal failure
        }

        // Attempt to convert the string to a double.
        t_outValue = std::stod(cleaned, &idx);

        // Make sure the ENTIRE string was a number (no trailing letters like "12abc").
        return idx == cleaned.size();  // True only if all characters were consumed
    }
    catch (...) {
        // If stod throws any exception, catch it and return false gracefully.
        // This prevents the program from crashing on bad input.
        return false;
    }
}

// Safely attempts to convert a string to an integer value.
// Returns true if the conversion succeeded, false if it failed.
// Uses try/catch per Airgead Banking Standards (Maintainability section).
bool AirgeadBankingApp::tryParseInt(const std::string& t_text, int& t_outValue) {
    try {
        size_t idx = 0;                        // Will track how many characters stoll consumed
        const std::string cleaned = trim(t_text);  // Remove whitespace from input

        // Empty strings are not valid numeric input.
        if (cleaned.empty()) {
            return false;  // Signal failure
        }

        // Parse as long long first so we can check for int overflow.
        long long value = std::stoll(cleaned, &idx);

        // Ensure the full string was consumed (no trailing junk characters).
        if (idx != cleaned.size()) {
            return false;  // Trailing characters found — not a clean integer
        }

        // Check that the value fits within the range of an int.
        if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
            return false;  // Value is too large or too small for an int
        }

        // Safe C++ style cast per Standards doc (Safety: use C++ casts, not C casts).
        t_outValue = static_cast<int>(value);
        return true;  // Successful parse
    }
    catch (...) {
        // Catch any conversion errors and return false gracefully.
        return false;
    }
}

// Repeatedly prompts the user until a valid positive double is entered.
// The requirements (page 1) specify that Initial Investment Amount and
// Monthly Deposit should be "a positive real number."
double AirgeadBankingApp::getPositiveDouble(const std::string& t_promptText) {
    while (true) {  // Loop until valid input is received
        std::cout << t_promptText;  // Display the prompt to the user
        std::string line;           // Variable to hold the raw input string
        std::getline(std::cin, line);  // Read the entire line (safer than cin >>)

        double value = 0.0;  // Will hold the parsed numeric value

        // Try to parse the input as a double.
        if (!tryParseDouble(line, value)) {
            // Input was not a valid number — inform the user and loop again.
            std::cout << "  Error: Invalid input. Please enter a numeric value." << std::endl;
            continue;  // Go back to the top of the while loop
        }

        // Check that the value is positive (greater than zero).
        if (value <= 0.0) {
            // Input was a number but not positive — inform and loop again.
            std::cout << "  Error: Please enter a value greater than 0." << std::endl;
            continue;  // Go back to the top of the while loop
        }

        return value;  // Valid positive double — return it to the caller
    }
}

// Repeatedly prompts the user until a valid positive integer is entered.
// Used for the "Number of Years" field which must be a whole number >= 1.
int AirgeadBankingApp::getPositiveInt(const std::string& t_promptText) {
    while (true) {  // Loop until valid input is received
        std::cout << t_promptText;  // Display the prompt to the user
        std::string line;           // Variable to hold the raw input string
        std::getline(std::cin, line);  // Read the entire line

        int value = 0;  // Will hold the parsed integer value

        // Try to parse the input as an integer.
        if (!tryParseInt(line, value)) {
            // Input was not a valid whole number — inform and loop again.
            std::cout << "  Error: Invalid input. Please enter a whole number." << std::endl;
            continue;  // Go back to the top of the while loop
        }

        // Check that the value is positive (at least 1 year).
        if (value <= 0) {
            // Input was an integer but not positive — inform and loop again.
            std::cout << "  Error: Please enter a value greater than 0." << std::endl;
            continue;  // Go back to the top of the while loop
        }

        return value;  // Valid positive integer — return it to the caller
    }
}

// Displays the "Data Input" banner.
// Matches the first screenshot on page 1 of the functional requirements.
void AirgeadBankingApp::displayInputScreenHeader() {
    std::cout << "**********************************" << std::endl;   // Top border
    std::cout << "********** Data Input ************" << std::endl;   // Title line
    std::cout << "**********************************" << std::endl;   // Bottom border
}

// Displays the user's entered values in a formatted summary.
// Uses $ for dollar amounts and % for the interest rate.
// Matches the second screenshot on page 1 of the functional requirements.
void AirgeadBankingApp::displayEnteredValues(double t_initialInvestmentAmount,
    double t_monthlyDeposit,
    double t_annualInterestRate,
    int t_numberOfYears) {
    std::cout << std::fixed << std::setprecision(2);  // Format money to 2 decimal places

    // Display each field with its label and formatted value.
    std::cout << "Initial Investment Amount: $"
        << t_initialInvestmentAmount << std::endl;  // e.g., $1.00
    std::cout << "Monthly Deposit: $"
        << t_monthlyDeposit << std::endl;           // e.g., $50.00
    std::cout << "Annual Interest: %"
        << t_annualInterestRate << std::endl;       // e.g., %5.00
    std::cout << "Number of Years: "
        << t_numberOfYears << std::endl;            // e.g., 5
}

// Pauses execution until the user presses Enter.
// Satisfies the "Press any key to continue . . ." requirement from page 1.
void AirgeadBankingApp::waitForUserContinue() {
    std::cout << "Press any key to continue . . ." << std::endl;  // Prompt user
    std::string dummy;          // Variable to absorb the Enter keypress
    std::getline(std::cin, dummy);  // Wait for user to press Enter
}

// Displays a formatted year-end report table.
// Called twice per run:
//   1) "Balance and Interest Without Additional Monthly Deposits"
//   2) "Balance and Interest With Additional Monthly Deposits"
// Satisfies Requirement #2 on page 2 of the functional requirements.
void AirgeadBankingApp::displayReport(const std::string& t_titleText,
    const std::vector<ReportRow>& t_rows) {
    // Print a blank line before the report for readability.
    std::cout << std::endl;

    // Print the report title (centered above the table).
    std::cout << "    " << t_titleText << std::endl;

    // Print the top border of the table using equals signs.
    std::cout << "================================================================="
        << std::endl;

    // Print the column headers: Year, Year End Balance, Year End Earned Interest.
    std::cout << std::left << std::setw(10) << "  Year"        // Left-aligned year header
        << std::right << std::setw(20) << "Year End Balance"  // Right-aligned balance header
        << std::setw(28) << "Year End Earned Interest"        // Right-aligned interest header
        << std::endl;

    // Print a separator line using dashes.
    std::cout << "-----------------------------------------------------------------"
        << std::endl;

    // Set formatting for dollar values: fixed-point with 2 decimal places.
    std::cout << std::fixed << std::setprecision(2);

    // Loop through each report row and print the year's data.
    for (const ReportRow& row : t_rows) {
        std::cout << std::right << std::setw(6) << row.yearNumber      // Year number
            << std::right << std::setw(24) << row.yearEndBalance  // Year-end balance ($)
            << std::right << std::setw(28) << row.yearEndEarnedInterest  // Interest ($)
            << std::endl;  // Move to the next line
    }
}

// Asks the user whether they want to run another scenario with different values.
// Satisfies Requirement #3: "The user should be able to test different monthly
// deposit amounts, interest rates, and lengths of time."
bool AirgeadBankingApp::askRunAgain() {
    while (true) {  // Loop until a valid Y or N is received
        std::cout << std::endl;  // Blank line for readability
        std::cout << "Would you like to test different values? (Y/N): ";  // Prompt

        std::string line;              // Variable to hold user's response
        std::getline(std::cin, line);  // Read the full line of input
        line = trim(line);             // Remove any leading/trailing whitespace

        // If the user just pressed Enter without typing anything, re-prompt.
        if (line.empty()) {
            continue;  // Go back to the top of the while loop
        }

        // Convert the first character to uppercase for case-insensitive comparison.
        // Uses static_cast (C++ style) per Standards doc (Safety section).
        const char c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(line[0]))
            );

        if (c == 'Y') {
            return true;   // User wants to run again
        }
        if (c == 'N') {
            return false;  // User wants to quit
        }

        // If input was neither Y nor N, inform the user and loop again.
        std::cout << "  Please enter Y or N." << std::endl;
    }
}

// Main application loop.
// Gathers input from the user, calculates both reports, displays results,
// and then offers to repeat with different values.
// This method is called from main() to keep main() minimal
// per Airgead Banking Standards (Portability section).
void AirgeadBankingApp::run() {
    bool runAgain = true;  // Controls the main application loop

    while (runAgain) {  // Continue running until the user chooses to stop

        // STEP 1: Display the Data Input header banner (Requirement #1).
        displayInputScreenHeader();

        // STEP 2: Gather the four inputs from the user with validation.
        // Each function loops until the user provides valid input.
        const double initialInvestmentAmount =
            getPositiveDouble("Initial Investment Amount: $");  // Get starting investment

        const double monthlyDeposit =
            getPositiveDouble("Monthly Deposit: $");            // Get monthly deposit

        const double annualInterestRate =
            getPositiveDouble("Annual Interest: %");            // Get annual interest rate

        const int numberOfYears =
            getPositiveInt("Number of Years: ");                // Get number of years

        // STEP 3: Display the entered values back to the user (second screenshot, page 1).
        std::cout << std::endl;              // Blank line for readability
        displayInputScreenHeader();          // Re-display the banner
        displayEnteredValues(               // Show all four values formatted
            initialInvestmentAmount,
            monthlyDeposit,
            annualInterestRate,
            numberOfYears
        );

        // STEP 4: Pause and wait for the user to continue (Requirement #1).
        waitForUserContinue();

        // STEP 5: Create the calculator object and set its inputs.
        InvestmentCalculator calculator;  // Instantiate the calculator
        calculator.setInputs(            // Pass all four user values
            initialInvestmentAmount,
            monthlyDeposit,
            annualInterestRate,
            numberOfYears
        );

        // STEP 6: Calculate both reports (Requirement #2).
        // Report 1: year-end balances WITHOUT additional monthly deposits.
        const std::vector<ReportRow> withoutDeposits =
            calculator.calculateReportWithoutMonthlyDeposits();

        // Report 2: year-end balances WITH additional monthly deposits.
        const std::vector<ReportRow> withDeposits =
            calculator.calculateReportWithMonthlyDeposits();

        // STEP 7: Display both reports to the console (Requirement #2).
        // Display the first report — without monthly deposits.
        displayReport(
            "Balance and Interest Without Additional Monthly Deposits",
            withoutDeposits
        );

        // Display the second report — with monthly deposits.
        displayReport(
            "Balance and Interest With Additional Monthly Deposits",
            withDeposits
        );

        // STEP 8: Ask if the user wants to test different values (Requirement #3).
        runAgain = askRunAgain();

        std::cout << std::endl;  // Blank line before next iteration or exit
    }
}