#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <math.h>

using namespace std;
void* sifter(void* threadID); // takes user input; message must be valid
void* fence(void* strFence); //part 1
void* hill(void* strHill); // part 2
void* pinnacle(void* strPinnacle); // part 3

void* fence(void* strFence) {

    string* conversion = static_cast<string*> (strFence);
    string fenceMsg = *conversion;
    int size = 0, dup = 0, zero = 0, max = 0;
    string fencePrefix, fenceMessage;
    cout << "\n";

    //cout << "String passed to fence: " << fenceMsg << endl;

    ////////////////////////////////////////////////////////////////////////////
    //VARIABLES FOR TESTING PURPOSES ONLY
    ////////////////////////////////////////////////////////////////////////////
    string valid = "4312567ttnaAptMTSUOaodwcolXknlypETZ";
    string invalid = "invalid";
    string invalid1 = "4312375asdjlasjasdkjdskjljadskllkjskjlds9a";
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    //FOR FINAL TESTING SET message = fenceMessage
    ////////////////////////////////////////////////////////////////////////////
    //string message = invalid;
    string message = fenceMsg;
    ////////////////////////////////////////////////////////////////////////////

    //Find size of the fencePrefix and the maximum number within this substring
    for (int i = 0; i < message.length(); i++) {
        if (isdigit(message.at(i))) {
            size++;
            if (!isdigit(message.at(i + 1))) {
                break;
            }
        }
    }

    //Split the strings up into the integer string and character string
    fencePrefix = message.substr(0, size);
    fenceMessage = message.substr(size, message.length());

    //If message does not contain at least 28 characters then pad it with space
    if (fenceMessage.length() < 28) {
        fenceMessage.append(28 - fenceMessage.length(), ' ');
    }

    //Convert all chars to uppercase
    transform(fenceMessage.begin(), fenceMessage.end(), fenceMessage.begin(), ::toupper);

    if (size != 0) {
        //Check to see if the fence prefix contains duplicates
        for (int i = 0; i < fencePrefix.length() - 1; i++) {
            for (int j = i + 1; j < fencePrefix.length(); j++) {
                if (fencePrefix.at(i) == fencePrefix.at(j)) {
                    dup++;
                }
            }
        }

        //Check to see if the prefix contains a zero
        for (int i = 0; i < fencePrefix.length(); i++) {
            if ((int) fencePrefix.at(i) - 48 == 0) {
                zero++;
            }
        }

        //Find the maximum value and make sure all numbers are present
        for (int i = 0; i < size; i++) {
            if ((int) message.at(i) - 48 > max) {
                max = (int) message.at(i) - 48;
            }
        }
    }

    //Decrypt message if there are no errors
    if (size == 0) {
        cout << "Error: No integers" << endl;
    } else if (dup > 0) {
        cout << "Error type 2. Contains duplicate integers" << endl;
    } else if (zero > 0) {
        cout << "Error type 3: Contains zero" << endl;
    } else if (max != size) {
        cout << "Error type 4: improper number of integers" << endl;
    } else {
        //cout << "EXECUTE ENCRYPTION" << endl;

        //Decryption execution and printing to console
        int strLen = fenceMessage.length();
        int cols = fencePrefix.length();
        int rows = (strLen / cols);
        int k = 0;

        char fence0[rows][cols];
        char fence1[rows][cols];

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                fence0[j][i] = fenceMessage[k];
                fence1[j][i] = fenceMessage[k];
                k++;
            }
        }
        //Pre-column swap matrix
        //        for (int i = 0; i < rows; ++i) {
        //            for (int j = 0; j < cols; ++j) {
        //                //cout << fence0[i][j] << ' ';
        //            }
        //            cout << endl;
        //        }

        //Swap the columns for the final step in the decryption
        for (int i = 0; i < cols; i++) {
            int currentCol = ((int) fencePrefix.at(i)) - 48;
            for (int j = 0; j < rows; j++) {
                fence0[j][i] = fence1[j][currentCol - 1];
            }
        }
        //cout << "\n";

        //Post-column swapped matrix
        //        for (int i = 0; i < rows; ++i) {
        //            for (int j = 0; j < cols; ++j) {
        //                cout << fence0[i][j] << ' ';
        //            }
        //            cout << endl;
        //        }

        //Print the decrypted message to the console
        cout << "Decrypted Message:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << fence0[i][j] << ' ';
            }
        }
    }
    cout << "\n";
    return 0;
}

