#include <iostream>
#include "BST.cpp"
#include <string>

int main()
{
    int num, den, stepCount, steps;
    std::string player1, player2;
    bool turn = 0;

    std::cout << "Enter a rational number (x y (omit the '/')): ";
    std::cin >> num >> den;
    std::cout << "\nEnter the max amount of steps you would like to take per turn: ";
    std::cin >> stepCount;
    std::cout << std::endl << std::endl << "Player 1's name: ";
    std::cin >> player1;
    std::cout << "\nPlayer 2's name: ";
    std::cin >> player2;
    std::cout << std::endl << std::endl;

    BST tree(num, den);

    while(tree.getCurrent() != nullptr && tree.getCurrent()->num != 0){
        turn = !turn;
        std::cout << "Current rational: " << tree.getCurrent()->num << "/"
                        << tree.getCurrent()->den << "\n\n"
                        << (turn ? player1 : player2) << "'s turn" << " how many steps: ";
        while (std::cin >> steps){
            if (steps > stepCount)
                std::cout << "Too high try again: ";
            else
                break;
        }
        tree.step(tree.getCurrent(), steps);
    }

    if(tree.getCurrent() == nullptr)
        std::cout << "\n\n" << (turn ? player1 : player2) << " loses!\n";
    else if (tree.getCurrent()->num == 0)
        std::cout << "\n\n" << (turn ? player1 : player2) << " wins!\n";

    std::cout << "Press enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}