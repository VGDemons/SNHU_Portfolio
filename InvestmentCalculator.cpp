// InvestmentCalculator.cpp
// Implements the InvestmentCalculator class.
// Contains the monthly compound interest calculation logic
// as specified in the Airgead Banking Functional Requirements (page 3).
// Formula: Interest = (Opening Amount + Deposited Amount) * ((Rate/100)/12)

#include "InvestmentCalculator.h"  // Include the class declaration

// Default constructor — sets all member data to zero so the object starts clean.
InvestmentCalculator::InvestmentCalculator()
    : m_initialInvestmentAmount(0.0),  // No initial investment yet
    m_monthlyDeposit(0.0),           // No monthly deposit yet
    m_annualInterestRate(0.0),       // No interest rate yet
    m_numberOfYears(0) {             // No years yet
    // All members initialized via initializer list above.
}

// Stores the four user-provided values into private member variables.
// Called after the user enters their data on the input screen.
void InvestmentCalculator::setInputs(double t_initialInvestmentAmount,
    double t_monthlyDeposit,
    double t_annualInterestRate,
    int t_numberOfYears) {
    m_initialInvestmentAmount = t_initialInvestmentAmount;  // Store initial investment
    m_monthlyDeposit = t_monthlyDeposit;                    // Store monthly deposit
    m_annualInterestRate = t_annualInterestRate;            // Store annual interest rate
    m_numberOfYears = t_numberOfYears;                      // Store number of years
}

// Report 1: Calculates year-end balances with NO additional monthly deposits.
// Passes 0.0 as the monthly deposit override so no deposits are added each month.
std::vector<ReportRow> InvestmentCalculator::calculateReportWithoutMonthlyDeposits() const {
    return calculateReport(0.0);  // Override deposit to zero
}

// Report 2: Calculates year-end balances WITH the user's monthly deposit.
// Passes the stored m_monthlyDeposit value so deposits are added each month.
std::vector<ReportRow> InvestmentCalculator::calculateReportWithMonthlyDeposits() const {
    return calculateReport(m_monthlyDeposit);  // Use the user's monthly deposit
}

// Core calculation — processes each month within each year.
// Uses the compound interest formula from Requirement #4 (page 3):
//   Interest = (Opening Amount + Deposited Amount) * ((Interest Rate / 100) / 12)
//   Closing Balance = (Opening Amount + Deposited Amount) + Interest
std::vector<ReportRow> InvestmentCalculator::calculateReport(double t_monthlyDepositOverride) const {
    const int MONTHS_PER_YEAR = 12;  // Constant: 12 months in a year

    std::vector<ReportRow> rows;  // Will hold one ReportRow per year

    // Convert annual interest rate from a percentage to a monthly decimal rate.
    // Example: 5% annual -> (5 / 100) / 12 = 0.004167 per month.
    const double monthlyInterestRate = (m_annualInterestRate / 100.0) / MONTHS_PER_YEAR;

    // Start the running balance at the user's initial investment amount.
    double currentBalance = m_initialInvestmentAmount;

    // Loop through each year (1 to numberOfYears).
    for (int year = 1; year <= m_numberOfYears; ++year) {

        // Track total interest earned during this entire year.
        // This resets to zero at the start of each year.
        double yearlyInterestTotal = 0.0;

        // Loop through each month within this year (1 to 12).
        for (int month = 1; month <= MONTHS_PER_YEAR; ++month) {

            // Opening Amount: the balance at the start of this month.
            // For month 1 of year 1, this is the initial investment.
            // For subsequent months, this is the previous month's closing balance.
            const double openingAmount = currentBalance;

            // Deposited Amount: the monthly deposit for this month.
            // This is 0.0 for the "without deposits" report.
            // This is the user's monthly deposit for the "with deposits" report.
            const double depositedAmount = t_monthlyDepositOverride;

            // Total: the sum of the opening balance and this month's deposit.
            // This is the amount that earns interest this month.
            const double total = openingAmount + depositedAmount;

            // Interest: calculated using the formula from the requirements.
            // Interest = (Opening + Deposited) * ((Rate / 100) / 12)
            const double interest = total * monthlyInterestRate;

            // Closing Balance: the total plus the interest earned this month.
            // This becomes the opening amount for the next month.
            const double closingBalance = total + interest;

            // Update the running balance to this month's closing balance.
            currentBalance = closingBalance;

            // Add this month's interest to the yearly total.
            yearlyInterestTotal += interest;
        }
        // After all 12 months, build a report row for this year.
        ReportRow row;                               // Create a new row
        row.yearNumber = year;                       // Store the year number
        row.yearEndBalance = currentBalance;         // Store year-end balance
        row.yearEndEarnedInterest = yearlyInterestTotal;  // Store year-end interest

        rows.push_back(row);  // Add this year's row to the results vector
    }

    return rows;  // Return the complete set of yearly report rows
}