void* hill(void* strHill) {
    string* conversion = static_cast<string*> (strHill);
    string hillMsg = *conversion;

    //cout << "String passed to hill: " << hillMsg << endl;

    ////////////////////////////////////////////////////////////////////////////
    //VARIABLES FOR TESTING PURPOSES ONLY
    ////////////////////////////////////////////////////////////////////////////
    string test = "ACDUJf 1 5 6 12";
    string valid = "PQLG 4 3 2 7";
    string valid1 = "abcd 4 3 2 7";
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    //IN ACTUAL PROGRAM FOR REAL TESTING SET strInts and strChars = hillMsg
    ////////////////////////////////////////////////////////////////////////////
    //string strChars = valid;
    //string strInts = valid;
    string strChars = hillMsg;
    string strInts = hillMsg;
    ////////////////////////////////////////////////////////////////////////////

    string strHillChars;
    int size, msgSize, count = 0, count0 = 0;
    cout << "\n";

    //Convert all chars to uppercase
    transform(strChars.begin(), strChars.end(), strChars.begin(), ::toupper);

    ////////////////////////////////////////////////////////////////////////////
    //                      Integer Operations
    ////////////////////////////////////////////////////////////////////////////

    //Pad the end of the string for integers with a space in case last index 
    //is a multiple digit number
    strInts += ' ';
    int nums[strInts.length()];

    //Checking the array which has the letters removed, collecting the integers 
    //and putting them into another array
    for (int i = 0; i < strInts.length(); i++) {
        if (isdigit(strInts.at(i)) && isdigit(strInts.at(i + 1))) {

            nums[i] = std::atoi(strInts.substr(i, i + 1).c_str());
            strInts.at(i) = 'a';
            strInts.at(i + 1) = 'a';
        } else if (isdigit(strInts.at(i))) {
            nums[i] = std::atoi(strInts.substr(i).c_str());
            strInts.at(i) = 'a';
        } else {
            nums[i] = -1;
        }
    }

    //Find number of integers in the strInts string
    for (int i = 0; i < strInts.length(); i++) {
        if (nums[i] != -1) {
            count0++;
        }
    }

    //New array to hold the integers extracted from the string
    int hillNums[count0];

    //Fill the hill array with the integers. Count used to see if there is the 
    //correct number of integers to continue with decryption
    for (int i = 0; i < strInts.length(); i++) {
        if (nums[i] != -1) {
            hillNums[count] = nums[i];
            count++;
        }
    }

    //Print loop for the integers to check for accuracy
    //        for(int i = 0; i < count; i++){
    //            cout << hillNums[i] << ' ';
    //        }
    //    cout << endl;
    ////////////////////////////////////////////////////////////////////////////
    //         End of integer operations. Begin char operations
    ////////////////////////////////////////////////////////////////////////////


    //Remove whitespace from input string
    std::string::iterator end_pos = std::remove(strChars.begin(), strChars.end(), ' ');
    strChars.erase(end_pos, strChars.end());
    strChars.append(" ");

    //Extract the letters from the strChars string and put them into the strHillChars string
    for (int i = 0; i < strChars.length(); i++) {
        if (!isdigit(strChars.at(i))) {
            msgSize++;
            strHillChars += strChars.at(i);
        }
    }

    //Trim the space out of the letters string that was used earlier 
    std::string::iterator end_posL = std::remove(strHillChars.begin(), strHillChars.end(), ' ');
    strHillChars.erase(end_posL, strHillChars.end());

    ////////////////////////////////////////////////////////////////////////////
    //    End of char operations. Begin testing to see if decryption occurs
    ////////////////////////////////////////////////////////////////////////////

    //If statements to determine if encryption should be executed to see if input is correct. 
    if (count != 4) {
        cout << "Error: incorrect number of integers for section 2" << endl;
    } else if (strHillChars.length() % 2 != 0) {
        cout << "Error: incorrect number of letters for section 1" << endl;
    } else {
        ////////////////////////////////////////////////////////////////////////////
        //                          Begin matrix operations
        ////////////////////////////////////////////////////////////////////////////

        int rowNum = 2, colNum = 2;
        int rowNum0 = 2, colNum0 = 1;
        int k = 0;
        int matS[rowNum][colNum];
        int matC[rowNum0][colNum0];
        int resMatrix[2][1];

        //Add elements to the integer matrix (matrix S)
        for (int row = 0; row < rowNum; row++) {
            for (int col = 0; col < colNum; col++) {
                matS[row][col] = (int) hillNums[k];
                k++;
            }
        }

        //Test output for integer matrix
        //        for (int row = 0; row < rowNum; row++) {
        //            for (int col = 0; col < colNum; col++) {
        //                cout << matS[row][col] << " ";
        //            }
        //            cout << endl;
        //        }
        //        cout << endl;

        //Convert the letters into their appropriate index in the alphabet. 0 indexing used
        int letterToInt[strHillChars.length()];
        for (int i = 0; i < strHillChars.length(); i++) {
            letterToInt[i] = (int) strHillChars.at(i) - 65;
        }

        //Perform matrix multiplication
        int sum = 0, countM = 0, s = 0, b = 0;
        int resStr[strHillChars.length()];

        //Matrix operations
        while (countM < strHillChars.length()) {

            //Fill matrix c (char matrix)
            for (int row = 0; row < rowNum0; row++) {
                for (int col = 0; col < colNum0; col++) {
                    matC[row][col] = letterToInt[s];
                    //cout << letterToInt[s] << endl;
                    s++;
                }
            }

            //Perform matrix multiplication and enter result into result array
            for (int t = 0; t < rowNum; t++) {
                for (int i = 0; i < colNum0; i++) {
                    for (int j = 0; j < rowNum0; j++) {
                        sum = sum + (matS[t][j] * matC[j][i]);
                    }
                    resStr[b] = sum % 26;
                    b++;
                    sum = 0;
                }
            }
            countM++;
            countM++;
        }

        //Print the decrypted message
        cout << "Decrypted Message:" << endl;
        for (int i = 0; i < strHillChars.length(); i++) {
            cout << (char) (resStr[i] + 65) << " ";
        }
        cout << endl;
    }
    return 0;
    pthread_exit(0);
}

