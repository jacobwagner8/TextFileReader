#include <iostream>
#include "console.h"
#include "hashmap.h"
#include "tokenscanner.h"
#include <string>
#include <fstream>
#include "filelib.h"
#include "simpio.h"
using namespace std;


void initializeMap(HashMap<int, Vector<string>> &data);
void printOptions();
double findAverage(int column, HashMap<int, Vector<string>> &data);
void printAllAverages(HashMap<int, Vector<string>> &data);
void printVector(Vector<string> curr);
void printSpecificAverage(HashMap<int, Vector<string>> &data);
void printAllKeys(HashMap<int, Vector<string>> &data);
void changeColumnName(HashMap<int, Vector<string>> &data);
void printSpecificColumn(HashMap<int, Vector<string>> &data);

/*
 * This function takes in the map and will ask the user
 * what column it is that they would like to see. It then gives
 * a little output about what is happening and then it calls
 * printVector to print out the data.
 */
void printSpecificColumn(HashMap<int, Vector<string>> &data) {

    int specificColumn = getInteger("Enter the column to view: ");

    cout << "Column " << specificColumn << " looks like:" << endl;
    printVector(data.get(specificColumn));
}

/*
 * This function takes in the hashmap and asks the user which
 * column it is that they would like to change the name of.
 * It then gets the data stored in the old column name, removes
 * the old column and then adds the data back to the hashmap
 * under the new column name.
 */
//NEED TO CHANGE SO THAT NAME CAN BE A STRING
void changeColumnName(HashMap<int, Vector<string>> &data) {

    int specificColumn = getInteger("Enter the column name you would like to change: ");

    Vector<string> temp = data.get(specificColumn);
    data.remove(specificColumn);

    int newName = getInteger("Enter the new name: ");
    data.add(newName, temp);
}

/*
 * Takes in the hashmap and prints all of the "keys" which
 * are also known as the columns of the dataset
 */
void printAllKeys(HashMap<int, Vector<string>> &data) {

    for (int curr : data) {
        cout << curr << endl;
    }
}

/*
 * This function takes in the hashmap and questions the client
 * which column they would like to find the average of. Then
 * it will take that column and call the findAverage function.
 * Once the average is returned from the function it will print
 * out what the average was found to be
 */
void printSpecificAverage(HashMap<int, Vector<string>> &data) {

    int specificColumn = getInteger("Enter column to find average: ");

    double result = findAverage(specificColumn, data);

    cout << "The average of " << specificColumn << " is:" << endl;
    cout << result << endl;
}

/*
 * This function takes in a specific Vector that is from the
 * hashmap and it will walk through the full vector and print
 * each element of the Vector.
 */
void printVector(Vector<string> curr) {

    string result;

    for (string tmp : curr) {
        result += (" " + tmp);
    }

    cout << result << endl;
}

/*
 * This function takes in the hashmap and iterates over
 * each key in the map to find its average, which it will then
 * print to the standard output.
 */
void printAllAverages(HashMap<int, Vector<string>> &data) {

    for (int curr : data) {
        cout << "Column " << curr << endl;
        double result = findAverage(curr, data);
        cout << "The average is: " << result << endl;
    }
}

/*
 * This function takes in the hashmap and a specific column.
 * It will get the Vector associated with the desired key and
 * then it will iterate over the length of the column, first
 * checking if the entry is a valid real number, and then
 * adding to the total. Once the vector is summed, it will go
 * ahead and make the division for the average.
 */
//CHANGE TO ONLY INCLUDE THE VECTOR NEEDED
double findAverage(int column, HashMap<int, Vector<string>> &data) {

    double sum = 0;

    Vector<string> specificColumn = data.get(column);

    for (int i = 0; i < specificColumn.size(); i++) {

        if (stringIsReal(specificColumn[i])) {
            double curr = stringToReal(specificColumn[i]);
            sum += curr;
        }

    }

    return (sum / specificColumn.size());
}

/*
This function creates the map of the specific columns that
the user want to have captured in the dataset. It starts
by reading in the file and asking for the number of columns
to skip as well as the number of columns to capture.
From there, the function will divide the columns up with a
tokenizer and put them into specific places in the map.
*/
//NEEDS DECOMP
//SKIP THE TOP ROW
void initializeMap(HashMap<int, Vector<string>> &data) {
    TokenScanner scanner;

    string filename = promptUserForFile("Input file name? ");
    ifstream inputFile;
    inputFile.open(filename);

    int columnsSkipped = getInteger("# of columns to skip: ");
    int columnsCaptured = getInteger("# of columns to capture: ");

    for (int column = 0; column < columnsCaptured; column++) {
        Vector<string> temp;
        data.add(column, temp);
    }

    string line;

    while (getline(inputFile, line)) {

        scanner.setInput(line);

        for (int i = 0; i < columnsSkipped; i++) {
            string token = scanner.nextToken();
        }

        for (int j = 0; j < columnsCaptured; j ++) {
            string token = scanner.nextToken();
            Vector<string> currVector = data.get(j);
            currVector.add(token);
            data.put(j, currVector);
        }

    }

}

/*
 * Used during the while loop to print out all of the options
 * that the client has to manipulate the data.
 */
void printOptions() {

    cout << "Enter 0 to quit the application" << endl;
    cout << "Enter 1 to print all averages" << endl;
    cout << "Enter 2 to print the average of a specifc column" << endl;
    cout << "Enter 3 to print out all the keys" << endl;
    cout << "Enter 4 to change the name of a column" << endl;
    cout << "Enter 5 to print out a specific columns data" << endl;
}

/*
 * This program takes in a dataset from the client, divides it
 * into readable columns, and allows for the client to find
 * averages of specific columns. This also makes it much more
 * readable for the human user.
 */
int main() {
    HashMap<int, Vector<string>> data;

    initializeMap(data);

    printOptions();

    int option = getInteger("Select an option: ");

    while (option != 0) {

        if (option == 1) {
            printAllAverages(data);
        } else if (option == 2) {
            printSpecificAverage(data);
        } else if (option == 3) {
            printAllKeys(data);
        } else if (option == 4) {
            changeColumnName(data);
        } else if (option == 5) {
            printSpecificColumn(data);
        } else {
            cout << "Please select a valid option";
        }

        printOptions();
        option = getInteger("Select an option: ");
    }
    return 0;
}
