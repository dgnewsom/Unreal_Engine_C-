#include <iostream>
#include <ctime>

void PrintIntroduction(int DifficultyLevel)
{
    //Introduction text
    std::cout << "\nYou are a secret agent breaking into a level " << DifficultyLevel <<  " secure server...\n";
    std::cout << "Enter the correct code to continue...\n";
}

bool PlayGame(int DifficultyLevel)
{
    PrintIntroduction(DifficultyLevel);

    //Declare code numbers
    const int CodeA = rand() % DifficultyLevel + DifficultyLevel, CodeB = rand() % DifficultyLevel + DifficultyLevel, CodeC = rand() % DifficultyLevel + DifficultyLevel;

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
        return true;
    }
    else
    {
        std::cout << "\nUnlucky - Try Again!\n";
        return false;
    }
}

int main()
{
    srand(time(NULL));

    int Difficulty = 1;
    int MaxDifficulty = 9;

    while(Difficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(Difficulty);
        std::cin.clear();
        std::cin.ignore();
        if(bLevelComplete)
        {
            ++Difficulty;
        }
    }

    std::cout << "Congratulations you have completed the game!";

    return 0;
}
