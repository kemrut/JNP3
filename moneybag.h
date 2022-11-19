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

constexpr void safeMultiplication(uint64_t& l, const uint64_t& r ){
  const uint64_t HALFSIZE_MAX = (1ul << UINT64_WIDTH/2) - 1ul;
  uint64_t lhs_high = l >> UINT64_WIDTH/2;
  uint64_t lhs_low  = l & HALFSIZE_MAX;
  uint64_t rhs_high = r >> UINT64_WIDTH/2;
  uint64_t rhs_low  = r & HALFSIZE_MAX;

  uint64_t bot_bits = lhs_low * rhs_low;
  if (!(lhs_high || rhs_high)) {
    l = bot_bits;
    return; 
  }
       
  uint16_t overflowed = lhs_high && rhs_high;
  uint64_t mid_bits1 = lhs_low * rhs_high;
  uint64_t mid_bits2 = lhs_high * rhs_low;

  if(overflowed || (mid_bits1 >> UINT64_WIDTH/2) != 0
    || (mid_bits2 >> UINT64_WIDTH/2) != 0){
       throw std::out_of_range("during safeMultiplication");
    }
  safeAdd(bot_bits, ((mid_bits1+mid_bits2) << UINT64_WIDTH/2));
  l = bot_bits;
}

class Moneybag {
public:
  typedef uint64_t coin_number_t;

  constexpr Moneybag(const uint64_t& l, const uint64_t& s, const uint64_t& d)
    : deniers(d), soliduses(s), livres(l) {}


  constexpr Moneybag(const Moneybag& mb)
    : deniers(mb.deniers), soliduses(mb.soliduses), livres(mb.livres) {}
  constexpr Moneybag(Moneybag&& mb)
    : deniers(std::move(mb.deniers)), soliduses(std::move(mb.soliduses)), livres(std::move(mb.livres)) {}

  // add two constructors from value(one with std::move())
  //~Moneybag() {}

  constexpr explicit operator bool() const {
    return deniers || soliduses || livres;
  }

  constexpr Moneybag& operator=(const Moneybag& mb)  {
    deniers = mb.deniers;
    soliduses = mb.soliduses;
    livres = mb.livres;
    return *this;
  }
  constexpr Moneybag& operator=(Moneybag&& mb) {
    deniers = std::move(mb.deniers);
    soliduses = std::move(mb.soliduses);
    livres = std::move(mb.livres);
    return *this;
  }

  friend constexpr bool operator==(const Moneybag& that, const Moneybag& t) {
    return t.deniers == that.deniers &&
      t.soliduses == that.soliduses &&
      t.livres == that.livres;
  }
/*
  constexpr bool operator>(const Moneybag& that){
    return (this->livres > that.livres ||
      this->soliduses > that.soliduses ||
      this->deniers > that.deniers) &&
      (this->livres >= that.livres &&
      this->soliduses >= that.soliduses &&
      this->deniers >= that.deniers);
  }
  constexpr bool operator<(const Moneybag& that){
    return (this->livres < that.livres ||
      this->soliduses <that.soliduses ||
      this->deniers < that.deniers) &&
      (this->livres <= that.livres &&
      this->soliduses <= that.soliduses &&
      this->deniers <= that.deniers);
  }
*/
  constexpr Moneybag& operator+=(const Moneybag& that) {
    safeAdd(this->deniers, that.deniers);
    safeAdd(this->soliduses, that.soliduses);
    safeAdd(this->livres, that.livres);
    return *this;
  }

  //exception?
  constexpr Moneybag& operator-=(const Moneybag& that) {
    if (!(deniers >= that.deniers && soliduses >= that.soliduses && livres >= that.livres)) {
      throw std::out_of_range("out of range");
    }
    else {
        deniers -= that.deniers;
        soliduses -= that.soliduses;
        livres -= that.livres;
    }
    return *this;
  }

  constexpr Moneybag& operator*=(uint64_t x) {
    safeMultiplication(this->deniers,x);
    safeMultiplication(this->livres,x);
    safeMultiplication(this->soliduses,x);
    return *this;
  }

  constexpr coin_number_t solidus_number() const {
    return soliduses;
  }
  constexpr coin_number_t livre_number() const {
    return livres;
  }
  constexpr coin_number_t denier_number() const {
    return deniers;
  }
  friend std::ostream& operator<<(std::ostream&, const Moneybag&);
private:
  coin_number_t deniers;
  coin_number_t soliduses;
  coin_number_t livres;

};


//TODO
constexpr std::partial_ordering operator<=>(const Moneybag& m1, const Moneybag& m2) {
    std::strong_ordering liv = m1.livre_number() <=> m2.livre_number();
    std::strong_ordering sol = m1.solidus_number() <=> m2.solidus_number();
    std::strong_ordering den = m1.denier_number() <=> m2.denier_number();

    if (std::is_eq(liv) && std::is_eq(sol) && std::is_eq(den)) {
        return std::partial_ordering::equivalent;
    }
    if (std::is_lteq(liv) && std::is_lteq(sol) && std::is_lteq(den)) {
        return std::partial_ordering::less;
    }
    if (std::is_gteq(liv) && std::is_gteq(sol) && std::is_gteq(den)) {
        return std::partial_ordering::greater;
    }
    else return std::partial_ordering::unordered;
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
    amount = m.denier_number() + 12 * m.solidus_number() + 240 * m.livre_number();
  }

  constexpr bool operator ==(Value& that) {
    return this->amount == that.get_amount();
  }

  bool operator ==(uint64_t num) {
    return this->amount == num;
  }

  explicit operator std::string() const {
      return std::to_string(amount);
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
  auxOut(os, bag.livres, "livr", "livres");
  os << ", ";
  auxOut(os, bag.soliduses, "solidus", "soliduses");
  os << ", ";
  auxOut(os, bag.deniers, "denier", "deniers");
   os << ")";
  return os;
}


#endif

