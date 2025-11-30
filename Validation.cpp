#include <string>
using namespace std;

bool hasNonSpace(const string &str){
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] != ' ') 
            return true;
    }
    return false; 
}

bool isValidName(const string &name){
    if (!hasNonSpace(name)) 
    return false; 

    bool hasLetter = false;
    for (int i = 0; name[i] != '\0'; i++){
        char c = name[i];

        if (c == ' ') 
        continue; 

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
            hasLetter = true;
            continue;
        }

        return false; 
    }
    return hasLetter;
}

bool isValidAge(int age){
    return age > 0 && age < 120;
}

bool isValidSalary(double salary){
    return salary >= 0;
}

bool isValidGender(const char &gender){
    return gender == 'M' || gender == 'F' || gender == 'm' || gender == 'f';
}

bool isValidEmail(const string &email){
    if (!hasNonSpace(email))
     return false; 

    bool hasAt = false;
    bool hasDot = false;

    for (int i = 0; email[i] != '\0'; i++){
        char c = email[i];

        if (c == ' ')
         return false; 
        if (c == '@') 
        hasAt = true;
        if (c == '.') 
        hasDot = true;
    }

    return hasAt && hasDot;
}
