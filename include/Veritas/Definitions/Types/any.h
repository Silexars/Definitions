#pragma once

#include <typeinfo>
#include <utility>

namespace Veritas {
    class any {
        public:
            any();
            any(any& any);
            any(any&& any);
            template<class T> any(T&& t)                          :content(new TContent<typename std::remove_reference<T>::type>(std::forward<T>(t))) {}
            ~any();

            any& operator=(any& any);
            any& operator=(any&& any);
            template<class T> any& operator=(const T& t)         { delete content; content = new TContent<T>(t); return *this; }
            template<class T> any& operator=(T&& t)              { delete content; content = new TContent<typename std::remove_reference<T>::type>(std::forward<T>(t)); return *this; }

            void clear();
            void swap(any& any);

            bool empty() const;
            const std::type_info& type() const;
        private:
            class Content {
                public:
                    virtual const std::type_info& type() const = 0;

                    virtual Content* clone() const = 0;

                    void *content;
            };

            template <class T>
            class TContent : public Content {
                public:
                    TContent(T& t) { content = new T(t); }
                    TContent(T&& t) { content = new T(std::move(t)); }
                    ~TContent() { delete (T*) content; }

                    Content* clone() const { return new TContent(*((T*) content)); }

                    const std::type_info& type() const { return typeid(T); }
            };

            template <class T> friend T any_cast(const any& a);
            template <class T> friend T* any_cast(const any* a);
            Content* content;
    };

    template <class T> T any_cast(const any& a) { return *((T*) a.content->content); }
    template <class T> T* any_cast(const any* a) { return (T*) a->content->content; }
}
