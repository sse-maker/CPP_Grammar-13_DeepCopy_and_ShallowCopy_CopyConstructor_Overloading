//
//  main.cpp
//  13_DeepCopy_and_ShallowCopy
//
//  Created by 세광 on 2021/07/02.
//

// 얕은 복사(참조 복사): 포인터 자체의 가리키고 있는 주소값을 바꾸는 것
// 깊은 복사(값 복사): 가리키고 있는 공간 자체에 들어있는 값을 바꾸는 것

#include <iostream>

using namespace std;

// string을 다루는 class
class String {
public:
    String() {
        cout << "String() 생성자 호출" << endl;
        strData = NULL; // NULL: 포인터가 지금 아무것도 가리키고 있지 않다는 것을 말해줄 때 사용
        len = 0;
    }
    
    String(const char *str) { // str: const char를 가리키는 포인터
        cout << "String(const char*) 생성자 호출" << endl;
        len = strlen(str); // len이 매개변수로 받은 str의 길이를 저장
        strData = new char[len + 1]; // 동적 할당 (null 문자를 고려해 len + 1만큼 할당)
        cout << "strData 할당: " << (void*)strData << endl;
        // strData가 문자열로 취급되지 않고 주소값이 출력될 수 있도록 void 포인터로 형변환
        // void 포인터의 경우 주소값만 가지고 있을 뿐 다른 자료형에 대한 정보는 가지고 있지 않음 (주소값에 저장된 값 자체를 바꿀 수는 없음)
        strcpy(strData, str); // 깊은 복사
    }
    
    String(const String &rhs) {
        cout << "String(String &rhs) 생성자 호출" << endl;
        strData = new char[rhs.len + 1];
        cout << "strData 할당: " << (void*)strData << endl;
        strcpy(strData, rhs.strData); // 깊은 복사
        len = rhs.len; // 깊은 복사
    }
    // String(String &rhs) 생성자를 작성하지 않을 경우 s2.strData가 따로 할당이 되지 않았은데 s2도 똑같이 "안녕"으로 출력됨 -> s1.strData에 들어있는 주소값이 똑같이 복사됨(얕은 복사)
    
    ~String() {
        cout << "~String() 소멸자 호출" << endl;
        delete[] strData;
        cout << "strData 해제됨: " << (void*)strData << endl;
        strData = NULL;
    }
    
    char *GetStrData() const { // 반환 형식: char 포인터
        return strData;
    }
    
    int Getlen() const {
        return len;
    }
    
private:
    char *strData; // 동적 할당이 된 문자열의 주소값을 포인터에 저장
    int len;
};

int main() {
    String s1("안녕");
    String s2(s1); // 복사 생성자
    
    cout << s1.GetStrData() << endl;
    cout << s2.GetStrData() << endl;
}
