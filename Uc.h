#ifndef UC_H
#define UC_H

#include <limits>
#include <map>
#include <vector>

#include "Class.h"
using namespace std;

/**
 * @brief Class that represents a UC. It saves all corresponding classes of a
 * given UC.
 */

class Uc {
   private:
    string ucCode;
    // classCode -> class
    map<string, Class> classes;

   public:
    // Constructors
    /**
 * @brief Default constructor for the Uc class.
 *
     * @details Time complexity: O(1)
     */
    Uc();
    /**
 * @brief Constructor for the Uc class with an initial UC code.
 *
 * @details This constructor creates an instance of the Uc class with the provided UC code.
 *@details Time complexity: O(1)
 *
 * @param ucCode The UC code to initialize the Uc instance.
     */
    Uc(const string &ucCode);



    // Class related methods
    /**
 * @brief Add a new class to the Uc.
 *
 * @details This function adds a new class to the Uc instance, associating it with
     * its class code.
 *@details Time complexity: O(log N) where N is the total number of classes in the UC
 * @param newClass The Class instance to be added to the Uc.
     */
    void addClass(const Class &newClass);
    /**
 * @brief Get a specific class by its class code.
 *
 * @details This function retrieves a specific class within the Uc instance based on its class code.
 *@details Time complexity: O(log N) where N is the total number of classes in the UC
 * @param classCode The class code of the class to be retrieved.
 * @return A reference to the Class instance associated with the given class code.
     */
    Class &getClass(const string &classCode);
    /**
 * @brief Get all classes within the academic unit.
 *
 * @details This function returns a constant reference to a map containing all the
     * classes associated with the academic unit (UC) instance.
     * The map's keys are class codes, and the values are Class instances.
 *@details Time complexity: O(1)
 * @return A constant reference to a map of class codes to Class instances within the UC.
     */
    const map<string, Class> &getAllClasses() const;
    /**
 * @brief Check if a class exists within the academic unit (UC).
 *
 * @details This function checks if a class with the specified class code exists within the academic unit (UC) instance.
 *@details Time complexity: O(log N) where N is the total number of classes in the UC
 * @param classCode The class code to check for existence.
 * @return `true` if the class exists, `false` otherwise.
     */
    bool hasClass(const string &classCode) const;
    /**
 * @brief Check if class changes result in balanced class sizes.
 *
 * @details This function checks whether changing students between classes within the academic unit (UC) would lead to a balanced distribution of students across those classes.
 *@details Time complexity: O(N) where N is the total number of classes in the UC
 * @param originClassCode The class code of the origin class, or an empty string if not changing from a specific class.
 * @param destinyClassCode The class code of the destiny class, or an empty string if not changing to a specific class.
 * @return `true` if the change results in balanced class sizes, `false` otherwise.
     */
    bool balancedClasses(const string &originClassCode,
                         const string &destinyClassCode) const;
};

#endif
