#ifndef MONEYBAG_H
#define MONEYBAG_H

#include <bits/stdc++.h>

constexpr void safeAdd(uint64_t& l, const uint64_t& r ){
  uint64_t middle = l/2;
  uint16_t extra = l - 2*middle;
  middle += r/2;
  extra += r -2*(r/2);

  middle += extra/2;
  // extra %= 2;
  if (UINT64_MAX/2 <= middle){
    throw std::out_of_range("when adding");
  }
    l += r;
}

class Moneybag {
public:
  typedef uint64_t coin_number_t;

  constexpr Moneybag(const uint64_t& l, const uint64_t& s, const uint64_t& d)
    : denars(d), solirs(s), liwrs(l) {}


  constexpr Moneybag(const Moneybag& mb )
    : denars(mb.denars ), solirs(mb.solirs), liwrs(mb.liwrs) {}
  constexpr Moneybag(Moneybag&& mb )
    : denars(std::move(mb.denars) ), solirs(std::move(mb.solirs)), liwrs(std::move(mb.liwrs)) {}

  // add two constructors from value(one with std::move())
  //~Moneybag() {}

  constexpr explicit operator bool() const{
    return denars || solirs || liwrs;
  }

  constexpr Moneybag& operator=(const Moneybag& mb) {
    denars = mb.denars;
    solirs = mb.solirs;
    liwrs = mb.liwrs;
    return *this;
  }
  constexpr Moneybag& operator=(Moneybag&& mb) {
    denars = std::move(mb.denars);
    solirs = std::move(mb.solirs);
    liwrs = std::move(mb.liwrs);
    return *this;
  }

  friend constexpr bool operator==(const Moneybag& that, const Moneybag& t){
    return t.denars == that.denars &&
      t.solirs == that.solirs &&
      t.liwrs == that.liwrs;
  }
  constexpr bool operator>(const Moneybag& that){
    return (this->liwrs > that.liwrs ||
      this->solirs > that.solirs ||
      this->denars > that.denars) &&
      (this->liwrs >= that.liwrs &&
      this->solirs >= that.solirs &&
      this->denars >= that.denars);
  }

  constexpr bool operator >=(const Moneybag& that) {
     return *this > that || *this == that;
  }

  constexpr Moneybag& operator+=(const Moneybag& that){
    safeAdd(this->denars, that.denars);
    safeAdd(this->solirs, that.solirs);
    safeAdd(this->liwrs, that.liwrs);
    return *this;
  }

  //exception?
  constexpr Moneybag& operator-=(const Moneybag& that) {
    if (denars >= that.denars && solirs >= that.solirs && liwrs >= that.liwrs) {
        denars -= that.denars;
        solirs -= that.solirs;
        liwrs -= that.liwrs;
    }
    return *this;
  }

  constexpr Moneybag& operator*=(uint64_t x) {
    this->denars *= x;
    this->liwrs *= x;
    this->solirs *= x;
    return *this;
  }

  constexpr coin_number_t solidus_number() const{
    return solirs;
  }
  constexpr coin_number_t livr_number() const{
    return liwrs;
  }
  constexpr coin_number_t denier_number() const{
    return denars;
  }
  friend std::ostream& operator<<(std::ostream&, const Moneybag&);
private:
  coin_number_t denars;
  coin_number_t solirs;
  coin_number_t liwrs;

};


//TODO
constexpr std::partial_ordering operator<=>(const Moneybag& m1, const Moneybag& m2) {

    return std::partial_ordering::unordered;
}

constexpr const Moneybag operator *(const Moneybag& m1, uint64_t x) {
    Moneybag m(m1);
    m *= x;
    return m;
}

constexpr const Moneybag operator *(uint64_t x, const Moneybag& m1) {
    Moneybag m(m1);
    m *= x;
    return m;
}

constexpr const Moneybag operator +(const Moneybag& m1, const Moneybag& m2) {
    Moneybag m(m1);
    return m += m2;
}

constexpr const Moneybag operator -(const Moneybag& m1, const Moneybag& m2) {
    Moneybag m(m1);
    return m -= m2;
}
constexpr Moneybag Livre = Moneybag(1, 0, 0);
constexpr Moneybag Solidus = Moneybag(0, 1, 0);
constexpr Moneybag Denier = Moneybag(0, 0, 1);


//casting to string not done
class Value {
public:
  constexpr uint64_t get_amount() const {
    return amount;
  }

  constexpr Value(const uint64_t& d)
    : amount(d) {}


  constexpr Value()
    : amount(0) {}


  constexpr Value(const Moneybag& m) {
    amount = m.denier_number() + 12 * m.solidus_number() + 240 * m.livr_number();
  }

  constexpr bool operator ==(Value& that) {
    return this->amount == that.get_amount();
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
//need to handle big values
private:
  uint64_t amount;
  //uint64_t big;
};

inline std::strong_ordering operator<=>(const Value& v1, const Value& v2) {
    return v1.get_amount() <=> v2.get_amount();
}

inline std::strong_ordering operator<=>(const Value& v1, const uint64_t& x) {
    return v1.get_amount() <=> x;
}

inline std::strong_ordering operator<=>(const uint64_t& x, const Value& v) {
    return x <=> v.get_amount();
}

constexpr bool operator ==(uint64_t x, const Value& v) {
    return v.get_amount() == x;
}
inline void auxOut(std::ostream& os,const uint64_t count,const std::string& singular, const std::string& multiplies){
  os << count << " ";
  if (count == 1){
    os << singular;
  } else{
    os << multiplies;
  }
}
inline std::ostream& operator<<(std::ostream& os, const Moneybag& bag) {
  os << "(";
  auxOut(os, bag.liwrs, "livr", "livres");
  os << ", ";
  auxOut(os, bag.solirs, "solidus", "soliduses");
  os << ", ";
  auxOut(os, bag.denars, "denier", "deniers");
   os << ")\n";
  return os;
}


#endif
