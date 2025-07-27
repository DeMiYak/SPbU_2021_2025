#include <iostream>
#include "Stack.h"

void test(){
    Stack<int>st(1);
    st.Push(2);
    st.Push(3);
    st.Push(4);
    st.Push(5);
    Stack<int>a(st);
    st.SetFront(-1);
    st.PrintNods();
    a.PrintNods();
}

int main() {
    test();
}
