//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Eskinder Kassahun
//============================================================================

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

struct Course {
    std::string courseNumber;            // Unique course identifier
    std::string courseName;              // Course title
    std::vector<std::string> prerequisites; // List of prerequisite course numbers
};

// Function to load data from a CSV file into a map
void loadDataStructure(std::map<std::string, Course>& courses) {
    std::string fileName;
    std::cout << "Enter the course data file name: ";
    std::cin >> fileName;
    
    std::ifstream file(fileName);  // Open the file
    if (!file) {                   // Error handling if file fails to open
        std::cerr << "Unable to open file " << fileName << std::endl;
        return;
    }
    
    std::string line;
    while (getline(file, line)) {   // Read each line from the file
        std::istringstream stream(line);
        std::string courseNumber, courseName, prerequisite;
        
        // Read course number and name
        getline(stream, courseNumber, ',');
        getline(stream, courseName, ',');
        
        Course course;
        course.courseNumber = courseNumber;
        course.courseName = courseName;
        
        // Collect all prerequisites
        while (getline(stream, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }
        
        courses[courseNumber] = course;  // Insert course into the map
    }
    file.close();
    std::cout << "Data loaded successfully." << std::endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(const std::map<std::string, Course>& courses) {
    std::cout << "Here is a sample schedule:" << std::endl;
    for (const auto& [courseNumber, course] : courses) {
        std::cout << courseNumber << ", " << course.courseName << std::endl;
    }
}

// Function to print information for a specific course
void printCourseInfo(const std::map<std::string, Course>& courses) {
    std::string courseNumber;
    std::cout << "What course do you want to know about? ";
    std::cin >> courseNumber;
    
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        std::cout << course.courseNumber << ", " << course.courseName << std::endl;
        std::cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            std::cout << "None";
        } else {
            for (const auto& prereq : course.prerequisites) {
                std::cout << prereq << " ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Course not found." << std::endl;
    }
}

// Function to display the main menu
void displayMenu() {
    std::cout << "1. Load Data Structure." << std::endl;
    std::cout << "2. Print Course List." << std::endl;
    std::cout << "3. Print Course." << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "What would you like to do? ";
}

// Main function
int main() {
    std::map<std::string, Course> courses;  // Data structure to store courses
    int choice;
    
    std::cout << "Welcome to the course planner." << std::endl;
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                loadDataStructure(courses);  // Load data from file
                break;
            case 2:
                printCourseList(courses);    // Print sorted course list
                break;
            case 3:
                printCourseInfo(courses);    // Print specific course details
                break;
            case 9:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cerr << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 9);
    
    return 0;
}