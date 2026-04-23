// InvestmentCalculator.h
// Declares the InvestmentCalculator class and ReportRow struct.
// This class handles all compound interest calculations for the Airgead Banking App.
// Follows Airgead Banking Standards: header guards, m_ prefix, t_ prefix.

#ifndef AIRGEAD_BANKING_INVESTMENTCALCULATOR_H_  // Header guard to prevent multiple inclusion
#define AIRGEAD_BANKING_INVESTMENTCALCULATOR_H_  // Define the guard symbol

#include <vector>  // Needed for std::vector to store report rows

// Struct to hold one row of the year-end report output.
// Each row represents one year's results.
struct ReportRow {
    int yearNumber;                // The year number (1, 2, 3, ...)
    double yearEndBalance;         // The balance at the end of that year
    double yearEndEarnedInterest;  // The total interest earned during that year
};

// Class that performs compound interest calculations based on user inputs.
// Encapsulates all financial logic separate from the user interface.
class InvestmentCalculator {
public:
    // Default constructor — initializes all member data to zero.
    InvestmentCalculator();

    // Stores the four user inputs into private member variables.
    // t_ prefix used for parameters per Airgead Banking Standards.
    void setInputs(double t_initialInvestmentAmount,   // Starting investment
        double t_monthlyDeposit,            // Monthly contribution
        double t_annualInterestRate,        // Annual rate as percentage
        int t_numberOfYears);               // Duration in years

    // Calculates year-end balances assuming NO monthly deposits are made.
    // Returns a vector of ReportRow, one per year.
    std::vector<ReportRow> calculateReportWithoutMonthlyDeposits() const;

    // Calculates year-end balances using the stored monthly deposit value.
    // Returns a vector of ReportRow, one per year.
    std::vector<ReportRow> calculateReportWithMonthlyDeposits() const;

private:
    // Private member data uses m_ prefix per Airgead Banking Standards.
    double m_initialInvestmentAmount;  // The starting investment amount entered by user
    double m_monthlyDeposit;           // The monthly deposit amount entered by user
    double m_annualInterestRate;       // The annual interest rate (percentage) entered by user
    int    m_numberOfYears;            // The number of years entered by user

    // Private helper — core calculation engine used by both public report methods.
    // t_monthlyDepositOverride is 0.0 for the "without" report,
    // or m_monthlyDeposit for the "with" report.
    std::vector<ReportRow> calculateReport(double t_monthlyDepositOverride) const;
};

#endif  // AIRGEAD_BANKING_INVESTMENTCALCULATOR_H_  // End of header guard