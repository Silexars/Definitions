#pragma once

#include <typeinfo>
#include <utility>
#include <type_traits>

namespace Veritas {
    class any {
        public:
            any();
            any(const any& any);
            any(any&& any);
            template <class T> any(T&& t, typename std::enable_if<!std::is_same<any&, T>::value, bool>::type = false) : content(new TypedContent<typename std::remove_reference<T>::type>(std::forward<T>(t))) {}
            ~any();

            any& operator=(const any& any);
            any& operator=(any&& any);
            template<class T> typename std::enable_if<!std::is_same<any&, T>::value, any>::type& operator=(T&& t) { delete content; content = new TypedContent<typename std::remove_reference<T>::type>(std::forward<T>(t)); return *this; }

            void clear();
            void swap(any& any);

            bool empty() const;
            const std::type_info& type() const;

            template <class T> T cast() { return *(typename std::remove_reference<T>::type*) content->content; }
            template <class T> T cast() const { return *(typename std::remove_reference<T>::type*) content->content; }
        private:
            class Content {
                public:
                    virtual ~Content() = default;

                    virtual const std::type_info& type() const = 0;

                    virtual Content* clone() const = 0;

                    void *content;
            };

            template <class ContentType>
            class TypedContent : public Content {
                public:
                    TypedContent(const ContentType& t) { content = (void*) new ContentType(t); }
                    TypedContent(TypedContent&& t) { content = new ContentType(std::move(t)); }
                    ~TypedContent() { delete (ContentType*) content; }

                    Content* clone() const { return new TypedContent(*((ContentType*) content)); }

                    const std::type_info& type() const { return typeid(ContentType); }

                    template <class CastType>
                    CastType& cast() { return *(CastType*) content; }
            };
            Content* content;
    };

    template <class T> T any_cast(any& a) { return a.cast<T>(); }
    template <class T> T any_cast(const any& a) { return a.cast<T>(); }
}
