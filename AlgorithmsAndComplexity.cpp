#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>

using namespace std;

// Define a struct named 'Oblong' to represent rectangular objects with specified properties.
struct Oblong {
    double span, elevation; // The width and height of the oblong.
    double a, b; // Center 
    double corner; // Degrees of the corner 
};

// Calculate the corner angle of an oblong object based on its properties.
double calcOblongCorner(const Oblong& tango) {
    double halfelevation = tango.elevation / 2; // Calculate half of the oblong's elevation.
    double halfspan = tango.span / 2; // Calculate half of the oblong's span (width).
    double ans = sqrt(halfspan * halfspan + halfelevation * halfelevation); // Calculate the distance from the oblong's center to its corner using the Pythagorean theorem.
    return atan2(ans, sqrt(tango.a * tango.a + tango.b * tango.b)) * 180 * 2 / M_PI;
    // Calculate the arctangent (inverse tangent) of ans, converting the result from radians to degrees.
    // The atan2 function is used to ensure correct quadrant mapping.
    // The result is multiplied by 180 to convert from radians to degrees and then by 2 to account for the full angle (360 degrees).
    // Finally, the result is divided by M_PI to normalize it.
}

// Generate a random double value within the specified range [min, max].
double arbitraryMinMax(double min, double max) {
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
    std::uniform_real_distribution<double> dis(min, max); // Create a uniform real distribution with the specified minimum and maximum values. This distribution will produce random double values within the given range.
    return dis(gen); // Generate and return a random double value from the distribution using the generator.
}

// Check if two rectangular objects (Oblongs) overlap.
bool doRectanglesOverlap(const Oblong& tango1, const Oblong& tango2) {
    double answerb = abs(tango1.b - tango2.b); // Calculate the absolute difference in the 'b' (vertical) coordinates of the two Oblongs.
    double answera = abs(tango1.a - tango2.a); // Calculate the absolute difference in the 'a' (horizontal) coordinates of the two Oblongs.
    double semiWidthAggregate = (tango1.span + tango2.span) / 2; // Calculate the semi-width aggregate, which is the average of the widths (spans) of the two Oblongs.
    double semiElevationAggregate = (tango1.elevation + tango2.elevation) / 2; // Calculate the semi-elevation aggregate, which is the average of the heights (elevations) of the two Oblongs.
    return answera <= semiWidthAggregate && answerb <= semiElevationAggregate;
    // Check if the absolute 'a' difference is less than or equal to half the total width (span) of both Oblongs
    // AND if the absolute 'b' difference is less than or equal to half the total height (elevation) of both Oblongs.
    // If both conditions are met, the Oblongs overlap, and the function returns true; otherwise, it returns false.
}



int main() {
    int second;
    cout << "Enter the number of rectangles: "; // Prompt the user to input the number of rectangles.
    cin >> second; // Read the user's input and store it in the 'second' variable.
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator based on the current time.
    vector<Oblong> oblong; // Create a vector to store the generated Oblong objects (rectangles).

    // Loop to generate 'second' number of rectangles.
    for (int first = 0; first < second; ++first) {
        Oblong tango;
        tango.corner = arbitraryMinMax(0.0, 360.0); // Generate a random corner angle within the range [0.0, 360.0].
        tango.a = arbitraryMinMax(-50.0, 50.0); // Generate random 'a' (horizontal) coordinate within the range [-50.0, 50.0].
        tango.b = arbitraryMinMax(-50.0, 50.0); // Generate random 'b' (vertical) coordinate within the range [-50.0, 50.0].
        tango.elevation = arbitraryMinMax(1.0, 5.0); // Generate random elevation (height) within the range [1.0, 5.0].
        tango.span = arbitraryMinMax(1.0, 5.0); // Generate random span (width) within the range [1.0, 5.0].

         // Check if the newly generated rectangle intersects with any of the existing rectangles.
        bool ifIntersecting = false;
        for (const Oblong& existingRect : oblong) {
            if (doRectanglesOverlap(tango, existingRect)) {
                ifIntersecting = true;
                break;
            }
        }
        // If the newly generated rectangle does not intersect with any existing ones, add it to the vector.
        if (!ifIntersecting) {
            oblong.push_back(tango);
        } else {
            // If there is an intersection, decrement 'first' to regenerate the rectangle.
            --first; 
        }
    }

    // Create an output file for writing rectangle data in CSV format.
   std::ofstream outputFile("anglesForRectangle.csv");
   // Check if the file is successfully opened.
    if (outputFile.is_open()) {
        // Write the rectangle data to the CSV file
        for (const Oblong& rect : oblong) {
            outputFile << rect.a << "," << rect.b << "," << rect.span << "," << rect.elevation << "," << rect.corner << std::endl;
        }
        outputFile.close(); // Close the output file.
        std::cout << "Data of Rectangles written to 'anglesForRectangle.csv'" << std::endl; // Inform the user that the data has been written to the CSV file.
    } else {
        std::cerr << "Unable to open anglesForRectangle.csv" << std::endl; // Display an error message if the file could not be opened.
    }

    // Calculate the total occlusion angle over all rectangles.
    double allinallCorner = 0.0;
    for (const Oblong& rect : oblong) {
        allinallCorner += calcOblongCorner(rect);
    }

    // Display the total occlusion angle to the user.
    std::cout << "Total occlusion angle over all rectangles: " << allinallCorner << " degrees" << std::endl;

    return 0;
}
