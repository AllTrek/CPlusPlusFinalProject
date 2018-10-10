


#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>
using namespace std;


// Sets default values for the seating chart.
const int ROW     = 15;
const int COLOUM  = 10;
const int SECTION = 3;


void mainMenu(double (&)[15], int (&)[ROW][COLOUM][SECTION], int(&), double (&));
void rowPriceConfigMenu(double (&)[15], int (&)[ROW][COLOUM][SECTION], int (&));
void setDefaultChartValue(int (&)[ROW][COLOUM][SECTION]);
void setRowPrice(double (&)[15]);
void purchaseTicket(int (&)[ROW][COLOUM][SECTION], double (&)[15], double (&),int (&));
void printRows(int (&)[ROW][COLOUM][SECTION], int (&));
void checkRowSeatsAvailability(int (&seats)[ROW][COLOUM][SECTION],int (&));
void viewRowPrices(double (&)[15]);
void loadRowPrice(double (&)[15]);
void saveRowPrice(double (&)[15]);
void loadSeatChart(int (&)[ROW][COLOUM][SECTION],double (&)[15], double (&),int (&));
void saveSeatChart(int (&seats)[ROW][COLOUM][SECTION]);
void totalTicketFile(int (&seats)[ROW][COLOUM][SECTION], int (&totalSeatsAvailable), double (&seatPrice)[15], double (&totalTicketPrice));
void bulkPricePurchase(double(&)[15]);
void text_animation(char a[100]);



int main(){
    //Seat,SeatPrice, totalTicketSales and totalSeatsAvailable get accessed within other function
    int seats[ROW][COLOUM][SECTION];
    double seatPrice[15];
    double totalTicketSales = 0;
    int totalSeatsAvailable = 0;
    char userSelection = 'p';
    int loopMenu = 0;

     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 15);

    // Set up for start up configuration menu
    rowPriceConfigMenu(seatPrice, seats, totalSeatsAvailable);
    system("cls");
    loadSeatChart(seats,seatPrice,totalTicketSales,totalSeatsAvailable);
    mainMenu(seatPrice, seats, totalSeatsAvailable, totalTicketSales); //calls menu

    // Allows the user to go back to the main menu once a function has ended
    do{

        cout << " Return to Main Menu? [Y/n] ";
        cin >> userSelection;
        userSelection = toupper(userSelection);

        if(userSelection == 'Y'){

            mainMenu(seatPrice, seats, totalSeatsAvailable, totalTicketSales);

        }else if(userSelection == 'N'){

            loopMenu = 1;
        }else{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n Error: Invalid Value. Please try again \n\n";
            SetConsoleTextAttribute(hConsole, 15);
        }

    }while (loopMenu == 0);
    system("cls");




    return 0;
}

