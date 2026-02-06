#include "input.hpp"
int get_int_input(int min, int max, std::string message){
    message += "Enter your selection: ";
    int to_return;
    std::string input;
    bool sucess = false;
    size_t size;

    //Print the prompt
    std::cout << message;
    //Get user input
    getline(std::cin, input);    
    while(!sucess){
        try{
            to_return = std::stoi(input, &size);
            //Check if stoi consumed the whole string of the user's input and
            //if the input was within the minimum and maximum range
            if(size != input.size() || to_return > max || to_return < min){
                throw std::invalid_argument("Invalid input");
            }
        }
        catch (std::invalid_argument const& ex){
            //Print error message and reprompt
            std::cout << std::endl << "Invalid input" << std::endl << std::endl;
            std::cout << message;
            getline(std::cin, input);
            continue;
        }
        sucess = true;
    }
    return to_return;
}