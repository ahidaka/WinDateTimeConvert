#include <Windows.h>
#include <stdio.h>
#include <iostream>

VOID DateTime();

int main()
{
    std::cout << "Hello DateTime!\n";

	DateTime();
}


//! for debug
VOID GetHMS(_In_ FILETIME* FileTime, _Out_ DWORD* H, _Out_ DWORD* M, _Out_ DWORD* S, _Out_ DWORD* MSec)
{
	ULONGLONG   tBase, tMSec, tSec, tMin, tHour;

	tBase = (((ULONGLONG)FileTime->dwHighDateTime) << 32) + FileTime->dwLowDateTime;
	tMSec = (tBase / 10000000); // msec, ok
	tSec = tMSec % 60; // sec
	tMin = tMSec / 60 % 60; // min
	tHour = tMSec / 3600 % 24; // hour

	//printf(" %lld:%lld:%lld\n", t68, t67, t66);
	if (H)
		*H = ((DWORD)tHour);
	if (M)
		*M = ((DWORD)tMin);
	if (S)
		*S = ((DWORD)tSec);
	if (MSec)
		*MSec = tBase % 10000000 / 10000;
}

//! for debug
VOID CheckFileTime(_In_ FILETIME* CurrentTime)
{
	typedef struct _hms {
		DWORD hh;
		DWORD mm;
		DWORD ss;
		DWORD msec;
	} HMS;
	HMS curr;

	GetHMS(CurrentTime, &curr.hh, &curr.mm, &curr.ss, &curr.msec);

	printf("Curr=%02ld:%02ld:%02ld.%03ld\n",
		curr.hh, curr.mm, curr.ss, curr.msec);
}

//! file date debug
VOID GetFileTime(_In_ FILETIME* LocalFileTime, _Out_ PSTR Buffer)
{
	SYSTEMTIME systemTime;

	FileTimeToSystemTime(LocalFileTime, &systemTime);

	sprintf_s(Buffer, 32, "%04d/%02d/%02d %02d:%02d:%02d.%03d",
		systemTime.wYear,
		systemTime.wMonth,
		systemTime.wDay,
		systemTime.wHour,
		systemTime.wMinute,
		systemTime.wSecond,
		systemTime.wMilliseconds
	);
}

VOID DateTime()
{
	FILETIME currentTime;
	SYSTEMTIME st;
	//ULONGLONG currentTime64;

    enum { len = 32 };
	CHAR bCurrentTime[len];

	GetLocalTime(&st);
	SystemTimeToFileTime(&st, &currentTime);
	//currentTime64 = *((ULONGLONG*)&currentTime);

    GetFileTime(&currentTime, bCurrentTime);

	printf("<%s>\n", bCurrentTime);

	CheckFileTime(&currentTime);

}