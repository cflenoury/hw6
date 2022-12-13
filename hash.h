#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cstring>
#include <cmath>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      //Create array for big ints
			unsigned long long w[] = {0, 0, 0, 0, 0};

			int wi = 4;//index in 'w'
			int ti = 0;//tracks digits in base 36 number (what power to rasie each number to convert to base 10)
			unsigned long long temp_sum = 0;

			for(int i = k.length()-1; i >= 0 ; i--){//start at the back of input string
				//convert letter to number
				unsigned long long temp_num = letterDigitToNumber( k[i] );

				//raise converted value to a "ti" power of 36 and
				//Add result to "temp_sum"
				temp_sum += pow(36, ti) * temp_num;			

				//Increment ti
				ti++;

				if (ti == 6){
					//std::cout << "Reseting ti\n";
					//reset ti to 0
					ti = 0;

					//place the sum in "wi" of "w" array
					w[wi] = temp_sum;

					//increment "wi"
					//std::cout << "wi is now " << wi << std::endl;
					wi--;

					//reset temp_sum to 0
					temp_sum = 0;
				}
				

			}//by the end of this loop, temp_sum will either be 0 or the value of the first few letters
			//(from left to right) after being converted to base 36 summed together to form base a base 10
			//int

			/*Cases to think about

			- When all w[] locations have been filled
			- When temp sum still has something in it

			*/

			if(temp_sum){//If temp sum is not 0
				//std::cout << "Placing left overs in w array\n";
				//place it properly in the big int array 'w'
				w[wi] = temp_sum;
			}

			temp_sum =0;
			
			//Produce final value with random values
			for(int i = 0; i < 5; i++){
				//std::cout << "w[" <<i << "] = " << w[i] << std::endl;
				temp_sum += rValues[i]*w[i];
			}

			return temp_sum;
			
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
			//char temp = letter;			
			
			//Cast input to integer
			int let = letter;

			//For alphabet letters
			if(let < 123 && let > 96){
				return letter - 97;
			}

			//Convert letter to lower case
			if(let >= 65 && let <= 90){
				return letter - 65;
			}

			//For integers
			if(let > 47 && let < 58){
				return letter - 22;
			}

			std::cerr << "Invlaid input\n";
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
