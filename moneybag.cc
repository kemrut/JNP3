#include <bits/stdc++.h>
#include "moneybag.h"


// constexpr void safeAdd(uint64_t& l, const uint64_t& r ){
//   uint64_t middle;
//   uint16_t extra;
//   middle = l/2;
//   extra = l - 2*middle;
//   middle += r/2;
//   extra += r -2*(r/2);

//   middle += extra/2;
//   // extra %= 2;
//   if (UINT64_MAX/2 <= middle){
//     throw std::out_of_range("when adding");
//   } 
//     l += r;
// }

// class Moneybag {
// public:
//   typedef uint64_t coin_number_t;

//   Moneybag(const uint64_t& l, const uint64_t& s, const uint64_t& d) 
//     : denars(d ), solirs(s), liwrs(l) {}
  
  
//   Moneybag(const Moneybag& mb )
//     : denars(mb.denars ), solirs(mb.solirs), liwrs(mb.liwrs) {}
//   Moneybag(Moneybag&& mb )
//     : denars(std::move(mb.denars) ), solirs(std::move(mb.solirs)), liwrs(std::move(mb.liwrs)) {}

//   // add two constructors from value(one with std::move())
//   ~Moneybag() {}
  
//   explicit operator bool() const{
//     return denars || solirs || liwrs;
//   }

//   Moneybag& operator=(const Moneybag& mb){
//     denars = mb.denars;
//     solirs = mb.solirs;
//     liwrs = mb.liwrs;
//     return *this;
//   }
//   Moneybag& operator=(Moneybag&& mb){
//     denars = std::move(mb.denars);
//     solirs = std::move(mb.solirs);
//     liwrs = std::move(mb.liwrs);
//     return *this;
//   }
  
//   bool operator==(const Moneybag& that){
//     return this->denars == that.denars &&
//       this->solirs == that.solirs &&
//       this->liwrs == that.liwrs;
//   }
//   bool operator>(const Moneybag& that){
//     return (this->liwrs > that.liwrs || 
//       this->solirs > that.solirs ||
//       this->denars > that.denars) &&
//       (this->liwrs >= that.liwrs &&
//       this->solirs >= that.solirs &&
//       this->denars >= that.denars);
//   }

//   bool operator >=(const Moneybag& that) {
//      return *this > that || *this == that;
//   }

//   bool operator <(const Moneybag& that) {
//     return Moneybag(that) > *this;
//   }

//   bool operator <=(const Moneybag& that) {
//     return Moneybag(that) >= *this;
//   }

//   Moneybag& operator+=(const Moneybag& that){
//     safeAdd(this->denars, that.denars);
//     safeAdd(this->solirs, that.solirs);
//     safeAdd(this->liwrs, that.liwrs);
//     return *this;
//   }
//   Moneybag& operator+(const Moneybag& that){
//     *this += that;
//     return *this;
//   }

//   coin_number_t solidus_number(){
//     return solirs;
//   }
//   coin_number_t livr_number(){
//     return liwrs;
//   }
//   coin_number_t denier_number(){
//     return denars;
//   }
// private:
//   uint64_t denars;
//   uint64_t solirs;
//   uint64_t liwrs;
//   friend std::ostream& operator<<(std::ostream&, const Moneybag&);
// };

// class Value {
// public:
//   uint64_t get_amount() {
//     return amount;
//   }

//   Value(const uint64_t& d){
//     amount = d;
//   }

//   Value(Moneybag& m) {
//     amount = m.denier_number() + 12 * m.solidus_number() + 240 * m.livr_number();
//   }
//   //do we need all of those operators?
//   bool operator >(Value& that) {
//     return this->amount > that.get_amount();
//   }

//   bool operator ==(Value& that) {
//     return this->amount == that.get_amount();
//   }

//   bool operator <(Value &that) {
//     return &that > this;
//   }

//   bool operator <=(Value &that) {
//     return &that > this || this == &that;
//   }

//   bool operator >=(Value &that) {
//     return this > &that || this == &that;
//   }

//   bool operator >(uint64_t num) {
//     return this->amount > num;
//   }

//   bool operator <(uint64_t num) {
//     return this->amount < num;
//   }

//   bool operator ==(uint64_t num) {
//     return this->amount == num;
//   }

//   bool operator >=(uint64_t num) {
//     return this->amount >= num;
//   }

//   bool operator <=(uint64_t num) {
//     return this->amount <= num;
//   }

//   std::string toString() {
//     std::ostringstream s;
//     s << amount;
//     return s.str();
//   }

// private:
//   uint64_t amount;
// };

// inline void auxOut(std::ostream& os,const uint64_t count,const std::string& singular, const std::string& multiplies){
//   os << count << " ";
//   if (count == 1){
//     os << singular;
//   } else{
//     os << multiplies;
//   }
// }
// inline std::ostream& operator<<(std::ostream& os, const Moneybag& bag) {
//   os << "(";
//   auxOut(os, bag.liwrs, "livr", "livres");
//   os << ", ";
//   auxOut(os, bag.solirs, "solidus", "soliduses");
//   os << ", ";
//   auxOut(os, bag.denars, "denier", "deniers");
//    os << ")\n";
//   return os;
// }


// using namespace std;

// int main() {
//     // Taka konstrukcja nie powinna się kompilować.
//     // Moneybag m0;

//     Moneybag m1 = Moneybag(1, 10, 19);

//     // Moneybag m2 = 2 * Solidus + 17 * Denier;
//     Moneybag m2 = Moneybag(0, 2, 17);

//     Moneybag m3(0, 0, 0);
//     Moneybag m4(m1);
//     m4 = m3;

//     // cout << m4 + m2 - Solidus << endl;

//     Moneybag::coin_number_t s = m2.solidus_number();
//     assert(s == 2);

//     assert(m1);
//     assert(!m3);
//     assert(m1 >= m2);
//     assert(m1 > m2);
//     assert(!(m1 < m2));
//     // cout<< m3<<"\n"<<m4<<"\n";
//     assert(m4 == m3);

//     assert(Moneybag(2, 2, 1) >= Moneybag(2, 1, 1));
//     assert(Moneybag(2, 2, 1) > Moneybag(2, 1, 1));
//     assert(!(Moneybag(1, 2, 2) <= Moneybag(2, 2, 1)));
//     assert(!(Moneybag(1, 2, 2) < Moneybag(2, 2, 1)));
//     // int k = Moneybag(1, 2, 3);

//     Value v1 = Value(m1);
//     Value v2(m2);

//     cout << v1.toString() << "\n";
//     cout << v2.toString() << "\n";
// }
