#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cassert>
#include <algorithm>

#ifndef _INTEGER_H_
# define _INTEGER_H_

class integer {
public:
    bool negetive;
    std::vector<uint32_t> num;

    integer(uint32_t i = 0);
    integer(const integer &) = default;
    integer(integer &&) = default;
    integer &operator=(const integer &) = default;
    integer &operator=(integer &&) = default;

    friend integer operator-(const integer &);
    friend integer operator+(const integer &);
    friend integer operator+(integer, const integer &);
    friend integer &operator+=(integer &, const integer &);
    friend integer operator-(integer, const integer &);
    friend integer &operator-=(integer &, const integer &);
    friend integer operator*(integer, const integer &);
    friend integer &operator*=(integer &, const integer &);
    friend integer operator/(integer, const integer &);
    friend integer &operator/=(integer &, const integer &);
    friend integer operator%(integer, const integer &);
    friend integer &operator%=(integer &, const integer &);

    friend integer operator<<(integer, const uint32_t &);
    friend integer operator>>(integer, const uint32_t &);
    friend integer operator&(integer, const integer &);
    friend integer operator|(integer, const integer &);
    friend integer operator^(integer, const integer &);
    friend integer &operator<<=(integer &, const uint32_t &);
    friend integer &operator>>=(integer &, const uint32_t &);
    friend integer &operator&=(integer &, const integer &);
    friend integer &operator|=(integer &, const integer &);
    friend integer &operator^=(integer &, const integer &);


    friend bool operator>(const integer &, const integer &);
    friend bool operator<(const integer &, const integer &);
    friend bool operator==(const integer &, const integer &);
    friend bool operator>=(const integer &, const integer &);
    friend bool operator<=(const integer &, const integer &);
    friend bool operator!=(const integer &, const integer &);

    friend std::ostream &operator<<(std::ostream &, const integer &);
    friend std::istream &operator>>(std::istream &, integer &);

    static integer ZERO;
    static integer ONE;
    static integer TWO;
};

integer integer::ZERO(0);
integer integer::ONE(1);
integer integer::TWO(2);