//Main menu. Passes the values from the main here to call other functions.
void mainMenu(double (&seatPrice)[15], int (&seats)[ROW][COLOUM][SECTION], int(&totalSeatsAvailable), double (&totalTicketPrice)){





    int userSelection = 0;
     system("cls");
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 10);

     cout << '\n' << setw(29) << "Main Menu";
     SetConsoleTextAttribute(hConsole, 15);


    cout << "\n===============================================\n\n";
    cout << " Please select one of the options available\n\n";

    cout << " [1] View Seating Chart\n";
    cout << " [2] Purchase Ticket\n";
    cout << " [3] View total ticket sales\n";
    cout << " [4] View number of available seats\n";
    cout << " [5] view row prices\n";

    SetConsoleTextAttribute(hConsole, 10);

     cout << '\n' << setw(29) << "More Options";


     SetConsoleTextAttribute(hConsole, 15);
     cout << "\n=============================================\n\n";
    cout << " [6]  Save row price\n";
    cout << " [7]  Load row price\n";
    cout << " [8]  Set individual row price\n"; //reset seating chart
    cout << " [9]  Set bulk row price\n";
    cout << " [10] Reset seating chart\n"; // add new row price // load road price file  // load seating chart file
    cout <<" [11] Save seating chart\n"; // this one
    cout <<" [12] Load Seating chart file\n"; // this one
    cout <<" [13] Program Info\n"; // this one
    cout <<" [14] Exit\n";
    cout << "===============================================\n\n";
    cout << "> ";
    cin >> userSelection;

    //Access different function based on user input
    if(userSelection > 0){

        switch (userSelection) {
            case 1:
                system("cls");
                printRows(seats,totalSeatsAvailable);
                break;

            case 2:
                system("cls");
                purchaseTicket(seats,seatPrice,totalTicketPrice,totalSeatsAvailable);
                break;

            case 3:
                system("cls");
                cout << "\n\n The total amount for tickets purchased is $" << totalTicketPrice << '\n';
                break;
            case 4:
                system("cls");
                totalSeatsAvailable += -450;
                checkRowSeatsAvailability(seats,totalSeatsAvailable);
                break;

            case 5:
                system("cls");
                viewRowPrices(seatPrice);
                break;
            case 6:
                system("cls");
                saveRowPrice(seatPrice);
                break;
            case 7:
                system("cls");
                loadRowPrice(seatPrice);
                totalTicketPrice = 0;
                totalTicketFile(seats, totalSeatsAvailable, seatPrice, totalTicketPrice);
                break;
            case 8:
                system("cls");
                setRowPrice(seatPrice);
                totalTicketPrice = 0;
                totalTicketFile(seats, totalSeatsAvailable, seatPrice, totalTicketPrice);
                break;
            case 9:
                system("cls");
                bulkPricePurchase(seatPrice);
                totalTicketPrice = 0;
                totalTicketFile(seats, totalSeatsAvailable, seatPrice, totalTicketPrice);
                break;
            case 10:
               cout << "Seating chart reset";
                system("pause");
                setDefaultChartValue(seats);
                totalTicketPrice = 0;
                break;
            case 11:   // check if need to do all this the load seat chart should have this fixed
                system("cls");
                saveSeatChart(seats);
                break;
            case 12:
                system("cls");
                loadSeatChart(seats, seatPrice, totalTicketPrice, totalSeatsAvailable);
                totalTicketPrice = 0;
                totalTicketFile(seats, totalSeatsAvailable, seatPrice, totalTicketPrice);
                break;
            case 13:
                system("cls");
                //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                cout << " License: ";
                SetConsoleTextAttribute(hConsole, 12);
                cout << "Inactive";
                SetConsoleTextAttribute(hConsole, 15);
                text_animation(" \n It has been dedicated that you are running an inactive version of the program.\n");
                text_animation(" Criminal copyright infringement is punishable by up to 5 years in prison and a fine of $250,000. \n");

                text_animation("\n Theater Seating V 2.0 \n By: Raul Garcia\n");
                text_animation(" Copyright 2018 The Best Project, Inc. All Rights Reserved\n\n");
                break;
            case 14:
                exit(1);
                break;

            default:
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n Error: Invalid option. Please try again \n\n";
                SetConsoleTextAttribute(hConsole, 15);
                break;
        }
    }else{
        cin.clear();
        cin.ignore(100, '\n');
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n Error: Invalid Value. Please try again \n\n";
            SetConsoleTextAttribute(hConsole, 15);
    }

}



//Starting menu for row price configuration.

