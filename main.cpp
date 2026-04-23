// main.cpp
// Entry point for the Airgead Banking investment calculator application.
// Per Airgead Banking Standards (Portability section):
//   "Have minimal code in main(). Most of your code should be in classes
//    and main is used simply as a driver to instantiate objects of these
//    classes and call proper functions."
// Per Airgead Banking Standards (Maintainability section):
//   "Properly utilize try/catch statements" to exit gracefully.

#include <iostream>             // Needed for std::cerr
#include "AirgeadBankingApp.h"  // Include the application class declaration

int main() {
    // Wrap the entire program in a try/catch block.
    // This ensures the program exits gracefully if an unexpected error occurs,
    // rather than crashing with an unhandled exception.
    // Per Standards doc: "Consider using try/catch" and "exit gracefully."
    try {
        AirgeadBankingApp app;  // Create the application object on the stack (no raw memory)
        app.run();              // Run the full application loop
    }
    catch (const std::exception& ex) {
        // Catch any standard library exception and display a meaningful message.
        std::cerr << "A fatal error occurred: " << ex.what() << std::endl;
        return 1;  // Return non-zero to indicate an error
    }
    catch (...) {
        // Catch any other unknown exception type.
        std::cerr << "An unknown fatal error occurred." << std::endl;
        return 1;  // Return non-zero to indicate an error
    }

    return 0;  // Return 0 to indicate successful program completion
}