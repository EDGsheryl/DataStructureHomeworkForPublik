#include <iostream>
using namespace std;

class cstring {
//your codes go here
    char *a;
    size_t length;
public:
    size_t _strlen(const char *); //get the length of the string
    char *_strcpy(char *dest, const char *src); //copy the [src] string into the [dest] string, return [dest] pointer
    char *_strcat(char *dest, const char *src); //append the [src] string to the [dest] string, return [dest] pointer
    size_t size() const; //get length of the string
    bool isEmpty() const; //return true if the string is null
    void empty(); //set the string to null
    cstring &concate(const cstring &); //concate two strings, result is stored into [this] string
    cstring &concate(const char *); //overloading
    char *get_str() const; //return the inner pointer
    cstring(); //default constructor
    cstring(char); //trivial constructor
    cstring(const char *); //trivial constructor
    cstring(const cstring &); //copy constructor
    cstring(cstring &&); //move copy constructor
    ~cstring();

    cstring &operator=(const char *str);
    cstring &operator=(const cstring &str);
    cstring &operator=(char *&&str);
    cstring &operator=(cstring &&str) noexcept;
    cstring &operator+=(const char *str);
    cstring &operator+=(const cstring &str);
    cstring operator+(const cstring &str);
    char& operator[](std::size_t n);
    friend ostream &operator<<(ostream &os, const cstring &str);
    friend istream &operator>>(istream &is, cstring &str);
};

class cstring;

size_t cstring::_strlen(const char *str) {
    if (str == nullptr) return 0;
    size_t cnt = 0;
    auto p = str;
    while ((*p) != '\0') {
        cnt++;
        p++;
    }
    return cnt;
}
char* cstring::_strcpy(char *dest, const char *src) {
    auto p1 = dest;
    if (dest== nullptr || dest==NULL)
    {
        p1 = dest = new char[this->_strlen(src)+1];
    }
    auto p2 = src;
    while (p2!=NULL && (*p2) != '\0') {
        *p1 = *p2;
        p1++;
        p2++;
    }
    *p1 = 0;
    return dest;
}

char* cstring::_strcat(char *dest, const char *src) {
    char *now=new char[this->_strlen(dest)+1];
    this->_strcpy(now,dest);
    delete[] dest;
    dest = new char[this->_strlen(now) + this->_strlen(src) +1];

    auto p1 = dest;
    auto p2 = src;
    auto p3 = now;
    while ((*p3) != '\0') {
        *p1=*p3;
        p1++;
        p3++;
    }
    while ((*p2) != '\0') {
        *p1 = *p2;
        p2++;
        p1++;
    }
    *p1=0;
    return dest;
}
size_t cstring::size() const {
    return this->length;
}
bool cstring::isEmpty() const {
    return this->length==0;
}
void cstring::empty() {
    delete(this->a);
    this->a= nullptr;
    this->length=0;
}
cstring& cstring::concate(const cstring& str) {
    this->a=this->_strcat(this->a,str.a);
    this->length+=str.length;
    return *this;
}
cstring& cstring::concate(const char *str) {
    this->_strcat(this->a,str);
    this->length+=this->_strlen(str);
    return *this;
}
char *cstring::get_str() const {
    return this->a;
}
cstring::cstring() {
    this->length=0;
    this->a = nullptr;
}
cstring::cstring(char x) {
    this->a =new char[2];
    this->a[0]=x;
    this->length=1;
}
cstring::cstring(const char * str) {
    this->a=new char[this->_strlen(str)+1];
    this->_strcpy(this->a,str);
    this->length=this->_strlen(this->a);
}
cstring::cstring(const cstring& str) {
    this->a=new char[this->_strlen(str.a)+1];
    this->_strcpy(this->a,str.a);
    this->length=this->_strlen(this->a);
}
cstring::cstring(cstring&& str) {
    this->a=str.a;
    this->length = str.length;
    str.a= nullptr;
    str.length=0;
}
cstring::~cstring() {
    delete[] this->a;
}

cstring& cstring::operator=(const char *str) {
    this->a=this->_strcpy(this->a,str);
    return *this;
}

cstring& cstring::operator=(const cstring &str) {
    this->a=this->_strcpy(this->a,str.a);
}

cstring& cstring::operator+=(const char *str) {
    this->a=this->_strcat(this->a,str);
}

cstring& cstring::operator+=(const cstring &str) {
    this->a=this->_strcat(this->a,str.a);
}

cstring cstring::operator+(const cstring &str) {
    cstring ret;
    ret.a=ret._strcat(ret.a,this->a);
    ret.a=ret._strcat(ret.a,str.a);
    return std::move(ret);
}

char& cstring::operator[](std::size_t n) {
    return this->a[n];
}

istream& operator>>(istream &is, cstring &str) {
    int maxcnt=2; // char[] size
    char *tmp = new char[maxcnt+1];
    int cnt=0;
    char ch;
    cstring* ret;
    while ((ch=is.get()) && (ch!=' ' && ch!='\n'))
    {
        tmp[cnt++]=ch;
        if (cnt==maxcnt)
        {
            maxcnt<<=1;
            char *nxt = new char[maxcnt+1];
            str._strcpy(nxt,tmp);
            std::swap(nxt,tmp);
            delete[] nxt;
        }
    }
    tmp[cnt++]=0;
    str.a=tmp;
    return is;
}

ostream& operator<<(ostream &os, const cstring &str) {
    os<<str.a;
    return os;
}

cstring &cstring::operator=(char *&&str) {
    this->a=str;
    this->length=this->_strlen(str);
    str= nullptr;
    return *this;
}

cstring &cstring::operator=(cstring &&str) noexcept {
    this->a=str.a;
    this->length=str.length;
    str.a= nullptr;
    return *this;
}

//DO NOT CHANGE ANYTHING BELOW!!!
void puts(const cstring& s)
{
    cout << s.get_str();
}

cstring f(const char *s)
{
    return cstring(s);
}

int main()
{
    char b1[128], b2[128];
    cin >> b1 >> b2;

    cstring s1(b1), s2(s1);

    puts(s2.concate(f(b2)));

    return 0;
}
