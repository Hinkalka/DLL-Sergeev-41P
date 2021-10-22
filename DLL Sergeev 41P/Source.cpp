#include "../k DLL/Header.h"

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
    BOOL bAllWentWell = TRUE;
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    if (bAllWentWell)
        return TRUE;
    else
        return FALSE;
}

LPWSTR Reading(LPWSTR path)
{
    DWORD d = 0;
    HINSTANCE FileHandle = CreateFile(PATH, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    LPWSTR ReadString = calloc(100500, sizeof(WCHAR));
    ReadFile(FileHandle, ReadString, 100500 * sizeof(WCHAR), &d, NULL);
    CloseHandle(FileHandle);
    ReadString[d / 2] = '\n';
    ReadString[d / 2 + 1] = '\0';
    return ReadString;
}
LPWSTR Writing(LPWSTR path1)
{
    DWORD d = 0;
    HINSTANCE File = CreateFile(PATH1, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    LPWSTR WriteString = calloc(100500, sizeof(WCHAR));
    WriteFile(File, WriteString, 100500 * sizeof(WCHAR), &d, NULL);
    CloseHandle(File);
    /*WriteString[d / 2] = '\n';
    WriteString[d / 2 + 1] = '\0';*/
    return WriteString;
}

DWORD LpwstrToDword(LPWSTR str)
{
    DWORD dw = 0;
    for (size_t i = 0; i < wcslen(str); i++)
    {
        dw += (str[i] - '0');
        dw *= 10;
    }
    return dw / 10;
}
DWORD CountUsers(LPWSTR str)
{
    DWORD count = 0;
    for (size_t i = 0; i < wcslen(str); i++)
    {
        if (str[i] == L'\n') count++;
    }
    return count;
}

__declspec(dllexport) U* CreateUserArray(LPWSTR path, LPDWORD n)
{
    LPWSTR str = Reading(path);
    DWORD count = CountUsers(str);
    U* users = calloc(count, sizeof(U));
    DWORD poz = 0, zap = 0, ind = 0;
    LPWSTR strvozr = calloc(3, sizeof(TCHAR));
    for (size_t i = 0; i < wcslen(str); i++)
    {
        if (str[i] == '\n')
        {
            strvozr = calloc(3, sizeof(TCHAR));
            zap++;
            poz = 0;
            ind = 0;
        }
        else
        {
            if (str[i] == ';')
            {
                poz++;
                ind = 0;
            }
            else
            {
                if (poz == 0) users[zap].f[ind] = str[i];
                if (poz == 1) users[zap].i[ind] = str[i];
                if (poz == 2) users[zap].o[ind] = str[i];
                if (poz == 3)
                {
                    if (str[i] == '\r')
                    {
                        strvozr[ind] = '\0';
                        users[zap].vozr = LpwstrToDword(strvozr);
                        free(strvozr);
                    }
                    else strvozr[ind] = str[i];
                }
                ind++;
            }
        }
        /*LPWSTR str = Writing(PATH1);
        if (poz == 0)
        {
            users[zap].f[ind] = "Иванов";
            users[zap].f[ind] = "Иванова";
        }
        else
        {
            i++;
        }*/
    }
    *n = count;
    return users;
}
__declspec(dllexport) U* CreateUser1Array(LPWSTR path1, LPDWORD n)
{
    LPWSTR str = Writing(path1);
    DWORD count = CountUsers(str);
    U* users = calloc(count, sizeof(U));
    DWORD poz = 0, zap = 0, ind = 0;
    for (size_t i = 0; i < wcslen(str); i++)
    {
        if (poz == 0)
        {
            users[zap].f[ind] = "Иванов";
            users[zap].f[ind] = "Иванова";
        }
        else
        {
            i++;
        }
    }
}