integer &operator+=(integer &lhs, const integer &rhs) {
    if (rhs.negetive == lhs.negetive) {
        while (lhs.num.size() < rhs.num.size()) lhs.num.push_back(0);
        uint32_t cnt = 0;
        for (int i = 0; i < rhs.num.size(); i++) {
            uint32_t temp = lhs.num[i];
            lhs.num[i] = lhs.num[i] + rhs.num[i] + cnt;
            cnt = temp > lhs.num[i] ? 1 : temp > (temp + rhs.num[i]) ? 1 : 0;
        }
        if (cnt != 0) lhs.num.push_back(cnt);
        while (!lhs.num.empty() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    } else {
        return lhs -= (-rhs);
    }
    return lhs;
}

integer operator+(integer lhs, const integer &rhs) {
    return lhs += rhs;
}

integer operator+(const integer &self) {
    return self;
}

integer operator-(const integer &self) {
    integer ret(self);
    ret.negetive = !ret.negetive;
    return ret;
}

integer &operator-=(integer &lhs, const integer &rhs) {
    if (rhs.negetive == lhs.negetive) {
        integer temp1 = lhs;
        integer temp2 = rhs;
        integer ans;

        temp1.negetive = temp2.negetive = false;

        if (temp1 >= temp2) {
            ans = lhs;
            uint32_t cnt = 0;
            for (int i = 0; i < temp2.num.size(); i++) {
                uint32_t temp = ans.num[i];
                ans.num[i] = ans.num[i] - temp2.num[i] - cnt;
                cnt = temp < ans.num[i] ? 1 : temp < temp2.num[i] ? 1 : 0;
            }
            for (int i = temp2.num.size(); i < ans.num.size() && cnt != 0; ++i) {
                uint32_t temp = ans.num[i];
                ans.num[i] = ans.num[i] - cnt;
                cnt = temp < cnt ? 1 : 0;
            }
            while (!ans.num.empty() && ans.num[ans.num.size() - 1] == 0) ans.num.pop_back();
            lhs.num = ans.num;
            return lhs;
        } else {
            lhs.num = (temp2 - temp1).num;
            lhs.negetive = !lhs.negetive;
            return lhs;
        }
    } else {
        return lhs += (-rhs);
    }
}

bool operator>(const integer &lhs, const integer &rhs) {
    if (lhs.num.empty() && rhs.num.empty()) return false;
    if (!lhs.negetive && rhs.negetive) return true;
    if (lhs.negetive && !rhs.negetive) return false;
    if (!lhs.negetive && !rhs.negetive) {
        if (lhs.num.size() > rhs.num.size()) return true;
        if (lhs.num.size() < rhs.num.size()) return false;
        for (int i = lhs.num.size() - 1; i >= 0; i--) {
            if (lhs.num[i] > rhs.num[i])
                return true;
            else if (lhs.num[i] < rhs.num[i])
                return false;
        }
        return false;
    }
    if (lhs.negetive && rhs.negetive) {
        if (lhs.num.size() < rhs.num.size()) return true;
        if (lhs.num.size() > rhs.num.size()) return false;
        for (int i = lhs.num.size() - 1; i >= 0; i--) {
            if (lhs.num[i] < rhs.num[i])
                return true;
            else if (lhs.num[i] > rhs.num[i])
                return false;
        }
        return false;
    }
}

integer operator-(integer lhs, const integer &rhs) {
    return lhs -= rhs;
}

integer::integer(uint32_t i) {
    this->negetive = false;
    if (i) num.push_back(i);
}

bool operator==(const integer &lhs, const integer &rhs) {
    return (lhs.num.empty() && rhs.num.empty()) || (lhs.negetive == rhs.negetive && lhs.num == rhs.num);
}

bool operator<(const integer &lhs, const integer &rhs) {
    return (rhs > lhs);
}

bool operator>=(const integer &lhs, const integer &rhs) {
    return (!(rhs > lhs));
}

bool operator<=(const integer &lhs, const integer &rhs) {
    return (!(lhs > rhs));
}

bool operator!=(const integer &lhs, const integer &rhs) {
    return (!(lhs == rhs));
}

integer operator<<(integer lhs, const uint32_t &rhs) {
    return lhs <<= rhs;
}

integer operator>>(integer lhs, const uint32_t &rhs) {
    return lhs >>= rhs;
}

integer operator*(integer lhs, const integer &rhs) {
    return lhs *= rhs;
}

integer &operator*=(integer &lhs, const integer &rhs) {
    if (lhs == integer::ZERO || rhs == integer::ZERO)
        return (lhs = integer::ZERO);
    integer ret(0);
    ret.negetive = lhs.negetive != rhs.negetive;
    integer maxi = lhs;
    integer mini = rhs;
    maxi.negetive = mini.negetive = false;
    if (mini > maxi) std::swap(mini, maxi);
    int cnt = -1;
    integer temp = maxi;
    lhs = integer::ZERO;
    while (!mini.num.empty()) {
        if (mini.num[0] & 1) {
            temp <<= (cnt + 1);
            lhs += temp;
            cnt = 0;
        } else ++cnt;
        mini >>= 1;
    }
    return lhs;
}

integer &operator<<=(integer &lhs, const uint32_t &rhs) {
    int k = rhs >> 5;
    int off = rhs % 32;
    for (int i = (off ? k + 1 : k); i > 0; i--)
        lhs.num.push_back(0);
    if (k) {
        int cnt = off == 0 ? 1 : 2;
        for (int i = lhs.num.size() - cnt; i >= k; i--)
            lhs.num[i] = lhs.num[i - k];
        for (int i = k - 1; i >= 0; i--)
            lhs.num[i] = 0;
    }

    if (off) {
        uint32_t T = 0xffffffff;
        T = T << (32 - off);
        uint32_t cnt = 0;
        for (int i = 0; i < lhs.num.size(); i++) {
            uint32_t t = lhs.num[i];
            lhs.num[i] = (t << off) | cnt;
            cnt = (t & T) >> (32 - off);
        }
    }

    while (lhs.num.size() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    return lhs;
}

integer &operator>>=(integer &lhs, const uint32_t &rhs) {
    int k = rhs >> 5;
    int off = rhs % 32;

    if (k) {
        for (int i = 0; i + k < lhs.num.size(); i++)
            lhs.num[i] = lhs.num[i + k];
        for (int i = 0; i < k; i++)
            lhs.num.pop_back();
    }

    if (off) {
        uint32_t T = 0xffffffff;
        T = T >> (32 - off);
        for (int i = 0; i + 1 < lhs.num.size(); i++) {
            lhs.num[i] = ((lhs.num[i] >> off) | (((lhs.num[i + 1] & T) << (32 - off))));
        }
        if (!lhs.num.empty()) lhs.num[lhs.num.size() - 1] >>= off;
    }

    while (!lhs.num.empty() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    return lhs;
}

std::ostream &operator<<(std::ostream &out, const integer &self) {
    if (self == integer::ZERO) {
        out << "0";
        return out;
    }
    if (self.negetive) out << "-";
    for (int i = self.num.size() - 1; i >= 0; i--) out << std::hex << self.num[i];

    return out;
}

std::istream &operator>>(std::istream &in, integer &self) {
    std::string s;
    in >> s;
    self.negetive = s[0] == '-';
    self.num.clear();
    int top = s.size() - (self.negetive ? 1 : 0);
    for (int i = 1; i <= (top + 7) / 8; i++)
        self.num.push_back(0);
    for (int i = self.negetive ? 1 : 0; i < top % 8 + (self.negetive ? 1 : 0); i++) {

        int now = self.num.size() - 1;

        if (s[i] >= '0' && s[i] <= '9') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - 'A' + 10;
        }
    }
    for (int i = top % 8 + (self.negetive ? 1 : 0); i < s.size(); i++) {
        int now = self.num.size() - 1 - (i - (self.negetive ? 1 : 0)) / 8;
        if (s[i] >= '0' && s[i] <= '9') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            self.num[now] = ((self.num[now]) << 4) + s[i] - 'A' + 10;
        }
    }

    while (!self.num.empty() && self.num[self.num.size() - 1] == 0) self.num.pop_back();
    return in;
}

integer &operator/=(integer &lhs, const integer &rhs) {
    assert(rhs != integer::ZERO);
    integer ret(0);
    ret.negetive = lhs.negetive != rhs.negetive;
    integer temp1 = lhs;
    integer temp2 = rhs;
    temp1.negetive = temp2.negetive = false;
    if (temp1 < temp2) return integer::ZERO;
    integer l = integer::ZERO, r = temp1;

    while (r - l > 1) {
        assert(r >= l);
        integer mid = ((l + r) >> 1);
        if (mid * temp2 > temp1)
            r = mid;
        else
            l = mid;
    }
    if (r * temp2 > temp1) ret.num = l.num;
    else ret.num = r.num;
    lhs = ret;
    return lhs;
}

integer operator/(integer lhs, const integer &rhs) {
    return lhs /= rhs;
}

integer &operator%=(integer &lhs, const integer &rhs) {
    integer temp = lhs / rhs;
    temp = temp * rhs;
    temp = lhs - temp;
    lhs = temp;
    return lhs;
}

integer operator%(integer lhs, const integer &rhs) {
    return (lhs %= rhs);
}

integer &operator&=(integer &lhs, const integer &rhs) {
    int top = std::min(lhs.num.size(), rhs.num.size());
    for (int i = 0; i < top; i++)
        lhs.num[i] &= rhs.num[i];
    while (!lhs.num.empty() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    return lhs;
}

integer operator&(integer lhs, const integer &rhs) {
    return (lhs &= rhs);
}

integer &operator|=(integer &lhs, const integer &rhs) {
    while (lhs.num.size() < rhs.num.size()) lhs.num.push_back(0);
    for (int i = 0; i < rhs.num.size(); i++)
        lhs.num[i] |= rhs.num[i];
    while (!lhs.num.empty() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    return lhs;
}

integer &operator^=(integer &lhs, const integer &rhs) {
    while (lhs.num.size() < rhs.num.size()) lhs.num.push_back(0);
    for (int i = 0; i < rhs.num.size(); i++)
        lhs.num[i] ^= rhs.num[i];
    while (!lhs.num.empty() && lhs.num[lhs.num.size() - 1] == 0) lhs.num.pop_back();
    return lhs;
}

integer operator|(integer lhs, const integer &rhs) {
    return (lhs |= rhs);
}

integer operator^(integer lhs, const integer &rhs) {
    return (lhs ^= rhs);
}

#endif // _INTEGER_H_