void rowPriceConfigMenu(double (&seatPrice)[15], int (&seats)[ROW][COLOUM][SECTION], int (&totalSeatsAvailable)){
    char userChoice = 'a';

    cout << '\n' << setw(40) << "Row Price Configuration\n\n";
    do{
        cout << " Would you like to load a saved row price? [Y/n] ";
        cin  >> userChoice;
        userChoice = toupper(userChoice);


        if(userChoice == 'Y'){
            system("cls");
            cout << '\n' << setw(40) << "Row Price Configuration\n\n";
            loadRowPrice(seatPrice);

        }else if(userChoice == 'N'){

            system("cls");
             cout << '\n' << setw(40) << "Row Price Configuration\n\n";
            cout << " Would you like to enter the price individually? [Y/n] ";

            cin >> userChoice;
            userChoice = toupper(userChoice);

            if(userChoice == 'Y'){
                system("cls");
                cout << '\n' << setw(40) << "Row Price Configuration\n\n";
                setRowPrice(seatPrice);

            }else if(userChoice == 'N'){
                system("cls");
                bulkPricePurchase(seatPrice);
            }


        }else{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << " Please Enter a valid choice.\n\n";
            SetConsoleTextAttribute(hConsole, 15);


        }

    }while(userChoice != 'Y' && userChoice != 'N' );
}



//sets the default values which is 1 for the seating chart
void setDefaultChartValue(int (&seats)[ROW][COLOUM][SECTION]){

    for(int i = 0; i < SECTION; i++){

        for(int x = 0; x < COLOUM; x++){

            for(int y = 0; y < ROW; y++){

                seats[y][x][i] = 1;
            }
        }
    }
}


// Allows the user to enter a price for the rows

void setRowPrice(double (&seatPrice)[15]){
    //

    double userPay = 0.00;

    cout << "\n\n Please enter a price for each row\n";

    for(int i = 0; i < ROW; i++){

        cout << " row number: "  << setw(3) << i + 1 << setw(5) << " $ ";
        cin >> userPay;

        if(userPay >= 0.00){
            seatPrice[i] = userPay;
        }else{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << " Please enter a valid price\n\n";
            SetConsoleTextAttribute(hConsole, 15);


            i = i -1;

        }

    }

}

// Allows the user to see the row prices
void viewRowPrices(double (&seatPrice)[15]){
    cout << fixed << setprecision(2);
    cout << "\n\n";
    for(int i = 0; i < 15; i++){
        if(i < 9){
            cout << " Row: "<< (i+1) << setw(11) << " Price: $" << seatPrice[i] << '\n';
        }else{
            cout << " Row: "<< (i+1) << setw(10) << " Price: $" << seatPrice[i] << '\n';
        }

    }


}

//Allows the user to purchase a ticket
void purchaseTicket(int (&seats)[ROW][COLOUM][SECTION], double (&seatPrice)[15], double (&totalTicketPrice),int (&totalSeatsAvailable)){

    int  selectRow = 0,
    selectSeatNumber = 0,
    selectSeatSection = 0;
    char userChoice = 'Y';
    char userConfirm = 'p';

    cout << setw(35) << "Purchase Ticket: \n\n";

    do{
        printRows(seats,totalSeatsAvailable);
        cout << " Enter Row: ";
        cin  >> selectRow;
        cout << "\n Enter Seat Number: ";
        cin  >> selectSeatNumber;
        cout << "\n Enter Section: ";
        cin  >>  selectSeatSection;
        //checks for validation

        if(selectRow > 0 && selectRow < 16 && selectSeatNumber > -1 && selectSeatNumber < 10 &&selectSeatSection > 0 && selectSeatSection < 4){
            cout << fixed << setprecision(2);
            cout << " Ticket Cost: $" << seatPrice[selectRow - 1] << "\n\n";
            cout << " confirm purchase [Y/n]";
            cin >> userConfirm;
            userConfirm = toupper(userConfirm);


            if(userConfirm == 'Y'){

                if(selectSeatNumber == 0){
                    selectSeatNumber = 10;
                }
                //check for second validation
                if(seats[selectRow - 1][selectSeatNumber - 1][selectSeatSection - 1] != 0){
                    //the -1 is for the starting at 0
                    seats[selectRow - 1][selectSeatNumber - 1][selectSeatSection - 1] = 0;
                    totalTicketPrice += seatPrice[selectRow - 1];

                    cout <<  " Would you like to purchase another ticket? [Y/n] ";
                    cin  >> userChoice;
                    userChoice = toupper(userChoice);
                }else{

                      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << " The seat you entered is taken. Please select another row \n \n";
                        SetConsoleTextAttribute(hConsole, 15);
                    system("pause");
                }

            }else{
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n Error: Invalid Value. Please try again \n\n";
                SetConsoleTextAttribute(hConsole, 15);

                cout << " Would you like to purchase another ticket? [Y/n]  ";
                cin  >> userChoice;
                userChoice = toupper(userChoice);
            }


        }else{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n Error: Invalid Value. Please try again \n\n";
            SetConsoleTextAttribute(hConsole, 15);
            system("pause");
            cin.clear();
            cin.ignore(100, '\n');
        }

    }while(userChoice == 'Y');

}





