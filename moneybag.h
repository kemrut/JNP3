/*Autorzy:
  Konrad Czarnecki
  Jacek Muszyński
*/

#ifndef MONEYBAG_H
#define MONEYBAG_H

#include <compare>
#include <iostream>
#include <string>
#include <sstream>

constexpr void safeAdd(uint64_t& l, const uint64_t& r) {
  uint64_t middle = l / 2;
  uint16_t extra = l - 2 * middle;
  middle += r / 2;
  extra += r - 2 * (r / 2);

  middle += extra / 2;
  if (UINT64_MAX / 2 <= middle) {
    throw std::out_of_range("when adding");
  }
  l += r;
}

class Moneybag {
  public:
    typedef uint64_t coin_number_t;

  constexpr Moneybag(const uint64_t& l, const uint64_t& s, const uint64_t& d):
    deniers(d), soliduses(s), livres(l) {}

  constexpr Moneybag(const Moneybag& mb):
    deniers(mb.deniers), soliduses(mb.soliduses), livres(mb.livres) {}
  constexpr Moneybag(Moneybag&& mb):
    deniers(std::move(mb.deniers)), soliduses(std::move(mb.soliduses)), livres(std::move(mb.livres)) {}

  // add two constructors from value(one with std::move())
  //~Moneybag() {}

  constexpr explicit operator bool() const {
    return deniers || soliduses || livres;
  }

  constexpr Moneybag& operator = (const Moneybag& mb) {
    deniers = mb.deniers;
    soliduses = mb.soliduses;
    livres = mb.livres;
    return *this;
  }

  friend constexpr bool operator == (const Moneybag& that, const Moneybag& t) {
    return t.deniers == that.deniers &&
      t.soliduses == that.soliduses &&
      t.livres == that.livres;
  }

  constexpr Moneybag& operator += (const Moneybag& that) {
    safeAdd(this -> deniers, that.deniers);
    safeAdd(this -> soliduses, that.soliduses);
    safeAdd(this -> livres, that.livres);
    return *this;
  }

  constexpr Moneybag& operator -= (const Moneybag& that) {
    if (!(deniers >= that.deniers && soliduses >= that.soliduses && livres >= that.livres)) {
      throw std::out_of_range("out of range");
    } else {
      deniers -= that.deniers;
      soliduses -= that.soliduses;
      livres -= that.livres;
    }
    return *this;
  }

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
  friend std::ostream& operator << (std::ostream& , const Moneybag&);
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

  constexpr Value(const uint64_t& d): amount(d) {}

  constexpr Value(): amount(0) {}

  constexpr Value(const Moneybag& m) {
    amount = m.denier_number() + 12 * m.solidus_number() + 240 * m.livre_number();
  }

  constexpr bool operator == (Value& that) {
    return this -> amount == that.get_amount();
  }

  bool operator == (uint64_t num) {
    return this -> amount == num;
  }

  explicit operator std::string() const {
    return std::to_string(amount);
  }

  std::string toString() {
    std::ostringstream s;
    s << amount;
    return s.str();
  }

  private:
    uint64_t amount;
};

inline std::strong_ordering operator <=> (const Value& v1, const Value& v2) {
  return v1.get_amount() <=> v2.get_amount();
}

inline std::strong_ordering operator <=> (const Value& v1, const uint64_t& x) {
  return v1.get_amount() <=> x;
}

inline std::strong_ordering operator <=> (const uint64_t& x, const Value& v) {
  return x <=> v.get_amount();
}

constexpr bool operator == (uint64_t x, const Value& v) {
  return v.get_amount() == x;
}

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
