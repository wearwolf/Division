#include <iostream>
#include <string>
#include <cmath>

using namespace std;
const int MAXDEC = 65;
const int NOPRINT = -1;
const int DECPRINT = -2;
const int NOPRINT2 = -3;

int getDigits(int number);
int getNextDigit(int &number);


int main (void) {	
		string tempInput;
		bool replay = true;

		//Loop until user quits
		while(replay) {
			//input
			int dividend;
			int divisor;

			//Digit counts
			int endDigits;
			int sorDigits;

			//The list of current values
			int curList[MAXDEC+1];
			//The list of calculated multiplied values
			int mulList[MAXDEC+1];
			//The list of digits making up the result
			int output[MAXDEC+1];

			int endCopy = 0;
			int remain = 0;
			int current = 0;
			int space = 0;
			int base = 4;

			//Flags
			bool input = false;
			bool start = false;
			replay = false;

			cout << "Format: A / B = C" << endl;
			cout << "A and B must be less than 100000000" << endl;
			cout << "A and B must be greater than 0" << endl;

			//Get the dividend from input
			while(!input) {
				input = true;
				cout << "Please enter a number for A:" << endl;

				//Get the input and convert it to an int
				cin >> tempInput;
				dividend = atoi(tempInput.c_str());

				//check if dividend is in correct range
				if (dividend <= 0 || dividend >= 100000000) {
					input = false;
					cout << "Invalid A:" << endl;
				}
			}
			input = false;

			//Get the divisor from input
			while(!input) {
				input = true;
				cout << "Please enter a number for B:" << endl;

				//Get the input and convert it to an int
				cin >> tempInput;
				divisor = atoi(tempInput.c_str());

				//check if divisor is in correct range
				if (divisor <= 0 || divisor >= 100000000) {
					input = false;
					cout << "Invalid B:" << endl;
				}
			}
			input = false;

			//Get the count of the digits in both numbers and make a copy of the dividend
			endDigits = getDigits(dividend);
			sorDigits = getDigits(divisor);
			endCopy = dividend;

			//Clear the lists
			for (int j = 0 ; j < MAXDEC + 1 ; j++) {
				output[j] = NOPRINT;
				curList[j] = NOPRINT;
				mulList[j] = NOPRINT;
			}


			//Loop through all the digits of the number
			for (int i = 0; i < endDigits ; i ++) {
				//Get the new value by adding the remainder and the next digit
				current = remain * 10 + getNextDigit(endCopy);


				for (int j = 0; j < 10; j++) {

					//Find the value for j such that j + 1 multiplied by the divisor is greater than the current value
					if ((j + 1) * divisor > current) {

						//if j = 0 and we haven't started printing then tell it to print nothing
						if (j == 0 && start == false) {
							output[i] = NOPRINT;
							curList[i] = NOPRINT;
							mulList[i] = NOPRINT;
						} else { 
							if (start == false) { //If j != 0 and not started printing, start
								start = true;
								curList[i] = NOPRINT2;
							}
							else {				//If this isn't the first line, add current to the list
								curList[i] = current;
							}
							//Determine the results and add them to their perspective lists
							mulList[i] = j * divisor;
							output[i] = j;
						}
						//Determine next remainder
						remain = current - j * divisor;
						break;
					}
				}
			}


			if (start == false) { //If still haven't started, set previous output to 0
				start = true;
				output[endDigits-1] = 0;
			}
			
			//Mark the decimal point
			output[endDigits] = DECPRINT;
			curList[endDigits] = DECPRINT;
			mulList[endDigits] = DECPRINT;

			//Loop through the decimal digits until maxDec or result is 0
			for (int i = endDigits + 1 ; i <= MAXDEC ; i ++) {
				//Get the new value from the remainder
				current = remain * 10;


				for (int j = 0; j < 10; j++) {
					//Find the value for j such that j + 1 multiplied by the divisor is greater than the current value
					if ((j + 1) * divisor > current) {
						//Add current to the list
						curList[i] = current;
						//Determine the results and add them to their perspective lists
						mulList[i] = j * divisor;
						output[i] = j;
						remain = current - j * divisor;
						break;
					}
				}
				if(remain == 0) { //If the remainder is 0, set the rest of the output to not print and stop

					break;
				}
			}

			cout << endl;
		
			//Spacer for the divisor
			for(int i = 0; i < sorDigits + 3; i++) {
				cout << " ";
			}

			//Print the resulting value
			for (int i = 0; i < MAXDEC ; i++) {
				if (output[i] == NOPRINT)
					cout << " ";
				else if (output[i] == DECPRINT)
					cout << ".";
				else
					cout << output[i];
			}
			cout << endl;

			//Print out the operation
			cout << divisor << " / " << dividend << endl;
	
			//Print out the process
			for (int i = 0; i < MAXDEC ; i++) {
				if(curList[i] == NOPRINT) {	//If current number is no print, skip
					continue;
				}
				if (curList[i] == DECPRINT) { //If current number is decimal, move the base back one
					base = base - 1;
					continue;
				}

				//print the current value
				if (curList[i] != NOPRINT2) {		
					space = sorDigits + i - getDigits(curList[i]) + base;
					for (int j = 0 ; j < space ; j++) {
						cout << " ";
					}
					cout << curList[i] << endl;
				}

				//Print the multiplied value
				space = sorDigits + i - getDigits(mulList[i]) + base;
				for (int j = 0 ; j < space ; j++) {
					cout << " ";
				}
				cout << mulList[i] << endl;
			}

				cout << endl;
				cout << "Do you want to divide another number? (Y/N): ";

				//Get the input
				cin >> tempInput;

				//check if string starts with y or Y
				if (tempInput[0] == 'y' || tempInput[0] == 'Y') {
					replay = true;
				}
		}

	return 0;
	}

	// Get the number of digits in the number
	int getDigits(int number) {
		for(int i = 1; i <= 8 ; i++) {
			//Multiply the number by 0.1 and then truncate by casting to an int
			number = (int)(number * 0.1);
			//Repeat util the number has ran out of digits
			if( number == 0) {
				//Return i which will be the number of digits
				return i;
			}		
		}
		return 0;
	}

	//returns the left most digit
	int getNextDigit(int &number) {
		//Get the number of digits in the number
		int dig = getDigits(number);

		//Power and inverse power
		int power = 1;
		double invPower = 1;

		//Loop through the number of digits to get the values
		for (int i = 0 ; i < dig - 1 ; i++) {
			power = power * 10;
			invPower = invPower * 0.1;
		}

		//Get the last digit
		int last = (int)(number * invPower);

		//Remove the last digit from the number
		number = number - (power * last);
		return last;
	}