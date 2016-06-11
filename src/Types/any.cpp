#include <Veritas/Definitions/Types/any.h>

using Veritas::any;

any::any() : content(0) {}
any::any(any& a) : content(a.content->clone()) {}
any::any(any&& a) : content(a.content) { a.content = 0; }
any::~any() { delete content; }

bool any::empty() const { return !content; }
const std::type_info& any::type() const {
    if (content) return content->type();
    else return typeid(void);
}

any& any::operator=(any& a) {
    delete content;

    content = a.content->clone();

    return *this;
}

any& any::operator=(any&& a) {
    delete content;

    content = a.content;
    a.content = 0;

    return *this;
}

void any::clear() {
    delete content;
    content = 0;
}

void any::swap(any &a) {
    Content* tmp = a.content;
    a.content = content;
    content = tmp;
}
