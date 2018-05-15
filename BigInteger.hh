#include <iostream>
#include <vector>
#include <queue>

/*
    it may go wrong, bad design =A=
*/

#ifndef _INTEGER_H_
# define _INTEGER_H_

class BigInteger {
public:
    bool negetive;
    std::vector<int> num;

    BigInteger(long long i = 0);

    BigInteger(const BigInteger &);

    BigInteger &operator=(const BigInteger &);

    BigInteger &operator=(BigInteger &&) = default;


    friend BigInteger operator-(const BigInteger &);

    friend BigInteger operator+(const BigInteger &);


    friend bool operator<(const BigInteger &, const BigInteger &);

    friend bool operator>(const BigInteger &, const BigInteger &);

    friend bool operator<=(const BigInteger &, const BigInteger &);

    friend bool operator>=(const BigInteger &, const BigInteger &);

    friend bool operator==(const BigInteger &, const BigInteger &);

    friend bool operator!=(const BigInteger &, const BigInteger &);


    friend BigInteger operator+(const BigInteger &, const BigInteger &);

    friend BigInteger operator-(const BigInteger &, const BigInteger &);

    friend BigInteger operator*(const BigInteger &, const BigInteger &);

    friend BigInteger operator/(const BigInteger &, const BigInteger &);

    friend BigInteger operator%(const BigInteger &, const BigInteger &);

    BigInteger &operator+=(const BigInteger &);

    BigInteger &operator-=(const BigInteger &);

    BigInteger &operator*=(const BigInteger &);

    BigInteger &operator/=(const BigInteger &);

    BigInteger &operator%=(const BigInteger &);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    friend std::istream &operator>>(std::istream &, BigInteger &);

};

BigInteger &BigInteger::operator=(const BigInteger &rhs) {
    this->negetive = rhs.negetive;
    this->num = rhs.num;
}

BigInteger::BigInteger(const BigInteger &rhs) {
    this->negetive = rhs.negetive;
    this->num = rhs.num;
}

BigInteger::BigInteger(long long i) {
    num.clear();
    negetive = i < 0;

    i = i < 0 ? -i : i;

    while (i) {
        num.push_back(i % 10);
        i /= 10;
    }
}

bool operator<(const BigInteger &lhs, const BigInteger &rhs) {
    if (lhs.negetive && !rhs.negetive) return true;
    if (lhs.negetive == rhs.negetive) {
        if (!lhs.negetive) {
            if (lhs.num.size() < rhs.num.size()) return true;
            else if (lhs.num.size() == rhs.num.size()) {
                for (int i = lhs.num.size() - 1; i >= 0; i--) {
                    if (lhs.num[i] < rhs.num[i]) return true;
                    else if (lhs.num[i] > rhs.num[i]) return false;
                }
            } else return false;
        } else {
            if (lhs.num.size() > rhs.num.size()) return true;
            else if (lhs.num.size() == rhs.num.size()) {
                for (int i = lhs.num.size() - 1; i >= 0; i--) {
                    if (lhs.num[i] > rhs.num[i]) return true;
                    else if (lhs.num[i] < rhs.num[i]) return false;
                }
            } else return false;
        }
    }
    return false;
}

bool operator>(const BigInteger &lhs, const BigInteger &rhs) {
    if (!lhs.negetive && rhs.negetive) return true;
    if (lhs.negetive == rhs.negetive) {
        if (!lhs.negetive) {
            if (lhs.num.size() > rhs.num.size()) return true;
            else if (lhs.num.size() == rhs.num.size()) {
                for (int i = lhs.num.size() - 1; i >= 0; i--) {
                    if (lhs.num[i] > rhs.num[i]) return true;
                    else if (lhs.num[i] < rhs.num[i]) return false;
                }
            } else return false;
        } else {
            if (lhs.num.size() < rhs.num.size()) return true;
            else if (lhs.num.size() == rhs.num.size()) {
                for (int i = lhs.num.size() - 1; i >= 0; i--) {
                    if (lhs.num[i] < rhs.num[i]) return true;
                    else if (lhs.num[i] > rhs.num[i]) return false;
                }
            } else return false;
        }
    }
    return false;
}

bool operator<=(const BigInteger &lhs, const BigInteger &rhs) {
    if (lhs < rhs) return true;
    return lhs == rhs;
}

bool operator>=(const BigInteger &lhs, const BigInteger &rhs) {
    if (lhs > rhs) return true;
    return lhs == rhs;
}

bool operator==(const BigInteger &lhs, const BigInteger &rhs) {
    return (rhs.num == lhs.num && lhs.negetive == rhs.negetive);
}

bool operator!=(const BigInteger &lhs, const BigInteger &rhs) {
    return (!(lhs == rhs));
}

BigInteger abs(const BigInteger &t) {
    BigInteger ret;
    ret.num = t.num;
    ret.negetive = false;
    return ret;
}

BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs) {

    if (!(lhs.negetive ^ rhs.negetive)) {                         //negetive+negetive  positive+positive
        BigInteger ret = lhs;
        for (int i = 0; i < rhs.num.size(); i++) {
            if (i < lhs.num.size()) ret.num[i] += rhs.num[i];
            else ret.num.push_back(rhs.num[i]);
        }
        for (int i = 0; i < ret.num.size(); i++) {
            if (i + 1 < ret.num.size()) {
                if (ret.num[i] > 10) {
                    ret.num[i] -= 10;
                    ret.num[i + 1]++;
                }
            } else {
                if (ret.num[i] > 10) {
                    ret.num[i] -= 10;
                    ret.num.push_back(1);
                }
            }
        }
        return ret;

    } else {
        if (abs(lhs) < abs(rhs)) {
            BigInteger ret;
            ret.negetive = !lhs.negetive;
            ret.num = rhs.num;
            for (int i = 0; i < lhs.num.size(); i++) ret.num[i] -= lhs.num[i];
            for (int i = 0; i < ret.num.size(); i++) {
                if (ret.num[i] < 0) {
                    ret.num[i] += 10;
                    ret.num[i + 1]--;
                }
            }
            while (ret.num[ret.num.size() - 1] == 0) ret.num.pop_back();
            return ret;
        } else if (abs(lhs) > abs(rhs)) {
            BigInteger ret;
            ret.negetive = lhs.negetive;
            ret.num = lhs.num;
            for (int i = 0; i < rhs.num.size(); i++) ret.num[i] -= rhs.num[i];
            for (int i = 0; i < ret.num.size(); i++) {
                if (ret.num[i] < 0) {
                    ret.num[i] += 10;
                    ret.num[i + 1]--;
                }
            }
            while (ret.num[ret.num.size() - 1] == 0) ret.num.pop_back();
            return ret;
        } else {
            return *(new BigInteger());
        }
    }

}

BigInteger operator-(const BigInteger &lhs, const BigInteger &rhs) {
    return (lhs + (-rhs));
}

BigInteger operator+(const BigInteger &self) {
    return self;
}

BigInteger operator-(const BigInteger &self) {
    BigInteger ret = self;
    ret.negetive = !ret.negetive;
    return ret;
}

BigInteger &BigInteger::operator+=(const BigInteger &rhs) {
    return ((*this) = (*this) + rhs);
}

std::ostream &operator<<(std::ostream &os, const BigInteger &rhs) {
    if (rhs.num.size() == 0) os << '0';
    if (rhs.negetive) os << '-';
    for (int i = rhs.num.size() - 1; i >= 0; i--) os << rhs.num[i];
    return os;
}

std::istream &operator>>(std::istream &in, BigInteger &rhs) {
    rhs.negetive = false;
    rhs.num.clear();
    std::string rd;
    in >> rd;
    if (rd.size()) {
        if (rd[0] == '-') {
            rhs.negetive = true;
        }

        for (int i = rd.size() - 1; i >= 0 && rd[i] != '-'; i--) rhs.num.push_back(rd[i] - '0');
    }
    return in;
}

BigInteger &BigInteger::operator-=(const BigInteger &rhs) {
    return ((*this) = (*this) - rhs);
}

BigInteger operator*(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger ret;
    ret.negetive = lhs.negetive != rhs.negetive;
    for (int i = 0; i < lhs.num.size() + rhs.num.size() + 10; i++) ret.num.push_back(0);
    for (int i = 0; i < lhs.num.size(); i++)
        for (int o = 0; o < rhs.num.size(); o++)
            ret.num[i + o] += (lhs.num[i]) * (rhs.num[o]);
    for (int i = 0; i < ret.num.size(); i++) {
        if (ret.num[i] < 10) continue;
        else {
            if (i + 1 >= ret.num.size()) ret.num.push_back(ret.num[i] / 10);
            else ret.num[i + 1] += ret.num[i] / 10;
            ret.num[i] %= 10;
        }
    }
    while (ret.num.size() && ret.num[ret.num.size() - 1] == 0) ret.num.pop_back();
    return ret;
}

BigInteger &BigInteger::operator*=(const BigInteger &rhs) {
    return ((*this) = (*this) * rhs);
}

BigInteger operator/(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger ret = BigInteger(0);
    ret.negetive = lhs.negetive != rhs.negetive;

    BigInteger remainer = BigInteger(0);
    std::deque<int> q;
    BigInteger rhstemp = rhs;
    rhstemp.negetive = false;
    for (int i = lhs.num.size() - 1; i >= 0; i--) {
        int j = 0;
        remainer = (remainer * 10) + lhs.num[i];
        while (remainer >= rhstemp) {
            remainer -= rhstemp;
            j++;
        }
        q.push_back(j);
    }
    while (!q.empty() && q.front() == 0) q.pop_front();
    while (!q.empty()) {
        ret.num.push_back(q.back());
        q.pop_back();
    }

    return ret;
}

BigInteger &BigInteger::operator/=(const BigInteger &rhs) {
    return ((*this) = (*this) / rhs);
}

BigInteger operator%(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger ret = lhs / rhs;
    ret = ret * rhs;
    ret = lhs - ret;
    return ret;
}

BigInteger &BigInteger::operator%=(const BigInteger &rhs) {
    return ((*this) = (*this) % rhs);
}

BigInteger power(const BigInteger &lhs, BigInteger rhs) {
    BigInteger ret(1);
    BigInteger now(lhs);

    while (rhs != 0) {
        if (rhs % 2 == 1) ret = ret * now;
        rhs /= 2;
        now = now * now;
    }

    return ret;
}

BigInteger power(const BigInteger &lhs, BigInteger rhs, const BigInteger MOD) {
    BigInteger ret(1);
    BigInteger now(lhs);

    while (rhs != 0) {
        if (rhs % 2 == 1) ret = (ret * now) % MOD;
        rhs /= 2;
        now = (now * now) % MOD;
    }

    return ret;
}

#endif // _INTEGER_H_
