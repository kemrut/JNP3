/*Konrad Czarnecki
  Jacek Muszyński
*/

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

  constexpr Moneybag& operator+=(const Moneybag& that) {
    safeAdd(this->deniers, that.deniers);
    safeAdd(this->soliduses, that.soliduses);
    safeAdd(this->livres, that.livres);
    return *this;
  }

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

  /*constexpr Moneybag& operator*=(uint64_t x) {
    
      safeMultiplication(this->deniers,x);
      safeMultiplication(this->livres,x);
      safeMultiplication(this->soliduses,x);
    
    return *this;
  }*/
  //multiplication placeholder
  constexpr Moneybag& operator *= (uint64_t x) {
    if (x != 0 && UINT64_MAX / x < std::max(livres, std::max(deniers, soliduses))) {
      throw std::out_of_range("out of range");
    } else {
      this -> deniers *= x;
      this -> livres *= x;
      this -> soliduses *= x;
    }
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

constexpr std::partial_ordering operator <=> (const Moneybag& m1, const Moneybag& m2) {
  uint64_t l1 = m1.livre_number(), l2 = m2.livre_number();
  uint64_t s1 = m1.solidus_number(), s2 = m2.solidus_number();
  uint64_t d1 = m1.denier_number(), d2 = m2.denier_number();

  if (d1 == d2 && l1 == l2 && s1 == s2) {
    return std::partial_ordering::equivalent;
  }
  if (d1 <= d2 && l1 <= l2 && s1 <= s2) {
    return std::partial_ordering::less;
  }
  if (d1 >= d2 && l1 >= l2 && s1 >= s2) {
    return std::partial_ordering::greater;
  } else return std::partial_ordering::unordered;
}

constexpr const Moneybag operator * (const Moneybag& m1, uint64_t x) {
  Moneybag m(m1);
  m *= x;
  return m;
}

constexpr const Moneybag operator * (uint64_t x, const Moneybag& m1) {
  Moneybag m(m1);
  m *= x;
  return m;
}

constexpr const Moneybag operator + (const Moneybag& m1, const Moneybag& m2) {
  Moneybag m(m1);
  return m += m2;
}

constexpr const Moneybag operator - (const Moneybag& m1, const Moneybag& m2) {
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

  constexpr uint64_t get_over() const {
    return over;
  }
  constexpr Value(const uint64_t& d): over(d / maxn), amount(d % maxn) {}

  constexpr Value(): over(0), amount(0) {}

  constexpr Value(const Moneybag& m) {
    uint64_t tmp = 0;
    amount = m.denier_number() % maxn;
    over = m.denier_number() / maxn;
    amount += 12 * (m.solidus_number() % maxn);
    over += 12 * (m.solidus_number() / maxn);
    amount += 240 * (m.livre_number() % maxn);
    over += 240 * (m.livre_number() / maxn);
    tmp = amount;
    amount = amount % maxn;
    tmp -= amount;
    over += tmp / maxn;
    

  }

  constexpr bool operator == (const Value& that) const = default;//{

//TODO
  explicit operator std::string() const {
    std::ostringstream s;
    if (over == 0) return std::to_string(amount);
    s << std::to_string(over) << std::setfill('0') << std::setw(12) << std::to_string(amount);
    return std::move(s).str();
  }

  std::strong_ordering operator <=> (const Value& v2) const = default;

  /*std::string toString() {
    std::ostringstream s;
    s << amount;
    return s.str();
  }*/

  private:
    uint64_t over;
    uint64_t amount;
    static const uint64_t maxn = 1000000000000;//10^12
};


inline void auxOut(std::ostream& os, const uint64_t count,
    const std::string& singular, const std::string& multiplies) {
  os << count << " ";
  if (count == 1) {
    os << singular;
  } else {
    os << multiplies;
  }
}
inline std::ostream & operator << (std::ostream& os, const Moneybag& bag) {
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