void printRows(int (&seats)[ROW][COLOUM][SECTION], int (&totalSeatsAvailable)){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int setRowNumberToPrint = 30,
    printRowNumber = 1,
    coloumCounter  = 0,  // Keeps track of the 10 column that are split into three sections. Using this instead of const COLOUM
    sectionCounter = 0;


    system("cls");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n"<< setw(28) << "Section\n";
    SetConsoleTextAttribute(hConsole, 15);

    cout << setw(9) << "1" << setw(10) << "2" << setw(11) << "3\n"
    << setw(9) << "|" << setw(10) << "|" << setw(11) <<"|\n";

    SetConsoleTextAttribute(hConsole, 10);
    cout<< " Seats"<< setw(33);
    SetConsoleTextAttribute(hConsole, 15);
    cout << "123456789012345678901234567890\n";


    for(int rowNumber = 0; rowNumber < 15; rowNumber++){

        if(setRowNumberToPrint == 30){ //Prints Row number after it has gone through the first row containing 30 elements

            cout << " Row " << printRowNumber << "\t";
            setRowNumberToPrint = 0;
            printRowNumber +=1;

        }


        for(int loopThroughColoums = 0; loopThroughColoums < 30; loopThroughColoums++){  // Keeps track of how many total coloumns the program has gone through.

            setRowNumberToPrint += 1;


            if(seats[rowNumber][coloumCounter][sectionCounter] == 0){
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "*";
                    SetConsoleTextAttribute(hConsole, 15);


            }else{
                cout << "#";
                totalSeatsAvailable += 1;
            }
            coloumCounter +=1;


            if(coloumCounter == 10){   // Resets value to 10 because the array is divided into three section with 10 coloum.
                coloumCounter = 0;
                sectionCounter+=1;

            }else{
                continue;
            }

        }


        cout << "\n";
        sectionCounter = 0; // Makes sure the section counter stay under 3

    }
    cout << "\n";
}


// Uses the same algorithm as the printorws to check for available seats.

void checkRowSeatsAvailability(int (&seats)[ROW][COLOUM][SECTION], int (&totalSeatsAvailable)){

    int coloumCounter  = 0,  // Keeps track of the 10 coloums that are split into three sections. Using this instead of const COLOUM
    sectionCounter = 0,
    checkAvailRow  = 0,
    availableSeats = 0;

    printRows(seats,totalSeatsAvailable);
    cout << "\n\n Enter a row number to check how many seats are available:  ";
    cin  >> checkAvailRow;

    while (checkAvailRow < 0 || checkAvailRow > ROW){
        cout << " Please enter a valid answer";
        cout << " Enter a row number to check how many seats are available:   ";
        cin  >> checkAvailRow;

    }
    checkAvailRow -= 1;

    for(int numberOfColoumInRow = 0; numberOfColoumInRow < 30; numberOfColoumInRow++){

        if(seats[checkAvailRow][coloumCounter][sectionCounter] == 1){
            availableSeats += 1;
        }

        coloumCounter +=1;

        if(coloumCounter == 10){
            coloumCounter = 0;

            if(sectionCounter < 2){
                sectionCounter+=1;
            }
        }
    }

    cout << "\n\n There are " << (availableSeats) << " seats avilable in row " << checkAvailRow + 1 << "\n";

}

