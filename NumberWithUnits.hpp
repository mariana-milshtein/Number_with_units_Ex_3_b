#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>

namespace ariel {
};
    class NumberWithUnits {
    private:
        static std::map<std::string,std::map<std::string, double>> units;
        static constexpr double eps = 0.000001;
        double amount;
        std::string unit;
        
    public:
        static void read_units(std::ifstream&);
        NumberWithUnits(double, std::string);
        ~NumberWithUnits();
        
        NumberWithUnits& operator +=(const NumberWithUnits&);
        NumberWithUnits operator +(const NumberWithUnits&);
        NumberWithUnits operator +();
        NumberWithUnits& operator ++();
        NumberWithUnits operator ++(int);
        NumberWithUnits& operator -=(const NumberWithUnits&);
        NumberWithUnits operator -(const NumberWithUnits&);
        NumberWithUnits operator -();
        NumberWithUnits& operator --();
        NumberWithUnits operator --(int);
        
        bool operator <(const NumberWithUnits&) const;
        bool operator >(const NumberWithUnits&) const;
        bool operator <=(const NumberWithUnits&) const;
        bool operator >=(const NumberWithUnits&) const;
        bool operator ==(const NumberWithUnits&) const;
        bool operator !=(const NumberWithUnits&) const;
        
        friend NumberWithUnits operator*(double,const NumberWithUnits&);
        friend NumberWithUnits operator*(const NumberWithUnits&,double);
        friend std::istream& operator>>(std::istream&, NumberWithUnits&);
        friend std::istream& operator>>(std::istream&, const NumberWithUnits&);
        friend std::ostream& operator<<(std::ostream&, const NumberWithUnits&);
    };    

