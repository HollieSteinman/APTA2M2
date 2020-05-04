#include <iostream>
#include <memory>

#define EXIT_SUCCESS 0

using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;

class test_object{
    public:
        test_object() {};
        ~test_object() {
            cout << "object destructor called" << endl;
        }
};

void foo(shared_ptr<int> arg);
void foo(shared_ptr<test_object> arg);
void foo(unique_ptr<test_object>& arg);

int main(void)
{
    shared_ptr<int> x = std::make_shared<int>(0);
    shared_ptr<int> y = std::make_shared<int>(-10);

    unique_ptr<int> y_un = std::make_unique<int>(-10);
    cout << y_un.get() << endl;
    cout << "x: " << *x << ", y: " << *y << endl;

    shared_ptr<test_object> test_ptr_shared = std::make_shared<test_object>();
    cout << "use count is now " << test_ptr_shared.use_count() << endl;
    unique_ptr<test_object> test_ptr_unique = std::make_unique<test_object>();
    foo(test_ptr_shared);
    foo(test_ptr_unique);
    foo(x);
    cout << "x: " << *x << ", y: " << *y << endl;

    y = x;
    cout << "x: " << *x << ", y: " << *y << endl;

    {
        int x = 2;
        shared_ptr<int> y = std::make_shared<int>(7);
        cout << "x: " << x << ", y: " << *y << endl;
    }

    cout << "x: " << *x << ", y: " << *y << endl;

    return EXIT_SUCCESS;
}

void foo(shared_ptr<int> arg)
{
    *arg += 1;
}

void foo(shared_ptr<test_object> arg){
    cout << "use count is now " << arg.use_count() << endl;
    cout <<"shared_ptr_test" << endl;
    return;
}

void foo(unique_ptr<test_object>& arg){
    cout <<"unique_ptr_test" << endl;
    return;
}
