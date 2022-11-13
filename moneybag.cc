#include <bits/stdc++.h>
#include "moneybag.h"


class Moneybag {
public:
  typedef uint64_t coin_number_t;

  Moneybag(const uint64_t& l, const uint64_t& s, const uint64_t& d){
    denars = d;
    solirs = s;
    liwrs = l;
  }

  explicit operator bool() const{
    return denars || solirs || liwrs;
  }
  bool operator==(const Moneybag& that){
    // or should valuse be compared?
    return this->denars == that.denars &&
      this->solirs == that.solirs &&
      this->liwrs == that.liwrs;
  }
  bool operator>(const Moneybag& that){
    if (this->liwrs > that.liwrs) return true;
    if (this->liwrs < that.liwrs) return false;

    if (this->solirs > that.solirs) return true;
    if (this->solirs  < that.solirs) return false;

    if (this->denars > that.denars) return true;
    return false;
  }

  bool operator >=(const Moneybag& that) {
    return this == &that || this > &that;
  }

  bool operator <(const Moneybag& that) {
    return &that > this;
  }

  bool operator <=(const Moneybag& that) {
    return &that >= this;
  }

  Moneybag& operator+=(const Moneybag& that){
    this->denars += that.denars;
    this->solirs += that.solirs;
    this->liwrs += that.liwrs;
    return *this;
  }

  coin_number_t solidus_number(){
    return solirs;
  }
  coin_number_t livr_number(){
    return liwrs;
  }
  coin_number_t denier_number(){
    return denars;
  }
private:
  uint64_t denars;
  uint64_t solirs;
  uint64_t liwrs;
  friend std::ostream& operator<<(std::ostream&, const Moneybag&);
};

class Value {
public:
  uint64_t get_amount() {
    return amount;
  }

  Value(const uint64_t& d){
    amount = d;
  }

  Value(Moneybag& m) {
    amount = m.denier_number() + 12 * m.solidus_number() + 240 * m.livr_number();
  }
  //do we need all of those operators?
  bool operator >(Value& that) {
    return this->amount > that.get_amount();
  }

  bool operator ==(Value& that) {
    return this->amount == that.get_amount();
  }

  bool operator <(Value &that) {
    return &that > this;
  }

  bool operator <=(Value &that) {
    return &that > this || this == &that;
  }

  bool operator >=(Value &that) {
    return this > &that || this == &that;
  }

  bool operator >(uint64_t num) {
    return this->amount > num;
  }

  bool operator <(uint64_t num) {
    return this->amount < num;
  }

  bool operator ==(uint64_t num) {
    return this->amount == num;
  }

  bool operator >=(uint64_t num) {
    return this->amount >= num;
  }

  bool operator <=(uint64_t num) {
    return this->amount <= num;
  }

  std::string toString() {
    std::ostringstream s;
    s << amount;
    return s.str();
  }

private:
  uint64_t amount;
};

void auxOut(std::ostream& os,const uint64_t count,const std::string& singular, const std::string& multiplies){
  os << count << " ";
  if (count == 1){
    os << singular;
  } else{
    os << multiplies;
  }
}
std::ostream& operator<<(std::ostream& os, const Moneybag& bag) {
  os << "(";
  auxOut(os, bag.liwrs, "livr", "livres");
  os << ", ";
  auxOut(os, bag.solirs, "solidus", "soliduses");
  os << ", ";
  auxOut(os, bag.denars, "denier", "deniers");
   os << ")\n";
  return os;
}


using namespace std;

int main() {
    // Taka konstrukcja nie powinna się kompilować.
    // Moneybag m0;

    Moneybag m1 = Moneybag(1, 10, 19);

    // Moneybag m2 = 2 * Solidus + 17 * Denier;
    Moneybag m2 = Moneybag(0, 2, 17);

    Moneybag m3(0, 0, 0);
    Moneybag m4(m1);
    m4 = m3;

    cout << m4 << endl;
    // cout << m4 + m2 - Solidus << endl;

    Moneybag::coin_number_t s = m2.solidus_number();
    assert(s == 2);

    assert(m1);
    assert(!m3);
    assert(m1 >= m2);
    assert(m1 > m2);
    assert(!(m1 < m2));
    assert(m4 == m3);

    assert(Moneybag(2, 2, 1) >= Moneybag(2, 1, 1));
    assert(Moneybag(2, 2, 1) > Moneybag(2, 1, 1));
    assert(!(Moneybag(1, 2, 2) <= Moneybag(2, 2, 1)));
    assert(!(Moneybag(1, 2, 2) < Moneybag(2, 2, 1)));
    // int k = Moneybag(1, 2, 3);

    Value v1 = Value(m1);
    Value v2(m2);

    cout << v1.toString() << "\n";
    cout << v2.toString() << "\n";
}
