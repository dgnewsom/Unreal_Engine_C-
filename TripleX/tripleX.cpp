#include <iostream>

void PlayGame()
{
    //Introduction text
    std::cout << "\nYou are a secret agent breaking into a secure server...\n";
    std::cout << "Enter the correct code to continue...\n";

    //Declare code numbers
    const int CodeA = 2, CodeB = 3, CodeC = 4;

    //Calculate sum and product
    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    //Print CodeSum and CodeProduct to console
    std::cout << "\n\tThere are 3 numbers in the code\n";
    std::cout << "\tThe sum of the numbers in the code is " << CodeSum << "\n";
    std::cout << "\tThe product of the numbers in the code is " << CodeProduct << "\n";

    //Get player guess
    int GuessA, GuessB, GuessC;
    std::cout << "\nEnter code (three digits separated by spaces)\n<<<< ";
    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;

    //Calculate player guess sum and product
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Compare player guess to code
    if(GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "\nCongratulations you're in!\n";
    }
    else
    {
        std::cout << "\nUnlucky - You were caught!\n";
    }
}

int main()
{
    PlayGame();

    return 0;
}
