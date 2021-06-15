#include "NumberWithUnits.hpp"
#include <sstream>
#include <stdlib.h> 

using namespace ariel;
        
        std::map<std::string,std::map<std::string, double>> NumberWithUnits::units;
        
        void NumberWithUnits::read_units(std::ifstream& file) {
                std::string s, from, to;
                char eq;
                int one;
                double amount;
                if(file.is_open()) {
                        while(getline (file,s)) {
                                std::stringstream ss(s);
                                ss >> one >> from >> eq >> amount >> to;
                                for(auto i = NumberWithUnits::units[to].begin(); i != NumberWithUnits::units[to].end(); i++) {
                                        NumberWithUnits::units[from][i->first] = amount*i->second;
                                        NumberWithUnits::units[i->first][from] = 1/(amount*i->second);
                                }
                                for(auto i = NumberWithUnits::units[from].begin(); i != NumberWithUnits::units[from].end(); i++) {
                                        NumberWithUnits::units[to][i->first] = (1/amount)*i->second;
                                        NumberWithUnits::units[i->first][to] = 1/((1/amount)*i->second);
                                }
                                NumberWithUnits::units[from][to] = amount;
                                NumberWithUnits::units[to][from] = 1/amount;
                                NumberWithUnits::units[from][from] = 1;
                                NumberWithUnits::units[to][to] = 1;
                        }        
                }
                // for (auto it=NumberWithUnits::units.begin(); it!=NumberWithUnits::units.end(); ++it) {
                //         std::cout << it->first << " = ";
                //         for (auto it2=it->second.begin(); it2!=it->second.end(); ++it2) {  
                //                  std::cout << "[" << it2->second << " " << it2->first << "] = ";
                //         }
                //         std::cout << std::endl;
                // }
                file.close();
        }
        NumberWithUnits::NumberWithUnits(double amount, std::string unit) {
                if(units.find(unit) != units.end()) {
                        this->amount = amount;
                        this->unit = unit;
                }       
                else {
                        throw std::logic_error("This unit is not exists!");
                }
        }
        
        NumberWithUnits::~NumberWithUnits() {}
        
        NumberWithUnits& NumberWithUnits::operator +=(const NumberWithUnits& rhs) {
                if(units[this->unit].find(rhs.unit) == units[this->unit].end()) {
                      throw std::logic_error("This units are not matched!");  
                }
                this->amount += rhs.amount*units[rhs.unit][this->unit];
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits& rhs) {
                NumberWithUnits ans(this->amount, this->unit);
                ans += rhs;
                return ans;
        }
        NumberWithUnits NumberWithUnits::operator +() {
                return NumberWithUnits(this->amount, this->unit);
        }
        NumberWithUnits& NumberWithUnits::operator ++() {
                this->amount++;
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator ++(int){
                NumberWithUnits ans(this->amount, this->unit);
                this->amount++;
                return ans;
        }
        NumberWithUnits& NumberWithUnits::operator -=(const NumberWithUnits& rhs) {
                if(units[this->unit].find(rhs.unit) == units[this->unit].end()) {
                      throw std::logic_error("This units are not matched!");  
                }
                this->amount -= rhs.amount*units[rhs.unit][this->unit];
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits& rhs) {
                NumberWithUnits ans(this->amount, this->unit);
                ans -= rhs;
                return ans;
        }
        NumberWithUnits NumberWithUnits::operator -() {
                return NumberWithUnits(-this->amount, this->unit);
        }
        NumberWithUnits& NumberWithUnits::operator --() {
                this->amount--;
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator --(int) {
                NumberWithUnits ans(this->amount, this->unit);
                this->amount--;
                return ans;
        }
        
        bool NumberWithUnits::operator <(const NumberWithUnits& rhs) const {
                if(units[this->unit].find(rhs.unit) == units[this->unit].end()) {throw std::logic_error("This units cannot be compared!"); }
                return this->amount*units[this->unit][rhs.unit] < rhs.amount;
        }
        bool NumberWithUnits::operator >(const NumberWithUnits& rhs) const {return rhs < *this;}
        bool NumberWithUnits::operator <=(const NumberWithUnits& rhs) const {return *this < rhs || *this == rhs;}
        bool NumberWithUnits::operator >=(const NumberWithUnits& rhs) const {return rhs <= *this;}
        bool NumberWithUnits::operator ==(const NumberWithUnits& rhs) const {
                if(units[this->unit].find(rhs.unit) == units[this->unit].end()) {throw std::logic_error("This units cannot be compared!"); }
               // std::cout << "*****************************\n" << this->unit << " compare to " <<  rhs.unit << " with " << this->amount*units[this->unit][rhs.unit] << " == " << rhs.amount << std::endl;
                return abs(this->amount*units[this->unit][rhs.unit] - rhs.amount) < NumberWithUnits::eps;
        }
        bool NumberWithUnits::operator !=(const NumberWithUnits& rhs) const {
                return !(*this == rhs);
        }
        
        NumberWithUnits operator*(double d,const NumberWithUnits& rhs) {
                return NumberWithUnits(d * rhs.amount, rhs.unit);
        }
        
        NumberWithUnits operator*(const NumberWithUnits& lhs,double d) {
                return d*lhs;
        }
        
        std::istream& operator>>(std::istream& is, NumberWithUnits& rhs) {
                char ch;
                is >> rhs.amount >> ch >> rhs.unit;
                if(rhs.unit[rhs.unit.size()-1] == ']') {
                        rhs.unit = rhs.unit.substr(0, rhs.unit.size()-1);
                }
                else {
                        is >> ch;
                }
                if(NumberWithUnits::units.find(rhs.unit) == NumberWithUnits::units.end()) {
                        throw std::logic_error("This unit is not exists!");
                }
                return is;
        }
        std::istream& operator>>(std::istream& is, const NumberWithUnits& rhs) {
                return is;
        }
        std::ostream& operator<<(std::ostream& os, const NumberWithUnits& rhs) {
                os << rhs.amount << "[" << rhs.unit << "]";
                return os;
                
        }
        
// int main() {
//         std::ifstream units_file{"units.txt"};
//         NumberWithUnits::read_units(units_file);
//         return 0;
// }