void* pinnacle(void* strPinnacle) {
    string* conversion = static_cast<string*> (strPinnacle);
    string pinnMsg = *conversion;

    //cout << "String passed to pinnacle: " << pinnMsg << endl;
    cout << "\n";

    ////////////////////////////////////////////////////////////////////////////
    //VARIABLES FOR TESTING PURPOSES ONLY
    ////////////////////////////////////////////////////////////////////////////
    string valid = "ABCDEF 1 2 3 5 2 1 0 2 4";
    string valid1 = "abcd 4 3 2 7";
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    //IN ACTUAL PROGRAM FOR REAL TESTING SET strInts and strChars = pinnMsg
    ////////////////////////////////////////////////////////////////////////////
    //string strChars = valid;
    //string strInts = valid;
    string strChars = pinnMsg;
    string strInts = pinnMsg;
    ////////////////////////////////////////////////////////////////////////////

    int size, msgSize, count = 0, count0 = 0;
    string strPinChars;

    //Convert all chars to uppercase in the string used for char operations
    transform(strChars.begin(), strChars.end(), strChars.begin(), ::toupper);

    ////////////////////////////////////////////////////////////////////////////
    //                      Integer Operations
    ////////////////////////////////////////////////////////////////////////////

    //Pad the end of the string for integers with a space in case last index 
    //is a multiple digit number
    strInts += ' ';
    int nums[strInts.length()];

    //Checking the array which has the letters removed, collecting the integers 
    //and putting them into another array
    for (int i = 0; i < strInts.length(); i++) {
        if (isdigit(strInts.at(i)) && isdigit(strInts.at(i + 1))) {

            nums[i] = std::atoi(strInts.substr(i, i + 1).c_str());
            strInts.at(i) = 'a';
            strInts.at(i + 1) = 'a';
        } else if (isdigit(strInts.at(i))) {
            nums[i] = std::atoi(strInts.substr(i).c_str());
            strInts.at(i) = 'a';
        } else {
            nums[i] = -1;
        }
    }

    for (int i = 0; i < strInts.length(); i++) {
        //cout << nums[i] << endl;
    }

    //Find number of integers in the strInts string
    for (int i = 0; i < strInts.length(); i++) {
        if (nums[i] != -1) {
            count0++;
        }
    }

    //New array to hold the integers extracted from the string
    int pinNums[count0];

    //Fill the hill array with the integers. Count used to see if there is the 
    //correct number of integers to continue with decryption
    for (int i = 0; i < strInts.length(); i++) {
        if (nums[i] != -1) {
            pinNums[count] = nums[i];
            count++;
        }
    }

    //Print loop for the integers to check for accuracy
    //            for(int i = 0; i < count; i++){
    //                cout << pinNums[i] << ' ';
    //            }
    //        cout << endl;

    ////////////////////////////////////////////////////////////////////////////
    //         End of integer operations. Begin char operations
    ////////////////////////////////////////////////////////////////////////////

    //Remove whitespace from input string
    std::string::iterator end_pos = std::remove(strChars.begin(), strChars.end(), ' ');
    strChars.erase(end_pos, strChars.end());
    strChars.append(" ");

    //Extract the letters from the strChars string and put them into the strPinChars string
    for (int i = 0; i < strChars.length(); i++) {
        if (!isdigit(strChars.at(i))) {
            msgSize++;
            strPinChars += strChars.at(i);
        }
    }

    //Trim the space out of the letters string that was used earlier 
    std::string::iterator end_posL = std::remove(strPinChars.begin(), strPinChars.end(), ' ');
    strPinChars.erase(end_posL, strPinChars.end());

    ////////////////////////////////////////////////////////////////////////////
    //    End of char operations. Begin testing to see if decryption occurs
    ////////////////////////////////////////////////////////////////////////////

    //If statements to determine if encryption should be executed to see if input is correct. 
    if (count != 9) {
        cout << "Error: incorrect number of integers for section 2" << endl;
    } else if (strPinChars.length() % 3 != 0) {
        cout << "Error: incorrect number of letters for section 1" << endl;
    } else {

        ////////////////////////////////////////////////////////////////////////////
        //                          Begin matrix operations
        ////////////////////////////////////////////////////////////////////////////

        int rowNum = 3, colNum = 3;
        int rowNum0 = 3, colNum0 = 1;
        int k = 0;
        int matS[rowNum][colNum];
        int matC[rowNum0][colNum0];
        int resMatrix[3][1];

        //Add elements to the integer matrix (matrix S)
        for (int row = 0; row < rowNum; row++) {
            for (int col = 0; col < colNum; col++) {
                matS[row][col] = (int) pinNums[k];
                k++;
            }
        }

        //Test output for integer matrix
        //        for (int row = 0; row < rowNum; row++) {
        //            for (int col = 0; col < colNum; col++) {
        //                cout << matS[row][col] << " ";
        //            }
        //            cout << endl;
        //        }
        //        cout << endl;

        //Convert the letters into their appropriate index in the alphabet. 0 indexing used
        int letterToInt[strPinChars.length()];
        for (int i = 0; i < strPinChars.length(); i++) {
            letterToInt[i] = (int) strPinChars.at(i) - 65;
        }

        //Perform matrix multiplication
        int sum = 0, countM = 0, s = 0, b = 0;
        int resStr[strPinChars.length()];

        while (countM < strPinChars.length()) {

            //Fill matrix c (char matrix)
            for (int row = 0; row < rowNum0; row++) {
                for (int col = 0; col < colNum0; col++) {
                    matC[row][col] = letterToInt[s];
                    s++;
                }
            }

            //Perform matrix multiplication and enter result into result array
            for (int t = 0; t < rowNum; t++) {
                for (int i = 0; i < colNum0; i++) {
                    for (int j = 0; j < rowNum0; j++) {
                        sum = sum + (matS[t][j] * matC[j][i]);
                    }
                    resStr[b] = sum % 26;
                    b++;
                    sum = 0;
                }
            }
            countM++;
            countM++;
        }
        //Print the decrypted message
        cout << "Decrypted Message:" << endl;
        for (int i = 0; i < strPinChars.length(); i++) {
            cout << (char) (resStr[i] + 65) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    return 0;
    pthread_exit(0);
}

void *sifter(void* arg) {

    string message, strFence, strHill, strPinnacle, temp;
    string ast1 = "*";
    string ast2 = "**";
    string ast3 = "***";

    bool b1, b2, b3, b4;
    int count = 0, num1, num2, num3;

    //cout << "In sifter Thread ID, " << tid << endl;



    while (count < 3) {

        message.clear();
        temp.clear();
        cout << "Enter message: " << endl;
        getline(cin, message);
        cout << endl;

        //Copy message into temporary string for checking to see if it is a valid message
        temp = message;

        if (message == "exit") {
            cout << "Exit word entered. Program terminating" << endl;
            std::exit(0);
        }


        //Three asterisks
        if (temp.find(ast3) <= temp.length()) {
            b3 = true;

            num3 = temp.find(ast3);

            temp[num3] = 'a';
            temp[num3 + 1] = 'a';
            temp[num3 + 2] = 'a';
        }

        //Two asterisks
        if (temp.find(ast2) <= temp.length()) {
            b2 = true;

            num2 = temp.find(ast2);

            temp[num2] = 'a';
            temp[num2 + 1] = 'a';
        }

        //One asterisk
        if (temp.find(ast1) <= temp.length()) {
            //b1 = true;
            num1 = temp.find(ast1);
            temp[num1] = 'a';

            if (temp.find(ast1) <= temp.length()) {
                b1 = false;
            } else {
                b1 = true;
                temp[num1] = 'a';
            }
        }

        //Create a string so that the white space can be removed
        string temp1 = temp;

        //Remove whitespace from temp1 string
        std::string::iterator end_pos = std::remove(temp1.begin(), temp1.end(), ' ');
        temp1.erase(end_pos, temp1.end());
        temp1.append(" ");

        //For message to be valid it must at least be 
        if (temp1.length() < 26) {
            b4 = false;
        } else {
            b4 = true;
        }
        
        if (b1 && b2 && b3 && b4) {
            count = 0;
            //cout << "executing decryption" << endl;

            //Fence substring (1 asterisk)
            if (num3 > num1 && num2 > num3) {
                strFence = message.substr(num1 + 1, (num3 - num1) - 1);
            } else if (num2 > num1 && num3 > num2) {
                strFence = message.substr(num1 + 1, (num2 - num1) - 1);
            } else if (num1 > num2 && num3 > num1) {
                strFence = message.substr(num1 + 1, (num3 - num1) - 1);
            } else if (num1 > num3 && num2 > num1) {
                strFence = message.substr(num1 + 1, (num2 - num1) - 1);
            } else {
                strFence = message.substr(num1 + 1, message.length() - 1);
            }

            //Hill substring (2 asterisks)
            if (num3 > num2 && num1 > num3) {
                strHill = message.substr(num2 + 2, (num3 - num2) - 2);
            } else if (num1 > num2 && num3 > num1) {
                strHill = message.substr(num2 + 2, (num1 - num2) - 2);
            } else if (num2 > num3 && num1 > num2) {
                strHill = message.substr(num2 + 2, (num1 - num2) - 2);
            } else if (num2 > num1 && num3 > num2) {
                strHill = message.substr(num2 + 2, (num3 - num2) - 2);
            } else {
                strHill = message.substr(num2 + 2, message.length() - 1);
            }

            //Pinnacle substring (3 asterisks)
            if (num3 > num1 && num2 > num3) {
                strPinnacle = message.substr(num3 + 3, (num2 - num3) - 3);
            } else if (num3 > num2 && num1 > num3) {
                strPinnacle = message.substr(num3 + 3, (num1 - num3) - 3);
            } else if (num1 > num3 && num2 > num1) {
                strPinnacle = message.substr(num3 + 3, (num1 - num3) - 3);
            } else if (num2 > num3 && num1 > num2) {
                strPinnacle = message.substr(num3 + 3, (num2 - num3) - 3);
            } else {
                strPinnacle = message.substr(num3 + 3, message.length() - 1);
            }

            pthread_t fenceT, hillT, pinnacleT;
            //Create fence thread
            int res0 = pthread_create(&fenceT, NULL, fence, &strFence);
            if (res0) {
                cout << "Error -- pthread create return code: " << res0 << endl;
                exit(EXIT_FAILURE);
            }
            pthread_join(fenceT, NULL);
            
            //cout << "Fence thread status: " << res0 << endl;

            //Create hill thread
            int res1 = pthread_create(&hillT, NULL, hill, &strHill);
            if (res1) {
                cout << "Error for creating hill thread -- error return code: " << res1 << endl;
                exit(EXIT_FAILURE);
            }
            pthread_join(hillT, NULL);
            
            //cout << "Hill thread status: " << res1 << endl;

            //Create pinnacle thread
            int res2 = pthread_create(&pinnacleT, NULL, pinnacle, &strPinnacle);
            if (res2) {
                cout << "Error for creating pinnacle thread -- error return code: " << res2 << endl;
                exit(EXIT_FAILURE);
            }
            pthread_join(pinnacleT, NULL);
            
            //cout << "Pinnacle thread status: " << res2 << endl;

        } else {
            count++;
            if (count < 3) {
                cout << "Error: Invalid code. " << 2 - count << " more chances." << endl;
            } else {
                cout << "Error: Number of tries exceeded. Program terminated." << endl;
            }
        }
    }
    return 0;
    pthread_exit(0);
}

int main() {
    //Create first thread
    pthread_t start;
    int arg = 0;
    int t = pthread_create(&start, NULL, sifter, (void*)arg);
    pthread_join(start, NULL);


    cout << endl;
}
