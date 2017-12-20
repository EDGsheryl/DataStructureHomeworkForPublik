//
// Created by 冰糖雪梨 on 2017/12/20.
//
#ifndef HELLO_MYLIST_H
#define HELLO_MYLIST_H

#endif //HELLO_MYLIST_H

template<typename T>
class mynode {
public:
    T val;
    mynode<T> *pre;
    mynode<T> *nxt;

    mynode(T _val) : val(_val) {
        pre = nxt = nullptr;
    }
};

template<typename T>
class mylist {
public:
    mynode<T> *head;
    mynode<T> *tail;
    int cnt;

    mylist() {
        head = new mynode<T>(*(new T()));
        tail = new mynode<T>(*(new T()));
        head->nxt = tail;
        tail->pre = head;
        cnt = 0;
    }

    size_t size() {
        return static_cast<size_t>(cnt);
    }

    void push_back(T _val) {
        mynode<T> *now = tail->pre;
        auto newnode = new mynode<T>(_val);
        now->nxt = newnode;
        newnode->nxt = tail;
        tail->pre = newnode;
        newnode->pre = now;
        cnt++;
    }

    mynode<T> &operator[](int n) {
        auto now = head->nxt;
        while (now != tail && n--) now = now->nxt;
        return (*now);
    }

    void pop_back() {
        if (cnt == 0) return;
        tail->pre = tail->pre->pre;
        tail->pre->nxt = tail;
        cnt--;
    }

    void traverse(void foo(T)) {
        auto now = head->nxt;
        while (now != tail) {
            foo(now->val);
            now = now->nxt;
        }
    }

    struct iterator {
        mynode<T> *val;

        void operator++(int) {
            val = val->nxt;
            return;
        }

        bool operator!=(iterator another) {
            return this->val->val != another.val->val;
        }

        T &operator*() {
            return val->val;
        }

        iterator &operator=(iterator another) {
            this->val = another.val;
            return another;
        };

        iterator operator+(int i) {
            int k = i;
            while (k--) {
                this->val = this->val->nxt;
            }
            return *this;
        }

    };

    iterator begin() const {
        iterator ret;
        ret.val = (head->nxt);
        return ret;
    }

    iterator end() const {
        iterator ret;
        ret.val = tail;
        return ret;
    }
};