// save row prices
void saveRowPrice(double (&seatPrice)[15]){

    int arraySize = 15;
    string fileName;

    cout << "\n Enter a name to save the file under: ";
    cin  >> fileName;
    fileName += ".txt";

    ofstream fileOne;
    fileOne.open(fileName.c_str());

    for(int i = 0; i < arraySize; i++){

        fileOne << seatPrice[i] << "\n";
    }

    fileOne.close();

}


void loadRowPrice(double (&seatPrice)[15]){

    int arraySize = 15;
    int count = 0; // goes through the items in the array
    string fileName,
    fullPath;


    // Opens the file based on the name that the user gave
    cout << "\n Enter the name of the file: ";
    cin  >> fileName;
    fileName += ".txt";

    ifstream fileOne;
    fileOne.open(fileName.c_str());

    // if the fail does not exist it tells the user to enter another name
    while (fileOne.fail()){
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << " The file does not exists.\n";
            SetConsoleTextAttribute(hConsole, 15);

            cout << "\n Enter the name of the file: ";
            cin  >> fileName;
            fileName += ".txt";

            fileOne.open(fileName.c_str());

    }

    while(count < arraySize && fileOne >> seatPrice[count] ){
        count++;
    }

    fileOne.close();
}



// load seating chart file. uses the same algorithm as the print rows to transfer the information. Also checks to make sure file exist
void loadSeatChart(int (&seats)[ROW][COLOUM][SECTION], double (&seatPrice)[15], double (&totalTicketPrice),int (&totalSeatsAvailable)){

      int coloumCounter  = 0,
      sectionCounter = 0;
    char userChoice = 'a';

    string fileName,
            fullPath;


    cout << '\n' << setw(40) << "Seating Chart Configuration\n\n";
    do{

         cout << " Would you like to load a saved seating chart [Y/n] ";
        cin  >> userChoice;
        userChoice = toupper(userChoice);

        if (userChoice == 'Y'){
            system("cls");
            cout << '\n' << setw(40) << "Seating Chart Configuration\n\n";
            cout << "\n Enter the name of the file: ";
            cin  >> fileName;
            fileName += ".txt";

            ifstream fileOne;
            fileOne.open(fileName.c_str());

            while (fileOne.fail()){

                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                cout << " The file does not exists.\n";
                SetConsoleTextAttribute(hConsole, 15);

                cout << "\n Enter the name of the file: ";
                cin  >> fileName;
                fileName += ".txt";

            fileOne.open(fileName.c_str());
            }


                for(int rowNumber = 0; rowNumber < 15; rowNumber++){


                    for(int loopThroughColoums = 0; loopThroughColoums < 30; loopThroughColoums++){

                        fileOne >> seats[rowNumber][coloumCounter][sectionCounter];
                        coloumCounter +=1;


                        if(coloumCounter == 10){
                            coloumCounter = 0;
                            sectionCounter+=1;

                        }else{
                            continue;
                        }

                    }


                    sectionCounter = 0;

                }
                fileOne.close();


        }else if(userChoice == 'N'){
           // cout << "Would you like to "
            setDefaultChartValue(seats);
        }else{
             HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cin.clear();
            cin.ignore(100, '\n');
            system("cls");
            cout << " Seating Chart Configuration";
            cout << " Please enter a valid choice \n\n";
            SetConsoleTextAttribute(hConsole, 15);
        }


    }while(userChoice != 'Y' && userChoice != 'N' );


    totalTicketFile(seats, totalSeatsAvailable, seatPrice, totalTicketPrice);
}

