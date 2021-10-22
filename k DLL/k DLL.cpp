#include "Header.h"
#define PATHDLL L"DLL.dll"
#define PATHLIST L"Users.csv"
typedef U(_cdecl MyFunction)(LPWSTR, LPDWORD);//прототип импортируемой функции
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATHDLL))) return 1;//открываем DLL
    MyFunction UserList = (MyFunction)GetProcAddress(MyDLL, "CreateUserArray");//инициализируем указатель на функцию
    DWORD count = 0;//переменная для количества записей
    U* users = UserList(PATH, &count);// получили массив записей (вызвали функцию из DLL)
    //проверка, что все правильно считалось в массив.
    DWORD w;
    HINSTANCE FileHandle = CreateFile(L"1.txt", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    for (size_t i = 0; i < count; i++)
    {
        WriteFile(FileHandle, users[i].f, wcslen(users[i].f) * sizeof(WCHAR), &w, NULL);
    }
    CloseHandle(FileHandle);
    MyFunction UserList = (MyFunction)GetProcAddress(MyDLL, "CreateUser1Array");
    HINSTANCE File = CreateFile(L"2.txt", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    for (size_t g = 0; g < count; g++)
    {
        WriteFile(File, users[g].f, wcslen(users[g].f) * sizeof(WCHAR), &w, NULL);
    }
    CloseHandle(File);
    return 0;
}