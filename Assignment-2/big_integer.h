

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include<string>


class big_integer 
{
    private: 
        std::string integer;
	static std::string add_two_strings(std::string left, std::string right);
	static std::string multiply_two_strings(std::string number, std::string multiplier);
	static std::string subtract_two_strings (std::string left, std::string right);
	static std::string divide_two_strings(std::string dividend, std::string divisor);
	static std::string mod_two_strings (std::string dividend, std::string divisor);

    public: 
        big_integer();
        big_integer(std::string larg_int);
        big_integer(const big_integer &big_int_2);
        std::string get_value() const;

        big_integer & operator= (const big_integer & rhs);
        const big_integer operator+ (const big_integer & rhs);
        const big_integer operator- (const big_integer & rhs);
        const big_integer operator* (const big_integer & rhs);
        const big_integer operator/ (const big_integer & rhs);
        const big_integer operator% (const big_integer & rhs);
	
        static bool is_bigger(std::string a, std::string b);
};


#endif