// uses same algorithm as the print rows to go through the rows and save the seating chart
void saveSeatChart(int (&seats)[ROW][COLOUM][SECTION]){

    int coloumCounter  = 0,
    sectionCounter = 0;

    string fileName,
    fullPath;

    cout << "\n Enter a name to save the file under: ";
    cin  >> fileName;
    fileName += ".txt";

    ofstream fileOne;
    fileOne.open(fileName.c_str());

    for(int rowNumber = 0; rowNumber < 15; rowNumber++){


        for(int loopThroughColoums = 0; loopThroughColoums < 30; loopThroughColoums++){

            if(seats[rowNumber][coloumCounter][sectionCounter] == 0){
                fileOne << 0;
                fileOne << '\n';
            }else{
                fileOne << 1;
                fileOne << '\n';

            }
            coloumCounter +=1;


            if(coloumCounter == 10){
                coloumCounter = 0;
                sectionCounter+=1;

            }else{
                continue;
            }

        }

        sectionCounter = 0;

    }

    fileOne.close();
}

//When a user decides to load a seating chart this updates the total ticket sale based on the loaded seating chart
void totalTicketFile(int (&seats)[ROW][COLOUM][SECTION], int (&totalSeatsAvailable), double (&seatPrice)[15], double (&totalTicketPrice)){


    int
    coloumCounter  = 0,  // Keeps track of the 10 coloums that are split into three sections. Using this instead of const COLOUM
    sectionCounter = 0;



    for(int rowNumber = 0; rowNumber < 15; rowNumber++){


        for(int loopThroughColoums = 0; loopThroughColoums < 30; loopThroughColoums++){  // Keeps track of how many total coloumns the program has gone through.



            if(seats[rowNumber][coloumCounter][sectionCounter] == 0){
                totalTicketPrice += seatPrice[rowNumber];
            }else{


            }
            coloumCounter +=1;


            if(coloumCounter == 10){   // Resets value to 10 because the array is divided into three section with 10 coloumns.
                coloumCounter = 0;
                sectionCounter+=1;

            }else{
                continue;
            }

        }

        sectionCounter = 0; // Makes sure the section counter stay under 3

    }
}
void bulkPricePurchase(double (&seatPrice)[15]){

    int startingRow = 0,
        endRow,
        price;

    char choice;

    bool leave = false;



    do{
            system("cls");
            cout << '\n' << setw(45) << "Row Price Configuration\n";
            cout << '\n' << setw(40) << "Bulk Row Price\n\n";

        cout << " Enter a starting row: ";
        cin  >> startingRow;

        cout << " \n Enter an ending row: ";
        cin >> endRow;

         cout << " \n Enter a price for rows " << startingRow << " - " << endRow << " : ";
         cin >> price;


        if(startingRow < endRow){
                if(startingRow > 0 && startingRow < 15 && endRow > 0 && endRow <= 15 && price > 0){

            for(startingRow; startingRow < endRow + 1; startingRow++){
                seatPrice[startingRow - 1] = price;
            }

        }else{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            cin.clear();
            cin.ignore(100, '\n');
            system("cls");
            cout << '\n' << setw(45) << "Row Price Configuration\n";
            cout << '\n' << setw(40) << "Bulk Row Price\n\n";
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n Error: Invalid Value. Please try again \n\n";
            SetConsoleTextAttribute(hConsole, 15);
        }

        }else{
                cin.clear();
                cin.ignore(100, '\n');
                cout << "\n Starting row needs to be a number less than ending row\n";
        }


        cout << " Would you like to enter another value [Y/n] ";
        cin >> choice;

        choice = toupper(choice);

        if(choice == 'N'){
            leave = true;
        }else{
            continue;
        }

    }while(leave == false);
}
// takes a char then checks to see if it's the end of the char.
// If it's not it will keep looping. the 300000 is the time delay
void text_animation(char a[100]){

    int i; double k;
    for(i=0; a[i]!='\0'; ++i){
        for(k=0;k<3000000;++k);
        cout <<a[i];
    }


}
