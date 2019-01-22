

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

class big_integer 
{
    private: 
        std::string integer;

    public: 
        big_integer();
        big_integer(std::string larg_int);
        big_integer(const big_integer &big_int_2);
        ~big_integer();
        std::string get_value() const;

        big_integer & operator= (const big_integer & rhs);
        const big_integer operator+ (const big_integer & rhs);
        const big_integer operator- (const big_integer & rhs);
        const big_integer operator* (const big_integer & rhs);
        const big_integer operator/ (const big_integer & rhs);
        const big_integer operator% (const big_integer & rhs);

        
};


#endif
